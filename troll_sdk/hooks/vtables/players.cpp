#include "../hooks.hpp"

void __fastcall hooks::players::build_transformations::hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 )
{
	auto pl = ( c_base_player* ) ecx;
	if ( !pl )
		return o_build_transformations( ecx, 0, a2, a3, a4, a5, a6, a7 );

	/* backup C_BaseAnimating::m_isJiggleBonesEnabled */
	auto o_jiggle_bones_enabled = pl->m_JiggleBones( );

	/* disable jiggle bones ( http://prntscr.com/sj25yo ) to not let valve animate weapons/etc. */
	pl->m_JiggleBones( ) = false;

	/* let valve do their things */
	o_build_transformations( ecx, 0, a2, a3, a4, a5, a6, a7 );

	/* restore jiggle_bones_enabled */
	pl->m_JiggleBones( ) = o_jiggle_bones_enabled;
}

void __fastcall hooks::players::calc_view::hook( void* ecx, void* edx, vec3_t& eye_origin, vec3_t& eye_angles, float& m_near, float& m_far, float& fov ) {
	auto pl = ( c_base_player* ) ecx;
	if ( !pl || pl->ent_index( ) != i::engine->get_local_player( ) )
		return o_calc_view( ecx, 0, eye_origin, eye_angles, m_near, m_far, fov );

	// Prevent CalcView from calling CCSGOPlayerAnimState::ModifyEyePosition( ... )
	// this will fix inaccuracies, for example when fakeducking - and will enforce
	// us to use our own rebuilt version of CCSGOPlayerAnimState::ModifyEyePosition from the server.

	/* backup our state */
	const auto o_new_animstate = pl->should_use_new_animstate( );

	/* make csgo don t call shit */
	pl->should_use_new_animstate( ) = false;

	/* let csgo fix their stuff */
	o_calc_view( ecx, 0, eye_origin, eye_angles, m_near, m_far, fov );

	/* restore */
	pl->should_use_new_animstate( ) = o_new_animstate;
}

void __fastcall hooks::players::do_extra_bones_processing::hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 )
{
	auto pl = ( c_base_player* ) ecx;
	if ( !pl ) {
		o_do_extra_bones_processing( ecx, 0, a2, a3, a4, a5, a6, a7 );
		return;
	}

	auto animstate = pl->get_animstate( );
	if ( !animstate || !animstate->m_entity ) {
		o_do_extra_bones_processing( ecx, 0, a2, a3, a4, a5, a6, a7 );
		return;
	}

	/* backup on ground */
	const auto o_on_ground = animstate->m_on_ground;

	/* set it to false */
	animstate->m_on_ground = false;

	/* set csgo do their stuff */
	o_do_extra_bones_processing( ecx, 0, a2, a3, a4, a5, a6, a7 );

	/* restore */
	animstate->m_on_ground = o_on_ground;
}

vec3_t* __fastcall hooks::players::get_eye_ang::hook( void* ecx, void* edx ) {
	auto pl = ( c_base_player* ) ecx;
	if ( !g::cmd || !pl || pl->ent_index( ) != i::engine->get_local_player( ) )
		return o_get_eye_ang( ecx, 0 );

	static auto ret_to_thirdperson_pitch = utils::find_sig_ida( "client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?" );
	static auto ret_to_thirdperson_yaw = utils::find_sig_ida( "client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?" );

	/* if we micromoving/breaking balance/breaking lby show sent angle so we won t see any flick on our animation */
	if ( _ReturnAddress( ) == ( void* ) ret_to_thirdperson_pitch || _ReturnAddress( ) == ( void* ) ret_to_thirdperson_yaw )
		return ( antiaim::m_in_lby_update || antiaim::m_in_balance_update || antiaim::m_can_micro_move ) ? &g::fake_angle : &g::cmd->viewangles;

	return o_get_eye_ang( ecx, 0 );
}

void __fastcall hooks::players::standard_blending_rules::hook( void* ecx, void* edx, studio_hdr_t* hdr, vec3_t* pos, quaternion* q, float curtime, int mask ) {
	auto pl = ( c_base_player* ) ecx;
	if ( !pl ) {
		return o_standard_blending_rules( ecx, 0, hdr, pos, q, curtime, mask );
	}

	/* stop interpolation */
	*( uint32_t* ) ( ( uintptr_t ) pl + 0xf0 ) |= 8;

	/* let csgo do their stuff */
	o_standard_blending_rules( ecx, 0, hdr, pos, q, curtime, mask );

	/* start interpolation again */
	*( uint32_t* ) ( ( uintptr_t ) pl + 0xf0 ) &= ~8;
}

void __fastcall hooks::players::update_clientside_animations::hook( void* ecx, void* edx ) {
	auto pl = ( c_base_player* ) ecx;
	if ( !pl || !pl->is_player( ) || pl->is_dormant( ) ) {
		o_update_clientside_animations( ecx, 0 );
		return;
	}

	o_update_clientside_animations( ecx, 0 );
}