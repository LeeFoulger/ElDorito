#pragma once

#include "camera.hpp"

namespace blam
{
	struct c_orbiting_camera : public c_camera
	{
		real_euler_angles2d m_facing;
		real m_distance;
		real m_z_offset;
		word __unknown20;
		bool __unknown22;
	};
	static_assert(sizeof(c_orbiting_camera) == 0x24);
}
