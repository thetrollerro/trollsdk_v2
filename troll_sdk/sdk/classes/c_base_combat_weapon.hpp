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
	weapon_scar20 = 38,
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
	weapon_knife_ccs = 503,
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

	std::string get_name( ) {
		return std::string( this->get_cs_weapon_data( )->weapon_name );
	}

	std::string weapon_name( ) {
		if ( !this || !m_iItemDefinitionIndex( ) )
			return "invalid";

		int weap_id = this->m_iItemDefinitionIndex( );
		switch ( weap_id ) {
		case weapon_deagle:
			return "deagle";
		case weapon_elite:
			return "elite";
		case weapon_fiveseven:
			return "fiveseven";
		case weapon_glock:
			return "glock";
		case weapon_ak47:
			return "ak47";
		case weapon_aug:
			return "aug";
		case weapon_awp:
			return "awp";
		case weapon_famas:
			return "famas";
		case weapon_g3sg1:
			return "g3sg1";
		case weapon_galilar:
			return "galilar";
		case weapon_m249:
			return "m249";
		case weapon_m4a1:
			return "m4a4";
		case weapon_mac10:
			return "mac10";
		case weapon_p90:
			return "p90";
		case weapon_ump45:
			return "ump45";
		case weapon_xm1014:
			return "xm1014";
		case weapon_bizon:
			return "bizon";
		case weapon_mag7:
			return "mag7";
		case weapon_negev:
			return "negev";
		case weapon_sawedoff:
			return "sawedoff";
		case weapon_tec9:
			return "tec9";
		case weapon_hkp2000:
			return "hkp2000";
		case weapon_mp7:
			return "mp7";
		case weapon_mp9:
			return "mp9";
		case weapon_nova:
			return "nova";
		case weapon_p250:
			return "p250";
		case weapon_scar20:
			return "scar20";
		case weapon_sg553:
			return "sg553";
		case weapon_ssg08:
			return "ssg08";
		case weapon_m4a1_silencer:
			return "m4a1_silencer";
		case weapon_usp_silencer:
			return "usp_silencer";
		case weapon_cz75a:
			return "cz75a";
		case weapon_revolver:
			return "revolver";
		case weapon_knife_bayonet:
			return "bayonet";
		case weapon_knife_ccs:
			return "knife_ccs";
		case weapon_knife_flip:
			return "knife_flip";
		case weapon_knife_gut:
			return "knife_gut";
		case weapon_knife_karambit:
			return "knife_karambit";
		case weapon_knife_m9_bayonet:
			return "knife_m9_bayonet";
		case weapon_knife_tactical:
			return "knife_tactical";
		case weapon_knife_falchion:
			return "knife_falchion";
		case weapon_knife_survival_bowie:
			return "knife_survival_bowie";
		case weapon_knife_butterfly:
			return "knife_butterfly";
		case weapon_knife_push:
			return "knife_push";
		case weapon_knife_cord:
			return "knife_cord";
		case weapon_knife_canis:
			return "knife_canis";
		case weapon_knife_ursus:
			return "knife_ursus";
		case weapon_knife_gypsy_jackknife:
			return "knife_gypsy_jackknife";
		case weapon_knife_stiletto:
			return "knife_stiletto";
		case weapon_knife_outdoor:
			return "knife_outdoor";
		case weapon_knife_widowmaker:
			return "knife_widowmaker";
		case weapon_knife_skeleton:
			return "knife_skeleton";
		case weapon_taser:
			return "zeus";
		default:
			return "invalid";
		}
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

	/* DT_BaseCombatWeapon */
	// m_iViewModelIndex    
	// m_iWorldModelIndex          
	// m_iWorldDroppedModelIndex   
	// m_iState                    
	// m_hOwner                    
	// m_iClip1   
	NETVAR( "DT_BaseCombatWeapon->m_iClip1", m_iClip1, int );
	// m_iClip2                    
	NETVAR( "DT_BaseCombatWeapon->m_iPrimaryReserveAmmoCount", m_iPrimaryReserveAmmoCount, int );
	// m_iSecondaryReserveAmmoCount
	// m_hWeaponWorldModel         
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