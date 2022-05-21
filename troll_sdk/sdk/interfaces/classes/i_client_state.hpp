#pragma once
#include <cstdint>
#include "i_trace.hpp"
#include "../../client_class.hpp"

class i_net_channel;
class i_client_state {
public:
    void force_full_update( ) {
        m_delta_tick = -1;
    }

    std::byte pad0[ 0x9C ]; //0x0000
    i_net_channel* m_net_channel; //0x009C
    int m_challenge_nr; //0x00A0
    std::byte pad1[ 0x64 ]; //0x00A4
    int m_signon_state;  //0x0108
    std::byte pad2[ 0x8 ]; //0x010C
    float m_next_cmd_time; //0x0114
    int m_server_count; //0x0118
    int m_current_seqeunce; //0x011C
    char _0x0120[ 8 ];

    struct {
        float        clock_offsets[ 16 ];
        int            cur_clock_offset;
        int            m_server_tick;
        int            m_client_tick;
    } m_clock_drift_mgr; //0x0124 

    int m_delta_tick; //0x0174
    bool m_paused; //0x0178
    std::byte pad4[ 0x7 ]; //0x0179
    int m_view_entity; //0x0180
    int m_player_slot; //0x0184
    char m_level_name[ 260 ]; //0x0188
    char m_level_name_short[ 80 ]; //0x028C
    char m_group_name[ 80 ]; //0x02DC
    std::byte pad5[ 0x5C ]; //0x032C
    int m_max_clients;  //0x0388
    std::byte pad6[ 0x4984 ]; //0x038C
    float m_last_server_tick_time; //0x4D10
    bool m_in_simulation; //0x4D14
    std::byte pad7[ 0xB ]; //0x4D15
    int m_old_tickcount; //0x4D18
    float m_tick_remainder; //0x4D1C
    float m_frametime; //0x4D20
    int m_last_outgoing_command; //0x4D38
    int m_choked_commands; //0x4D30
    int m_last_command_ack; //0x4D2C
    int m_command_ack; //0x4D30
    int m_sound_sequence; //0x4D34
    std::byte pad8[ 0x50 ]; //0x4D38
    vec3_t m_viewangles; //0x4D88
    std::byte pad9[ 204 ]; //0x4D9A
    event_t* events;
};