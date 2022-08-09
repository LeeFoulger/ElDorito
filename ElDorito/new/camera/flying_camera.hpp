#pragma once

#include "camera.hpp"

namespace blam
{
	struct c_flying_camera : public c_camera
	{
		enum e_flags
		{
			_zoomed_bit = 0,            // not the actual name
			_lock_in_xy_plane_bit = 1,
			_collision_bit = 2,         // default
			_orientation_bit = 3,       // default
			_movement_bit = 4           // default
		};

		real_point3d m_position;
		real_euler_angles2d m_facing;
		real m_roll;
		real __unknown28;
		real __unknown2C;
		bool __unknown30;
		real __unknown34;

		dword_flags m_flags;

		inline void set_lock_in_xy_plane(bool value)
		{
			if (value)
				m_flags |= (1 << _lock_in_xy_plane_bit);
			else
				m_flags |= ~(1 << _lock_in_xy_plane_bit);
		}

		inline void set_collision(bool value)
		{
			if (value)
				m_flags |= (1 << _collision_bit);
			else
				m_flags |= ~(1 << _collision_bit);
		}

		inline void enable_orientation(bool value)
		{
			if (value)
				m_flags |= (1 << _orientation_bit);
			else
				m_flags |= ~(1 << _orientation_bit);
		}

		inline void enable_movement(bool value)
		{
			if (value)
				m_flags |= (1 << _movement_bit);
			else
				m_flags |= ~(1 << _movement_bit);
		}
	};
	static_assert(sizeof(c_flying_camera) == 0x3C);
}
