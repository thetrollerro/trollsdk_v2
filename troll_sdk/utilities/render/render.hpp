#pragma once
#include <vector>
#include <cstdint>
#include <string_view>
#include <d3d9.h>
#include <d3dx9.h>
namespace render {

	namespace fonts {
		extern ID3DXFont* def;
		extern ID3DXFont* watermark;
		extern ID3DXFont* esp_def;
		extern ID3DXFont* esp_sec;
		extern ID3DXFont* keystrokes;
	}

	struct vtx_t {
		float x, y, z, rhw;
		std::uint32_t color;
	};

	struct custom_vtx_t {
		float x, y, z, rhw;
		std::uint32_t color;
		float tu, tv;
	};

	struct pos {
		int x, y;
	};

	struct dim {
		int w, h;
	};

	struct rect {
		int x, y, w, h;
	};
	void destroy_fonts( );
	void create_fonts( );
	void create_font( void** font, const std::string& family, int size, bool bold );
	void create_font( void** font, const std::string& family, int size, int width );
	void screen_size( int& width, int& height );
	void text_size( void* font, const std::string& text, dim& dimentions );
	void rectangle( int x, int y, int width, int height, std::uint32_t color );
	void gradient( int x, int y, int width, int height, std::uint32_t color1, std::uint32_t color2, bool is_horizontal );
	void outline( int x, int y, int width, int height, std::uint32_t color );
	void line( int x, int y, int x2, int y2, std::uint32_t color );
	void text( int x, int y, std::uint32_t color, void* font, const std::string& text );
	void circle( int x, int y, int radius, int segments, std::uint32_t color );
	void texture( unsigned char* data, int x, int y, int width, int height, float scale );
	void clip_rect( int x, int y, int width, int height );
	bool key_pressed( const std::uint32_t key );
	void mouse_pos( pos& position );
}