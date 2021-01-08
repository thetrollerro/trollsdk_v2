#include "../hooks.hpp"

bool __fastcall hooks::file_system::sv_pure_loose_file_allowed::hook( void* ecx, void* edx ) {
	static auto return_to_client = ( void* ) utils::find_sig_ida( "client.dll", "83 F8 02 0F 85 ? ? ? ? 8B 3D ? ? ? ? FF D7" );
	static auto return_to_engine = ( void* ) utils::find_sig_ida( "engine.dll", "83 F8 02 75 6C 68 ? ? ? ? FF 15 ? ? ? ? 8B 4C 24 28 83 C4 04" );

	if ( _ReturnAddress( ) == return_to_client || _ReturnAddress( ) == return_to_engine )
		return false;

	return true;
}