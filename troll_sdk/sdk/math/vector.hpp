#pragma once
#include <cmath>
#include <algorithm>
#include <winerror.h>
#define deg(a) a * 57.295779513082

typedef float vec_t;
class vec3_t {
public:
	float x, y, z;

	vec3_t( ) {
		init( );
	}

	vec3_t( float x, float y, float z = 0.0f ) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void init( ) {
		this->x = this->y = this->z = 0.0f;
	}

	void init( float x, float y, float z ) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	bool is_valid( ) {
		return std::isfinite( this->x ) && std::isfinite( this->y ) && std::isfinite( this->z );
	}

	bool is_zero( ) {
		return vec3_t( this->x, this->y, this->z ) == vec3_t( 0.0f, 0.0f, 0.0f );
	}

	void invalidate( ) {
		this->x = this->y = this->z = std::numeric_limits< float >::infinity( );
	}

	void clear( ) {
		this->x = this->y = this->z = 0.0f;
	}

	float& operator[]( int i ) {
		return ( ( float* ) this )[ i ];
	}

	float operator[]( int i ) const {
		return ( ( float* ) this )[ i ];
	}

	void zero( ) {
		this->x = this->y = this->z = 0.0f;
	}

	bool operator==( const vec3_t& src ) const {
		return ( src.x == this->x ) && ( src.y == y ) && ( src.z == z );
	}

	bool operator!=( const vec3_t& src ) const {
		return ( src.x != this->x ) || ( src.y != y ) || ( src.z != z );
	}

	vec3_t& operator+=( const vec3_t& v ) {
		this->x += v.x; this->y += v.y; this->z += v.z;

		return *this;
	}

	vec3_t& operator-=( const vec3_t& v ) {
		this->x -= v.x; this->y -= v.y; this->z -= v.z;

		return *this;
	}

	vec3_t& operator*=( float fl ) {
		this->x *= fl;
		this->y *= fl;
		this->z *= fl;

		return *this;
	}

	vec3_t& operator*=( const vec3_t& v ) {
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;

		return *this;
	}

	vec3_t& operator/=( const vec3_t& v ) {
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;

		return *this;
	}

	vec3_t& operator+=( float fl ) {
		this->x += fl;
		this->y += fl;
		this->z += fl;

		return *this;
	}

	vec3_t& operator/=( float fl ) {
		this->x /= fl;
		this->y /= fl;
		this->z /= fl;

		return *this;
	}

	vec3_t& operator-=( float fl ) {
		this->x -= fl;
		this->y -= fl;
		this->z -= fl;

		return *this;
	}

	void clamp( ) {
		while ( this->x < -89.0f )
			this->x += 89.0f;

		if ( this->x > 89.0f )
			this->x = 89.0f;

		while ( this->y < -180.0f )
			this->y += 360.0f;

		while ( this->y > 180.0f )
			this->y -= 360.0f;

		this->z = 0.0f;
	}

	void normalize_in_place( )
	{
		*this = normalized( );
	}
	float dot( const vec3_t& vOther ) const
	{
		return ( x * vOther.x + y * vOther.y + z * vOther.z );
	}

	float dot( const float* fOther ) const
	{
		const vec3_t& a = *this;

		return( a.x * fOther[ 0 ] + a.y * fOther[ 1 ] + a.z * fOther[ 2 ] );
	}

	vec3_t normalize( )
	{
		vec3_t vector;
		float length = this->length( );

		if ( length != 0 )
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else
		{
			vector.x = vector.y = 0.0f; vector.z = 1.0f;
		}

		return vector;
	}
	vec3_t normalized( ) const
	{
		vec3_t res = *this;
		float l = res.length( );
		if ( l != 0.0f ) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float normalize_place( ) const
	{
		vec3_t v = *this;

		float iradius = 1.f / ( this->length( ) + 1.192092896e-07F ); //FLT_EPSILON

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;

		return v.length( );
	}

	float dist_to( const vec3_t& vec ) const {
		vec3_t delta;

		delta.x = this->x - vec.x;
		delta.y = this->y - vec.y;
		delta.z = this->z - vec.z;

		return delta.length( );
	}

	float dist_to_sqr( const vec3_t& vec ) const {
		vec3_t delta;

		delta.x = this->x - vec.x;
		delta.y = this->y - vec.y;
		delta.z = this->z - vec.z;

		return delta.length_sqr( );
	}

	float dot_product( const vec3_t& vec ) const {
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

	vec3_t cross_product( const vec3_t& vec ) const {
		return vec3_t( this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x );
	}

	float length( ) const {
		return std::sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	}

	float length_sqr( ) const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	float length_2d_sqr( ) const {
		return this->x * this->x + this->y * this->y;
	}

	float length_2d( ) const {
		return std::sqrtf( this->x * this->x + this->y * this->y );
	}

	void vector_cross_product( const vec3_t& a, const vec3_t& b, vec3_t& result )
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}

	vec3_t cross( const vec3_t& vOther )
	{
		vec3_t res;
		vector_cross_product( *this, vOther, res );
		return res;
	}

	vec3_t angle( vec3_t* up = 0 )
	{
		if ( !x && !y )
			return vec3_t( 0, 0, 0 );

		float roll = 0;

		if ( up ) {
			vec3_t left = ( *up ).cross( *this );

			roll = deg( atan2f( left.z, ( left.y * x ) - ( left.x * y ) ) );
		}

		return vec3_t( deg( atan2f( -z, sqrtf( x * x + y * y ) ) ), deg( atan2f( y, x ) ), roll );
	}

	vec3_t& operator=( const vec3_t& vec ) {
		this->x = vec.x; this->y = vec.y; this->z = vec.z;

		return *this;
	}

	vec3_t operator-( ) const {
		return vec3_t( -this->x, -this->y, -this->z );
	}

	vec3_t operator+( const vec3_t& v ) const {
		return vec3_t( this->x + v.x, this->y + v.y, this->z + v.z );
	}

	vec3_t operator-( const vec3_t& v ) const {
		return vec3_t( this->x - v.x, this->y - v.y, this->z - v.z );
	}

	vec3_t operator*( float fl ) const {
		return vec3_t( this->x * fl, this->y * fl, this->z * fl );
	}

	vec3_t operator*( const vec3_t& v ) const {
		return vec3_t( this->x * v.x, this->y * v.y, this->z * v.z );
	}

	vec3_t operator/( float fl ) const {
		return vec3_t( this->x / fl, this->y / fl, this->z / fl );
	}

	vec3_t operator/( const vec3_t& v ) const {
		return vec3_t( this->x / v.x, this->y / v.y, this->z / v.z );
	}
};

__forceinline vec3_t operator*( float lhs, const vec3_t& rhs ) {
	return rhs * lhs;
}

__forceinline vec3_t operator/( float lhs, const vec3_t& rhs ) {
	return rhs / lhs;
}

class vec2_t {
public:
	float x, y;

	vec2_t( ) {
		x = 0; y = 0;
	};
	vec2_t( float X, float Y ) {
		x = X; y = Y;
	};
	vec2_t( vec3_t vec ) {
		x = vec.x; y = vec.y;
	}

	inline vec2_t operator*( const float n ) const {
		return vec2_t( x * n, y * n );
	}
	inline vec2_t operator+( const vec2_t& v ) const {
		return vec2_t( x + v.x, y + v.y );
	}
	inline vec2_t operator-( const vec2_t& v ) const {
		return vec2_t( x - v.x, y - v.y );
	}
	inline void operator+=( const vec2_t& v ) {
		x += v.x;
		y += v.y;
	}
	inline void operator-=( const vec2_t& v ) {
		x -= v.x;
		y -= v.y;
	}

	bool operator==( const vec2_t& v ) const {
		return ( v.x == x && v.y == y );
	}
	bool operator!=( const vec2_t& v ) const {
		return ( v.x != x || v.y != y );
	}

	inline float length( ) {
		return sqrt( ( x * x ) + ( y * y ) );
	}
};