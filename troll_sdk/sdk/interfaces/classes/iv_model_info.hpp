#pragma once
#include "../../models.hpp"
#include "../../../utilities/utilities.hpp"

class iv_model_info {
public:
	model_t* get_model( int index ) {
		using o_fn = model_t * ( __thiscall* )( iv_model_info*, int );
		return utils::call_virtual<o_fn>( this, 1 )( this, index );
	}
	int get_model_index( const char* filename ) {
		using o_fn = int( __thiscall* )( iv_model_info*, const char* );
		return utils::call_virtual<o_fn>( this, 2 )( this, filename );
	}
	const char* get_model_name( const void* model ) {
		using o_fn = const char* ( __thiscall* )( iv_model_info*, const void* );
		return utils::call_virtual<o_fn>( this, 3 )( this, model );
	}
	studio_hdr_t* get_studio_model( const model_t* model ) {
		using o_fn = studio_hdr_t * ( __thiscall* )( iv_model_info*, const model_t* );
		return utils::call_virtual<o_fn>( this, 32 )( this, model );
	}
};