#pragma once
#include "../../../utilities/utilities.hpp"

class i_localize {
public:
	char* find( const char* token_name ) {
		using original_fn = char* ( __thiscall* )( i_localize*, const char* );
		return ( *( original_fn** ) this )[ 11 ]( this, token_name );
	}
};