#pragma once
#include "c_base_combat_weapon.hpp"
#include "../interfaces/interfaces.hpp"
#include "i_client_entity.hpp"
#include "../../utilities/math/math.hpp"
#include "c_base_entity.hpp"

class c_base_player;

enum data_update_type_t {
	data_update_created = 0,
	data_update_datatable_changed,
};

enum client_frame_stage_t {
	frame_undefined = -1,
	frame_start,
	frame_net_update_start,
	frame_net_update_postdataupdate_start,
	frame_net_update_postdataupdate_end,
	frame_net_update_end,
	frame_render_start,
	frame_render_end
};

enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_flags {
	fl_onground = ( 1 << 0 ),
	fl_ducking = ( 1 << 1 ),
	fl_waterjump = ( 1 << 2 ),
	fl_ontrain = ( 1 << 3 ),
	fl_inrain = ( 1 << 4 ),
	fl_frozen = ( 1 << 5 ),
	fl_atcontrols = ( 1 << 6 ),
	fl_client = ( 1 << 7 ),
	fl_fakeclient = ( 1 << 8 ),
	fl_inwater = ( 1 << 9 ),
	fl_fly = ( 1 << 10 ),
	fl_swim = ( 1 << 11 ),
	fl_conveyor = ( 1 << 12 ),
	fl_npc = ( 1 << 13 ),
	fl_godmode = ( 1 << 14 ),
	fl_notarget = ( 1 << 15 ),
	fl_aimtarget = ( 1 << 16 ),
	fl_partialground = ( 1 << 17 ),
	fl_staticprop = ( 1 << 18 ),
	fl_graphed = ( 1 << 19 ),
	fl_grenade = ( 1 << 20 ),
	fl_stepmovement = ( 1 << 21 ),
	fl_donttouch = ( 1 << 22 ),
	fl_basevelocity = ( 1 << 23 ),
	fl_worldbrush = ( 1 << 24 ),
	fl_object = ( 1 << 25 ),
	fl_killme = ( 1 << 26 ),
	fl_onfire = ( 1 << 27 ),
	fl_dissolving = ( 1 << 28 ),
	fl_transragdoll = ( 1 << 29 ),
	fl_unblockable_by_player = ( 1 << 30 )
};

/* other structs */
class c_bone_acessor {
public:
	int get_readable( ) {
		return m_readable;
	}

	void set_readable( int flags ) {
		m_readable = flags;
	}

	int get_writeable( ) {
		return m_writeable;
	}

	void set_writeable( int flags ) {
		m_writeable = flags;
	}

	const matrix_t& get_bone( int bone ) const {
		return m_bones[ bone ];
	}

	matrix_t& get_bone_for_write( int bone ) {
		return m_bones[ bone ];
	}

	matrix_t* get_bone_arr_for_write( ) const {
		return m_bones;
	};

	void set_bone_arr_for_write( matrix_t* bone ) {
		m_bones = bone;
	}

private:
	const void* m_animating;
	matrix_t* m_bones;
	int m_readable;
	int m_writeable;
};

struct animstate_pose_param_cache_t {
	std::uint8_t pad_0x0[ 0x4 ]; //0x0
	std::uint32_t m_idx; //0x4 
	char* m_name; //0x8

	void set_value( c_base_player* e, float val );
};

class animstate_t {
public:
	std::uint8_t pad_0x0000[ 0x4 ]; //0x0000
	bool m_force_update; //0x0005 
	std::uint8_t pad_0x0006[ 0x5A ]; //0x0006
	c_base_player* m_entity; //0x0060 
	c_base_combat_weapon* m_weapon; //0x0064 
	c_base_combat_weapon* m_last_weapon; //0x0068 
	float m_last_clientside_anim_update; //0x006C 
	uint32_t m_last_clientside_anim_framecount; //0x0070 
	float m_last_clientside_anim_update_time_delta; //0x0074 
	float m_eye_yaw; //0x0078 
	float m_pitch; //0x007C 
	float m_abs_yaw; //0x0080 
	float m_feet_yaw; //0x0084 
	float m_body_yaw; //0x0088 
	float m_body_yaw_clamped; //0x008C 
	float m_feet_vel_dir_delta; //0x0090 
	uint8_t pad_0x0094[ 0x4 ]; //0x0094
	float m_feet_cycle; //0x0098 
	float m_feet_yaw_rate; //0x009C 
	uint8_t pad_0x00A0[ 0x4 ]; //0x00A0
	float m_duck_amount; //0x00A4 
	float m_landing_duck_additive; //0x00A8 
	uint8_t pad_0x00AC[ 0x4 ]; //0x00AC
	vec3_t m_origin; //0x00B0 
	vec3_t m_old_origin; //0x00BC 
	vec2_t m_vel2d; //0x00C8 
	uint8_t pad_0x00D0[ 0x10 ]; //0x00D0
	vec2_t m_last_accelerating_vel; //0x00E0 
	uint8_t pad_0x00E8[ 0x4 ]; //0x00E8
	float m_speed2d; //0x00EC 
	float m_up_vel; //0x00F0 
	float m_speed_normalized; //0x00F4 
	float m_run_speed; //0x00F8 
	float m_unk_feet_speed_ratio; //0x00FC 
	float m_time_since_move; //0x0100 
	float m_time_since_stop; //0x0104 
	bool m_on_ground; //0x0108 
	bool m_hit_ground; //0x0109 
	uint8_t pad_0x010A[ 0x4 ]; //0x010A
	float m_time_in_air; //0x0110 
	uint8_t pad_0x0114[ 0x6 ]; //0x0114
	float m_ground_fraction; //0x011C 
	uint8_t pad_0x0120[ 0x2 ]; //0x0120
	float m_unk_fraction; //0x0124 
	uint8_t pad_0x0128[ 0xC ]; //0x0128
	bool m_moving; //0x0134
	uint8_t pad_0x0135[ 0x7B ]; //0x0135
	animstate_pose_param_cache_t m_lean_yaw_pose; //0x1B0
	animstate_pose_param_cache_t m_speed_pose; //0x01BC
	animstate_pose_param_cache_t m_ladder_speed_pose; //0x01C8
	animstate_pose_param_cache_t m_ladder_yaw_pose; //0x01D4
	animstate_pose_param_cache_t m_move_yaw_pose; //0x01E0
	animstate_pose_param_cache_t m_run_pose; //0x01EC 
	animstate_pose_param_cache_t m_body_yaw_pose; //0x01F8
	animstate_pose_param_cache_t m_body_pitch_pose; //0x0204
	animstate_pose_param_cache_t m_dead_yaw_pose; //0x0210
	animstate_pose_param_cache_t m_stand_pose; //0x021C
	animstate_pose_param_cache_t m_jump_fall_pose; //0x0228
	animstate_pose_param_cache_t m_aim_blend_stand_idle_pose; //0x0234
	animstate_pose_param_cache_t m_aim_blend_crouch_idle_pose; //0x0240
	animstate_pose_param_cache_t m_strafe_yaw_pose; //0x024C
	animstate_pose_param_cache_t m_aim_blend_stand_walk_pose; //0x0258
	animstate_pose_param_cache_t m_aim_blend_stand_run_pose; //0x0264
	animstate_pose_param_cache_t m_aim_blend_crouch_walk_pose; //0x0270
	animstate_pose_param_cache_t m_move_blend_walk_pose; //0x027C
	animstate_pose_param_cache_t m_move_blend_run_pose; //0x0288
	animstate_pose_param_cache_t m_move_blend_crouch_pose; //0x0294
	uint8_t pad_0x02A0[ 0x4 ]; //0x02A0
	float m_vel_unk; //0x02A4 
	uint8_t pad_0x02A8[ 0x86 ]; //0x02A8
	float m_min_yaw; //0x0330 
	float m_max_yaw; //0x0334 
	float m_max_pitch; //0x0338 
	float m_min_pitch; //0x033C

	void reset( );
	void update( vec3_t& ang );
}; //Size=0x0340

struct animlayer_t {
	char pad_0x01[ 0x14 ];
	int	m_order;
	int	m_sequence;
	float m_previous_cycle;
	float m_weight;
	float m_weight_delta_rate;
	float m_playback_rate;
	float m_cycle;
	void* m_owner;
	char pad_0x02[ 0x4 ];
};

/* local player */
class c_local_player
{
	friend bool operator==( const c_local_player& lhs, void* rhs );
public:
	c_local_player( ) : m_local( nullptr ) {}

	operator bool( ) const { return *m_local != nullptr; }
	operator c_base_player* ( ) const { return *m_local; }

	c_base_player* operator->( ) { return *m_local; }

private:
	c_base_player** m_local;
};


inline c_local_player g_local;

class c_base_player : public c_base_entity {
public:
	static __forceinline c_base_player* get_player_by_index( int index ) {
		return static_cast< c_base_player* >( get_entity_by_index( index ) );
	}

	/* offsets / indexes */
	float m_flSpawnTime( ) {
		return *( float* ) ( ( uintptr_t ) this + 0xA370 );
	}

	int& m_iEFlags( ) {
		return *( int* ) ( ( uintptr_t ) this + 0xE8 );
	}

	vec3_t& tp_angles( ) {
		static int m_tp_angles = ( netvars::get_offset( "DT_BasePlayer->deadflag" ) + 0x4 ); // 0x31D4 + 0x4
		return *( vec3_t* ) ( ( uintptr_t ) this + m_tp_angles );
	}

	vec3_t& m_vecAbsVelocity( ) {
		return *( vec3_t* ) ( ( uintptr_t ) this + 0x94 );
	}

	c_bone_acessor* get_bone_acessor( ) {
		return ( c_bone_acessor* ) ( ( uintptr_t ) this + 0x290C );
	}

	bool& m_JiggleBones( ) {
		return *( bool* ) ( ( uintptr_t ) this + 0x292C );
	}

	c_usercmd& m_PlayerCommand( ) {
		return *( c_usercmd* ) ( ( uintptr_t ) this + 0x326C );
	}

	c_usercmd*& m_pCurrentCommand( ) {
		return *( c_usercmd** ) ( ( uintptr_t ) this + 0x3314 );
	}

	animlayer_t* get_animoverlays( ) {
		return *( animlayer_t** ) ( ( uintptr_t ) this + 0x2980 );
	}

	animstate_t* get_animstate( ) {
		return *( animstate_t** ) ( ( DWORD ) this + 0x3914 );
	}

	bool is_player( ) {
		using o_fn = bool( __thiscall* )( c_base_player* );
		return utils::call_virtual<o_fn>( this, 157 )( this );
	}

	bool is_weapon( ) {
		using o_fn = bool( __thiscall* )( c_base_player* );
		return utils::call_virtual<o_fn>( this, 166 )( this );
	}

	void set_model_index( int index ) {
		using o_fn = void( __thiscall* )( void*, int );
		return utils::call_virtual<o_fn>( this, 75 )( this, index );
	}

	vec3_t& get_abs_origin( ) {
		using o_fn = vec3_t & ( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 10 )( this );
	}

	vec3_t& get_abs_angles( ) {
		using o_fn = vec3_t & ( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 11 )( this );
	}

	void update_clientside_animation( ) {
		typedef void( __thiscall* o_fn )( void* );
		return utils::call_virtual<o_fn>( this, 223 )( this );
	}

	/* other */
	c_base_combat_weapon* get_active_weapon( ) {
		auto active_weapon = *( int* ) ( uintptr_t( this ) + netvars::get_offset( "DT_CSPlayer->m_hActiveWeapon" ) ) & 0xFFF;
		return reinterpret_cast< c_base_combat_weapon* >( i::entitylist->get_client_entity( active_weapon ) );
	}

	void invalidate_bone_cache( ) {
		*( uint32_t* ) ( ( uintptr_t ) ( this ) + 0x2924 ) = -FLT_MAX; // m_flLastBoneSetupTime = -FLT_MAX
		*( uint32_t* ) ( ( uintptr_t ) ( this ) + 0x2690 ) = 0; // m_iMostRecentModelBoneCounter = 0;
	}

	bool is_alive( ) {
		return m_iHealth( ) > 0;
	}

	matrix_t get_bone_matrix( int id ) {
		matrix_t matrix;

		auto offset = *reinterpret_cast< uintptr_t* >( uintptr_t( this ) + 0x26A8 );
		if ( offset )
			matrix = *reinterpret_cast< matrix_t* >( offset + 0x30 * id );

		return matrix;
	}

	vec3_t get_bone_pos( int i ) {
		matrix_t matrix[ 128 ];

		if ( this->setup_bones( matrix, 128, 0x00000100, GetTickCount64( ) ) ) {
			return vec3_t( matrix[ i ][ 0 ][ 3 ], matrix[ i ][ 1 ][ 3 ], matrix[ i ][ 2 ][ 3 ] );
		}

		return vec3_t( 0, 0, 0 );
	}

	void create_anim_state( animstate_t* state )
	{
		using create_anim_state_t = void( __thiscall* ) ( animstate_t*, c_base_player* );
		static auto create_anim_state = reinterpret_cast< create_anim_state_t > ( utils::find_sig_ida( "client.dll", "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46" ) );

		if ( !create_anim_state )
			return;

		if ( !state )
			return;

		create_anim_state( state, this );
	}

	float max_desync_delta( ) {
		auto animstate = uintptr_t( this->get_animstate( ) );

		float duckammount = *( float* ) ( animstate + 0xA4 );
		float speedfraction = std::fmax( 0, std::fmin( *reinterpret_cast< float* >( animstate + 0xF8 ), 1 ) );

		float speedfactor = std::fmax( 0, std::fmin( 1, *reinterpret_cast< float* > ( animstate + 0xFC ) ) );

		float unk1 = ( ( *reinterpret_cast< float* > ( animstate + 0x11C ) * -0.30000001 ) - 0.19999999 ) * speedfraction;
		float unk2 = unk1 + 1.f;
		float unk3;

		if ( duckammount > 0 ) {

			unk2 += ( ( duckammount * speedfactor ) * ( 0.5f - unk2 ) );

		}

		unk3 = *( float* ) ( animstate + 0x334 ) * unk2;

		return unk3;
	}

	vec3_t get_hitbox_pos( int hitbox, matrix_t* matrix = nullptr )
	{
		auto mdl = this->get_model( );
		if ( !mdl ) return vec3_t( 0, 0, 0 );

		studio_hdr_t* m_studio_model = i::modelinfo->get_studio_model( this->get_model( ) );
		if ( !m_studio_model ) return vec3_t( 0, 0, 0 );

		auto* m_hitbox = m_studio_model->hitbox_set( 0 )->hitbox( hitbox );
		if ( !m_hitbox ) return vec3_t( 0, 0, 0 );

		/* if there is no matrix use bone accessor's one */
		if ( !matrix ) {
			matrix = ( matrix_t* ) this->get_bone_acessor( )->get_bone_arr_for_write( );
		}

		vec3_t vmin, vmax;

		math::vector_transform( m_hitbox->mins, matrix[ m_hitbox->bone ], vmin );
		math::vector_transform( m_hitbox->maxs, matrix[ m_hitbox->bone ], vmax );

		auto pos = ( vmin + vmax ) * 0.5f;

		return pos;
	}

	vec3_t get_eye_pos( ) {
		return m_vecOrigin( ) + m_vecViewOffset( );
	}

	bool can_see_player_pos( c_base_player* player, vec3_t& pos ) {
		trace_t tr;
		ray_t ray;
		trace_filter filter;
		filter.skip = this;

		filter.skip = this;

		ray.initialize( get_eye_pos( ), pos );
		i::trace->trace_ray( ray, mask_shot | contents_grate, &filter, &tr );

		return tr.player == player || tr.fraction > 0.97f;
	}

	int get_choked_packets( ) {
		static int last_ticks[ 65 ];
		auto ticks = time2ticks( this->m_flSimulationTime( ) - this->m_flOldSimulationTime( ) );
		if ( ticks == 0 && last_ticks[ this->ent_index( ) ] > 0 ) {
			return last_ticks[ this->ent_index( ) ] - 1;
		}
		else {
			last_ticks[ this->ent_index( ) ] = ticks;
			return ticks;
		}
	}

	player_info_t get_player_info( )
	{
		player_info_t pinfo;
		i::engine->get_player_info( ent_index( ), &pinfo );
		return pinfo;
	}

	void set_abs_angles( vec3_t angles ) {
		using o_fn = void( __thiscall* )( void*, const vec3_t& );
		static o_fn set_angles_fn = ( o_fn ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" );
		set_angles_fn( this, angles );
	}

	void set_abs_origin( vec3_t position ) {
		using o_fn = void( __thiscall* )( void*, const vec3_t& );
		static o_fn set_position_fn = ( o_fn ) utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" );
		set_position_fn( this, position );
	}

	bool is_enemy( ) {
		return ( this->m_iTeamNum( ) != g_local->m_iTeamNum( ) );
	}

	bool is_valid_target( ) {
		if ( !this ) return false;
		auto class_id = this->get_client_class( )->class_id;
		if ( !this->is_enemy( ) ) return false;
		if ( this->m_iHealth( ) <= 0 ) return false;
		if ( class_id != class_id_cs_player ) return false;
		if ( this->m_vecOrigin( ) == vec3_t( 0, 0, 0 ) ) return false;
		if ( this->m_bGunGameImmunity( ) ) return false;
		if ( this->is_dormant( ) ) return false;

		return true;
	}

	/* DT_BasePlayer */
	// m_iFOV                                 
	// m_iFOVStart                            
	// m_flFOVTime                            
	// m_iDefaultFOV                          
	// m_hZoomOwner                           
	// m_afPhysicsFlags                       
	// m_hVehicle                             
	// m_hUseEntity                           
	// m_hGroundEntity                        
	NETVAR( "DT_BasePlayer->m_iHealth", m_iHealth, int );
	NETVAR( "DT_BasePlayer->m_lifeState", m_lifeState, int );
	//m_iBonusProgress
	//m_iBonusChallenge
	NETVAR( "DT_BasePlayer->m_flMaxspeed", m_flMaxspeed, float );
	NETVAR( "DT_BasePlayer->m_fFlags", m_fFlags, int );
	// m_iObserverMode
	// m_bActiveCameraMan
	// m_bCameraManXRay
	// m_bCameraManOverview
	// m_bCameraManScoreBoard
	// m_uCameraManGraphs
	// m_iDeathPostEffect
	NETVAR( "DT_BasePlayer->m_hObserverTarget", m_hObserverTarget, unsigned long );
	NETVAR( "DT_BasePlayer->m_hViewModel[0]", m_hViewModel, int );
	// m_hViewModel
	// m_iCoachingTeam
	// m_szLastPlaceName
	// m_vecLadderNormal
	// m_ladderSurfaceProps
	// m_ubEFNoInterpParity
	// m_hPostProcessCtrl
	// m_hColorCorrectionCtrl
	// m_PlayerFog.m_hCtrl
	// m_vphysicsCollisionState
	// m_hViewEntity
	// m_bShouldDrawPlayerWhileUsingViewEntity
	NETVAR( "DT_BasePlayer->m_flDuckAmount", m_flDuckAmount, float );
	NETVAR( "DT_BasePlayer->m_flDuckSpeed", m_flDuckSpeed, float );
	// m_nWaterLevel
	// localdata
	NETVAR( "DT_BasePlayer->m_vecViewOffset[0]", m_vecViewOffset, vec3_t );
	// m_vecViewOffset[1]
	// m_vecViewOffset[2]
	// m_flFriction
	// m_fOnTarget
	NETVAR( "DT_BasePlayer->m_nTickBase", m_nTickBase, int );
	// m_nNextThinkTick
	// m_hLastWeapon
	NETVAR( "DT_BasePlayer->m_vecVelocity[0]", m_vecVelocity, vec3_t );
	// m_vecVelocity[1]
	// m_vecVelocity[2]
	// m_vecBaseVelocity
	// m_hConstraintEntity                
	// m_vecConstraintCenter
	// m_flConstraintRadius               
	// m_flConstraintWidth                
	// m_flConstraintSpeedFactor          
	// m_bConstraintPastRadius            
	// m_flDeathTime                      
	// m_flNextDecalTime                  
	// m_fForceTeam                       
	// m_flLaggedMovementValue            
	// m_hTonemapController               
	// m_Local                            
	// m_iHideHUD                     
	// m_flFOVRate                    
	// m_bDucked                      
	// m_bDucking                     
	// m_flLastDuckTime               
	// m_bInDuckJump
	// m_nDuckTimeMsecs
	// m_nDuckJumpTimeMsecs
	// m_nJumpTimeMsecs
	// m_flFallVelocity 
	NETVAR( "DT_BasePlayer->m_viewPunchAngle", m_viewPunchAngle, vec3_t );
	NETVAR( "DT_BasePlayer->m_aimPunchAngle", m_aimPunchAngle, vec3_t );
	// m_aimPunchAngleVel             
	// m_bDrawViewmodel               
	// m_bWearingSuit                 
	// m_bPoisoned                    
	// m_flStepSize                   
	// m_bAllowAutoMovement           
	// m_skybox3d.scale               
	// m_skybox3d.origin              
	// m_skybox3d.area                
	// m_skybox3d.fog.enable          
	// m_skybox3d.fog.blend           
	// m_skybox3d.fog.dirPrimary      
	// m_skybox3d.fog.colorPrimary    
	// m_skybox3d.fog.colorSecondary  
	// m_skybox3d.fog.start           
	// m_skybox3d.fog.end             
	// m_skybox3d.fog.maxdensity      
	// m_skybox3d.fog.HDRColorScale   
	// m_audio.localSound[0]          
	// m_audio.localSound[1]          
	// m_audio.localSound[2]          
	// m_audio.localSound[3]          
	// m_audio.localSound[4]          
	// m_audio.localSound[5]          
	// m_audio.localSound[6]          
	// m_audio.localSound[7]          
	// m_audio.soundscapeIndex        
	// m_audio.localBits              
	// m_audio.entIndex               
	// m_chAreaBits                   
	// m_chAreaPortalBits             
	// pl                                     
	// deadflag                           
	// m_iAmmo                                

	/* DT_CSPlayer */
	NETVAR( "DT_CSPlayer->m_flSimulationTime", m_flSimulationTime, float );
	NETVAR_OFFSET( "DT_CSPlayer->m_flSimulationTime", 0x4, m_flOldSimulationTime, float );
	NETVAR( "DT_CSPlayer->m_angEyeAngles[0]", m_angEyeAngles, vec3_t );
	// m_angEyeAngles[1]                             
	// m_iAddonBits                                
	// m_iPrimaryAddon                             
	// m_iSecondaryAddon                           
	// m_iThrowGrenadeCounter                      
	// m_bWaitForNoAttack                          
	// m_bIsRespawningForDMBonus                   
	// m_iPlayerState     
	NETVAR( "DT_CSPlayer->m_iAccount", m_iAccount, int );
	// m_iStartAccount                             
	// m_totalHitsOnServer                         
	// m_bInBombZone                               
	// m_bInBuyZone                                
	// m_bInNoDefuseArea                           
	// m_bKilledByTaser                            
	// m_iMoveState                                
	// m_iClass                           
	NETVAR( "DT_CSPlayer->m_ArmorValue", m_ArmorValue, int );
	// m_angEyeAngles                     
	NETVAR( "DT_CSPlayer->m_bHasDefuser", m_bHasDefuser, bool );
	NETVAR( "DT_CSPlayer->m_bHasNightVision", m_bHasNightVision, float );
	NETVAR( "DT_CSPlayer->m_bNightVisionOn", m_bNightVisionOn, float );
	// m_bInHostageRescueZone                      
	NETVAR( "DT_CSPlayer->m_bIsDefusing", m_bIsDefusing, bool );
	// m_bIsGrabbingHostage                        
	// m_iBlockingUseActionInProgress 
	NETVAR( "DT_CSPlayer->m_bIsScoped", m_bIsScoped, bool );
	// m_bIsWalking                                
	// m_nIsAutoMounting                           
	// m_bResumeZoom                               
	// m_fImmuneToGunGameDamageTime                
	NETVAR( "DT_CSPlayer->m_bGunGameImmunity", m_bGunGameImmunity, bool );
	// m_bHasMovedSinceSpawn                       
	// m_bMadeFinalGunGameProgressiveKill          
	// m_iGunGameProgressiveWeaponIndex            
	// m_iNumGunGameTRKillPoints                   
	// m_iNumGunGameKillsWithCurrentWeapon         
	// m_iNumRoundKills                            
	// m_fMolotovUseTime                           
	// m_fMolotovDamageTime                        
	// m_szArmsModel                               
	// m_hCarriedHostage                           
	// m_hCarriedHostageProp                       
	// m_bIsRescuing                               
	// m_flGroundAccelLinearFracLastTime           
	// m_bCanMoveDuringFreezePeriod                
	// m_isCurrentGunGameLeader                    
	// m_isCurrentGunGameTeamLeader                
	// m_flGuardianTooFarDistFrac                  
	// m_flDetectedByEnemySensorTime               
	// m_bIsPlayerGhost                            
	// m_bHasParachute                             
	// m_unMusicID      
	NETVAR( "DT_CSPlayer->m_bHasHelmet", m_bHasHelmet, bool );
	NETVAR( "DT_CSPlayer->m_bHasHeavyArmor", m_bHasHeavyArmor, bool );
	// m_nHeavyAssaultSuitCooldownRemaining        
	NETVAR( "DT_CSPlayer->m_flFlashDuration", m_flFlashDuration, float );
	NETVAR( "DT_CSPlayer->m_flFlashMaxAlpha", m_flFlashMaxAlpha, float );
	// m_iProgressBarDuration                      
	// m_flProgressBarStartTime                    
	// m_hRagdoll                                  
	// m_hPlayerPing                               
	// m_cycleLatch                                
	// m_unCurrentEquipmentValue                   
	// m_unRoundStartEquipmentValue                
	// m_unFreezetimeEndEquipmentValue             
	// m_bIsControllingBot                         
	// m_bHasControlledBotThisRound                
	// m_bCanControlObservedBot                    
	// m_iControlledBotEntIndex                    
	// m_vecAutomoveTargetEnd                      
	// m_flAutoMoveStartTime                       
	// m_flAutoMoveTargetTime                      
	// m_bIsAssassinationTarget                    
	// m_bHud_MiniScoreHidden                      
	// m_bHud_RadarHidden                          
	// m_nLastKillerIndex                          
	// m_nLastConcurrentKilled                     
	// m_nDeathCamMusic                            
	// m_bIsHoldingLookAtWeapon                    
	// m_bIsLookingAtWeapon                        
	// m_iNumRoundKillsHeadshots                   
	// m_unTotalRoundDamageDealt    
	NETVAR( "DT_CSPlayer->m_flLowerBodyYawTarget", m_flLowerBodyYawTarget, float );
	// m_bStrafing                                 
	// m_flThirdpersonRecoil                       
	// m_bHideTargetID                             
	// m_bIsSpawnRappelling                        
	// m_vecSpawnRappellingRopeOrigin              
	NETVAR( "DT_CSPlayer->m_nSurvivalTeam", m_nSurvivalTeam, int );
	// m_hSurvivalAssassinationTarget              
	NETVAR( "DT_CSPlayer->m_flHealthShotBoostExpirationTime", m_flHealthShotBoostExpirationTime, float );
	// m_flLastExoJumpTime                         
	// cslocaldata                                 
	NETVAR( "DT_CSPlayer->m_vecOrigin", m_vecOrigin, vec3_t );
	// m_vecOrigin[2]                          
	// m_flStamina                             
	// m_iDirection      
	NETVAR( "DT_CSPlayer->m_iShotsFired", m_iShotsFired, int );
	NETVAR( "DT_CSPlayer->m_flNextAttack", m_flNextAttack, float );
	// m_nNumFastDucks                         
	// m_bDuckOverride                         
	// m_flVelocityModifier                    
	// m_unActiveQuestId                       
	// m_nQuestProgressReason                  
	// m_bPlayerDominated                      
	// m_bPlayerDominatingMe                   
	// m_iWeaponPurchasesThisRound             
	// csnonlocaldata                                                       
	// csteamdata                                  
	// m_iWeaponPurchasesThisMatch             
	// m_EquippedLoadoutItemDefIndices         
	// m_iMatchStats_Kills                         
	// m_iMatchStats_Damage                        
	// m_iMatchStats_EquipmentValue                
	// m_iMatchStats_MoneySaved                    
	// m_iMatchStats_KillReward                    
	// m_iMatchStats_LiveTime                      
	// m_iMatchStats_Deaths                        
	// m_iMatchStats_Assists            
	NETVAR( "DT_CSPlayer->m_flAnimTime", m_flAnimTime, float );
	NETVAR( "DT_CSPlayer->m_flCycle", m_flCycle, float );
	// m_iMatchStats_HeadShotKills                 
	// m_iMatchStats_Objective                     
	// m_iMatchStats_CashEarned                    
	// m_iMatchStats_UtilityDamage                 
	// m_iMatchStats_EnemiesFlashed                
	// m_rank                                      
	// m_passiveItems    
	NETVAR_PTR( "DT_CSPlayer->m_hMyWeapons", m_hMyWeapons, UINT );
	NETVAR_PTR( "DT_CSPlayer->m_hMyWearables", m_hMyWearables, UINT );

	/* DT_SmokeGrenadeProjectile */
	NETVAR( "DT_SmokeGrenadeProjectile->m_nSmokeEffectTickBegin", m_nSmokeEffectTickBegin, int );

	/* DT_BaseAnimating */
	NETVAR( "DT_BaseAnimating->m_bClientSideAnimation", m_bClientSideAnimation, bool );
	std::array<float, 24>& m_flPoseParameter( ) {
		static int _m_flPoseParameter = netvars::get_offset( "DT_BaseAnimating->m_flPoseParameter" );
		return *( std::array<float, 24>* )( uintptr_t( this ) + _m_flPoseParameter );
	}
};
