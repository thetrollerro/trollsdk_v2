#pragma once
#include <vector>
#include <cstdint>
#include <string_view>
#include <d3d9.h>
#include <d3dx9.h>
namespace render {
	void start( IDirect3DDevice9* dev );

	namespace fonts {
		extern ID3DXFont* def;
		extern ID3DXFont* watermark;
		extern ID3DXFont* esp_def;
		extern ID3DXFont* esp_sec;
		extern ID3DXFont* keystrokes;
	}

	inline struct vtx_t {
		float x, y, z, rhw;
		std::uint32_t color;
	}vtx_t_;

	inline struct custom_vtx_t {
		float x, y, z, rhw;
		std::uint32_t color;
		float tu, tv;
	}custom_vtx_t_;

	inline struct pos {
		int x, y;
	}pos_;

	inline struct dim {
		int w, h;
	}dim_;

	inline struct rect {
		int x, y, w, h;

		bool operator==( const rect& v ) {
			return ( this->x == v.x
				&& this->y == v.y
				&& this->w == v.w
				&& this->h == v.h );
		}

		bool operator!=( const rect& v ) {
			return ( this->x != v.x
				|| this->y != v.y
				|| this->w != v.w
				|| this->h != v.h );
		}
	}rect_;

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
	void circle( int x, int y, int radius, std::uint32_t color );
	void empty_circle( int x, int y, int radius, std::uint32_t color );
	void texture( unsigned char* data, int x, int y, int width, int height, float scale );
	void clip_rect( int x, int y, int width, int height );
	bool key_pressed( const std::uint32_t key );
	void mouse_pos( pos& position );

	inline IDirect3DDevice9* device;
	inline bool initialized = false;
}