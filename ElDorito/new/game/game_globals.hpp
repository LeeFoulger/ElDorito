#pragma once

#include "cseries/cseries.hpp"
#include "memory/data.hpp"
#include "game_options.hpp"

namespace blam
{
	// TODO: find a home
	struct s_game_cluster_bit_vectors
	{
		c_static_array<c_static_flags<256>, 16> flags;
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

		dword __unknown24B58;
		byte active_game_progress[0x80];

		bool game_in_progress;

		bool game_lost;
		bool game_revert;
		bool __unknown24BDF;
		dword game_lost_wait_time;

		bool game_finished;
		byte : 8;
		byte : 8;
		byte : 8;
		dword game_finished_wait_time;

		c_flags<e_campaign_skulls_primary, dword, k_campaign_skull_primary_count> active_primary_skulls;
		c_flags<e_campaign_skulls_secondary, dword, k_campaign_skull_secondary_count> active_secondary_skulls;

		byte __data24BF4[4];

		s_game_cluster_bit_vectors cluster_pvs;
		s_game_cluster_bit_vectors cluster_pvs_local;
		s_game_cluster_bit_vectors cluster_activation;

		// game_pvs_enable_scripted_camera_pvs
		// game_pvs_clear_scripted_camera_pvs
		bool scripted_camera_pvs;
		byte : 8;

		// game_pvs_scripted_clear
		// game_pvs_scripted_set_object
		// game_pvs_scripted_set_camera_point
		word scripted;

		// game_pvs_scripted_set_object
		// game_pvs_scripted_set_camera_point
		// scenario_group, scenario_block, scenario_cutscene_camera_point_block, camera_point_index
		datum_index scripted_object_index; // scenario_group.scenario_block.cutscene_camera_points[camera_point_index]

		byte __data25200[8];
	};
	static_assert(sizeof(game_globals_storage) == 0x25208);
	
	extern game_globals_storage* game_globals_get();
	extern s_game_cluster_bit_vectors* game_get_cluster_pvs();
	extern s_game_cluster_bit_vectors* game_get_cluster_pvs_local();
	extern s_game_cluster_bit_vectors* game_get_cluster_activation();
}