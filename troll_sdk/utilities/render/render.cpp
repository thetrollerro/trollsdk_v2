#include "render.hpp"
#include "../../main.hpp"

/* https://www.unknowncheats.me/forum/direct3d/60883-draw-drawprimtiveup-d3d9.html */

void render::start( IDirect3DDevice9* dev ) {
	device = dev;

	/* just in-case */
	if ( device != dev ) {
		initialized = false;
		device = dev;
	}

	initialized = true;
}

namespace render {
	namespace fonts {
		ID3DXFont* def;
		ID3DXFont* watermark;
		ID3DXFont* esp_def;
		ID3DXFont* esp_sec;
		ID3DXFont* keystrokes;
	}
}

void render::destroy_fonts( ) {
	render::fonts::def->Release( );
	render::fonts::watermark->Release( );
	render::fonts::esp_def->Release( );
	render::fonts::esp_sec->Release( );
	render::fonts::keystrokes->Release( );
}

void render::create_fonts( ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	render::create_font( ( void** ) &render::fonts::def, "Tahoma", 32, true );
	render::create_font( ( void** ) &render::fonts::watermark, "Tahoma", 16, false );
	render::create_font( ( void** ) &render::fonts::esp_def, "Smallest Pixel-7", 10, FW_NORMAL );
	render::create_font( ( void** ) &render::fonts::esp_sec, "Tahoma", 10, false );
	render::create_font( ( void** ) &render::fonts::keystrokes, "Verdana", 20, FW_BOLD );
}

void render::create_font( void** font, const std::string& family, int size, bool bold ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	ID3DXFont* d3d_font = nullptr;
	D3DXCreateFontA( device, size, 0, bold ? FW_BOLD : FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 0, DEFAULT_PITCH | FF_DONTCARE, family.data( ), &d3d_font );
	*font = d3d_font;
}

void render::create_font( void** font, const std::string& family, int size, int width ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	ID3DXFont* d3d_font = nullptr;
	D3DXCreateFontA( device, size, 0, width, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 0, DEFAULT_PITCH | FF_DONTCARE, family.data( ), &d3d_font );
	*font = d3d_font;
}

void render::screen_size( int& width, int& height ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	RECT screen_rect;
	GetWindowRect( GetDesktopWindow( ), &screen_rect );

	width = screen_rect.right;
	height = screen_rect.bottom;
}

void render::text_size( void* font, const std::string& text, dim& dimentions ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	RECT rect = RECT( );
	reinterpret_cast< ID3DXFont* >( font )->DrawTextA( nullptr, text.data( ), text.length( ), &rect, DT_CALCRECT, D3DCOLOR_RGBA( 0, 0, 0, 0 ) );
	dimentions = dim { rect.right - rect.left, rect.bottom - rect.top };
}

void render::rectangle( int x, int y, int width, int height, std::uint32_t color ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	vtx_t vert[ 4 ] = {
		{ x - 0.5f, y - 0.5f, 0.0f, 1.0f, color },
		{ x + width - 0.5f, y - 0.5f, 0.0f, 1.0f, color },
		{ x - 0.5f, y + height - 0.5f, 0.0f, 1.0f, color },
		{ x + width - 0.5f, y + height - 0.5f, 0.0f, 1.0f, color }
	};

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetTexture( 0, nullptr );
	device->SetPixelShader( nullptr );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vert, sizeof( vtx_t ) );
}

void render::gradient( int x, int y, int width, int height, std::uint32_t color1, std::uint32_t color2, bool is_horizontal ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	const auto d3d_clr1 = color1;
	const auto d3d_clr2 = color2;
	std::uint32_t c1, c2, c3, c4;

	if ( is_horizontal ) {
		c1 = d3d_clr1;
		c2 = d3d_clr2;
		c3 = d3d_clr1;
		c4 = d3d_clr2;
	}
	else {
		c1 = d3d_clr1;
		c2 = d3d_clr1;
		c3 = d3d_clr2;
		c4 = d3d_clr2;
	}


	vtx_t vert[ 4 ] = {
		{ x - 0.5f, y - 0.5f, 0.0f, 1.0f, c1 },
		{ x + width - 0.5f, y - 0.5f, 0.0f, 1.0f, c2 },
		{ x - 0.5f, y + height - 0.5f, 0.0f, 1.0f, c3 },
		{ x + width - 0.5f, y + height - 0.5f, 0.0f, 1.0f, c4 }
	};

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetTexture( 0, nullptr );
	device->SetPixelShader( nullptr );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vert, sizeof( vtx_t ) );
}

void render::outline( int x, int y, int width, int height, std::uint32_t color ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	rectangle( x, y, width, 1, color );
	rectangle( x, y + height, width, 1, color );
	rectangle( x, y, 1, height, color );
	rectangle( x + width, y, 1, height + 1, color );
}

void render::line( int x, int y, int x2, int y2, std::uint32_t color ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	vtx_t vert[ 2 ] = {
		{ x - 0.5f, y - 0.5f, 0.0f, 1.0f, color },
		{ x2 - 0.5f, y2 - 0.5f, 0.0f, 1.0f, color }
	};

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetTexture( 0, nullptr );
	device->SetPixelShader( nullptr );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->DrawPrimitiveUP( D3DPT_LINELIST, 1, &vert, sizeof( vtx_t ) );
}

void render::text( int x, int y, std::uint32_t color, void* font, const std::string& text ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	RECT rect;
	SetRect( &rect, x, y, x, y );
	reinterpret_cast< ID3DXFont* >( font )->DrawTextA( nullptr, text.data( ), text.length( ), &rect, DT_LEFT | DT_NOCLIP, color );
}

void render::circle( int x, int y, int radius, int segments, std::uint32_t color ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	std::vector< vtx_t > circle( segments + 2 );

	const auto angle = 360.0f * D3DX_PI / 180.0f;

	circle[ 0 ].x = x - 0.5f;
	circle[ 0 ].y = y - 0.5f;
	circle[ 0 ].z = 0;
	circle[ 0 ].rhw = 1;
	circle[ 0 ].color = color;

	for ( auto i = 1; i < segments + 2; i++ ) {
		circle[ i ].x = ( float ) ( x - radius * std::cosf( D3DX_PI * ( ( i - 1 ) / ( segments / 2.0f ) ) ) ) - 0.5f;
		circle[ i ].y = ( float ) ( y - radius * std::sinf( D3DX_PI * ( ( i - 1 ) / ( segments / 2.0f ) ) ) ) - 0.5f;
		circle[ i ].z = 0;
		circle[ i ].rhw = 1;
		circle[ i ].color = color;
	}

	const auto _res = segments + 2;

	for ( auto i = 0; i < _res; i++ ) {
		circle[ i ].x = x + std::cosf( angle ) * ( circle[ i ].x - x ) - std::sinf( angle ) * ( circle[ i ].y - y ) - 0.5f;
		circle[ i ].y = y + std::sinf( angle ) * ( circle[ i ].x - x ) + std::cosf( angle ) * ( circle[ i ].y - y ) - 0.5f;
	}

	IDirect3DVertexBuffer9* vb = nullptr;

	device->CreateVertexBuffer( ( segments + 2 ) * sizeof( vtx_t ), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &vb, nullptr );

	void* verticies;
	vb->Lock( 0, ( segments + 2 ) * sizeof( vtx_t ), ( void** ) &verticies, 0 );
	std::memcpy( verticies, &circle[ 0 ], ( segments + 2 ) * sizeof( vtx_t ) );
	vb->Unlock( );

	device->SetTexture( 0, nullptr );
	device->SetPixelShader( nullptr );
	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetStreamSource( 0, vb, 0, sizeof( vtx_t ) );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, segments );

	if ( vb )
		vb->Release( );
}

void render::texture( unsigned char* data, int x, int y, int width, int height, float scale ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	D3DXVECTOR2 center = D3DXVECTOR2( width / 2, height / 2 );
	D3DXVECTOR2 trans = D3DXVECTOR2( x, y );
	D3DXMATRIX mat;
	D3DXVECTOR2 scaling( scale, scale );

	D3DXMatrixTransformation2D( &mat, nullptr, 0.0f, &scaling, &center, 0.0f, &trans );

	ID3DXSprite* sprite = nullptr;
	D3DXCreateSprite( device, &sprite );

	IDirect3DTexture9* tex = nullptr;
	D3DXCreateTextureFromFileInMemory( device, data, 4 * width * height, &tex );

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	device->SetPixelShader( nullptr );

	sprite->Begin( 0 );
	sprite->SetTransform( &mat );
	sprite->Draw( tex, nullptr, nullptr, nullptr, 0xFFFFFFFF );
	sprite->End( );
	sprite->Release( );
}

void render::clip_rect( int x, int y, int width, int height ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	RECT rect { x - 0.5f, y - 0.5f, x + width - 0.5f, y + height - 0.5f };
	device->SetScissorRect( &rect );
}

bool render::key_pressed( const std::uint32_t key ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return false;
	}

	return GetAsyncKeyState( key );
}

void render::mouse_pos( pos& position ) {
	if ( !initialized ) {
		/* the d3d device changed or was not set */
		return;
	}

	RECT rect;
	GetWindowRect( GetActiveWindow( ), &rect );

	POINT Pos;
	GetCursorPos( &Pos );

	position.x = Pos.x - rect.left;
	position.y = Pos.y - rect.top;
}