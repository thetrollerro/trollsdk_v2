#include <Windows.h>
#include <iostream>
#include <thread>
#include "sdk/interfaces/interfaces.hpp"
#include "hooks/hooks.hpp"
#include "sdk/netvar/netvar.hpp"
HINSTANCE this_mod;
void dll_on_attach( ) {
	/* wait for all modules to load */
	while ( !GetModuleHandleA( "serverbrowser.dll" ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	/* initialize csgo hack */
	i::init( );
	netvars::init( );
	hooks::init( );
	 
	/* wait for unload key */
	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

	/* unload */
	hooks::restore( );

	fclose( ( FILE* ) stdin );
	fclose( ( FILE* ) stdout );
	FreeConsole( );
	FreeLibraryAndExitThread( this_mod, 0 );
}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID reserved ) {

	if ( reason == DLL_PROCESS_ATTACH )
		CreateThread( nullptr, 0, ( LPTHREAD_START_ROUTINE ) dll_on_attach, HMODULE( instance ), 0, nullptr );

	return true;
}