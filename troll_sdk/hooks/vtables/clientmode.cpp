#include "../hooks.hpp"
#include "../../menu/menu.hpp"

bool __fastcall hooks::clientmode::createmove::hook( void* ecx, void* edx, float input_sample_frametime, c_usercmd* cmd ) {
	o_createmove( i::clientmode, 0, input_sample_frametime, cmd );

	/* get local here too bcuz we need it to get updated after the frame ( the tick is after the frame ) */
	g_local = ( c_base_player* ) i::entitylist->get_client_entity( i::engine->get_local_player( ) );

	if ( !cmd || !cmd->command_number || !i::engine->is_in_game( ) || !i::engine->is_connected( ) || !g_local || !g_local->is_alive( ) ) {
		return false;
	}

	/* globals */
	g::cmd = cmd;
	exploit::tick_count = cmd->tick_count;
	g::send_packet = true;

	/* get send_packet stuff */
	uintptr_t* framePtr; __asm mov framePtr, ebp;

	/* fix attack stuff */ {
		auto weapon = g_local->get_active_weapon( );
		if ( weapon ) {
			float flServerTime = g_local->m_nTickBase( ) * i::globalvars->m_interval_per_tick;
			bool can_shoot = ( weapon->m_flNextPrimaryAttack( ) <= flServerTime );
			if ( ( !can_shoot && !weapon->is_knife( ) && !weapon->is_nade( ) && !weapon->is_zeus( ) ) || menu::opened ) {
				cmd->buttons &= ~in_attack;
			}
		}
	}

	/* update prediction */
	engine_prediction::update( );

	/* prediction system related */ {
		engine_prediction::predict( cmd );

		/* predict our lby update */
		antiaim::predict_lby( );

		engine_prediction::restore( );
	}

	/* anti-untrsted */ {
		cmd->viewangles.clamp( );
	}

	/* get global angles */ {
		if ( g::send_packet ) {
			g::fake_angle = cmd->viewangles;
		}
		else {
			g::real_angle = cmd->viewangles;
		}
	}

	*( bool* ) ( *framePtr - 0x1C ) = g::send_packet;
	return false;
}

int __fastcall hooks::clientmode::do_post_screen_effects::hook( void* ecx, void* edx, int a ) {
	if ( !i::engine->is_in_game( ) || !i::engine->is_connected( ) || !g_local ) {
		return o_do_post_screen_effects( i::clientmode, 0, a );
	}

	return o_do_post_screen_effects( i::clientmode, 0, a );
}

float __fastcall hooks::clientmode::get_viewmodel_fov::hook( void* ecx, void* edx ) {
	return o_get_viewmodel_fov( i::clientmode, 0 );
}

void __fastcall hooks::clientmode::override_view::hook( void* ecx, void* edx, view_setup_t* view ) {
	if ( !i::engine->is_in_game( ) || !i::engine->is_connected( ) || !g_local || !g_local->is_alive( ) ) {
		o_override_view( i::clientmode, 0, view );
		return;
	}

	o_override_view( i::clientmode, 0, view );
}