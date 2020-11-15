#pragma once
#include <array>
#include "../../sdk/classes/c_base_player.hpp"

namespace animations {
	/* bone build */
	bool build_matrix( c_base_player* pl, matrix_t* out, int max_bones, int mask, float seed );
	bool setup_bones( c_base_player* pl, matrix_t* out, int max_bones, int mask, float seed );
	void fix_onshot( c_usercmd* cmd );

	/* fresh tick count */
	bool fresh_tick( );

	/* poses */
	void simulate_jumpfall( c_base_player* pl );
	float jump_fall( c_base_player* pl, float air_time );
}