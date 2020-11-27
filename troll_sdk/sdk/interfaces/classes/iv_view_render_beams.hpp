#pragma once
#include "../../math/vector.hpp"
#include "../../math/matrix.hpp"
#include <winnt.h>
#include "i_trace.hpp"

enum
{
	te_beampoints = 0x00,		// beam effect between two points
	te_sprite = 0x01,	// additive sprite, plays 1 cycle
	te_beamdisk = 0x02,	// disk that expands to max radius over lifetime
	te_beamcylinder = 0x03,		// cylinder that expands to max radius over lifetime
	te_beamfollow = 0x04,		// create a line of decaying beam segments until entity stops moving
	te_beamring = 0x05,		// connect a beam ring to two entities
	te_beamspline = 0x06,
	te_beamringpoint = 0x07,
	te_beamlaser = 0x08,		// fades according to viewpoint
	te_beamtesla = 0x09,
};
enum
{
	fbeam_startentity = 0x00000001,
	fbeam_endentity = 0x00000002,
	fbeam_fadein = 0x00000004,
	fbeam_fadeout = 0x00000008,
	fbeam_sinenoise = 0x00000010,
	fbeam_solid = 0x00000020,
	fbeam_shadein = 0x00000040,
	fbeam_shadeout = 0x00000080,
	fbeam_onlynoiseonce = 0x00000100,		// Only calculate our noise once
	fbeam_notile = 0x00000200,
	fbeam_use_hitboxes = 0x00000400,		// Attachment indices represent hitbox indices instead when this is set.
	fbeam_startvisible = 0x00000800,		// Has this client actually seen this beam's start entity yet?
	fbeam_endvisible = 0x00001000,		// has this client actually seen this beam's end entity yet?
	fbeam_isactive = 0x00002000,
	fbeam_forever = 0x00004000,
	fbeam_halobeam = 0x00008000,		// when drawing a beam with a halo, don't ignore the segments and endwidth
	fbeam_reversed = 0x00010000,
	num_beam_flags = 17	// keep this updated!
};

struct beam_trail_t
{
	// NOTE:  Don't add user defined fields except after these four fields.
	beam_trail_t* next;
	float			die;
	vec3_t			org;
	vec3_t			vel;
};

#define noise_divisions		128
#define max_beam_ents		10


typedef int pixelvis_handle_t;

class beam_t
{
public:
	beam_t( );

	// Methods of IClientRenderable
	virtual const vec3_t& get_render_origin( void ) = 0;
	virtual const vec3_t& get_render_angles( void ) = 0;
	virtual const matrix_t& renderable_to_world_transform( ) = 0;
	virtual void			get_render_bounds( vec3_t& mins, vec3_t& maxs ) = 0;
	virtual bool			should_draw( void ) = 0;
	virtual bool			is_transparent( void ) = 0;
	virtual int				draw_model( int flags ) = 0;
	virtual void			compute_fx_blend( ) = 0;
	virtual int				get_fx_blend( ) = 0;

	// Resets the beam state
	void			reset( );

	// Method to computing the bounding box
	void			compute_bounds( );

	// Bounding box...
	vec3_t			mins;
	vec3_t			maxs;
	pixelvis_handle_t* query_handle_halo;
	float			halo_proxy_size;

	// Data is below..

	// Next beam in list
	beam_t* next;

	// Type of beam
	int				type;
	int				flags;

	// Control points for the beam
	int				num_attachments;
	vec3_t			attachment[ max_beam_ents ];
	vec3_t			delta;

	// 0 .. 1 over lifetime of beam
	float			t;
	float			freq;

	// Time when beam should die
	float			die;
	float			width;
	float			end_width;
	float			fade_length;
	float			amplitude;
	float			life;

	// Color
	float			r, g, b;
	float			brightness;

	// Speed
	float			speed;

	// Animation
	float			frame_rate;
	float			frame;
	int				segments;

	// Attachment entities for the beam
	HANDLE			entity[ max_beam_ents ];
	int				attachmentindex[ max_beam_ents ];

	// Model info
	int				model_index;
	int				halo_index;

	float			halo_scale;
	int				frame_count;

	float			rg_noise[ noise_divisions + 1 ];

	// Popcorn trail for beam follows to use
	beam_trail_t* trail;

	// for TE_BEAMRINGPOINT
	float			start_radius;
	float			end_radius;

	// for FBEAM_ONLYNOISEONCE
	bool			calculated_noise;

	float			hdr_color_scale;

};
class c_base_player;
struct beam_info_t
{
	//beam
	int				m_type;
	c_base_player* m_start_ent;
	int				m_start_attachment;
	c_base_player* m_endent;
	int				m_nendattachment;
	vec3_t			m_vecstart;
	vec3_t			m_vecend;
	int				m_modelindex;
	const char* m_szmodelname;
	int				m_haloindex;
	const char* m_szhaloname;
	float			m_haloscale;
	float			m_life;
	float			m_width;
	float			m_endwidth;
	float			m_fadelength;
	float			m_amplitude;
	float			m_brightness;
	float			m_speed;
	int				m_startframe;
	float			m_framerate;
	float			m_red;
	float			m_green;
	float			m_blue;
	bool			m_brenderable;
	int				m_segments;
	int				m_nflags;
	// rings
	vec3_t			m_vec_center;
	float			m_start_radius;
	float			m_end_radius;

	beam_info_t( )
	{
		m_type = te_beampoints;
		m_segments = -1;
		m_szmodelname = nullptr;
		m_szhaloname = nullptr;
		m_modelindex = -1;
		m_haloindex = -1;
		m_brenderable = true;
		m_nflags = 0;
	}
};

class c_beam;
class iv_view_render_beams
{
public:
	virtual void	init_beams( void ) = 0;
	virtual void	shut_down_beams( void ) = 0;
	virtual void	clear_beams( void ) = 0;

	// updates the state of the temp ent beams
	virtual void	update_temp_ent_beams( ) = 0;

	virtual void	draw_beam( c_beam* pbeam, i_trace_filter* pentitybeamtracefilter = nullptr ) = 0;
	virtual void	draw_beam( beam_t* pbeam ) = 0;

	virtual void	kill_dead_beams( c_base_player* pent ) = 0;

	// new interfaces!
	virtual beam_t* create_beaments( beam_info_t& beaminfo ) = 0;
	virtual beam_t* create_beament_point( beam_info_t& beaminfo ) = 0;
	virtual	beam_t* create_beam_points( beam_info_t& beaminfo ) = 0;
	virtual beam_t* create_beam_ring( beam_info_t& beaminfo ) = 0;
	virtual beam_t* create_beam_ring_point( beam_info_t& beaminfo ) = 0;
	virtual beam_t* create_beam_circle_points( beam_info_t& beaminfo ) = 0;
	virtual beam_t* create_beam_follow( beam_info_t& beaminfo ) = 0;

	virtual void	free_beam( beam_t* pbeam ) = 0;
	virtual void	update_beam_info( beam_t* pbeam, beam_info_t& beaminfo ) = 0;

	// these will go away!
	virtual void	create_beaments( int startent, int endent, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float amplitude, float brightness, float speed, int startframe, float framerate, float r, float g, float b, int type = -1 ) = 0;
	virtual void	create_beament_point( int	nstartentity, const vec3_t* pstart, int nendentity, const vec3_t* pend, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float amplitude, float brightness, float speed, int startframe, float framerate, float r, float g, float b ) = 0;
	virtual void	create_beam_points( vec3_t& start, vec3_t& end, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float amplitude, float brightness, float speed, int startframe, float framerate, float r, float g, float b ) = 0;
	virtual void	create_beam_ring( int startent, int endent, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float amplitude, float brightness, float speed, int startframe, float framerate, float r, float g, float b, int flags = 0 ) = 0;
	virtual void	create_beam_ring_point( const vec3_t& center, float start_radius, float end_radius, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float amplitude, float brightness, float speed, int startframe, float framerate, float r, float g, float b, int flags = 0 ) = 0;
	virtual void	create_beam_circle_points( int type, vec3_t& start, vec3_t& end, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float amplitude, float brightness, float speed, int startframe, float framerate, float r, float g, float b ) = 0;
	virtual void	create_beam_follow( int startent, int modelindex, int haloindex, float haloscale, float life, float width, float m_nendwidth, float m_nfadelength, float r, float g, float b, float brightness ) = 0;
};