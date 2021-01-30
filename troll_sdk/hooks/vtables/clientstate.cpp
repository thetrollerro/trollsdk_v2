#include "../hooks.hpp"

void __fastcall hooks::clientstate::check_file_crcs_with_server::hook( void* ecx, void* edx ) {
	/* https://github.com/perilouswithadollarsign/cstrike15_src/blob/29e4c1fda9698d5cebcdaf1a0de4b829fa149bf8/engine/client.cpp#L1844 */
	/* as u can see it gets called every frame :thinking: */

	/* basically this will fix server kicks by creating materials for chams ( we return this fund to prevent CRC Check from happening */
	if ( i::engine->is_in_game( ) )
		return;
}