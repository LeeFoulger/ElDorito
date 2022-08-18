#include "player_control.hpp"

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace blam
{
    inline s_player_control_globals* player_control_globals_get()
    {
        using namespace Blam::Memory;

        s_thread_local_storage* tls = ElDorito::GetMainTls();
        if (!tls || !tls->player_control_globals)
            return nullptr;

        return tls->player_control_globals;
    }

    inline bool player_control_get_machinima_camera_enabled()
    {
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

    inline void player_control_toggle_machinima_camera_enabled()
    {
        s_player_control_globals* player_control_globals = player_control_globals_get();
        if (!player_control_globals)
            return;

        player_control_globals->machinima_camera_enabled = !player_control_globals->machinima_camera_enabled;
    }

    inline void player_control_toggle_machinima_camera_use_old_controls()
    {
        s_player_control_globals* player_control_globals = player_control_globals_get();
        if (!player_control_globals)
            return;

        player_control_globals->machinima_camera_use_old_controls = !player_control_globals->machinima_camera_use_old_controls;
    }

    inline void player_control_toggle_machinima_camera_debug()
    {
        s_player_control_globals* player_control_globals = player_control_globals_get();
        if (!player_control_globals)
            return;

        player_control_globals->machinima_camera_debug = !player_control_globals->machinima_camera_debug;
    }

    inline void player_control_toggle_player_input(long user_index)
    {
        s_player_control_globals* player_control_globals = player_control_globals_get();
        if (!player_control_globals)
            return;

        player_control_globals->input_user_states[user_index].player_input_locked = !player_control_globals->input_user_states[user_index].player_input_locked;
    }
}