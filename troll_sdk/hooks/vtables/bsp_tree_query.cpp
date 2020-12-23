#include "../hooks.hpp"

int __fastcall hooks::bsp_tree_query::list_leaves_in_box::hook( void* ecx, void* edx, vec3_t& mins, vec3_t& maxs, unsigned short* list, int list_max )
{
	if ( !i::engine->is_in_game( ) || !g_local )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	/* func sig 55 8B EC 83 E4 F8 81 EC ? ? ? ? 8B 45 08 53 56 8B 75 */
	/* to find:
	 * call dword ptr[eax+18h]
	 * mov [ esp + 930h + leaf_count ], eax
	 * call jmp     short unk_1024d4e8
	*/

	static auto r_list_leaves_in_box = utils::find_sig_ida( "client.dll", "89 44 24 14 EB 08 C7 44 24 ? ? ? ? ? 8B 45" );
	if ( _ReturnAddress( ) != ( void* ) r_list_leaves_in_box )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto info = *( renderable_info_t** ) ( ( uintptr_t ) _AddressOfReturnAddress( ) + 0x14 );
	if ( !info || !info->renderable )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto base_entity = info->renderable->get_client_unknown( )->get_base_entity( );
	if ( !base_entity || base_entity->get_client_class( )->class_id != class_id_cs_player )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	info->flags &= ~0x100;
	info->flags2 |= 0xC0;

#define max_coord_float ( 16384.0f )
#define min_coord_float ( -max_coord_float )

	static const vec3_t map_min = vec3_t( min_coord_float, min_coord_float, min_coord_float );
	static const vec3_t map_max = vec3_t( max_coord_float, max_coord_float, max_coord_float );

	auto ret = o_list_leaves_in_box( ecx, edx, map_min, map_max, list, list_max );
	return ret;
}