#pragma once
#include <array>
#include "../../sdk/classes/c_base_player.hpp"

namespace animations {
	bool setup_bones( c_base_player* pl, matrix_t* out, int max_bones, int mask, float seed );
	bool fresh_tick( );
}