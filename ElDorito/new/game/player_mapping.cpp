#include "player_mapping.hpp"

#include <cassert>

#include <ElDorito.hpp>
#include <Blam/Memory/TlsData.hpp>

namespace blam
{
    inline s_player_mapping_globals* player_mapping_globals_get()
    {
        using namespace Blam::Memory;

        s_thread_local_storage* tls = ElDorito::GetMainTls();
        if (!tls || !tls->player_control_globals)
            return nullptr;

        return tls->player_mapping_globals;
    }

	long player_index_from_user_index(long user_index)
	{
        if (user_index == -1)
            return -1;

        return player_mapping_globals_get()->output_user_player_mapping[user_index];

        //assert(user_index < 4);
        //s_player_mapping_globals* player_mapping_globals = player_mapping_globals_get();
        //datum_index input_user_index = player_mapping_globals->input_user_player_mapping[user_index];
        //if (input_user_index != -1)
        //{
        //    assert(input_user_index < 16);
        //    assert(player_mapping_globals->player_input_user_mapping[DATUM_INDEX_TO_ABSOLUTE_INDEX(player_index)] == user_index);
        //}
        //return input_user_index;
	}

    bool players_user_is_active(long user_index)
    {
        if (user_index == -1)
            return false;

        return player_mapping_globals_get()->output_user_player_mapping[user_index] != -1;
    }

    long player_mapping_get_player_count()
    {
        return player_mapping_globals_get()->active_output_user_count;
    }
}
