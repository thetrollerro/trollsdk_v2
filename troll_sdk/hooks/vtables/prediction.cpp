#include "../hooks.hpp"

bool __fastcall hooks::prediction::in_prediction::hook( void* ecx, void* edx ) {
	static auto maintain_sequence_transitions = ( void* ) ( utils::find_sig_ida( _( "client.dll" ), _( "84 C0 74 17 8B 87" ) ) );
	static auto setup_bones_ptr = ( void* ) ( utils::find_sig_ida( _( "client.dll" ), _( "8B 40 ? FF D0 84 C0 74 ? F3 0F 10 05 ? ? ? ? EB ?" ) ) + 5 );

	if ( _ReturnAddress( ) == maintain_sequence_transitions || _ReturnAddress( ) == setup_bones_ptr )
		return false;

	return o_in_prediction( ecx, edx );
}

bool __fastcall hooks::prediction::perform_prediction::hook( void* ecx, void* edx, int slot, c_base_player* pl, bool recived_world_update, int incoming_acknowledged, int outgoing_command ) {
	if ( !i::engine->is_in_game( ) || !pl || !g_local | !g_local->is_alive( ) || pl != g_local )
		return o_perform_prediction( ecx, edx, slot, pl, recived_world_update, incoming_acknowledged, outgoing_command );

	return o_perform_prediction( ecx, edx, slot, pl, recived_world_update, incoming_acknowledged, outgoing_command );
}

void __fastcall hooks::prediction::run_command::hook( void* ecx, void* edx, c_base_player* e, c_usercmd* cmd, void* move_helper ) {
	if ( !i::engine->is_in_game( ) || !e || e->ent_index( ) != i::engine->get_local_player( ) )
		return o_run_command( ecx, edx, e, cmd, move_helper );

	auto tickrate = ( int ) std::round( 1.f / i::globalvars->m_interval_per_tick );
	static auto sv_max_usercmd_future_ticks = i::cvar->find_var( "sv_max_usercmd_future_ticks" );

	/* predict cmd */
	if ( cmd->tick_count > i::globalvars->m_tick_count + ( tickrate + sv_max_usercmd_future_ticks->get_int( ) ) ) {
		cmd->hasbeenpredicted = true;
		if ( e->is_alive( ) ) {
			e->set_abs_origin( e->m_vecOrigin( ) );

			if ( i::globalvars->m_frame_time > 0.0f && !i::prediction->m_engine_paused )
				++e->m_nTickBase( );
		}
		return;
	}

	/* patch attack packet before running command */
	engine_prediction::patch_attack_packet( cmd, true );

	o_run_command( ecx, edx, e, cmd, move_helper );

	/* we predicted patch again */
	engine_prediction::patch_attack_packet( cmd, false );
}

void __fastcall hooks::prediction::setup_move::hook( void* ecx, void* edx, c_base_player* e, c_usercmd* cmd, c_move_helper* move_helper, c_movedata* move_data ) {
	/* run our original hook to update our move helper/data */
	o_setup_move( ecx, edx, e, cmd, move_helper, move_data );
}