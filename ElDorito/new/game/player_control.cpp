#include "player_control.hpp"

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace
{
    bool(__cdecl* game_in_progress)(void) = reinterpret_cast<decltype(game_in_progress)>(0x005314B0);
    bool(__cdecl* game_is_ui_shell)(void) = reinterpret_cast<decltype(game_is_ui_shell)>(0x00531E90);
}

namespace blam
{
    s_player_control_globals* player_control_globals_get()
    {
        Blam::Memory::s_thread_local_storage* tls = ElDorito::GetMainTls();
        if (!tls || !tls->player_control_globals)
            return nullptr;

        return tls->player_control_globals;
    }

    inline bool player_control_get_machinima_camera_enabled()
    {
        // unsure `game_options_get` is needed here
        //if (game_in_progress() && !game_is_ui_shell())
        //    game_options_get();
        //return player_control_globals->machinima_camera_enabled;

        if (game_in_progress() && !game_is_ui_shell())
            return player_control_globals_get()->machinima_camera_enabled;

        return false;
    }

    inline bool player_control_get_machinima_camera_use_old_controls()
    {
        if (player_control_get_machinima_camera_enabled())
            return player_control_globals_get()->machinima_camera_use_old_controls;

        return false;
    }

    inline bool player_control_get_machinima_camera_debug()
    {
        if (player_control_get_machinima_camera_enabled())
            return player_control_globals_get()->machinima_camera_debug;

        return false;
    }

    inline void player_control_set_machinima_camera(bool enabled, bool debug, bool use_old_controls)
    {
        s_player_control_globals* player_control_globals = player_control_globals_get();
        if (!player_control_globals)
            return;

        player_control_globals->machinima_camera_enabled = enabled;
        player_control_globals->machinima_camera_debug = debug;
        player_control_globals->machinima_camera_use_old_controls = use_old_controls;
    }
}