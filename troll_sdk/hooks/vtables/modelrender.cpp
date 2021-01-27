#include "../hooks.hpp"

void __fastcall hooks::modelrender::draw_model_exec::hook( void* ecx, void* edx, void* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* custom_bone_to_world ) {
	o_draw_model_exec( ecx, 0, ctx, state, info, custom_bone_to_world );
}