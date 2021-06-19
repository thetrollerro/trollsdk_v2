#include "globals.hpp"

namespace g {
	c_usercmd* cmd = nullptr;
	c_usercmd* shot_cmd = nullptr;
	bool send_packet = true;
	vec3_t choked_angle = vec3_t( 0, 0, 0 );
	vec3_t sent_angle = vec3_t( 0, 0, 0 );
	int stage;
	bool should_store_angle;
	vec3_t non_predicted_angle;
	bool inserting_into_tree;
	bool fake_ducking;
	int missed_shots[ 65 ];
}