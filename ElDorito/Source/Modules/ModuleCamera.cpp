#include "ModuleCamera.hpp"
#include <sstream>
#include "../ElDorito.hpp"
#include "../Blam/BlamNetwork.hpp"
#include "../Patches/Ui.hpp"
#include "../Blam/BlamInput.hpp"
#include "ModuleInput.hpp"
#include "../Blam/Memory/TlsData.hpp"
#include "../Blam/Math/MathUtil.hpp"

namespace
{
	enum CameraDefinitionType : int
	{
		Position = 0,
		PositionShift = 1,
		LookShift = 2,
		Depth = 3,
		FieldOfView = 4,
		LookVectors = 5
	};

	bool flying = false;

	// determine which camera definitions are editable based on the current camera mode
	bool __stdcall IsCameraDefinitionEditable(CameraDefinitionType definition)
	{
		auto mode = Utils::String::ToLower(Modules::ModuleCamera::Instance().VarCameraMode->ValueString);
		if (!mode.compare("first") || !mode.compare("third"))
		{
			if (definition == CameraDefinitionType::PositionShift ||
				definition == CameraDefinitionType::LookShift ||
				definition == CameraDefinitionType::Depth)
			{
				return true;
			}
		}
		else if (!mode.compare("flying") || !mode.compare("static"))
		{
			return true;
		}

		return false;
	}

	// hook @ 0x61440D - allows for the modification of specific camera components based on current perspective
	__declspec(naked) void UpdateCameraDefinitions()
	{
		__asm
		{
			pushad
			shr		esi, 1						; convert camera definition offset to an index
			push	esi							; CameraDefinitionType
			call	IsCameraDefinitionEditable
			test	al, al
			popad
			jnz		skip
			mov		eax, [eax + ecx * 4]		; get data(definition + item * 4)
			mov		[edi + ecx * 4], eax		; store it in the 3rd camera array
			skip:
			push	0614413h
			ret
		}
	}

	// hook @ 0x614818 - allows for the modification of specific camera components based on current perspective
	__declspec(naked) void UpdateCameraDefinitionsAlt1()
	{
		__asm
		{
			pushad
			shr		esi, 1
			push	esi
			call	IsCameraDefinitionEditable
			test	al, al
			popad
			jnz		skip
			movss   dword ptr [edx + eax * 4], xmm0
			skip:
			push	061481Dh
			ret
		}
	}

	// hook @ 0x6148BE - allows for the modification of specific camera components based on current perspective
	__declspec(naked) void UpdateCameraDefinitionsAlt2()
	{
		__asm
		{
			pushad
			shr		esi, 1
			push	esi
			call	IsCameraDefinitionEditable
			test	al, al
			popad
			jnz		skip
			movss   dword ptr [edx + eax * 4], xmm1
			skip:
			push	06148C3h
			ret
		}
	}

	// hook @ 0x614902 - allows for the modification of specific camera components based on current perspective
	__declspec(naked) void UpdateCameraDefinitionsAlt3()
	{
		__asm
		{
			pushad
			shr		esi, 1
			push	esi
			call	IsCameraDefinitionEditable
			test	al, al
			popad
			jnz		skip
			movss   dword ptr [edi + eax * 4], xmm0
			skip:
			push	0614907h
			ret
		}
	}


	bool VariableCameraCrosshairUpdate(const std::vector<std::string>& Arguments, std::string& returnInfo)
	{
		Modules::ModuleCamera::Instance().CenteredCrosshairFirstPersonPatch.Apply(!Modules::ModuleCamera::Instance().VarCameraCenteredCrosshairFirst->ValueInt);
		Modules::ModuleCamera::Instance().CenteredCrosshairThirdPersonPatch.Apply(!Modules::ModuleCamera::Instance().VarCameraCenteredCrosshairThird->ValueInt);
		return true;
	}

	bool VariableCameraFovUpdate(const std::vector<std::string>& Arguments, std::string& returnInfo)
	{
		auto &moduleCamera = Modules::ModuleCamera::Instance();
		float value = moduleCamera.VarCameraFov->ValueFloat;
		Pointer::Base(0x1F01D98).Write(value);
		Pointer::Base(0x149D42C).Write(value);
		return true;
	}

	bool VariableCameraHideHudUpdate(const std::vector<std::string>& Arguments, std::string& returnInfo)
	{
		unsigned long value = Modules::ModuleCamera::Instance().VarCameraHideHud->ValueInt;

		std::string status = "shown.";
		bool statusBool = value != 0;
		if (statusBool)
			status = "hidden.";

		Modules::ModuleCamera::Instance().HideHudPatch.Apply(!statusBool);

		Patches::Ui::UpdateHUDDistortion();

		returnInfo = "HUD " + status;
		return true;
	}

	bool VariableCameraSpeedUpdate(const std::vector<std::string>& Arguments, std::string& returnInfo)
	{
		float speed = Modules::ModuleCamera::Instance().VarCameraSpeed->ValueFloat;

		std::stringstream ss;
		ss << "Camera speed set to " << speed;
		returnInfo = ss.str();

		return true;
	}

	//bool VariableCameraSave(const std::vector<std::string>& Arguments, std::string& returnInfo)
	//{
	//	auto mode = Utils::String::ToLower(Modules::ModuleCamera::Instance().VarCameraMode->ValueString);
	//	Pointer &directorGlobalsPtr = ElDorito::GetMainTls(GameGlobals::Director::TLSOffset)[0];

	//	// only allow saving while in flycam or static modes
	//	if (mode != "flying" && mode != "static")
	//		return true;

	//	// TODO: finish

	//	return true;
	//}
	//
	//bool VariableCameraLoad(const std::vector<std::string>& Arguments, std::string& returnInfo)
	//{
	//	auto mode = Utils::String::ToLower(Modules::ModuleCamera::Instance().VarCameraMode->ValueString);
	//	Pointer &directorGlobalsPtr = ElDorito::GetMainTls(GameGlobals::Director::TLSOffset)[0];

	//	// only allow loading while in flycam or static modes
	//	if (mode != "flying" && mode != "static")
	//		return true;

	//	// TODO: finish

	//	return true;
	//}

	bool VariableCameraPositionUpdate(const std::vector<std::string>& Arguments, std::string& returnInfo)
	{
		Blam::Memory::s_director_globals& director_globals = *((Blam::Memory::s_thread_local_storage*)ElDorito::GetMainTls())->director_globals;
		Blam::c_director& director = director_globals.directors[0];

		Blam::Memory::s_observer_globals& g_observer_globals = *((Blam::Memory::s_thread_local_storage*)ElDorito::GetMainTls())->g_observer_globals;
		Blam::s_observer& observer = g_observer_globals.observers[director.m_user_index];

		float(&position)[3] = observer.positions_focus_position; // 0x834, 0x838, 0x83C

		if (Arguments.size() < 3) {
			std::stringstream ss;
			ss << "X: " << position[0] << ", Y: " << position[1] << ", Z: " << position[2];
			returnInfo = ss.str();
			return false;
		}

		// update position
		position[0] = std::stof(Arguments[0]);// X
		position[1] = std::stof(Arguments[1]);// Y
		position[2] = std::stof(Arguments[2]);// Z
		return true;
	}

	bool VariableCameraModeUpdate(const std::vector<std::string>&Arguments, std::string & returnInfo)
	{
		auto mode = Utils::String::ToLower(Modules::ModuleCamera::Instance().VarCameraMode->ValueString);

		flying = false;

		Blam::Memory::s_director_globals& director_globals = *((Blam::Memory::s_thread_local_storage*)ElDorito::GetMainTls())->director_globals;
		Blam::c_director& director = director_globals.directors[0];
		Blam::s_director_info& director_info = director_globals.infos[director.m_user_index];

		Blam::Memory::s_observer_globals& g_observer_globals = *((Blam::Memory::s_thread_local_storage*)ElDorito::GetMainTls())->g_observer_globals;
		Blam::s_observer& observer = g_observer_globals.observers[director.m_user_index];

		// get new camera perspective function camera_vtable
		Blam::e_camera_mode camera_mode = Blam::k_camera_mode_null;
		if (!mode.compare("default"))
		{
		}
		else if (!mode.compare("first")) // c_first_person_camera
		{
			camera_mode = Blam::_camera_mode_first_person; // 0x166ACB0;
			observer.positions_focus_offset[0] = 0.0f;
			observer.positions_focus_offset[1] = 0.0f;
			observer.positions_focus_offset[2] = 0.0f;
			observer.positions_look_shift[0] = 0.0f;
			observer.positions_look_shift[1] = 0.0f;
			observer.positions_focus_distance = 0.0f;
		}
		else if (!mode.compare("third")) // c_following_camera
		{
			camera_mode = Blam::_camera_mode_following; // 0x16724D4;
			observer.positions_focus_offset[0] = 0.0f;
			observer.positions_focus_offset[1] = 0.0f;
			observer.positions_focus_offset[2] = 0.1f;
			observer.positions_look_shift[0] = 0.0f;
			observer.positions_look_shift[1] = 0.0f;
			observer.positions_focus_distance = 0.5f;
			observer.horizontal_field_of_view = 110.0f * Blam::Math::RAD;
		}
		else if (!mode.compare("flying")) // c_flying_camera
		{
			camera_mode = Blam::_camera_mode_flying; // 0x16726D0;
			observer.positions_focus_offset[0] = 0.0f;
			observer.positions_focus_offset[1] = 0.0f;
			observer.positions_focus_offset[2] = 0.0f;
			observer.positions_look_shift[0] = 0.0f;
			observer.positions_look_shift[1] = 0.0f;
			observer.positions_focus_distance = 0.0f;
			flying = true;
		}
		else if (!mode.compare("static")) // c_static_camera
		{
			camera_mode = Blam::_camera_mode_static; // 0x16728A8;
			observer.positions_focus_offset[0] = 0.0f;
			observer.positions_focus_offset[1] = 0.0f;
			observer.positions_focus_offset[2] = 0.0f;
			observer.positions_look_shift[0] = 0.0f;
			observer.positions_look_shift[1] = 0.0f;
			observer.positions_focus_distance = 0.0f;
		}
		else
		{
			returnInfo = "valid modes: default, first, third, flying, static";
			return false;
		}

		/*
		else if (!mode.compare("dead")) // c_dead_camera
			camera_mode = Blam::_camera_mode_dead; // 0x16725DC;
		else if (!mode.compare("scripted")) // c_scripted_camera
			camera_mode = Blam::_camera_mode_scripted; // 0x167280C;
		else if (!mode.compare("orbiting")) // c_orbiting_camera
			camera_mode = Blam::_camera_mode_orbiting; // 0x167265C;
		else if (!mode.compare("debug")) // c_camera
			camera_vtable = 0x1672130;
		else if (!mode.compare("null")) // c_null_camera - crashes
			camera_mode = Blam::k_camera_mode_null; // 0x165A6E4;
		else if (!mode.compare("authored")) // c_authored_camera
			camera_mode = Blam::_camera_mode_authored; // 0x1672920;
		*/

		// prevent the game from updating certain camera values depending on the current camera mode
		Modules::ModuleCamera::Instance().CameraPermissionHook.Apply(mode == "default");
		Modules::ModuleCamera::Instance().CameraPermissionHookAlt1.Apply(mode == "default");
		Modules::ModuleCamera::Instance().CameraPermissionHookAlt2.Apply(mode == "default");
		Modules::ModuleCamera::Instance().CameraPermissionHookAlt3.Apply(mode == "default");

		// prevent the game from automatically switching camera modes depending on the current mode
		Modules::ModuleCamera::Instance().Debug1CameraPatch.Apply(mode == "default");
		Modules::ModuleCamera::Instance().Debug2CameraPatch.Apply(mode == "default");
		Modules::ModuleCamera::Instance().ThirdPersonPatch.Apply(mode == "default");
		Modules::ModuleCamera::Instance().ThirdPersonPatch2.Apply(mode != "third");
		Modules::ModuleCamera::Instance().FirstPersonPatch.Apply(mode == "default");
		Modules::ModuleCamera::Instance().DeadPersonPatch.Apply(mode == "default");

		// hides the hud when flying or in static camera mode
		Modules::ModuleCamera::Instance().HideHudPatch.Apply(mode != "flying" && mode != "static");

		// prevents death from resetting look angles when in static camera mode
		Modules::ModuleCamera::Instance().StaticILookVectorPatch.Apply(mode != "static");
		Modules::ModuleCamera::Instance().StaticKLookVectorPatch.Apply(mode != "static");

		// disable player movement while in flycam
		Pointer playerControlGlobalsPtr(ElDorito::GetMainTls(GameGlobals::Input::TLSOffset)[0]);
		playerControlGlobalsPtr(GameGlobals::Input::DisablePlayerInputIndex).Write(mode == "flying");

		if (camera_mode != Blam::k_camera_mode_null)
		{
			unsigned long camera_vtable = Blam::camera_mode_vtable_get(camera_mode);
			Blam::c_camera& camera = director.m_camera.camera;

			// update camera vtable
			Blam::c_camera_vtbl* old_camera_vtable = camera.__vftable;
			camera.__vftable = reinterpret_cast<Blam::c_camera_vtbl*>(camera_vtable);

			long director_perspective = 3;
			//if (game_in_progress())
			{
				director_perspective = camera.__vftable->get_perspective(&camera);
				if (!director_perspective)
					director_perspective = director.m_transition_time > 0.0;
				//if (game_is_ui_shell())
				//	director_perspective = 3;
			}

			if (director_info.director_perspective != director_perspective || director_info.camera_mode != camera_mode)
			{
				director_info.director_perspective = (Blam::e_director_perspective)director_perspective;
				director_info.camera_mode = camera_mode;

				void(*first_person_weapon_perspective_changed)(long) =
					reinterpret_cast<decltype(first_person_weapon_perspective_changed)>(0xA9C550);
				first_person_weapon_perspective_changed(director.m_user_index);
			}
		}

		return true;
	}

	bool VariableCameraShowCoordinatesUpdate(const std::vector<std::string>& Arguments, std::string& returnInfo)
	{
		auto session = Blam::Network::GetActiveSession();
		if (!session || Arguments.size() != 1)
		{
			returnInfo = "Unable to enable debug coordinates!";
			return false;
		}

		std::string status = "disabled.";

		if (Modules::ModuleCamera::Instance().VarCameraShowCoordinates->ValueInt != 0) {
			Modules::ModuleCamera::Instance().ShowCoordinatesPatch.Apply();
			status = "enabled.";
		}
		else {
			Modules::ModuleCamera::Instance().ShowCoordinatesPatch.Reset();
			status = "disabled.";
		}


		returnInfo = "Debug coordinates " + status;
		return true;
	}
}

namespace Modules
{
	ModuleCamera::ModuleCamera() : ModuleBase("Camera"),
		CameraPermissionHook(0x21440D, UpdateCameraDefinitions),
		CameraPermissionHookAlt1(0x214818, UpdateCameraDefinitionsAlt1),
		CameraPermissionHookAlt2(0x2148BE, UpdateCameraDefinitionsAlt2),
		CameraPermissionHookAlt3(0x214902, UpdateCameraDefinitionsAlt3),
		Debug1CameraPatch(0x325A80, 0x90, 6),
		Debug2CameraPatch(0x191525, 0x90, 6),
		ThirdPersonPatch(0x328640, 0x90, 6),
		ThirdPersonPatch2(0x321BA5, 0x90, 2), // hack to fix third person camera glitching
		FirstPersonPatch(0x25F420, 0x90, 6),
		DeadPersonPatch(0x329E6F, 0x90, 6),
		StaticILookVectorPatch(0x211433, 0x90, 8),
		StaticKLookVectorPatch(0x21143E, 0x90, 6),
		HideHudPatch(0x12B5A5C, { 0xC3, 0xF5, 0x48, 0x40 }), // 3.14f in hex form
		CenteredCrosshairFirstPersonPatch(0x25FA43, { 0x31, 0xC0, 0x90, 0x90 }),
		CenteredCrosshairThirdPersonPatch(0x32989C, { 0x31, 0xC0, 0x90, 0x90 }),
		ShowCoordinatesPatch(0x192064, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 })
	{
		// TODO: commands for setting camera speed, positions, save/restore etc.

		VarCameraCenteredCrosshairFirst = AddVariableInt("CenteredCrosshairFirst", "crosshair_first", "Controls whether the crosshair should be centered in first person", eCommandFlagsArchived, 0, VariableCameraCrosshairUpdate);
		VarCameraCenteredCrosshairFirst->ValueIntMin = 0;
		VarCameraCenteredCrosshairFirst->ValueIntMax = 1;

		VarCameraCenteredCrosshairThird = AddVariableInt("CenteredCrosshairThird", "crosshair_third", "Controls whether the crosshair should be centered in third person", eCommandFlagsArchived, 1, VariableCameraCrosshairUpdate);
		VarCameraCenteredCrosshairThird->ValueIntMin = 0;
		VarCameraCenteredCrosshairThird->ValueIntMax = 1;

		VarCameraFov = AddVariableFloat("FOV", "fov", "The cameras field of view", eCommandFlagsArchived, 90.f, VariableCameraFovUpdate);
		VarCameraFov->ValueFloatMin = 55.f;
		VarCameraFov->ValueFloatMax = 120.f;

		VarCameraHideHud = AddVariableInt("HideHUD", "hud", "Toggles the HUD", eCommandFlagsArchived, 0, VariableCameraHideHudUpdate);
		VarCameraHideHud->ValueIntMin = 0;
		VarCameraHideHud->ValueIntMax = 1;

		VarCameraSpeed = AddVariableFloat("Speed", "camera_speed", "The camera speed", eCommandFlagsArchived, 0.1f, VariableCameraSpeedUpdate);
		VarCameraSpeed->ValueFloatMin = 0.01f;
		VarCameraSpeed->ValueFloatMax = 5.0f;

		VarCameraPosition = AddCommand("Position", "camera_position", "The cameras position, Doesn't work when camera mode is set to default", eCommandFlagsNone, VariableCameraPositionUpdate, { "X Coordinate", "Y Coordinate", "Z Coordinate" });

		this->VarCameraMode = AddVariableString("Mode", "camera_mode", "Camera mode, valid modes: default, first, third, flying, static",
			(CommandFlags)(eCommandFlagsDontUpdateInitial | eCommandFlagsCheat), "default", VariableCameraModeUpdate);

		VarCameraShowCoordinates = AddVariableInt("ShowCoordinates", "coords", "The cameras field of view", eCommandFlagsArchived, 0, VariableCameraShowCoordinatesUpdate);
		VarCameraShowCoordinates->ValueIntMin = 0;
		VarCameraShowCoordinates->ValueIntMax = 1;
	}

	void ModuleCamera::UpdatePosition()
	{
		if (!flying)
			return;

		Blam::Memory::s_director_globals& director_globals = *((Blam::Memory::s_thread_local_storage*)ElDorito::GetMainTls())->director_globals;
		Blam::c_director& director = director_globals.directors[0];

		Blam::Memory::s_observer_globals& g_observer_globals = *((Blam::Memory::s_thread_local_storage*)ElDorito::GetMainTls())->g_observer_globals;
		Blam::s_observer& observer = g_observer_globals.observers[director.m_user_index];

		Pointer playerControlGlobalsPtr(ElDorito::GetMainTls(GameGlobals::Input::TLSOffset)[0]);

		float moveDelta = Modules::ModuleCamera::Instance().VarCameraSpeed->ValueFloat;
		float lookDelta = 0.01f;	// not used yet

		// current values
		float hLookAngle = playerControlGlobalsPtr(0x30C).Read<float>();
		float vLookAngle = playerControlGlobalsPtr(0x310).Read<float>();
		float xPos = observer.positions_focus_position[0];
		float yPos = observer.positions_focus_position[1];
		float zPos = observer.positions_focus_position[2];
		float xShift = observer.positions_focus_offset[0];
		float yShift = observer.positions_focus_offset[1];
		float zShift = observer.positions_focus_offset[2];
		float hShift = observer.positions_look_shift[0];
		float vShift = observer.positions_look_shift[1];
		float depth = observer.positions_focus_distance;
		float fov = observer.horizontal_field_of_view;
		float iForward = observer.positions_forward[0];
		float jForward = observer.positions_forward[1];
		float kForward = observer.positions_forward[2];
		float iUp = observer.positions_up[0];
		float jUp = observer.positions_up[1];
		float kUp = observer.positions_up[2];
		float iRight = cos(hLookAngle + 3.14159265359f / 2);
		float jRight = sin(hLookAngle + 3.14159265359f / 2);

		struct ControllerAxes { int16_t LeftX, LeftY, RightX, RightY; };
		auto& controllerAxes = *(ControllerAxes*)(0x0244D1F0 + 0x2F4);
		bool controllerEnabled = Pointer::Base(0x204DE98).Read<bool>();

		if (GetActionState(Blam::Input::eGameActionUiLeftBumper)->Ticks > 0)
			zPos -= moveDelta;

		if (GetActionState(Blam::Input::eGameActionUiRightBumper)->Ticks > 0)
			zPos += moveDelta;

		if (GetActionState(Blam::Input::eGameActionMoveForward)->Ticks > 0 || GetActionState(Blam::Input::eGameActionMoveBack)->Ticks > 0 || (controllerEnabled && controllerAxes.LeftY != 0))
		{
			float mod = 1;
			if (controllerEnabled)
				mod = controllerAxes.LeftY / 32768.0f;
			else if (GetActionState(Blam::Input::eGameActionMoveBack)->Ticks > 0)
				mod = -1;

			xPos += iForward * (moveDelta * mod);
			yPos += jForward * (moveDelta * mod);
			zPos += kForward * (moveDelta * mod);
		}

		if (GetActionState(Blam::Input::eGameActionMoveLeft)->Ticks > 0 || GetActionState(Blam::Input::eGameActionMoveRight)->Ticks > 0 || (controllerEnabled && controllerAxes.LeftX != 0))
		{
			float mod = 1;
			if (controllerEnabled)
				mod = controllerAxes.LeftX / 32768.0f;
			else if (GetActionState(Blam::Input::eGameActionMoveLeft)->Ticks > 0)
				mod = -1;

			xPos -= iRight * (moveDelta * mod);
			yPos -= jRight * (moveDelta * mod);
		}

		if (GetAsyncKeyState('Z') & 0x8000)
		{
			fov -= 0.003f;
		}
		if (GetAsyncKeyState('C') & 0x8000)
		{
			fov += 0.003f;
		}

		// update position
		observer.positions_focus_position[0] = xPos;
		observer.positions_focus_position[1] = yPos;
		observer.positions_focus_position[2] = zPos;

		// update look angles
		observer.positions_forward[0] = cos(hLookAngle) * cos(vLookAngle);
		observer.positions_forward[1] = sin(hLookAngle) * cos(vLookAngle);
		observer.positions_forward[2] = sin(vLookAngle);
		observer.positions_up[0] = -cos(hLookAngle) * sin(vLookAngle);
		observer.positions_up[1] = -sin(hLookAngle) * sin(vLookAngle);
		observer.positions_up[2] = cos(vLookAngle);

		observer.horizontal_field_of_view = fov;
	}

	bool ModuleCamera::IsFlying() const
	{
		return flying;
	}
}
