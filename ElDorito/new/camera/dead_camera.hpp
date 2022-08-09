#pragma once

#include "camera.hpp"

namespace blam
{
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
}
