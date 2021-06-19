#pragma once
#include <cstddef>
#include <rpcndr.h>
#include "../../../utilities/utilities.hpp"

struct surfacephysicsparams_t {
public:
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};
struct surfaceaudioparams_t {
public:
	float reflectivity;
	float hardness_factor;
	float roughness_factor;
	float rough_threshold;
	float hard_threshold;
	float hard_velocity_threshold;
	float high_pitch_occlusion;
	float mid_pitch_occlusion;
	float low_pitch_occlusion;
};
struct surfacesoundnames_t {
public:
	unsigned short walk_step_left;
	unsigned short walk_step_right;
	unsigned short run_step_left;
	unsigned short run_step_right;
	unsigned short impact_soft;
	unsigned short impact_hard;
	unsigned short scrape_smooth;
	unsigned short scrape_rough;
	unsigned short bullet_impact;
	unsigned short rolling;
	unsigned short break_sound;
	unsigned short strain_sound;
};
struct surfacegameprops_t {
public:
	float max_speed_factor;
	float jump_factor;
	float penetration_modifier;
	float damage_modifier;
	unsigned short material;
	byte climbable;
	char pad00[ 0x4 ];
};

struct surfacedata_t {
public:
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
};

class i_surface_props {
public:
	virtual ~i_surface_props( void ) {}
	virtual int parse_surface_data( const char* name, const char* file ) = 0;
	virtual int surface_prop_count( void ) const = 0;
	virtual int get_surface_index( const char* name ) const = 0;
	virtual void get_physics_properties( int idx, float* density, float* thickness, float* friction, float* elasticity ) const = 0;
	virtual surfacedata_t* get_surface_data( int idx ) = 0;
	virtual const char* get_string( unsigned short idx ) const = 0;
	virtual const char* get_prop_name( int idx ) const = 0;
	virtual void set_world_material_index_table( int* arr, int size ) = 0;
	virtual void get_physics_parameters( int idx, surfacephysicsparams_t* out ) const = 0;
};
