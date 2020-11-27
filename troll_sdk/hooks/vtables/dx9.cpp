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
		return o_endscene( i::dx9, 0, dev );
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

	return o_endscene( i::dx9, 0, dev );
}

long __fastcall hooks::dx9::reset::hook( void* ecx, void* edx, IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params ) {
	/* destroy fonts */
	render::destroy_fonts( );

	if ( !menu::d3d_init )
		return o_reset( i::dx9, 0, dev, params );

	/* invalidate dev objects */
	ImGui_ImplDX9_InvalidateDeviceObjects( );

	auto hr = o_reset( i::dx9, 0, dev, params );
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
	/* open menu */ {
		static bool m_pressed = false;
		const bool m_held = GetAsyncKeyState( VK_INSERT );
		if ( m_pressed != m_held ) {

			if ( m_held ) {
				menu::opened = !menu::opened;
			}

			m_pressed = m_held;
		}
	}

	// ImGui_ImplWin32_WndProcHandler returns false instead of true, so we just do this.
	if ( menu::d3d_init && menu::opened && !ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam ) )
		return true;

	return CallWindowProcA( o_wndproc, hwnd, msg, wparam, lparam );
}