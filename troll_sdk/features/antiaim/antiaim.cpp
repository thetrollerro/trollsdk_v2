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

	if ( g_local->m_vecVelocity( ).length_2d( ) > 0.1f ) {
		m_lby_update_time = i::globalvars->m_cur_time + 0.22f;
	}
	if ( m_lby_update_time < i::globalvars->m_cur_time ) {
		m_lby_update_time = i::globalvars->m_cur_time + 1.1f;
		m_in_lby_update = true;
	}

	if ( m_lby_update_time - i::globalvars->m_interval_per_tick < i::globalvars->m_cur_time )
		m_in_balance_update = true;

	/* https://www.unknowncheats.me/forum/2628078-post10.html
	   used for micro movements
	   while not already moving
	*/

	/* get if can micro move */
	if ( i::clientstate->choked_commands <= 0 && !m_in_lby_update ) {
		m_can_micro_move = true;
	}
}
