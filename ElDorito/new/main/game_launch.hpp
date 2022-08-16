#pragma once

#include "game/game_options.hpp"

namespace blam
{
	struct s_main_game_launch_globals
	{
		/* in release builds strip scenario_path and player_count

		// main_game_change_immediate
		// main_game_load_from_core_name
		char scenario_path[256];

		// main_game_launch
		// main_game_launch_set_coop_player_count
		// main_game_launch_set_multiplayer_splitscreen_count
		long player_count;

		*/

		game_options options;
	};

	extern s_main_game_launch_globals& launch_globals_get();
}