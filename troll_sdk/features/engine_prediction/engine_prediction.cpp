#include "engine_prediction.hpp"

namespace engine_prediction {

	void predict( c_usercmd* cmd ) {
		/* fix tickbase */
		static float m_nTickBase;
		static c_usercmd* last_cmd;
		if ( !last_cmd || last_cmd->hasbeenpredicted )
			m_nTickBase = g_local->m_nTickBase( );
		else
			++m_nTickBase;

		last_cmd = cmd;

		/* backup stuff */
		stored_vars.m_in_prediction = i::prediction->m_in_prediction;
		stored_vars.m_is_first_time_predicted = i::prediction->m_is_first_time_predicted;

		/* anounce that we are predicting */
		i::prediction->m_in_prediction = true;
		i::prediction->m_is_first_time_predicted = false;

		/* backup vars */
		stored_vars.m_cur_time = i::globalvars->m_cur_time;
		stored_vars.m_frame_time = i::globalvars->m_frame_time;

		/* set vars appropriatly */
		i::globalvars->m_cur_time = m_nTickBase * i::globalvars->m_interval_per_tick;
		i::globalvars->m_frame_time = i::prediction->m_engine_paused ? 0.f : i::globalvars->m_interval_per_tick;

		/* get movedata */
		c_movedata data;
		memset( &data, 0, sizeof( data ) );

		/* set target player */
		i::game_movement->start_track_prediction_errors( g_local );
		i::movehelper->set_host( g_local );

		/* run movement */
		i::prediction->setup_move( g_local, cmd, i::movehelper, &data );
		i::game_movement->process_movement( g_local, &data );
		i::prediction->finish_move( g_local, cmd, &data );

		/* get max delta */
		antiaim::m_max_delta = ( g_local->max_desync_delta( ) * 2 ) + ( g_local->get_animstate( )->m_last_clientside_anim_update_time_delta * 120.f );
	}

	void restore( ) {
		/* restore stuff */
		i::prediction->m_in_prediction = stored_vars.m_in_prediction;
		i::prediction->m_is_first_time_predicted = stored_vars.m_is_first_time_predicted;

		/* reset player host */
		i::game_movement->finish_track_prediction_errors( g_local );
		i::movehelper->set_host( nullptr );

		/* restore vars */
		i::globalvars->m_cur_time = stored_vars.m_cur_time;
		i::globalvars->m_frame_time = stored_vars.m_frame_time;
	}

	void update( ) {
		if ( g::stage == frame_net_update_end && !g::cmd->buttons & in_attack ) {
			/* call CPrediction::Update */
			i::prediction->update( i::clientstate->m_delta_tick, i::clientstate->m_delta_tick > 0, i::clientstate->m_last_command_ack, i::clientstate->m_last_outgoing_command + i::clientstate->m_choked_commands );
		}
	}

	void correct_viewmodel_data( ) {
		if ( g_local->m_hViewModel( ) != 0xFFFFFFFF ) {
			const auto view_model = ( c_base_player* ) i::entitylist->get_client_entity_from_handle( g_local->m_hViewModel( ) );
			if ( !view_model )
				return;

			view_model->m_flAnimTime( ) = stored_viewmodel.m_viewmodel_anim_time;
			view_model->m_flCycle( ) = stored_viewmodel.m_viewmodel_cycle;
		}
	}

	void update_viewmodel_data( ) {
		if ( g_local->m_hViewModel( ) != 0xFFFFFFFF ) {
			const auto view_model = ( c_base_player* ) i::entitylist->get_client_entity_from_handle( g_local->m_hViewModel( ) );
			if ( !view_model )
				return;

			stored_viewmodel.m_viewmodel_anim_time = view_model->m_flAnimTime( );
			stored_viewmodel.m_viewmodel_cycle = view_model->m_flCycle( );
		}
	}

	void patch_attack_packet( c_usercmd* cmd, bool predicted ) {
		static bool m_bLastAttack = false;
		static bool m_bInvalidCycle = false;
		static float m_flLastCycle = 0.f;

		if ( predicted ) {
			m_bLastAttack = cmd->weaponselect || ( cmd->buttons & in_attack );
			m_flLastCycle = g_local->m_flCycle( );
		}
		else if ( m_bLastAttack && !m_bInvalidCycle )
			m_bInvalidCycle = g_local->m_flCycle( ) == 0.f && m_flLastCycle > 0.f;

		if ( m_bInvalidCycle )
			g_local->m_flCycle( ) = m_flLastCycle;
	}

}