#pragma once
#include <cstdint>
#include "i_trace.hpp"
#include "../../client_class.hpp"

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
		delta_tick = -1;
	}

	std::byte pad0[ 0x9C ]; //0x0000
	i_net_channel* net_channel; //0x009C
	int challenge_nr; //0x00A0
	std::byte pad1[ 0x64 ]; //0x00A4
	int signon_state;  //0x0108
	std::byte pad2[ 0x8 ]; //0x010C
	float next_cmd_time; //0x0114
	int server_count; //0x0118
	int current_seqeunce; //0x011C
	char _0x0120[ 4 ];
	__int32 clock_drift_mgr; //0x0124 
	char _0x0128[ 68 ];
	__int32 server_tick; //0x016C 
	__int32 client_tick; //0x0170 
	int delta_tick; //0x0174
	bool paused; //0x0178
	std::byte pad4[ 0x7 ]; //0x0179
	int view_entity; //0x0180
	int player_slot; //0x0184
	char level_name[ 260 ]; //0x0188
	char level_name_short[ 80 ]; //0x028C
	char group_name[ 80 ]; //0x02DC
	std::byte pad5[ 0x5C ]; //0x032C
	int max_clients;  //0x0388
	std::byte pad6[ 0x4984 ]; //0x038C
	float last_server_tick_time; //0x4D10
	bool in_simulation; //0x4D14
	std::byte pad7[ 0xB ]; //0x4D15
	int old_tickcount; //0x4D18
	float tick_remainder; //0x4D1C
	float frametime; //0x4D20
	int last_outgoing_command; //0x4D38
	int choked_commands; //0x4D30
	int last_command_ack; //0x4D2C
	int command_ack; //0x4D30
	int sound_sequence; //0x4D34
	std::byte pad8[ 0x50 ]; //0x4D38
	vec3_t viewangles; //0x4D88
	std::byte pad9[ 0xD0 ]; //0x4D9A
};