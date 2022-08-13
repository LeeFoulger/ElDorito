#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_assault_traits.hpp"

namespace blam
{
	struct c_game_engine_assault_variant : c_game_engine_base_variant
	{
		e_assault_variant_flags m_variant_flags;
		e_assault_respawn_settings m_respawn;
		e_assault_game_type_settings m_game_type;
		e_assault_enemy_bomb_waypoint_settings m_enemy_bomb_waypoint;
		short m_score_to_win;
		short m_score_unknown0;                                        // halo online specific
		short m_score_unknown1;                                        // halo online specific
		short m_score_unknown2;                                        // halo online specific
		short m_score_unknown3;                                        // halo online specific
		e_assault_variant_sudden_death_time m_sudden_death_time;
		short m_bomb_reset_time;                                       // seconds
		short m_bomb_arming_time;                                      // seconds
		short m_bomb_disarming_time;                                   // seconds
		short m_bomb_fuse_time;                                        // seconds
		c_player_traits m_carrier_traits;
		c_player_traits m_arming_traits;
		byte pad[4];
		byte unused[0x38];
	};
	static_assert(sizeof(c_game_engine_assault_variant) == 0x260);
}