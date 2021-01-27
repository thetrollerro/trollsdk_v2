#include "../hooks.hpp"

bool __fastcall hooks::file_system::sv_pure_loose_file_allowed::hook( void* ecx, void* edx ) {
	return true;
}