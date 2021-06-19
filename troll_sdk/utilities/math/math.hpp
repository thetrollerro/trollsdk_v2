#pragma once
#include "../../sdk/math/vector.hpp"
#include <DirectXMath.h>
#include "../../sdk/math/matrix.hpp"

#define CHECK_VALID( _v ) 0
#define FastSqrt(x)	(sqrt)(x)
#define VALVE_RAND_MAX 0x7fff
#define TICK_INTERVAL			(i::globalvars->interval_per_tick)
constexpr auto M_PI = 3.14159265358;
namespace math {
	float random_float( float min, float max );
	void random_seed( int seed );
	void sin_cos( float rad, float* sine, float* cosine );
	float normalize_yaw( float yaw );
	float normalize_pitch( float pitch );
	vec3_t angle_normalization( vec3_t angle );
	float get_fov( const vec3_t& viewAngle, const vec3_t& aimAngle );
	void angle_matrix( const vec3_t& ang, matrix_t& out );
	void angle_matrix( const vec3_t& ang, const vec3_t& pos, matrix_t& out );
	void concat_transforms( const matrix_t& in1, const matrix_t& in2, matrix_t& out );
	vec3_t vector_rotate( vec3_t& in1, vec3_t& in2 );
	bool intersect_line_with_bb( vec3_t& start, vec3_t& end, vec3_t& min, vec3_t& max );
	float rad2deg( float rad );
	float deg2rad( float deg );
	float grd_to_bog( float grd );
	vec3_t angle_vector( vec3_t angles );
	void angle_vectors( const vec3_t& angles, vec3_t& forward );
	void angle_vectors( const vec3_t& angles, vec3_t& forward, vec3_t& right, vec3_t& up );
	void angle_vectors( const vec3_t& angles, vec3_t* forward = nullptr, vec3_t* right = nullptr, vec3_t* up = nullptr );
	void vector_angles( const vec3_t& forward, vec3_t& up, vec3_t& angles );
	void vector_angles( const vec3_t& vecForward, vec3_t& vecAngles );
	void get_shotgun_spread( int a1, int a2, int a3, float* a4, float* a5 );
	void vector_transform( const vec3_t in1, const matrix_t in2, vec3_t& out );
	vec3_t calc_angle( const vec3_t& vecSource, const vec3_t& vecDestination );
	vec3_t vector_approach( vec3_t target, vec3_t value, float speed );
	float segment_to_segment( const vec3_t s1, const vec3_t s2, const vec3_t k1, const vec3_t k2 );
	void vector_i_transform( const vec3_t& in, const matrix_t& matrix, vec3_t& out );

	__forceinline float dot_product( const vec3_t& a, const vec3_t& b ) {
		return ( a.x * b.x + a.y * b.y + a.z * b.z );
	}
	__forceinline vec3_t cross_product( const vec3_t& a, const vec3_t& b ) {
		return vec3_t( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
	}

	template <class t>
	__forceinline t lerp( float flPercent, t const& A, t const& B ) {
		return A + ( B - A ) * flPercent;
	}

	inline float interpolate( const float from, const float to, const float percent ) {
		return to * percent + from * ( 1.f - percent );
	}

	__forceinline vec3_t interpolate( const vec3_t from, const vec3_t to, const float percent ) {
		return to * percent + from * ( 1.f - percent );
	}

	__forceinline float AngleDiff( float destAngle, float srcAngle ) {
		float value;
		value = fmodf( destAngle - srcAngle, 360.0f );
		if ( destAngle > srcAngle && value >= 180 )
			value -= 360;
		else if ( value <= -180 )
			value += 360;
		return value;
	}

	typedef __declspec( align( 16 ) ) union {
		float f[ 4 ];
		__m128 v;
	} m128;

	inline __m128 sqrt_ps( const __m128 squared ) {
		return _mm_sqrt_ps( squared );
	}
};