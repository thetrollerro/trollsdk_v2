#pragma once
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <initializer_list>
#include <Psapi.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "../sdk/datamap.hpp"
#include "../sdk/math/vector.hpp"
#include "security/xorstr.hpp"
#pragma comment(lib, "psapi.lib")

#define in_range(x,a,b)   (x >= a && x <= b)
#define get_bits( x )    (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (in_range(x,'0','9') ? x - '0' : 0))
#define get_byte( x )    (get_bits(x[0]) << 4 | get_bits(x[1]))
class c_base_player;

namespace utils {
	template<typename FuncType>
	__forceinline static FuncType call_virtual( void* ppClass, int index ) {
		int* pVTable = *( int** ) ppClass;
		int dwAddress = pVTable[ index ];
		return ( FuncType ) ( dwAddress );
	}

	float server_time( );
	bool can_shoot( );
	uintptr_t find_sig_ida( const char* module1, const char* signature );
	DWORD find_sig_byte( const char* module_name, const BYTE* mask, const char* mask_string );
	unsigned int find_in_data_map( datamap_t* m_map, const char* name );
	void __cdecl dbg_print( char const* msg, ... );
	bool world_to_screen( const vec3_t& origin, vec3_t& screen );
	bool visible(const vec3_t& start, const vec3_t& end, c_base_player* entity, c_base_player* from);
}