#pragma once
#include "i_client_unknown.hpp"

class i_client_thinkable
{
public:
	virtual i_client_unknown* get_client_unknown( ) = 0;
	virtual void client_think( ) = 0;
	virtual void* get_think_handle( ) = 0;
	virtual void set_think_handle( void* hThink ) = 0;
	virtual void release( ) = 0;
};