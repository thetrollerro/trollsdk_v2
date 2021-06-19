#include "../hooks.hpp"

void __fastcall hooks::bsp_tree_query::insert_into_tree::hook( void* ecx, void* edx, vec3_t* mins, vec3_t* maxs ) {
	g::inserting_into_tree = true;
	return o_insert_into_tree( ecx, edx, mins, maxs );
	g::inserting_into_tree = false;
}

int __fastcall hooks::bsp_tree_query::list_leaves_in_box::hook( void* ecx, void* edx, vec3_t& mins, vec3_t& maxs, unsigned short* list, int list_max ) {
	if ( !i::engine->is_in_game( ) || !g_local )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	/* func sig 55 8B EC 83 E4 F8 81 EC ? ? ? ? 8B 45 08 53 56 8B 75 */
	/* to find:
	 * call dword ptr[eax+18h]
	 * mov [ esp + 930h + leaf_count ], eax
	 * call jmp     short unk_1024d4e8
	*/

	static auto r_list_leaves_in_box = utils::find_sig_ida( _( "client.dll" ), _( "89 44 24 14 EB 08 C7 44 24 ? ? ? ? ? 8B 45" ) );
	if ( _ReturnAddress( ) != ( void* ) r_list_leaves_in_box && !g::inserting_into_tree )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto info = *( renderable_info_t** ) ( ( uintptr_t ) _AddressOfReturnAddress( ) + 0x14 );
	if ( !info || !info->renderable )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto base_entity = info->renderable->get_client_unknown( )->get_base_entity( );
	if ( !base_entity || base_entity->get_client_class( )->class_id != class_id_cs_player )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	info->flags &= ~0x100;
	info->flags2 |= 0xC0;

	static const vec3_t map_min = vec3_t( -16384.0f, -16384.0f, -16384.0f );

	static const vec3_t map_max = vec3_t( 16384.0f, 16384.0f, 16384.0f );

	return o_list_leaves_in_box( ecx, edx, map_min, map_max, list, list_max );
}