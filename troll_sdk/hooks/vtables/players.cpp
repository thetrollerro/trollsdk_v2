#include "../hooks.hpp"

vec3_t* __fastcall hooks::players::get_eye_ang::hook( void* ecx, void* edx ) {
	if ( !g_local || !i::engine->is_in_game( ) ) return o_get_eye_ang( ecx, edx );
	if ( ecx != g_local ) return o_get_eye_ang( ecx, 0 );

	static auto ret_to_thirdperson_pitch = utils::find_sig_ida( "client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?" );
	static auto ret_to_thirdperson_yaw = utils::find_sig_ida( "client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?" );

	if ( _ReturnAddress( ) == ( void* ) ret_to_thirdperson_pitch || _ReturnAddress( ) == ( void* ) ret_to_thirdperson_yaw )
		return g::cmd ? &g::cmd->viewangles : &g_local->m_angEyeAngles( );

	return o_get_eye_ang( ecx, 0 );
}