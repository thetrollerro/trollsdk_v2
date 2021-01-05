#include "../hooks.hpp"

i_material* __fastcall hooks::material_system::find_material::hook( void* ecx, void* edx, const char* mat_name, const char* group_name, bool complain, const char* complain_prefix ) {
	return o_find_material( ecx, 0, mat_name, group_name, complain, complain_prefix );
}