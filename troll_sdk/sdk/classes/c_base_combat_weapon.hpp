#pragma once
#include "../../utilities/utilities.hpp"
#include "../netvar/netvar.hpp"
#include "c_base_attributable_item.hpp"

enum cs_c_base_combat_weaponype {
	weapontype_knife = 0,
	weapontype_pistol,
	weapontype_submachinegun,
	weapontype_rifle,
	weapontype_shotgun,
	weapontype_sniper_rifle,
	weapontype_machinegun,
	weapontype_c4,
	weapontype_placeholder,
	weapontype_grenade,
	weapontype_unknown
};

enum item_def_idx : short {
	weapon_none = 0,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_ak47 = 7,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galilar = 13,
	weapon_m249,
	weapon_m4a1 = 16,
	weapon_mac10,
	weapon_p90 = 19,
	weapon_mp5sd = 23,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_shield,
	weapon_scar20,
	weapon_sg553,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4,
	weapon_healthshot = 57,
	weapon_knife_t = 59,
	weapon_m4a1_silencer,
	weapon_usp_silencer,
	weapon_cz75a = 63,
	weapon_revolver,
	weapon_tagrenade = 68,
	weapon_fists,
	weapon_breachcharge,
	weapon_tablet = 72,
	weapon_melee = 74,
	weapon_axe,
	weapon_hammer,
	weapon_spanner = 78,
	weapon_knife_ghost = 80,
	weapon_firebomb,
	weapon_diversion,
	weapon_frag_grenade,
	weapon_snowball,
	weapon_bumpmine,
	weapon_knife_bayonet = 500,
	weapon_knife_css = 503,
	weapon_knife_flip = 505,
	weapon_knife_gut,
	weapon_knife_karambit,
	weapon_knife_m9_bayonet,
	weapon_knife_tactical,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly,
	weapon_knife_push,
	weapon_knife_cord,
	weapon_knife_canis,
	weapon_knife_ursus = 519,
	weapon_knife_gypsy_jackknife,
	weapon_knife_outdoor,
	weapon_knife_stiletto = 522,
	weapon_knife_widowmaker,
	weapon_knife_skeleton = 525,
	studded_brokenfang_gloves = 4725,
	glove_studded_bloodhound = 5027,
	glove_t_side,
	glove_ct_side,
	glove_sporty,
	glove_slick,
	glove_leather_wrap,
	glove_motorcycle,
	glove_specialist,
	glove_hydra,
};

class weapon_info_t
{
public:
	char pad_0000[4]; //0x0000
	char* console_name; //0x0004
	char pad_0008[12]; //0x0008
	int max_clip1; //0x0014
	char pad_0018[12]; //0x0018
	int max_clip2; //0x0024
	char pad_0028[4]; //0x0028
	char* worldmodel; //0x002C
	char* viewmodel; //0x0030
	char* dropped_model; //0x0034
	char pad_0038[4]; //0x0038
	char* N00000984; //0x003C
	char pad_0040[56]; //0x0040
	char* empty_sound; //0x0078
	char pad_007C[4]; //0x007C
	char* bullet_type; //0x0080
	char pad_0084[4]; //0x0084
	char* hud_name; //0x0088
	char* weapon_name; //0x008C
	char pad_0090[60]; //0x0090
	int weapon_type; //0x00CC
	int weapon_price; //0x00D0
	int kill_award; //0x00D4
	char* animation_prefix; //0x00D8
	float cycle_time; //0x00DC
	float cycle_time_alt; //0x00E0
	float time_to_idle; //0x00E4
	float idle_interval; //0x00E8
	bool full_auto; //0x00EC
	char pad_00ED[3]; //0x00ED
	int damage; //0x00F0
	char headshotmultyplrier[4];
	float armor_ratio; //0x00F4
	int bullets; //0x00F8
	float penetration; //0x00FC
	float flinch_velocity_modifier_large; //0x0100
	float flinch_velocity_modifier_small; //0x0104
	float range; //0x0108
	float range_modifier; //0x010C
	char pad_0110[28]; //0x0110
	int crosshair_mindistance; //0x012C
	float max_speed[2]; //0x0130
	char pad_0138[4]; //0x0138
	float spread[2]; //0x013C
	float inaccuracy_crouch[2]; //0x0144
	float inaccuracy_stand[2]; //0x014C
	float inaccuracy_jump[2]; //0x0158
	float inaccuracy_land[2]; //0x0160
	float inaccuracy_ladder[2]; //0x0168
	float inaccuracy_fire[2]; //0x0170
	float inaccuracy_move[2]; //0x0178
	float inaccuracy_reload; //0x0180
	int recoil_seed; //0x0184
	float recoil_angle[2]; //0x0188
	float recoil_angle_variance[2]; //0x0190
	float recoil_magnitude[2]; //0x0198
	float recoild_magnitude_variance[2]; //0x01A0
	float recovery_time_crouch; //0x01A8
	float recovery_time_stand; //0x01AC
	float recovery_time_crouch_final; //0x01B0
	float recovery_time_stand_final; //0x01B4
	int recovery_transitition_start_bullet; //0x01B8
	int recovery_transitition_end_bullet; //0x01BC
	bool unzoom_after_shot; //0x01C0
	char pad_01C1[31]; //0x01C1
	char* weapon_class; //0x01E0
	char pad_01E4[56]; //0x01E4
	float inaccuracy_pitch_shift; //0x021C
	float inaccuracy_sound_threshold; //0x0220
	float bot_audible_range; //0x0224
	char pad_0228[12]; //0x0228
	bool has_burst_mode; //0x0234
};

class c_base_view_model : public c_base_entity {
public:
	/* DT_BaseViewModel */
	NETVAR( "DT_BaseViewModel->m_nModelIndex", m_nModelIndex, int );
	NETVAR( "DT_BaseViewModel->m_nViewModelIndex", m_nViewModelIndex, int );
	NETVAR( "DT_BaseViewModel->m_hWeapon", m_hWeapon, int );
	NETVAR( "DT_BaseViewModel->m_hOwner", m_hOwner, int );

	inline int get_model_index( ) {

		return *( int* ) ( ( DWORD ) this + 0x258 );
	}
};

class c_base_combat_weapon : public c_base_attributable_item {
public:

	/* other */
	float get_inaccuracy( ) {
		using o_fn = float( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 483 )( this );
	}

	float get_spread( ) {
		using o_fn = float( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 453 )( this );
	}

	void update_accuracy_penalty( ) {
		using o_fn = void( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 484 )( this );
	}

	weapon_info_t* get_cs_weapon_data( ) {
		using o_fn = weapon_info_t * ( __thiscall* )( void* );
		return utils::call_virtual< o_fn >( this, 461 )( this );
	}

	bool is_knife( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_knife;
	}

	bool is_nade( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_grenade;
	}

	bool is_zeus( ) {
		return this->m_iItemDefinitionIndex( ) == weapon_taser;
	}

	bool is_pistol( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_pistol;
	}

	bool is_rifle( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_rifle;
	}

	bool is_sniper( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_sniper_rifle;
	}

	bool is_smg( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_submachinegun;
	}

	bool is_heavy( ) {
		if ( !this->get_cs_weapon_data( ) )
			return false;

		return this->get_cs_weapon_data( )->weapon_type == weapontype_machinegun;
	}

	bool is_gun( ) {
		if ( !this )
			return false;

		int id = this->m_iItemDefinitionIndex( );

		if ( id == weapon_c4 || this->is_knife( ) || this->is_nade( ) )
			return false;

		return true;
	}

	void set_model_index( int index ) {
		using o_fn = void( __thiscall* )( void*, int );
		return utils::call_virtual<o_fn>( this, 75 )( this, index );
	}

	std::string get_name( ) {
		if ( !this->get_cs_weapon_data( ) )
			return "invalid";

		return std::string( this->get_cs_weapon_data( )->weapon_name );
	}

	std::string weapon_name( ) {
		if ( !this || !m_iItemDefinitionIndex( ) )
			return "invalid";

		int weap_id = this->m_iItemDefinitionIndex( );
		switch ( weap_id ) {
		case weapon_deagle:
			return "deagle";
			break;
		case weapon_elite:
			return "duals";
			break;
		case weapon_fiveseven:
			return "five seven";
			break;
		case weapon_glock:
			return "glock";
			break;
		case weapon_ak47:
			return "ak-47";
			break;
		case weapon_aug:
			return "aug";
			break;
		case weapon_awp:
			return "awp";
			break;
		case weapon_famas:
			return "famas";
			break;
		case weapon_g3sg1:
			return "g3sg1";
			break;
		case weapon_galilar:
			return "galil-ar";
			break;
		case weapon_m249:
			return "m249";
			break;
		case weapon_m4a1_silencer:
			return "m4a1-s";
			break;
		case weapon_m4a1:
			return "m4a4";
			break;
		case weapon_mac10:
			return "mac-10";
			break;
		case weapon_p90:
			return "p90";
			break;
		case weapon_mp5sd:
			return "mp5";
			break;
		case weapon_ump45:
			return "ump-45";
			break;
		case weapon_xm1014:
			return "xm1014";
			break;
		case weapon_bizon:
			return "bizon";
			break;
		case weapon_mag7:
			return "mag7";
			break;
		case weapon_negev:
			return "negev";
			break;
		case weapon_sawedoff:
			return "sawed-off";
			break;
		case weapon_tec9:
			return "tec-9";
			break;
		case weapon_taser:
			return "taser";
			break;
		case weapon_hkp2000:
			return "p2000";
			break;
		case weapon_mp7:
			return "mp7";
			break;
		case weapon_mp9:
			return "mp9";
			break;
		case weapon_nova:
			return "nova";
			break;
		case weapon_p250:
			return "p250";
			break;
		case weapon_shield:
			return "shield";
			break;
		case weapon_scar20:
			return "scar20";
			break;
		case weapon_sg553:
			return "sg553";
			break;
		case weapon_ssg08:
			return "ssg-08";
			break;
		case weapon_flashbang:
			return "flashbang";
			break;
		case weapon_hegrenade:
			return "he grenade";
			break;
		case weapon_smokegrenade:
			return "smoke grenade";
			break;
		case weapon_molotov:
			return "molotov";
			break;
		case weapon_decoy:
			return "decoy";
			break;
		case weapon_incgrenade:
			return "incendiary";
			break;
		case weapon_c4:
			return "c4";
			break;
		case weapon_healthshot:
			return "health shot";
			break;
		case weapon_usp_silencer:
			return "usp-s";
			break;
		case weapon_cz75a:
			return "cz75-a";
			break;
		case weapon_revolver:
			return "revolver";
			break;
		case weapon_knife_bayonet:
			return "bayonet";
			break;
		case weapon_knife_css:
			return "classic knife";
			break;
		case weapon_knife_flip:
			return "flip knife";
			break;
		case weapon_knife_gut:
			return "gut knife";
			break;
		case weapon_knife_karambit:
			return "karambit";
			break;
		case weapon_knife_m9_bayonet:
			return "m9 bayonet";
			break;
		case weapon_knife_tactical:
			return "huntsman knife";
			break;
		case weapon_knife_falchion:
			return "falchion knife";
			break;
		case weapon_knife_survival_bowie:
			return "bowie knife";
			break;
		case weapon_knife_butterfly:
			return "butterfly knife";
			break;
		case weapon_knife_push:
			return "shadow daggers";
			break;
		case weapon_knife_cord:
			return "paracord knife";
			break;
		case weapon_knife_canis:
			return "survival knife";
			break;
		case weapon_knife_ursus:
			return "ursus knife";
			break;
		case weapon_knife_gypsy_jackknife:
			return "navaja knife";
			break;
		case weapon_knife_outdoor:
			return "nomad knife";
			break;
		case weapon_knife_stiletto:
			return "stiletto knife";
			break;
		case weapon_knife_widowmaker:
			return "talon knife";
			break;
		case weapon_knife_skeleton:
			return "skeleton knife";
			break;
		default:
			return "knife";
		}
	}

	vec3_t calculate_spread( int seed, float inaccuracy, float spread, bool revolver2 = false );


	/* DT_BaseCombatWeapon */
	NETVAR( "DT_BaseCombatWeapon->m_iViewModelIndex", m_iViewModelIndex, int );
	// m_iWorldModelIndex          
	// m_iWorldDroppedModelIndex   
	// m_iState                    
	// m_hOwner                    
	// m_iClip1   
	NETVAR( "DT_BaseCombatWeapon->m_iClip1", m_iClip1, int );
	// m_iClip2                    
	NETVAR( "DT_BaseCombatWeapon->m_iPrimaryReserveAmmoCount", m_iPrimaryReserveAmmoCount, int );
	// m_iSecondaryReserveAmmoCount
	NETVAR( "DT_BaseCombatWeapon->m_hWeaponWorldModel", m_hWeaponWorldModel, HANDLE );
	// m_iNumEmptyAttacks          
	// LocalWeaponData             
	// m_iPrimaryAmmoType      
	// m_iSecondaryAmmoType    
	// m_nViewModelIndex       
	// m_bFlipViewModel        
	// m_iWeaponOrigin         
	// m_iWeaponModule         
	// LocalActiveWeaponData       
	NETVAR( "DT_BaseCombatWeapon->m_Activity", m_Activity, int );
	NETVAR( "DT_BaseCombatWeapon->m_flNextPrimaryAttack", m_flNextPrimaryAttack, float );
	NETVAR( "DT_BaseCombatWeapon->m_flNextSecondaryAttack", m_flNextSecondaryAttack, float );
	// m_nNextThinkTick        
	// m_flTimeWeaponIdle      


	/* DT_WeaponCSBase */
	// m_weaponMode
	NETVAR( "DT_WeaponCSBase->m_fAccuracyPenalty", m_fAccuracyPenalty, float );
	NETVAR( "DT_WeaponCSBase->m_fLastShotTime", m_fLastShotTime, float );
	NETVAR( "DT_WeaponCSBase->m_flRecoilIndex", m_flRecoilIndex, float );
	// m_hPrevOwner
	// m_bBurstMode
	NETVAR( "DT_BaseCombatWeapon->m_flPostponeFireReadyTime", m_flPostponeFireReadyTime, float );
	NETVAR( "DT_BaseCombatWeapon->m_bInReload", m_bInReload, bool );
	// m_bReloadVisuallyComplete
	// m_bSilencerOn
	// m_flDoneSwitchingSilencer
	// m_iOriginalTeamNumber
	// m_iIronSightMode

	/* DT_WeaponCSBaseGun */
	NETVAR( "DT_WeaponCSBaseGun->m_zoomLevel", m_zoomLevel, int );
	NETVAR( "DT_WeaponCSBaseGun->m_iBurstShotsRemaining", m_iBurstShotsRemaining, int );

	/* DT_BaseCSGrenade */
	NETVAR( "DT_BaseCSGrenade->m_fThrowTime", m_fThrowTime, float );
	NETVAR( "DT_BaseCSGrenade->m_bPinPulled", m_bPinPulled, bool );

};

class c_gloves : public c_base_combat_weapon {
public:
	void pre_data_update( int type ) {
		PVOID networkable = ( PVOID ) ( ( DWORD ) ( this ) + 0x8 );
		typedef void( __thiscall* o_fn )( PVOID, int );
		return utils::call_virtual<o_fn>( networkable, 6 )( networkable, type );
	}

	void set_glove_model_index( int index ) {
		using o_fn = void( __thiscall* )( void*, int );
		return utils::call_virtual<o_fn>( this, 75 )( this, index );
	}
};
