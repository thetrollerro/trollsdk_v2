#pragma once
#include <array>
#include "../../sdk/classes/c_base_player.hpp"

namespace animations {
	/* bone build */
	bool generate_matrix( c_base_player* pl, matrix_t* out, int mask );
	bool build_matrix( c_base_player* pl, matrix_t* matrix, int mask );
	bool copy_matrix( c_base_player* pl, matrix_t* out );

	/* fresh tick count */
	bool fresh_tick( );
}