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

	using e_game_time_pause_reason = long;

	extern game_time_globals_definition* game_time_globals_get();

	extern long __cdecl game_seconds_integer_to_ticks(long seconds); // 0x00564B40
	extern real __cdecl game_seconds_to_ticks_real(real seconds); // 0x00564B70
	extern long __cdecl game_seconds_to_ticks_round(real seconds);; // 0x00564BB0
	extern real __cdecl game_tick_length(); // 0x00564C20
	extern long __cdecl game_tick_rate(); // 0x00564C40
	extern real __cdecl game_ticks_to_seconds(real ticks); // 0x00564C60
	extern void __cdecl game_time_advance(); // 0x00564C90
	extern void __cdecl game_time_discard(long desired_ticks, long actual_ticks, real* elapsed_game_dt); // 0x00564CB0
	extern void __cdecl game_time_dispose(); // 0x00564D10
	extern void __cdecl game_time_dispose_from_old_map(); // 0x00564D20
	extern long __cdecl game_time_get(); // 0x00564D50
	extern bool __cdecl game_time_get_paused(); // 0x00564D70
	extern bool __cdecl game_time_get_paused_for_reason(e_game_time_pause_reason); // 0x00564E20
	extern real __cdecl game_time_get_safe_in_seconds(); // 0x00564E60
	extern real __cdecl game_time_get_speed(); // 0x00564EB0
	extern void __cdecl game_time_initialize(); // 0x00564ED0
	extern void __cdecl game_time_initialize_for_new_map(); // 0x00564F30
	extern bool __cdecl game_time_initialized(); // 0x00564FA0
	extern void __cdecl game_time_set(long time); // 0x00564FE0
	extern void __cdecl game_time_set_paused(bool, e_game_time_pause_reason); // 0x00565000
	extern void __cdecl game_time_set_rate_scale(real, real, real); // 0x00565060
	extern void __cdecl game_time_set_speed(real); // 0x00565110
	extern void __cdecl game_time_update(real, real*, long*); // 0x00565250
}