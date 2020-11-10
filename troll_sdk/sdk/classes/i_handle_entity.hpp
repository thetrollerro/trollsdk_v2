#pragma once

class i_handle_entity
{
public:
	virtual ~i_handle_entity( ) {}
	virtual void set_ref_handle( unsigned long& handle ) = 0;
	virtual unsigned long& get_ref_handle( ) const = 0;
};
