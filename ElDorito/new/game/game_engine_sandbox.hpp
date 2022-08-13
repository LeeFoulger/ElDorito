#pragma once

#include "game_engine_variant.hpp"
#include "game_engine_sandbox_traits.hpp"

namespace blam
{
	struct c_game_engine_sandbox_variant : c_game_engine_base_variant
	{
		e_sandbox_variant_flags m_variant_flags;
		e_sandbox_editing_mode m_edit_mode;
		e_sandbox_respawn_time m_respawn_time;
		c_player_traits m_all_player_traits;
		byte unused[0x70];
	};
	static_assert(sizeof(c_game_engine_sandbox_variant) == 0x260);
}