#include "../hooks.hpp"

void __fastcall hooks::engine_sound::emit_sound_1::hook( void* ecx, void* edx, i_recipient_filter& filter, int ent_index, int channel, const char* sound_entry, unsigned int sound_entry_hash, const char* sample, float volume, int seed, float attenuation, int flags, int pitch, const vec3_t* origin, const vec3_t* direction, void* utl_vec_origins, bool update_positions, float sound_time, int speaker_entity, int unk ) {
	o_emit_sound_1( ecx, edx, filter, ent_index, channel, sound_entry, sound_entry_hash, sample, volume, seed, attenuation, flags, pitch, origin, direction, utl_vec_origins, update_positions, sound_time, speaker_entity, unk );
}