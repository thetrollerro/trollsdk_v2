#include <Windows.h>
#include <iostream>
#include <thread>
#include "sdk/interfaces/interfaces.hpp"
#include "hooks/hooks.hpp"
#include "sdk/netvar/netvar.hpp"
#include "utilities/security/xorstr.hpp"

void dll_on_attach( HINSTANCE mod ) {
	/* wait for all modules to load */
	while ( !GetModuleHandleA( _( "serverbrowser.dll" ) ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	//MessageBox( 0, _( "onistrix Was Succesfully Injected" ), _( "onistrix.club" ), MB_OK | MB_ICONINFORMATION );

	/*if ( GlobalFindAtomA( _( "IfUSeeThisSuckMyCockBitch" ) ) == 0 ) {
		MessageBox( 0, _( ", Sike Bitch u Really thougth u cracked the cheat ajajajaja" ), _( "onistrix.club" ), 0 );
		exit( 0 );
	}*/

	/* initialize csgo hack */
	i::init( );
	render::start( i::dx9 );
	netvars::init( );
	hooks::init( );

	/* after initializing we disable our atom */
	GlobalDeleteAtom( GlobalFindAtomA( _( "IfUSeeThisSuckMyCockBitch" ) ) );

	/* wait for unload key */
	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

	/* unload */
	hooks::restore( );

	fclose( ( FILE* ) stdin );
	fclose( ( FILE* ) stdout );
	FreeConsole( );
	FreeLibraryAndExitThread( mod, 0 );
}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID reserved ) {

	if ( reason == DLL_PROCESS_ATTACH )
		CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( dll_on_attach ), HMODULE( instance ), 0, nullptr );

	return true;
}