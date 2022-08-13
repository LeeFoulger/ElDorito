#pragma once

namespace blam
{
	enum e_game_mode : long
	{
		_game_mode_none = 0,
		_game_mode_campaign,
		_game_mode_multiplayer,
		_game_mode_mainmenu,
		_game_mode_shared,

		k_game_mode_count
	};
	static_assert(sizeof(e_game_mode) == 0x4);
}