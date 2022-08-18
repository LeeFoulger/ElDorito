#include "PatchCamera.hpp"
#include "../Blam/BlamObjects.hpp"
#include "../Modules/ModuleCamera.hpp"
#include <cstdint>

#include <camera/camera.hpp>
#include <camera/director.hpp>

namespace
{
	float GetScriptedCameraFovHook();
	void DeadCameraFovHook();
	void __fastcall following_camera_update_hook(blam::c_following_camera* following_camera, void* unused, int localPlayerIndex, int a4, blam::s_observer_command* command);

	long director_get_perspective_hook(long user_index);
	bool director_in_unit_perspective_hook(long user_index);

	bool LodIncreased = false;
}

namespace Patches::Camera
{
	void ApplyAll()
	{
		Hook(0x32E18C, GetScriptedCameraFovHook, HookFlags::IsCall).Apply();
		Hook(0x2122C5, DeadCameraFovHook).Apply();
		Pointer(0x016724DC).Write(uint32_t(&following_camera_update_hook));

		Hook(0x001C211F, director_get_perspective_hook, HookFlags::IsCall).Apply();
		Hook(0x00645340, director_get_perspective_hook, HookFlags::IsCall).Apply();
		Hook(0x00645396, director_in_unit_perspective_hook, HookFlags::IsCall).Apply();
	}

	const char *IncreaseLOD()
	{
		std::string result;

		// LOD patches compliments of zedd
		// Patch for lod dword_176DB40 (2.0) -> dword_176DB50 (10.0)
		// Patch to apply cine lod to everything
		if (!LodIncreased)
		{
			memset(Pointer(0xA65EBB), 0x50, 1);
			memset(Pointer(0xA1962C), 0x90, 2);
			LodIncreased = true;
			result = "Lod increased: true";
		}
		else
		{
			memset(Pointer(0xA65EBB), 0x40, 1);
			memset(Pointer(0xA1962C), 0x74, 1);
			memset(Pointer(0xA1962D), 0x10, 1);
			LodIncreased = false;
			result = "Lod increased: false";
		}
		return result.c_str();
	}
}

namespace
{
	float GetScriptedCameraFovHook()
	{
		const auto game_is_mainmenu = (bool(*)())(0x00531E90);

		auto fov = 0.0f;

		if (game_is_mainmenu())
		{
			fov = 70.0f;
		}
		else
		{
			auto scriptedCameraFov = *(float*)0x018ECE00;
			if (scriptedCameraFov == 0.0f)
				fov = *(float*)0x18BB1C8;
			else
				fov = scriptedCameraFov;
		}

		return fov * 0.017453292f;
	}

	float *GetPreferedCameraFovPointer()
	{
		return &Modules::ModuleCamera::Instance().VarCameraFov->ValueFloat;
	}

	__declspec(naked) void DeadCameraFovHook()
	{
		__asm
		{
			test dword ptr[ecx], 0x800
			jnz NOT_DEAD
			pushad
			call GetPreferedCameraFovPointer
			movss xmm0, [eax]
			popad
			mov eax, 0x006122E0
			jmp eax
			NOT_DEAD:
			mov eax, 0x0061230A
			jmp eax
		}
	}

	void __fastcall following_camera_update_hook(blam::c_following_camera *following_camera, void *unused, int localPlayerIndex, int a4, blam::s_observer_command* command)
	{
		const auto c_following_camera__update = (void(__thiscall *)(blam::c_following_camera*, int, int a4, blam::s_observer_command*))(0x00729730);
		const auto &moduleCamera = Modules::ModuleCamera::Instance();

		c_following_camera__update(following_camera, localPlayerIndex, a4, command);

		// scale fov by prefered fov
		command->field_of_view = command->field_of_view / moduleCamera.VarCameraFov->DefaultValueFloat * moduleCamera.VarCameraFov->ValueFloat;

		// scale position shift and depth with target object scale
		auto object_index = following_camera->m_object_index;
		if (object_index == -1)
			return;

		auto targetObject = Blam::Objects::Get(object_index);
		if (!targetObject)
			return;	

		auto s = (float)std::pow(targetObject->Scale, 0.5);
		command->focus_distance *= s;

		// TODO: add operator* from `RealVector3D` to `real_vector3d`
		command->focus_offset.i *= s;
		command->focus_offset.j *= s;
		command->focus_offset.k *= s;
	}

	long director_get_perspective_hook(long user_index)
	{
		if (blam::director_get(user_index))
			return blam::director_get_perspective(user_index);

		static long(*director_get_perspective)(long) = reinterpret_cast<decltype(director_get_perspective)>(0x00591A40);
		return director_get_perspective(user_index);
	}

	bool director_in_unit_perspective_hook(long user_index)
	{
		if (blam::director_get(user_index))
			return ((1 << blam::director_get_perspective(user_index)) & 3) != 0;

		static bool(*director_in_unit_perspective)(long) = reinterpret_cast<decltype(director_in_unit_perspective)>(0x00591BA0);
		return director_in_unit_perspective(user_index);
	}
}
