#pragma once

#include "../cseries/cseries.hpp"
#include "../memory/data.hpp"

#include "observer.hpp"

#include "camera.hpp"
#include "following_camera.hpp"
#include "orbiting_camera.hpp"
#include "flying_camera.hpp"
#include "first_person_camera.hpp"
#include "dead_camera.hpp"
#include "static_camera.hpp"

namespace blam
{
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

	extern const char* director_mode_get_name(e_director_mode director_mode);

	enum e_director_perspective : long
	{
		_director_perspective_first_person = 0,

		// c_following_camera, c_dead_camera, c_orbiting_camera
		_director_perspective_1,

		_director_perspective_scripted,

		// c_null_camera, (c_authored_camera default)
		_director_perspective_3,

		k_number_of_director_perspectives,
	};

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

		char m_camera[0x4C];

		s_observer_command m_observer_command;
		real m_transition_time;
		long m_user_index;
		long m_output_user_index;
		bool __unknown148;

		byte pad[3];

		long get_perspective();
		bool set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update);

		inline bool set_camera_mode(e_camera_mode camera_mode, real transition_time)
		{
			return set_camera_mode_internal(camera_mode, transition_time, false);
		}

		template<typename t_type = c_camera>
		inline t_type* get_camera()
		{
			if (!m_camera[0])
				return nullptr;

			return (t_type*)&m_camera;
		}

		inline bool in_free_camera_mode()
		{
			if (!m_camera[0])
				return false;

			e_camera_mode camera_mode = get_camera()->get_type();
			if (camera_mode == _camera_mode_flying || camera_mode == _camera_mode_scripted)
				return true;

			if (camera_mode == _camera_mode_authored)
				return get_camera()->get_target() == -1;

			return false;
		}
	};
	static_assert(sizeof(c_director) == 0x14C);

	struct s_director_info
	{
		e_director_mode director_mode;
		long director_perspective; // e_director_perspective
		e_camera_mode camera_mode;
	};
	static_assert(sizeof(s_director_info) == 0xC);

	struct s_director_globals
	{
		// c_static_array<unsigned char [352],4> directors;
		unsigned char directors[4][0x160];

		s_director_info infos[4];
		real __unknown5B0;
		real __unknown5B4;
		dword __unknown5B8;
		char __data5BC[4];
	};
	static_assert(sizeof(s_director_globals) == 0x5C0);

	extern c_director* director_get(long user_index);
	extern s_director_info* director_get_info(long user_index);
	extern long director_get_perspective(long user_index);
	extern void director_set_mode(long user_index, e_director_mode director_mode);
	extern bool director_get_camera_third_person(long);
	extern bool director_in_scripted_camera(void);
}