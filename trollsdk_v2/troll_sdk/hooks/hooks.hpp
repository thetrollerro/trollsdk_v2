#pragma once
#include "../main.hpp"
#include "../utilities/minhook/minhook.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace hooks {
	inline unsigned int get_virtual( void* _class, unsigned int index ) {
		return static_cast< unsigned int >( ( *reinterpret_cast< int** >( _class ) )[ index ] );
	}

	namespace clientdll {
		namespace create_move {
			void __fastcall call( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active, bool& send_packet );
			void __fastcall hook( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active, bool& send_packet );
			using fn = void( __fastcall* )( void*, void*, int, float, bool, bool& );
		}

		namespace frame_stage_notify {
			void __fastcall hook( void* ecx, void* edx, int stage );
			using fn = void( __fastcall* )( void*, void*, int );
		}
	}

	namespace clientmode {
		namespace override_view {
			void __fastcall hook( void* ecx, void* edx, view_setup_t* view );
			using fn = void( __fastcall* )( void*, void*, view_setup_t* );
		}
	}

	namespace dx9 {
		namespace endscene {
			long __stdcall hook( IDirect3DDevice9* dev );
			using fn = long( __stdcall* )( IDirect3DDevice9* );
		}

		namespace reset {
			long __stdcall hook( IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params );
			using fn = long( __stdcall* )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
		}

		namespace wndproc {
			long __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
		}
	}

	namespace players {
		namespace get_eye_ang {
			vec3_t* __fastcall hook( void* ecx, void* edx );
			using fn = vec3_t * ( __fastcall* )( void*, void* );
		}
	}

	namespace surface {
		namespace lock_cursor {
			void __fastcall hook( void* ecx, void* edx );
			using fn = void( __fastcall* )( void*, void* );
		}
	}

	inline HWND csgo_window = nullptr;
	inline WNDPROC o_wndproc = nullptr;
	void init( );
	void restore( );
}

inline hooks::clientdll::create_move::fn o_create_move = nullptr;
inline hooks::clientdll::frame_stage_notify::fn o_frame_stage_notify = nullptr;
//inline hooks::clientmode::create_move::fn o_create_move = nullptr;
inline hooks::clientmode::override_view::fn o_override_view = nullptr;
inline hooks::dx9::endscene::fn o_endscene = nullptr;
inline hooks::dx9::reset::fn o_reset = nullptr;
inline hooks::players::get_eye_ang::fn o_get_eye_ang = nullptr;
inline hooks::surface::lock_cursor::fn o_lock_cursor = nullptr;