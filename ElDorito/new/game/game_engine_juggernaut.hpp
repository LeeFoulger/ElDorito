#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_juggernaut_traits.hpp"

namespace blam
{
	struct c_game_engine_juggernaut_variant : c_game_engine_base_variant
	{
		short m_score_to_win_round;
		short m_score_unknown;                                          // halo online specific
		short m_unknown;                                                // always set to '0'
		e_juggernaut_initial_juggernaut_settings m_initial_juggernaut;
		e_juggernaut_next_juggernaut_settings m_next_juggernaut;
		e_juggernaut_variant_flags m_variant_flags;
		e_juggernaut_zone_movement_settings m_zone_movement;
		e_juggernaut_zone_order_settings m_zone_order;
		char m_kill_points;
		char m_juggeraut_kill_points;
		char m_kill_as_juggernaut_points;
		char m_destination_arrival_points;
		char m_suicide_points;
		char m_betrayal_points;
		char m_juggernaut_delay;
		c_player_traits m_juggernaut_traits;
		byte pad[2];
		byte unused[0x60];
	};
	static_assert(sizeof(c_game_engine_juggernaut_variant) == 0x260);
}