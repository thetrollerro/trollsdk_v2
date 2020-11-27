#include "globals.hpp"

namespace g {
	c_usercmd* cmd = nullptr;
	bool send_packet = true;
	vec3_t real_angle = vec3_t( 0, 0, 0 );
	vec3_t fake_angle = vec3_t( 0, 0, 0 );
	int stage;
}

namespace exploit {
	int shift_rate;
	int tick_base_shift;
	float last_doubletap;
	int last_tickbase;
	int last_cmdnr;
	int tick_count;
	float vel_mod;
}