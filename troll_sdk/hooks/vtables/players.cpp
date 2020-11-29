#include "../hooks.hpp"

void __fastcall hooks::players::build_transformations::hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 )
{
	auto player = ( c_base_player* ) ecx;
	if ( !player )
		return o_build_transformations( ecx, 0, a2, a3, a4, a5, a6, a7 );

	/* backup C_BaseAnimating::m_isJiggleBonesEnabled */
	auto o_jiggle_bones_enabled = player->m_JiggleBones( );

	/* disable jiggle bones ( http://prntscr.com/sj25yo ) to not let valve animate weapons/etc. */
	player->m_JiggleBones( ) = false;

	/* let valve do their things */
	o_build_transformations( ecx, 0, a2, a3, a4, a5, a6, a7 );

	/* restore jiggle_bones_enabled */
	player->m_JiggleBones( ) = o_jiggle_bones_enabled;
}

void __fastcall hooks::players::calc_view::hook( void* ecx, void* edx, vec3_t& eye_origin, vec3_t& eye_angles, float& m_near, float& m_far, float& fov ) {
	auto pl = ( c_base_player* ) ecx;
	if ( !pl || !g_local || pl != g_local )
		return o_calc_view( ecx, 0, eye_origin, eye_angles, m_near, m_far, fov );

	auto o_new_animstate = pl->should_use_new_animstate( );
	pl->should_use_new_animstate( ) = false;
	o_calc_view( ecx, 0, eye_origin, eye_angles, m_near, m_far, fov );
	pl->should_use_new_animstate( ) = o_new_animstate;
}

void __fastcall hooks::players::do_extra_bones_processing::hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 )
{
	const auto e = ( c_base_player* ) ecx;
	if ( !e ) {
		o_do_extra_bones_processing( ecx, 0, a2, a3, a4, a5, a6, a7 );
		return;
	}

	auto animstate = e->get_animstate( );
	if ( !animstate || !animstate->m_entity ) {
		o_do_extra_bones_processing( ecx, 0, a2, a3, a4, a5, a6, a7 );
		return;
	}

	/* prevent call to do_procedural_foot_plant */
	auto o_on_ground = animstate->m_on_ground;

	animstate->m_on_ground = false;

	o_do_extra_bones_processing( ecx, 0, a2, a3, a4, a5, a6, a7 );

	animstate->m_on_ground = o_on_ground;
}

vec3_t* __fastcall hooks::players::get_eye_ang::hook( void* ecx, void* edx ) {
	auto pl = ( c_base_player* ) ecx;
	if ( !g::cmd || !pl || !g_local || pl != g_local )
		return o_get_eye_ang( ecx, 0 );

	static auto ret_to_thirdperson_pitch = utils::find_sig_ida( "client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?" );
	static auto ret_to_thirdperson_yaw = utils::find_sig_ida( "client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?" );

	if ( _ReturnAddress( ) == ( void* ) ret_to_thirdperson_pitch || _ReturnAddress( ) == ( void* ) ret_to_thirdperson_yaw )
		return  antiaim::m_in_lby_update ? &g::fake_angle : &g::cmd->viewangles;

	return o_get_eye_ang( ecx, 0 );
}

bool __fastcall hooks::players::setup_bones::hook( void* ecx, void* edx, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float curtime ) {
	auto pl = ( c_base_player* ) ( ( uintptr_t ) ecx - 0x4 );
	if ( pl && pl->get_client_class( )->class_id == class_id_cs_player && !pl->is_dormant( ) ) {
		if ( pl->ent_index( ) == i::engine->get_local_player( ) ) {
			static auto host_timescale = i::cvar->find_var( "host_timescale" );
			const float o_curtime = i::globalvars->m_cur_time;
			const float o_realtime = i::globalvars->m_real_time;
			const float o_frametime = i::globalvars->m_frame_time;
			const float o_absframetime = i::globalvars->m_absolute_frame_time;
			const float o_absframetimestart = i::globalvars->m_absolute_frame_start_time_std_dev;
			const float o_interpolationamount = i::globalvars->m_interpolation_amount;
			const int o_framecount = i::globalvars->m_frame_count;
			const int o_tickcount = i::globalvars->m_tick_count;

			/* simulate gvars */
			i::globalvars->m_cur_time = pl->m_flSimulationTime( );
			i::globalvars->m_real_time = pl->m_flSimulationTime( );
			i::globalvars->m_frame_time = i::globalvars->m_interval_per_tick * host_timescale->get_float( );
			i::globalvars->m_absolute_frame_time = i::globalvars->m_interval_per_tick * host_timescale->get_float( );
			i::globalvars->m_absolute_frame_start_time_std_dev = pl->m_flSimulationTime( ) - i::globalvars->m_interval_per_tick * host_timescale->get_float( );
			i::globalvars->m_interpolation_amount = 0;
			i::globalvars->m_frame_count = time2ticks( pl->m_flSimulationTime( ) );
			i::globalvars->m_tick_count = time2ticks( pl->m_flSimulationTime( ) );

			/* stop interpolation */
			*( uint32_t* ) ( ( uintptr_t ) pl + 0xF0 ) |= 8;

			/* build bones */
			const bool ret = o_setup_bones( ecx, 0, bone_to_world_out, max_bones, bone_mask, curtime );

			/* start interpolation again */
			*( uint32_t* ) ( ( uintptr_t ) pl + 0xF0 ) &= ~8;

			/* restore */
			i::globalvars->m_cur_time = o_curtime;
			i::globalvars->m_real_time = o_realtime;
			i::globalvars->m_frame_time = o_frametime;
			i::globalvars->m_absolute_frame_time = o_absframetime;
			i::globalvars->m_absolute_frame_start_time_std_dev = o_absframetimestart;
			i::globalvars->m_interpolation_amount = o_interpolationamount;
			i::globalvars->m_frame_count = o_framecount;
			i::globalvars->m_tick_count = o_tickcount;
			return ret;
		}
		else {

		}
	}

	return o_setup_bones( ecx, 0, bone_to_world_out, max_bones, bone_mask, curtime );
}

void __fastcall hooks::players::standard_blending_rules::hook( void* ecx, void* edx, studio_hdr_t* hdr, vec3_t* pos, quaternion* q, float curtime, int mask ) {
	auto e = ( c_base_player* ) ecx;
	if ( !e ) {
		return o_standard_blending_rules( ecx, 0, hdr, pos, q, curtime, mask );
	}

	/* stop interpolation */
	*( uint32_t* ) ( ( uintptr_t ) e + 0xf0 ) |= 8;

	/* let csgo do their stuff */
	o_standard_blending_rules( ecx, 0, hdr, pos, q, curtime, mask );

	/* start interpolation again */
	*( uint32_t* ) ( ( uintptr_t ) e + 0xf0 ) &= ~8;
}