#pragma once
#include "../../../utilities/utilities.hpp"

class i_localize {
public:
	wchar_t* find( const char* token_name ) {
		using fn = wchar_t* ( __thiscall* )( i_localize*, const char* );
		return utils::call_virtual< fn >( this, 11 )( this, token_name );
	}
};