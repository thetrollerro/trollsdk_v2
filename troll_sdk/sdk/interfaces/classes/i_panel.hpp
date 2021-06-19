#pragma once
#include "../../../utilities/utilities.hpp"

class i_panel {
public:
	const char* get_name( unsigned int vguiPanel ) {
		using fn = const char* ( __thiscall* )( void*, unsigned int );
		return utils::call_virtual<fn>( this, 36 )( this, vguiPanel );
	}

	const char* get_class_name( unsigned int vguiPanel ) {
		using fn = const char* ( __thiscall* )( void*, unsigned int );
		return utils::call_virtual<fn>( this, 37 )( this, vguiPanel );
	}
};