#include "../hooks.hpp"
#include "../../menu/menu.hpp"

void __fastcall hooks::clientdll::create_move::call( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active, bool& send_packet ) {
	o_create_move( i::clientdll, 0, sequence_number, sample_frametime, active, send_packet );

	auto cmd = i::input->get_user_cmd( sequence_number );
	auto verified = i::input->get_verified_user_cmd( sequence_number );

	if ( !cmd || !cmd->command_number || !i::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		return;
	}

	/* globals */
	g::cmd = cmd;
	g::send_packet = send_packet = true;

	/* fix attack stuff */ {
		auto weapon = g_local->get_active_weapon( );
		if ( weapon ) {
			float flServerTime = g_local->m_nTickBase( ) * i::globalvars->m_interval_per_tick;
			bool can_shoot = ( weapon->m_flNextPrimaryAttack( ) <= flServerTime );
			if ( ( !can_shoot && !weapon->is_nade( ) ) || menu::opened ) {
				cmd->buttons &= ~in_attack;
			}
		}
	}

	vec3_t o_ang = cmd->viewangles;

	/* update old commands so they get predicted */
	engine_prediction::update( );

	engine_prediction::predict( cmd ); 

	engine_prediction::restore( );

	/* get global angles */ {
		if ( g::send_packet ) {
			g::fake_angle = cmd->viewangles;
		}
		else {
			g::real_angle = cmd->viewangles;
		}
	}

	/* anti-untrsted */ {
		cmd->viewangles.clamp( );
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

std::vector<const char*> smoke_materials =
{
	"particle/beam_smoke_01",
	"particle/particle_smokegrenade",
	"particle/particle_smokegrenade1",
	"particle/particle_smokegrenade2",
	"particle/particle_smokegrenade3",
	"particle/particle_smokegrenade_sc",
	"particle/smoke1/smoke1",
	"particle/smoke1/smoke1_ash",
	"particle/smoke1/smoke1_nearcull",
	"particle/smoke1/smoke1_nearcull2",
	"particle/smoke1/smoke1_snow",
	"particle/smokesprites_0001",
	"particle/smokestack",
	"particle/vistasmokev1/vistasmokev1",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_nearcull",
	"particle/vistasmokev1/vistasmokev1_nearcull_fog",
	"particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev4_emods_nocull",
	"particle/vistasmokev1/vistasmokev4_nearcull",
	"particle/vistasmokev1/vistasmokev4_nocull"
};


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
		
		break;

	case frame_render_end:

		break;

	}

	o_frame_stage_notify( i::clientdll, 0, stage );
}