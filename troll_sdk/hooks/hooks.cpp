#include "hooks.hpp"

namespace hooks {

	void init( ) {
		while ( !( csgo_window = FindWindowA( "Valve001", nullptr ) ) ) {
			using namespace std::literals::chrono_literals;
			std::this_thread::sleep_for( 50ms );
		}

		/* create fonts */
		render::create_fonts( );

		/* hook wproc */
		o_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongPtrA( csgo_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( dx9::wndproc::hook ) ) );

		/* get targets */
		static auto do_procedual_foot_plant_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 57 8B 56" ) );
		static auto modify_eye_position_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 5C 53 8B D9 56 57 83" ) );
		static auto insert_into_tree_target = ( void* ) ( utils::find_sig_ida( _( "client.dll" ), _( "E8? ? ? ? 80 7D FF 00 74 44" ) ) + 0x1 );
		static auto list_leaves_in_box_target = ( void* ) utils::find_sig_ida( _( "engine.dll" ), _( "55 8B EC 83 EC 18 8B 4D 0C" ) ); // 6
		static auto create_move_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 EC 08 FF 15 ? ? ? ? 84 C0" ) ); // 22
		static auto frame_stage_notify_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 80 74 01 00 00 FF D0 A2" ) );// 37
		static auto do_post_screen_effects_target = ( void* ) get_virtual( i::clientmode, 44 ); // 44
		static auto get_viewmodel_fov_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" ) );
		static auto override_view_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ? 85 FF" ) ); // 18
		static auto endscene_target = ( void* ) get_virtual( i::dx9, 42 ); // 42
		static auto present_target = ( void* ) get_virtual( i::dx9, 17 ); // 17
		static auto reset_target = ( void* ) get_virtual( i::dx9, 16 ); // 16
		static auto cl_move_target = ( void* ) utils::find_sig_ida( _( "engine.dll" ), _( "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ? 8A" ) );
		static auto fire_game_event_target = ( void* ) get_virtual( i::engine, 59 ); // 59
		static auto get_viewangles_target = ( void* ) get_virtual( i::engine, 18 ); // 18
		static auto is_connected_target = ( void* ) get_virtual( i::engine, 27 ); // 27
		static auto is_hltv_target = ( void* ) get_virtual( i::engine, 93 ); // 93
		static auto is_in_game_target = ( void* ) get_virtual( i::engine, 26 ); // 26
		static auto is_paused_target = ( void* ) get_virtual( i::engine, 90 ); // 90
		static auto emit_sound_1_target = ( void* ) get_virtual( i::engine_sound, 5 );
		static auto sv_pure_loose_file_allowed_target = ( void* ) get_virtual( i::file_system, 128 );
		static auto check_for_sequence_change_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 51 53 8B 5D 08 56 8B F1 57 85" ) );
		static auto should_skip_animframe_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "57 8B F9 8B 07 8B 80 ? ? ? ? FF D0 84 C0 75 02 5F C3" ) );
		static auto sv_cheats_get_bool_target = ( void* ) utils::find_sig_ida( _( "engine.dll" ), _( "8B 51 1C 3B D1 75 06 8B 41 30 33 C1 C3 8B 02 8B CA FF 60 34 CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 83 E4 F8 0F 54 05" ) );
		static auto find_material_target = ( void* ) utils::find_sig_ida( _( "materialsystem.dll" ), _( "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 24 53" ) );
		static auto draw_model_exec_target = ( void* ) utils::find_sig_ida( _( "engine.dll" ), _( "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 56 8B 75 10" ) ); // 21
		static auto process_packet_target = ( void* ) utils::find_sig_ida( _( "engine.dll" ), _( "55 8B EC 83 E4 C0 81 EC ? ? ? ? 53 56" ) );
		static auto send_net_message_target = ( void* ) utils::find_sig_ida( _( "engine.dll" ), _( "55 8B EC 83 EC 08 56 8B F1 8B 86 ? ? ? ? 85 C0" ) );
		static auto paint_traverse_target = ( void* ) get_virtual( i::panel, 41 ); // 41
		static auto build_transformations_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F0 81 EC ? ? ? ? 56 57 8B F9 8B 0D ? ? ? ? 89 7C 24 1C" ) );
		static auto calc_view_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 24 53 56 57 FF 75 18" ) );
		static auto do_extra_bones_processing_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 81 EC FC 00 00 00 53 56 8B F1 57" ) ); // 197
		static auto get_eye_ang_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "56 8B F1 85 F6 74 32" ) ); // its a nervar lmao
		static auto process_interpolated_list_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "0F B7 05 ? ? ? ? 3D ? ? ? ? 74 3F" ) );
		static auto standard_blending_rules_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 8B 75 08 57 8B F9 85 F6" ) );
		static auto update_clientside_animation_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" ) );
		static auto in_prediction_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "8A 41 08 C3" ) ); // 14
		static auto perform_prediction_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 EC 18 53 56 8B 35 ? ? ? ? 8B D9 57 8B CE 89 5D F8 89 75 E8 8B 06 FF 90 ? ? ? ? FF 75 18 8B CB FF 75 14 FF 75 10 FF 75 08" ) );
		static auto run_command_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 C0 83 EC 34 53 56 8B 75 08" ) ); // 19
		static auto setup_move_target = ( void* ) get_virtual( i::prediction, 20 ); // 20
		static auto setup_bones_target = ( void* ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9" ) ); // 13
		static auto draw_set_color_target = ( void* ) utils::find_sig_ida( _( "vguimatsurface.dll" ), _( "55 8B EC 66 0F 6E 45 ? 8A 45 08" ) ); // 15
		static auto lock_cursor_target = ( void* ) utils::find_sig_ida( _( "vguimatsurface.dll" ), _( "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01" ) ); // 67

		/* init mh */
		MH_Initialize( );

		/* do our hooks */
		MH_CreateHook( do_procedual_foot_plant_target, animstate::do_procedual_foot_plant::hook, ( void** ) &o_do_procedual_foot_plant );
		MH_CreateHook( modify_eye_position_target, animstate::modify_eye_position::hook, ( void** ) &o_modify_eye_position );
		MH_CreateHook( insert_into_tree_target, bsp_tree_query::insert_into_tree::hook, ( void** ) &o_insert_into_tree );
		MH_CreateHook( list_leaves_in_box_target, bsp_tree_query::list_leaves_in_box::hook, ( void** ) &o_list_leaves_in_box );
		MH_CreateHook( create_move_target, clientdll::create_move::hook, ( void** ) &o_create_move );
		MH_CreateHook( frame_stage_notify_target, clientdll::frame_stage_notify::hook, ( void** ) &o_frame_stage_notify );
		MH_CreateHook( do_post_screen_effects_target, clientmode::do_post_screen_effects::hook, ( void** ) &o_do_post_screen_effects );
		MH_CreateHook( get_viewmodel_fov_target, clientmode::get_viewmodel_fov::hook, ( void** ) &o_get_viewmodel_fov );
		MH_CreateHook( override_view_target, clientmode::override_view::hook, ( void** ) &o_override_view );
		MH_CreateHook( endscene_target, dx9::endscene::hook, ( void** ) &o_endscene );
		//MH_CreateHook( present_target, dx9::present::hook, ( void** ) &o_present );
		MH_CreateHook( reset_target, dx9::reset::hook, ( void** ) &o_reset );
		MH_CreateHook( cl_move_target, engine::cl_move::hook, ( void** ) &o_cl_move );
		MH_CreateHook( fire_game_event_target, engine::fire_game_event::hook, ( void** ) &o_fire_game_event );
		MH_CreateHook( get_viewangles_target, engine::get_viewangles::hook, ( void** ) &o_get_viewangles );
		MH_CreateHook( is_connected_target, engine::is_connected::hook, ( void** ) &o_is_connected );
		MH_CreateHook( is_hltv_target, engine::is_hltv::hook, ( void** ) &o_is_hltv );
		MH_CreateHook( is_in_game_target, engine::is_in_game::hook, ( void** ) &o_is_in_game );
		MH_CreateHook( is_paused_target, engine::is_paused::hook, ( void** ) &o_is_paused );
		MH_CreateHook( emit_sound_1_target, engine_sound::emit_sound_1::hook, ( void** ) &o_emit_sound_1 );
		MH_CreateHook( sv_pure_loose_file_allowed_target, file_system::sv_pure_loose_file_allowed::hook, ( void** ) &o_sv_pure_loose_file_allowed );
		MH_CreateHook( check_for_sequence_change_target, game::check_for_sequence_change::hook, ( void** ) &o_check_for_sequence_change );
		MH_CreateHook( should_skip_animframe_target, game::should_skip_animframe::hook, ( void** ) &o_should_skip_animframe );
		MH_CreateHook( sv_cheats_get_bool_target, game::sv_cheats_get_bool::hook, ( void** ) &o_sv_cheats_get_bool );
		MH_CreateHook( find_material_target, material_system::find_material::hook, ( void** ) &o_find_material );
		MH_CreateHook( draw_model_exec_target, modelrender::draw_model_exec::hook, ( void** ) &o_draw_model_exec );
		MH_CreateHook( process_packet_target, net_channel::process_packet::hook, ( void** ) &o_process_packet );
		MH_CreateHook( send_net_message_target, net_channel::send_net_message::hook, ( void** ) &o_send_net_message );
		MH_CreateHook( paint_traverse_target, panel::paint_traverse::hook, ( void** ) &o_paint_traverse );
		MH_CreateHook( build_transformations_target, players::build_transformations::hook, ( void** ) &o_build_transformations );
		MH_CreateHook( calc_view_target, players::calc_view::hook, ( void** ) &o_calc_view );
		MH_CreateHook( do_extra_bones_processing_target, players::do_extra_bones_processing::hook, ( void** ) &o_do_extra_bones_processing );
		MH_CreateHook( get_eye_ang_target, players::get_eye_ang::hook, ( void** ) &o_get_eye_ang );
		MH_CreateHook( standard_blending_rules_target, players::standard_blending_rules::hook, ( void** ) &o_standard_blending_rules );
		MH_CreateHook( update_clientside_animation_target, players::update_clientside_animations::hook, ( void** ) &o_update_clientside_animations );
		MH_CreateHook( in_prediction_target, prediction::in_prediction::hook, ( void** ) &o_in_prediction );
		//MH_CreateHook( perform_prediction_target, prediction::perform_prediction::hook, ( void** ) &o_perform_prediction ); // use only if u need it ( may cause issues if u let it empty )
		MH_CreateHook( run_command_target, prediction::run_command::hook, ( void** ) &o_run_command );
		MH_CreateHook( setup_move_target, prediction::setup_move::hook, ( void** ) &o_setup_move );
		//MH_CreateHook( setup_bones_target, renderable::setup_bones::hook, ( void** ) &o_setup_bones );
		MH_CreateHook( draw_set_color_target, surface::draw_set_color::hook, ( void** ) &o_draw_set_color );
		MH_CreateHook( lock_cursor_target, surface::lock_cursor::hook, ( void** ) &o_lock_cursor );

		/* enable mhs */
		MH_EnableHook( nullptr );

		/* init events */
		event_mgr.initialize( );
	}

	void restore( ) {
		/* disable and remove our hooks */
		MH_DisableHook( nullptr );
		MH_RemoveHook( nullptr );

		/* animate again */
		if ( i::engine->is_in_game( ) && g_local && g_local->is_alive( ) )
			g_local->m_bClientSideAnimation( ) = true;

		/* shutdown imgui */
		ImGui_ImplDX9_Shutdown( );
		ImGui_ImplWin32_Shutdown( );
		ImGui::DestroyContext( );

		/* restore events */
		event_mgr.restore( );

		/* restore wnd_proc */
		SetWindowLongA( csgo_window, GWLP_WNDPROC, long( o_wndproc ) );

		/* stuff of minhooking */
		MH_Uninitialize( );
	}

}