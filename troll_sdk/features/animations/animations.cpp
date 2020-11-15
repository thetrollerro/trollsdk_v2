#include "animations.hpp"
#include "../../main.hpp"
#include "../../hooks/hooks.hpp"

/* animstate etc */
void animstate_pose_param_cache_t::set_value( c_base_player* e, float val ) {
	if ( m_idx >= 0 )
		e->m_flPoseParameter( )[ m_idx ] = val;
}

void animstate_t::reset( ) {
	using o_fn = void( __thiscall* )( void* );
	static o_fn reset_animstate = ( o_fn ) utils::find_sig_ida( "client.dll", "56 6A 01 68 ? ? ? ? 8B F1" );
	reset_animstate( this );
}

void animstate_t::update( vec3_t& ang ) {
	using o_fn = void( __vectorcall* )( void*, void*, float, float, float, void* );
	static auto update_animstate = reinterpret_cast< o_fn >( utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54" ) );
	update_animstate( this, nullptr, ang.z, ang.y, ang.x, nullptr );
}

float animations::jump_fall( c_base_player* pl, float air_time ) {
	const float airtime = ( air_time - 0.72f ) * 1.25f;
	const float clamped = airtime >= 0.f ? std::min< float >( airtime, 1.f ) : 0.f;
	float jump_fall = ( 3.f - ( clamped + clamped ) ) * ( clamped * clamped );

	if ( jump_fall >= 0.f )
		jump_fall = std::min< float >( jump_fall, 1.f );

	return jump_fall;
}

void animations::simulate_jumpfall( c_base_player* pl ) {
	auto state = pl->get_animstate( );
	auto layers = pl->get_animoverlays( );

	if ( !state || !layers )
		return;

	state->m_jump_fall_pose.set_value( pl, jump_fall( pl, layers[ 4 ].m_cycle ) );
}

bool animations::fresh_tick( ) {
	static int o_tick = i::globalvars->m_tick_count;
	if ( o_tick != i::globalvars->m_tick_count ) {
		o_tick = i::globalvars->m_tick_count;
		return true;
	}
	return false;
}

void animations::fix_onshot( c_usercmd* cmd ) {
	if ( cmd->buttons & in_attack ) {
		g::send_packet = true;
	}
}

bool animations::build_matrix( c_base_player* pl, matrix_t* out, int max_bones, int mask, float seed ) {
	const auto backup_mask_1 = *reinterpret_cast< int* >( uintptr_t( pl ) + 0x269C );
	const auto backup_mask_2 = *reinterpret_cast< int* >( uintptr_t( pl ) + 0x26B0 );
	const auto backup_flags = *reinterpret_cast< int* >( uintptr_t( pl ) + 0xe8 );
	const auto backup_effects = *reinterpret_cast< int* >( uintptr_t( pl ) + 0xf0 );
	const auto backup_use_pred_time = *reinterpret_cast< int* >( uintptr_t( pl ) + 0x2ee );
	const auto backup_abs_origin = pl->get_abs_origin( );

	*reinterpret_cast< int* >( uintptr_t( pl ) + 0xA68 ) = 0;
	const auto backup_frametime = i::globalvars->m_frame_time;

	i::globalvars->m_frame_time = FLT_MAX;

	*reinterpret_cast< int* >( uintptr_t( pl ) + 0x269C ) = 0;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0x26B0 ) |= 512;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0xe8 ) |= 8;

	/* disable matrix interpolation */
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0xf0 ) |= 8;

	/* use our setup time */
	*reinterpret_cast< bool* >( uintptr_t( pl ) + 0x2ee ) = false;

	/* thanks chambers */
	auto b = *reinterpret_cast< char* > ( uintptr_t( pl ) + 0x68 );
	//auto ik = *reinterpret_cast< void** > ( uintptr_t ( pl ) + N ( 0x2670 ) );

	auto backup_num_ik_chains = 0;

	*reinterpret_cast< char* > ( uintptr_t( pl ) + 0x68 ) |= 2;

	/* use uninterpolated origin */
	pl->set_abs_origin( pl->m_vecOrigin( ) );
	pl->invalidate_bone_cache( );

	bool ret = o_setup_bones( pl->get_client_renderable( ), nullptr, out, max_bones, mask, seed );
	pl->set_abs_origin( backup_abs_origin );
	*reinterpret_cast< char* > ( uintptr_t( pl ) + 0x68 ) = b;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0x269C ) = backup_mask_1;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0x26B0 ) = backup_mask_2;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0xe8 ) = backup_flags;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0xf0 ) = backup_effects;
	*reinterpret_cast< int* >( uintptr_t( pl ) + 0x2ee ) = backup_use_pred_time;

	i::globalvars->m_frame_time = backup_frametime;

	return ret;
}
bool animations::setup_bones( c_base_player* pl, matrix_t* out, int max_bones, int mask, float seed ) {
	__asm {
		mov edi, pl
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push seed
		push mask
		push max_bones
		push out
		call dword ptr ds : [edx + 0x34]
	}
}

