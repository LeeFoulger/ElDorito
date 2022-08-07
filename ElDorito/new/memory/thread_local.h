#pragma once

#include <ElDorito.hpp>
#include "cseries\cseries.hpp"
#include "memory\data.hpp"

namespace blam
{
	struct s_cluster_reference
	{
		unsigned char bsp_index;
		unsigned char cluster_index;
	};
	static_assert(sizeof(s_cluster_reference) == 0x2);

	struct s_location
	{
		s_cluster_reference cluster_reference;
		unsigned short __unknown2;
	};
	static_assert(sizeof(s_location) == 0x4);

	enum e_director_mode : long
	{
		_director_mode_game = 0,
		_director_mode_saved_film,
		_director_mode_observer,
		_director_mode_debug,
		_director_mode_unused,
		_director_mode_editor,

		k_number_of_director_modes
	};

	enum e_director_perspective : long
	{
		_director_perspective_first_person = 0,

		// c_following_camera, c_dead_camera, c_orbiting_camera
		_director_perspective_1,

		// c_scripted_camera
		_director_perspective_2,

		// c_null_camera, (c_authored_camera default)
		_director_perspective_3,

		k_number_of_director_perspectives,
	};

	enum e_camera_mode : unsigned long
	{
		_camera_mode_following = 0,
		_camera_mode_orbiting,
		_camera_mode_flying,
		_camera_mode_first_person,
		_camera_mode_dead,
		_camera_mode_static,
		_camera_mode_scripted,
		_camera_mode_authored,

		k_number_of_camera_modes,
		k_camera_mode_null = 0xFFFFFFFF,
	};

	struct s_observer_command
	{
		dword_flags flags;
		real_point3d position;
		real_vector3d focus_offset;
		real_point2d look_shift;
		real focus_distance;
		real field_of_view;
		real_vector3d forward;
		real_vector3d up;
		real_vector3d velocities;
		real_matrix4x3 focus_space;
		dword __unknown84;
		real_point3d center;
		real timer;
		char __data98[40];
		real __unknownC0[6];
		char __dataD8[20];
	};
	static_assert(sizeof(s_observer_command) == 0xEC);

	struct s_observer_result
	{
		real_point3d focus_point;
		s_location location;
		float __unknown10[3];
		float __unknown1C[3];
		real_vector3d forward;
		real_vector3d up;
		real horizontal_field_of_view;
		char __data44[36];
		real vertical_field_of_view;
		real __unknown60;
	};

	struct s_observer
	{
		dword header_signature;
		s_observer_command* pending_command;
		s_observer_command command;
		bool updated_for_frame;
		bool __unknownF5;
		bool __unknownF6;
		bool __unknownF7;
		float __unknownF8;
		char __dataFC[16];
		s_observer_result result;
		real_point3d positions_focus_position;
		real_vector3d positions_focus_offset;
		real_point2d positions_look_shift;
		real positions_focus_distance;
		real horizontal_field_of_view;
		real_vector3d positions_forward;
		real_vector3d positions_up;
		real_matrix4x3 focus_space;
		real_vector3d velocities_v;
		real_vector3d velocities_forward;
		char __data208[16];
		real_vector3d velocities_r;
		real_vector3d accelerations_a;
		real_vector3d accelerations_r;
		char __data244[16];
		real_vector3d accelerations_forward;
		char __data258[364];
		unsigned long trailer_signature;
	};
	static_assert(sizeof(s_observer) == 0x3C8);

	struct s_director_globals;
	s_director_globals* director_globals_get()
	{
		s_director_globals* director_globals = *(s_director_globals**)ElDorito::GetMainTls(0x60);
		if (!director_globals)
			return nullptr;

		return director_globals;
	}

	struct c_camera
	{
		virtual e_camera_mode get_type();
		virtual e_director_perspective get_perspective();
		virtual void update(long, real, s_observer_command*);
		virtual long get_target();
		virtual void set_target(long);
		virtual void set_position(real_point3d const*);
		virtual void set_forward(real_vector3d const*);
		virtual void set_roll(real);
		virtual void enable_orientation(bool);
		virtual void enable_movement(bool);
		virtual void enable_roll(bool);
		virtual void handle_deleted_player(long);
		virtual void handle_deleted_object(long);
		virtual real get_unknown(); // c_flying_camera, c_static_camera, c_scripted_camera

		datum_index m_object_index;
		dword __unknown8;
		dword __unknownC;
	};
	static_assert(sizeof(c_camera) == 0x10);

	struct c_null_camera : public c_camera
	{
	};
	static_assert(sizeof(c_null_camera) == 0x10);

#pragma pack(push, 2)
	struct c_following_camera : public c_camera
	{
		dword __unknown10;
		dword __unknown14;
		real __unknown18;
		real_vector3d __vector1C;
		datum_index m_target_object_index;
		word __unknown2C;
		dword __unknown2E;
		word __unknown32;
	};
	static_assert(sizeof(c_following_camera) == 0x34);
#pragma pack(pop)

	struct c_orbiting_camera : public c_camera
	{
		real_euler_angles2d m_facing;
		real m_minimum_distance;
		real m_z_offset;
		word __unknown20;
		bool __unknown22;
	};
	static_assert(sizeof(c_orbiting_camera) == 0x24);

	struct c_flying_camera : public c_camera
	{
		enum e_flags
		{
			_zoomed_bit = 0,
			_orientation_bit = 3,
			_movement_bit = 4
		};

		real_point3d m_position;
		real_euler_angles2d m_facing;
		real m_roll;
		real __unknown28;
		real __unknown2C;
		bool __unknown30;
		real __unknown34;
		dword_flags m_zoomed_bit : 1;
		dword_flags m_flag_bit1 : 1;
		dword_flags m_flag_bit2 : 1;
		dword_flags m_orientation_enabled : 1;
		dword_flags m_movement_enabled : 1;
		dword_flags m_flag_bits5_31 : 3;
	};
	static_assert(sizeof(c_flying_camera) == 0x3C);

	struct c_first_person_camera : public c_camera
	{
		real m_field_of_view;
		real_euler_angles2d m_facing;
		bool __unknown1C;
	};
	static_assert(sizeof(c_first_person_camera) == 0x20);

	struct c_dead_camera : public c_camera
	{
		real_point3d m_position;
		real_euler_angles2d m_facing;
		real m_focus_distance;
		real m_field_of_view;
		real __unknown2C;
		datum_index m_target_player_index;
		datum_index m_target_object_index;
		bool __unknown38;
		byte m_user_index;
		char __data[18];
	};
	static_assert(sizeof(c_dead_camera) == 0x4C);

	struct c_static_camera : public c_camera
	{
		real_point3d m_position;
		real_vector3d m_forward;
		real m_field_of_view;
		real __unknown2C;
		dword __unknown30;
	};
	static_assert(sizeof(c_static_camera) == 0x34);

	struct c_scripted_camera : public c_camera
	{
	};
	static_assert(sizeof(c_scripted_camera) == 0x10);

	struct c_authored_camera : public c_camera
	{
		bool __unknown10;
		bool __unknown11;
		c_first_person_camera m_first_person_camera;
		real_point3d m_position;
		real_vector3d m_forward;
	};
	static_assert(sizeof(c_authored_camera) == 0x4C);

	struct c_director
	{
		virtual e_director_mode get_type();
		virtual void update(real);
		virtual bool should_draw_hud();
		virtual bool should_draw_hud_saved_film();
		virtual bool inhibits_facing();
		virtual bool inhibits_input();
		virtual void handle_deleted_player(long);
		virtual void handle_deleted_object(long);
		virtual bool can_use_camera_mode(e_camera_mode);
		//virtual void select_fallback_target(); // c_observer_director, c_saved_film_director

		union
		{
			c_camera m_camera;
			c_null_camera m_null;
			c_following_camera m_following;
			c_orbiting_camera m_orbiting;
			c_flying_camera m_flying;
			c_first_person_camera m_first_person;
			c_dead_camera m_dead;
			c_static_camera m_static;
			c_scripted_camera m_scripted;
			c_authored_camera m_authored;
		};

		s_observer_command m_observer_command;
		real m_transition_time;
		long m_user_index;
		long m_player_index;
		char __data[0x18];

		long get_perspective();
		bool set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update);

		inline bool set_camera_mode(e_camera_mode camera_mode, real transition_time)
		{
			return set_camera_mode_internal(camera_mode, transition_time, false);
		}
	};
	static_assert(sizeof(c_director) == 0x160);

	struct s_director_info
	{
		e_director_mode director_mode;
		long director_perspective; // e_director_perspective
		e_camera_mode camera_mode;
	};
	static_assert(sizeof(s_director_info) == 0xC);

	struct s_director_globals
	{
		c_director directors[4];
		s_director_info infos[4];
		real __unknown5B0[4];
	};
	static_assert(sizeof(s_director_globals) == 0x5C0);

	struct s_observer_globals
	{
		real __unknown0;
		s_observer observers[4];
		char __dataF24[4];
	};
	static_assert(sizeof(s_observer_globals) == 0xF28);

	const char* k_camera_mode_names[k_number_of_camera_modes]
	{
		"following",
		"orbiting",
		"flying",
		"first_person",
		"dead",
		"static",
		"scripted",
		"authored",
	};

	inline e_camera_mode camera_mode_from_string(const char* str)
	{
		e_camera_mode camera_mode = k_camera_mode_null;
		for (long i = _camera_mode_following; i < k_number_of_camera_modes; i++)
		{
			if (strcmp(str, k_camera_mode_names[i]) != 0)
				continue;

			camera_mode = e_camera_mode(i);
		}

		return camera_mode;
	}

	c_director* director_get(long user_index)
	{
		s_director_globals* director_globals = *(s_director_globals**)ElDorito::GetMainTls(0x60);
		if (!director_globals)
			return nullptr;

		return &director_globals->directors[user_index];
	}

	s_director_info* director_get_info(long user_index)
	{
		s_director_globals* director_globals = *(s_director_globals**)ElDorito::GetMainTls(0x60);
		if (!director_globals)
			return nullptr;

		return &director_globals->infos[user_index];
	}

	s_observer* observer_get(long user_index)
	{
		s_observer_globals* observer_globals = *(s_observer_globals**)ElDorito::GetMainTls(0xE8);
		if (!observer_globals)
			return nullptr;

		return &observer_globals->observers[user_index];
	}

	long director_get_perspective(long user_index)
	{
		c_director* director = director_get(user_index);
		if (!director)
			return 0;

		return director->get_perspective();
	}

	long c_director::get_perspective()
	{
		static bool(__cdecl * game_in_progress)() = reinterpret_cast<decltype(game_in_progress)>(0x005314B0);
		static bool(__cdecl * game_is_ui_shell)() = reinterpret_cast<decltype(game_is_ui_shell)>(0x00531E90);

		if (!game_in_progress())
			return 3;
		long director_perspective = m_camera.get_perspective();
		if (!director_perspective)
			director_perspective = m_transition_time > 0.0;
		if (game_is_ui_shell())
			return 3;

		return director_perspective;
	}

	bool c_director::set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update)
	{
		static void(__thiscall * following_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(following_camera_ctor)>(0x00728630);
		static void(__thiscall * orbiting_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(orbiting_camera_ctor)>(0x0072A5E0);
		static void(__thiscall * flying_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(flying_camera_ctor)>(0x0072ACA0);
		static void(__thiscall * first_person_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(first_person_camera_ctor)>(0x0065F410);
		static void(__thiscall * dead_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(dead_camera_ctor)>(0x00729E60);
		static void(__thiscall * static_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(static_camera_ctor)>(0x0072F170);
		static void(__thiscall * scripted_camera_ctor)(c_camera*) = reinterpret_cast<decltype(scripted_camera_ctor)>(0x0072BEB0);
		static void(__thiscall * authored_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(authored_camera_ctor)>(0x0072F2E0);

		static long(__cdecl * dead_or_alive_unit_from_user)(long) = reinterpret_cast<decltype(dead_or_alive_unit_from_user)>(0x005916F0);
		static void(__cdecl * first_person_weapon_perspective_changed)(long) = reinterpret_cast<decltype(first_person_weapon_perspective_changed)>(0xA9C550);

		if (!can_use_camera_mode(camera_mode))
			return false;

		e_camera_mode current_camera_mode = m_camera.get_type();
		bool result = camera_mode != current_camera_mode;
		if (result || force_update)
		{
			switch (camera_mode)
			{
			case _camera_mode_following:
				following_camera_ctor(&m_camera, dead_or_alive_unit_from_user(m_user_index));
				break;
			case _camera_mode_orbiting:
				orbiting_camera_ctor(&m_camera, dead_or_alive_unit_from_user(m_user_index));
				break;
			case _camera_mode_flying:
				flying_camera_ctor(&m_camera, m_user_index);
				break;
			case _camera_mode_first_person:
				first_person_camera_ctor(&m_camera, dead_or_alive_unit_from_user(m_user_index));
				break;
			case _camera_mode_dead:
				dead_camera_ctor(&m_camera, m_user_index);
				break;
			case _camera_mode_static:
				static_camera_ctor(&m_camera, m_user_index);
				break;
			case _camera_mode_scripted:
				scripted_camera_ctor(&m_camera);
				break;
			case _camera_mode_authored:
				authored_camera_ctor(&m_camera, m_user_index);
				break;
			}
			m_transition_time = transition_time;
		}

		long director_perspective = get_perspective();
		s_director_globals* director_globals = director_globals_get();
		if (director_globals->infos[m_user_index].director_perspective != director_perspective ||
			director_globals->infos[m_user_index].camera_mode != camera_mode)
		{
			director_globals->infos[m_user_index].director_perspective = director_perspective;
			director_globals->infos[m_user_index].camera_mode = camera_mode;
			first_person_weapon_perspective_changed(m_user_index);
		}

		return result || force_update;
	}

	struct s_player_control_non_deterministic_input_user_state
	{
		char __data0[6];
		bool player_input_locked;
		char __data7[0x30-7];
	};
	static_assert(sizeof(s_player_control_non_deterministic_input_user_state) == 0x30);

	struct s_player_interaction
	{
		word interaction_type;
		word interaction_seat_index;
		dword interaction_object;
	};
	static_assert(sizeof(s_player_interaction) == 0x8);

	struct s_player_action_context
	{
		s_player_interaction interaction;
		dword melee_target_unit;
	};
	static_assert(sizeof(s_player_action_context) == 0xC);

	struct s_aim_assist_targeting_result
	{
		bool __unknown0;
		dword target_player_index;
		dword target_object_index;
		dword model_target;
		real primary_autoaim_level;
		real secondary_autoaim_level;
		real_vector3d lead_vector;
		dword_flags flags;
	};
	static_assert(sizeof(s_aim_assist_targeting_result) == 0x28);

	struct s_player_control_internal_state
	{
		dword control_flags;
		dword action_flags;
		real_euler_angles2d desired_angles;
		real_point2d throttle;
		real primary_trigger;
		real secondary_trigger;
		word weapon_set_identifier;
		byte primary_weapon_index;
		byte secondary_weapon_index;
		word grenade_index;
		word zoom_level;
		s_player_action_context action_context;
		s_aim_assist_targeting_result targeting;
		bool map_editor_rotation_valid;
		bool map_editor_player_locked_for_manipulation;
		char __data66[2];
		real_euler_angles2d map_editor_rotation;
		word_flags map_editor_flags;
		char __data6A[2];
	};
	static_assert(sizeof(s_player_control_internal_state) == 0x6C);

	struct s_player_control_state
	{
		dword unit_index;
		s_player_control_internal_state internal_state;
	};
	static_assert(sizeof(s_player_control_state) == 0x70);

	struct s_player_control
	{
		s_player_control_state state;
		char __data70[120];
		real_point3d __positionE8;
		char __dataF4[4];
	};
	static_assert(sizeof(s_player_control) == 0xF8);

	struct s_player_control_globals
	{
		s_player_control_non_deterministic_input_user_state input_user_states[16];
		s_player_control controls[4];
		s_player_control_state control_states[4];
		dword __unknown8A0;
		dword __unknown8A4;
		bool machinima_camera_enabled;
		bool machinima_camera_use_old_controls;
		bool machinima_camera_debug;
		char __data8AB[5];
	};
	static_assert(sizeof(s_player_control_globals) == 0x8B0);
}
