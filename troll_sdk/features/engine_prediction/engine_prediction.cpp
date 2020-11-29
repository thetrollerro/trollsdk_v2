#include "engine_prediction.hpp"

void engine_prediction::predict( c_usercmd* cmd ) {
	const auto get_random_seed = [ & ] ( ) {
		using o_fn = unsigned long( __cdecl* )( std::uintptr_t );
		static auto offset = utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 70 6A 58" );
		static auto MD5_PseudoRandom = reinterpret_cast< o_fn >( offset );
		return MD5_PseudoRandom( cmd->command_number ) & 0x7FFFFFFF;
	};

	/* fix tickbase */
	static float m_nTickBase;
	static c_usercmd* last_cmd;
	if ( last_cmd ) {
		if ( last_cmd->hasbeenpredicted )
			m_nTickBase = g_local->m_nTickBase( );
		else
			++m_nTickBase;
	}

	/* anounce that we started predicting */
	i::prediction->m_in_prediction = true;

	/* get some stuff */
	memset( &data, 0, sizeof( data ) );

	/* backup stuff */
	stored_vars.m_in_prediction = i::prediction->m_in_prediction;
	stored_vars.m_is_first_time_predicted = i::prediction->m_is_first_time_predicted;

	/* anounce that we are predicting */
	i::prediction->m_in_prediction = true;
	i::prediction->m_is_first_time_predicted = false;

	/* backup vars */
	stored_vars.m_cur_time = i::globalvars->m_cur_time;
	stored_vars.m_frame_time = i::globalvars->m_frame_time;

	/* fix randomseed cuz in clientmode createmove it isn t called :/ and clientdll createmove its kinda shit idk */
	cmd->random_seed = get_random_seed( ); // remove if u wanna hook clientdll createmove

	/* set vars appropriatly */
	i::globalvars->m_cur_time = ticks2time( m_nTickBase );
	i::globalvars->m_frame_time = i::prediction->m_engine_paused ? 0.f : i::globalvars->m_interval_per_tick;

	/* set target player */
	i::game_movement->start_track_prediction_errors( g_local );
	i::movehelper->set_host( g_local );

	/* run movement */
	i::prediction->setup_move( g_local, cmd, i::movehelper, &data );
	i::game_movement->process_movement( g_local, &data );
	i::prediction->finish_move( g_local, cmd, &data );

	/* reset player host */
	i::game_movement->finish_track_prediction_errors( g_local );
	i::movehelper->set_host( nullptr );

	/* fix accuracy */
	auto weapon = g_local->get_active_weapon( );
	if ( !weapon ) {
		return;
	}

	/* update accuracy ( helps rage to be more accurate ) */
	weapon->update_accuracy_penalty( );

	/* get deltas */
	antiaim::m_max_delta = 90.4f;
	antiaim::m_max_lby_delta = ( g_local->max_desync_delta( ) * 2 ) + ( g_local->get_animstate( )->m_last_clientside_anim_update_time_delta * 120.f );
}

void engine_prediction::restore( ) {
	/* restore stuff */
	i::prediction->m_in_prediction = stored_vars.m_in_prediction;
	i::prediction->m_is_first_time_predicted = stored_vars.m_is_first_time_predicted;

	/* restore vars */
	i::globalvars->m_cur_time = stored_vars.m_cur_time;
	i::globalvars->m_frame_time = stored_vars.m_frame_time;
}

void engine_prediction::update( ) {
	if ( g::stage == frame_net_update_end && !g::cmd->buttons & in_attack ) {
		/* call CPrediction::Update */
		i::prediction->update( i::clientstate->delta_tick, i::clientstate->delta_tick > 0, i::clientstate->last_command_ack, i::clientstate->last_outgoing_command + i::clientstate->choked_commands );
	}
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