#pragma once
#include "../math/vector.hpp"
class i_client_unknown;
class collideable_t {
public:
	virtual i_handle_entity* get_entity_handle( ) = 0;
	virtual vec3_t& mins( ) const = 0;
	virtual vec3_t& maxs( ) const = 0;
};