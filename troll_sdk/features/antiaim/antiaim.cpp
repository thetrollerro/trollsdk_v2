#include "antiaim.hpp"
#include "../../main.hpp"

void antiaim::predict_lby( ) {
	static float spawn_time;

	m_in_lby_update = false;
	m_in_balance_update = false;
	m_can_micro_move = false;

	if ( !( g_local->m_fFlags( ) & fl_onground ) ) {
		return;
	}

	const auto state = g_local->get_animstate( );
	if ( !state ) return;

	if ( g_local->m_flSpawnTime( ) != spawn_time ) {
		spawn_time = g_local->m_flSpawnTime( );
		m_lby_update_time = spawn_time;
	}

	if ( g_local->m_vecVelocity( ).length_2d( ) > 0.1f )
		m_lby_update_time = i::globalvars->m_cur_time + 0.22f;
	else if ( i::globalvars->m_cur_time >= m_lby_update_time ) {
		m_in_lby_update = true;
		m_lby_update_time = i::globalvars->m_cur_time + 1.1f;
	}

	if ( m_lby_update_time - i::globalvars->m_interval_per_tick < i::globalvars->m_cur_time )
		m_in_balance_update = true;

	/* https://www.unknowncheats.me/forum/2628078-post10.html
	   used for micro movements
	   while not already moving
	*/

	/* get if can micro move */
	if ( ( i::clientstate->choked( ) <= 0 && !m_in_lby_update ) ) {
		m_can_micro_move = true;
	}
}
