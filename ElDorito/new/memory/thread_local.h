#pragma once

#include "camera/observer.hpp"
#include "camera/camera.hpp"
#include "camera/director.hpp"
#include "game/game_globals.hpp"
#include "game/player_control.hpp"
#include "game/player_mapping.hpp"

namespace blam
{
	//struct simulation_gamestate_entity_datum : datum_header

	struct s_game_tick_time_samples
	{
		long flags;
		float float4;
		float float8;
		float floatC;
		dword __unknown10;
	};
	static_assert(sizeof(s_game_tick_time_samples) == 0x14);

	struct s_main_time_globals
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
		dword __unknown10;
		dword __unknown14;
		dword __unknown18;
		dword __unknown1C;
		dword __unknown20;
		dword __unknown24;
		dword __unknown28;
		dword __unknown2C;
		dword __unknown30;
		dword __unknown34;
		dword __unknown38;
		dword __unknown3C;
	};
	static_assert(sizeof(s_main_time_globals) == 0x40);

	struct players_globals
	{
		char __data[0x234];
	};
	static_assert(sizeof(players_globals) == 0x234);

	struct game_engine_globals
	{
		dword Flags;
		dword __unknown4;
		dword __unknown8;
		word __unknownC;
		word GameSimulation;
		dword __unknown16[7];
		dword __unknown2C;
		dword __unknown30[14390];
		word __unknownE108;
		word __unknownE10A;
		dword __unknownE10C;
		byte __unknownE110;
		byte __unknownE111[3];
		byte __unknownE114[124];
		byte __unknownE190[1832];
		byte ForgeLegalNotice;
		byte __unknownE8B9[4311];
		word RoundTimeLimit;
		word __unknownF992;
		dword RoundTimeLimitTicksPerSecond;
		byte __unknownF996[1304];
		byte MultiplayerScoreboard[0x420];
		byte __unknown102D0[0x3AD0];
		dword __unknown13DA0;
		dword __unknown13DA4[3];
		dword GameType;
		dword ObjectCount;
		dword __unknown13DB8;
		byte __unknown13DBC[6812];
	};
	static_assert(sizeof(game_engine_globals) == 0x15858);

	struct local_game_engine_globals
	{
		char __data[0xC4];
	};
	static_assert(sizeof(local_game_engine_globals) == 0xC4);

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

	struct s_breakable_surface_globals
	{
		char __data[0x3CE18];
	};
	static_assert(sizeof(s_breakable_surface_globals) == 0x3CE18);

	//struct breakable_surface_set_broken_event_datum : datum_header

	//struct hs_thread_deterministic_data : datum_header

	struct hs_runtime
	{
		dword __unknown0;
		dword __unknown4;
	};
	static_assert(sizeof(hs_runtime) == 0x8);

	//struct hs_global_data : datum_header

	//struct hs_distributed_global_data : datum_header

	//struct hs_thread_tracking_data : datum_header

	//struct hs_thread_non_deterministic_data : datum_header

	//struct effect_datum : datum_header

	//struct effect_event_datum : datum_header

	//struct effect_location_datum : datum_header

	struct s_effect_counts
	{
		char __data[0x18];
	};
	static_assert(sizeof(s_effect_counts) == 0x18);

	//struct effect_geometry_sample_datum : datum_header

	struct effect_messaging_queue
	{
		char __data[0x17084];
	};
	static_assert(sizeof(effect_messaging_queue) == 0x17084);

	struct effect_lightprobes
	{
		char __data[0xFE00];
	};
	static_assert(sizeof(effect_lightprobes) == 0xFE00);

	struct s_havok_gamestate
	{
		dword __unknown0;
		dword __unknown4;
	};
	static_assert(sizeof(s_havok_gamestate) == 0x8);

	struct s_player_control_globals_deterministic
	{
		char __data[0x80];
	};
	static_assert(sizeof(s_player_control_globals_deterministic) == 0x80);

	//struct game_looping_sound_datum : datum_header

	struct s_game_sound_globals
	{
		char __data[0x154];
	};
	static_assert(sizeof(s_game_sound_globals) == 0x154);

	struct s_game_sound_impulse_datum
	{
		char __data[0x200];
	};
	static_assert(sizeof(s_game_sound_impulse_datum) == 0x200);

	struct s_structure_seam_globals
	{
		char __data[0x14614];
	};
	static_assert(sizeof(s_structure_seam_globals) == 0x14614);

	struct visibility_active_portals
	{
		char __data[0x800];
	};
	static_assert(sizeof(visibility_active_portals) == 0x800);

	struct s_campaign_metagame_globals
	{
		char __data[0x1A158];
	};
	static_assert(sizeof(s_campaign_metagame_globals) == 0x1A158);

	struct s_observer_gamestate_globals
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(s_observer_gamestate_globals) == 0xC);

	struct rumble_global_data
	{
		char __data[0x22C];
	};
	static_assert(sizeof(rumble_global_data) == 0x22C);

	struct s_bink_shared_game_state
	{
		dword __unknown0;
		dword __unknown4;
	};
	static_assert(sizeof(s_bink_shared_game_state) == 0x8);

	struct sound_class_datum
	{
		char __data[0x1144];
	};
	static_assert(sizeof(sound_class_datum) == 0x1144);

	struct s_game_allegiance_globals
	{
		char __data[0x184];
	};
	static_assert(sizeof(s_game_allegiance_globals) == 0x184);

	struct s_atmosphere_fog_globals
	{
		char __data[0x14];
	};
	static_assert(sizeof(s_atmosphere_fog_globals) == 0x14);

	struct s_scenario_soft_ceilings_globals
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(s_scenario_soft_ceilings_globals) == 0x10);

	struct s_game_sound_player_effects_globals
	{
		char __data[0x28];
	};
	static_assert(sizeof(s_game_sound_player_effects_globals) == 0x28);

	struct cinematic_new_globals
	{
		char __data[0x3C];
	};
	static_assert(sizeof(cinematic_new_globals) == 0x3C);

	struct cinematic_globals
	{
		char __unknown0[4];
		char show_letterbox;
		char start_stop;
		char skip_start_stop;
		char suppress_bsp_object_creation;
		char __unknown8[24];
		dword subtitle_string_id;
		float subtitle_time_shown;
		float subtitle_time_shown2;
		char __unknown2C[2];
		char outro_start_stop;
		char __unknown2F[10201];
	};
	static_assert(sizeof(cinematic_globals) == 0x2808);

	struct cinematic_light_globals
	{
		char __data[0xB2C8];
	};
	static_assert(sizeof(cinematic_light_globals) == 0xB2C8);

	struct s_physics_constants
	{
		dword gravity;
		dword water_density;
		dword air_density;
		dword __unknownC;
		dword __unknown10;
		float float14;
		dword __unknown18;
		dword __unknown1C;
	};
	static_assert(sizeof(s_physics_constants) == 0x20);

	//struct recorded_animation_datum : datum_header

	struct s_game_save_globals
	{
		char __data[0x18];
	};
	static_assert(sizeof(s_game_save_globals) == 0x18);

	//struct s_rasterizer_screen_effect : datum_header

	struct s_player_effect_globals
	{
		char __data[0x3A0];
	};
	static_assert(sizeof(s_player_effect_globals) == 0x3A0);

	struct s_scenario_interpolator_globals
	{
		char __data[0x204];
	};
	static_assert(sizeof(s_scenario_interpolator_globals) == 0x204);

	struct s_survival_mode_globals
	{
		long lives;
		short set;
		short round;
		short wave;
		short __unknownA;
		short set_multiplier;
		short __unknown10;
		long round_multiplier;
		short waves_per_round;
		short rounds_per_set;
		char __unknown18[4];
		long __unknown1C;
		char __unknown20[4];
		long __unknown24;
		long __unknown28;
		char __unknown2C[4];
		long scoreboard;
		char __unknown34[464];

		char __data[0x5DC];
	};
	static_assert(sizeof(s_survival_mode_globals) == 0x7E0);

	struct s_player_training_globals
	{
		char __data[0x8E8];
	};
	static_assert(sizeof(s_player_training_globals) == 0x8E8);

	struct s_scenario_kill_trigger_volumes_state
	{
		char __data[0x84];
	};
	static_assert(sizeof(s_scenario_kill_trigger_volumes_state) == 0x84);

	struct s_game_sound_deterministic_globals
	{
		char __data[0x1300];
	};
	static_assert(sizeof(s_game_sound_deterministic_globals) == 0x1300);

	//struct s_decal_system_datum : datum_header

	struct s_decal_counts
	{
		char __data[0x20];
	};
	static_assert(sizeof(s_decal_counts) == 0x20);

	struct decal
	{
		char __data[0x130];
	};
	static_assert(sizeof(decal) == 0x130);

	struct s_decal_message_queue
	{
		char __data[0x824];
	};
	static_assert(sizeof(s_decal_message_queue) == 0x824);

	struct s_impact_globals
	{
		byte __unknown0[0x8C];
	};
	static_assert(sizeof(s_impact_globals) == 0x8C);

	struct impacts
	{
		byte __unknown0[0xB4];
	};
	static_assert(sizeof(impacts) == 0xB4);

	struct impact_arrays
	{
		byte __unknown0[0x88];
	};
	static_assert(sizeof(impact_arrays) == 0x88);

	struct object_list_header
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(object_list_header) == 0xC);

	struct list_object
	{
		char __data[0x8C];
	};
	static_assert(sizeof(list_object) == 0x8C);

	struct scripted_camera_globals
	{
		byte __unknown0[0xF0];
	};
	static_assert(sizeof(scripted_camera_globals) == 0xF0);

	//struct s_particle_system_datum : datum_header

	struct contrail_system
	{
		char __data[0x4C];
	};
	static_assert(sizeof(contrail_system) == 0x4C);

	struct contrail
	{
		char __data[0x4C];
	};
	static_assert(sizeof(contrail) == 0x4C);

	struct contrail_location
	{
		char __data[0x60];
	};
	static_assert(sizeof(contrail_location) == 0x60);

	struct contrail_profile
	{
		char __data[0x4C];
	};
	static_assert(sizeof(contrail_profile) == 0x4C);

	struct particle_location
	{
		char __data[0x60];
	};
	static_assert(sizeof(particle_location) == 0x60);

	struct light_volume_location
	{
		char __data[0x2C];
	};
	static_assert(sizeof(light_volume_location) == 0x2C);

	struct light_volume
	{
		char __data[0x34];
	};
	static_assert(sizeof(light_volume) == 0x34);

	struct light_volume_system
	{
		char __data[0x2C];
	};
	static_assert(sizeof(light_volume_system) == 0x2C);

	struct beam_system
	{
		char __data[0x34];
	};
	static_assert(sizeof(beam_system) == 0x34);

	struct beam
	{
		char __data[0x2C];
	};
	static_assert(sizeof(beam) == 0x2C);

	struct beam_location
	{
		char __data[0x30];
	};
	static_assert(sizeof(beam_location) == 0x30);

	struct hue_saturation_control
	{
		dword graphics_override;
		dword saturation;
		dword color;
		dword __unknownC;
		dword __unknown10;
	};
	static_assert(sizeof(hue_saturation_control) == 0x14);

	struct ragdolls
	{
		char __data[0x130];
	};
	static_assert(sizeof(ragdolls) == 0x130);

	struct particle_emitter
	{
		char __data[0x90];
	};
	static_assert(sizeof(particle_emitter) == 0x90);

	struct rasterizer_game_states
	{
		char motion_blur;
		char atmosphere_fog;
		char patchy_fog;
		char weather;
		char cinematic_motion_blur;
		char __unknown5[39];
		char autoexposure;
		char __unknown44[475];
	};
	static_assert(sizeof(rasterizer_game_states) == 0x208);

	struct scripted_exposure_globals
	{
		char __data[0x34];
	};
	static_assert(sizeof(scripted_exposure_globals) == 0x34);

	struct render_hud_globals
	{
		char __data[0x480];
	};
	static_assert(sizeof(render_hud_globals) == 0x480);

	struct water_interaction_ripples
	{
		char __data[0x1400];
	};
	static_assert(sizeof(water_interaction_ripples) == 0x1400);

	struct render_texture_globals
	{
		char camera_enable;
		char camera_dynamic_lights_enable;
		short __unknown2;
		long camera_render_mode;
		long __unknown8;
		long __unknownC;
		long __unknown10;
		long __unknown14;
		long __unknown18;
		long camera_object_handle;
		long camera_marker_name;
		long __unknown24;
		long camera_position_world_x;
		long camera_position_world_y;
		long camera_position_world_z;
		long camera_target_object_x;
		long camera_target_object_y;
		long camera_target_object_z;
		char __unknown40[28];
		float camera_fov;
		long aspect_ratio;
		long camera_resolution_width;
		long camera_resolution_height;
	};
	static_assert(sizeof(render_texture_globals) == 0x6C);

	struct render_game_globals
	{
		char __data[0xD80];
	};
	static_assert(sizeof(render_game_globals) == 0xD80);

	struct depth_of_field_globals
	{
		bool enable;
		char __unknown1[3];
		float __unknown4;
		float __unknown8;
		float __unknownC;
		float intensity;
		float __unknown14;
		float __unknown18;
		float __unknown1C;
		float __unknown20;
		float __unknown24;
		float __unknown28;
		float __unknown2C;
		float __unknown30;
		float __unknown34;
		float __unknown38;
		float __unknown3C;
	};
	static_assert(sizeof(depth_of_field_globals) == 0x40);

	struct cached_object_render_states
	{
		char __data[0x4D8];
	};
	static_assert(sizeof(cached_object_render_states) == 0x4D8);

	struct particle_emitter_gpu_row
	{
		char __data[0x18];
	};
	static_assert(sizeof(particle_emitter_gpu_row) == 0x18);

	struct particle_emitter_gpu_1
	{
		char __data[0x14];
	};
	static_assert(sizeof(particle_emitter_gpu_1) == 0x14);

	struct beam_gpu
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(beam_gpu) == 0x10);

	struct beam_gpu_row
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(beam_gpu_row) == 0xC);

	struct contrail_gpu_row
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(contrail_gpu_row) == 0x10);

	struct contrail_gpu
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
		dword __unknown10;
	};
	static_assert(sizeof(contrail_gpu) == 0x14);

	struct light_volume_gpu
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(light_volume_gpu) == 0x10);

	struct light_volume_gpu_row
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(light_volume_gpu_row) == 0xC);

	struct render_object_globals
	{
		char __data[0x3C040];
	};
	static_assert(sizeof(render_object_globals) == 0x3C040);

	struct shield_render_cache_message
	{
		char __data[0x14];
	};
	static_assert(sizeof(shield_render_cache_message) == 0x14);

	struct chud_player_hud_elements
	{
		char __unknown0[2];
		char crosshair;
		char shield;
		char grenades;
		char messages;
		char motion_sensor;
		char spike_grenades;
		char fire_grenades;
		char compass;
		char stamina;
		char energy_meters;
		char consumables;
	};

	struct chud_persistent_user_data
	{
		char __data[0x14D];
		chud_player_hud_elements player_hud;
		char __unknown181[0x316];
	};
	static_assert(sizeof(chud_persistent_user_data) == 0x470);

	struct chud_persistent_global_data
	{
		char __unknown0[0x14D];
		chud_player_hud_elements player_hud[4];
		char __unknown181[0x273];
		char bonus_round_show_timer;
		char bonus_round_start_timer;
		char __unknown3F6[2];
		long bonus_round_set_timer;
		long bonus_round_set_target_score;
		char __unknown3FC[0xF640];
	};
	static_assert(sizeof(chud_persistent_global_data) == 0xFA40);

	// struct chud_widget_datum : datum_header

	struct s_first_person_orientations
	{
		char __data[0x12C00];
	};
	static_assert(sizeof(s_first_person_orientations) == 0x12C00);

	struct first_person_weapon
	{
		char __data[0x14000];
	};
	static_assert(sizeof(first_person_weapon) == 0x14000);

	struct s_cortana_globals
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(s_cortana_globals) == 0x10);

	struct s_current_objective_state
	{
		char __data[0x14];
	};
	static_assert(sizeof(s_current_objective_state) == 0x14);

	struct s_object_globals
	{
		char __data[0x6608];
	};
	static_assert(sizeof(s_object_globals) == 0x6608);

	struct objects_memory_pool
	{
		char __data[0x44];
	};
	static_assert(sizeof(objects_memory_pool) == 0x44);

	struct object_messaging_queue
	{
		char __data[0x4104];
	};
	static_assert(sizeof(object_messaging_queue) == 0x4104);

	struct damage_globals
	{
		char __data[0x810];
	};
	static_assert(sizeof(damage_globals) == 0x810);

	struct object_render_data
	{
		char __data[0x2000];
	};
	static_assert(sizeof(object_render_data) == 0x2000);

	struct s_damage_globals
	{
		char __data[0x810];
	};
	static_assert(sizeof(s_damage_globals) == 0x810);

	struct s_object_placement_globals
	{
		char __data[0x320];
	};
	static_assert(sizeof(s_object_placement_globals) == 0x320);

	struct device_groups
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(device_groups) == 0x10);

	struct object_scripting
	{
		char __data[0x304];
	};
	static_assert(sizeof(object_scripting) == 0x304);

	struct s_object_broadphase
	{
		char __data[0x32450];
	};
	static_assert(sizeof(s_object_broadphase) == 0x32450);

	struct s_object_early_movers_globals
	{
		char __data[0x2688];
	};
	static_assert(sizeof(s_object_early_movers_globals) == 0x2688);

	struct s_object_scehdule_globals
	{
		char __data[0x27C];
	};
	static_assert(sizeof(s_object_scehdule_globals) == 0x27C);

	struct object_activation_regions
	{
		char __data[0x28];
	};
	static_assert(sizeof(object_activation_regions) == 0x28);

	struct lights
	{
		char __data[0xE4];
	};
	static_assert(sizeof(lights) == 0xE4);

	struct lights_game_globals_definition
	{
		char __data[0x40];
	};
	static_assert(sizeof(lights_game_globals_definition) == 0x40);

	struct s_nondeterministic_light_data
	{
		char __data[0x2580];
	};
	static_assert(sizeof(s_nondeterministic_light_data) == 0x2580);

	struct widget
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(widget) == 0xC);

	struct s_recycling_volumes
	{
		char __data[0x148];
	};
	static_assert(sizeof(s_recycling_volumes) == 0x148);

	//struct recycling_group_datum : datum_header

	struct muffin
	{
		char __data[0x1890];
	};
	static_assert(sizeof(muffin) == 0x1890);

	struct leaf_system
	{
		char __data[0x94C];
	};
	static_assert(sizeof(leaf_system) == 0x94C);

	struct antenna
	{
		char __data[0x64];
	};
	static_assert(sizeof(antenna) == 0x64);

	struct cloth
	{
		char __data[0x1704];
	};
	static_assert(sizeof(cloth) == 0x1704);

	struct actor
	{
		char __data[0xA98];
	};
	static_assert(sizeof(actor) == 0xA98);

	struct actor_firing_position
	{
		char __data[0x400];
	};
	static_assert(sizeof(actor_firing_position) == 0x400);

	struct ai_reference_frame
	{
		char __data[0x4B0];
	};
	static_assert(sizeof(ai_reference_frame) == 0x4B0);

	struct ai_globals
	{
		char enable;
		char __unknown1;
		short flags;
		char __unknown4;
		char fast_and_dumb;
		char __unknown5[1666];
	};
	static_assert(sizeof(ai_globals) == 0x688);

	struct ai_player_state
	{
		char __data[0xB0];
	};
	static_assert(sizeof(ai_player_state) == 0xB0);

	struct vocalization_records
	{
		char __data[0x5C];
	};
	static_assert(sizeof(vocalization_records) == 0x5C);

	struct vocalization_timers
	{
		char __data[0xFB8];
	};
	static_assert(sizeof(vocalization_timers) == 0xFB8);

	struct command_scripts
	{
		char __data[0x188];
	};
	static_assert(sizeof(command_scripts) == 0x188);

	struct objectives
	{
		dword __unknown0;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(objectives) == 0xC);

	struct task_records
	{
		char __data[0x61A80];
	};
	static_assert(sizeof(task_records) == 0x61A80);

	struct squad
	{
		char __data[0xEC];
	};
	static_assert(sizeof(squad) == 0xEC);

	struct squad_group
	{
		char __data[0x24];
	};
	static_assert(sizeof(squad_group) == 0x24);

	struct swarm
	{
		char __data[0x34];
	};
	static_assert(sizeof(swarm) == 0x34);

	struct swarm_spawner
	{
		char __data[0x258];
	};
	static_assert(sizeof(swarm_spawner) == 0x258);

	struct spawner_globals
	{
		short __unknown0;
	};
	static_assert(sizeof(spawner_globals) == 0x2);

	struct dynamic_firing_points
	{
		char __data[0x584];
	};
	static_assert(sizeof(dynamic_firing_points) == 0x584);

	struct propref
	{
		char __data[0x3C];
	};
	static_assert(sizeof(propref) == 0x3C);

	struct prop
	{
		char __data[0xC4];
	};
	static_assert(sizeof(prop) == 0xC4);

	struct tracking
	{
		char __data[0x100];
	};
	static_assert(sizeof(tracking) == 0x100);

	struct joint_state
	{
		char __data[0xCC];
	};
	static_assert(sizeof(joint_state) == 0xCC);

	struct clump
	{
		char __data[0x108];
	};
	static_assert(sizeof(clump) == 0x108);

	struct squad_patrol
	{
		char __data[0x6C4];
	};
	static_assert(sizeof(squad_patrol) == 0x6C4);

	struct flocks
	{
		char __data[0x4C];
	};
	static_assert(sizeof(flocks) == 0x4C);

	struct formations
	{
		char __data[0x294];
	};
	static_assert(sizeof(formations) == 0x294);

	struct vision_mode
	{
		char __data[0xF0];
	};
	static_assert(sizeof(vision_mode) == 0xF0);
}
