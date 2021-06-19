#define NOMINMAX
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <Psapi.h>
#include "utilities.hpp"
#include "../sdk/sdk.hpp"
#include "globals/globals.hpp"

namespace utils {

	float server_time( ) {
		return g_local->m_nTickBase( ) * i::globalvars->m_interval_per_tick;
	}

	bool can_shoot( ) {
		if ( !g_local || !g_local->is_alive( ) )
			return false;

		if ( ( g_local->m_nTickBase( ) * i::globalvars->m_interval_per_tick ) <= g_local->m_flNextAttack( ) )
			return false;

		if ( !g::weapon )
			return false;

		if ( g::weapon->is_nade( ) )
			return true;

		static float lastFire = 0, nextAttack = 0;
		static c_base_combat_weapon* old_weapon;

		if ( lastFire != g::weapon->m_fLastShotTime( ) || g::weapon != old_weapon ) {
			lastFire = g::weapon->m_fLastShotTime( );
			nextAttack = g::weapon->m_flNextPrimaryAttack( );
		}

		if ( g::weapon->m_iClip1( ) == 0 )
			return false;

		old_weapon = g::weapon;

		return ( nextAttack <= g_local->m_nTickBase( ) * i::globalvars->m_interval_per_tick );
	}

	typedef void( __cdecl* MsgFn )( char const* pMsg, va_list );
	MsgFn oMsg;
	void __cdecl dbg_print( char const* msg, ... )
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

	uintptr_t find_sig_ida( const char* module1, const char* signature )
	{
		/* antario? */
		const char* pat = signature;
		DWORD first_match = 0;
		DWORD range_start = ( DWORD ) GetModuleHandleA( module1 );
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

	unsigned int find_in_data_map( datamap_t* m_map, const char* name )
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

	DWORD find_sig_byte( const char* module_name, const BYTE* mask, const char* mask_string )
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

	bool world_to_screen( const vec3_t& origin, vec3_t& screen )
	{
		const auto screen_transform = [ &origin, &screen ] ( ) -> bool {
			static std::uintptr_t matrix;
			if ( !matrix ) {
				matrix = static_cast< std::uintptr_t >( find_sig_ida( _( "client.dll" ), _( "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9" ) ) );
				matrix += 3;
				matrix = *reinterpret_cast< std::uintptr_t* >( matrix );
				matrix += 176;
			}

			const matrix_t& w2s_matrix = *reinterpret_cast< matrix_t* >( matrix );
			screen.x = w2s_matrix.mat_val[ 0 ][ 0 ] * origin.x + w2s_matrix.mat_val[ 0 ][ 1 ] * origin.y + w2s_matrix.mat_val[ 0 ][ 2 ] * origin.z + w2s_matrix.mat_val[ 0 ][ 3 ];
			screen.y = w2s_matrix.mat_val[ 1 ][ 0 ] * origin.x + w2s_matrix.mat_val[ 1 ][ 1 ] * origin.y + w2s_matrix.mat_val[ 1 ][ 2 ] * origin.z + w2s_matrix.mat_val[ 1 ][ 3 ];
			screen.z = 0.0f;

			float w = w2s_matrix.mat_val[ 3 ][ 0 ] * origin.x + w2s_matrix.mat_val[ 3 ][ 1 ] * origin.y + w2s_matrix.mat_val[ 3 ][ 2 ] * origin.z + w2s_matrix.mat_val[ 3 ][ 3 ];

			if ( w < 0.001f ) {
				screen.x *= 100000;
				screen.y *= 100000;
				return true;
			}

			float invw = 1.f / w;
			screen.x *= invw;
			screen.y *= invw;

			return false;
		};

		if ( !screen_transform( ) ) {
			int screen_width, screen_height;
			i::engine->get_screen_size( screen_width, screen_height );

			screen.x = ( screen_width * 0.5f ) + ( screen.x * screen_width ) * 0.5f;
			screen.y = ( screen_height * 0.5f ) - ( screen.y * screen_height ) * 0.5f;

			return true;
		}

		return false;
	}

	bool visible( const vec3_t& start, const vec3_t& end, c_base_player* entity, c_base_player* from )
	{
		trace_t trace;
		trace_filter filter;
		filter.skip = from;
		//g_ctx.globals.autowalling = true;
		i::trace->trace_ray( ray_t( start, end ), mask_shot_hull | contents_hitbox, &filter, &trace );
		//g_ctx.globals.autowalling = false;
		return trace.player == entity || trace.fraction == 1.0f;
	}

}