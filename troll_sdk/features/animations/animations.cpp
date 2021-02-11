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

namespace animations {

	bool fresh_tick( ) {
		static int o_tick = i::globalvars->m_tick_count;
		if ( o_tick != i::globalvars->m_tick_count ) {
			o_tick = i::globalvars->m_tick_count;
			return true;
		}
		return false;
	}

	bool build_matrix( c_base_player* pl, matrix_t* out, float seed ) {
		if ( !pl || !pl->is_player( ) || !pl->is_alive( ) ) {
			return false;
		}

		auto hdr = pl->get_model_ptr( );
		if ( !hdr ) {
			return false;
		}

		/* get base matrix */
		matrix_t base_matrix;
		math::angle_matrix( pl->get_abs_angles( ), pl->get_abs_origin( ), base_matrix );

		/* backup */
		const auto backup_occlusion_flags = pl->m_iOcclusionFlags( );
		const auto backup_animframe = *( int* ) ( ( uintptr_t ) pl + 0x274 );

		/* repair last animated frame */
		*reinterpret_cast< char* > ( uintptr_t( pl ) + 0xA68 ) = 0;
		const auto o_frametime = i::globalvars->m_frame_time;

		/* dont skip any frame */
		*( int* ) ( ( uintptr_t ) pl + 0x274 ) = 0;

		/* shit yes frametime */
		i::globalvars->m_frame_time = FLT_MAX;

		/* disable matrix interpolation */
		*reinterpret_cast< int* >( uintptr_t( pl ) + 0xf0 ) |= 8;

		/* overwrite old matrix with the new one */
		pl->invalidate_bone_cache( );

		/* skip call to acumulate layers */
		pl->m_iOcclusionFlags( ) |= 0xA;

		/* get bone matrix */
		generate_matrix( pl, out, seed );

		/* restore occlusion flags after building matrix */
		pl->m_iOcclusionFlags( ) = backup_occlusion_flags;

		/* restore */
		i::globalvars->m_frame_time = o_frametime;
		*( int* ) ( ( uintptr_t ) pl + 0x274 ) = backup_animframe;

		return true;
	}

	bool generate_matrix( c_base_player* pl, matrix_t* out, float seed ) {
		return o_setup_bones( pl->get_client_renderable( ), nullptr, out, 128, bone_used_by_anything & ~bone_used_by_attachment, seed );
	}

	bool copy_matrix( c_base_player* pl, matrix_t* out ) {
		return std::memcpy( out, pl->get_bone_acessor( )->get_bone_arr_for_write( ), sizeof( matrix_t ) * 128 );
	}

}