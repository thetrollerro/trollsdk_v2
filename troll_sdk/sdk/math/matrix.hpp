#pragma once

#include <sstream>
#include "vector.hpp"

#define float32_nan_bits     ( std::uint32_t ) 0x7fc00000	// not a number!
#define float32_nan          bits_to_float( float32_nan_bits )
#define vec_t_nan float32_nan
#define assert( _exp ) ( (void ) 0 )

inline float bits_to_float( std::uint32_t i ) {
	struct convertor_t
	{
		float f;
		unsigned long ul;
	}tmp;

	tmp.ul = i;
	return tmp.f;
}

struct matrix_t {
	matrix_t( ) { }
	matrix_t( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23 )
	{
		mat_val[ 0 ][ 0 ] = m00;	mat_val[ 0 ][ 1 ] = m01; mat_val[ 0 ][ 2 ] = m02; mat_val[ 0 ][ 3 ] = m03;
		mat_val[ 1 ][ 0 ] = m10;	mat_val[ 1 ][ 1 ] = m11; mat_val[ 1 ][ 2 ] = m12; mat_val[ 1 ][ 3 ] = m13;
		mat_val[ 2 ][ 0 ] = m20;	mat_val[ 2 ][ 1 ] = m21; mat_val[ 2 ][ 2 ] = m22; mat_val[ 2 ][ 3 ] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void init( const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t& vecOrigin ) {
		mat_val[ 0 ][ 0 ] = xAxis.x; mat_val[ 0 ][ 1 ] = yAxis.x; mat_val[ 0 ][ 2 ] = zAxis.x; mat_val[ 0 ][ 3 ] = vecOrigin.x;
		mat_val[ 1 ][ 0 ] = xAxis.y; mat_val[ 1 ][ 1 ] = yAxis.y; mat_val[ 1 ][ 2 ] = zAxis.y; mat_val[ 1 ][ 3 ] = vecOrigin.y;
		mat_val[ 2 ][ 0 ] = xAxis.z; mat_val[ 2 ][ 1 ] = yAxis.z; mat_val[ 2 ][ 2 ] = zAxis.z; mat_val[ 2 ][ 3 ] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix_t( const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t& vecOrigin ) {
		init( xAxis, yAxis, zAxis, vecOrigin );
	}

	inline vec3_t get_origin( )
	{
		return vec3_t( mat_val[ 0 ][ 3 ], mat_val[ 1 ][ 3 ], mat_val[ 2 ][ 3 ] );
	}

	inline void set_origin( vec3_t const& p ) {
		mat_val[ 0 ][ 3 ] = p.x;
		mat_val[ 1 ][ 3 ] = p.y;
		mat_val[ 2 ][ 3 ] = p.z;
	}

	vec3_t get_x_axis( ) const { return at( 0 ); }
	vec3_t get_y_axis( ) const { return at( 1 ); }
	vec3_t get_z_axis( ) const { return at( 2 ); }
	vec3_t get_origin( ) const { return at( 3 ); }

	vec3_t at( int i ) const {
		return vec3_t { mat_val[ 0 ][ i ], mat_val[ 1 ][ i ], mat_val[ 2 ][ i ] };
	}

	inline void invalidate( void ) {
		for ( int i = 0; i < 3; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				mat_val[ i ][ j ] = vec_t_nan;
			}
		}
	}

	float* operator[]( int i ) { assert( ( i >= 0 ) && ( i < 3 ) ); return mat_val[ i ]; }
	const float* operator[]( int i ) const { assert( ( i >= 0 ) && ( i < 3 ) ); return mat_val[ i ]; }
	float* base( ) { return &mat_val[ 0 ][ 0 ]; }
	const float* base( ) const { return &mat_val[ 0 ][ 0 ]; }

	float mat_val[ 3 ][ 4 ];
};