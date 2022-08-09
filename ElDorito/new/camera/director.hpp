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

//#include "director.hpp"
//#include "game_director.hpp"
//#include "observer_director.hpp"
//#include "saved_film_director.hpp"
//#include "editor_director.hpp"

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

		// c_scripted_camera
		_director_perspective_2,

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

			char camera_data[0x4C];
		};

		s_observer_command m_observer_command;
		real m_transition_time;
		long m_user_index;
		long m_player_index;
		bool __unknown148;
		e_camera_mode m_camera_mode;
		long __unknown150;
		char __data[12];

		long get_perspective();
		bool set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update);

		inline bool set_camera_mode(e_camera_mode camera_mode, real transition_time)
		{
			return set_camera_mode_internal(camera_mode, transition_time, false);
		}

		inline c_camera* get_camera()
		{
			return &m_camera;
		}

		inline bool in_free_camera_mode()
		{
			e_camera_mode camera_mode = m_camera.get_type();
			if (camera_mode == _camera_mode_flying || camera_mode == _camera_mode_scripted)
				return true;

			if (camera_mode == _camera_mode_authored)
				return m_camera.get_target() == -1;

			return false;
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
		real __unknown5B0;
		real __unknown5B4;
		dword __unknown5B8;
		char __data5BC[4];
	};
	static_assert(sizeof(s_director_globals) == 0x5C0);

	extern s_director_globals* director_globals_get();
	extern c_director* director_get(long user_index);
	extern s_director_info* director_get_info(long user_index);
	extern long director_get_perspective(long user_index);
}