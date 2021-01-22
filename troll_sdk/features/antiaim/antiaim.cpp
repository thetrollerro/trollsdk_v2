#include "antiaim.hpp"
#include "../../main.hpp"

void antiaim::predict_lby( ) {
	/* reset values every tick */
	m_in_lby_update = false;
	m_in_balance_update = false;
	m_can_micro_move = false;
	m_should_resync = false;

	/* do only when on ground */
	if ( !( g_local->m_fFlags( ) & fl_onground ) ) {
		return;
	}

	static float spawn_time = g_local->m_flSpawnTime( );
	if ( g_local->m_flSpawnTime( ) != spawn_time ) {
		spawn_time = g_local->m_flSpawnTime( );
		m_lby_update_time = spawn_time;
		m_should_resync = true;
	}

	/* get our lby timing */
	if ( g_local->m_vecVelocity( ).length_2d( ) > 0.1f ) {
		m_lby_update_time = i::globalvars->m_cur_time + 0.22f;
	}
	if ( m_should_resync || m_lby_update_time < i::globalvars->m_cur_time ) {
		m_lby_update_time = i::globalvars->m_cur_time + 1.1f;
		m_in_lby_update = true;
	}

	/* see if we are in balance update */
	if ( m_lby_update_time - i::globalvars->m_interval_per_tick < i::globalvars->m_cur_time )
		m_in_balance_update = true;

	/* check if we can micromove so ur lby will update faster */
	if ( i::clientstate->m_choked_commands <= 0 && !m_in_lby_update ) { // micromove and add our lby delta to our desync
		m_can_micro_move = true;
	}
}