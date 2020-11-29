#include "../hooks.hpp"

void __cdecl hooks::engine::cl_move::hook( float accumulated_extra_samples, bool final_tick ) {
	return o_cl_move( accumulated_extra_samples, final_tick );
}

void __fastcall hooks::engine::fire_game_event::hook( void* ecx, void* edx ) {
	if ( !g_local || !g_local->is_alive( ) )
		return o_fire_game_event( ecx, edx );

	/* get this from CL_FireEvents string "Failed to execute event for classId" in engine.dll */
	auto event = *( event_t** ) ( uintptr_t( i::clientstate ) + 0x4E6C );
	while ( event ) {
		event->delay = 0.0f;
		event = event->next;
	}

	return o_fire_game_event( ecx, edx );
}

bool __fastcall hooks::engine::is_connected::hook( void* ecx, void* edx ) {
	return o_is_connected( ecx, edx );
}

bool __fastcall hooks::engine::is_hltv::hook( void* ecx, void* edx ) {
	static auto return_to_setup_vel = ( void* ) utils::find_sig_ida( "client.dll", "84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80" );
	static auto return_to_accumulate_layers = ( void* ) utils::find_sig_ida( "client.dll", "84 C0 75 0D F6 87" );

	if ( _ReturnAddress( ) == return_to_setup_vel || _ReturnAddress( ) == return_to_accumulate_layers )
		return true;

	return o_is_hltv( ecx, edx );
}

bool __fastcall hooks::engine::is_in_game::hook( void* ecx, void* edx ) {
	return o_is_in_game( ecx, edx );
}