#include "../hooks.hpp"

bool __fastcall hooks::game::should_skip_animframe::hook( void* ecx, void* edx ) {
	return false;
	/* return o_should_skip_animframe( ecx, edx ) */
}

bool __fastcall hooks::game::sv_cheats_get_bool::hook( void* ecx, void* edx ) {
	static auto cam_think = ( void* ) utils::find_sig_ida( "client.dll", "85 C0 75 30 38 86" );

	if ( _ReturnAddress( ) == cam_think )
		return true;

	return o_sv_cheats_get_bool( ecx, edx );
}