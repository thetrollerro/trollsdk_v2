#include "../hooks.hpp"

bool __fastcall hooks::file_system::sv_pure_loose_file_allowed::hook( void* ecx, void* edx ) {
	if ( !i::engine->is_in_game( ) || !g_local ) {
		return o_sv_pure_loose_file_allowed( ecx, edx );
	}

	return true;
}