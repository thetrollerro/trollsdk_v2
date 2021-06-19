#pragma once
#include <minwindef.h>
#include "../../math/matrix.hpp"
#include "../../math/vector.hpp"

class c_base_player;
enum {
	char_tex_antlion = 'a',
	char_tex_bloodyflesh = 'b',
	char_tex_concrete = 'c',
	char_tex_dirt = 'd',
	char_tex_eggshell = 'e',
	char_tex_flesh = 'f',
	char_tex_grate = 'g',
	char_tex_alienflesh = 'h',
	char_tex_clip = 'i',
	char_tex_plastic = 'l',
	char_tex_metal = 'm',
	char_tex_sand = 'n',
	char_tex_foliage = 'o',
	char_tex_computer = 'p',
	char_tex_slosh = 's',
	char_tex_tile = 't',
	char_tex_cardboard = 'u',
	char_tex_vent = 'v',
	char_tex_wood = 'w',
	char_tex_glass = 'y',
	char_tex_warpshield = 'z',
};

// m_takedamage
enum {
	damage_no = 0,
	damage_events_only = 1,
	damage_yes = 2,
	damage_aim = 3,
};

enum collision_group_t {
	collision_group_none = 0,
	collision_group_debris,
	collision_group_debris_trigger,
	collision_group_interactive_debris,
	collision_group_interactive,
	collision_group_player,
	collision_group_breakable_glass,
	collision_group_vehicle,
	collision_group_player_movement,
	collision_group_npc,
	collision_group_in_vehicle,
	collision_group_weapon,
	collision_group_vehicle_clip,
	collision_group_projectile,
	collision_group_door_blocker,
	collision_group_passable_door,
	collision_group_dissolving,
	collision_group_pushaway,
	collision_group_npc_actor,
	collision_group_npc_scripted,
	collision_group_pz_clip,
	collision_group_debris_block_projectile,
	last_shared_collision_group
};

enum tracetype_t {
	trace_everything = 0,
	trace_world_only,
	trace_entities_only,
	trace_everything_filter_props
};

enum contents_t {
	contents_empty = 0,
	contents_solid = 0x1,
	contents_window = 0x2,
	contents_aux = 0x4,
	contents_grate = 0x8,
	contents_slime = 0x10,
	contents_water = 0x20,
	contents_blocklos = 0x40,
	contents_opaque = 0x80,
	contents_testfogvolume = 0x100,
	contents_unused = 0x200,
	contents_blocklight = 0x400,
	contents_team1 = 0x800,
	contents_team2 = 0x1000,
	contents_ignore_nodraw_opaque = 0x2000,
	contents_moveable = 0x4000,
	contents_areaportal = 0x8000,
	contents_playerclip = 0x10000,
	contents_monsterclip = 0x20000,
	contents_current_0 = 0x40000,
	contents_current_90 = 0x80000,
	contents_current_180 = 0x100000,
	contents_current_270 = 0x200000,
	contents_current_up = 0x400000,
	contents_current_down = 0x800000,
	contents_origin = 0x1000000,
	contents_monster = 0x2000000,
	contents_debris = 0x4000000,
	contents_detail = 0x8000000,
	contents_translucent = 0x10000000,
	contents_ladder = 0x20000000,
	contents_hitbox = 0x40000000,
};

enum masks_t {
	mask_all = 0xffffffff,
	mask_solid = contents_solid | contents_moveable | contents_window | contents_monster | contents_grate,
	mask_playersolid = contents_solid | contents_moveable | contents_playerclip | contents_window | contents_monster | contents_grate,
	mask_npcsolid = contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate,
	mask_npcfluid = contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate,
	mask_water = contents_water | contents_moveable | contents_slime,
	mask_opaque = contents_solid | contents_moveable | contents_opaque,
	mask_opaque_and_npcs = mask_opaque | contents_monster,
	mask_blocklos = contents_solid | contents_moveable | contents_blocklos,
	mask_blocklos_and_npcs = mask_blocklos | contents_monster,
	mask_visible = mask_opaque | contents_ignore_nodraw_opaque,
	mask_visible_and_npcs = mask_opaque_and_npcs | contents_ignore_nodraw_opaque,
	mask_shot = contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate | contents_hitbox,
	mask_shot_brushonly = contents_solid | contents_moveable | contents_window | contents_debris,
	mask_shot_hull = contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate,
	mask_shot_portal = contents_solid | contents_moveable | contents_window | contents_monster,
	mask_solid_brushonly = contents_solid | contents_moveable | contents_window | contents_grate,
	mask_playersolid_brushonly = contents_solid | contents_moveable | contents_window | contents_playerclip | contents_grate,
	mask_npcsolid_brushonly = contents_solid | contents_moveable | contents_window | contents_monsterclip | contents_grate,
	mask_npcworldstatic = contents_solid | contents_window | contents_monsterclip | contents_grate,
	mask_npcworldstatic_fluid = contents_solid | contents_window | contents_monsterclip,
	mask_splitareportal = contents_water | contents_slime,
	mask_current = contents_current_0 | contents_current_90 | contents_current_180 | contents_current_270 | contents_current_up | contents_current_down,
	mask_deadsolid = contents_solid | contents_playerclip | contents_window | contents_grate,
};

enum {
	surf_light = 0x0001,
	surf_sky2d = 0x0002,
	surf_sky = 0x0004,
	surf_warp = 0x0008,
	surf_trans = 0x0010,
	surf_noportal = 0x0020,
	surf_trigger = 0x0040,
	surf_nodraw = 0x0080,
	surf_hint = 0x0100,
	surf_skip = 0x0200,
	surf_nolight = 0x0400,
	surf_bumplight = 0x0800,
	surf_noshadows = 0x1000,
	surf_nodecals = 0x2000,
	surf_nopaint = surf_nodecals,
	surf_nochop = 0x4000,
	surf_hitbox = 0x8000
};

enum surfaceflags_t {
	dispsurf_flag_surface = ( 1 << 0 ),
	dispsurf_flag_walkable = ( 1 << 1 ),
	dispsurf_flag_buildable = ( 1 << 2 ),
	dispsurf_flag_surfprop1 = ( 1 << 3 ),
	dispsurf_flag_surfprop2 = ( 1 << 4 ),
};

class __declspec( align( 16 ) )vec_aligned : public vec3_t {
public:
	vec_aligned& operator=( const vec3_t& vOther ) {
		init( vOther.x, vOther.y, vOther.z );
		return *this;
	}

	float w;
};

class i_handle_entity;

struct ray_t {
public:
	__forceinline ray_t( ) : m_world_axis_transform {}, m_is_ray {}, m_is_swept {} {}

	__forceinline ray_t( const vec3_t& start, const vec3_t& end ) {
		m_delta = vec_aligned { end - start };
		m_world_axis_transform = nullptr;
		m_is_swept = m_delta.length( ) != 0.f;
		m_extents.x = m_extents.y = m_extents.z = 0.0f;
		m_is_ray = m_extents.length_sqr( ) < 1e-6;
		m_start_offset.x = m_start_offset.y = m_start_offset.z = 0.0f;
		*reinterpret_cast< vec3_t* >( &m_start ) = start;
	}

	__forceinline ray_t( const vec3_t& start, const vec3_t& end, const vec3_t& mins, const vec3_t& maxs ) {
		m_delta = vec_aligned { end - start };
		m_world_axis_transform = nullptr;
		m_is_swept = m_delta.length_sqr( ) != 0.f;
		m_extents = vec_aligned { maxs - mins };
		m_extents *= 0.5f;
		m_is_ray = m_extents.length_sqr( ) < 1e-6;
		m_start_offset = vec_aligned { mins + maxs };
		m_start_offset *= 0.5f;
		m_start = vec_aligned { start + m_start_offset };
		m_start_offset *= -1.f;
	}

public:
	vec_aligned m_start;
	vec_aligned m_delta;
	vec_aligned	m_start_offset;
	vec_aligned	m_extents;
	const matrix_t* m_world_axis_transform;
	bool m_is_ray;
	bool m_is_swept;
};

struct csurface_t {
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

struct cplane_t {
	vec3_t normal;
	float m_dist;
	BYTE m_type;
	BYTE m_sign_bits;
	BYTE m_pad[ 2 ];
};

class trace_t {
public:
	vec3_t start;
	vec3_t end;
	cplane_t plane;
	float fraction;
	int contents;
	unsigned short disp_flags;
	bool allsolid;
	bool start_solid;
	float fraction_left_solid;
	csurface_t surface;
	int hit_group;
	short physics_bone;
	c_base_player* player;
	int hitbox;

	__forceinline bool did_hit( ) const {
		return fraction < 1.f || allsolid || start_solid;
	}
};

class i_trace_filter {
public:
	virtual bool should_hit_entity( void* ent, int contents_mask ) = 0;
	virtual tracetype_t get_trace_type( ) const = 0;
};

class trace_filter : public i_trace_filter {
public:
	trace_filter( ) { } 
	explicit trace_filter( void* player ) {
		skip = player;
	}

	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return ( entity_handle != skip );
	}

	tracetype_t get_trace_type( ) const {
		return trace_everything;
	}

	void* skip;
};

class trace_entity_t : public i_trace_filter {
public:
	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return ( entity_handle != skip );
	}

	tracetype_t get_trace_type( ) const {
		return trace_entities_only;
	}

	void* skip;
};

class trace_world_only_t : public i_trace_filter {
public:
	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return false;
	}

	tracetype_t get_trace_type( ) const {
		return trace_world_only;
	}

	void* skip;
};
class collideable_t;
class i_trace {
public:
	virtual int get_point_contents( const vec3_t& pos, int mask = mask_all, i_handle_entity** ent = nullptr ) = 0;
	virtual int get_point_contents_world( const vec3_t& pos, int mask = mask_all ) = 0;
	virtual int get_point_contents_collideable( collideable_t* collide, const vec3_t& pos ) = 0;
	virtual void clip_ray_to_entity( const ray_t& ray, unsigned int mask, c_base_player* pl, trace_t* engine_trace ) = 0;
	virtual void clip_ray_to_collideable( const ray_t& ray, unsigned int mask, collideable_t* collide, trace_t* engine_trace ) = 0;
	virtual void trace_ray( const ray_t& ray, unsigned int mask, i_trace_filter* filter, trace_t* engine_trace ) = 0;
};