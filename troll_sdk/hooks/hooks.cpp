#include "hooks.hpp"
#include <thread>

void hooks::init( ) {
	while ( !( csgo_window = FindWindowA( "Valve001", nullptr ) ) ) {
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for( 50ms );
	}

	/* create fonts */
	render::create_fonts( );

	/* get local player */
	g_local = *( c_local_player* ) ( utils::find_sig_ida( "client.dll", "8B 0D ? ? ? ? 83 FF FF 74 07" ) + 2 );

	/* hook wproc */
	o_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( csgo_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( dx9::wndproc::hook ) ) );

	/* get targets */
	auto create_move_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 EC 08 FF 15 ? ? ? ? 84 C0" ); // 22
	auto frame_stage_notify_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 80 74 01 00 00 FF D0 A2" ); // 37
	auto write_usercmd_delta_to_buffer_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 EC 68 53 56 8B D9 C7 45" ); // 24
	auto do_post_screen_effects_target = ( void* ) get_virtual( i::clientmode, 44 ); // 44
	auto override_view_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ? 85 FF" ); // 18
	auto endscene_target = ( void* ) get_virtual( i::dx9, 42 ); // 42
	auto reset_target = ( void* ) get_virtual( i::dx9, 16 ); // 16
	auto fire_game_event_target = ( void* ) get_virtual( i::engine, 59 );
	auto is_hltv_target = ( void* ) get_virtual( i::engine, 93 );
	auto draw_model_exec_target = ( void* ) utils::find_sig_ida( "engine.dll", "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 56 8B 75 10" ); // 21
	auto build_transformations_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F0 81 EC ? ? ? ? 56 57 8B F9 8B 0D ? ? ? ? 89 7C 24 1C" );
	auto do_extra_bones_processing_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 81 EC FC 00 00 00 53 56 8B F1 57" ); // 197
	auto get_eye_ang_target = ( void* ) utils::find_sig_ida( "client.dll", "56 8B F1 85 F6 74 32" ); // idk
	auto setup_bones_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9" ); // 13
	auto standard_blending_rules_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 8B 75 08 57 8B F9 85 F6" );
	auto lock_cursor_target = ( void* ) utils::find_sig_ida( "vguimatsurface.dll", "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01" ); // 67

	/* init mh */
	MH_Initialize( );

	/* do our hooks */
	MH_CreateHook( create_move_target, clientdll::create_move::hook, ( void** ) &o_create_move );
	MH_CreateHook( frame_stage_notify_target, clientdll::frame_stage_notify::hook, ( void** ) &o_frame_stage_notify );
	MH_CreateHook( write_usercmd_delta_to_buffer_target, clientdll::write_usercmd_delta_to_buffer::hook, ( void** ) &o_write_usercmd_delta_to_buffer );
	MH_CreateHook( do_post_screen_effects_target, clientmode::do_post_screen_effects::hook, ( void** ) &o_do_post_screen_effects );
	MH_CreateHook( override_view_target, clientmode::override_view::hook, ( void** ) &o_override_view );
	MH_CreateHook( endscene_target, dx9::endscene::hook, ( void** ) &o_endscene );
	MH_CreateHook( reset_target, dx9::reset::hook, ( void** ) &o_reset );
	MH_CreateHook( fire_game_event_target, engine::fire_game_event::hook, ( void** ) &o_fire_game_event );
	MH_CreateHook( is_hltv_target, engine::is_hltv::hook, ( void** ) &o_is_hltv );
	MH_CreateHook( draw_model_exec_target, modelrender::draw_model_exec::hook, ( void** ) &o_draw_model_exec );
	MH_CreateHook( build_transformations_target, players::build_transformations::hook, ( void** ) &o_build_transformations );
	MH_CreateHook( do_extra_bones_processing_target, players::do_extra_bones_processing::hook, ( void** ) &o_do_extra_bones_processing );
	MH_CreateHook( get_eye_ang_target, players::get_eye_ang::hook, ( void** ) &o_get_eye_ang );
	MH_CreateHook( setup_bones_target, players::setup_bones::hook, ( void** ) &o_setup_bones );
	MH_CreateHook( standard_blending_rules_target, players::standard_blending_rules::hook, ( void** ) &o_standard_blending_rules );
	MH_CreateHook( lock_cursor_target, surface::lock_cursor::hook, ( void** ) &o_lock_cursor );

	/* enable mhs */
	MH_EnableHook( nullptr );

	/* init events */
	event_mgr.initialize( );
}

void hooks::restore( ) {
	MH_RemoveHook( MH_ALL_HOOKS );
	MH_Uninitialize( );

	/* animate again */
	if ( g_local )
		g_local->m_bClientSideAnimation( ) = true;

	/* shutdown imgui */
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );

	/* restore events */
	event_mgr.restore( );

	/* restore wnd_proc */
	SetWindowLongA( csgo_window, GWLP_WNDPROC, long( o_wndproc ) );
}

