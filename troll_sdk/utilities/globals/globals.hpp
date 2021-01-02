#pragma once
#include "../../sdk/interfaces/classes/c_input.hpp"
#include "../../sdk/math/vector.hpp"

namespace g {
	extern c_usercmd* cmd;
	extern bool send_packet;
	extern vec3_t real_angle;
	extern vec3_t fake_angle;
	extern int stage;
	extern bool should_store_angle;
	extern vec3_t non_predicted_angle;
}

namespace exploit {
	extern int shift_rate;
	extern int tick_base_shift;
	extern float last_doubletap;
	extern int last_tickbase;
	extern int last_cmdnr;
	extern int tick_count;
	extern float vel_mod;
}
