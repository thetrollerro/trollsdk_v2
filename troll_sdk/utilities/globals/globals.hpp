#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "../../sdk/interfaces/classes/c_input.hpp"
#include "../../sdk/math/vector.hpp"

class c_base_player;
class c_base_combat_weapon;
class weapon_info_t;
namespace g {
	extern c_usercmd* cmd;
	extern c_usercmd* shot_cmd;
	extern bool send_packet;
	extern vec3_t choked_angle;
	extern vec3_t sent_angle;
	extern int stage;
	extern bool should_store_angle;
	extern vec3_t non_predicted_angle;
	extern bool inserting_into_tree;
	extern bool fake_ducking;
	extern int missed_shots[ 65 ];

	// vars for optimization
	inline vec3_t eye_pos, shoot_pos;
	inline c_base_combat_weapon* weapon;
	inline weapon_info_t* weapon_data;
}