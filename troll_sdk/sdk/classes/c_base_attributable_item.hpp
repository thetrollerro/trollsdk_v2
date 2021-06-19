#pragma once
#include "c_base_entity.hpp"

class c_base_attributable_item : public c_base_entity {
public:
	/* DT_BaseAttributableItem */
	NETVAR( "DT_BaseAttributableItem->m_OriginalOwnerXuidLow", m_OriginalOwnerXuidLow, int );
	NETVAR( "DT_BaseAttributableItem->m_OriginalOwnerXuidHigh", m_OriginalOwnerXuidHigh, int );
	NETVAR( "DT_BaseAttributableItem->m_nFallbackPaintKit", m_nFallbackPaintKit, int );
	NETVAR( "DT_BaseAttributableItem->m_nFallbackSeed", m_nFallbackSeed, int );
	NETVAR( "DT_BaseAttributableItem->m_flFallbackWear", m_flFallbackWear, float );
	// m_nFallbackStatTrak                         
	// m_AttributeManager                          
	// m_hOuter                                
	// m_ProviderType                          
	// m_iReapplyProvisionParity               
	// m_Item                                  
	NETVAR( "DT_BaseAttributableItem->m_iItemDefinitionIndex", m_iItemDefinitionIndex, short );
	// m_iEntityLevel                      
	NETVAR( "DT_BaseAttributableItem->m_iItemIDHigh", m_iItemIDHigh, int );
	// m_iItemIDLow                        
	NETVAR( "DT_BaseAttributableItem->m_iAccountID", m_iAccountID, int );
	NETVAR( "DT_BaseAttributableItem->m_iEntityQuality", m_iEntityQuality, int );
	// m_bInitialized                      
	// m_szCustomName                      
	// m_NetworkedDynamicAttributesForDemos
	// m_Attributes                    
	// lengthproxy                 
	// lengthprop32   
};