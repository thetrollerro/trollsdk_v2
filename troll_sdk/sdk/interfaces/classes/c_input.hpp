#pragma once
#include "../../math/vector.hpp"
#include <cstring>
#include "../../../utilities/utilities.hpp"
#include "../../classes/c_usercmd.hpp"

class bf_read;
class bf_write;

class c_input {
public:
	void* pvftable {};
	bool trackir_available {};
	bool mouse_initialized {};
	bool mouse_active {};
	bool joystick_advanced_init {};
	char pad_0x08[ 0x2C ] {};
	void* keys {};
	char pad_0x38[ 0x64 ] {};
	int pad_0x41 {};
	int pad_0x42 {};
	int pad_0x43 {};
	int pad_0x44 {};
	bool camera_intercepting_mouse {};
	bool camera_in_thirdperson {};
	bool camera_moving_with_mouse {};
	vec3_t camera_offset;
	bool camera_distance_move {};
	int camera_old_x {};
	int camera_old_y {};
	int camera_x {};
	int camera_y {};
	bool camera_is_orthographic {};
	vec3_t previous_view_angles;
	vec3_t previous_view_angles_tilt;
	float last_forward_move {};
	int clear_input_state {};
	c_usercmd* commands {};
	c_verified_usercmd* verified_commands {};
	c_usercmd* get_user_cmd( int sequence_number ) {
		return &commands[ sequence_number % 150 ];
	}
	c_usercmd* get_user_cmd( int slot, int sequence_number ) {
		typedef c_usercmd* ( __thiscall* o_getusercmd )( void*, int, int );
		return utils::call_virtual <o_getusercmd>( this, 8 )( this, slot, sequence_number );
	}
	c_verified_usercmd* get_verified_user_cmd( int sequence_number ) {
		return &verified_commands[ sequence_number % 150 ];
	}
};
