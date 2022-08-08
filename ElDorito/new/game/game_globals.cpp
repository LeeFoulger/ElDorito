#include <ElDorito.hpp>
#include <game\game_globals.hpp>

namespace blam
{
	game_globals_storage* game_globals_get()
	{
		return *(blam::game_globals_storage**)ElDorito::Instance().GetMainTls(0x3C);
	}
}