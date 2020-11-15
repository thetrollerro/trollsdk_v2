#include "../hooks.hpp"

void __fastcall hooks::engine::fire_game_event::hook( void* ecx, void* edx ) {
	if ( !g_local || !g_local->is_alive( ) )
		return o_fire_game_event( i::engine, 0 );

	struct event_t {
	public:
		uint8_t pad1[ 4 ];
		float delay;
		uint8_t pad2[ 48 ];
		event_t* next;
	};
	auto event = *( event_t** ) ( uintptr_t( i::clientstate ) + 0x4E6C );
	while ( event ) {
		event->delay = 0.0f;
		event = event->next;
	}

	return o_fire_game_event( i::engine, 0 );
}

bool __fastcall hooks::engine::is_hltv::hook( void* ecx, void* edx ) {
	static auto return_to_setup_vel = ( void* ) utils::find_sig_ida( "client.dll", "84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80" );
	static auto return_to_accumulate_layers = ( void* ) utils::find_sig_ida( "client.dll", "84 C0 75 0D F6 87" );

	if ( _ReturnAddress( ) == return_to_setup_vel )
		return true;

	if ( _ReturnAddress( ) == return_to_accumulate_layers )
		return true;

	return o_is_hltv( i::engine, 0 );
}