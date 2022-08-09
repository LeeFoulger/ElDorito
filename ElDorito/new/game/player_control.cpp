#include "player_control.hpp"

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace blam
{
    s_player_control_globals* player_control_globals_get()
    {
        Blam::Memory::s_thread_local_storage* tls = ElDorito::GetMainTls();
        if (!tls || !tls->player_control_globals)
            return nullptr;

        return tls->player_control_globals;
    }
}