#pragma once
#include "../../math/vector.hpp"
#include "../../utl.hpp"
struct sndinfo_t;
class i_recipient_filter;

enum soundlevel_t
{
	sndlvl_none = 0,
	sndlvl_20db = 20,		// rustling leaves
	sndlvl_25db = 25,		// whispering
	sndlvl_30db = 30,		// library
	sndlvl_35db = 35,
	sndlvl_40db = 40,
	sndlvl_45db = 45,		// refrigerator
	sndlvl_50db = 50,	    // 3.9    // average home
	sndlvl_55db = 55,	    // 3.0
	sndlvl_idle = 60,	    // 2.0	
	sndlvl_60db = 60,	    // 2.0	// normal conversation, clothes dryer
	sndlvl_65db = 65,	    // 1.5	// washing machine, dishwasher
	sndlvl_static = 66,	    // 1.25
	sndlvl_70db = 70,	    // 1.0	// car, vacuum cleaner, mixer, electric sewing machine
	sndlvl_norm = 75,
	sndlvl_75db = 75,	    // 0.8	// busy traffic
	sndlvl_80db = 80,	    // 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
	sndlvl_talking = 80,    // 0.7
	sndlvl_85db = 85,	    // 0.6	// average factory, electric shaver
	sndlvl_90db = 90,	    // 0.5	// screaming child, passing motorcycle, convertible ride on frw
	sndlvl_95db = 95,
	sndlvl_100db = 100,	    // 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
	sndlvl_105db = 105,     // helicopter, power mower
	sndlvl_110db = 110,     // snowmobile drvrs seat, inboard motorboat, sandblasting
	sndlvl_120db = 120,     // auto horn, propeller aircraft
	sndlvl_130db = 130,     // air raid siren
	sndlvl_gunfire = 140,	// 0.27	// threshold of pain, gunshot, jet engine
	sndlvl_140db = 140,	    // 0.2
	sndlvl_150db = 150,	    // 0.2
	sndlvl_180db = 180,		// rocket launching
};

//-----------------------------------------------------------------------------
// common pitch values
//-----------------------------------------------------------------------------
#define	pitch_norm		100			  // non-pitch shifted
#define pitch_low		95			    // other values are possible - 0-255, where 255 is very high
#define pitch_high		120

struct start_sound_params_t;

class i_engine_sound {
public:
	virtual bool precache_sound( const char* pSample, bool bPreload = false, bool bIsUISound = false ) = 0;
	virtual bool is_sound_precached( const char* pSample ) = 0;
	virtual void prefech_sound( const char* pSample ) = 0;
	virtual bool is_looping_sound( const char* pSample ) = 0;
	virtual float get_sound_duration( const char* pSample ) = 0;
	virtual int emit_sound( i_recipient_filter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags = 0, int iPitch = pitch_norm, const vec3_t* pOrigin = NULL, const vec3_t* pDirection = NULL, CUtlVector< vec3_t >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1 ) = 0;
	virtual int emit_sound( i_recipient_filter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = pitch_norm, const vec3_t* pOrigin = NULL, const vec3_t* pDirection = NULL, CUtlVector< vec3_t >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1 ) = 0;
	virtual void emit_sentence_by_index( i_recipient_filter& filter, int iEntIndex, int iChannel, int iSentenceIndex, float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = pitch_norm, const vec3_t* pOrigin = nullptr, const vec3_t* pdirection = NULL, CUtlVector< vec3_t >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1 ) = 0;
	virtual void stop_sound( int iEntIndex, int iChannel, const char* pSample, unsigned int nSoundEntryHash ) = 0;
	virtual void stop_all_sounds( bool bClearBuffers ) = 0;
	virtual void set_room_type( i_recipient_filter& filter, int roomType ) = 0;
	virtual void set_player_dsp( i_recipient_filter& filter, int dspType, bool fastReset ) = 0;
	virtual int emit_ambient_sound( const char* pSample, float flVolume, int iPitch = pitch_norm, int flags = 0, float soundtime = 0.0f ) = 0;
	virtual float get_dist_gain_from_sound_level( soundlevel_t soundlevel, float dist ) = 0;
	virtual int get_guid_for_last_sound_emitted( ) = 0;
	virtual bool is_sound_still_playing( int guid ) = 0;
	virtual void stop_sound_by_guid( int guid, bool bForceSync ) = 0;
	virtual void set_volume_by_guid( int guid, float fvol ) = 0;
	virtual void unk( ) = 0;
	virtual void get_active_sound( CUtlVector<sndinfo_t>& sndlist ) = 0;
	virtual void precache_sentece_group( const char* pGroupName ) = 0;
	virtual void motify_begin_movie_playback( ) = 0;
	virtual void notify_end_movie_playback( ) = 0;
	virtual bool get_sound_channel_volume( const char* sound, float& flVolumeLeft, float& flVolumeRight ) = 0;
	virtual float get_elapsed_time_by_guid( int guid ) = 0;
};