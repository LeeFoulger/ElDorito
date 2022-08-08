#pragma once
#include <cseries\cseries.hpp>
#include <game\game_mode.hpp>

namespace blam
{
	struct game_globals_storage
	{
		char unknown0[0x10];
		game_mode current_game_mode;
		char unknown14[0x13A];
		short current_insertion_point;
		char unknown150[0x250B8];
	};
	static_assert(sizeof(game_globals_storage) == 0x25208);

	game_globals_storage* game_globals_get();
}