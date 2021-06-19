#include "animations.hpp"
#include "../../main.hpp"
#include "../../hooks/hooks.hpp"

void animstate_pose_param_cache_t::set_value( c_base_player* e, float val ) {
	if ( m_idx >= 0 )
		e->m_flPoseParameter( )[ m_idx ] = val;
}

void animstate_t::reset( ) {
	using o_fn = void( __thiscall* )( void* );
	static o_fn reset_animstate = ( o_fn ) utils::find_sig_ida( _( "client.dll" ), _( "56 6A 01 68 ? ? ? ? 8B F1" ) );
	reset_animstate( this );
}

void animstate_t::update( vec3_t& ang ) {
	using o_fn = void( __vectorcall* )( void*, void*, float, float, float, void* );
	static auto update_animstate = reinterpret_cast< o_fn >( utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54" ) ) );
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

	bool build_matrix( c_base_player* pl, matrix_t* matrix, int mask ) {
		const auto backup_mask_1 = *reinterpret_cast< int* >( uintptr_t( pl ) + 0x269C );
		const auto backup_mask_2 = *reinterpret_cast< int* >( uintptr_t( pl ) + 0x26B0 );
		const auto backup_flags = *reinterpret_cast< int* >( uintptr_t( pl ) + 0xe8 );
		const auto backup_effects = *reinterpret_cast< int* >( uintptr_t( pl ) + 0xf0 );
		const auto backup_use_pred_time = *reinterpret_cast< int* >( uintptr_t( pl ) + 0x2ee );
		auto backup_abs_origin = pl->get_abs_origin( );

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

		auto backup_num_ik_chains = 0;

		*reinterpret_cast< char* > ( uintptr_t( pl ) + 0x68 ) |= 2;

		/* use uninterpolated origin */
		pl->invalidate_bone_cache( );
		pl->set_abs_origin( pl->m_vecOrigin( ) );

		const auto ret = pl->setup_bones( matrix, 128, mask, pl->m_flSimulationTime( ) );
		*reinterpret_cast< char* > ( uintptr_t( pl ) + 0x68 ) = b;
		*reinterpret_cast< int* >( uintptr_t( pl ) + 0x269C ) = backup_mask_1;
		*reinterpret_cast< int* >( uintptr_t( pl ) + 0x26B0 ) = backup_mask_2;
		*reinterpret_cast< int* >( uintptr_t( pl ) + 0xe8 ) = backup_flags;
		*reinterpret_cast< int* >( uintptr_t( pl ) + 0xf0 ) = backup_effects;
		*reinterpret_cast< int* >( uintptr_t( pl ) + 0x2ee ) = backup_use_pred_time;

		i::globalvars->m_frame_time = backup_frametime;
		pl->set_abs_origin( backup_abs_origin );

		return ret;
	}

	int bone_used_by_server = bone_used_by_hitbox | bone_used_by_vertex_lod0 | bone_used_by_vertex_lod1 | bone_used_by_vertex_lod2
		| bone_used_by_vertex_lod3 | bone_used_by_vertex_lod4 | bone_used_by_vertex_lod5 | bone_used_by_vertex_lod6 | bone_used_by_vertex_lod7;

	bool generate_matrix( c_base_player* pl, matrix_t* out, int mask ) {
		alignas( 16 ) matrix_t bone_out[ 128 ];
		const auto ret = pl->setup_bones( bone_out, 128, mask, pl->m_flSimulationTime( ) );
		memcpy( out, bone_out, sizeof( matrix_t[ 128 ] ) );
		return ret;
	}

	bool copy_matrix( c_base_player* pl, matrix_t* out ) {
		return std::memcpy( out, pl->GetBoneArrayForWrite( ), sizeof( matrix_t ) * 128 );
	}

}