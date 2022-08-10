#pragma once
#include "../Preferences/Preferences.hpp"

#include "../BlamData.hpp"
#include "../BlamObjects.hpp"
#include "../BlamPlayers.hpp"

#include <memory/thread_local.h>

namespace Blam::Memory
{
	using namespace blam;

	struct s_thread_local_storage;
	//s_thread_local_storage* get_thread_local()
	//{
	//	// TODO: Replace all instances of GetMainTls with get_thread_local 
	//	// once all the needed structs for s_thread_local_storage are written out.
	//	return ElDorito::GetMainTls().Read<s_thread_local_storage*>();
	//}

	struct simulation_gamestate_entity_datum : DatumBase
	{
		word __unknown2;
		dword __unknown4;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(simulation_gamestate_entity_datum) == 0x10);

	struct breakable_surface_set_broken_event_datum : DatumBase
	{
		char __data[0x462];
	};
	static_assert(sizeof(breakable_surface_set_broken_event_datum) == 0x464);

	struct hs_thread_deterministic_data : DatumBase
	{
		char __data[0x522];
	};
	static_assert(sizeof(hs_thread_deterministic_data) == 0x524);

	struct hs_global_data : DatumBase
	{
		word __unknown2;
		dword __unknown4;
	};
	static_assert(sizeof(hs_global_data) == 0x8);

	struct hs_distributed_global_data : DatumBase
	{
		char __data[0x2A];
	};
	static_assert(sizeof(hs_distributed_global_data) == 0x2C);

	struct hs_thread_tracking_data : DatumBase
	{
		word __unknown2;
		dword __unknown4;
		dword __unknown8;
	};
	static_assert(sizeof(hs_thread_tracking_data) == 0xC);

	struct hs_thread_non_deterministic_data : DatumBase
	{
		char __data[0x522];
	};
	static_assert(sizeof(hs_thread_non_deterministic_data) == 0x524);

	struct effect_datum : DatumBase
	{
		char __data[0x9E];
	};
	static_assert(sizeof(effect_datum) == 0xA0);

	struct effect_event_datum : DatumBase
	{
		char __data[0x12];
	};
	static_assert(sizeof(effect_event_datum) == 0x14);

	struct effect_location_datum : DatumBase
	{
		char __data[0x3E];
	};
	static_assert(sizeof(effect_location_datum) == 0x40);

	struct effect_geometry_sample_datum : DatumBase
	{
		char __data[0x26];
	};
	static_assert(sizeof(effect_geometry_sample_datum) == 0x28);

	struct game_looping_sound_datum : DatumBase
	{
		char __data[0x1E];
	};
	static_assert(sizeof(game_looping_sound_datum) == 0x20);

	struct recorded_animation_datum : DatumBase
	{
		char __data[0xA2];
	};
	static_assert(sizeof(recorded_animation_datum) == 0xA4);

	struct screen_effect_datum : DatumBase
	{
		word field_2;
		dword tag_index;
		float seconds_active;
		real_vector3d position;
		dword object_index;
		dword field_1c;
		real_vector3d field_20;
		real_vector3d field_2c;
		dword field_38;
	};
	static_assert(sizeof(screen_effect_datum) == 0x3C);

	struct s_decal_system_datum : DatumBase
	{
		short : 16;
		long tag_index;
		long __unknown8;
		long __unknownC;
		long __unknown10;
		long __unknown14;
		long __unknown18;
		long __unknown1C;
		long __unknown20;
		long __unknown24;
		long __unknown28;
		long __unknown2C;
		long __unknown30;
		long __unknown34;
		long __unknown38;
		long __unknown3C;
		long __unknown40;
		long __unknown44;
		long __unknown48;
		long __unknown4C;
		char __unknown50[0x307];
	};
	static_assert(sizeof(s_decal_system_datum) == 0x358);

	struct s_particle_system_datum : DatumBase
	{
		short particle_tag_index;
		long __unknown4;
		long __unknown8;
		long __unknownC;
		long __unknown10;
		long __unknown14;
		long __unknown18;
		long __unknown1C;
		long __unknown20;
		long __unknown24;
		long __unknown28;
		long __unknown2C;
		long __unknown30;
		long __unknown34;
		long __unknown38;
		long __unknown3C;
		long __unknown40;
		long __unknown44;
		long __unknown48;
		long __unknown4C;
		long __unknown50;
		long __unknown54;
	};
	static_assert(sizeof(s_particle_system_datum) == 0x58);

	struct chud_widget_datum : DatumBase
	{
		char __data[0x16];
	};
	static_assert(sizeof(chud_widget_datum) == 0x18);

	struct cluster_partition
	{
		DataArrayBase* first_data;
		DataArrayBase* data_reference;
		void* cluster_first_data_references;
	};

	struct recycling_group_datum : DatumBase
	{
		char __data[0x12];
	};
	static_assert(sizeof(recycling_group_datum) == 0x14);

	struct s_thread_local_storage
	{
		char* __unknown0;
		char* __unknown4;

		//  name: "sim. gamestate entities"
		// count: 2048
		//  size: 0x10
		DataArray<simulation_gamestate_entity_datum>* simulation_gamestate_entity_data;

		// name: "gamestate timing samples", "global"
		// size: 0x14
		s_game_tick_time_samples* g_main_gamestate_timing_data;

		// name: "render timing samples", "global"
		// size: 0x14
		s_game_tick_time_samples* g_main_render_timing_data;

		// name: "main_timing", "globals"
		// size: 0x40
		s_main_time_globals* g_main_time_globals;

		// size: 0x42000
		Blam::Preferences* g_global_preferences;

		char* __unknown1C;

		// from assert
		long g_registered_thread_index;

		char* __unknown24;
		char* __unknown28;
		char* __unknown2C;
		char* __unknown30;

		// name: "random math", "globals"
		// size: 0x4
		dword* g_deterministic_random_seed_ptr;

		char* filo_related;

		// name: "game globals"
		// size: 0x25208
		game_globals_storage* game_globals;

		// name: "players"
		// count: 16
		//  size: 0x2F08
		DataArray<Blam::Players::PlayerDatum>* player_data;

		// name: "players globals"
		players_globals* players_globals;

		// name: "game engine globals"
		// size: 0x15858
		game_engine_globals* game_engine_globals;

		// name: "local game engine globals"
		// size: 0xC4
		local_game_engine_globals* local_game_engine_globals;

		// name: "game time globals"
		// size: 0x2C
		game_time_globals_definition* game_time_globals;

		// name: "breakable surface breakable_surface_globals"
		// size: 0x3CE18
		s_breakable_surface_globals* breakable_surface_globals;

		//  name: "breakable surface set broken events"
		// count: 64
		//  size: 0x464
		DataArray<breakable_surface_set_broken_event_datum>* g_breakable_surface_set_broken_event_data;

		// name: "player mapping globals"
		// size: 0xE8
		s_player_mapping_globals* player_mapping_globals;

		// name: "director globals"
		// size: 0x5C0
		s_director_globals* director_globals;

		// name: "director scripting"
		// size: 0x1
		bool* director_camera_scripted;

		DataArray<hs_thread_deterministic_data>* hs_thread_deterministic_data;
		hs_runtime* hs_runtime;
		DataArray<hs_global_data>* hs_global_data;
		DataArray<hs_distributed_global_data>* hs_distributed_global_data;
		DataArray<hs_thread_tracking_data>* hs_thread_tracking_data;
		DataArray<hs_thread_non_deterministic_data>* hs_thread_non_deterministic_data;

		char* __unknown80;
		char* __unknown84;
		char* __unknown88;
		char* __unknown8C;
		char* __unknown90;
		char* __unknown94;
		char* __unknown98;
		char* __unknown9C;

		//  name: "effect"
		// count: 640
		//  size: 0xA0
		DataArray<effect_datum>* effect_data;

		//  name: "effect event"
		// count: 640
		//  size: 0x14
		DataArray<effect_event_datum>* event_data;

		//  name: "effect location"
		// count: 1152
		//  size: 0x40
		DataArray<effect_location_datum>* effect_location_data;

		// name: "effect counts"
		// size: 0x18
		s_effect_counts* g_effect_counts;

		//  name: "effect geometry sample"
		// count: 128
		//  size: 0x28
		DataArray<effect_geometry_sample_datum>* effect_geometry_sample_data;

		// name: "effect messaging queue"
		// size: 0x17084
		effect_messaging_queue* g_effect_message_queue;

		// name: "effect lightprobes"
		// size: 0xFE00
		effect_lightprobes* effect_lightprobe_data;

		// name: "havok gamestate"
		// size: 0x8
		s_havok_gamestate* g_havok_game_state;

		// from assert
		long havok_style_fpu_exceptions_count;

		// name: "player control globals"
		// size: 0x8B0
		s_player_control_globals* player_control_globals;

		// name: "player control globals deterministic"
		// size: 0x80
		s_player_control_globals_deterministic* player_control_globals_deterministic;

		//  name: "object looping sounds"
		// count: 1024
		//  size: 0x20
		DataArray<game_looping_sound_datum>* game_looping_sound_data;

		// name: "game sound globals"
		// size: 0x154
		s_game_sound_globals* game_sound_globals;

		// name: "game sound scripted impulses"
		// size: 0x200
		s_game_sound_impulse_datum* game_sound_scripted_impulses;

		// name: "s_structure_seam_globals"
		// size: 0x14614
		s_structure_seam_globals* g_structure_seam_globals;

		// name: "visibility active portals"
		// size: 0x800
		visibility_active_portals* visibility_active_portals;

		// name: "campaign meta-game globals"
		// size: 0x1A158
		s_campaign_metagame_globals* g_campaign_metagame_globals;

		// name: "observer gamestate globals"
		// size: 0xC
		s_observer_gamestate_globals* observer_gamestate_globals;

		// name: "observer globals"
		// size: 0xF28
		s_observer_globals* g_observer_globals;

		// name: "rumble"
		// size: 0x22C
		rumble_global_data* rumble_globals;

		// name: "bink game state"
		// size: 0x8
		s_bink_shared_game_state* bink_game_state;

		char* __unknownF4;

		struct s_font_cache_globals* g_font_cache_globals;

		// name: "sound classes"
		// size: 0x1144
		sound_class_datum* sound_class_data;

		// name: "game allegiance globals"
		// size: 0x184
		s_game_allegiance_globals* game_allegiance_globals;

		// name: "atmosphere fog globals"
		// size: 0x14
		s_atmosphere_fog_globals* g_atmosphere_fog_globals;

		// name: "soft surface globals"
		// size: 0x10
		s_scenario_soft_ceilings_globals* g_scenario_soft_ceilings_globals;

		// name: "game sound player effects globals"
		// size: 0x28
		s_game_sound_player_effects_globals* g_game_sound_player_effects_globals;

		//  name: "havok proxies"
		// count: 16
		//  size: 0x44
		char* g_havok_proxy_data; // s_data_array

		char* __unknown114;
		char* __unknown118;
		char* __unknown11C;
		char* __unknown120;
		char* __unknown124;
		char* __unknown128;
		char* __unknown12C;
		char* __unknown130;
		char* __unknown134;
		char* __unknown138;
		char* __unknown13C;
		char* __unknown140;
		char* __unknown144;
		char* __unknown148;
		char* __unknown14C;
		char* __unknown150;
		char* __unknown154;
		char* __unknown158;
		char* __unknown15C;
		char* __unknown160;
		char* __unknown164;
		char* __unknown168;
		char* __unknown16C;
		char* __unknown170;
		char* __unknown174;
		char* __unknown178;
		char* __unknown17C;
		char* __unknown180;
		char* __unknown184;
		char* __unknown188;
		char* __unknown18C;
		char* __unknown190;
		char* __unknown194;
		char* __unknown198;
		char* __unknown19C;
		char* __unknown1A0;
		char* __unknown1A4;
		char* __unknown1A8;
		char* __unknown1AC;
		char* __unknown1B0;
		char* __unknown1B4;
		char* __unknown1B8;
		char* __unknown1BC;
		char* __unknown1C0;
		char* __unknown1C4;
		char* __unknown1C8;
		char* __unknown1CC;
		char* __unknown1D0;
		char* __unknown1D4;
		char* __unknown1D8;
		char* __unknown1Dc;
		char* __unknown1E0;
		char* __unknown1E4;
		char* __unknown1E8;
		char* __unknown1EC;
		char* __unknown1F0;
		char* __unknown1F4;
		char* __unknown1F8;
		char* __unknown1FC;
		char* __unknown200;
		char* __unknown204;
		char* __unknown208;
		char* __unknown20C;
		char* __unknown210;
		char* __unknown214;
		char* __unknown218;
		char* __unknown21C;
		char* __unknown220;
		char* __unknown224;
		char* __unknown228;
		char* __unknown22C;
		char* __unknown230;
		char* __unknown234;
		char* __unknown238;
		char* __unknown23C;
		char* __unknown240;
		char* __unknown244;
		char* __unknown248;
		char* __unknown24C;
		char* __unknown250;
		char* __unknown254;
		char* __unknown258;
		char* __unknown25C;
		char* __unknown260;
		char* __unknown264;
		char* __unknown268;
		char* __unknown26C;
		char* __unknown270;
		char* __unknown274;
		char* __unknown278;
		char* __unknown27C;
		char* __unknown280;
		char* __unknown284;
		char* __unknown288;
		char* __unknown28C;
		char* __unknown290;
		char* __unknown294;
		char* __unknown298;
		char* __unknown29C;
		char* __unknown2A0;
		char* __unknown2A4;
		char* __unknown2A8;
		char* __unknown2AC;
		char* __unknown2B0;
		char* __unknown2B4;
		char* __unknown2B8;
		char* __unknown2BC;
		char* __unknown2C0;
		char* __unknown2C4;
		char* __unknown2C8;
		char* __unknown2CC;
		char* __unknown2D0;
		char* __unknown2D4;
		char* __unknown2D8;
		char* __unknown2DC;
		char* __unknown2E0;
		char* __unknown2E4;
		char* __unknown2E8;
		char* __unknown2EC;
		char* __unknown2F0;
		char* __unknown2F4;
		char* __unknown2F8;
		char* __unknown2FC;
		char* __unknown300;
		char* __unknown304;
		char* __unknown308;
		char* __unknown30C;
		char* __unknown310;
		char* __unknown314;
		char* __unknown318;
		char* __unknown31C;

		// name: "cinematic new globals"
		// size: 0x2808
		cinematic_new_globals* cinematic_new_globals;

		// name: "cinematic globals"
		// size: 0x3C
		cinematic_globals* cinematic_globals;

		// name: "cinematic light globals"
		// size: 0xB2C8
		cinematic_light_globals* cinematic_light_globals;

		// name: "physics constants"
		// size: 0x20
		s_physics_constants* g_physics_constants;

		//  name: "recorded animations"
		// count: 1
		//  size: 0xA4
		Blam::DataArray<recorded_animation_datum>* animation_threads;

		// name: "game save globals"
		// size: 0x18
		s_game_save_globals* g_game_save_globals;

		//  name: "screen_effect"
		// count: 64
		//  size: 0x3C
		Blam::DataArray<screen_effect_datum>* screen_effect_data;

		// name: "player effects"
		// size: 0x3A0
		s_player_effect_globals* player_effect_globals;

		// name: "scenario interpolator globals"
		// size: 0x204
		s_scenario_interpolator_globals* scenario_interpolator_globals;

		// name: "survival mode globals"
		// size: 0x7E0
		s_survival_mode_globals* g_survival_mode_globals;

		// name: "player training globals", "globals"
		// size: 0x8E8
		s_player_training_globals* player_training_globals;

		// name: "kill trigger volume state"
		// size: 0x84
		s_scenario_kill_trigger_volumes_state* g_scenario_kill_trigger_volumes_state;

		// name: "deterministic game sound globals"
		// size: 0x1300
		s_game_sound_deterministic_globals* g_future_development_game_sound_deterministic_globals;

		//  name: "decal_system"
		// count: 856
		//  size: 0x54
		Blam::DataArray<s_decal_system_datum>* decal_system;

		// name: "decal counts"
		// size: 0x20
		s_decal_counts* decal_counts;

		//  name: "decal"
		// count: 856
		//  size: 0x130
		decal* decal_data;

		// name: "decal messaging queue"
		// size: 0x824
		s_decal_message_queue* g_decal_message_queue;

		// name: "impact globals"
		// size: 0x8C
		s_impact_globals* g_impact_globals;

		//  name: "impacts"
		// count: 32
		//  size: 0xB4
		impacts* impacts;

		//  name: "impact arrarys"
		// count: 32
		//  size: 0x88
		impact_arrays* impact_arrays;

		//  name: "object list header"
		// count: 48
		//  size: 0xC
		object_list_header* object_list_header;

		//  name: "list object"
		// count: 128
		//  size: 0xC
		list_object* list_object;

		// name: "scripted camera globals"
		// size: 0xF0
		scripted_camera_globals* scripted_camera_globals;

		Blam::DataArrayBase* particles;
		Blam::DataArray<s_particle_system_datum>* particle_system;
		contrail_system* contrail_system;
		contrail* contrail;
		contrail_location* contrail_location;
		contrail_profile* contrail_profile;
		particle_location* particle_location;
		light_volume_system* light_volume_system;
		light_volume_location* light_volume_location;
		light_volume* light_volume;
		beam_system* beam_system;
		beam* beam;
		beam_location* beam_location;
		char* __unknown3B0_render_postprocess_color_tweaking;
		ragdolls* ragdolls;
		particle_emitter* particle_emitter;
		rasterizer_game_states* rasterizer_game_states;
		hue_saturation_control* hue_saturation_control;
		char* __unknown3C4;
		scripted_exposure_globals* scripted_exposure_globals;
		render_hud_globals* render_hud_globals;
		water_interaction_ripples* water_interaction_ripples;
		render_texture_globals* render_texture_globals;
		render_game_globals* render_game_globals;
		depth_of_field_globals* depth_of_field_globals;
		cached_object_render_states* cached_object_render_states;
		particle_emitter_gpu_row* particle_emitter_gpu_row;
		particle_emitter_gpu_1* particle_emitter_gpu_1;
		char* particle_emitter_gpu_2;
		beam_gpu* beam_gpu;
		beam_gpu_row* beam_gpu_row;
		char* particle_emitter_gpu_3;
		contrail_gpu_row* contrail_gpu_row;
		contrail_gpu* contrail_gpu;
		char* particle_emitter_gpu_4;
		light_volume_gpu* light_volume_gpu;
		light_volume_gpu_row* light_volume_gpu_row;
		char* particle_emitter_gpu_5;
		char* rasterizer_implicit_geometry_data;
		render_object_globals* render_object_globals;
		shield_render_cache_message* shield_render_cache_message;
		chud_persistent_user_data* chud_persistent_user_data;
		chud_persistent_global_data* chud_persistent_global_data;

		// name: "chud widgets[0]"
		// name: "chud widgets[1]"
		// name: "chud widgets[2]"
		// name: "chud widgets[3]"
		Blam::DataArray<chud_widget_datum>* chud_widgets[4];

		// name: "fp orientations"
		// size: 0x12C00
		s_first_person_orientations* first_person_orientations;

		// name: "fp weapons"
		// size: 0x14000
		first_person_weapon* first_person_weapon;

		// name: "chud", "cortana effect"
		// size: 0x10
		s_cortana_globals* g_cortana_globals;

		// name: "campaign objectives"
		// size: 0x14
		s_current_objective_state* g_objectives;

		//  name: "object"
		// count: 2048
		//  size: 0x18
		DataArray<Blam::Objects::ObjectHeader>* object_header_data;

		// name: "object globals"
		// size: 0x6608
		s_object_globals* object_globals;

		// name: "objects"
		// size: 0x180000
		// s_memory_pool* object_memory_pool
		objects_memory_pool* objects_memory_pool;

		// name: "object name list"
		// size: 0x2000
		long* g_object_name_list;

		// name: "object messaging queue"
		// size: 0x4104
		// s_object_render_thread_message (*g_object_message_queue)[2048];
		object_messaging_queue* g_object_message_queue;

		// name: "collideable object"
		// size: 0x14
		cluster_partition collideable_object_cluster_partition;

		// name: "noncollideable object"
		// size: 0x14
		cluster_partition noncollideable_object_cluster_partition;

		// name: "OBJ: Render Data", "Render"
		// size: 0x2000
		object_render_data* object_render_data;

		// name: "damage globals"
		// size: 0x810
		s_damage_globals* damage_globals;

		// name: "object placement globals"
		// size: 0x320
		s_object_placement_globals* object_placement_globals;

		//  name: "device groups"
		// count: 1024
		//  size: 0x10
		device_groups* device_groups_data;

		// name: "object scripting"
		// size: 0x304
		object_scripting* object_scripting;

		// name: "object_broadphase", "global"
		// size: 0x32450
		s_object_broadphase* g_object_broadphase;

		// name: "object early movers"
		// size: 0x2688
		s_object_early_movers_globals* g_object_early_movers_globals;

		// name: "object schedule globals"
		// size: 0x27C
		s_object_scehdule_globals* g_object_scehdule_globals;

		//  name: "object activation regions"
		// count: 128
		//  size: 0x28
		object_activation_regions* g_object_activation_regions_data;

		//  name: "lights"
		// count: 400
		//  size: 0xE4
		lights* lights;

		// name: "lights globals"
		// size: 0x40
		lights_game_globals_definition* lights_game_globals;

		// name: "light"
		// size: 0xC
		cluster_partition light_cluster_partition;

		// name: "nondet_light_data", "render lights"
		// size: 0x2580
		s_nondeterministic_light_data* g_nondeterministic_light_data;

		widget* widget_data;

		// name: "recycling_volumes"
		// size: 0x148
		s_recycling_volumes* recycling_volumes;

		//  name: "recycling_group"
		// count: 128
		//  size: 0x14
		DataArray<recycling_group_datum>* recycling_groups;

		muffin* muffin_data;

		leaf_system* leaf_system_data;

		antenna* antenna_data;

		cloth* cloth_data;

		char* __unknown4CC;
		char* __unknown4D0;
		char* __unknown4D4;
		char* __unknown4D8;
		char* __unknown4DC;
		char* __unknown4E0;
		char* __unknown4E4;
		char* __unknown4E8;
		char* __unknown4EC;
		char* __unknown4F0;
		char* __unknown4F4;
		char* __unknown4F8;
		char* __unknown4FC;
		char* __unknown500;
		char* __unknown504;
		char* __unknown508;
		char* __unknown50C;
		char* __unknown510;
		char* __unknown514;
		char* __unknown518;

		actor* actor;
		actor_firing_position* actor_firing_position;
		ai_reference_frame* ai_reference_frame;
		ai_globals* ai_globals;
		ai_player_state* ai_player_state;
		vocalization_records* vocalization_records;
		vocalization_timers* vocalization_timers;
		command_scripts* command_scripts;
		objectives* objectives;
		task_records* task_records;
		squad* squad;
		squad_group* squad_group;
		swarm* swarm;
		swarm_spawner* swarm_spawner;
		spawner_globals* spawner_globals;
		dynamic_firing_points* dynamic_firing_points;
		propref* propref;
		prop* prop;
		tracking* tracking;
		joint_state* joint_state;
		clump* clump;
		squad_patrol* squad_patrol;
		flocks* flocks;
		formations* formations;

		// name: "vision mode globals"
		// size: 0xF0
		vision_mode* vision_mode;

		char* __unknown580;
	};
}