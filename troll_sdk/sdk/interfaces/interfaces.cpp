#include "interfaces.hpp"
#include "../../utilities/utilities.hpp"

void i::init( ) {
	/* init interfaces */
	entitylist = get_interface<c_entity_list>( _( "client.dll" ), _( "VClientEntityList003" ), true );
	file_system = get_interface<c_file_system>( _( "filesystem_stdio.dll" ), _( "VFileSystem017" ), true );
	game_movement = get_interface<c_game_movement>( _( "client.dll" ), _( "GameMovement001" ), true );
	input_system = get_interface<c_input_system>( _( "inputsystem.dll" ), _( "InputSystemVersion001" ), true );
	memalloc = *reinterpret_cast< c_memalloc** >( GetProcAddress( GetModuleHandleA( _( "tier0.dll" ) ), _( "g_pMemAlloc" ) ) );
	prediction = get_interface<c_prediction>( _( "client.dll" ), _( "VClientPrediction001" ), true );
	clientdll = get_interface<i_client_dll>( _( "client.dll" ), _( "VClient018" ), true );
	cvar = get_interface<i_cvar>( _( "vstdlib.dll" ), _( "VEngineCvar007" ), true );
	engine_sound = get_interface<i_engine_sound>( _( "engine.dll" ), _( "IEngineSoundClient003" ), true );
	event_manager = get_interface<i_game_event_manager>( _( "engine.dll" ), _( "GAMEEVENTSMANAGER002" ), true );
	key_values = reinterpret_cast< i_key_values * ( __cdecl* )( ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "KeyValuesSystem" ) )( );
	localize = get_interface<i_localize>( _( "localize.dll" ), _( "Localize_001" ), true );
	material_system = get_interface<i_material_system>( _( "materialsystem.dll" ), _( "VMaterialSystem080" ), true );
	panel = get_interface<i_panel>( _( "vgui2.dll" ), _( "VGUI_Panel009" ), true );
	surface = get_interface<i_surface>( _( "vguimatsurface.dll" ), _( "VGUI_Surface031" ), true );
	surface_props = get_interface<i_surface_props>( _( "vphysics.dll" ), _( "VPhysicsSurfaceProps001" ), true );
	trace = get_interface<i_trace>( _( "engine.dll" ), _( "EngineTraceClient004" ), true );
	debug_overlay = get_interface<iv_debug_overlay>( _( "engine.dll" ), _( "VDebugOverlay004" ), true );
	engine = get_interface<iv_engine_client>( _( "engine.dll" ), _( "VEngineClient014" ), true );
	modelinfo = get_interface<iv_model_info>( _( "engine.dll" ), _( "VModelInfoClient004" ), true );
	modelrender = get_interface<iv_model_render>( _( "engine.dll" ), _( "VEngineModel016" ), true );

	/* custom */
	globalvars = **( c_global_vars*** ) ( ( *( DWORD** ) clientdll )[ 11 ] + 10 );
	glow_manager = *( c_glow_object_manager** ) ( utils::find_sig_ida( _( "client.dll" ), _( "0F 11 05 ? ? ? ? 83 C8 01" ) ) + 3 );
	input = *( c_input** ) ( utils::find_sig_ida( _( "client.dll" ), _( "B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? B8 ? ? ? ?" ) ) + 7 );
	movehelper = **( c_move_helper*** ) ( utils::find_sig_ida( _( "client.dll" ), _( "8B 0D ? ? ? ? 8B 46 08 68" ) ) + 2 );
	clientmode = **( i_client_mode*** ) ( ( *( DWORD** ) clientdll )[ 10 ] + 5 );
	clientstate = **( i_client_state*** ) ( utils::find_sig_ida( _( "engine.dll" ), _( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) ) + 1 );
	render_beams = *( iv_view_render_beams** ) ( utils::find_sig_ida( _( "client.dll" ), _( "A1 ? ? ? ? FF 10 A1 ? ? ? ? B9" ) ) + 0x1 );
	dx9 = **( IDirect3DDevice9*** ) ( utils::find_sig_ida( _( "shaderapidx9.dll" ), _( "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C" ) ) + 1 );
}