#pragma once
#include <cstdint>
#include "i_trace.hpp"

class c_clock_drift_mgr
{
public:
	float clock_offsets[ 17 ];   //0x0000
	uint32_t cur_clock_offsets; //0x0044
	uint32_t server_tick;     //0x0048
	uint32_t client_tick;     //0x004C
}; //Size: 0x0050

class c_event_info
{
public:

	uint16_t class_id; //0x0000 0 implies not in use
	char pad_0002[ 2 ]; //0x0002 
	float fire_delay; //0x0004 If non-zero, the delay time when the event should be fired ( fixed up on the client )
	char pad_0008[ 4 ]; //0x0008
	c_client_class* client_class; //0x000C
	void* data; //0x0010 Raw event data
	char pad_0014[ 48 ]; //0x0014
}; //Size: 0x0044

class i_net_channel;
class i_client_state {
public:
	void force_full_update( ) {
		*reinterpret_cast< int* >( std::uintptr_t( this ) + 0x174 ) = -1;
	}

	char pad000[ 0x9C ];
	i_net_channel* net_channel;
	int nChallengeNr;
	char pad001[ 0x4 ];
	double connect_time;
	int retry_number;
	char pad002[ 0x54 ];
	int nSignonState;
	char pad003[ 0x4 ];
	double flNextCmdTime;
	int nServerCount;
	int current_sequence;
	char pad004[ 0x8 ];
	c_clock_drift_mgr clock_drift_mgr;
	int delta_tick;
	char pad005[ 0x4 ];
	int nViewEntity;
	int nPlayerSlot;
	bool bPaused;
	char pad006[ 0x3 ];
	char szLevelName[ 0x104 ];
	char szLevelNameShort[ 0x28 ];
	char  pad007[ 0xD4 ];
	int max_clients;
	char pad008[ 0x4994 ];
	int oldtickcount;
	float tickRemainder;
	float frameTime;
	int last_outgoing_command;
	int choked_commands;
	int last_command_ack;
	int last_server_tick;
	int command_ack;
	int nSoundSequence;
	int last_progress_percent;
	bool is_hltv;
	char pad009[ 0x4B ];
	vec3_t viewangles;
	char pad010[ 0xCC ];
	c_event_info* events;

	std::uint32_t& choked( ) {
		return *reinterpret_cast< std::uint32_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x4D30 );
	}
};