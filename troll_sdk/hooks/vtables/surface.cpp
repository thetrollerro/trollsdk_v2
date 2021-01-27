#include "../hooks.hpp"
#include "../../menu/menu.hpp"

void __fastcall hooks::surface::draw_set_color::hook( void* ecx, void* edx, int r, int g, int b, int a ) {
	return o_draw_set_color( ecx, 0, r, g, b, a );
}

void __fastcall hooks::surface::lock_cursor::hook( void* ecx, void* edx ) {
	if ( menu::opened ) {
		i::surface->unlock_cursor( );
		return;
	}

	o_lock_cursor( ecx, 0 );
}