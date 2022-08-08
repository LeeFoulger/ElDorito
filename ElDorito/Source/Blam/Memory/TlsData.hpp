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

	struct s_rasterizer_screen_effect : DatumBase
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
	static_assert(sizeof(s_rasterizer_screen_effect) == 0x3C);

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


	struct s_thread_local_storage
	{
		char* __unknown0;
		char* __unknown4;

		// name: "sim. gamestate entities"
		DataArray<simulation_gamestate_entity_datum>* simulation_gamestate_entity_data;

		// name: "gamestate timing samples", "global"
		s_game_tick_time_samples* g_main_gamestate_timing_data;

		// name: "render timing samples", "global"
		s_game_tick_time_samples* g_main_render_timing_data;

		// name: "main_timing", "globals"
		s_main_time_globals* g_main_time_globals;

		Blam::Preferences* preferences;

		char* __unknown1C;
		char* __unknown20;
		char* __unknown24;
		char* __unknown28;
		char* __unknown2C;
		char* __unknown30;

		// name: "random math", "globals"
		random_math_globals* random_math_globals;

		char* filo_related;

		// name: "game globals"
		game_globals_storage* game_globals;

		// name: "players"
		DataArray<Blam::Players::PlayerDatum>* player_data;

		// name: "players globals"
		players_globals* players_globals;

		// name: "game engine globals"
		game_engine_globals* game_engine_globals;

		// name: "local game engine globals"
		local_game_engine_globals* local_game_engine_globals;

		// name: "game time globals"
		game_time_globals_definition* game_time_globals;

		// name: "breakable surface breakable_surface_globals"
		s_breakable_surface_globals* breakable_surface_globals;

		//  name: "breakable surface set broken events"
		DataArray<breakable_surface_set_broken_event_datum>* g_breakable_surface_set_broken_event_data;

		// name: "player mapping globals"
		s_player_mapping_globals* player_mapping_globals;

		// name: "director globals"
		s_director_globals* director_globals;

		// name: "director scripting"
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
		DataArray<effect_datum>* effect_data;

		//  name: "effect event"
		DataArray<effect_event_datum>* event_data;

		//  name: "effect location"
		DataArray<effect_location_datum>* effect_location_data;

		// name: "effect counts"
		s_effect_counts* g_effect_counts;

		//  name: "effect geometry sample"
		DataArray<effect_geometry_sample_datum>* effect_geometry_sample_data;

		// name: "effect messaging queue"
		effect_messaging_queue* g_effect_message_queue;

		// name: "effect lightprobes"
		effect_lightprobes* effect_lightprobe_data;

		// name: "havok gamestate"
		s_havok_gamestate* g_havok_game_state;

		// from assert
		long havok_style_fpu_exceptions_count;

		// name: "player control globals"
		s_player_control_globals* player_control_globals;

		// name: "player control globals deterministic"
		s_player_control_globals_deterministic* player_control_globals_deterministic;

		//  name: "object looping sounds"
		DataArray<game_looping_sound_datum>* game_looping_sound_data;

		// name: "game sound globals"
		s_game_sound_globals* game_sound_globals;

		// name: "game sound scripted impulses"
		s_game_sound_impulse_datum* game_sound_scripted_impulses;

		// name: "s_structure_seam_globals"
		s_structure_seam_globals* g_structure_seam_globals;

		// name: "visibility active portals"
		visibility_active_portals* visibility_active_portals;

		// name: "campaign meta-game globals"
		s_campaign_metagame_globals* g_campaign_metagame_globals;

		// name: "observer gamestate globals"
		s_observer_gamestate_globals* observer_gamestate_globals;

		// name: "observer globals"
		s_observer_globals* g_observer_globals;

		// name: "rumble"
		rumble_global_data* rumble_globals;

		// name: "bink game state"
		s_bink_shared_game_state* bink_game_state;

		char* __unknownF4;

		struct s_font_cache_globals* g_font_cache_globals;

		// name: "sound classes"
		sound_class_datum* sound_class_data;

		// name: "game allegiance globals"
		s_game_allegiance_globals* game_allegiance_globals;

		atmosphere_fog_globals* atmosphere_fog_globals; // screen_effect?

		// name: "soft surface globals"
		s_scenario_soft_ceilings_globals* g_scenario_soft_ceilings_globals;

		// name: "game sound player effects globals"
		s_game_sound_player_effects_globals* g_game_sound_player_effects_globals;


		//  name: "havok proxies"
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

		cinematic_new_globals* cinematic_new_globals;
		cinematic_globals* cinematic_globals;
		cinematic_light_globals* cinematic_light_globals;
		physics_constants* physics_constants;
		recorded_animations* recorded_animations;
		game_save_globals* game_save_globals;
		Blam::DataArray<s_rasterizer_screen_effect>* rasterizer_screen_effects;
		player_effects* player_effects;
		scenario_interpolator_globals* scenario_interpolator_globals;
		survival_mode_globals* survival_mode_globals;
		player_training_globals* player_training_globals;
		scenario_kill_trigger_volume_state* scenario_kill_trigger_volume_state;
		deterministic_game_sound_globals* deterministic_game_sound_globals;
		Blam::DataArray<s_decal_system_datum>* decal_system;
		decal_counts* decal_counts;
		decal* decal;
		decal_messaging_queue* decal_messaging_queue;
		impact_globals* impact_globals;
		impacts* impacts;
		impact_arrays* impact_arrays;
		object_list_header* object_list_header;
		list_object* list_object;
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
		user_widget* user_widget_0;
		user_widget* user_widget_1;
		user_widget* user_widget_2;
		user_widget* user_widget_3;
		first_person_orientations* first_person_orientations;
		first_person_weapons* first_person_weapons;
		cortana_globals* cortana_globals;
		campaign_objectives* campaign_objectives;
		DataArray<Blam::Objects::ObjectHeader>* object_header;
		object_globals* object_globals;
		objects_memory_pool* objects_memory_pool;
		object_name_list* object_name_list;
		object_messaging_queue* object_messaging_queue;
		char* collideable_object;
		damage_globals* damage_globals;

		char* __unknown464;

		char* noncollideable_object;

		char* __unknown46C;
		char* __unknown470;

		object_render_data* object_render_data;
		char* damage;
		object_placement* object_placement;
		device_groups* device_groups;
		object_scripting* object_scripting;
		object_broadphase* object_broadphase;
		object_early_movers* object_early_movers;
		object_schedule_globals* object_schedule_globals;
		object_activation_regions* object_activation_regions;
		lights* lights;
		lights_globals* lights_globals;
		char* light_data_reference;
		char* light_cluster_reference;
		char* light_first_data;
		nondeterministic_render_light_data* nondeterministic_render_light_data;
		widget* widget;
		recycling_volumes* recycling_volumes;
		recycling_group* recycling_group;
		muffin* muffin;
		leaf_system* leaf_system;
		antenna* antenna;
		cloth* cloth;

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
		vision_mode* vision_mode;

		char* __unknown580;
	};
}