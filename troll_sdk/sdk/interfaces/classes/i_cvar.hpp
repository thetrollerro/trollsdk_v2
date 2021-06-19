#pragma once

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

class color;
class i_cvar {
public:
	c_convar* find_var( const char* convar_name ) {
		using find_var_fn = c_convar * ( __thiscall* )( void*, const char* );
		return utils::call_virtual<find_var_fn>( this, 16 )( this, convar_name );
	}

	template< typename... arguments >
	void console_color_print_f( const uint32_t& _color, const char* format, arguments ... args ) {
		using o_fn = void( __cdecl* )( void*, const uint32_t&, const char* ... );
		return utils::call_virtual<o_fn>( this, 25 )( this, _color, format, args... );
	}
};