#include "../hooks.hpp"
#include "../../menu/menu.hpp"

void __stdcall hooks::clientdll::create_move::call( int sequence_number, float sample_frametime, bool active, bool& send_packet ) {
	o_create_move( sequence_number, sample_frametime, active/*, send_packet*/ );

	auto cmd = i::input->get_user_cmd( sequence_number );
	auto verified = i::input->get_verified_user_cmd( sequence_number );

	if ( !cmd || !cmd->command_number ) {
		return;
	}

	/* globals */
	g::cmd = cmd;
	g::send_packet = true;

	g::weapon = nullptr;
	g::weapon_data = nullptr;

	if ( !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		return;
	}

	g::eye_pos = g_local->get_eye_pos( );
	g::weapon = g_local->get_active_weapon( );
	if ( g::weapon )
		g::weapon_data = g::weapon->get_cs_weapon_data( );

	/* fix attack stuff */
	if ( !utils::can_shoot( ) || menu::opened ) {
		cmd->buttons &= ~in_attack;
	}

	/* get viewangle before our prediction cuz prediction will change it */
	g::non_predicted_angle = cmd->viewangles;

	/* update pred */
	engine_prediction::update( );

	/* prediction system related */ {
		engine_prediction::predict( cmd, g_local );

		/* predict our lby times */
		antiaim::predict_lby( );

		engine_prediction::restore( g_local );
	}

	/* anti-untrsted */ {
		cmd->viewangles.normalize( );
		cmd->viewangles.clamp( );
	}

	/* get global angles */ {
		if ( g::send_packet ) {
			g::sent_angle = cmd->viewangles;
		}
		else {
			g::choked_angle = cmd->viewangles;
		}
	}

	/* end our createmove */
	send_packet = g::send_packet;
	verified->m_cmd = *cmd;
	verified->m_crc = cmd->get_checksum( );
}

__declspec( naked ) void __fastcall hooks::clientdll::create_move::hook( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active ) {
	__asm {
		push ebp
		mov  ebp, esp
		push ebx
		push esp
		push dword ptr[ active ]
		push dword ptr[ sample_frametime ]
		push dword ptr[ sequence_number ]
		call hooks::clientdll::create_move::call
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}

static std::vector<const char*> smoke_materials = {
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust"
};

void __fastcall hooks::clientdll::frame_stage_notify::hook( void* ecx, void* edx, int stage ) {
	if ( !i::engine->is_in_game( ) ) {
		g_local = nullptr;
		return;
	}

	g_local = c_base_player::get_player_by_index( i::engine->get_local_player( ) );

	/* save stage for later use */
	if ( stage != frame_start ) {
		g::stage = stage;
	}

	if ( i::engine->is_in_game( ) && g_local ) {
		switch ( stage )
		{

		case frame_start:

			break;

		case frame_net_update_start:

			break;

		case frame_net_update_postdataupdate_start:

			break;

		case frame_net_update_postdataupdate_end:

			break;

		case frame_net_update_end:

			break;

		case frame_render_start:

			break;

		case frame_render_end:

			break;

		}
	}

	/* call og and do our features that needs to be done after */
	o_frame_stage_notify( ecx, edx, stage );
}