#pragma once
#include "../../math/vector.hpp"
#include "i_surface.hpp"
#include "c_input_system.hpp"

struct view_setup_t {
	__int32 x; // 0x0000
	__int32 x_old; // 0x0004
	__int32 y; // 0x0008
	__int32 y_old; // 0x000C
	__int32 width; // 0x0010
	__int32 width_old; // 0x0014
	__int32 height; // 0x0018
	__int32 height_old; // 0x001C
	char pad_0x0020[ 0x90 ]; // 0x0020
	float fov; // 0x00B0
	float viewmodel_fov; // 0x00B4
	vec3_t origin; // 0x00B8
	vec3_t angles; // 0x00C4
	char pad_0x00D0[ 0x7C ]; // 0x00D0
};

class c_usercmd;
class c_base_entity;
class c_base_player;
struct audio_state_t;
class i_client_mode {
public:
public:
	virtual			~i_client_mode( ) {}

	virtual void	init_viewport( ) = 0;
	virtual void	init( ) = 0;
	virtual void	vgui_shutdown( ) = 0;
	virtual void	shutdown( ) = 0;
	virtual void	enable( ) = 0;
	virtual void	enable_with_root_panel( vgui::vpanel proot ) = 0;
	virtual void	disable( ) = 0;
	virtual void	layout( bool force = false ) = 0;
	virtual vgui::vpanel* get_viewport( ) = 0;
	virtual vgui::vpanel* get_panel_from_viewport( const char* chname_path ) = 0;
	virtual vgui::h_font* get_viewport_animation_controller( ) = 0; // it is animation controllor but ya fuk it
	virtual void	process_input( bool active ) = 0;
	virtual bool	should_draw_detail_objects( ) = 0;
	virtual bool	should_draw_entity( c_base_entity* ent ) = 0; // hmm disable teammate render like ot does ? xd
	virtual bool	should_draw_local_player( c_base_player* player ) = 0;
	virtual bool	should_draw_particles( ) = 0;
	virtual bool	should_draw_fog( void ) = 0;
	virtual void	override_view( view_setup_t* setup ) = 0;
	virtual void	override_audio_state( audio_state_t* audiostate ) = 0;
	virtual int		key_input( int down, button_code_t keynum, const char* currentbinding ) = 0;
	virtual void	start_message_mode( int messagemodetype ) = 0;
	virtual vgui::vpanel* get_message_panel( ) = 0;
	virtual void	override_mouse_input( float* x, float* y ) = 0;
	virtual bool	create_move( float input_sampletime, c_usercmd* cmd ) = 0;
	virtual void	level_init( const char* newmap ) = 0;
	virtual void	level_shutdown( void ) = 0;
	virtual bool	should_draw_viewmodel( void ) = 0;
	virtual bool	should_draw_crosshair( void ) = 0;
	virtual void	adjust_engine_viewport( int& x, int& y, int& width, int& height ) = 0;
	virtual void	pre_render( view_setup_t* setup ) = 0;
	virtual void	post_render( void ) = 0;
	virtual void	post_render_vgui( ) = 0;
	virtual void	activate_ingame_vgui_context( vgui::vpanel* panel ) = 0;
	virtual void	deactivate_ingame_vgui_context( ) = 0;
	virtual float	get_viewmodel_fov( void ) = 0;
	virtual bool	can_record_demo( char* errormsg, int length ) const = 0;
	virtual wchar_t* get_server_name( void ) = 0;
	virtual void		set_server_name( wchar_t* name ) = 0;
	virtual wchar_t* get_map_name( void ) = 0;
	virtual void		set_map_name( wchar_t* name ) = 0;
	virtual void	on_color_correction_weights_reset( void ) = 0;
	virtual float	get_color_correction_scale( void ) const = 0;
	virtual int		hud_element_key_input( int down, button_code_t keynum, const char* currentbinding ) = 0;
	virtual void	do_post_screen_space_effects( const view_setup_t* setup ) = 0;
	virtual void	update_camera_man_ui_state( int type, int optionalparam, int xuid ) = 0;
	virtual void	score_board_off( void ) = 0;
	virtual void	graph_page_changed( void ) = 0;
public:
	// called every frame.
	virtual void	update( ) = 0;

	virtual void	set_blur_fade( float scale ) = 0;
	virtual float	get_blur_fade( void ) = 0;
};