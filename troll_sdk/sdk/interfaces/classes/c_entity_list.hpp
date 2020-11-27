#pragma once
#include "../../../utilities/utilities.hpp"
class i_client_networkable;
class i_client_entity;
class c_base_handle;
class c_entity_list {
public:
	virtual i_client_networkable* get_client_networkable( int i ) = 0;
	virtual void* pad_0x1( void ) = 0;
	virtual void* pad_0x2( void ) = 0;
	virtual i_client_entity* get_client_entity( int i ) = 0;
	virtual i_client_entity* get_client_entity_from_handle( c_base_handle handle ) = 0;
	virtual int number_of_entities( bool include_non_networkable ) = 0;
	virtual int get_highest_entity_index( void ) = 0;
	virtual void set_max_entities( int max_entities ) = 0;
	virtual int get_max_entities( ) = 0;

	i_client_entity* get_client_entity_from_handle( HANDLE hEnt )
	{
		typedef i_client_entity* ( __thiscall* o_fn )( PVOID, HANDLE );
		return utils::call_virtual<o_fn>( this, 4 )( this, hEnt );
	}
};