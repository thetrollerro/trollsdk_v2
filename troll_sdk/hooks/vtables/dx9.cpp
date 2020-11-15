#include "../hooks.hpp"
#include "../../menu/menu.hpp"

long __fastcall hooks::dx9::endscene::hook( void* ecx, void* edx, IDirect3DDevice9* dev ) {
	/* endscene gets called twice so we call it once */
	static auto ret = _ReturnAddress( );
	if ( ret != _ReturnAddress( ) ) {
		return o_endscene( ecx, edx, dev );
	}

	/* init d3d */
	if ( !menu::d3d_init ) {
		menu::style( dev );
		menu::d3d_init = true;
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

	return o_endscene( ecx, edx, dev );
}

long __fastcall hooks::dx9::reset::hook( void* ecx, void* edx, IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params ) {
	/* destroy fonts */
	render::destroy_fonts( );

	if ( !menu::d3d_init )
		return o_reset( ecx, edx, dev, params );

	/* invalidate dev objects */
	ImGui_ImplDX9_InvalidateDeviceObjects( );

	auto hr = o_reset( ecx, edx, dev, params );
	if ( SUCCEEDED( hr ) ) {
		/* recreate imgui */
		ImGui_ImplDX9_CreateDeviceObjects( );

		/* recreate fonts */
		render::create_fonts( );
	}

	return hr;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
long __stdcall hooks::dx9::wndproc::hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	if ( msg == WM_KEYUP && wparam == VK_INSERT )
		menu::opened = !menu::opened;

	// ImGui_ImplWin32_WndProcHandler returns false instead of true, so we just do this.
	if ( menu::opened && !ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam ) )
		return true;

	return CallWindowProcA( o_wndproc, hwnd, msg, wparam, lparam );
}