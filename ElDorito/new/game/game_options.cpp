#include "game_options.hpp"
#include "game_globals.hpp"

#include <cassert>
#include <stdio.h>

namespace blam
{
	// bool game_in_startup_phase(void)

	bool game_in_progress(void)
	{
		game_globals_storage* game_globals = game_globals_get();

		//return game_globals && game_globals->game_in_progress && !game_globals->initializing && game_globals->map_active;
		if (game_globals && game_globals->game_in_progress)
		{
			assert(!game_globals->initializing);
			assert(game_globals->map_active);

			return true;
		}

		return false;
	}

	// long game_create_lock_resources(e_game_create_mode)
	// void game_create_unlock_resources(e_game_create_mode, long&)
	// void game_start(enum e_game_create_mode)

	bool game_options_valid(void)
	{
		game_globals_storage* game_globals = game_globals_get();

		return game_globals && (game_globals->initializing || game_globals->map_active);
	}

	game_options* game_options_get(void)
	{
		game_globals_storage* game_globals = game_globals_get();
		assert(game_globals && (game_globals->initializing || game_globals->map_active));

		return &game_globals->options;
	}

	void game_options_print_game_id(void)
	{
		printf("%I64d\n", game_options_get()->game_instance);
	}

	// void game_options_setup_for_saved_film(e_game_playback_type playback_type)

	void game_options_clear_game_playback(void)
	{
		game_globals_storage* game_globals = game_globals_get();
		assert(game_globals && (game_globals->initializing || game_globals->map_active));

		game_globals->options.game_playback = _game_playback_none;
	}

	// void game_options_game_engine_fixup(void)

	e_campaign_difficulty_level game_difficulty_level_get(void)
	{
		return game_options_get()->campaign_difficulty;
	}

	e_campaign_difficulty_level game_difficulty_level_get_ignore_easy(void)
	{
		if (game_difficulty_level_get() == _campaign_difficulty_level_easy)
			return _campaign_difficulty_level_normal;

		return game_difficulty_level_get();
	}

	e_game_mode game_mode_get(void)
	{
		return game_options_get()->game_mode;
	}

	bool game_is_ui_shell(void)
	{
		return game_options_get()->game_mode == _game_mode_mainmenu;
	}

	bool game_is_multiplayer(void)
	{
		return game_options_get()->game_mode == _game_mode_multiplayer;
	}

	bool game_is_campaign(void)
	{
		return game_options_get()->game_mode == _game_mode_campaign;
	}

	// bool game_is_survival(void)
	// void game_set_active_skulls(dword* active_skulls)

	void game_set_difficulty(e_campaign_difficulty_level campaign_difficulty)
	{
		if (game_in_progress() && 
			game_is_campaign() && 
			campaign_difficulty >= _campaign_difficulty_level_easy &&
			campaign_difficulty < k_campaign_difficulty_levels_count)
		{
			game_options_get()->campaign_difficulty = campaign_difficulty;
		}
	}

	// bool game_is_cooperative(void)
	// long game_coop_player_count(void)

	bool game_is_playtest(void)
	{
		return game_options_get()->playtest_mode;
	}

	// bool game_had_an_update_tick_this_frame(void)

	e_game_simulation_type game_simulation_get(void)
	{
		return game_options_get()->game_simulation;
	}

	bool game_is_playback(void)
	{
		return game_playback_get();
	}

	e_game_playback_type game_playback_get(void)
	{
		return game_options_get()->game_playback;
	}

	// void game_playback_set(e_game_playback_type playback_type)

	void game_simulation_set(e_game_simulation_type game_simulation)
	{
		char const* k_game_simulation_names[k_game_simulation_count]
		{
			"none",
			"local",
			"sync-client",
			"sync-server",
			"dist-client",
			"dist-server"
		};

		assert(game_simulation > _game_simulation_none && game_simulation < k_game_simulation_count);

		game_globals_storage* game_globals = game_globals_get();
		assert(game_globals && (game_globals->initializing || game_globals->map_active));

		game_globals->options.game_simulation = game_simulation;
		printf("game_simulation: %s\n", k_game_simulation_names[game_simulation]);
	}

	bool game_is_synchronous_networking(void)
	{
		e_game_simulation_type game_simulation = game_options_get()->game_simulation;
		if (game_simulation >= _game_simulation_synchronous_client &&
			game_simulation <= _game_simulation_synchronous_server)
			return true;

		return false;
	}

	bool game_is_networked(void)
	{
		e_game_simulation_type game_simulation = game_options_get()->game_simulation;
		if (game_simulation >= _game_simulation_synchronous_client &&
			game_simulation <= _game_simulation_distributed_server)
			return true;

		return false;
	}

	// bool game_is_in_progress_on_live(void)

	bool game_is_server(void)
	{
		e_game_simulation_type game_simulation = game_options_get()->game_simulation;
		if (game_simulation == _game_simulation_synchronous_server ||
			game_simulation == _game_simulation_distributed_server)
			return true;

		return false;
	}

	bool game_is_authoritative(void)
	{
		return !game_is_predicted();
	}

	bool game_is_predicted(void)
	{
		return game_options_get()->game_simulation == _game_simulation_distributed_client;
	}

	bool game_is_distributed(void)
	{
		e_game_simulation_type game_simulation = game_options_get()->game_simulation;
		if (game_simulation >= _game_simulation_distributed_client &&
			game_simulation <= _game_simulation_distributed_server)
			return true;

		return false;
	}

	long game_tick_rate_get(void)
	{
		return game_options_get()->game_tick_rate;
	}

	// bool game_coop_allow_respawn(void)

	e_language game_get_master_language(void)
	{
		return game_options_get()->language;
	}

	// bool game_is_language_neutral(void)
	// void game_won(void)
	// bool game_is_won(void)
	// void game_lost(bool)
	// bool game_is_lost(void)
	// void game_finish(void)
	// void game_finish_immediate(void)
	// bool game_is_finished(void)
	// bool game_is_finished_immediate(void)
	// bool game_is_finished_waiting_for_level_advance(void)
}