#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_koth_traits.hpp"

namespace blam
{
	struct c_game_engine_king_variant : c_game_engine_base_variant
	{
		e_king_variant_flags m_variant_flags;
		short m_score_to_win;
		short m_score_unknown;                                  // halo online specific
		e_king_moving_hill_settings m_moving_hill;
		e_king_moving_hill_order_settings m_moving_hill_order;
		char m_uncontested_hill_bonus_points;
		char m_points_per_kill;
		char m_inside_hill_points;
		char m_outside_hill_points;
		c_player_traits m_inside_hill_traits_name;
		byte pad[6];
		byte unused[0x60];
	};
	static_assert(sizeof(c_game_engine_king_variant) == 0x260);
}