#pragma once

#include "cseries/cseries.hpp"
#include "game_engine_variant.hpp"
#include "game_engine_vip_traits.hpp"

namespace blam
{
	struct c_game_engine_vip_variant : c_game_engine_base_variant
	{
		// default: 15
		// maximum: 500
		short m_score_to_win_round;

		// halo online specific
		// default: 10
		// maximum: 500
		short m_score_unknown;

		c_flags<e_vip_variant_flags, word_flags, k_vip_variant_flags> m_variant_flags;

		// default: 0
		// maximum: 20
		char m_kill_points;

		// default: 0
		// maximum: 20
		char m_takedown_points;

		// default: 0
		// maximum: 20
		char m_kill_as_vip_points;

		// default: 0
		// maximum: 20
		char m_vip_death_points;

		// default: 0
		// maximum: 20
		char m_destination_arrival_points;

		// default: 0
		// maximum: 20
		char m_suicide_points;

		// default: 0
		// maximum: 20
		char m_betrayal_points;

		// default: 0
		// maximum: 20
		char m_vip_suicide_points;

		c_enum<e_vip_selection_settings, char, k_vip_selection_settings> m_vip_selection;
		c_enum<e_vip_zone_movement_settings, char, k_vip_zone_movement_settings> m_zone_movement;
		c_enum<e_vip_zone_order_settings, char, k_vip_zone_order_settings> m_zone_order;

		byte pad[1];

		// default: 0
		// maximum: 50
		short m_influence_radius;

		c_player_traits m_vip_team_traits;
		c_player_traits m_vip_influence_traits;
		c_player_traits m_vip_traits;

		byte unused[0x28];
	};
	static_assert(sizeof(c_game_engine_vip_variant) == 0x260);
}