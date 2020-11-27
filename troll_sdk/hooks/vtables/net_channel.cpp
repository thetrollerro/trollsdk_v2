#include "../hooks.hpp"

void __cdecl hooks::net_channel::process_packet::hook( void* packet, bool header ) {
	if ( !i::engine->get_net_channel( ) )
		return o_process_packet( packet, header );

	/* get this from CL_FireEvents string "Failed to execute event for classId" in engine.dll */
	auto event = *( event_t** ) ( uintptr_t( i::clientstate ) + 0x4E6C );
	while ( event ) {
		event->delay = 0.0f;
		event = event->next;
	}

	/* game events are actually fired in OnRenderStart which is WAY later after they are received */
	/* effective delay by lerp time, now we call them right after theyre received (all receive proxies are invoked without delay). */
	i::engine->fire_game_event( );
}