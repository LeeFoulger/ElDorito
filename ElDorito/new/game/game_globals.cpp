#include "game_globals.hpp"

#include <cassert>

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace blam
{
	game_globals_storage* game_globals_get()
	{
		using namespace Blam::Memory;

		s_thread_local_storage* tls = ElDorito::GetMainTls();

		return tls->game_globals;
	}

	bool game_is_available(void)
	{
		game_globals_storage* game_globals = game_globals_get();

		return game_globals && game_globals->map_active && game_globals->active_structure_bsp_mask;
	}

	s_game_cluster_bit_vectors* game_get_cluster_pvs()
	{
		game_globals_storage* game_globals = game_globals_get();
		assert(game_globals && game_globals->map_active && game_globals->active_structure_bsp_mask != 0);

		return &game_globals->cluster_pvs;
	}

	s_game_cluster_bit_vectors* game_get_cluster_pvs_local()
	{
		game_globals_storage* game_globals = game_globals_get();
		assert(game_globals && game_globals->map_active && game_globals->active_structure_bsp_mask != 0);

		return &game_globals->cluster_pvs_local;
	}

	s_game_cluster_bit_vectors* game_get_cluster_activation()
	{
		game_globals_storage* game_globals = game_globals_get();
		assert(game_globals && game_globals->map_active && game_globals->active_structure_bsp_mask != 0);

		return &game_globals->cluster_activation;
	}

	// bool game_test_cluster_activation(s_cluster_reference* cluster_reference)
	// void game_pvs_enable_scripted_camera_pvs()
	// void game_pvs_clear_scripted_camera_pvs()
	// void game_pvs_scripted_set_object(long)
	// void game_pvs_scripted_set_camera_point(short)
	// void game_pvs_scripted_clear()
	// game_update_pvs
}