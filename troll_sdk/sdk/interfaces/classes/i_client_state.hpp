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

class i_net_channel;
class i_client_state {
public:
	void force_full_update( ) {
		delta_tick = -1;
	}

	uint8_t pad0[ 0x9C ]; //0x0000
	i_net_channel* net_channel; //0x009C
	int challenge_nr; //0x00A0
	uint8_t pad1[ 0x64 ]; //0x00A4
	int signon_state;  //0x0108
	uint8_t pad2[ 0x8 ]; //0x010C
	float next_cmd_time; //0x0114
	int server_count; //0x0118
	int current_seqeunce; //0x011C
	uint8_t pad0x3[ 4 ];
	c_clock_drift_mgr clock_drift_mgr; //0x0124 
	uint8_t pad3[ 68 ];
	int server_tick; //0x016C 
	int client_tick; //0x0170 
	int delta_tick; //0x0174
	bool paused; //0x0178
	uint8_t pad4[ 0x7 ]; //0x0179
	int view_entity; //0x0180
	int player_slot; //0x0184
	char level_name[ 260 ]; //0x0188
	char level_name_short[ 80 ]; //0x028C
	char group_name[ 80 ]; //0x02DC
	uint8_t pad5[ 0x5C ]; //0x032C
	int max_clients;  //0x0388
	uint8_t pad6[ 0x4984 ]; //0x038C
	float last_server_tick_time; //0x4D10
	bool in_simulation; //0x4D14
	uint8_t pad7[ 0xB ]; //0x4D15
	int old_tickcount; //0x4D18
	float tick_remainder; //0x4D1C
	float frametime; //0x4D20
	int last_outgoing_command; //0x4D38
	int choked_commands; //0x4D30
	int last_command_ack; //0x4D2C
	int command_ack; //0x4D30
	int sound_sequence; //0x4D34
	uint8_t pad8[ 0x50 ]; //0x4D38
	vec3_t viewangles; //0x4D88
	uint8_t pad9[ 0xD0 ]; //0x4D9A
};