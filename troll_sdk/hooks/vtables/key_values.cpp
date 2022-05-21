#include "../hooks.hpp"

void* __fastcall hooks::key_values::alloc_key_values_memory::hook( void* ecx, void* edx, int size ) {
	static auto alloc_key_values_engine = ( void* ) ( utils::find_sig_ida( "engine.dll", "FF 52 04 85 C0 74 0C 56" ) + 3 );
	static auto alloc_key_values_client = ( void* ) ( utils::find_sig_ida( "client.dll", "FF 52 04 85 C0 74 0C 56" ) + 3 );
	static auto alloc_key_values_material = ( void* ) ( utils::find_sig_ida( "materialsystem.dll", "FF 52 04 85 C0 74 0C 56" ) + 3 );
	static auto alloc_key_values_studio = ( void* ) ( utils::find_sig_ida( "studiorender.dll", "FF 52 04 85 C0 74 0C 56" ) + 3 );

	if ( _ReturnAddress( ) == alloc_key_values_engine || _ReturnAddress( ) == alloc_key_values_client || _ReturnAddress( ) == alloc_key_values_material || _ReturnAddress( ) == alloc_key_values_studio )
		return nullptr;

	return o_alloc_key_values_memory( ecx, edx, size );
}