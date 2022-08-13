#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_territories_traits.hpp"

namespace blam
{
	struct c_game_engine_territories_variant : c_game_engine_base_variant
	{
		e_territories_variant_flags m_variant_flags;
		e_territories_respawn_on_capture_settings m_respawn_on_capture;
		e_territories_capture_time_settings m_capture_time;
		e_territories_sudden_death_settings m_sudden_death_time;
		c_player_traits m_defender_traits;
		c_player_traits m_attacker_traits;
		byte unused[0x50];
	};
	static_assert(sizeof(c_game_engine_territories_variant) == 0x260);
}