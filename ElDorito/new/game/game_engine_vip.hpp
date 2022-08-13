#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_vip_traits.hpp"

namespace blam
{
	struct c_game_engine_vip_variant : c_game_engine_base_variant
	{
		short m_score_to_win_round;
		short m_score_unknown;                         // halo online specific
		e_vip_variant_flags m_variant_flags;
		char m_kill_points;
		char m_takedown_points;
		char m_kill_as_vip_points;
		char m_vip_death_points;
		char m_destination_arrival_points;
		char m_suicide_points;
		char m_betrayal_points;
		char m_vip_suicide_points;
		e_vip_selection_settings m_vip_selection;
		e_vip_zone_movement_settings m_zone_movement;
		e_vip_zone_order_settings m_zone_order;
		byte pad[1];
		short m_influence_radius;
		c_player_traits m_vip_team_traits;
		c_player_traits m_vip_influence_traits;
		c_player_traits m_vip_traits;
		byte unused[0x28];
	};
	static_assert(sizeof(c_game_engine_vip_variant) == 0x260);
}