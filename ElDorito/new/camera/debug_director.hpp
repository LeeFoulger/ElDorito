#pragma once

#include "director.hpp"

namespace blam
{
	struct c_debug_director : public c_director
	{
		long __unknown14C;

		// get_camera()->get_type() == _camera_mode_flying
		// biped_control_mode || !editor_input_inhibited()
		bool __unknown150;

		// flying camera (0)
		// static camera (1)
		bool biped_control_mode;

		byte pad[2];
		byte unused[0xC];
	};
	static_assert(sizeof(c_debug_director) == 0x160);
}