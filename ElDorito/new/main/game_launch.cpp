#include "game_launch.hpp"

namespace blam
{
	s_main_game_launch_globals& g_launch_globals = *reinterpret_cast<s_main_game_launch_globals*>(0x023B6348);

	s_main_game_launch_globals& launch_globals_get()
	{
		return g_launch_globals;
	}
}