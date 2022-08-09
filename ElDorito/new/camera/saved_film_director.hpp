#pragma once

#include "observer_director.hpp"

namespace blam
{
	struct c_saved_film_director : public c_observer_director
	{
		bool __unknown158;
		bool __unknown159;
	};
	static_assert(sizeof(c_saved_film_director) == 0x160);
}