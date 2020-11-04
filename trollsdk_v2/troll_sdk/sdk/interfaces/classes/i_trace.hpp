#pragma once
#include <minwindef.h>
#include "../../math/matrix.hpp"
#include "../../math/vector.hpp"

class c_base_player;

#define	surf_light		0x0001		// value will hold the light strength
#define	surf_sky2d		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3d skybox
#define	surf_sky		0x0004		// don't draw, but add to skybox
#define	surf_warp		0x0008		// turbulent water warp
#define	surf_trans		0x0010
#define surf_noportal	0x0020	// the surface can not have a portal placed on it
#define	surf_trigger	0x0040	// fixme: this is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	surf_nodraw		0x0080	// don't bother referencing the texture
#define	surf_hint		0x0100	// make a primary bsp splitter
#define	surf_skip		0x0200	// completely ignore, allowing non-closed brushes
#define surf_nolight	0x0400	// don't calculate light
#define surf_bumplight	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define surf_noshadows	0x1000	// don't receive shadows
#define surf_nodecals	0x2000	// don't receive decals
#define surf_nopaint	0x2000	// the surface can not have paint placed on it
#define surf_nochop		0x4000	// don't subdivide patches on this surface
#define surf_hitbox		0x8000	// surface is part of a hitbox

#define char_tex_antlion		'a'
#define char_tex_bloodyflesh	'b'
#define	char_tex_concrete		'c'
#define char_tex_dirt			'd'
#define char_tex_eggshell		'e' ///< the egg sacs in the tunnels in ep2.
#define char_tex_flesh			'f'
#define char_tex_grate			'g'
#define char_tex_alienflesh		'h'
#define char_tex_clip			'i'
//#define char_tex_unused		'j'
#define char_tex_snow			'k'
#define char_tex_plastic		'l'
#define char_tex_metal			'm'
#define char_tex_sand			'n'
#define char_tex_foliage		'o'
#define char_tex_computer		'p'
//#define char_tex_unused		'q'
#define char_tex_reflective		'r'
#define char_tex_slosh			's'
#define char_tex_tile			't'
#define char_tex_cardboard		'u'
#define char_tex_vent			'v'
#define char_tex_wood			'w'
//#define char_tex_unused		'x' ///< do not use - "fake" materials use this (ladders, wading, clips, etc)
#define char_tex_glass			'y'
#define char_tex_warpshield		'z' ///< wierd-looking jello effect for advisor shield.

enum contents : uint32_t {
	contents_empty = 0,
	contents_solid = 0x1,
	contents_window = 0x2,
	contents_aux = 0x4,
	contents_grate = 0x8,
	contents_slime = 0x10,
	contents_water = 0x20,
	contents_blocklos = 0x40,
	contents_opaque = 0x80,
	last_visible_contents = contents_opaque,
	all_visible_contents = ( last_visible_contents | ( last_visible_contents - 1 ) ),
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
	contents_hitbox = 0x40000000
};

enum mask : uint32_t {
	mask_all = ( 0xffffffff ),
	mask_solid = ( contents_solid | contents_moveable | contents_window | contents_monster | contents_grate ),
	mask_playersolid = ( contents_solid | contents_moveable | contents_playerclip | contents_window | contents_monster | contents_grate ),
	mask_npcsolid = ( contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate ),
	mask_npcfluid = ( contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster ),
	mask_water = ( contents_water | contents_moveable | contents_slime ),
	mask_opaque = ( contents_solid | contents_moveable | contents_opaque ),
	mask_opaque_and_npcs = ( mask_opaque | contents_monster ),
	mask_blocklos = ( contents_solid | contents_moveable | contents_blocklos ),
	mask_blocklos_and_npcs = ( mask_blocklos | contents_monster ),
	mask_visible = ( mask_opaque | contents_ignore_nodraw_opaque ),
	mask_visible_and_npcs = ( mask_opaque_and_npcs | contents_ignore_nodraw_opaque ),
	mask_shot = ( contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_hitbox ),
	mask_shot_brushonly = ( contents_solid | contents_moveable | contents_window | contents_debris ),
	mask_shot_hull = ( contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate ),
	mask_shot_portal = ( contents_solid | contents_moveable | contents_window | contents_monster ),
	mask_solid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_grate ),
	mask_playersolid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_playerclip | contents_grate ),
	mask_npcsolid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_monsterclip | contents_grate ),
	mask_npcworldstatic = ( contents_solid | contents_window | contents_monsterclip | contents_grate ),
	mask_npcworldstatic_fluid = ( contents_solid | contents_window | contents_monsterclip ),
	mask_splitareaportal = ( contents_water | contents_slime ),
	mask_current = ( contents_current_0 | contents_current_90 | contents_current_180 | contents_current_270 | contents_current_up | contents_current_down ),
	mask_deadsolid = ( contents_solid | contents_playerclip | contents_window | contents_grate )
};

class __declspec( align( 16 ) )VectorAligned : public vec3_t {
public:
	VectorAligned& operator=( const vec3_t& vOther ) {
		init( vOther.x, vOther.y, vOther.z );
		return *this;
	}

	float w;
};

class i_handle_entity;

struct ray_t {
	VectorAligned m_start; // starting point, centered within the extents
	VectorAligned m_delta; // direction + length of the ray
	VectorAligned m_start_offset; // Add this to m_Start to get the actual ray start
	VectorAligned m_extents; // Describes an axis aligned box extruded along a ray
	const matrix_t* m_world_axis_transform;
	//const matrix_t *m_pWorldAxisTransform;
	bool m_is_ray; // are the extents zero?
	bool m_is_swept; // is delta != 0?

	ray_t( ) : m_world_axis_transform( NULL ) {}

	ray_t( vec3_t _start, vec3_t _end )
	{
		initialize( _start, _end );
	}

	ray_t( vec3_t _start, vec3_t _end, vec3_t _mins, vec3_t _maxs )
	{
		initialize( _start, _end, _mins, _maxs );
	}

	void initialize( const vec3_t& start, const vec3_t& end ) {
		m_delta = end - start;

		m_is_swept = ( m_delta.length_sqr( ) != 0 );

		m_extents.x = m_extents.y = m_extents.z = 0.0f;
		m_is_ray = true;

		m_start_offset.x = m_start_offset.y = m_start_offset.z = 0.0f;

		m_start = start;
	}

	void initialize( vec3_t& vecStart, vec3_t& vecEnd, vec3_t min, vec3_t max ) {
		m_delta = vecEnd - vecStart;

		m_is_swept = ( m_delta.length_sqr( ) != 0 );

		m_extents.x = ( max.x - min.x );
		m_extents.y = ( max.y - min.y );
		m_extents.z = ( max.z - min.z );
		m_is_ray = false;

		m_start_offset.x = m_start_offset.y = m_start_offset.z = 0.0f;

		m_start = vecStart + ( ( max + min ) * 0.5f );
	}

private:
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

struct trace_t {
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

	bool did_hit( ) const {
		return fraction < 1.f;
	}

	bool did_hit_world( ) const {
		return false;
	}

	bool did_hit_non_world_entity( ) const {
		return player != NULL && !did_hit_world( );
	}
};

enum trace_type_t {
	trace_everything = 0,
	trace_world_only, // note: this does *not* test static props!!!
	trace_entities_only, // note: this version will *not* test static props
	trace_everything_filter_props, // note: this version will pass the ihandleentity for props through the filter, unlike all other filters
};

class i_trace_filter {
public:
	virtual bool should_hit_entity( void* ent, int contents_mask ) = 0;
	virtual trace_type_t get_trace_type( ) const = 0;
};

class trace_filter : public i_trace_filter {
public:
	trace_filter( ) {}

	explicit trace_filter( c_base_player* player, trace_type_t tracetype = trace_everything )
	{
		skip = player;
	}

	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return ( entity_handle != skip );
	}

	trace_type_t get_trace_type( ) const {
		return trace_everything;
	}

	void* skip;
};

class trace_filter_one_entity : public i_trace_filter {
public:
	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return ( entity_handle == player );
	}

	trace_type_t get_trace_type( ) const {
		return trace_everything;
	}

	void* player;
};

class trace_filter_one_entity2 : public i_trace_filter {
public:
	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return ( entity_handle == player );
	}

	trace_type_t get_trace_type( ) const {
		return trace_entities_only;
	}

	void* player;
};

class trace_filter_skip_two_entities : public i_trace_filter {
public:
	trace_filter_skip_two_entities( void* ent, void* ent2 ) {
		passentity1 = ent;
		passentity2 = ent2;
	}

	virtual bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return !( entity_handle == passentity1 || entity_handle == passentity2 );
	}

	virtual trace_type_t get_trace_type( ) const {
		return trace_everything;
	}

	void* passentity1;
	void* passentity2;
};

class trace_filter_skip_one_entity : public i_trace_filter {
public:
	trace_filter_skip_one_entity( void* ent ) {
		passentity1 = ent;
	}

	virtual bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return !( entity_handle == passentity1 );
	}

	virtual trace_type_t get_trace_type( ) const {
		return trace_everything;
	}

	void* passentity1;
};

class trace_entity_t : public i_trace_filter {
public:
	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return !( entity_handle == skip );
	}

	trace_type_t get_trace_type( ) const {
		return trace_entities_only;
	}

	void* skip;
};

class trace_world_only_t : public i_trace_filter {
public:
	bool should_hit_entity( void* entity_handle, int contents_mask ) {
		return false;
	}

	trace_type_t get_trace_type( ) const {
		return trace_everything;
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