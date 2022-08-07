#pragma once

#include <ElDorito.hpp>
#include "cseries\cseries.hpp"

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

	struct c_camera;
	struct c_camera_vtbl
	{
		e_camera_mode(__thiscall* get_type)(c_camera*);
		e_director_perspective(__thiscall* get_perspective)(c_camera*);
		void(__thiscall* update)(c_camera*, long, real, s_observer_command*);
		long(__thiscall* get_target)(c_camera*);
		void(__thiscall* set_target)(c_camera*, long);
		void(__thiscall* set_position)(c_camera*, real_point3d*);
		void(__thiscall* set_forward)(c_camera*, real_vector3d*);
		void(__thiscall* set_roll)(c_camera*, real);
		void(__thiscall* enable_orientation)(c_camera*, bool);
		void(__thiscall* enable_movement)(c_camera*, bool);
		void(__thiscall* enable_roll)(c_camera*, bool);
		void(__thiscall* handle_deleted_player)(c_camera*, long);
		void(__thiscall* handle_deleted_object)(c_camera*, long);
	};

	struct c_camera
	{
		#pragma region c_camera::vftable
		c_camera_vtbl* vftable;

		e_camera_mode get_type()
		{
			return vftable->get_type(this);
		}
		e_director_perspective get_perspective()
		{
			return vftable->get_perspective(this);
		}
		void update(long a1, real a2, s_observer_command* result)
		{
			return vftable->update(this, a1, a2, result);
		}
		long get_target()
		{
			return vftable->get_target(this);
		}
		void set_target(long a1)
		{
			return vftable->set_target(this, a1);
		}
		void set_position(real_point3d* position)
		{
			return vftable->set_position(this, position);
		}
		void set_forward(real_vector3d* forward)
		{
			return vftable->set_forward(this, forward);
		}
		void set_roll(real roll)
		{
			return vftable->set_roll(this, roll);
		}
		void enable_orientation(bool enable)
		{
			return vftable->enable_orientation(this, enable);
		}
		void enable_movement(bool enable)
		{
			return vftable->enable_movement(this, enable);
		}
		void enable_roll(bool enable)
		{
			return vftable->enable_roll(this, enable);
		}
		void handle_deleted_player(long a1)
		{
			return vftable->handle_deleted_player(this, a1);
		}
		void handle_deleted_object(long a1)
		{
			return vftable->handle_deleted_object(this, a1);
		}
		#pragma endregion

		unsigned long m_object_index;
		unsigned long __unknown8;
		unsigned long __unknownC;

		void swap_vtable(unsigned long vftable_addr)
		{
			c_camera_vtbl* old_camera_vtable = vftable;
			vftable = reinterpret_cast<c_camera_vtbl*>(vftable_addr);
		}
	};
	static_assert(sizeof(c_camera) == 0x10);

	struct c_director;
	struct c_director_vtbl
	{
		e_director_mode(__thiscall* get_type)(c_director*);
		void(__thiscall* update)(c_director*, real);
		bool(__thiscall* should_draw_hud)(c_director*);
		bool(__thiscall* should_draw_hud_saved_film)(c_director*);
		bool(__thiscall* inhibits_facing)(c_director*);
		bool(__thiscall* inhibits_input)(c_director*);
		void(__fastcall* handle_deleted_player)(c_director*, long);
		void(__fastcall* handle_deleted_object)(c_director*, long);
		bool(__thiscall* can_use_camera_mode)(c_director*, e_camera_mode);
	};

	struct c_director
	{
		#pragma region c_director::vftable
		c_director_vtbl* vftable;

		e_director_mode get_type()
		{
			return vftable->get_type(this);
		}
		void update(real a1)
		{
			return vftable->update(this, a1);
		}
		bool should_draw_hud()
		{
			return vftable->should_draw_hud(this);
		}
		bool should_draw_hud_saved_film()
		{
			return vftable->should_draw_hud_saved_film(this);
		}
		bool inhibits_facing()
		{
			return vftable->inhibits_facing(this);
		}
		bool inhibits_input()
		{
			return vftable->inhibits_input(this);
		}
		void handle_deleted_player(long a1)
		{
			return vftable->handle_deleted_player(this, a1);
		}
		void handle_deleted_object(long a1)
		{
			return vftable->handle_deleted_object(this, a1);
		}
		bool can_use_camera_mode(e_camera_mode camera_mode)
		{
			return vftable->can_use_camera_mode(this, camera_mode);
		}
		#pragma endregion

		union
		{
			c_camera m_camera;
			char camera_data[0x4C];
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
