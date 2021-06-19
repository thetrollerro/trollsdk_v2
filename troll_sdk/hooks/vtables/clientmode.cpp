#include "../hooks.hpp"
#include "../../menu/menu.hpp"

int __fastcall hooks::clientmode::do_post_screen_effects::hook( void* ecx, void* edx, int a ) {
	if ( !i::engine->is_in_game( ) || !g_local ) {
		return o_do_post_screen_effects( ecx, edx, a );
	}

	return o_do_post_screen_effects( ecx, edx, a );
}

float __fastcall hooks::clientmode::get_viewmodel_fov::hook( void* ecx, void* edx ) {
	return o_get_viewmodel_fov( ecx, edx );
}

void __fastcall hooks::clientmode::override_view::hook( void* ecx, void* edx, view_setup_t* view ) {
	if ( !i::engine->is_in_game( ) || !g_local ) {
		o_override_view( ecx, edx, view );
		return;
	}

	o_override_view( ecx, edx, view );
}