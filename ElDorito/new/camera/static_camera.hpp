#pragma once

#include "camera.hpp"

namespace blam
{
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
}