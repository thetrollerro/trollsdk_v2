#include "../hooks.hpp"

void __fastcall hooks::animstate::do_procedual_foot_plant::hook( void* ecx, void* edx, matrix_t* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos ) {
	// the function is only called by DoExtraBoneProcessing so there is no need to check for return address
	// returning nothing prevents the "leg shuffling"

	return;
}

void __fastcall hooks::animstate::modify_eye_position::hook( void* ecx, void* edx, vec3_t& input_eye_position ) {
	auto animation_state = ( animstate_t* ) ecx;

	// nope https://github.com/perilouswithadollarsign/cstrike15_src/blob/29e4c1fda9698d5cebcdaf1a0de4b829fa149bf8/game/shared/cstrike15/csgo_playeranimstate.cpp#L450
	animation_state->m_smooth_height_valid( ) = false;

	return o_modify_eye_position( ecx, edx, input_eye_position );
}