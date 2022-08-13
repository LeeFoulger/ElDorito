#pragma once

#include "cseries\cseries.hpp"
#include "game_options.hpp"

namespace blam
{
	// TODO: find a home
	struct s_game_cluster_bit_vectors
	{
		dword __unknown[16][8];
	};
	static_assert(sizeof(s_game_cluster_bit_vectors) == 0x200);

	struct game_globals_storage
	{
		bool initializing;
		bool map_active;
		byte : 8;
		byte : 8;
		dword active_structure_bsp_mask;
		dword active_designer_zone_mask;
		dword active_cinematic_zone_mask;
		game_options options;
		dword __unkown24B58;
		byte current_game_progress[0x80];
		bool game_in_progress;
		byte __data24BDD[0x7];
		bool finished;
		byte __data24BE5[3];
		dword end_match_wait_time;
		dword active_current_primary_skulls;
		dword active_current_secondary_skulls;
		byte __data24BF4[4];
		s_game_cluster_bit_vectors cluster_pvs;
		s_game_cluster_bit_vectors cluster_pvs_local;
		s_game_cluster_bit_vectors cluster_activation;
		byte __data251F8[0x10];
	};
	static_assert(sizeof(game_globals_storage) == 0x25208);
	
	extern game_globals_storage* game_globals_get(void);
	extern s_game_cluster_bit_vectors* game_get_cluster_pvs(void);
	extern s_game_cluster_bit_vectors* game_get_cluster_pvs_local(void);
	extern s_game_cluster_bit_vectors* game_get_cluster_activation(void);
}