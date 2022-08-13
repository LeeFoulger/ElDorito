#pragma once

#include "game_engine_player_traits.hpp"

namespace blam
{
	enum e_game_engine_variant : long
	{
		_game_engine_base_variant = 0,
		_game_engine_ctf_variant,
		_game_engine_slayer_variant,
		_game_engine_oddball_variant,
		_game_engine_king_variant,
		_game_engine_sandbox_variant,
		_game_engine_vip_variant,
		_game_engine_juggernaut_variant,
		_game_engine_territories_variant,
		_game_engine_assault_variant,
		_game_engine_infection_variant,

		k_game_engine_variants,
		k_game_engine_variant_default = _game_engine_base_variant
	};

	extern const char* game_engine_variant_get_name(long index);

	enum e_base_variant_flags
	{
		_base_variant_flags_built_in = 0,

		k_base_variant_flags
	};

	enum e_game_engine_miscellaneous_option_flags : byte_flags
	{
		_game_engine_miscellaneous_option_teams_enabled = 1 << 0,
		_game_engine_miscellaneous_option_round_reset_players = 1 << 1,
		_game_engine_miscellaneous_option_round_reset_map = 1 << 2,

		k_game_engine_miscellaneous_option_flags
	};

	enum e_game_engine_respawn_options_flags : byte_flags
	{
		_game_engine_respawn_options_inherit_respawn_time = 1 << 0,
		_game_engine_respawn_options_respawn_with_teammate = 1 << 1,
		_game_engine_respawn_options_respawn_at_location = 1 << 2,
		_game_engine_respawn_options_respawn_on_kills = 1 << 3,

		k_game_engine_respawn_options_flags
	};

	enum e_game_engine_social_options_flags : word_flags
	{
		_game_engine_social_options_observers_enabled = 1 << 0,
		_game_engine_social_options_team_changing_enabled = 1 << 1,
		_game_engine_social_options_team_changing_balancing_only = 1 << 2,
		_game_engine_social_options_friendly_fire_enabled = 1 << 3,
		_game_engine_social_options_betrayal_booting_enabled = 1 << 4,
		_game_engine_social_options_enemy_voice_enabled = 1 << 5,
		_game_engine_social_options_open_channel_voice_enabled = 1 << 6,
		_game_engine_social_options_dead_player_voice_enabled = 1 << 7,

		k_game_engine_social_options_flags
	};

	enum e_game_engine_map_override_options_flags : dword_flags
	{
		_game_engine_map_override_options_grenades_on_map = 1 << 0,
		_game_engine_map_override_options_indestructible_vehicles = 1 << 1,

		k_game_engine_map_override_options_flags
	};

	struct c_game_engine_miscellaneous_options
	{
		e_game_engine_miscellaneous_option_flags m_flags;
		byte m_round_time_limit;                           // minutes
		byte m_number_of_rounds;
		byte m_early_victory_win_count;
	};
	static_assert(sizeof(c_game_engine_miscellaneous_options) == 0x4);

	struct c_game_engine_respawn_options
	{
		e_game_engine_respawn_options_flags m_flags;
		byte m_lives_per_round;
		byte m_team_lives_per_round;
		byte m_respawn_time;                          // seconds
		byte m_suicide_penalty;                       // seconds
		byte m_betrayal_penalty;                      // seconds
		byte m_unknown_penalty;                       // seconds
		byte m_respawn_growth;
		byte m_respawn_player_traits_duration;
		byte pad[3];                                  // woman bound for glory, why you leaving me again?
		c_player_traits m_respawn_player_traits;
	};
	static_assert(sizeof(c_game_engine_respawn_options) == 0x28);

	struct c_game_engine_social_options
	{
		e_game_engine_social_options_flags m_flags;
		word m_team_changing;
	};
	static_assert(sizeof(c_game_engine_social_options) == 0x4);

	struct c_game_engine_map_override_options
	{
		e_game_engine_map_override_options_flags m_flags;
		c_player_traits m_player_traits;
		word m_weapon_set;
		word m_vehicle_set;
		c_player_traits m_red_powerup_traits;
		c_player_traits m_blue_powerup_traits;
		c_player_traits m_yellow_powerup_traits;
		byte m_red_powerup_traits_duration;                // seconds
		byte m_blue_powerup_traits_duration;               // seconds
		byte m_yellow_powerup_traits_duration;             // seconds
		byte pad;                                          // gonna pack her bags and leave this house of pain
	};
	static_assert(sizeof(c_game_engine_map_override_options) == 0x7C);
}
