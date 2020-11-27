#pragma once
#include "../../main.hpp"
#include "sounds.hpp"

class events : public i_game_event_listener {
public:
	void fire_game_event( i_game_event* event );
	int get_event_debug_id = 42;

	void initialize( ) {
		i::event_manager->add_listener( this, "player_hurt", false );
		i::event_manager->add_listener( this, "player_death", false );
		i::event_manager->add_listener( this, "bullet_impact", false );
		i::event_manager->add_listener( this, "weapon_fire", false );
		i::event_manager->add_listener( this, "round_start", false );
		i::event_manager->add_listener( this, "item_purchase", false );
		i::event_manager->add_listener( this, "bullet_impact", false );
	}

	void restore( ) {
		i::event_manager->remove_listener( this );
	}
}; inline events event_mgr;