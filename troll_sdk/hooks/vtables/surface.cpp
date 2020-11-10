#include "../hooks.hpp"
#include "../../menu/menu.hpp"

void __fastcall hooks::surface::lock_cursor::hook( void* ecx, void* edx ) {
	if ( menu::opened ) {
		i::surface->unlock_cursor( );
		return;
	}

	o_lock_cursor( i::clientdll, 0 );
}