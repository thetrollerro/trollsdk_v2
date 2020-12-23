#include "../hooks.hpp"
#include "../../menu/menu.hpp"

bool __fastcall hooks::clientmode::createmove::hook( void* ecx, void* edx, float input_sample_frametime, c_usercmd* cmd ) {
	o_createmove( ecx, edx, input_sample_frametime, cmd );

	if ( !cmd || !cmd->command_number || !i::engine->is_in_game( ) || !g_local ) {
		return false;
	}

	/* timers for animfix */
	return false;
}

int __fastcall hooks::clientmode::do_post_screen_effects::hook( void* ecx, void* edx, int a ) {
	if ( !i::engine->is_in_game( ) || !g_local ) {
		return o_do_post_screen_effects( ecx, edx, a );
	}

	return o_do_post_screen_effects( ecx, edx, a );
}

float __fastcall hooks::clientmode::get_viewmodel_fov::hook( void* ecx, void* edx ) {
	return o_get_viewmodel_fov( ecx, edx );
}

void __fastcall hooks::clientmode::override_view::hook( void* ecx, void* edx, view_setup_t* view ) {
	if ( !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		o_override_view( ecx, edx, view );
		return;
	}

	o_override_view( ecx, edx, view );
}