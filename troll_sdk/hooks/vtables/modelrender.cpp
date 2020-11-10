#include "../hooks.hpp"

void __fastcall hooks::modelrender::draw_model_exec::hook( void* ecx, void* edx, void* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* custom_bone_to_world )
{
	auto color_modulation = [ ] ( const float* color, i_material* material ) -> void {
		if ( material ) {
			material->alpha_modulate( color[ 3 ] );
			material->color_modulate( color[ 0 ], color[ 1 ], color[ 2 ] );
			bool found_tint;
			const auto tint = material->find_var( "$envmaptint", &found_tint );
			if ( found_tint )
				tint->set_vector( vec3_t( color[ 0 ], color[ 1 ], color[ 2 ] ) );
		}
	};

	auto player = c_base_player::get_player_by_index( info.entity_index );

	/* checks */
	if ( i::modelrender->is_forced_mat( ) || !i::engine->is_in_game( ) || !g_local )
		return o_draw_model_exec( i::modelrender, 0, ctx, state, info, custom_bone_to_world );


	o_draw_model_exec( i::modelrender, 0, ctx, state, info, custom_bone_to_world );
	i::modelrender->force_mat( nullptr );
}