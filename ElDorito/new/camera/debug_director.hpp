#pragma once

#include "director.hpp"

namespace blam
{
	struct c_debug_director : public c_director
	{
		long __unknown14C;
		bool __unknown150;
		bool control_mode;

		byte pad[2];
		byte unused[0xC];
	};
	static_assert(sizeof(c_debug_director) == 0x160);
}