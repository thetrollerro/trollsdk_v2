#include "../hooks.hpp"
#include "../../menu/menu.hpp"

void __fastcall hooks::clientdll::create_move::call( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active, bool& send_packet ) {
	o_create_move( i::clientdll, 0, sequence_number, sample_frametime, active, send_packet );

	auto cmd = i::input->get_user_cmd( 0, sequence_number );
	auto verified = &i::input->verified_commands[ sequence_number % 150 ];

	if ( !cmd || !cmd->command_number || !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		return;
	}

	/* globals */
	g::cmd = cmd;
	g::send_packet = send_packet;
	vec3_t o_ang = cmd->viewangles;

	/* fix attack stuff */ {
		auto weapon = g_local->get_active_weapon( );
		if ( weapon ) {
			bool can_shoot = ( weapon->m_flNextPrimaryAttack( ) <= g_local->m_nTickBase( ) * i::globalvars->m_interval_per_tick );
			if ( ( !can_shoot && !weapon->is_nade( ) ) || menu::opened ) {
				cmd->buttons &= ~in_attack;
			}
		}
	}

	/* do prediction */ {
		engine_prediction::predict( );



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

	send_packet = g::send_packet;
	verified->m_cmd = *cmd;
	verified->m_crc = cmd->get_checksum( );
}

__declspec( naked ) void __fastcall hooks::clientdll::create_move::hook( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active, bool& send_packet ) {
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

void __fastcall hooks::clientdll::frame_stage_notify::hook( void* ecx, void* edx, int stage ) {
	if ( !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		o_frame_stage_notify( i::clientdll, 0, stage );
		return;
	}

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
	
		/* pvs fix */
		for ( int i = 1; i < 65; i++ ) {
			auto pl = c_base_player::get_player_by_index( i );
			if ( !pl || !pl->is_player( ) || pl == g_local ) continue;

			*( int* ) ( ( uintptr_t ) pl + 0xA30 ) = i::globalvars->m_frame_count;
			*( int* ) ( ( uintptr_t ) pl + 0xA28 ) = 0;
		}

		break;

	case frame_render_end:

		break;

	}

	o_frame_stage_notify( i::clientdll, 0, stage );
}