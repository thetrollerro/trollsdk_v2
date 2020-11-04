#pragma once
#include "../math/vector.hpp"
struct matrix_t;
struct model_t;
class i_client_unknown;
class i_client_renderable;
class i_client_renderable
{
public:
	virtual i_client_unknown* get_client_unknown( ) = 0;
	virtual vec3_t const& get_render_origin( void ) = 0;
	virtual vec3_t const& get_render_angles( void ) = 0;
	virtual bool should_draw( void ) = 0;
	virtual uint32_t render_flags( void ) = 0;
	virtual void unknown( void ) const {}
	virtual unsigned short get_shadow_handle( ) const = 0;
	virtual unsigned short& render_andle( ) = 0;
	virtual model_t* get_model( ) const = 0;
	virtual int draw_model( int flags, const uint32_t& instance ) = 0;
	virtual int get_body( ) = 0;
	virtual void get_color_modulation( float* color ) = 0;
	virtual bool lod_test( ) = 0;
	virtual bool setup_bones( matrix_t* bone_to_world_out, int max_bones, uint32_t mask, float curr_time ) = 0;
	virtual void setup_weights( const matrix_t* bone_to_world_out, int flex_weight_count, float* flex_weights, float* flex_delayed_weights ) = 0;
	virtual void do_animation_events( void ) = 0;
	virtual void* get_pvs_notify_interface( ) = 0;
	virtual void get_render_bounds( vec3_t& mins, vec3_t& maxs ) = 0;
	virtual void get_render_bounds_world_space( vec3_t& mins, vec3_t& maxs ) = 0;
	virtual void get_shadow_render_bounds( vec3_t& mins, vec3_t& maxs, uint32_t shadow_type ) = 0;
	virtual bool should_receive_projected_textures( int flags ) = 0;
	virtual bool get_shadow_cast_distance( float* pDist, uint32_t shadow_type ) const = 0;
	virtual bool get_shadow_cast_direction( vec3_t, uint32_t shadow_type ) const = 0;
	virtual bool is_shadow_dirty( ) = 0;
	virtual void mark_shadow_dirty( bool dirty ) = 0;
	virtual i_client_renderable* get_shadow_parent( ) = 0;
	virtual i_client_renderable* first_shadow_child( ) = 0;
	virtual i_client_renderable* next_shadow_peer( ) = 0;
	virtual uint32_t shadow_cast_Type( ) = 0;
	virtual void create_model_instance( ) = 0;
	virtual unsigned short get_model_instance( ) = 0;
	virtual const matrix_t& renderable_to_world_transform( ) = 0;
	virtual int lookup_attachment( const char* attachment_name ) = 0;
	virtual bool get_attachment( int number, vec3_t& origin, vec3_t& angles ) = 0;
	virtual bool get_attachment( int number, matrix_t& matrix ) = 0;
	virtual float* get_render_clip_plane( void ) = 0;
	virtual int get_skin( ) = 0;
	virtual void on_threaded_draw_setup( ) = 0;
	virtual bool uses_flex_delayed_weights( ) = 0;
	virtual void record_tool_message( ) = 0;
	virtual bool should_draw_for_split_screen_user( int slot ) = 0;
	virtual uint8_t override_alpha_modulation( uint8_t alpha ) = 0;
	virtual uint8_t override_shadow_alpha_modulation( uint8_t alpha ) = 0;
};