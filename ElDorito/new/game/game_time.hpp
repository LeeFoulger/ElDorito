#pragma once

#include "cseries/cseries.hpp"

namespace blam
{
	struct game_time_globals_definition
	{
		bool initialized;
		byte : 8;
		word flags;
		word ticks_per_second;
		word : 16;
		float seconds_per_tick;
		dword elapsed_ticks;
		dword gamespeed;
		dword __unknown14;
		dword __unknown18;
		dword __unknown1C;
		dword __unknown20;
		dword __unknown24;
		dword __unknown28;
	};
	static_assert(sizeof(game_time_globals_definition) == 0x2C);

	struct s_game_tick_time_samples
	{
		long flags;
		real __unknown4;
		real __unknown8;
		real __unknownC;
		dword __unknown10;
	};
	static_assert(sizeof(s_game_tick_time_samples) == 0x14);

	extern game_time_globals_definition* game_time_globals_get();
	extern long game_seconds_to_ticks_round(real seconds);
}