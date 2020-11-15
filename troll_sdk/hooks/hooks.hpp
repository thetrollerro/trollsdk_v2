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

		namespace write_usercmd_delta_to_buffer {
			bool __fastcall hook( void* ecx, void* edx, int slot, bf_write* buf, int from, int to, bool is_new_cmd );
			using fn = bool( __fastcall* )( void*, void*, int, bf_write*, int, int, bool );
		}
	}

	namespace clientmode {
		namespace do_post_screen_effects {
			int __fastcall hook( void* ecx, void* edx, int a );
			using fn = int( __fastcall* )( void*, void*, int );
		}

		namespace override_view {
			void __fastcall hook( void* ecx, void* edx, view_setup_t* view );
			using fn = void( __fastcall* )( void*, void*, view_setup_t* );
		}
	}

	namespace dx9 {
		namespace endscene {
			long __fastcall hook( void* ecx, void* edx, IDirect3DDevice9* dev );
			using fn = long( __fastcall* )( void*, void*, IDirect3DDevice9* );
		}

		namespace reset {
			long __fastcall hook( void* ecx, void* edx, IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params );
			using fn = long( __fastcall* )( void*, void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
		}

		namespace wndproc {
			long __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
		}
	}

	namespace engine {
		namespace fire_game_event {
			void __fastcall hook( void* ecx, void* edx );
			using fn = void( __fastcall* )( void*, void* );
		}

		namespace is_hltv {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}
	}

	namespace modelrender {
		namespace draw_model_exec {
			void __fastcall hook( void* ecx, void* edx, void* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* custom_bone_to_world = nullptr );
			using fn = void( __fastcall* )( void*, void*, void*, const draw_model_state_t&, const model_render_info_t&, matrix_t* );
		}
	}

	namespace players {
		namespace build_transformations {
			void __fastcall hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
			using fn = void( __fastcall* )( void*, void*, int, int, int, int, int, int );
		}

		namespace do_extra_bones_processing {
			void __fastcall hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
			using fn = void( __fastcall* )( void*, void*, int, int, int, int, int, int );
		}

		namespace get_eye_ang {
			vec3_t* __fastcall hook( void* ecx, void* edx );
			using fn = vec3_t * ( __fastcall* )( void*, void* );
		}

		namespace setup_bones {
			bool __fastcall hook( void* ecx, void* edx, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float curtime );
			using fn = bool( __fastcall* )( void*, void*, matrix_t*, int, int, float );
		}

		namespace standard_blending_rules {
			void __fastcall hook( void* ecx, void* edx, studio_hdr_t* hdr, vec3_t* pos, quaternion* q, float curtime, int mask );
			using fn = void( __fastcall* )( void*, void*, studio_hdr_t*, vec3_t*, quaternion*, float, int );
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
inline hooks::clientdll::write_usercmd_delta_to_buffer::fn o_write_usercmd_delta_to_buffer = nullptr;
inline hooks::clientmode::do_post_screen_effects::fn o_do_post_screen_effects = nullptr;
inline hooks::clientmode::override_view::fn o_override_view = nullptr;
inline hooks::dx9::endscene::fn o_endscene = nullptr;
inline hooks::dx9::reset::fn o_reset = nullptr;
inline hooks::engine::fire_game_event::fn o_fire_game_event = nullptr;
inline hooks::engine::is_hltv::fn o_is_hltv = nullptr;
inline hooks::modelrender::draw_model_exec::fn o_draw_model_exec = nullptr;
inline hooks::players::build_transformations::fn o_build_transformations = nullptr;
inline hooks::players::do_extra_bones_processing::fn o_do_extra_bones_processing = nullptr;
inline hooks::players::get_eye_ang::fn o_get_eye_ang = nullptr;
inline hooks::players::setup_bones::fn o_setup_bones = nullptr;
inline hooks::players::standard_blending_rules::fn o_standard_blending_rules = nullptr;
inline hooks::surface::lock_cursor::fn o_lock_cursor = nullptr;