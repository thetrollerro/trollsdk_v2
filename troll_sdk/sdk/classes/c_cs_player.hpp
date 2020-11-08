#pragma once
#include "../netvar/netvar.hpp"

class c_cs_player {
public:
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
};