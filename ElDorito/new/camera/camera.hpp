#pragma once

#include "../cseries/cseries.hpp"
#include "../memory/data.hpp"

namespace blam
{
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

	extern const char* camera_mode_get_name(long camera_mode);

	struct c_camera
	{
		virtual e_camera_mode get_type();
		virtual long get_perspective();
		virtual void update(long, real, void*);
		virtual long get_target();
		virtual void set_target(long);
		virtual void set_position(real_point3d const*);
		virtual void set_forward(real_vector3d const*);
		virtual void set_roll(real);
		virtual void enable_orientation(bool);
		virtual void enable_movement(bool);
		virtual void enable_roll(bool);
		virtual void handle_deleted_player(long);
		virtual void handle_deleted_object(long);
		virtual real get_unknown(); // c_flying_camera, c_static_camera, c_scripted_camera

		enum e_flags
		{
			_next_move_instantly_bit = 0
		};

		datum_index m_object_index;
		dword_flags m_flags;
		dword __unknownC;

		void set_next_move_instantly();
	};
	static_assert(sizeof(c_camera) == 0x10);

	struct c_null_camera : public c_camera
	{
	};
	static_assert(sizeof(c_null_camera) == 0x10);

#pragma pack(push, 2)
	struct c_following_camera : public c_camera
	{
		dword __unknown10;
		dword __unknown14;
		real __unknown18;
		real_vector3d __vector1C;
		datum_index m_target_object_index;
		word __unknown2C;
		dword __unknown2E;
		word __unknown32;
	};
	static_assert(sizeof(c_following_camera) == 0x34);
#pragma pack(pop)

	struct c_orbiting_camera : public c_camera
	{
		real_euler_angles2d m_facing;
		real m_distance;
		real m_z_offset;
		word __unknown20;
		bool __unknown22;
	};
	static_assert(sizeof(c_orbiting_camera) == 0x24);

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

	struct c_first_person_camera : public c_camera
	{
		real m_field_of_view;
		real_euler_angles2d m_facing;
		bool __unknown1C;
	};
	static_assert(sizeof(c_first_person_camera) == 0x20);

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

	struct c_authored_camera : public c_camera
	{
		bool __unknown10;
		bool __unknown11;
		c_first_person_camera m_first_person_camera;
		real_point3d m_position;
		real_vector3d m_forward;
	};
	static_assert(sizeof(c_authored_camera) == 0x4C);

	extern e_camera_mode camera_mode_from_string(const char* str);
}
