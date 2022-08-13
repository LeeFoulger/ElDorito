#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_oddball_traits.hpp"

namespace blam
{
	struct c_game_engine_oddball_variant : c_game_engine_base_variant
	{
		e_oddball_variant_flags m_variant_flags;
		short m_score_to_win;
		short m_carrying_points;                  // points per second when carrying the ball
		short m_unknown_points;                   // halo online specific
		char m_kill_points;
		char m_ball_kill_points;                  // number of points for a melee kill with the ball
		char m_carrier_kill_points;               // number of points for killing the ball carrier
		char m_ball_count;
		short m_ball_spawn_delay;                 // seconds, time until first ball spawn after round start, and also delay in respawning ball if it goes out of play
		short m_ball_inactive_respawn;            // seconds, time until ball respawns if it is inactive
		c_player_traits m_carrier_traits;
		byte pad[2];
		byte unused[0x60];
	};
	static_assert(sizeof(c_game_engine_oddball_variant) == 0x260);
}