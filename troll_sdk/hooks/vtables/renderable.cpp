#include "../hooks.hpp"

bool __fastcall hooks::renderable::setup_bones::hook( void* ecx, void* edx, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float curtime ) {
	return o_setup_bones( ecx, edx, bone_to_world_out, max_bones, bone_mask, curtime );
}