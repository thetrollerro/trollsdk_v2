#pragma once
#include "i_client_unknown.hpp"
#include "i_client_renderable.hpp"
#include "i_client_networkable.hpp"
#include "i_client_thinkable.hpp"

class i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable
{
public:
	virtual void release( void ) = 0;
};