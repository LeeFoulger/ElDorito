#pragma once

#include "cseries/cseries.hpp"

namespace blam
{
	enum e_game_progression_level
	{
		_game_progression_level_none = 0,
		_game_progression_level_normal,
		_game_progression_level_hub_and_level_is_hub,
		_game_progression_level_spoke_and_level_is_spoke,

		k_game_progression_level_count
	};

	struct s_campaign_armaments_player
	{
		bool valid;
		byte __data[0x1D];
	};
	static_assert(sizeof(s_campaign_armaments_player) == 0x1E);

	struct s_campaign_game_progression
	{
		byte __data[0x80];
	};
	static_assert(sizeof(s_campaign_game_progression) == 0x80);

	struct s_hub_progression
	{
		s_campaign_armaments_player hub_armaments[4];
		long hub_return_to_insertion_point;
		bool hub_progression_valid;
		byte : 8;
		byte : 8;
		byte : 8;
	};
	static_assert(sizeof(s_hub_progression) == 0x80);

}