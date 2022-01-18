#pragma once
#include "../../math/vector.hpp"
#include <cstring>
#include "../../../utilities/utilities.hpp"
#include "../../classes/c_usercmd.hpp"

class bf_read;
class bf_write;

class c_input {
public:
	char pad_0000[ 0xC ];
	bool trackir_available;
	bool mouse_initialized;
	bool mouse_active;
	char pad_0x08[ 0x9E ];
	bool camera_in_thirdperson;
	char pad_00C3[ 0x2 ];
	vec3_t camera_offset;
	char pad_00D1[ 0x38 ];
	c_usercmd* commands;
	c_verified_usercmd* verified_commands;
	c_usercmd* get_user_cmd( int sequence_number ) {
		typedef c_usercmd* ( __thiscall* o_getusercmd )( void*, int, int );
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
