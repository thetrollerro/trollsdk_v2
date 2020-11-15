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

	auto chams_materials = [ ] ( int type ) -> i_material* {
		/* chams materials */
		static i_material*
			flat = nullptr, * textured = nullptr,
			* metallic = nullptr, * pulsing = nullptr;

		/* bool if created_materials */
		static bool created_materials = false;

		if ( !created_materials ) {
			/* create materials */
			flat = i::material_system->find_material( "debug/debugdrawflat", texture_group_other );
			textured = i::material_system->find_material( "debug/debugambientcube", texture_group_other );
			metallic = i::material_system->find_material( "vitality_metallic", texture_group_other );
			pulsing = i::material_system->find_material( "models/inventory_items/dogtags/dogtags_outline", texture_group_other );

			/* set materials created to true */
			created_materials = true;
		}

		/* check for int value */
		switch ( type ) {
		case 0: return flat;
		case 1: return textured;
		case 2: return metallic;
		case 3: return pulsing;
		}
	};
	auto chams_overlays = [ ] ( int type ) -> i_material* {
		/* chams overlays */
		static i_material* dev_glow = nullptr, * glow_overlay = nullptr;

		/* bool created_overlays */
		static bool created_overlays = false;

		/* check if materials has been created */
		if ( !created_overlays ) {

			/* set material values */
			glow_overlay = i::material_system->find_material( "dev/glow_armsrace", texture_group_other );
			dev_glow = i::material_system->find_material( "dev/glow_armsrace", texture_group_other );

			/* set materials created to true */
			created_overlays = true;
		}

		/* check for int value */
		switch ( type ) {
		case 0: {
			bool found_tint2; auto tint2 = glow_overlay->find_var( "$envmapfresnelminmaxexp", &found_tint2 );
			if ( found_tint2 && tint2 ) {
				tint2->set_vector( vec3_t( 0.f, 1.f, 2.f ) );
			}
			return glow_overlay;
		}
		case 1: return dev_glow;
		}
	};

	/* get model */
	bool is_player = strstr( info.model->name, ( "models/player" ) ) != nullptr;
	bool is_arm = strstr( info.model->name, ( "arms" ) ) != nullptr;
	bool is_weapon = strstr( info.model->name, ( "weapons/v_" ) ) != nullptr;

	o_draw_model_exec( i::modelrender, 0, ctx, state, info, custom_bone_to_world );
	i::modelrender->force_mat( nullptr );
}