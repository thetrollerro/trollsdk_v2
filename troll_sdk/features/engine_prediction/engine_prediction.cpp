#include "engine_prediction.hpp"

namespace engine_prediction {

	void update_button_state( c_base_player* pl, int buttons ) {
		/* https://github.com/perilouswithadollarsign/cstrike15_src/blob/29e4c1fda9698d5cebcdaf1a0de4b829fa149bf8/game/shared/baseplayer_shared.cpp#L961 */

		int buttons_changed = buttons ^ *( int* ) ( std::uintptr_t( pl ) + 0x3208 );

		*( int* ) ( std::uintptr_t( pl ) + 0x320C ) = *( int* ) ( std::uintptr_t( pl ) + 0x3208 );
		*( int* ) ( std::uintptr_t( pl ) + 0x3208 ) = buttons;
		/* m_afButtonPressed */ *( int* ) ( std::uintptr_t( pl ) + 0x3200 ) = buttons & buttons_changed;
		/* m_afButtonReleased */ *( int* ) ( std::uintptr_t( pl ) + 0x3204 ) = buttons_changed & ~buttons;
	}

	void predict( c_usercmd* cmd, c_base_player* player ) {
		if ( !i::engine->is_in_game( ) || !player ) {
			return;
		}

		//if ( !stored_vars.move_data )
		memset( &stored_vars.move_data, 0, sizeof( c_movedata ) );

		if ( !stored_vars.prediction_player || !stored_vars.prediction_seed ) {
			stored_vars.prediction_seed = *reinterpret_cast< std::uintptr_t* >( std::uintptr_t( utils::find_sig_ida( "client.dll", "8B 47 40 A3" ) ) + 4 );
			stored_vars.prediction_player = *reinterpret_cast< std::uintptr_t* >( std::uintptr_t( utils::find_sig_ida( "client.dll", "0F 5B C0 89 35" ) ) + 5 );;
		}
		*reinterpret_cast< int* >( stored_vars.prediction_seed ) = cmd ? cmd->random_seed : -1;
		*reinterpret_cast< int* >( stored_vars.prediction_player ) = std::uintptr_t( player );
		*reinterpret_cast< c_usercmd** >( std::uintptr_t( player ) + 0x3348 ) = cmd; /* 0x3334 */
		*reinterpret_cast< c_usercmd** >( std::uintptr_t( player ) + 0x3288 ) = cmd;

		stored_vars.tickbase = player->m_nTickBase( );
		stored_vars.unpred_flags = player->m_fFlags( );
		stored_vars.unpred_vel = player->m_vecVelocity( );

		/* backup stuff */
		stored_vars.m_in_prediction = i::prediction->m_in_prediction;
		stored_vars.m_is_first_time_predicted = i::prediction->m_is_first_time_predicted;

		/* backup vars */
		stored_vars.m_cur_time = i::globalvars->m_cur_time;
		stored_vars.m_frame_time = i::globalvars->m_frame_time;

		/* set vars appropriatly */
		i::globalvars->m_cur_time = stored_vars.fixed_curtime = player->m_nTickBase( ) * i::globalvars->m_interval_per_tick;
		i::globalvars->m_frame_time = i::prediction->m_engine_paused ? 0.f : i::globalvars->m_interval_per_tick;

		/* anounce that we are predicting */
		i::prediction->m_in_prediction = true;
		i::prediction->m_is_first_time_predicted = false;

		if ( cmd->impulse )
			*reinterpret_cast< std::uint32_t* >( std::uintptr_t( player ) + 0x320C ) = cmd->impulse;

		//cmd->buttons |= *( std::uint32_t* ) ( std::uintptr_t( player ) + 0x3334 ); /* m_afButtonForced */
		//cmd->buttons &= ~*( std::uint32_t* ) ( std::uintptr_t( player ) + 0x3330 ); /* m_afButtonDisabled */

		update_button_state( player, cmd->buttons );

		i::prediction->check_moving_ground( player, i::globalvars->m_frame_time );

		i::game_movement->start_track_prediction_errors( player );

		i::movehelper->set_host( player );
		i::prediction->setup_move( player, cmd, i::movehelper, &stored_vars.move_data );
		i::game_movement->process_movement( player, &stored_vars.move_data );
		i::prediction->finish_move( player, cmd, &stored_vars.move_data );
		i::movehelper->process_impacts( );

		i::game_movement->finish_track_prediction_errors( player );
		i::movehelper->set_host( nullptr );
		i::game_movement->reset( );

		//player->m_nTickBase( ) = stored_vars.tickbase;

		i::prediction->m_is_first_time_predicted = stored_vars.m_is_first_time_predicted;
		i::prediction->m_in_prediction = stored_vars.m_in_prediction;

		/* get deltas */
		antiaim::m_max_delta = ( player->max_desync_delta( ) * 2 ) + ( player->get_animstate( )->m_last_clientside_anim_update_time_delta * 120.f );
	}

	void restore( c_base_player* player ) {
		if ( !i::engine->is_in_game( ) || !player || !player->is_alive( ) ) {
			return;
		}

		*reinterpret_cast< std::uint32_t* >( std::uintptr_t( player ) + 0x3348 ) = 0;
		if ( stored_vars.prediction_player && stored_vars.prediction_seed ) {
			*reinterpret_cast< int* >( stored_vars.prediction_seed ) = 0xffffffff;
			*reinterpret_cast< int* >( stored_vars.prediction_player ) = 0;
		}
		if ( !i::prediction->m_engine_paused && i::globalvars->m_frame_time > 0 ) {
			//player->m_nTickBase( )++;
		}
		i::globalvars->m_cur_time = stored_vars.m_cur_time;
		i::globalvars->m_frame_time = stored_vars.m_frame_time;
	}

	void update( ) {
		if ( i::clientstate && i::clientstate->m_delta_tick > 0 )
			i::prediction->update( i::clientstate->m_delta_tick, i::clientstate->m_delta_tick > 0, i::clientstate->m_last_command_ack, i::clientstate->m_last_outgoing_command + i::clientstate->m_choked_commands );
	}

	void correct_viewmodel_data( ) {
		if ( !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
			return;
		}

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