#include "../hooks.hpp"

i_material* chams_materials( int type ) {
	/* chams materials */
	static i_material*
		flat = nullptr, * textured = nullptr,
		* metallic = nullptr, * pulsing = nullptr;

	/* bool if created_materials */
	static bool created_materials = false;

	if ( !created_materials ) {
		std::ofstream( "csgo\\materials\\material_reflective.vmt" ) << R"#("VertexLitGeneric" {
				 "$basetexture" "vgui/white"
				 "$ignorez" "0"
				 "$envmap" "env_cubemap"
				 "$normalmapalphaenvmapmask" "1"
				 "$envmapcontrast"  "1"
				 "$nofog" "1"
				 "$model" "1"
				 "$nocull" "0"
				 "$selfillum" "1"
				 "$halflambert" "1"
				 "$znearer" "0"
				 "$flat" "1" 
				})#";

		/* create materials */
		flat = i::material_system->find_material( "debug/debugdrawflat", texture_group_other );
		textured = i::material_system->find_material( "debug/debugambientcube", texture_group_other );
		metallic = i::material_system->find_material( "material_reflective.vmt", texture_group_other );
		pulsing = i::material_system->find_material( "models/inventory_items/dogtags/dogtags_outline", texture_group_other );

		/* increment */
		flat->increment_reference_count( );
		textured->increment_reference_count( );
		metallic->increment_reference_count( );
		pulsing->increment_reference_count( );

		/* set materials created to true */
		created_materials = true;
	}

	/* check for int value */
	if ( created_materials ) {
		switch ( type ) {
		case 0: return flat; break;
		case 1: return textured; break;
		case 2: return metallic; break;
		case 3: return pulsing; break;
		}
	}
};
i_material* chams_overlays( int type ) {
	/* chams overlays */
	static i_material* dev_glow = nullptr, * glow_overlay = nullptr;

	/* bool created_overlays */
	static bool created_overlays = false;

	/* check if materials has been created */
	if ( !created_overlays ) {
		std::ofstream( "csgo/materials/glowOverlay.vmt" ) << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[0.2 0.2 0.7]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 1 2]"
				"$alpha" "[3]"
			})#";

		/* set material values */
		glow_overlay = i::material_system->find_material( "glowOverlay.vmt", texture_group_other );
		dev_glow = i::material_system->find_material( "dev/glow_armsrace", texture_group_other );

		/* increment */
		glow_overlay->increment_reference_count( );
		dev_glow->increment_reference_count( );

		/* set materials created to true */
		created_overlays = true;
	}

	/* check for int value */
	if ( created_overlays ) {
		switch ( type ) {
		case 0: {
			return glow_overlay;
		} break;
		case 1: {
			return dev_glow;
		} break;
		}
	}
};

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

	/* checks */
	if ( !i::engine->is_in_game( ) || i::modelrender->is_forced_mat( ) || !g_local )
		return o_draw_model_exec( ecx, edx, ctx, state, info, custom_bone_to_world );

	o_draw_model_exec( ecx, edx, ctx, state, info, custom_bone_to_world );
	i::modelrender->force_mat( nullptr );
}