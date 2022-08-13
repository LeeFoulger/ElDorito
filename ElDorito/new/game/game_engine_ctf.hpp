#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_ctf_traits.hpp"

namespace blam
{
	struct c_game_engine_ctf_variant : c_game_engine_base_variant
	{
		e_ctf_variant_flags m_variant_flags;
		e_ctf_home_flag_waypoint_settings m_home_flag_waypoint;
		e_ctf_game_type_settings m_game_type;
		e_ctf_respawn_settings m_respawn;
		e_ctf_touch_return_settings m_touch_return_timeout;
		e_ctf_sudden_death_time m_sudden_death_time;
		short m_score_to_win;
		short m_score_unknown;                                   // halo online specific
		short m_flag_reset_time;                                 // seconds
		c_player_traits m_carrier_traits;
		byte pad[6];
		byte unused[0x60];
	};
	static_assert(sizeof(c_game_engine_ctf_variant) == 0x260);
}