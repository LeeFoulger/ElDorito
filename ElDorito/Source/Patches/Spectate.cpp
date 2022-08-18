#include "Spectate.hpp"
#include "../Blam/BlamPlayers.hpp"
#include "../Blam/BlamInput.hpp"
#include "../Blam/BlamTime.hpp"
#include "../Blam/BlamObjects.hpp"
#include "../Blam/BlamNetwork.hpp"
#include "../ElDorito.hpp"
#include "../Patch.hpp"
#include "../Utils/String.hpp"
#include "../Web/Ui/ScreenLayer.hpp"
#include "../Web/Ui/WebTimer.hpp"
#include "../Modules/ModuleInput.hpp"
#include "../Modules/ModuleSettings.hpp"
#include "../ThirdParty/rapidjson/writer.h"
#include "../ThirdParty/rapidjson/stringbuffer.h"

#include <camera/game_director.hpp>

namespace
{
	void __fastcall game_director_update_hook(blam::c_game_director* director, void* unused, int a2);
	void __cdecl input_abstraction_get_player_look_angular_velocity_hook(long controller_index, blam::real_euler_angles2d* angular_velocity);

	struct
	{
		bool Active;
		uint32_t PlayerIndex;
	} state;
}

namespace Patches::Spectate
{
	void ApplyAll()
	{
		Pointer(0x01671F5C).Write((uint32_t)game_director_update_hook);
		Hook(0x32A8D6, input_abstraction_get_player_look_angular_velocity_hook, HookFlags::IsCall).Apply();
	}
}

namespace
{
	int GetNetworkPlayerIndex(uint32_t playerDatumIndex)
	{
		const auto player_globals_get_network_address = (uint8_t*(*)(uint16_t playerIndex))(0x541EB0);

		auto player = Blam::Players::GetPlayers().Get(playerDatumIndex);
		if (!player)
			return -1;
		
		// this is how it's done in simulation
		auto playerGlobalsIndex = *(uint16_t*)((uint8_t*)player + 0x24);
		if (playerGlobalsIndex == -1)
			return -1;
		auto xnkaddr = *(uint8_t**)ElDorito::GetMainTls(0x44) + 0x10 * (playerGlobalsIndex + 1);
		auto session = Blam::Network::GetActiveSession();
		for (auto i = session->MembershipInfo.FindFirstPeer(); i != -1; i = session->MembershipInfo.FindNextPeer(i))
		{
			auto peerAddress = (uint8_t*)&session->MembershipInfo.Peers[i];
			if (!memcmp(xnkaddr, peerAddress, 0x10))
				return session->MembershipInfo.GetPeerPlayer(i);
		}

		return -1;
	}

	void NotifyPlayerChanged(Blam::DatumHandle playerDatumIndex)
	{
		auto player = Blam::Players::GetPlayers().Get(playerDatumIndex);
		if (!player)
			return;

		auto networkPlayerIndex = GetNetworkPlayerIndex(playerDatumIndex);
		if (networkPlayerIndex == -1)
			return;

		auto playerDisplayName = Utils::String::ThinString(player->Properties.DisplayName);
		auto teamIndex = player->Properties.TeamIndex;

		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);

		jsonWriter.StartObject();
		jsonWriter.Key("playerIndex");
		jsonWriter.Uint(networkPlayerIndex);
		jsonWriter.Key("teamIndex");
		jsonWriter.Uint(teamIndex);
		jsonWriter.Key("displayName");
		jsonWriter.String(playerDisplayName.c_str());
		jsonWriter.EndObject();

		Web::Ui::ScreenLayer::Notify("spectate_change", jsonBuffer.GetString(), true);
	}

	void NotifyEnded()
	{
		Web::Ui::ScreenLayer::Notify("spectate_end", "{}", true);
	}

	bool IsSpectating(int localPlayerIndex)
	{
		static auto game_engine_in_state = (bool(*)(char state))(0x005523A0);
		const auto game_engine_round_in_progress = (bool(*)())(0x00550F90);

		if (localPlayerIndex == -1)
			return false;

		if (!game_engine_round_in_progress() || game_engine_in_state(4))
			return false;

		auto playerIndex = Blam::Players::GetLocalPlayer(localPlayerIndex);
		if (playerIndex == Blam::DatumHandle::Null)
			return false;

		auto player = Blam::Players::GetPlayers().Get(playerIndex);
		if (player->SlaveUnit != Blam::DatumHandle::Null)
			return false;

		auto secondsUntilSpawn = Pointer(player)(0x2CBC).Read<int>();

		return player->SlaveUnit == Blam::DatumHandle::Null && secondsUntilSpawn > 1 
			&& !(Pointer(player)(0x4).Read<uint32_t>() & 8u);
	}

	void __fastcall game_director_update_hook(blam::c_game_director* director, void* unused, int a2)
	{
		static void(__thiscall* game_director_update)(blam::c_game_director*, long) = reinterpret_cast<decltype(game_director_update)>(0x007219A0);
		
		if (IsSpectating(director->m_user_index))
		{
			if (!state.Active)
			{
				state.Active = true;
				state.PlayerIndex = -1;

				// prevent switching players instantly
				for (int i = Blam::Input::eGameActionNextPlayer; i <= Blam::Input::eGameActionPrevPlayer; i++)
				{
					auto action = Blam::Input::GetActionState(Blam::Input::GameAction(i));
					action->Ticks = 0;
					action->Flags |= Blam::Input::eActionStateFlagsHandled;
				}
			}

			if (state.Active)
			{
				if (state.PlayerIndex != director->m_output_user_index)
				{
					state.PlayerIndex = director->m_output_user_index;
					NotifyPlayerChanged(director->m_output_user_index);
				}
			}
		}
		else
		{
			if (state.Active)
			{
				state.Active = false;
				state.PlayerIndex = -1;
				NotifyEnded();
			}
		}

		game_director_update(director, a2);
	}

	void __cdecl input_abstraction_get_player_look_angular_velocity_hook(long controller_index, blam::real_euler_angles2d* angular_velocity)
	{
		auto& moduleInput = Modules::ModuleInput::Instance();
		Modules::ModuleSettings& moduleSettings = Modules::ModuleSettings::Instance();
		Blam::Input::BindingsTable* bindings = moduleInput.GetBindings();

		float sens = moduleInput.VarSpectateSensitivity->ValueFloat;

		// the controller defaults are unreasonably sensitive
		const bool isUsingController = *(bool*)0x0244DE98;
		if (!isUsingController)
		{
			angular_velocity->yaw = (moduleSettings.VarMouseSensitivityHorizontal->ValueInt / 100.0f * 360.0f) * 0.017453294f * sens;
			angular_velocity->pitch = (moduleSettings.VarMouseSensitivityVertical->ValueInt / 100.0f * 360.0f) * 0.017453294f * sens;
			return;
		}

		sens *= 0.015f;
		angular_velocity->yaw = bindings->ControllerSensitivityX * 0.017453292f * sens;
		angular_velocity->pitch = bindings->ControllerSensitivityY * 0.017453292f * sens;
	}
}