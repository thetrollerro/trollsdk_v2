#pragma once
#include <array>
#include "../../sdk/classes/c_base_player.hpp"

namespace animations {
	/* bone bulld */
	bool generate_matrix( c_base_player* pl, matrix_t* out, float seed );
	bool build_matrix( c_base_player* pl, matrix_t* out, float seed );
	bool copy_matrix( c_base_player* pl, matrix_t* out );

	/* other */
	bool fresh_tick( );
}