#include "director.hpp"

#include <ElDorito.hpp>

namespace blam
{
	const char* k_director_mode_names[k_number_of_director_modes]
	{
		"game",
		"saved_film",
		"observer",
		"debug",
		"unused",
		"editor"
	};
	const char* director_mode_get_name(e_director_mode director_mode)
	{
		if (director_mode < _director_mode_game || director_mode >= k_number_of_director_modes)
			return "<invalid 'director_mode'>";

		return k_director_mode_names[director_mode];
	}

	s_director_globals* director_globals_get()
	{
		s_director_globals* director_globals = *(s_director_globals**)ElDorito::GetMainTls(0x60);
		if (!director_globals)
			return nullptr;

		return director_globals;
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
}