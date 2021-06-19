#include "../hooks.hpp"
/* all the hooks from are basically idk from where tf they come xd i just have sigs n shit */

void __fastcall hooks::game::check_for_sequence_change::hook( void* ecx, void* edx, void* hdr, int cur_sequence, bool force_new_sequence, bool interpolate ) {
	// no sequence interpolation over here mate
	// forces the animation queue to clear

	return o_check_for_sequence_change( ecx, edx, hdr, cur_sequence, force_new_sequence, false );
}

bool __fastcall hooks::game::should_skip_animframe::hook( void* ecx, void* edx ) {
	return false;
	/* return o_should_skip_animframe( ecx, edx ) */
}

bool __fastcall hooks::game::sv_cheats_get_bool::hook( void* ecx, void* edx ) {
	if ( !ecx ) // gay
		return false;

	static auto cam_think = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "85 C0 75 30 38 86" ) );
	static auto cl_extrapolate_ret = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "85 C0 74 22 8B 0D ? ? ? ? 8B 01 8B" ) );
	static auto hermite_fix_ret = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "0F B6 15 ? ? ? ? 85 C0" ) );
	static auto cl_interpolate_ret = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "85 C0 BF ? ? ? ? 0F 95 C3" ) );

	auto rtr = _ReturnAddress( );

	if ( rtr == cl_interpolate_ret || rtr == hermite_fix_ret || rtr == cl_extrapolate_ret )
		return false;

	if ( rtr == cam_think )
		return true;

	return o_sv_cheats_get_bool( ecx, nullptr );
}