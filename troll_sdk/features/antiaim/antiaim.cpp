#include "antiaim.hpp"
#include "../../main.hpp"

void antiaim::predict_lby( ) {
	static float o_lby_update_time;

	m_in_lby_update = false;
	m_should_resync = false;
	m_can_micro_move = false;

	if ( !( g_local->m_fFlags( ) & fl_onground ) ) {
		return;
	}

	if ( m_lby_update_time != o_lby_update_time ) {
		m_should_resync = true;
	}

	if ( g_local->m_vecVelocity( ).length_2d( ) > 0.1f ) {
		m_lby_update_time = i::globalvars->m_cur_time + 0.22f;
	}
	else if ( m_lby_update_time < i::globalvars->m_cur_time || m_should_resync ) {
		m_lby_update_time = i::globalvars->m_cur_time + 1.1f;
		o_lby_update_time = m_lby_update_time;
		if ( m_should_resync ) m_should_resync = false;
		m_in_lby_update = true;
	}

	/* https://www.unknowncheats.me/forum/2628078-post10.html
	   used for micro movements
	   while not already moving
	*/

	/* get if can micro move */
	if ( i::clientstate->choked_commands <= 0 && !m_in_lby_update ) {
		m_can_micro_move = true;
	}
}