#include "antiaim.hpp"
#include "../../main.hpp"

void antiaim::predict_lby( ) {
	/* reset values every tick */
	m_in_lby_update = false;
	m_in_balance_update = false;

	/* do only when on ground */
	if ( !( g_local->m_fFlags( ) & fl_onground ) ) {
		return;
	}

	/* get our lby timing */
	if ( g_local->m_vecVelocity( ).length_2d( ) > 0.1f ) {
		m_lby_update_time = i::globalvars->m_cur_time + 0.22f;
	}
	if ( m_lby_update_time < i::globalvars->m_cur_time ) {
		m_lby_update_time = i::globalvars->m_cur_time + 1.1f;
		m_in_lby_update = true;
	}

	/* see if we are in balance update */
	if ( m_lby_update_time - i::globalvars->m_interval_per_tick < i::globalvars->m_cur_time )
		m_in_balance_update = true;
}