#include "engine_prediction.hpp"

void engine_prediction::predict( c_usercmd* cmd ) {
	static int m_nTickBase;
	static c_usercmd* last_cmd;
	if ( last_cmd ) {
		if ( last_cmd->hasbeenpredicted )
			m_nTickBase = g_local->m_nTickBase( );
		else
			++m_nTickBase;
	}

	last_cmd = cmd;

	/* anounce that we are predicting */
	i::prediction->m_in_prediction = true;

	/* CPrediction::StartCommand */
	g_local->m_pCurrentCommand( ) = cmd;
	g_local->m_PlayerCommand( ) = *cmd;

	/* backup vars */
	stored_vars.m_cur_time = i::globalvars->m_cur_time;
	stored_vars.m_frame_time = i::globalvars->m_frame_time;

	/* set vars appropriatly */
	i::globalvars->m_cur_time = ticks2time( m_nTickBase );
	i::globalvars->m_frame_time = i::prediction->m_engine_paused ? 0.f : i::globalvars->m_interval_per_tick;

	/* set target player */
	i::movehelper->set_host( g_local );
	i::game_movement->start_track_prediction_errors( g_local );

	/* get move data */
	c_movedata data;
	memset( &data, 0, sizeof( data ) );

	/* setup input */
	i::prediction->setup_move( g_local, cmd, i::movehelper, &data );

	/* run movement */
	i::prediction->setup_move( g_local, cmd, i::movehelper, &data );
	i::game_movement->process_movement( g_local, &data );
	i::prediction->finish_move( g_local, cmd, &data );
	i::game_movement->finish_track_prediction_errors( g_local );

	/* reset player host */
	i::movehelper->set_host( nullptr );
}

void engine_prediction::restore( ) {
	i::prediction->m_in_prediction = false;

	/* restore vars */
	i::globalvars->m_cur_time = stored_vars.m_cur_time;
	i::globalvars->m_frame_time = stored_vars.m_frame_time;
}

void engine_prediction::update( ) {
	/* this will fix old commands that are not predicted ( should fix lowfps prediction issues ) */
	bool valid { i::clientstate->delta_tick > 0 };
	int start = i::clientstate->last_command_ack;
	int stop = i::clientstate->last_outgoing_command + i::clientstate->choked( );

	/* call CPrediction::Update */
	i::prediction->update( i::clientstate->delta_tick, valid, start, stop );
}

void engine_prediction::correct_viewmodel_data( ) {
	if ( g_local->m_hViewModel( ) != 0xFFFFFFFF ) {
		const auto view_model = ( c_base_player* ) i::entitylist->get_client_entity_from_handle( g_local->m_hViewModel( ) );
		if ( !view_model )
			return;

		view_model->m_flAnimTime( ) = stored_viewmodel.m_viewmodel_anim_time;
		view_model->m_flCycle( ) = stored_viewmodel.m_viewmodel_cycle;
	}
}

void engine_prediction::update_viewmodel_data( ) {
	if ( g_local->m_hViewModel( ) != 0xFFFFFFFF ) {
		const auto view_model = ( c_base_player* ) i::entitylist->get_client_entity_from_handle( g_local->m_hViewModel( ) );
		if ( !view_model )
			return;

		stored_viewmodel.m_viewmodel_anim_time = view_model->m_flAnimTime( );
		stored_viewmodel.m_viewmodel_cycle = view_model->m_flCycle( );
	}
}