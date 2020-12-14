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

bool animations::fresh_tick( ) {
	static int o_tick = i::globalvars->m_tick_count;
	if ( o_tick != i::globalvars->m_tick_count ) {
		o_tick = i::globalvars->m_tick_count;
		return true;
	}
	return false;
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

bool animations::build_matrix( c_base_player* pl, matrix_t* out, int max_bones, int mask, float seed ) {
	return o_setup_bones( pl->get_client_renderable( ), nullptr, out, max_bones, mask, seed );
}

