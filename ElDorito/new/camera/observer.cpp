#include "observer.hpp"

#include <Blam/Memory/TlsData.hpp>

namespace blam
{
	s_observer* observer_get(long user_index)
	{
		using namespace Blam::Memory;

		s_observer_globals* g_observer_globals = GetTls()->g_observer_globals;
		if (!g_observer_globals)
			return nullptr;

		return &g_observer_globals->observers[user_index];
	}
}