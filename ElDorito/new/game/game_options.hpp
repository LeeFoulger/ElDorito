#pragma once

#include "cseries/cseries.hpp"
#include "cseries/language.hpp"
#include "game_mode.hpp"
#include "game_engine_variant.hpp"
#include "game_engine_ctf.hpp"
#include "game_engine_slayer.hpp"
#include "game_engine_oddball.hpp"
#include "game_engine_king.hpp"
#include "game_engine_sandbox.hpp"
#include "game_engine_vip.hpp"
#include "game_engine_juggernaut.hpp"
#include "game_engine_territories.hpp"
#include "game_engine_assault.hpp"
#include "game_engine_infection.hpp"

namespace blam
{
	// TODO: find a home
	enum e_game_simulation_type : char
	{
		_game_simulation_none = 0,
		_game_simulation_local,
		_game_simulation_synchronous_client,
		_game_simulation_synchronous_server,
		_game_simulation_distributed_client,
		_game_simulation_distributed_server,

		k_game_simulation_count
	};
	static_assert(sizeof(e_game_simulation_type) == sizeof(char));

	// TODO: find a home
	enum e_game_playback_type : short
	{
		_game_playback_none = 0,
		_game_playback_local,
		_game_playback_network_server,
		_game_playback_network_client,

		k_game_playback_count
	};
	static_assert(sizeof(e_game_playback_type) == sizeof(short));

	// TODO: find a home
	enum e_campaign_difficulty_level : short
	{
		_campaign_difficulty_level_easy = 0,
		_campaign_difficulty_level_normal,
		_campaign_difficulty_level_heroic,
		_campaign_difficulty_level_legendary,

		k_campaign_difficulty_levels_count
	};
	static_assert(sizeof(e_campaign_difficulty_level) == sizeof(short));

	// TODO: find a home
	struct s_campaign_armaments_player
	{
		bool valid;
		byte __data[29];
	};

	// TODO: find a home
	struct s_hub_progression
	{
		s_campaign_armaments_player hub_armaments[4];
		long hub_return_to_insertion_point;
		bool hub_progression_valid;
		byte : 8;
		byte : 8;
		byte : 8;
	};
	static_assert(sizeof(s_hub_progression) == 0x80);

	// TODO: find a home
	struct s_game_matchmaking_options
	{
		word hopper_identifier;
		byte xlast_index;
		bool is_ranked;
		bool team_game;
		byte : 8;
		wchar_t hopper_name[32];
		byte : 8;
		byte : 8;
		long draw_probability;
		long beta;
		long tau;
		long experience_base_increment;
		long experience_penalty_decrement;
	};
	static_assert(sizeof(s_game_matchmaking_options) == 0x5C);

	// TODO: find a home
	struct c_game_variant
	{
		e_game_engine_variant m_game_engine_index;

		union
		{
			c_game_engine_base_variant m_base_variant;
			c_game_engine_ctf_variant m_ctf_variant;
			c_game_engine_slayer_variant m_slayer_variant;
			c_game_engine_oddball_variant m_oddball_variant;
			c_game_engine_king_variant m_king_variant;
			c_game_engine_sandbox_variant m_sandbox_variant;
			c_game_engine_vip_variant m_vip_variant;
			c_game_engine_juggernaut_variant m_juggernaut_variant;
			c_game_engine_territories_variant m_territories_variant;
			c_game_engine_assault_variant m_assault_variant;
			c_game_engine_infection_variant m_infection_variant;
			byte variant_data[0x260];
		};
	};
	static_assert(sizeof(c_game_variant) == 0x264);

	// TODO: find a home
	struct c_map_variant
	{
		byte __data[0xE090];
	};
	static_assert(sizeof(c_map_variant) == 0xE090);

	// TODO: find a home
	struct s_game_machine_options
	{
		byte __data[0x128];
	};
	static_assert(sizeof(s_game_machine_options) == 0x128);

	// TODO: find a home
	struct s_game_player_options
	{
		byte __data[0x1640];
	};
	static_assert(sizeof(s_game_player_options) == 0x1640);

	struct game_options
	{
		e_game_mode game_mode;
		e_game_simulation_type game_simulation;
		byte game_network_type;
		short game_tick_rate;
		qword game_instance;
		long random_seed;
		e_language language;
		long determinism_version;
		long campaign_id;
		long map_id;
		char scenario_path[260];
		short initial_zone_set_index;
		bool load_level_only;
		bool dump_machine_index;
		bool dump_object_log;
		bool dump_random_seeds;
		bool playtest_mode;
		byte : 8;
		e_game_playback_type game_playback;
		bool record_saved_film;
		byte : 8;
		long playback_start_ticks;
		long playback_length_in_ticks;
		e_campaign_difficulty_level campaign_difficulty;
		short campaign_insertion_index;
		short campaign_metagame_scoring;
		bool campaign_metagame_enabled;
		bool survival_enabled;
		byte : 8; // halo3_tag_test: campaign_allow_persistent_storage
		byte : 8; // halo3_tag_test: campaign_customization_enabled
		s_campaign_armaments_player campaign_armaments[4];
		byte : 8;
		byte : 8;
		byte campaign_game_progression[0x80];
		dword active_primary_skulls;
		dword active_secondary_skulls;
		s_hub_progression hub_progression;
		bool matchmade_game;
		byte __align2C9[7];
		s_game_matchmaking_options matchmaking_options;
		c_game_variant game_variant;
		c_map_variant map_variant;
		s_game_machine_options machine_options;
		s_game_player_options players[16];
	};
	static_assert(sizeof(game_options) == 0x24B48);

	//extern bool game_in_startup_phase(void);
	extern bool game_in_progress(void);
	//extern long game_create_lock_resources(e_game_create_mode);
	//extern void game_create_unlock_resources(e_game_create_mode, long&);
	//extern void game_start(enum e_game_create_mode);
	extern bool game_options_valid(void);
	extern game_options* game_options_get(void);
	extern void game_options_print_game_id(void);
	//extern void game_options_setup_for_saved_film(e_game_playback_type playback_type);
	extern void game_options_clear_game_playback(void);
	//extern void game_options_game_engine_fixup(void);
	extern e_campaign_difficulty_level game_difficulty_level_get(void);
	extern e_campaign_difficulty_level game_difficulty_level_get_ignore_easy(void);
	extern e_game_mode game_mode_get(void);
	extern bool game_is_ui_shell(void);
	extern bool game_is_multiplayer(void);
	extern bool game_is_campaign(void);
	//extern bool game_is_survival(void);
	//extern void game_set_active_skulls(dword* active_skulls);
	extern void game_set_difficulty(e_campaign_difficulty_level campaign_difficulty);
	//extern bool game_is_cooperative(void);
	//extern long game_coop_player_count(void);
	extern bool game_is_playtest(void);
	//extern bool game_had_an_update_tick_this_frame(void);
	extern e_game_simulation_type game_simulation_get(void);
	extern bool game_is_playback(void);
	extern e_game_playback_type game_playback_get(void);
	//extern void game_playback_set(e_game_playback_type playback_type);
	extern void game_simulation_set(e_game_simulation_type game_simulation);
	extern bool game_is_synchronous_networking(void);
	extern bool game_is_networked(void);
	//extern bool game_is_in_progress_on_live(void);
	extern bool game_is_server(void);
	extern bool game_is_authoritative(void);
	extern bool game_is_predicted(void);
	extern bool game_is_distributed(void);
	extern long game_tick_rate_get(void);
	//extern bool game_coop_allow_respawn(void);
	extern e_language game_get_master_language(void);
	//extern bool game_is_language_neutral(void);
	//extern void game_won(void);
	//extern bool game_is_won(void);
	//extern void game_lost(bool);
	//extern bool game_is_lost(void);
	//extern void game_finish(void);
	//extern void game_finish_immediate(void);
	//extern bool game_is_finished(void);
	//extern bool game_is_finished_immediate(void);
	//extern bool game_is_finished_waiting_for_level_advance(void);
}