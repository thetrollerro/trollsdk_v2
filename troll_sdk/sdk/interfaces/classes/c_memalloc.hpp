#pragma once
struct crt_mem_state;
#define MEMALLOC_VERSION 1
typedef size_t( *mem_alloc_fail_handler_t )( size_t );

class c_memalloc
{
public:
	auto allocate( int size ) -> void* {
		using fn = void* ( __thiscall* )( void*, int );
		return utils::call_virtual< fn >( this, 1 )( this, size );
	}

	auto reallocate( void* mem, int size ) -> void* {
		using fn = void* ( __thiscall* )( void*, void*, int );
		return utils::call_virtual< fn >( this, 3 )( this, mem, size );
	}

	auto free( void* mem ) -> void {
		using fn = void( __thiscall* )( void*, void* );
		return utils::call_virtual< fn >( this, 5 )( this, mem );
	}
};