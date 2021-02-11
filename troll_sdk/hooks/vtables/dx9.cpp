#include "../hooks.hpp"
#include "../../menu/menu.hpp"

long __fastcall hooks::dx9::endscene::hook( void* ecx, void* edx, IDirect3DDevice9* dev ) {
	/* init d3d */
	if ( !menu::d3d_init ) {
		menu::style( dev );
		menu::d3d_init = true;
	}

	/* endscene gets called twice so we call it once */
	static auto ret = _ReturnAddress( );
	if ( ret != _ReturnAddress( ) ) {
		return o_endscene( ecx, 0, dev );
	}

	/* backup */
	IDirect3DStateBlock9* stateBlock = nullptr;
	IDirect3DVertexDeclaration9* vertDec = nullptr;
	dev->GetVertexDeclaration( &vertDec );
	dev->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlock );

	/* menu */
	menu::init( );

	/* restore */
	stateBlock->Apply( );
	stateBlock->Release( );
	dev->SetVertexDeclaration( vertDec );

	return o_endscene( ecx, 0, dev );
}

long __fastcall hooks::dx9::present::hook( void* ecx, void* edx, IDirect3DDevice9* dev, RECT* source_rect, RECT* dust_rect, HWND dest_window_override, RGNDATA* dirty_region ) {
	/* here our esp will be streamproof so ya call it here if we wan t streamproof :D */

	return o_present( ecx, 0, dev, source_rect, dust_rect, dest_window_override, dirty_region );
}

long __fastcall hooks::dx9::reset::hook( void* ecx, void* edx, IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params ) {
	/* destroy fonts */
	render::destroy_fonts( );

	if ( !menu::d3d_init )
		return o_reset( ecx, 0, dev, params );

	/* invalidate dev objects */
	ImGui_ImplDX9_InvalidateDeviceObjects( );

	auto hr = o_reset( ecx, 0, dev, params );
	if ( SUCCEEDED( hr ) ) {
		/* recreate imgui */
		ImGui_ImplDX9_CreateDeviceObjects( );

		/* recreate fonts */
		render::create_fonts( );
	}

	return hr;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
long __stdcall hooks::dx9::wndproc::hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {

	if ( msg == WM_KEYUP && wparam == VK_INSERT )
		menu::opened = !menu::opened;

	if ( menu::opened ) {
		/* ImGui_ImplWin32_WndProcHandler returns false instead of true, so we just do this. */
		if ( ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam ) ) {
			return true;
		}

		/* block game input for some messages */
		switch ( msg )
		{
			/* pressing mouse key */
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:

			/* scrolling */
		case WM_MOUSEWHEEL:

			/* after releasing mouse key */
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:

			/* when moving mouse */
		case WM_MOUSEMOVE:

			/* don't allow game input */
			return true;
		}
	}

	return CallWindowProcA( o_wndproc, hwnd, msg, wparam, lparam );
}