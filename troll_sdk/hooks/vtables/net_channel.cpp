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

int __fastcall hooks::net_channel::send_datagram::hook( void* ecx, void* edx, void* data ) {
	//if ( !i::engine->get_net_channel( ) )
	//	return o_send_datagram( ecx, edx, data );

	//auto o_rel_state = i::engine->get_net_channel( )->m_in_rel_state;
	//auto o_in_seq = i::engine->get_net_channel( )->m_in_seq;

	////if ( extended_bt )
	//{
	//	float correct = std::fmaxf( 0.f, ( 200.f / 1000.f ) - i::engine->get_net_channel( )->get_latency( flow_outgoing ) - lag_comp::lerp_time( ) );

	//	i::engine->get_net_channel( )->m_in_seq += 2 * ( 64 - 3 ) - static_cast< uint32_t >( ( 64 - 3 ) * correct );
	//}

	int ret = o_send_datagram( ecx, edx, data );

	/*i::engine->get_net_channel()->m_in_rel_state = o_rel_state;
	i::engine->get_net_channel()->m_in_seq = o_in_seq;*/

	return ret;
}

bool __fastcall hooks::net_channel::send_net_message::hook( void* ecx, void* edx, i_net_message& message, bool force_reliable, bool voice ) {
	if ( message.get_type( ) == 14 )
		return false;

	if ( message.get_type( ) == 9 )
		voice = true;

	return o_send_net_message( ecx, edx, message, force_reliable, voice );
}