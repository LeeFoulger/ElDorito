#pragma once

namespace blam
{

	enum e_juggernaut_initial_juggernaut_settings : char
	{
		_juggernaut_initial_juggernaut_settings_random = 0,
		_juggernaut_initial_juggernaut_settings_first_kill,
		_juggernaut_initial_juggernaut_settings_first_death,

		k_juggernaut_initial_juggernaut_settings,
		k_juggernaut_initial_juggernaut_settings_default = _juggernaut_initial_juggernaut_settings_random
	};

	enum e_juggernaut_next_juggernaut_settings : char
	{
		_juggernaut_next_juggernaut_settings_on_killing_juggernaut = 0,
		_juggernaut_next_juggernaut_settings_on_killed_by_juggernaut,
		_juggernaut_next_juggernaut_settings_unchanged,
		_juggernaut_next_juggernaut_settings_random,

		k_juggernaut_next_juggernaut_settings,
		k_juggernaut_next_juggernaut_settings_default = _juggernaut_next_juggernaut_settings_on_killing_juggernaut
	};

	enum e_juggernaut_variant_flags : byte_flags
	{
		_juggernaut_variant_flags_allied_against_juggernaut = 1 << 0,
		_juggernaut_variant_flags_respawn_on_lone_juggernaut = 1 << 1,
		_juggernaut_variant_flags_destination_zones_enabled = 1 << 2,

		k_juggernaut_variant_flags
	};

	enum e_juggernaut_zone_movement_settings : char
	{
		_juggernaut_zone_movement_settings_off = 0,
		_juggernaut_zone_movement_settings_10_seconds,
		_juggernaut_zone_movement_settings_15_seconds,
		_juggernaut_zone_movement_settings_30_seconds,
		_juggernaut_zone_movement_settings_1_minute,
		_juggernaut_zone_movement_settings_2_minutes,
		_juggernaut_zone_movement_settings_3_minutes,
		_juggernaut_zone_movement_settings_4_minutes,
		_juggernaut_zone_movement_settings_5_minutes,
		_juggernaut_zone_movement_settings_on_arrival,
		_juggernaut_zone_movement_settings_on_switch,

		k_juggernaut_zone_movement_settings,
		k_juggernaut_zone_movement_settings_default = _juggernaut_zone_movement_settings_off
	};

	enum e_juggernaut_zone_order_settings : char
	{
		_juggernaut_zone_order_settings_random = 0,
		_juggernaut_zone_order_settings_sequence,

		k_juggernaut_zone_order_settings,
		k_juggernaut_zone_order_settings_default = _juggernaut_zone_order_settings_random
	};
}