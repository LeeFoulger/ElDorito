#pragma once

#include "director.hpp"

namespace blam
{
	struct c_game_director : public c_director
	{
		byte unused[0x14];
	};
	static_assert(sizeof(c_game_director) == 0x160);
}