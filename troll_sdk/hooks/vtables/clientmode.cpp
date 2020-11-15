#include "../hooks.hpp"
#include "../../menu/menu.hpp"

int __fastcall hooks::clientmode::do_post_screen_effects::hook( void* ecx, void* edx, int a ) {

	return o_do_post_screen_effects( i::clientmode, 0, a );
}

void __fastcall hooks::clientmode::override_view::hook( void* ecx, void* edx, view_setup_t* view ) {
	if ( !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		o_override_view( i::clientmode, 0, view );
		return;
	}

	o_override_view( i::clientmode, 0, view );
}