#pragma once
#include "../../main.hpp"

namespace engine_prediction {
	inline struct stored_vars {
		bool m_in_prediction;
		bool m_is_first_time_predicted;
		float m_frame_time;
		float m_cur_time;
		int unpred_flags;
		int tickbase;
		vec3_t unpred_vel;
		c_movedata move_data;
		uintptr_t prediction_player;
		uintptr_t prediction_seed;
		float fixed_curtime;
	}stored_vars;

	inline struct viewmodel_t {
		float m_viewmodel_cycle;
		float m_viewmodel_anim_time;
	}stored_viewmodel;

	void predict( c_usercmd* cmd, c_base_player* player );
	void restore( c_base_player* player );

	void update( );

	void update_viewmodel_data( );
	void correct_viewmodel_data( );

	void patch_attack_packet( c_usercmd* cmd, bool predicted );

	void fix_revolver( c_base_combat_weapon* m_pweapon );
}