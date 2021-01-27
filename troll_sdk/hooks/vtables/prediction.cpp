#include "../hooks.hpp"

bool __fastcall hooks::prediction::in_prediction::hook( void* ecx, void* edx ) {
	static auto maintain_sequence_transitions = ( void* ) ( utils::find_sig_ida( "client.dll", "84 C0 74 17 8B 87" ) );
	static auto setup_bones_ptr = ( void* ) ( utils::find_sig_ida( "client.dll", "8B 40 ? FF D0 84 C0 74 ? F3 0F 10 05 ? ? ? ? EB ?" ) + 5 );

	if ( _ReturnAddress( ) == maintain_sequence_transitions || _ReturnAddress( ) == setup_bones_ptr )
		return false;

	return o_in_prediction( ecx, 0 );
}

bool __fastcall hooks::prediction::perform_prediction::hook( void* ecx, void* edx, int slot, c_base_player* pl, bool recived_world_update, int incoming_acknowledged, int outgoing_command ) {
	if ( !i::engine->is_in_game( ) || !pl || !g_local | !g_local->is_alive( ) || pl != g_local )
		return o_perform_prediction( ecx, 0, slot, pl, recived_world_update, incoming_acknowledged, outgoing_command );

	return o_perform_prediction( ecx, 0, slot, pl, recived_world_update, incoming_acknowledged, outgoing_command );
}

void __fastcall hooks::prediction::run_command::hook( void* ecx, void* edx, c_base_player* e, c_usercmd* cmd, void* move_helper ) {
	if ( !i::engine->is_in_game( ) || !e || !g_local || !g_local->is_alive( ) || e != g_local )
		return o_run_command( ecx, 0, e, cmd, move_helper );

	/* predict cmd */
	if ( cmd->tick_count >= ( exploit::tick_count + int( 1 / i::globalvars->m_interval_per_tick ) + 8 ) ) {
		cmd->hasbeenpredicted = true;
		return;
	}

	/* backup */
	const auto o_tickbase = e->m_nTickBase( );
	const auto o_curtime = i::globalvars->m_cur_time;

	/* fix our tickbase */
	if ( cmd->command_number == exploit::last_cmdnr ) {
		e->m_nTickBase( ) -= exploit::shifted_ticks;
		++e->m_nTickBase( );

		i::globalvars->m_cur_time = ticks2time( e->m_nTickBase( ) );
	}

	const auto o_vel_modifier = g_local->m_flVelocityModifier( );

	engine_prediction::patch_attack_packet( cmd, true );

	if ( cmd->command_number == i::clientstate->m_last_command_ack + 1 )
		g_local->m_flVelocityModifier( ) = exploit::vel_mod;

	/* run usercommands */
	o_run_command( ecx, 0, e, cmd, move_helper );

	/* restore vel modifier */
	g_local->m_flVelocityModifier( ) = o_vel_modifier;

	/* restore */
	if ( cmd->command_number == exploit::last_cmdnr ) {
		e->m_nTickBase( ) = o_tickbase;

		i::globalvars->m_cur_time = o_curtime;
	}

	engine_prediction::patch_attack_packet( cmd, false );

	/* store netdata */
	//netdata::store( );
}