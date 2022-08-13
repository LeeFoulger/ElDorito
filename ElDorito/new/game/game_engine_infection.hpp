#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_infection_traits.hpp"

namespace blam
{
	struct c_game_engine_infection_variant : c_game_engine_base_variant
	{
		e_infection_variant_flags m_variant_flags;
		e_infection_safe_havens_settings m_safe_havens;
		e_infection_next_zombie_settings m_next_zombie;
		e_infection_initial_zombie_count_settings m_initial_zombie_count;
		short m_safe_haven_movement_time;                                 // 0 is no movement
		char m_zombie_kill_points;
		char m_infection_points;
		char m_safe_haven_arrival_points;
		char m_suicide_points;
		char m_betrayal_points;
		char m_last_man_bonus_points;
		c_player_traits m_zombie_traits;
		c_player_traits m_first_zombie_traits;
		c_player_traits m_safe_haven_defender_traits;
		c_player_traits m_last_human_traits;
		byte pad[4];
		byte unused[0x10];
	};
	static_assert(sizeof(c_game_engine_infection_variant) == 0x260);

}