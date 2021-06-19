#pragma once
#include <windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "classes/c_entity_list.hpp"
#include "classes/c_file_system.hpp"
#include "classes/c_game_movement.hpp"
#include "classes/c_global_vars.hpp"
#include "classes/c_glow_object_manager.hpp"
#include "classes/c_input.hpp"
#include "classes/c_input_system.hpp"
#include "classes/c_memalloc.hpp"
#include "classes/c_move_helper.hpp"
#include "classes/c_prediction.hpp"
#include "classes/i_app_system.hpp"
#include "classes/i_client_dll.hpp"
#include "classes/i_client_mode.hpp"
#include "classes/i_client_state.hpp"
#include "classes/i_cvar.hpp"
#include "classes/i_engine_sound.hpp"
#include "classes/i_game_event_manager.hpp"
#include "classes/i_localize.hpp"
#include "classes/i_material_system.hpp"
#include "classes/i_panel.hpp"
#include "classes/i_surface.hpp"
#include "classes/i_surface_props.hpp"
#include "classes/i_trace.hpp"
#include "classes/iv_debug_overlay.hpp"
#include "classes/iv_engine_client.hpp"
#include "classes/iv_model_info.hpp"
#include "classes/iv_model_render.hpp"
#include "classes/iv_view_render_beams.hpp"
#include <d3d9.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

namespace i {
	/* credits: gladiatorcheatz */
	class interface_reg
	{
	private:
		using InstantiateInterfaceFn = void* ( * )( );
	public:
		InstantiateInterfaceFn create_fn;
		const char* name;
		interface_reg* next;
	};

	template<typename T>
	static T* get_interface( const char* modName, const char* ifaceName, bool exact = false )
	{
		T* i_interface = nullptr;
		interface_reg* interface_reg_list;
		int partMatchLen = strlen( ifaceName );

		DWORD interface_fn = reinterpret_cast< DWORD >( GetProcAddress( GetModuleHandleA( modName ), "CreateInterface" ) );

		if ( !interface_fn )
			return nullptr;

		unsigned int jmp_start = ( unsigned int ) ( interface_fn ) +4;
		unsigned int jmp_target = jmp_start + *( unsigned int* ) ( jmp_start + 1 ) + 5;

		interface_reg_list = **reinterpret_cast< interface_reg*** >( jmp_target + 6 );

		for ( interface_reg* cur = interface_reg_list; cur; cur = cur->next )
		{
			if ( exact == true )
			{
				if ( strcmp( cur->name, ifaceName ) == 0 )
					i_interface = reinterpret_cast< T* >( cur->create_fn( ) );
			}
			else
			{
				if ( !strncmp( cur->name, ifaceName, partMatchLen ) && std::atoi( cur->name + partMatchLen ) > 0 )
					i_interface = reinterpret_cast< T* >( cur->create_fn( ) );
			}
		}
		return i_interface;
	}

	/* do interfaces here */
	inline c_entity_list* entitylist;
	inline c_file_system* file_system;
	inline c_game_movement* game_movement;
	inline c_global_vars* globalvars;
	inline c_glow_object_manager* glow_manager;
	inline c_input* input;
	inline c_input_system* input_system;
	inline c_memalloc* memalloc;
	inline c_move_helper* movehelper;
	inline c_prediction* prediction;
	inline i_client_dll* clientdll;
	inline i_client_mode* clientmode;
	inline i_client_state* clientstate;
	inline i_cvar* cvar;
	inline i_engine_sound* engine_sound;
	inline i_game_event_manager* event_manager;
	inline i_localize* localize;
	inline i_material_system* material_system;
	inline i_panel* panel;
	inline i_surface* surface;
	inline i_surface_props* surface_props;
	inline i_trace* trace;
	inline iv_debug_overlay* debug_overlay;
	inline iv_engine_client* engine;
	inline iv_model_info* modelinfo;
	inline iv_model_render* modelrender;
	inline iv_view_render_beams* render_beams;
	inline IDirect3DDevice9* dx9;

	void init( );
}

constexpr int time2ticks( float t ) {
	return static_cast< int >( t / i::globalvars->m_interval_per_tick + 0.5f );
}

constexpr float ticks2time( int t ) {
	return static_cast< float >( t ) * i::globalvars->m_interval_per_tick;
}

inline std::string ws2s( const std::wstring& s )
{
	int len;
	int slength = ( int ) s.length( ) + 1;
	len = WideCharToMultiByte( CP_ACP, 0, s.c_str( ), slength, 0, 0, 0, 0 );
	std::string r( len, '\0' );
	WideCharToMultiByte( CP_ACP, 0, s.c_str( ), slength, &r[ 0 ], len, 0, 0 );
	return r;
}