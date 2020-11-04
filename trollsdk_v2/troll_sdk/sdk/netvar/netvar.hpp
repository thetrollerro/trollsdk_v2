#pragma once
#include <windows.h>
#include <SDKDDKVer.h>
#include <string.h>
#include <vadefs.h>
#include <stdio.h>
#include <xstring>
#include <Psapi.h>
#include <thread>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <time.h>
#include <winuser.h>
#include <random>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>
#include <thread>
#include <array>
#include <assert.h>
#include <deque>
#include <intrin.h>
#include <atomic>
#include <mutex>
#include <stdint.h>
#include <stdlib.h>
#include <process.h>
#include <Wincon.h>
#include <cstdint>
#include <chrono>
#include <Shlobj.h>
#include <future>
#include <Lmcons.h>
#include <tchar.h>
#include "../../sdk/structs.hpp"

#define NETVAR(name, func_name, type) \
type& func_name( ) { \
    return *(type*)( uintptr_t( this ) + netvars::get_offset( name ) ); \
} 

#define NETVAR_PTR(name, func_name, type) \
type* func_name( ) { \
    return (type*)( uintptr_t( this ) + netvars::get_offset(name ) ); \
} 

#define OFFSET(type, var, offset) \
type& var() { \
	return *(type*)(uintptr_t(this) + offset); \
} 

#define OFFSET_PTR(type, var, offset) \
type*& var() { \
	return *(type**)(uintptr_t(this) + offset); \
} 

#define NETVAR_OFFSET(  name, off, func, type ) \
type& func( ) { \
	static auto offset = netvars::get_offset( name ); \
	return *( type* ) ( uintptr_t( this ) + offset + off ); \
} 

namespace netvars {
	struct netvar_data_t {
		bool m_datamap_var; // we can't do proxies on stuff from datamaps :).
		recv_prop* m_prop_ptr;
		std::size_t m_offset;

		netvar_data_t( ) : m_datamap_var { }, m_prop_ptr { }, m_offset { } { }
	};

	extern std::unordered_map< std::string, int > m_client_ids;
	extern std::unordered_map< std::string, std::unordered_map< std::string, netvar_data_t > > m_offsets;

	bool init( );
	void store_table( const std::string& name, recv_table* table, std::size_t offset = 0 );
	int get_client_id( const std::string& network_name );
	int get( const std::string& table, const std::string& prop );
	int get_offset( const char* name );
}