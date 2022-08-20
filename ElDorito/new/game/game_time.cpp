#include "game_time.hpp"

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace blam
{
	game_time_globals_definition* game_time_globals_get()
	{
		using namespace Blam::Memory;

		s_thread_local_storage* tls = ElDorito::GetMainTls();

		return tls->game_time_globals;
	}

	long game_seconds_to_ticks_round(real seconds)
	{
		real tick_rate = game_time_globals_get()->ticks_per_second * seconds;
		if (tick_rate < 0.0)
			return static_cast<long>((-1.0 * 0.5) + tick_rate);
		else
			return static_cast<long>((1.0 * 0.5) + tick_rate);
	}
}