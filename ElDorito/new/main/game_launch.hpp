#pragma once

#include "game/game_options.hpp"

namespace blam
{
	struct s_main_game_launch_globals
	{
		/* in release builds strip core_name and player_count

		// main_game_change_immediate
		// main_game_load_from_core_name
		char core_name[256];

		// main_game_launch
		// main_game_launch_set_coop_player_count
		// main_game_launch_set_multiplayer_splitscreen_count
		long player_count;

		*/

		game_options options;
	};

	extern s_main_game_launch_globals& launch_globals_get();

	extern void main_game_launch(const char* map_name);
	//extern void main_game_launch_default(void);
	//extern void main_game_launch_default_editor(void);
	//extern void main_game_launch_legacy(char const*);
	//extern void main_game_launch_set_active_primary_skulls(long);
	//extern void main_game_launch_set_active_secondary_skulls(long);
	extern void main_game_launch_set_coop_player_count(long);
	//extern void main_game_launch_set_difficulty(long);
	//extern void main_game_launch_set_initial_zone_set_index(long);
	//extern void main_game_launch_set_insertion_point(short);
	extern void main_game_launch_set_map_name(char const*);
	//extern void main_game_launch_set_multiplayer_engine(char const*);
	extern void main_game_launch_set_multiplayer_splitscreen_count(long);
	//extern void main_game_launch_set_multiplayer_variant(char const*);
	//extern void main_game_launch_set_tick_rate(long);
}