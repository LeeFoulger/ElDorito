#include "observer.hpp"

#include <ElDorito.hpp>

namespace blam
{
	s_observer* observer_get(long user_index)
	{
		s_observer_globals* observer_globals = *(s_observer_globals**)ElDorito::GetMainTls(0xE8);
		if (!observer_globals)
			return nullptr;

		return &observer_globals->observers[user_index];
	}
}