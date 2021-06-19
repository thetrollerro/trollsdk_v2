#include "events.hpp"
#include <playsoundapi.h>
#pragma comment(lib, "winmm.lib")

void events::fire_game_event( i_game_event* event ) {
	if ( !i::engine->is_in_game( ) || !event || !g_local )
		return;

	/* vars */
	auto attacker = c_base_player::get_player_by_index( i::engine->get_player_for_userid( event->get_int( "attacker" ) ) );
	auto pl = c_base_player::get_player_by_index( i::engine->get_player_for_userid( event->get_int( "userid" ) ) );

	if ( !attacker || !pl )
		return;

	player_info_t info;
	i::engine->get_player_info( pl->ent_index( ), &info );

	auto name = event->get_name( );
	if ( !strcmp( name, "player_hurt" ) ) {

	}

	if ( !strcmp( name, "player_death" ) ) {

	}

	if ( !strcmp( name, "round_prestart" ) || !strcmp( name, "round_start" ) ) {

	}

	if ( !strcmp( name, "item_purchase" ) ) {

	}

	if ( !strcmp( name, "bullet_impact" ) ) {

	}

	if ( !strcmp( name, "weapon_fire" ) ) {

	}
}
