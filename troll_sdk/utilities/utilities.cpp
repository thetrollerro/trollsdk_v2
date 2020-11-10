#define NOMINMAX
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <Psapi.h>
#include "utilities.hpp"

typedef void( __cdecl* MsgFn )( char const* pMsg, va_list );
MsgFn oMsg;
void __cdecl utils::dbg_print( char const* msg, ... )
{
	if ( !oMsg )
		oMsg = ( MsgFn ) GetProcAddress( GetModuleHandleA( ( "tier0.dll" ) ), ( "Msg" ) );

	char buffer[ 989 ];
	va_list list;
	va_start( list, msg );
	vsprintf_s( buffer, msg, list );
	va_end( list );
	oMsg( buffer, list );
}

uintptr_t utils::find_sig_ida( const char* module, const char* signature )
{
	/* antario? */
	const char* pat = signature;
	DWORD first_match = 0;
	DWORD range_start = ( DWORD ) GetModuleHandleA( module );
	MODULEINFO module_info;
	GetModuleInformation( GetCurrentProcess( ), reinterpret_cast< HMODULE >( range_start ), &module_info, sizeof( MODULEINFO ) );
	DWORD range_end = range_start + module_info.SizeOfImage;
	for ( DWORD pCur = range_start; pCur < range_end; pCur++ )
	{
		if ( !*pat )
			return first_match;

		if ( *( PBYTE ) pat == '\?' || *( BYTE* ) pCur == get_byte( pat ) )
		{
			if ( !first_match )
				first_match = pCur;

			if ( !pat[ 2 ] )
				return first_match;

			if ( *( PWORD ) pat == '\?\?' || *( PBYTE ) pat != '\?' )
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = signature;
			first_match = 0;
		}
	}
	return NULL;
}

unsigned int utils::find_in_data_map( datamap_t* m_map, const char* name )
{
	while ( m_map )
	{
		for ( int i = 0; i < m_map->data_fields; i++ )
		{
			if ( m_map->data_description[ i ].field_name == NULL )
				continue;

			if ( strcmp( name, m_map->data_description[ i ].field_name ) == 0 )
				return m_map->data_description[ i ].field_offset[ 0 ];

			if ( m_map->data_description[ i ].field_type == 10 )
			{
				if ( m_map->data_description[ i ].td )
				{
					unsigned int offset;

					if ( ( offset = find_in_data_map( m_map->data_description[ i ].td, name ) ) != 0 )
						return offset;
				}
			}
		}
		m_map = m_map->base_map;
	}

	return 0;
}

DWORD utils::find_sig_byte( const char* module_name, const BYTE* mask, const char* mask_string )
{
	/* get module addresses */
	const unsigned int module_address = reinterpret_cast< unsigned int >( GetModuleHandleA( module_name ) );

	/// Get module information to the size
	MODULEINFO module_info;
	GetModuleInformation( GetCurrentProcess( ), reinterpret_cast< HMODULE >( module_address ), &module_info, sizeof( MODULEINFO ) );

	auto is_correct_mask = [ ] ( const unsigned char* data, const unsigned char* mask, const char* mask_string ) -> bool
	{
		for ( ; *mask_string; ++mask_string, ++mask, ++data )
			if ( *mask_string == 'x' && *mask != *data )
				return false;

		return ( *mask_string ) == 0;
	};

	/// Iterate until we find a matching mask
	for ( unsigned int c = 0; c < module_info.SizeOfImage; c += 1 )
	{
		/// does it match?
		if ( is_correct_mask( reinterpret_cast< unsigned char* >( module_address + c ), mask, mask_string ) )
			return ( module_address + c );
	}

	return 0;
}