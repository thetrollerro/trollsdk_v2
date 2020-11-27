#pragma once
#include "../../main.hpp"

namespace engine_prediction {
	inline struct stored_vars {
		bool m_in_prediction;
		bool m_is_first_time_predicted;
		float m_frame_time;
		float m_cur_time;
	}stored_vars;

	inline struct viewmodel_t {
		float m_viewmodel_cycle;
		float m_viewmodel_anim_time;
	}stored_viewmodel;

	inline c_movedata data;

	void predict( c_usercmd* cmd );
	void restore( );

	void update( );

	void update_viewmodel_data( );
	void correct_viewmodel_data( );
}