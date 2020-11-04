#include "interfaces.hpp"
#include "../../utilities/utilities.hpp"

void i::init( ) {
	/* init interfaces */
	entitylist = get_interface<c_entity_list>( ( "client.dll" ), ( "VClientEntityList003" ), true );
	game_movement = get_interface<c_game_movement>( "client.dll", "GameMovement001", true );
	input_system = get_interface<c_input_system>( "inputsystem.dll", "InputSystemVersion001", true );
	prediction = get_interface<c_prediction>( "client.dll", "VClientPrediction001", true );
	clientdll = get_interface<i_client_dll>( "client.dll", "VClient018", true );
	cvar = get_interface<i_cvar>( "vstdlib.dll", "VEngineCvar007", true );
	material_system = get_interface<i_material_system>( "materialsystem.dll", "VMaterialSystem080", true );
	surface = get_interface<i_surface>( "vguimatsurface.dll", "VGUI_Surface031", true );
	trace = get_interface<i_trace>( "engine.dll", "EngineTraceClient004", true );
	engine = get_interface<iv_engine_client>( "engine.dll", "VEngineClient014", true );
	modelinfo = get_interface<iv_model_info>( "engine.dll", "VModelInfoClient004", true );
	modelrender = get_interface<iv_model_render>( "engine.dll", "VEngineModel016", true );

	/* custom */
	globalvars = **( c_global_vars*** ) ( ( *( DWORD** ) clientdll )[ 11 ] + 10 );
	input = *( c_input** ) ( utils::find_sig_ida( "client.dll", "B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? B8 ? ? ? ?" ) + 7 );
	movehelper = **( c_move_helper*** ) ( utils::find_sig_ida( "client.dll", "8B 0D ? ? ? ? 8B 46 08 68" ) + 2 );
	clientmode = **( i_client_mode*** ) ( ( *( DWORD** ) clientdll )[ 10 ] + 5 );
	clientstate = **( i_client_state*** ) ( utils::find_sig_ida( "engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) + 1 );
	dx9 = **( IDirect3DDevice9*** ) ( utils::find_sig_ida( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1 );
}