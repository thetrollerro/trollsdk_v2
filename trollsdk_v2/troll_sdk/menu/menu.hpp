#pragma once
#include "../main.hpp"

namespace menu {
	inline bool opened;
	inline bool d3d_init;

	void style( IDirect3DDevice9* dev );
	void init( );
	void render( );

	void misc_tab( );
}