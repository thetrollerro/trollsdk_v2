#include "c_base_combat_weapon.hpp"
#include "../../utilities/math/math.hpp"

vec3_t c_base_combat_weapon::calculate_spread( int seed, float inaccuracy, float spread, bool revolver2 ) {
	weapon_info_t* wep_info;
	int        item_def_index;
	float      recoil_index, r1, r2, r3, r4, s1, c1, s2, c2;

	// if we have no bullets, we have no spread.
	wep_info = this->get_cs_weapon_data( );
	if ( !wep_info || !wep_info->bullets )
		return {};

	// get some data for later.
	item_def_index = m_iItemDefinitionIndex( );
	recoil_index = m_flRecoilIndex( );

	// seed randomseed.
	math::random_seed( ( seed & 0xff ) + 1 );

	// generate needed floats.
	r1 = math::random_float( 0.f, 1.f );
	r2 = math::random_float( 0.f, M_PI * 2.f );

	if ( /*wep_info->m_weapon_type == WEAPONTYPE_SHOTGUN &&*/ i::cvar->find_var( "weapon_accuracy_shotgun_spread_patterns" )->get_int( ) > 0 )
		math::get_shotgun_spread( item_def_index, 0, 0 /*bullet_i*/ + wep_info->bullets * recoil_index, &r4, &r3 );

	else {
		r3 = math::random_float( 0.f, 1.f );
		r4 = math::random_float( 0.f, M_PI * 2.f );
	}

	// revolver secondary spread.
	if ( item_def_index == weapon_revolver && revolver2 ) {
		r1 = 1.f - ( r1 * r1 );
		r3 = 1.f - ( r3 * r3 );
	}

	// negev spread.
	else if ( item_def_index == weapon_negev && recoil_index < 3.f ) {
		for ( int i { 3 }; i > recoil_index; --i ) {
			r1 *= r1;
			r3 *= r3;
		}

		r1 = 1.f - r1;
		r3 = 1.f - r3;
	}

	// get needed sine / cosine values.
	c1 = std::cos( r2 );
	c2 = std::cos( r4 );
	s1 = std::sin( r2 );
	s2 = std::sin( r4 );

	// calculate spread vector.
	return {
		( c1 * ( r1 * inaccuracy ) ) + ( c2 * ( r3 * spread ) ),
		( s1 * ( r1 * inaccuracy ) ) + ( s2 * ( r3 * spread ) ),
		0.f
	};
}