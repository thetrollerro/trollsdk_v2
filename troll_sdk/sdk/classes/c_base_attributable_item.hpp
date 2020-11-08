#pragma once
#include "c_base_entity.hpp"

class c_base_attributable_item : public c_base_entity {
public:
	/* DT_BaseAttributableItem */
	// m_OriginalOwnerXuidLow                      
	// m_OriginalOwnerXuidHigh                     
	// m_nFallbackPaintKit                         
	// m_nFallbackSeed                             
	// m_flFallbackWear                            
	// m_nFallbackStatTrak                         
	// m_AttributeManager                          
	// m_hOuter                                
	// m_ProviderType                          
	// m_iReapplyProvisionParity               
	// m_Item                                  
	NETVAR( "DT_BaseAttributableItem->m_iItemDefinitionIndex", m_iItemDefinitionIndex, short );
	// m_iEntityLevel                      
	// m_iItemIDHigh                       
	// m_iItemIDLow                        
	// m_iAccountID                        
	// m_iEntityQuality                    
	// m_bInitialized                      
	// m_szCustomName                      
	// m_NetworkedDynamicAttributesForDemos
	// m_Attributes                    
	// lengthproxy                 
	// lengthprop32   
};