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

	namespace animstate {
		namespace do_procedual_foot_plant {
			void __fastcall hook( void* ecx, void* edx, matrix_t* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos );
			using fn = void( __fastcall* )( void*, void*, matrix_t*, void*, void*, void* );
		}

		namespace modify_eye_position {
			void __fastcall hook( void* ecx, void* edx, vec3_t& input_eye_position );
			using fn = void( __fastcall* )( void*, void*, vec3_t& );
		}
	}

	namespace bsp_tree_query {
		namespace insert_into_tree {
			void __fastcall hook( void* ecx, void* edx, vec3_t* mins, vec3_t* maxs );
			using fn = void( __fastcall* )( void*, void*, vec3_t*, vec3_t* );
		}

		namespace list_leaves_in_box {
			int __fastcall hook( void* ecx, void* edx, vec3_t& mins, vec3_t& maxs, unsigned short* list, int list_max );
			using fn = int( __fastcall* )( void*, void*, const vec3_t&, const vec3_t&, unsigned short*, int );
		}
	}

	namespace clientdll {
		namespace create_move {
			void __stdcall call( int sequence_number, float sample_frametime, bool active, bool& send_packet );
			void __fastcall hook( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active );
			using fn = void( __stdcall* )( int, float, bool );
		}

		namespace frame_stage_notify {
			void __fastcall hook( void* ecx, void* edx, int stage );
			using fn = void( __fastcall* )( void*, void*, int );
		}
	}

	namespace clientmode {
		namespace do_post_screen_effects {
			int __fastcall hook( void* ecx, void* edx, int a );
			using fn = int( __fastcall* )( void*, void*, int );
		}

		namespace get_viewmodel_fov {
			float __fastcall hook( void* ecx, void* edx );
			using fn = float( __fastcall* )( void*, void* );
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

		namespace present {
			long __fastcall hook( void* ecx, void* edx, IDirect3DDevice9* dev, RECT* source_rect, RECT* dust_rect, HWND dest_window_override, RGNDATA* dirty_region );
			using fn = long( __fastcall* )( void*, void*, IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA* );
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
		namespace cl_move {
			void __cdecl hook( float accumulated_extra_samples, bool final_tick );
			using fn = void( __cdecl* )( float, bool );
		}

		namespace fire_game_event {
			void __fastcall hook( void* ecx, void* edx );
			using fn = void( __fastcall* )( void*, void* );
		}

		namespace get_viewangles {
			void __fastcall hook( void* ecx, void* edx, vec3_t& ang );
			using fn = void( __fastcall* )( void*, void*, vec3_t& );
		}

		namespace is_connected {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}

		namespace is_hltv {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}

		namespace is_in_game {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}

		namespace is_paused {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}
	}

	namespace engine_sound {
		namespace emit_sound_1 {
			void __fastcall hook( void* ecx, void* edx, i_recipient_filter& filter, int ent_index, int channel, const char* sound_entry, unsigned int sound_entry_hash, const char* sample, float volume, int seed, float attenuation, int flags, int pitch, const vec3_t* origin, const vec3_t* direction, void* utl_vec_origins, bool update_positions, float sound_time, int speaker_entity, int unk );
			using fn = void( __fastcall* )( void*, void*, i_recipient_filter&, int, int, const char*, unsigned int, const char*, float, int, float, int, int, const vec3_t*, const vec3_t*, void*, bool, float, int, int );
		}
	}

	namespace file_system {
		namespace sv_pure_loose_file_allowed {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}
	}

	namespace game {
		namespace check_for_sequence_change {
			void __fastcall hook( void* ecx, void* edx, void* hdr, int cur_sequence, bool force_new_sequence, bool interpolate );
			using fn = void( __fastcall* )( void*, void*, void*, int, bool, bool );
		}

		namespace should_skip_animframe {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}

		namespace sv_cheats_get_bool {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}
	}

	namespace material_system {
		namespace find_material {
			i_material* __fastcall hook( void* ecx, void* edx, const char* mat_name, const char* group_name, bool complain, const char* complain_prefix );
			using fn = i_material * ( __fastcall* )( void*, void*, const char*, const char*, bool, const char* );
		}
	}

	namespace modelrender {
		namespace draw_model_exec {
			void __fastcall hook( void* ecx, void* edx, void* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* custom_bone_to_world = nullptr );
			using fn = void( __fastcall* )( void*, void*, void*, const draw_model_state_t&, const model_render_info_t&, matrix_t* );
		}
	}

	namespace net_channel {
		namespace process_packet {
			void __cdecl hook( void* packet, bool header );
			using fn = void( __cdecl* )( void*, bool );
		}

		namespace send_datagram {
			int __fastcall hook( void* ecx, void* edx, void* data );
			using fn = int( __fastcall* )( void*, void*, void* );
		}

		namespace send_net_message {
			bool __fastcall hook( void* ecx, void* edx, i_net_message& message, bool force_reliable, bool voice );
			using fn = bool( __fastcall* )( void*, void*, i_net_message&, bool, bool );
		}
	}

	namespace panel {
		namespace paint_traverse {
			void __fastcall hook( void* panels, void* edx, vgui::vpanel vgui_panel, bool force_repaint, bool allow_force );
			using fn = void( __fastcall* )( void*, void*, vgui::vpanel, bool, bool );
		}
	}

	namespace players {
		namespace build_transformations {
			void __fastcall hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
			using fn = void( __fastcall* )( void*, void*, int, int, int, int, int, int );
		}

		namespace calc_view {
			void __fastcall hook( void* ecx, void* edx, vec3_t& eye_origin, vec3_t& eye_angles, float& m_near, float& m_far, float& fov );
			using fn = void( __fastcall* )( void*, void*, vec3_t&, vec3_t&, float&, float&, float& );
		}

		namespace do_extra_bones_processing {
			void __fastcall hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
			using fn = void( __fastcall* )( void*, void*, int, int, int, int, int, int );
		}

		namespace get_eye_ang {
			vec3_t* __fastcall hook( void* ecx, void* edx );
			using fn = vec3_t * ( __fastcall* )( void*, void* );
		}

		namespace standard_blending_rules {
			void __fastcall hook( void* ecx, void* edx, studio_hdr_t* hdr, vec3_t* pos, quaternion* q, float curtime, int mask );
			using fn = void( __fastcall* )( void*, void*, studio_hdr_t*, vec3_t*, quaternion*, float, int );
		}

		namespace update_clientside_animations {
			void __fastcall hook( void* ecx, void* edx );
			using fn = void( __fastcall* )( void*, void* );
		}
	}

	namespace prediction {
		namespace in_prediction {
			bool __fastcall hook( void* ecx, void* edx );
			using fn = bool( __fastcall* )( void*, void* );
		}

		namespace perform_prediction {
			bool __fastcall hook( void* ecx, void* edx, int slot, c_base_player* pl, bool recived_world_update, int incoming_acknowledged, int outgoing_command );
			using fn = bool( __fastcall* )( void*, void*, int, c_base_player*, bool, int, int );
		}

		namespace run_command {
			void __fastcall hook( void* ecx, void* edx, c_base_player* e, c_usercmd* cmd, void* move_helper );
			using fn = void( __fastcall* )( void*, void*, c_base_player*, c_usercmd*, void* );
		}

		namespace setup_move {
			void __fastcall hook( void* ecx, void* edx, c_base_player* e, c_usercmd* cmd, c_move_helper* move_helper, c_movedata* move_data );
			using fn = void( __fastcall* )( void*, void*, c_base_player*, c_usercmd*, void*, void* );
		}
	}

	namespace renderable {
		namespace setup_bones {
			bool __fastcall hook( void* ecx, void* edx, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float curtime );
			using fn = bool( __fastcall* )( void*, void*, matrix_t*, int, int, float );
		}
	}

	namespace surface {
		namespace draw_set_color {
			void __fastcall hook( void* ecx, void* edx, int r, int g, int b, int a );
			using fn = void( __fastcall* )( void*, void*, int, int, int, int );
		}

		namespace lock_cursor {
			void __fastcall hook( void* ecx, void* edx );
			using fn = void( __fastcall* )( void*, void* );
		}
	}

	inline HWND csgo_window = nullptr;
	void init( );
	void restore( );
}

inline hooks::animstate::do_procedual_foot_plant::fn o_do_procedual_foot_plant = nullptr;
inline hooks::animstate::modify_eye_position::fn o_modify_eye_position = nullptr;
inline hooks::bsp_tree_query::insert_into_tree::fn o_insert_into_tree = nullptr;
inline hooks::bsp_tree_query::list_leaves_in_box::fn o_list_leaves_in_box = nullptr;
inline hooks::clientdll::create_move::fn o_create_move = nullptr;
inline hooks::clientdll::frame_stage_notify::fn o_frame_stage_notify = nullptr;
inline hooks::clientmode::do_post_screen_effects::fn o_do_post_screen_effects = nullptr;
inline hooks::clientmode::get_viewmodel_fov::fn o_get_viewmodel_fov = nullptr;
inline hooks::clientmode::override_view::fn o_override_view = nullptr;
inline hooks::dx9::endscene::fn o_endscene = nullptr;
inline hooks::dx9::present::fn o_present = nullptr;
inline hooks::dx9::reset::fn o_reset = nullptr;
inline WNDPROC o_wndproc = nullptr;
inline hooks::engine::cl_move::fn o_cl_move = nullptr;
inline hooks::engine::fire_game_event::fn o_fire_game_event = nullptr;
inline hooks::engine::get_viewangles::fn o_get_viewangles = nullptr;
inline hooks::engine::is_connected::fn o_is_connected = nullptr;
inline hooks::engine::is_hltv::fn o_is_hltv = nullptr;
inline hooks::engine::is_in_game::fn o_is_in_game = nullptr;
inline hooks::engine::is_paused::fn o_is_paused = nullptr;
inline hooks::engine_sound::emit_sound_1::fn o_emit_sound_1 = nullptr;
inline hooks::file_system::sv_pure_loose_file_allowed::fn o_sv_pure_loose_file_allowed = nullptr;
inline hooks::game::check_for_sequence_change::fn o_check_for_sequence_change = nullptr;
inline hooks::game::should_skip_animframe::fn o_should_skip_animframe = nullptr;
inline hooks::game::sv_cheats_get_bool::fn o_sv_cheats_get_bool = nullptr;
inline hooks::material_system::find_material::fn o_find_material = nullptr;
inline hooks::modelrender::draw_model_exec::fn o_draw_model_exec = nullptr;
inline hooks::net_channel::process_packet::fn o_process_packet = nullptr;
inline hooks::net_channel::send_datagram::fn o_send_datagram = nullptr;
inline hooks::net_channel::send_net_message::fn o_send_net_message = nullptr;
inline hooks::panel::paint_traverse::fn o_paint_traverse = nullptr;
inline hooks::players::build_transformations::fn o_build_transformations = nullptr;
inline hooks::players::calc_view::fn o_calc_view = nullptr;
inline hooks::players::do_extra_bones_processing::fn o_do_extra_bones_processing = nullptr;
inline hooks::players::get_eye_ang::fn o_get_eye_ang = nullptr;
inline hooks::players::standard_blending_rules::fn o_standard_blending_rules = nullptr;
inline hooks::players::update_clientside_animations::fn o_update_clientside_animations = nullptr;
inline hooks::prediction::in_prediction::fn o_in_prediction = nullptr;
inline hooks::prediction::perform_prediction::fn o_perform_prediction = nullptr;
inline hooks::prediction::run_command::fn o_run_command = nullptr;
inline hooks::prediction::setup_move::fn o_setup_move = nullptr;
inline hooks::renderable::setup_bones::fn o_setup_bones = nullptr;
inline hooks::surface::draw_set_color::fn o_draw_set_color = nullptr;
inline hooks::surface::lock_cursor::fn o_lock_cursor = nullptr;