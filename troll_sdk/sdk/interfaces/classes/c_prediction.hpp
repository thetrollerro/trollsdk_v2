#pragma once
#include "../../../utilities/utilities.hpp"
#include "../../math/vector.hpp"
#include "../../classes/c_usercmd.hpp"

class c_base_player;
class c_move_helper;
class c_prediction {
public:
	void get_local_viewangles( vec3_t& angle ) {
		using fn = void( __thiscall* )( void*, vec3_t& );
		utils::call_virtual< fn >( this, 12 )( this, angle );
	}

	void set_local_viewangles( vec3_t& angle ) {
		using fn = void( __thiscall* )( void*, vec3_t& );
		utils::call_virtual< fn >( this, 13 )( this, angle );
	}

	void update( int start_frame, bool valid_frame, int inc_ack, int out_cmd ) {
		using fn = void( __thiscall* )( void*, int, bool, int, int );
		utils::call_virtual< fn >( this, 3 )( this, start_frame, valid_frame, inc_ack, out_cmd );
	}

	void check_moving_ground( c_base_player* player, double frametime ) {
		using fn = void( __thiscall* )( void*, c_base_player*, double );
		utils::call_virtual< fn >( this, 18 )( this, player, frametime );
	}

	void run_command( c_base_player* player, c_usercmd* ucmd, c_move_helper* moveHelper ) {
		typedef void( __thiscall* fn )( void*, c_base_player*, c_usercmd*, c_move_helper* );
		utils::call_virtual< fn >( this, 19 )( this, player, ucmd, moveHelper );
	}

	void setup_move( c_base_player* player, c_usercmd* ucmd, c_move_helper* helper, void* movedata ) {
		using fn = void( __thiscall* )( void*, c_base_player*, c_usercmd*, c_move_helper*, void* );
		utils::call_virtual< fn >( this, 20 )( this, player, ucmd, helper, movedata );
	}

	void finish_move( c_base_player* player, c_usercmd* ucmd, void* movedata ) {
		using fn = void( __thiscall* )( void*, c_base_player*, c_usercmd*, void* );
		utils::call_virtual< fn >( this, 21 )( this, player, ucmd, movedata );
	}

	uint8_t pad_0x1[ 0x8 ];
	bool m_in_prediction;
	uint8_t pad_0x2[ 0x1 ];
	bool m_engine_paused;
	uint8_t pad_0x3[ 13 ];
	bool m_is_first_time_predicted;
};