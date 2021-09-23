#pragma once
#include "../netvar/netvar.hpp"
#include "../datamap.hpp"
#include "i_client_entity.hpp"
#include "../interfaces/interfaces.hpp"

class c_base_player;
class c_base_entity : public i_client_entity {
public:
	static __forceinline c_base_entity* get_entity_by_index( int index ) {
		return static_cast< c_base_entity* >( i::entitylist->get_client_entity( index ) );
	}

	/* datamap */
	datamap_t* get_data_desc_map( ) {
		typedef datamap_t* ( __thiscall* o_fn )( void* );
		return utils::call_virtual<o_fn>( this, 15 )( this );
	}

	datamap_t* get_pred_desc_map( ) {
		typedef datamap_t* ( __thiscall* o_fn )( void* );
		return utils::call_virtual<o_fn>( this, 17 )( this );
	}

	/* other */
	bool is_player( ) {
		using o_fn = bool( __thiscall* )( c_base_entity* );
		return utils::call_virtual<o_fn>( this, 158 )( this );
	}

	bool is_weapon( ) {
		using o_fn = bool( __thiscall* )( c_base_entity* );
		return utils::call_virtual<o_fn>( this, 166 )( this );
	}

	const matrix_t& m_rgflCoordinateFrame( ) {
		static auto _m_rgflCoordinateFrame = netvars::get_offset( "DT_BaseEntity->m_CollisionGroup" ) - 0x30;
		return *( matrix_t* ) ( ( uintptr_t ) this + _m_rgflCoordinateFrame );
	}

	/* DT_EnvTonemapController */
	NETVAR( "DT_EnvTonemapController->m_bUseCustomAutoExposureMin", m_bUseCustomAutoExposureMin, bool );
	NETVAR( "DT_EnvTonemapController->m_bUseCustomAutoExposureMax", m_bUseCustomAutoExposureMax, bool );
	NETVAR( "DT_EnvTonemapController->m_bUseCustomBloomScale", m_bUseCustomBloomScale, bool );
	NETVAR( "DT_EnvTonemapController->m_flCustomAutoExposureMin", m_flCustomAutoExposureMin, float );
	NETVAR( "DT_EnvTonemapController->m_flCustomAutoExposureMax", m_flCustomAutoExposureMax, float );
	NETVAR( "DT_EnvTonemapController->m_flCustomBloomScale", m_flCustomBloomScale, float );
	NETVAR( "DT_EnvTonemapController->m_flCustomBloomScaleMinimum", m_flCustomBloomScaleMinimum, float );
	NETVAR( "DT_EnvTonemapController->m_flBloomExponent", m_flBloomExponent, float );
	NETVAR( "DT_EnvTonemapController->m_flBloomSaturation", m_flBloomSaturation, float );
	NETVAR( "DT_EnvTonemapController->m_flTonemapPercentTarget", m_flTonemapPercentTarget, float );
	NETVAR( "DT_EnvTonemapController->m_flTonemapPercentBrightPixels", m_flTonemapPercentBrightPixels, float );
	NETVAR( "DT_EnvTonemapController->m_flTonemapMinAvgLum", m_flTonemapMinAvgLum, float );
	NETVAR( "DT_EnvTonemapController->m_flTonemapRate", m_flTonemapRate, float );

	/* DT_BaseEntity */
	// m_cellbits
	// m_cellX
	// m_cellY
	// m_cellZ
	NETVAR( "DT_BaseEntity->m_angRotation", m_angRotation, vec3_t );
	NETVAR( "DT_BaseEntity->m_nModelIndex", m_nModelIndex, int );
	// m_fEffects
	// m_nRenderMode
	// m_nRenderFX
	// m_clrRender
	NETVAR( "DT_BaseEntity->m_iTeamNum", m_iTeamNum, int );
	// m_iPendingTeamNum
	// m_CollisionGroup
	// m_flElasticity
	NETVAR( "DT_BaseEntity->m_flShadowCastDistance", m_flShadowCastDistance, float );
	NETVAR( "DT_BaseEntity->m_hOwnerEntity", m_hOwnerEntity, unsigned long );
	// m_hEffectEntity
	// moveparent
	// m_iParentAttachment
	// m_iName
	NETVAR_OFFSET( "DT_BaseEntity->m_nRenderMode", 0x1, m_nMoveType, int );
	// movecollide
	// m_iTextureFrameIndex
	// m_bSimulatedEveryTick
	// m_bAnimatedEveryTick
	// m_bAlternateSorting
	NETVAR( "DT_BaseEntity->m_bSpotted", m_bSpotted, bool );
	// m_bIsAutoaimTarget
	// m_fadeMinDist
	// m_fadeMaxDist
	// m_flFadeScale
	// m_nMinCPULevel
	// m_nMaxCPULevel
	// m_nMinGPULevel
	// m_nMaxGPULevel
	// m_flUseLookAtAngle
	// m_flLastMadeNoiseTime
	// m_flMaxFallVelocity
	NETVAR( "DT_BaseEntity->m_flVelocityModifier", m_flVelocityModifier, float );
	// m_bEligibleForScreenHighlight
	// m_Collision->m_vecMins
	// m_Collision->m_vecMaxs
	// m_Collision->m_nSolidType
	// m_Collision->m_usSolidFlags
	// m_Collision->m_nSurroundType
	// m_Collision->m_triggerBloat
	// m_Collision->m_vecSpecifiedSurroundingMins
	// m_Collision->m_vecSpecifiedSurroundingMaxs
	// m_bSpottedBy
	// m_bSpottedByMask

};