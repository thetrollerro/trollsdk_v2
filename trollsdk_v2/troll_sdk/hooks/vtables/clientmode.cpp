#include "../hooks.hpp"
#include "../../menu/menu.hpp"

void __fastcall hooks::clientmode::override_view::hook( void* ecx, void* edx, view_setup_t* view ) {
	if ( !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		o_override_view( i::clientmode, 0, view );
		return;
	}

	o_override_view( i::clientmode, 0, view );
}