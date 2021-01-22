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
	glove_studded_bloodhound = 5027,
	glove_t_side = 5028,
	glove_ct_side = 5029,
	glove_sporty = 5030,
	glove_slick = 5031,
	glove_leather_wrap = 5032,
	glove_motorcycle = 5033,
	glove_specialist = 5034,
	glove_hydra = 5035,
	max_itemdefinitionindex
};

class weapon_info_t {
public:
	uint8_t pad0[ 0x14 ];
	uint32_t max_clip;
	uint8_t pad1[ 0xC ];
	uint32_t max_reserved_ammo;
	uint8_t pad2[ 0x60 ];
	char* hud_name;
	char* weapon_name;
	uint8_t pad3[ 0x38 ];
	uint32_t weapon_type;
	uint8_t pad4[ 0x4 ];
	uint32_t price;
	uint32_t reward;
	uint8_t pad5[ 0x4 ];
	float_t fire_rate;
	uint8_t pad6[ 0xC ];
	uint8_t full_auto;
	uint8_t pad7[ 0x3 ];
	uint32_t dmg;
	float_t armor_ratio;
	uint32_t bullets;
	float_t penetration;
	uint8_t pad8[ 0x8 ];
	float_t range;
	float_t range_modifier;
	uint8_t pad9[ 0x10 ];
	uint8_t has_silencer;
	uint8_t pad10[ 0xF ];
	float_t max_speed;
	float_t max_speed_alt;
	uint8_t pad11[ 0x4C ];
	uint32_t recoil_seed;
	uint8_t pad12[ 0x20 ];
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
		return utils::call_virtual<o_fn>( this, 482 )( this );
	}

	float get_spread( ) {
		using o_fn = float( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 452 )( this );
	}

	void update_accuracy_penalty( ) {
		using o_fn = void( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 483 )( this );
	}

	weapon_info_t* get_cs_weapon_data( ) {
		using o_fn = weapon_info_t * ( __thiscall* )( void* );
		return utils::call_virtual< o_fn >( this, 460 )( this );
	}

	bool is_knife( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_knife;
	}

	bool is_nade( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_grenade;
	}

	bool is_zeus( ) {
		return m_iItemDefinitionIndex( ) == weapon_taser;
	}

	bool is_pistol( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_pistol;
	}

	bool is_rifle( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_rifle;
	}

	bool is_sniper( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_sniper_rifle;
	}

	bool is_smg( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_submachinegun;
	}

	bool is_heavy( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_machinegun;
	}

	void set_model_index( int index ) {
		using o_fn = void( __thiscall* )( void*, int );
		return utils::call_virtual<o_fn>( this, 75 )( this, index );
	}

	std::string get_name( ) {
		return std::string( this->get_cs_weapon_data( )->weapon_name );
	}

	float fire_rate( ) {
		if ( !this || this->is_knife( ) || this->is_nade( ) ) return 0.f;

		std::string weapon_name = this->get_name( );

		if ( weapon_name == "weapon_glock" )
			return 0.15f;
		else if ( weapon_name == "weapon_hkp2000" )
			return 0.169f;
		else if ( weapon_name == "weapon_p250" )//the cz and p250 have the same name idky same with other guns
			return 0.15f;
		else if ( weapon_name == "weapon_tec9" )
			return 0.12f;
		else if ( weapon_name == "weapon_elite" )
			return 0.12f;
		else if ( weapon_name == "weapon_fiveseven" )
			return 0.15f;
		else if ( weapon_name == "weapon_deagle" )
			return 0.224f;
		else if ( weapon_name == "weapon_nova" )
			return 0.882f;
		else if ( weapon_name == "weapon_sawedoff" )
			return 0.845f;
		else if ( weapon_name == "weapon_mag7" )
			return 0.845f;
		else if ( weapon_name == "weapon_xm1014" )
			return 0.35f;
		else if ( weapon_name == "weapon_mac10" )
			return 0.075f;
		else if ( weapon_name == "weapon_ump45" )
			return 0.089f;
		else if ( weapon_name == "weapon_mp9" )
			return 0.070f;
		else if ( weapon_name == "weapon_bizon" )
			return 0.08f;
		else if ( weapon_name == "weapon_mp7" )
			return 0.08f;
		else if ( weapon_name == "weapon_p90" )
			return 0.070f;
		else if ( weapon_name == "weapon_galilar" )
			return 0.089f;
		else if ( weapon_name == "weapon_ak47" )
			return 0.1f;
		else if ( weapon_name == "weapon_sg556" )
			return 0.089f;
		else if ( weapon_name == "weapon_m4a1" )
			return 0.089f;
		else if ( weapon_name == "weapon_aug" )
			return 0.089f;
		else if ( weapon_name == "weapon_m249" )
			return 0.08f;
		else if ( weapon_name == "weapon_negev" )
			return 0.0008f;
		else if ( weapon_name == "weapon_ssg08" )
			return 1.25f;
		else if ( weapon_name == "weapon_awp" )
			return 1.463f;
		else if ( weapon_name == "weapon_g3sg1" )
			return 0.25f;
		else if ( weapon_name == "weapon_scar20" )
			return 0.25f;
		else if ( weapon_name == "weapon_mp5sd" )
			return 0.08f;
		else
			return .0f;
	}

	std::string weapon_name( ) {
		if ( !this || !m_iItemDefinitionIndex( ) )
			return "invalid";

		int weap_id = this->m_iItemDefinitionIndex( );
		switch ( weap_id ) {
		case weapon_deagle:
			return "Deagle";
			break;
		case weapon_elite:
			return "Duals";
			break;
		case weapon_fiveseven:
			return "Five Seven";
			break;
		case weapon_glock:
			return "Glock";
			break;
		case weapon_ak47:
			return "AK-47";
			break;
		case weapon_aug:
			return "Aug";
			break;
		case weapon_awp:
			return "Awp";
			break;
		case weapon_famas:
			return "Famas";
			break;
		case weapon_g3sg1:
			return "G3SG1";
			break;
		case weapon_galilar:
			return "Galil-AR";
			break;
		case weapon_m249:
			return "M249";
			break;
		case weapon_m4a1_silencer:
			return "M4A1-S";
			break;
		case weapon_m4a1:
			return "M4A4";
			break;
		case weapon_mac10:
			return "MAC-10";
			break;
		case weapon_p90:
			return "P90";
			break;
		case weapon_mp5sd:
			return "MP5";
			break;
		case weapon_ump45:
			return "UMP-45";
			break;
		case weapon_xm1014:
			return "XM1014";
			break;
		case weapon_bizon:
			return "Bizon";
			break;
		case weapon_mag7:
			return "MAG7";
			break;
		case weapon_negev:
			return "Negev";
			break;
		case weapon_sawedoff:
			return "Sawed-off";
			break;
		case weapon_tec9:
			return "Tec-9";
			break;
		case weapon_taser:
			return "Taser";
			break;
		case weapon_hkp2000:
			return "P2000";
			break;
		case weapon_mp7:
			return "MP7";
			break;
		case weapon_mp9:
			return "MP9";
			break;
		case weapon_nova:
			return "Nova";
			break;
		case weapon_p250:
			return "P250";
			break;
		case weapon_shield:
			return "Shield";
			break;
		case weapon_scar20:
			return "Scar20";
			break;
		case weapon_sg553:
			return "SG553";
			break;
		case weapon_ssg08:
			return "SSG-08";
			break;
		case weapon_flashbang:
			return "Flashbang";
			break;
		case weapon_hegrenade:
			return "HE grenade";
			break;
		case weapon_smokegrenade:
			return "Smoke grenade";
			break;
		case weapon_molotov:
			return "Molotov";
			break;
		case weapon_decoy:
			return "Decoy";
			break;
		case weapon_incgrenade:
			return "Incendiary";
			break;
		case weapon_c4:
			return "C4";
			break;
		case weapon_healthshot:
			return "Health Shot";
			break;
		case weapon_usp_silencer:
			return "USP-S";
			break;
		case weapon_cz75a:
			return "CZ75-A";
			break;
		case weapon_revolver:
			return "Revolver";
			break;
		case weapon_knife_bayonet:
			return "Bayonet";
			break;
		case weapon_knife_css:
			return "Classic Knife";
			break;
		case weapon_knife_flip:
			return "Flip Knife";
			break;
		case weapon_knife_gut:
			return "Gut Knife";
			break;
		case weapon_knife_karambit:
			return "Karambit";
			break;
		case weapon_knife_m9_bayonet:
			return "M9 Bayonet";
			break;
		case weapon_knife_tactical:
			return "Huntsman Knife";
			break;
		case weapon_knife_falchion:
			return "Falchion Knife";
			break;
		case weapon_knife_survival_bowie:
			return "Bowie Knife";
			break;
		case weapon_knife_butterfly:
			return "Butterfly Knife";
			break;
		case weapon_knife_push:
			return "Shadow Daggers";
			break;
		case weapon_knife_cord:
			return "Paracord Knife";
			break;
		case weapon_knife_canis:
			return "Survival Knife";
			break;
		case weapon_knife_ursus:
			return "Ursus Knife";
			break;
		case weapon_knife_gypsy_jackknife:
			return "Navaja Knife";
			break;
		case weapon_knife_outdoor:
			return "Nomad Knife";
			break;
		case weapon_knife_stiletto:
			return "Stiletto Knife";
			break;
		case weapon_knife_widowmaker:
			return "Talon Knife";
			break;
		case weapon_knife_skeleton:
			return "Skeleton Knife";
			break;
		default:
			return "Knife";
		}
	}

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
	NETVAR( "DT_BaseCombatWeapon->m_flNextPrimaryAttack", m_flNextPrimaryAttack, float );
	NETVAR( "DT_BaseCombatWeapon->m_flNextSecondaryAttack", m_flNextSecondaryAttack, float );
	// m_nNextThinkTick        
	// m_flTimeWeaponIdle      

	/* DT_WeaponCSBase */
	// m_weaponMode
	NETVAR( "DT_WeaponCSBase->m_fAccuracyPenalty", m_fAccuracyPenalty, float );
	NETVAR( "DT_WeaponCSBase->m_fLastShotTime", m_fLastShotTime, float );
	// m_flRecoilIndex
	// m_flRecoilIndex
	// m_hPrevOwner
	// m_bBurstMode
	NETVAR( "DT_BaseCombatWeapon->m_flPostponeFireReadyTime", m_flPostponeFireReadyTime, float );
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
