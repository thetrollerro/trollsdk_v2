#include "hooks.hpp"
#include <thread>

void hooks::init( ) {
	while ( !( csgo_window = FindWindowA( "Valve001", nullptr ) ) ) {
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for( 50ms );
	}

	g_local = *( c_local_player* ) ( utils::find_sig_ida( "client.dll", "8B 0D ? ? ? ? 83 FF FF 74 07" ) + 2 );

	o_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( csgo_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( dx9::wndproc::hook ) ) );

	auto create_move_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 EC 08 FF 15 ? ? ? ? 84 C0" )/*get_virtual( i::clientdll, 22 )*/; // 22
	auto frame_stage_notify_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 80 74 01 00 00 FF D0 A2" ); // 37
	auto override_view_target = ( void* ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ? 85 FF" ); // 18
	auto endscene_target = ( void* ) get_virtual( i::dx9, 42 ); // 42
	auto reset_target = ( void* ) get_virtual( i::dx9, 16 ); // 16
	auto get_eye_ang_target = ( void* ) utils::find_sig_ida( "client.dll", "56 8B F1 85 F6 74 32" );
	auto lock_cursor_target = ( void* ) utils::find_sig_ida( "vguimatsurface.dll", "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01" ); // 67

	MH_Initialize( );

	MH_CreateHook( create_move_target, clientdll::create_move::hook, ( void** ) &o_create_move );
	MH_CreateHook( frame_stage_notify_target, clientdll::frame_stage_notify::hook, ( void** ) &o_frame_stage_notify );
	MH_CreateHook( override_view_target, clientmode::override_view::hook, ( void** ) &o_override_view );
	MH_CreateHook( endscene_target, dx9::endscene::hook, ( void** ) &o_endscene );
	MH_CreateHook( reset_target, dx9::reset::hook, ( void** ) &o_reset );
	MH_CreateHook( get_eye_ang_target, players::get_eye_ang::hook, ( void** ) &o_get_eye_ang );
	MH_CreateHook( lock_cursor_target, surface::lock_cursor::hook, ( void** ) &o_lock_cursor );

	MH_EnableHook( nullptr );
}

void hooks::restore( ) {
	MH_RemoveHook( MH_ALL_HOOKS );
	MH_Uninitialize( );

	/* shutdown imgui */
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );

	/* restore wnd_proc */
	SetWindowLongA( FindWindowA( "Valve001", nullptr ), GWLP_WNDPROC, long( o_wndproc ) );
}

