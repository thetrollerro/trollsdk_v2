#include "../hooks.hpp"
/* all the hooks from are basically idk from where tf they come xd i just have sigs n shit */

void __fastcall hooks::game::check_file_crcs_with_server::hook( void* ecx, void* edx ) {
	/* https://github.com/perilouswithadollarsign/cstrike15_src/blob/29e4c1fda9698d5cebcdaf1a0de4b829fa149bf8/engine/client.cpp#L1844 */
	/* as u can see it gets called every frame :thinking: */

	/* basically this will fix server kicks by creating materials for chams ( we return this fund to prevent CRC Check from happening */
	return;
}

bool __fastcall hooks::game::should_skip_animframe::hook( void* ecx, void* edx ) {
	return false;
	/* return o_should_skip_animframe( ecx, 0 ) */
}

bool __fastcall hooks::game::sv_cheats_get_bool::hook( void* ecx, void* edx ) {
	static auto cam_think = ( void* ) utils::find_sig_ida( "client.dll", "85 C0 75 30 38 86" );

	if ( _ReturnAddress( ) == cam_think )
		return true;

	return o_sv_cheats_get_bool( ecx, 0 );
}