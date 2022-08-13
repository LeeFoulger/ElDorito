#pragma once
#pragma pack(push, 1)

#include "cseries/cseries.hpp"

namespace blam
{
	enum e_damage_resistance_percentage_setting : char
	{
		_damage_resistance_percentage_setting_unchanged = 0,  // UNCHANGED
		_damage_resistance_percentage_setting_10_percent,     // 0.1
		_damage_resistance_percentage_setting_50_percent,     // 0.5
		_damage_resistance_percentage_setting_90_percent,     // 0.9
		_damage_resistance_percentage_setting_100_percent,    // 1.0
		_damage_resistance_percentage_setting_110_percent,    // 1.1
		_damage_resistance_percentage_setting_150_percent,    // 1.5
		_damage_resistance_percentage_setting_200_percent,    // 2.0
		_damage_resistance_percentage_setting_300_percent,    // 3.0
		_damage_resistance_percentage_setting_500_percent,    // 5.0
		_damage_resistance_percentage_setting_1000_percent,   // 10.0
		_damage_resistance_percentage_setting_2000_percent,   // 20.0
		_damage_resistance_percentage_setting_invulnerable,   // 1000.0

		k_damage_resistance_percentage_settings
	};

	enum e_shield_recharge_rate_percentage_setting : char
	{
		_shield_recharge_rate_percentage_setting_unchanged = 0,        // UNCHANGED
		_shield_recharge_rate_percentage_setting_negative_25_percent,  // -0.25
		_shield_recharge_rate_percentage_setting_negative_10_percent,  // -0.1
		_shield_recharge_rate_percentage_setting_negative_5_percent,   // -0.05
		_shield_recharge_rate_percentage_setting_0_percent,            // 0.0
		_shield_recharge_rate_percentage_setting_50_percent,           // 0.5
		_shield_recharge_rate_percentage_setting_90_percent,           // 0.9
		_shield_recharge_rate_percentage_setting_100_percent,          // 1.0
		_shield_recharge_rate_percentage_setting_110_percent,          // 1.1
		_shield_recharge_rate_percentage_setting_200_percent,          // 2.0

		k_shield_recharge_rate_percentage_settings
	};

	enum e_vampirism_percentage_setting : char
	{
		_vampirism_percentage_setting_unchanged = 0,  // UNCHANGED
		_vampirism_percentage_setting_0_percent,      // 0.0
		_vampirism_percentage_setting_10_percent,     // 0.1
		_vampirism_percentage_setting_25_percent,     // 0.25
		_vampirism_percentage_setting_50_percent,     // 0.5
		_vampirism_percentage_setting_100_percent,    // 1.0

		k_vampirism_percentage_settings
	};

	enum e_headshot_immunity_setting : char
	{
		_headshot_immunity_setting_unchanged = 0,            // UNCHANGED
		_headshot_immunity_setting_immune_to_headshots,      // ENABLED
		_headshot_immunity_setting_not_immune_to_headshots,  // DISABLED

		k_headshot_immunity_settings
	};

	enum e_shield_multiplier_setting : char
	{
		_shield_multiplier_setting_unchanged = 0,  // UNCHANGED
		_shield_multiplier_setting_0x,             // 0
		_shield_multiplier_setting_1x,             // 1 (NORMAL)
		_shield_multiplier_setting_2x,             // 2
		_shield_multiplier_setting_3x,             // 3
		_shield_multiplier_setting_4x,             // 4

		k_shield_multiplier_settings
	};

	struct c_player_trait_shield_vitality
	{
		e_damage_resistance_percentage_setting m_damage_resistance;
		e_shield_recharge_rate_percentage_setting m_shield_recharge_rate;
		e_vampirism_percentage_setting m_shield_vampirism;
		e_headshot_immunity_setting m_headshot_immunity;
		e_shield_multiplier_setting m_shield_multiplier;

		// elephant
		byte pad[3];
	};
	static_assert(sizeof(c_player_trait_shield_vitality) == 0x8);

	enum e_grenade_count_setting : short
	{
		_grenade_count_setting_unchanged = 0,  // UNCHANGED
		_grenade_count_setting_map_default,    // MAP DEFAULT
		_grenade_count_setting_none,           // NONE

		k_grenade_count_settings
	};

	enum e_damage_modifier_percentage_setting : char
	{
		_damage_modifier_percentage_setting_unchanged = 0,  // UNCHANGED
		_damage_modifier_percentage_setting_0_percent,      // 0.0
		_damage_modifier_percentage_setting_25_percent,     // 0.25
		_damage_modifier_percentage_setting_50_percent,     // 0.5
		_damage_modifier_percentage_setting_75_percent,     // 0.75
		_damage_modifier_percentage_setting_90_percent,     // 0.9
		_damage_modifier_percentage_setting_100_percent,    // 1.0
		_damage_modifier_percentage_setting_110_percent,    // 1.1
		_damage_modifier_percentage_setting_125_percent,    // 1.25
		_damage_modifier_percentage_setting_150_percent,    // 1.5
		_damage_modifier_percentage_setting_200_percent,    // 2.0
		_damage_modifier_percentage_setting_300_percent,    // 3.0
		_damage_modifier_percentage_setting_fatality,       // 1000.0 (FATALITY)

		k_damage_modifier_percentage_settings
	};

	enum e_recharging_grenades_setting : char
	{
		_recharging_grenades_setting_unchanged = 0,  // UNCHANGED
		_recharging_grenades_setting_enabled,        // ENABLED
		_recharging_grenades_setting_disabled,       // DISABLED

		k_recharging_grenades_settings
	};

	enum e_infinite_ammo_setting : char
	{
		_infinite_ammo_setting_unchanged = 0,  // UNCHANGED
		_infinite_ammo_setting_disabled,       // DISABLED
		_infinite_ammo_setting_enabled,        // ENABLED

		k_infinite_ammo_settings
	};

	enum e_weapon_pickup_setting : char
	{
		_weapon_pickup_setting_unchanged = 0,  // UNCHANGED
		_weapon_pickup_setting_allowed,        // ENABLED
		_weapon_pickup_setting_disallowed,     // DISABLED

		k_weapon_pickup_settings
	};

	struct c_player_trait_weapons
	{
		e_grenade_count_setting m_initial_grenade_count;
		char m_initial_primary_weapon;
		char m_initial_secondary_weapon;
		e_damage_modifier_percentage_setting m_damage_modifier;
		e_recharging_grenades_setting m_recharging_grenades;
		e_infinite_ammo_setting m_infinite_ammo;
		e_weapon_pickup_setting m_weapon_pickup;
	};
	static_assert(sizeof(c_player_trait_weapons) == 0x8);

	enum e_player_speed_setting : char
	{
		_player_speed_setting_unchanged = 0,  // UNCHANGED
		_player_speed_setting_25_percent,     // 0.25
		_player_speed_setting_50_percent,     // 0.5
		_player_speed_setting_75_percent,     // 0.75
		_player_speed_setting_90_percent,     // 0.9
		_player_speed_setting_100_percent,    // 1.0
		_player_speed_setting_110_percent,    // 1.1
		_player_speed_setting_125_percent,    // 1.25
		_player_speed_setting_150_percent,    // 1.5
		_player_speed_setting_200_percent,    // 2.0
		_player_speed_setting_300_percent,    // 3.0

		k_player_speed_settings
	};

	enum e_player_gravity_setting : char
	{
		_player_gravity_setting_unchanged = 0,  // UNCHANGED
		_player_gravity_setting_50_percent,     // 0.5
		_player_gravity_setting_75_percent,     // 0.75
		_player_gravity_setting_100_percent,    // 1.0
		_player_gravity_setting_150_percent,    // 1.5
		_player_gravity_setting_200_percent,    // 2.0

		k_player_gravity_settings
	};

	enum e_vehicle_usage_setting : char
	{
		_vehicle_usage_setting_unchanged = 0,   // UNCHANGED
		_vehicle_usage_setting_none,            // NONE
		_vehicle_usage_setting_passenger_only,  // PASSENGER ONLY
		_vehicle_usage_setting_full,            // FULL

		k_vehicle_usage_settings
	};

	struct c_player_trait_movement
	{
		e_player_speed_setting m_speed_multiplier;
		e_player_gravity_setting m_gravity_multiplier;
		e_vehicle_usage_setting m_vehicle_usage;
		byte pad;                   // shark
	};
	static_assert(sizeof(c_player_trait_movement) == 0x4);

	enum e_active_camo_setting : char
	{
		_active_camo_setting_unchanged = 0,  // UNCHANGED
		_active_camo_setting_off,            // OFF (0.0)
		_active_camo_setting_poor,           // POOR (0.33)
		_active_camo_setting_good,           // GOOD (0.66)
		_active_camo_setting_invisible,      // INVISIBLE (1.0)

		k_active_camo_settings
	};

	enum e_waypoint_setting : char
	{
		_waypoint_setting_unchanged = 0,  // UNCHANGED
		_waypoint_setting_off,            // OFF
		_waypoint_setting_allies,         // ALLIES
		_waypoint_setting_all,            // ALL

		k_waypoint_settings
	};

	enum e_aura_setting : char
	{
		_aura_setting_unchanged = 0,  // UNCHANGED
		_aura_setting_off,            // OFF
		_aura_setting_team_color,     // TEAM COLOR
		_aura_setting_black,          // BLACK
		_aura_setting_white,          // WHITE

		k_aura_settings
	};

	enum e_forced_change_color_setting : char
	{
		_forced_change_color_setting_unchanged = 0,   // UNCHANGED
		_forced_change_color_setting_off,             // OFF
		_forced_change_color_setting_mp_team_red,     // RED
		_forced_change_color_setting_mp_team_blue,    // BLUE
		_forced_change_color_setting_mp_team_green,   // GREEN
		_forced_change_color_setting_mp_team_yellow,  // YELLOW
		_forced_change_color_setting_mp_team_purple,  // PURPLE
		_forced_change_color_setting_mp_team_orange,  // ORANGE
		_forced_change_color_setting_mp_team_brown,   // BROWN
		_forced_change_color_setting_mp_team_grey,    // GREY (PINK)
		_forced_change_color_setting_extra1,          // XTRA 1 (PRIMARY COLOR)
		_forced_change_color_setting_extra2,          // XTRA 2 (SECONDARY COLOR)
		_forced_change_color_setting_extra3,          // XTRA 3 (TERTIARY COLOR)
		_forced_change_color_setting_extra4,          // XTRA 4 (QUATERNARY COLOR)

		k_forced_change_color_settings
	};

	// Traits that affect the player's appearance
	struct c_player_trait_appearance
	{
		e_active_camo_setting m_active_camo_setting;
		e_waypoint_setting m_waypoint_setting;
		e_aura_setting m_aura_setting;
		e_forced_change_color_setting m_forced_change_color_setting;
	};
	static_assert(sizeof(c_player_trait_appearance) == 0x4);

	enum e_motion_tracker_setting : short
	{
		_motion_tracker_setting_unchanged = 0,                                   // UNCHANGED
		_motion_tracker_setting_off,                                             // OFF
		_motion_tracker_setting_moving_friendly_bipeds_moving_neutral_vehicles,  // FRIENDLY ONLY
		_motion_tracker_setting_moving_bipeds_moving_vehicles,                   // NORMAL
		_motion_tracker_setting_all_bipeds_moving_vehicles,                      // ALWAYS

		k_motion_tracker_settings
	};

	enum e_motion_tracker_range_setting : short
	{
		_motion_tracker_range_setting_unchanged = 0,  // UNCHANGED
		_motion_tracker_range_setting_10_meters,      // 10m
		_motion_tracker_range_setting_15_meters,      // 15m
		_motion_tracker_range_setting_25_meters,      // 25m
		_motion_tracker_range_setting_50_meters,      // 50m
		_motion_tracker_range_setting_75_meters,      // 75m
		_motion_tracker_range_setting_100_meters,     // 100m
		_motion_tracker_range_setting_150_meters,     // 150m

		k_motion_tracker_range_settings
	};

	// Traits that affect the HUD motion sensor behavior
	struct c_player_trait_sensors
	{
		e_motion_tracker_setting m_motion_tracker_settings;
		e_motion_tracker_range_setting m_motion_tracker_range;
	};
	static_assert(sizeof(c_player_trait_sensors) == 0x4);

	struct c_player_traits
	{
		c_player_trait_shield_vitality m_shield_traits;
		c_player_trait_weapons m_weapon_traits;
		c_player_trait_movement m_movement_traits;
		c_player_trait_appearance m_appearance_traits;
		c_player_trait_sensors m_sensor_traits;
	};
	static_assert(sizeof(c_player_traits) == 0x1C);
}

#pragma pack(pop)