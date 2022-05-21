#pragma once
#include "../../../utilities/utilities.hpp"

class c_convar {
public:
	__forceinline float get_float( void ) {
		int xord = ( int ) ( *( int* ) ( &f_value ) ^ ( uintptr_t ) this );
		return *( float* ) &xord;
	}

	__forceinline int get_int( void ) {
		int xord = ( int ) ( *( int* ) ( &n_value ) ^ ( uintptr_t ) this );
		return *( int* ) &xord;
	}

	bool get_bool( void ) {
		return !!get_int( );
	}

	void set_value( const char* value ) {
		using set_value_fn = void( __thiscall* )( void*, const char* );
		utils::call_virtual<set_value_fn>( this, 14 )( this, value );
	}

	void set_value( float value ) {
		using set_value_fn = void( __thiscall* )( void*, float );
		utils::call_virtual<set_value_fn>( this, 15 )( this, value );
	}

	void set_value( int value ) {
		using set_value_fn = void( __thiscall* )( void*, int );
		utils::call_virtual<set_value_fn>( this, 16 )( this, value );
	}

	/*void set_value( color value ) {
		return ( ( void( __thiscall* )( void*, color ) ) get_vfunc( this, 17 ) )( this, value );
	}*/

	void null_callback( void ) {
		*( int* ) ( ( uintptr_t ) &change_callback_fn + 0xC ) = 0;
	}

	unsigned char pad_0x0[ 0x4 ];
	c_convar* next;
	int registered;
	char* name;
	char* help_string;
	int flags;
	unsigned char pad_0x18[ 0x4 ];
	c_convar* parent;
	char* default_value;
	char* string;
	int string_len;
	float f_value;
	int n_value;
	int has_min;
	float min_val;
	int has_max;
	float max_val;
	void* change_callback_fn;
};

#pragma region COLORS_FOR_CONSOLE_PRINT
struct c_console_color
{
	unsigned char r, g, b, a;
};

class c_color {
public:
	unsigned char RGBA[ 4 ];

	c_color( )
	{
		RGBA[ 0 ] = 255;
		RGBA[ 1 ] = 255;
		RGBA[ 2 ] = 255;
		RGBA[ 3 ] = 255;
	}

	c_color( int r, int g, int b, int a = 255 )
	{
		RGBA[ 0 ] = r;
		RGBA[ 1 ] = g;
		RGBA[ 2 ] = b;
		RGBA[ 3 ] = a;
	}

	inline int r( ) const
	{
		return RGBA[ 0 ];
	}

	inline int g( ) const
	{
		return RGBA[ 1 ];
	}

	inline int b( ) const
	{
		return RGBA[ 2 ];
	}

	inline int a( ) const
	{
		return RGBA[ 3 ];
	}

	bool operator!=( c_color color )
	{
		return RGBA[ 0 ] != color.RGBA[ 0 ] || RGBA[ 1 ] != color.RGBA[ 1 ] || RGBA[ 2 ] != color.RGBA[ 2 ] || RGBA[ 3 ] != color.RGBA[ 3 ];
	}

	bool operator==( c_color color )
	{
		return RGBA[ 0 ] == color.RGBA[ 0 ] && RGBA[ 1 ] == color.RGBA[ 1 ] && RGBA[ 2 ] == color.RGBA[ 2 ] && RGBA[ 3 ] == color.RGBA[ 3 ];
	}

	static float base( const unsigned char col )
	{
		return col / 255.f;
	}
};
#pragma endregion

class color;
class i_cvar {
public:
	c_convar* find_var( const char* convar_name ) {
		using find_var_fn = c_convar * ( __thiscall* )( void*, const char* );
		return utils::call_virtual<find_var_fn>( this, 16 )( this, convar_name );
	}

	template <typename... args>
	void console_color_printf( const c_color& color, const char* format, args... arg ) {
		const c_console_color cl = { static_cast< unsigned char >( color.r( ) ), static_cast< unsigned char >( color.g( ) ),
			static_cast< unsigned char >( color.b( ) ), static_cast< unsigned char >( color.a( ) ) };

		reinterpret_cast< void( * )( void*, const c_console_color&, const char*, ... ) >(
			( *reinterpret_cast< uint32_t** >( this ) )[ 25 ] )( this, cl, format, arg... );
	}
};
