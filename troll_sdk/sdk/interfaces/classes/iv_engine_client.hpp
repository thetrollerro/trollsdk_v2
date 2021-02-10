#pragma once
#include <cstdint>
#include "../../math/vector.hpp"
#include "../../math/matrix.hpp"
#include "../../../utilities/utilities.hpp"

typedef struct player_info_s
{
	__int64         unknown;
	union
	{
		__int64       steam_id64;
		struct
		{
			__int32     xuid_low;
			__int32     xuid_high;
		};
	};
	char            name[ 128 ];
	int             used_id;
	char            szsteam_id[ 20 ];
	char            pad_0x00A8[ 0x10 ];
	unsigned long   steam_id;
	char            friends_name[ 128 ];
	bool            fake_player;
	bool            is_hltv;
	unsigned int    custom_files[ 4 ];
	unsigned char   files_downloaded;
} player_info_t;

#define flow_outgoing	0		
#define flow_incoming	1
#define max_flows		2		// in & out

class i_net_channel {
public:
	uint8_t pad_0x0000[ 0x17 ];
	bool should_delete;
	int out_sequence_nr;
	int in_sequence_nr;
	int out_sequence_nr_ack;
	int out_reliable_state;
	int in_reliable_state;
	int choked_packets;
};

class i_net_message {
public:
	virtual	~i_net_message( ) {};

	virtual void set_net_channel( void* netchan ) = 0;
	virtual void set_reliable( bool state ) = 0;

	virtual bool process( void ) = 0;

	virtual	bool read_from_buffer( bf_read& buffer ) = 0;
	virtual	bool write_to_buffer( bf_write& buffer ) = 0;

	virtual bool is_reliable( void ) const = 0;

	virtual int get_type( void ) const = 0;
	virtual int get_group( void ) const = 0;
	virtual const char* get_name( void ) const = 0;
	virtual void* get_net_channel( void ) const = 0;
	virtual const char* to_string( void ) const = 0;
};

class i_net_channel_info {
public:

	enum {
		generic = 0,	// must be first and is default group
		localplayer,	// bytes for local player entity update
		otherplayers,	// bytes for other players update
		entities,		// all other entity bytes
		sounds,			// game sounds
		events,			// event messages
		usermessages,	// user messages
		entmessages,	// entity messages
		voice,			// voice data
		stringtable,	// a stringtable update
		move,			// client move cmds
		stringcmd,		// string command
		signon,			// various signondata
		total,			// must be last and is not a real group
	};

	virtual const char* get_name( void ) const = 0;	// get channel name
	virtual const char* get_address( void ) const = 0; // get channel IP address as string
	virtual float		get_time( void ) const = 0;	// current net time
	virtual float		get_time_connected( void ) const = 0;	// get connection time in seconds
	virtual int			get_buffer_size( void ) const = 0;	// netchannel packet history size
	virtual int			get_data_rate( void ) const = 0; // send data rate in byte/sec

	virtual bool		is_loop_back( void ) const = 0;	// true if loopback channel
	virtual bool		is_timing_out( void ) const = 0;	// true if timing out
	virtual bool		is_play_back( void ) const = 0;	// true if demo playback

	virtual float		get_latency( int flow ) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		get_average_latency( int flow ) const = 0; // average packet latency in seconds
	virtual float		get_average_loss( int flow ) const = 0;	 // avg packet loss[0..1]
	virtual float		get_average_choke( int flow ) const = 0;	 // avg packet choke[0..1]
	virtual float		get_average_data( int flow ) const = 0;	 // data flow in bytes/sec
	virtual float		get_average_packets( int flow ) const = 0; // avg packets/sec
	virtual int			get_total_data( int flow ) const = 0;	 // total flow in/out in bytes
	virtual int			get_sequence_number( int flow ) const = 0;	// last send seq number
	virtual bool		is_valid_packet( int flow, int frame_number ) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		get_packet_time( int flow, int frame_number ) const = 0; // time when packet was send
	virtual int			get_packet_bytes( int flow, int frame_number, int group ) const = 0; // group size of this packet
	virtual bool		get_stream_progress( int flow, int* received, int* total ) const = 0;  // TCP progress if transmitting
	virtual float		get_since_last_time_recieved( void ) const = 0;	// get time since last recieved packet in seconds
	virtual	float		get_command_interpolation_ammount( int flow, int frame_number ) const = 0;
	virtual void		get_packet_response_latency( int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke ) const = 0;
	virtual void		get_remote_framerate( float* pflFrameTime, float* pflFrameTimeStdDeviation ) const = 0;

	virtual float		get_timeout_seconds( ) const = 0;
};

class i_material;
class c_key_values;
class i_material_system;
struct model_t;
struct client_textmessage_t;
class i_game_stats_data;
class isp_shared_memory;
class c_sentence;
class c_audio_source;
class i_spatial_query;
struct frustum_t;
class audio_state_t;
class surf_info;
class i_achievment_mgr;
class c_phys_collide;
class c_steam_api_context;
typedef struct InputContextHandle_t__* InputContextHandle_t;
typedef void( *pfndemocustomdatacallback )( uint8_t*, size_t );
class iv_engine_client {
public:
	virtual int                   get_intersecting_surfaces( const model_t* model, const vec3_t& vCenter, const float radius, const bool bOnlyVisibleSurfaces, surf_info* pInfos, const int nMaxInfos ) = 0;
	virtual vec3_t                get_light_for_point( const vec3_t& pos, bool bClamp ) = 0;
	virtual i_material* trace_line_material_and_lighting( const vec3_t& start, const vec3_t& end, vec3_t& diffuseLightColor, vec3_t& baseColor ) = 0;
	virtual const char* parse_file( const char* data, char* token, int maxlen ) = 0;
	virtual bool                  copy_file( const char* source, const char* destination ) = 0;
	virtual void                  get_screen_size( int& width, int& height ) = 0;
	virtual void                  server_cmd( const char* szCmdString, bool bReliable = true ) = 0;
	virtual void                  client_cmd( const char* szCmdString ) = 0;
	virtual bool                  get_player_info( int ent_num, player_info_t* pinfo ) = 0;
	virtual int                   get_player_for_userid( int userID ) = 0;
	virtual client_textmessage_t* text_message_get( const char* pName ) = 0; // 10
	virtual bool                  con_is_visible( void ) = 0;
	virtual int                   get_local_player( void ) = 0;
	virtual const model_t* load_model( const char* pName, bool bProp = false ) = 0;
	virtual float                 get_last_time_stamp( void ) = 0;
	virtual c_sentence* get_sentence( c_audio_source* pAudioSource ) = 0; // 15
	virtual float                 get_sentence_length( c_audio_source* pAudioSource ) = 0;
	virtual bool                  is_streaming( c_audio_source* pAudioSource ) const = 0;
	virtual void                  get_viewangles( vec3_t& va ) = 0;
	virtual void                  set_viewangles( vec3_t& va ) = 0;
	virtual int                   get_max_clients( void ) = 0; // 20
	virtual const char* key_lookup_binding( const char* pBinding ) = 0;
	virtual const char* key_binding_for_key( int& code ) = 0;
	virtual void                  key_set_binding( int, char const* ) = 0;
	virtual void                  start_key_trap_mode( void ) = 0;
	virtual bool                  check_done_key_trapping( int& code ) = 0;
	virtual bool                  is_in_game( void ) = 0;
	virtual bool                  is_connected( void ) = 0;
	virtual bool                  is_drawing_loading_image( void ) = 0;
	virtual void                  hide_loading_plague( void ) = 0;
	virtual void                  con_nprintf( int pos, const char* fmt, ... ) = 0; // 30
	virtual void                  con_nxprintf( const struct con_nprint_s* info, const char* fmt, ... ) = 0;
	virtual int                   is_box_visible( const vec3_t& mins, const vec3_t& maxs ) = 0;
	virtual int                   is_box_in_view_cursor( const vec3_t& mins, const vec3_t& maxs ) = 0;
	virtual bool                  cull_box( const vec3_t& mins, const vec3_t& maxs ) = 0;
	virtual void                  sound_extra_update( void ) = 0;
	virtual const char* get_game_directory( void ) = 0;
	virtual const matrix_t& world_to_screen_matrix( ) = 0;
	virtual const matrix_t& world_to_view_matrix( ) = 0;
	virtual int                   game_lump_version( int lumpId ) const = 0;
	virtual int                   game_lump_size( int lumpId ) const = 0; // 40
	virtual bool                  load_game_lump( int lumpId, void* pBuffer, int size ) = 0;
	virtual int                   level_leaf_count( ) const = 0;
	virtual i_spatial_query* get_bsp_tree_query( ) = 0;
	virtual void                  linear_to_gamma( float* linear, float* gamma ) = 0;
	virtual float                 light_style_value( int style ) = 0; // 45
	virtual void                  compute_dynamic_lighting( const vec3_t& pt, const vec3_t* pNormal, vec3_t& color ) = 0;
	virtual void                  get_ambient_light_color( vec3_t& color ) = 0;
	virtual int                   get_dx_suport_level( ) = 0;
	virtual bool                  supports_hdr( ) = 0;
	virtual void                  mat_stub( i_material_system* pMatSys ) = 0; // 50
	virtual void                  get_chapter_name( char* pchBuff, int iMaxLength ) = 0;
	virtual char const* get_level_name( void ) = 0;
	virtual char const* get_level_name_short( void ) = 0;
	virtual char const* get_map_group_name( void ) = 0;
	virtual struct voice_tweak_s* get_voice_tweak_api( void ) = 0;
	virtual void                  set_voice_caster_id( unsigned int someint ) = 0; // 56
	virtual void                  enginestats_beginframe( void ) = 0;
	virtual void                  enginestats_endframe( void ) = 0;
	virtual void                  fire_game_event( ) = 0;
	virtual int                   get_leaves_area( unsigned short* pLeaves, int nLeaves ) = 0;
	virtual bool                  does_box_touch_area_frustum( const vec3_t& mins, const vec3_t& maxs, int iArea ) = 0; // 60
	virtual int                   get_frustum_list( frustum_t** pList, int listMax ) = 0;
	virtual bool                  should_use_area_frustum( int i ) = 0;
	virtual void                  set_audio_state( const audio_state_t& state ) = 0;
	virtual int                   sentence_group_pick( int groupIndex, char* name, int nameBufLen ) = 0;
	virtual int                   sentence_group_pick_senquentical( int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset ) = 0;
	virtual int                   sentence_index_from_name( const char* pSentenceName ) = 0;
	virtual const char* sentence_name_from_index( int sentenceIndex ) = 0;
	virtual int                   sentence_groupname_from_name( const char* pGroupName ) = 0;
	virtual const char* sentence_groupname_from_index( int groupIndex ) = 0;
	virtual float                 sentence_length( int sentenceIndex ) = 0;
	virtual void                  compute_lighting( const vec3_t& pt, const vec3_t* pNormal, bool bClamp, vec3_t& color, vec3_t* pBoxColors = NULL ) = 0;
	virtual void                  activate_occluder( int nOccluderIndex, bool bActive ) = 0;
	virtual bool                  is_occluded( const vec3_t& vecAbsMins, const vec3_t& vecAbsMaxs ) = 0; // 74
	virtual int                   get_occlusion_view_id( void ) = 0;
	virtual void* save_alloc_memory( size_t num, size_t size ) = 0;
	virtual void                  save_free_memory( void* pSaveMem ) = 0;
	virtual i_net_channel_info* get_net_channel_info( void ) = 0;
	virtual void                  debug_draw_phys_collide( const c_phys_collide* pCollide, i_material* pMaterial, const matrix_t& transform, const uint8_t* color ) = 0; //79
	virtual void                  check_point( const char* pName ) = 0; // 80
	virtual void                  draw_portals( ) = 0;
	virtual bool                  is_playing_demo( void ) = 0;
	virtual bool                  is_recording_demo( void ) = 0;
	virtual bool                  is_playing_time_demo( void ) = 0;
	virtual int                   get_demo_recording_tick( void ) = 0;
	virtual int                   get_demoplaybacktick( void ) = 0;
	virtual int                   get_demoplaybackstarttick( void ) = 0;
	virtual float                 get_demoplaybacktimescale( void ) = 0;
	virtual int                   get_demoplaybacktotalticks( void ) = 0;
	virtual bool                  is_paused( void ) = 0; // 90
	virtual float                 get_time_scale( void ) const = 0;
	virtual bool                  is_taking_screenshot( void ) = 0;
	virtual bool                  is_hltv( void ) = 0;
	virtual bool                  is_level_mainmenu_background( void ) = 0;
	virtual void                  get_mainmenu_background_name( char* dest, int destlen ) = 0;
	virtual void                  set_occlusion_parameters( const int /*occlusionparams_t*/& params ) = 0; // 96
	virtual void                  get_ui_language( char* dest, int destlen ) = 0;
	virtual int                   is_skybox_visible_from_point( const vec3_t& vecpoint ) = 0;
	virtual const char* get_map_entities_string( ) = 0;
	virtual bool                  is_in_edit_mode( void ) = 0; // 100
	virtual float                 get_screen_aspectratio( int viewportwidth, int viewportheight ) = 0;
	virtual bool                  removed_steam_refresh_login( const char* password, bool issecure ) = 0;
	virtual bool                  removed_steam_process_call( bool& finished ) = 0;
	virtual unsigned int          get_engine_build_number( ) = 0; // engines build
	virtual const char* get_product_version_string( ) = 0; // mods version number (steam.inf)
	virtual void                  grab_precolor_corrected_frame( int x, int y, int width, int height ) = 0;
	virtual bool                  is_hammer_running( ) const = 0;
	virtual void                  execute_client_cmd( const char* szcmdstring ) = 0; //108
	virtual bool                  map_hash_drlighting( void ) = 0;
	virtual bool                  map_has_light_map_alpha_data( void ) = 0;
	virtual int                   get_appid( ) = 0;
	virtual vec3_t                get_light_for_point_fast( const vec3_t& pos, bool bclamp ) = 0;
	virtual void                  clientcmd_unrestricted( char  const*, int, bool ) = 0;
	virtual void                  clientcmd_unrestricted( const char* szcmdstring ) = 0; // 114
	virtual void                  set_restrict_server_commands( bool brestrict ) = 0;
	virtual void                  set_restrict_client_commands( bool brestrict ) = 0;
	virtual void                  set_overlay_bind_proxy( int ioverlayid, void* pbindproxy ) = 0;
	virtual bool                  copy_framebuffer_to_material( const char* pmaterialname ) = 0;
	virtual void                  read_configuration( const int icontroller, const bool readdefault ) = 0;
	virtual void                  set_achievementmgr( i_achievment_mgr* pachievementmgr ) = 0;
	virtual i_achievment_mgr* get_achievementmgr( ) = 0;
	virtual bool                  map_load_failed( void ) = 0;
	virtual void                  set_map_load_failed( bool bstate ) = 0;
	virtual bool                  is_low_violence( ) = 0;
	virtual const char* get_most_recent_savegame( void ) = 0;
	virtual void                  set_most_recent_savegame( const char* lpszfilename ) = 0;
	virtual void                  start_xbox_exiting_process( ) = 0;
	virtual bool                  is_save_in_progress( ) = 0;
	virtual bool                  isautosavedangerousinprogress( void ) = 0;
	virtual unsigned int          onstoragedeviceattached( int icontroller ) = 0;
	virtual void                  onstoragedevicedetached( int icontroller ) = 0;
	virtual const char* get_saved_irname( void ) = 0;
	virtual void                  write_screenshot( const char* pfilename ) = 0;
	virtual void                  reset_demointerpolation( void ) = 0;
	virtual int                   get_active_split_screen_player_slot( ) = 0;
	virtual int                   set_active_split_screen_player_slot( int slot ) = 0;
	virtual bool                  set_local_player_is_resolvable( char const* pchcontext, int nline, bool bResolvable ) = 0;
	virtual bool                  is_local_player_resolvable( ) = 0;
	virtual int                   get_split_screen_player( int nslot ) = 0;
	virtual bool                  is_split_screenactive( ) = 0;
	virtual bool                  is_valid_split_screenslot( int nslot ) = 0;
	virtual int                   first_valid_split_screenslot( ) = 0; // -1 == invalid
	virtual int                   next_valid_split_screenslot( int npreviousslot ) = 0; // -1 == invalid
	virtual isp_shared_memory* get_single_player_shared_memoryspace( const char* szname, int ent_num = ( 1 << 11 ) ) = 0;
	virtual void                  compute_lighting_cube( const vec3_t& pt, bool bclamp, vec3_t* pboxColors ) = 0;
	virtual void                  register_demo_custom_data_call_back( const char* szcallbacksaveid, pfndemocustomdatacallback pCallback ) = 0;
	virtual void                  record_demo_custom_data( pfndemocustomdatacallback pcallback, const void* pData, size_t iDataLength ) = 0;
	virtual void                  set_pitch_scale( float flpitchscale ) = 0;
	virtual float                 get_pitch_scale( void ) = 0;
	virtual bool                  loadfilmmaker( ) = 0;
	virtual void                  unloadfilmmaker( ) = 0;
	virtual void                  set_leaf_flag( int nleafindex, int nflagbits ) = 0;
	virtual void                  recalculate_bsp_leafflags( void ) = 0;
	virtual bool                  dsp_get_current_das_room_new( void ) = 0;
	virtual bool                  dsp_get_current_das_room_changed( void ) = 0;
	virtual bool                  dsp_get_current_das_room_skyabove( void ) = 0;
	virtual float                 dsp_get_current_das_room_skypercent( void ) = 0;
	virtual void                  set_mix_group_of_current_mixer( const char* szgroupname, const char* szparam, float val, int setMixerType ) = 0;
	virtual int                   get_mix_layerindex( const char* szmixlayername ) = 0;
	virtual void                  set_mix_layer_level( int index, float level ) = 0;
	virtual int                   get_mix_group_index( char  const* groupname ) = 0;
	virtual void                  set_mix_layer_trigger_factor( int i1, int i2, float fl ) = 0;
	virtual void                  set_mix_layer_trigger_factor( char  const* char1, char  const* char2, float fl ) = 0;
	virtual bool                  is_creating_res_list( ) = 0;
	virtual bool                  is_creating_xboxresvlist( ) = 0;
	virtual void                  set_timescale( float fltimescale ) = 0;
	virtual void                  set_game_stats_data( i_game_stats_data* pgamestatsdata ) = 0;
	virtual i_game_stats_data* get_game_stats_data( ) = 0;
	virtual void                  get_mouse_delta( int& dx, int& dy, bool b ) = 0; // unknown
	virtual   const char* key_lookupbindingex( const char* pbinding, int iuserid = -1, int istartCount = 0, int iAllowJoystick = -1 ) = 0;
	virtual int                   key_codeforbinding( char  const*, int, int, int ) = 0;
	virtual void                  update_dande_lights( void ) = 0;
	virtual int                   get_bugs_ubmission_count( ) const = 0;
	virtual void                  clear_bug_submission_count( ) = 0;
	virtual bool                  does_level_contain_water( ) const = 0;
	virtual float                 get_server_simulation_frame_time( ) const = 0;
	virtual void                  solid_moved( class c_client_entity* psolident, class c_collideable* pSolidCollide, const vec3_t* pPrevAbsOrigin, bool accurateBboxTriggerChecks ) = 0;
	virtual void                  trigger_moved( class c_client_entity* ptriggerent, bool accurateBboxTriggerChecks ) = 0;
	virtual void                  compute_leaves_connected( const vec3_t& vecorigin, int ncount, const int* pLeafIndices, bool* pIsConnected ) = 0;
	virtual bool                  is_in_commentary_mode( void ) = 0;
	virtual void                  set_blur_fade( float amount ) = 0;
	virtual bool                  is_transitioning_to_load( ) = 0;
	virtual void                  search_paths_changed_after_install( ) = 0;
	virtual void                  configure_system_level( int ncpulevel, int ngpulevel ) = 0;
	virtual void                  set_connection_password( char const* pchcurrentpw ) = 0;
	virtual c_steam_api_context* get_steam_apicontext( ) = 0;
	virtual void                  submit_stat_record( char const* szmapname, unsigned int uiblobversion, unsigned int uiBlobSize, const void* pvBlob ) = 0;
	virtual void                  server_cmd_keyvalues( c_key_values* pkeyvalues ) = 0; // 203
	virtual void                  sphere_paints_urface( const model_t* model, const vec3_t& location, unsigned char chr, float fl1, float fl2 ) = 0;
	virtual bool                  has_paint_map( void ) = 0;
	virtual void                  enable_paint_map_render( ) = 0;
	virtual void                tracepaintsurface( const model_t* model, const vec3_t& position, float radius, int& surfColors ) = 0;
	virtual void                  sphere_trace_paint_surface( const model_t* model, const vec3_t& position, const vec3_t& vec2, float radius, /*CUtlVector<unsigned char, CUtlMemory<unsigned char, int>>*/ int& utilVecShit ) = 0;
	virtual void                  removeall_paint( ) = 0;
	virtual void                  paintall_surfaces( unsigned char uchr ) = 0;
	virtual void                  remove_paint( const model_t* model ) = 0;
	virtual bool                  is_active_app( ) = 0;
	virtual bool                  is_client_local_to_active_server( ) = 0;
	virtual void                  tickprogressbar( ) = 0;
	virtual InputContextHandle_t  get_input_context( int /*engineinputcontextid_t*/ id ) = 0;
	virtual void                  get_startup_image( char* filename, int size ) = 0;
	virtual bool                  is_using_local_network_backdoor( void ) = 0;
	virtual void                  save_game( const char*, bool, char*, int, char*, int ) = 0;
	virtual void                  get_generic_memory_stats(/* genericmemorystat_t */ void** ) = 0;
	virtual bool                  game_has_shutdown_and_flushedmemory( void ) = 0;
	virtual int                   get_last_acknowledged_command( void ) = 0;
	virtual void                  finish_container_writes( int i ) = 0;
	virtual void                  finish_async_save( void ) = 0;
	virtual int                   get_server_tick( void ) = 0;
	virtual const char* get_mod_directory( void ) = 0;
	virtual bool                  audio_lang_changed( void ) = 0;
	virtual bool                  is_autosave_in_progress( void ) = 0;
	virtual void                  start_loading_screen_for_command( const char* command ) = 0;
	virtual void                  start_loading_screen_for_keyvalues( c_key_values* values ) = 0;
	virtual void                  sosset_opvar_float( const char*, float ) = 0;
	virtual void                  sosget_opvar_float( const char*, float& ) = 0;
	virtual bool                  is_subscribed_map( const char*, bool ) = 0;
	virtual bool                  is_featured_map( const char*, bool ) = 0;
	virtual void                  get_demo_playback_event_parameters( void ) = 0;
	virtual int                   get_client_version( void ) = 0;
	virtual bool                  is_demo_skipping( void ) = 0;
	virtual void                  set_demo_important_event_data( const c_key_values* values ) = 0;
	virtual void                  clear_events( void ) = 0;
	virtual int                   get_safezone_xmin( void ) = 0;
	virtual bool                  is_voice_recording( void ) = 0;
	virtual void                  force_voice_record_on( void ) = 0;
	virtual bool                  is_replay( void ) = 0;

	i_net_channel* get_net_channel( ) // i wanna fucking die
	{
		typedef i_net_channel* ( __thiscall* fn )( void* );
		return utils::call_virtual<fn>( this, 78 )( this );
	}
};