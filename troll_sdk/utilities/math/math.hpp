#pragma once
#include "../../sdk/math/vector.hpp"
#include <DirectXMath.h>
#include "../../sdk/math/matrix.hpp"

#define CHECK_VALID( _v ) 0
#define FastSqrt(x)	(sqrt)(x)
#define VALVE_RAND_MAX 0x7fff
#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)
#define TICK_INTERVAL			(i::globalvars->interval_per_tick)
constexpr auto M_PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912;
#define PI_F	((float)(M_PI)) 
namespace math {
	void sin_cos( float rad, float* sine, float* cosine );
	float normalize_yaw( float yaw );
	vec3_t angle_normalization( vec3_t angle );
	void clamp_angles( vec3_t& ang );
	float get_fov( const vec3_t& viewAngle, const vec3_t& aimAngle );
	void normalize_angles( vec3_t& angles );
	float rad2deg( float rad );
	float deg2rad( float deg );
	float grd_to_bog( float grd );
	vec3_t ang_vectors( vec3_t& angles );
	void angle_vectors( const vec3_t& angles, vec3_t& forward );
	float random_float( float min, float max );
	int random_int( int min, int max );
	float fast_sqrt( float x );
	void vector_transform( const vec3_t in1, const matrix_t in2, vec3_t& out );
	float vector_length( const vec3_t& v );
	bool sanitize_angles( vec3_t& angles );
	void vector_angles( const vec3_t& forward, vec3_t& up, vec3_t& angles );
	void angle_vectors( const vec3_t& angles, vec3_t& forward, vec3_t& right, vec3_t& up );
	vec3_t calc_angle( const vec3_t& vecSource, const vec3_t& vecDestination );
	float distance( vec2_t point1, vec2_t point2 );
	float GRD_TO_BOG( float GRD );
	void angle_vectors( const vec3_t& angles, vec3_t* forward = nullptr, vec3_t* right = nullptr, vec3_t* up = nullptr );
	void vector_angles( const vec3_t& vecForward, vec3_t& vecAngles );
	float vector_normalize( vec3_t& v );
	vec3_t calc_angle_vec( const vec3_t& src, const vec3_t& dst );
	vec3_t vector_approach( vec3_t target, vec3_t value, float speed );
};