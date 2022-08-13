#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_slayer_traits.hpp"

namespace blam
{
	struct c_game_engine_slayer_variant : c_game_engine_base_variant
	{
		short m_score_to_win;
		short m_score_unknown;
		short m_kill_points;
		char m_assist_points;
		char m_death_points;
		char m_suicide_points;
		char m_betrayal_points;
		char m_leader_killed_points;
		char m_elimination_points;
		char m_assassination_points;
		char m_headshot_points;
		char m_melee_points;
		char m_sticky_points;
		char m_splatter_points;
		char m_killing_spree_points;
		c_player_traits m_leader_traits;  // leader team traits if teams enabled
		byte pad[2];
		byte unused[0x60];
	};
	static_assert(sizeof(c_game_engine_slayer_variant) == 0x260);
}