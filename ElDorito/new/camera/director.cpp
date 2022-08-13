#include "director.hpp"

#include "../game/game_options.hpp"

#include "game_director.hpp"
#include "saved_film_director.hpp"
#include "observer_director.hpp"
#include "debug_director.hpp"
#include "editor_director.hpp"

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace
{
	long(__cdecl* dead_or_alive_unit_from_user)(long) = reinterpret_cast<decltype(dead_or_alive_unit_from_user)>(0x005916F0);
	void(__cdecl* first_person_weapon_perspective_changed)(long) = reinterpret_cast<decltype(first_person_weapon_perspective_changed)>(0xA9C550);
	long(__cdecl* players_first_active_user)(void) = reinterpret_cast<decltype(players_first_active_user)>(0x00589A30);

	using namespace blam;

	void(__thiscall* game_director_ctor)(c_director*, long) = reinterpret_cast<decltype(game_director_ctor)>(0x007215C0);
	void(__thiscall* saved_film_director_ctor)(c_director*, long) = reinterpret_cast<decltype(saved_film_director_ctor)>(0x007276C0);
	void(__thiscall* observer_director_ctor)(c_director*, long) = reinterpret_cast<decltype(observer_director_ctor)>(0x00726430);
	void(__thiscall* debug_director_ctor)(c_director*, long) = reinterpret_cast<decltype(debug_director_ctor)>(0x007260D0);
	void(__thiscall* editor_director_ctor)(c_director*, long) = reinterpret_cast<decltype(editor_director_ctor)>(0x00727EA0);

	void(__thiscall* following_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(following_camera_ctor)>(0x00728630);
	void(__thiscall* orbiting_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(orbiting_camera_ctor)>(0x0072A5E0);
	void(__thiscall* flying_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(flying_camera_ctor)>(0x0072ACA0);
	void(__thiscall* first_person_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(first_person_camera_ctor)>(0x0065F410);
	void(__thiscall* dead_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(dead_camera_ctor)>(0x00729E60);
	void(__thiscall* static_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(static_camera_ctor)>(0x0072F170);
	void(__thiscall* scripted_camera_ctor)(c_camera*) = reinterpret_cast<decltype(scripted_camera_ctor)>(0x0072BEB0);
	void(__thiscall* authored_camera_ctor)(c_camera*, long) = reinterpret_cast<decltype(authored_camera_ctor)>(0x0072F2E0);
}

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

	e_director_mode director_mode_from_string(const char* str)
	{
		e_director_mode director_mode = e_director_mode(-1);
		for (long i = _camera_mode_following; i < k_number_of_director_modes; i++)
		{
			if (strcmp(str, k_director_mode_names[i]) != 0)
				continue;

			director_mode = e_director_mode(i);
		}

		return director_mode;
	}

	inline s_director_globals* director_globals_get()
	{
		using namespace Blam::Memory;
		s_thread_local_storage* tls = ElDorito::GetMainTls();

		s_director_globals* director_globals = tls->director_globals;
		if (!tls || !director_globals || !director_globals->directors[0][0])
			return nullptr;

		return director_globals;
	}

	long c_director::get_perspective()
	{
		if (!game_in_progress())
			return 3;
		long director_perspective = get_camera()->get_perspective();
		if (!director_perspective)
			director_perspective = m_transition_time > 0.0;
		if (game_is_ui_shell())
			return 3;

		return director_perspective;
	}

	bool c_director::set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update)
	{
		if (!can_use_camera_mode(camera_mode))
			return false;

		c_camera* camera = get_camera();
		e_camera_mode current_camera_mode = camera->get_type();

		bool result = camera_mode != current_camera_mode;
		if (result || force_update)
		{
			switch (camera_mode)
			{
			case _camera_mode_following:
				following_camera_ctor(camera, dead_or_alive_unit_from_user(m_user_index));
				break;
			case _camera_mode_orbiting:
				orbiting_camera_ctor(camera, dead_or_alive_unit_from_user(m_user_index));
				break;
			case _camera_mode_flying:
				flying_camera_ctor(camera, m_user_index);
				break;
			case _camera_mode_first_person:
				first_person_camera_ctor(camera, dead_or_alive_unit_from_user(m_user_index));
				break;
			case _camera_mode_dead:
				dead_camera_ctor(camera, m_user_index);
				break;
			case _camera_mode_static:
				static_camera_ctor(camera, m_user_index);
				break;
			case _camera_mode_scripted:
				scripted_camera_ctor(camera);
				break;
			case _camera_mode_authored:
				authored_camera_ctor(camera, m_user_index);
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

	c_director* director_get(long user_index)
	{
		if (!director_globals_get())
			return nullptr;

		return (c_director*)&director_globals_get()->directors[user_index];
	}

	s_director_info* director_get_info(long user_index)
	{
		if (!director_globals_get())
			return nullptr;

		return &director_globals_get()->infos[user_index];
	}

	long director_get_perspective(long user_index)
	{
		c_director* director = director_get(user_index);
		if (!director)
			return 0;

		return director->get_perspective();
	}

	void director_set_mode(long user_index, e_director_mode director_mode)
	{
		c_director* director = director_get(user_index);

		switch (director_mode)
		{
		case _director_mode_game:
			game_director_ctor(director, user_index);
			break;
		case _director_mode_saved_film:
			saved_film_director_ctor(director, user_index);
			break;
		case _director_mode_observer:
			observer_director_ctor(director, user_index);
			break;
		case _director_mode_debug:
			debug_director_ctor(director, user_index);
			break;
		case _director_mode_editor:
			editor_director_ctor(director, user_index);
			break;
		}

		director_get_info(user_index)->director_mode = director_mode;
	}

	bool director_get_camera_third_person(long user_index)
	{
		return director_get(user_index)->get_camera()->get_type() == _camera_mode_orbiting;
	}

	bool director_in_scripted_camera(void)
	{
		using namespace Blam::Memory;
		s_thread_local_storage* tls = ElDorito::GetMainTls();

		return tls->director_camera_scripted;
	}
}