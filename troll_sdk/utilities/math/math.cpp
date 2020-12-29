#include "math.hpp"
#include "../../main.hpp"

void math::angle_matrix( const vec3_t& ang, matrix_t& out )
{
	float sr, sp, sy, cr, cp, cy;

	sp = std::sin( math::deg2rad( ang[ 0 ] ) );
	cp = std::cos( math::deg2rad( ang[ 0 ] ) );

	sy = std::sin( math::deg2rad( ang[ 1 ] ) );
	cy = std::cos( math::deg2rad( ang[ 1 ] ) );

	sr = std::sin( math::deg2rad( ang[ 2 ] ) );
	cr = std::cos( math::deg2rad( ang[ 2 ] ) );

	// matrix = (YAW * PITCH) * ROLL
	out[ 0 ][ 0 ] = cp * cy;
	out[ 1 ][ 0 ] = cp * sy;
	out[ 2 ][ 0 ] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;
	out[ 0 ][ 1 ] = sp * srcy - crsy;
	out[ 1 ][ 1 ] = sp * srsy + crcy;
	out[ 2 ][ 1 ] = sr * cp;

	out[ 0 ][ 2 ] = ( sp * crcy + srsy );
	out[ 1 ][ 2 ] = ( sp * crsy - srcy );
	out[ 2 ][ 2 ] = cr * cp;

	out[ 0 ][ 3 ] = 0.0f;
	out[ 1 ][ 3 ] = 0.0f;
	out[ 2 ][ 3 ] = 0.0f;
}

void math::angle_matrix( const vec3_t& ang, const vec3_t& pos, matrix_t& out ) {
	//	g_csgo.AngleMatrix( ang , out );
	angle_matrix( ang, out );

	out.set_origin( pos );
}

void math::sin_cos( float rad, float* sine, float* cosine )
{
	*sine = std::sinf( rad );
	*cosine = std::cosf( rad );
}

float math::normalize_yaw( float yaw )
{
	while ( yaw > 180 )
		yaw -= 360.f;

	while ( yaw < -180 )
		yaw += 360.f;

	return yaw;
}

vec3_t math::angle_normalization( vec3_t angle ) {
	while ( angle.x > 89.f ) {
		angle.x -= 180.f;
	}
	while ( angle.x < -89.f ) {
		angle.x += 180.f;
	}
	if ( angle.y > 180 ) {
		angle.y -= ( round( angle.y / 360 ) * 360.f );
	}
	else if ( angle.y < -180 ) {
		angle.y += ( round( angle.y / 360 ) * -360.f );
	}
	if ( ( angle.z > 50 ) || ( angle.z < 50 ) ) {
		angle.z = 0;
	}
	return angle;
}

void math::clamp_angles( vec3_t& ang )
{
	if ( ang.x > 89.0f )
		ang.x = 89.0f;
	else if ( ang.x < -89.0f )
		ang.x = -89.0f;

	if ( ang.y > 180.0f )
		ang.y = 180.0f;
	else if ( ang.y < -180.0f )
		ang.y = -180.0f;

	ang.z = 0;
}

float math::get_fov( const vec3_t& viewAngle, const vec3_t& aimAngle )
{
	vec3_t ang, aim;

	angle_vectors( viewAngle, aim );
	angle_vectors( aimAngle, ang );

	return RAD2DEG( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
}

bool math::sanitize_angles( vec3_t& angles )
{
	angles.x = fmaxf( fminf( angles.x, 89.f ), -89.f );
	while ( angles.y > 180.f ) angles.y -= 360.f;
	while ( angles.y < -180.f ) angles.y += 360.f;
	angles.z = 0.f;

	if ( !isfinite( angles.x ) || !isfinite( angles.y ) || !isfinite( angles.z ) ) {
		return false;
	}

	if ( angles.x > 89.f || angles.x < -89.f || angles.y > 180.f || angles.y < -180.f || angles.z != 0.f ) {
		return false;
	}

	return true;
}

void math::normalize_angles( vec3_t& angles )
{
	for ( auto i = 0; i < 3; i++ ) {
		while ( angles[ i ] < -180.0f ) angles[ i ] += 360.0f;
		while ( angles[ i ] > 180.0f ) angles[ i ] -= 360.0f;
	}
}

float math::vector_normalize( vec3_t& v )
{
	assert( v.is_valid( ) );
	float l = v.length( );
	if ( l != 0.0f )
	{
		v /= l;
	}
	else
	{
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}

float math::rad2deg( float rad ) {
	float result = rad * ( 180.0f / M_PI );
	return result;
}

float math::deg2rad( float deg ) {
	float result = deg * ( M_PI / 180.0f );
	return result;
}

float math::grd_to_bog( float grd ) {
	return ( M_PI / 180 ) * grd;
}

vec3_t math::angle_vector( vec3_t angles ) {
	auto sy = sin( angles.y / 180.f * static_cast< float >( M_PI ) );
	auto cy = cos( angles.y / 180.f * static_cast< float >( M_PI ) );

	auto sp = sin( angles.x / 180.f * static_cast< float >( M_PI ) );
	auto cp = cos( angles.x / 180.f * static_cast< float >( M_PI ) );

	return vec3_t( cp * cy, cp * sy, -sp );
}


void math::angle_vectors( const vec3_t& angles, vec3_t& forward )
{
	float sp, sy, cp, cy;

	sin_cos( deg2rad( angles[ 1 ] ), &sy, &cy );
	sin_cos( deg2rad( angles[ 0 ] ), &sp, &cp );

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

float math::random_float( float min, float max )
{
	static auto random_float = reinterpret_cast< float( * )( float, float ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomFloat" ) );

	return random_float( min, max );
}

int math::random_int( int min, int max ) {
	static auto random_int = reinterpret_cast< int( * )( int, int ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomInt" ) );
	return random_int( min, max );
}

float math::fast_sqrt( float x ) {
	unsigned int i = *( unsigned int* ) &x;
	i += 127 << 23;
	i >>= 1;
	return *( float* ) &i;
}

void math::vector_transform( const vec3_t in1, const matrix_t in2, vec3_t& out ) {
	out[ 0 ] = dot_product( in1, vec3_t( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out[ 1 ] = dot_product( in1, vec3_t( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out[ 2 ] = dot_product( in1, vec3_t( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}

float math::vector_length( const vec3_t& v )
{
	CHECK_VALID( v );
	return ( float ) FastSqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

void math::vector_angles( const vec3_t& forward, vec3_t& up, vec3_t& angles ) {
	vec3_t left = cross_product( up, forward );
	left.normalize_in_place( );

	float forwardDist = forward.length_2d( );

	if ( forwardDist > 0.001f ) {
		angles.x = atan2f( -forward.z, forwardDist ) * 180 / M_PI;
		angles.y = atan2f( forward.y, forward.x ) * 180 / M_PI;

		float upZ = ( left.y * forward.x ) - ( left.x * forward.y );
		angles.z = atan2f( left.z, upZ ) * 180 / M_PI;
	}
	else {
		angles.x = atan2f( -forward.z, forwardDist ) * 180 / M_PI;
		angles.y = atan2f( -left.x, left.y ) * 180 / M_PI;
		angles.z = 0;
	}
}

void math::angle_vectors( const vec3_t& angles, vec3_t& forward, vec3_t& right, vec3_t& up )
{
	float sr, sp, sy, cr, cp, cy;

	sin_cos( deg2rad( angles[ 1 ] ), &sy, &cy );
	sin_cos( deg2rad( angles[ 0 ] ), &sp, &cp );
	sin_cos( deg2rad( angles[ 2 ] ), &sr, &cr );

	forward.x = ( cp * cy );
	forward.y = ( cp * sy );
	forward.z = ( -sp );
	right.x = ( -1 * sr * sp * cy + -1 * cr * -sy );
	right.y = ( -1 * sr * sp * sy + -1 * cr * cy );
	right.z = ( -1 * sr * cp );
	up.x = ( cr * sp * cy + -sr * -sy );
	up.y = ( cr * sp * sy + -sr * cy );
	up.z = ( cr * cp );
}
vec3_t math::calc_angle( const vec3_t& vecSource, const vec3_t& vecDestination )
{
	vec3_t qAngles;
	vec3_t delta = vec3_t( ( vecSource[ 0 ] - vecDestination[ 0 ] ), ( vecSource[ 1 ] - vecDestination[ 1 ] ), ( vecSource[ 2 ] - vecDestination[ 2 ] ) );
	float hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
	qAngles[ 0 ] = ( float ) ( atan( delta[ 2 ] / hyp ) * ( 180.0f / M_PI ) );
	qAngles[ 1 ] = ( float ) ( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0f / M_PI ) );
	qAngles[ 2 ] = 0.f;
	if ( delta[ 0 ] >= 0.f )
		qAngles[ 1 ] += 180.f;

	return qAngles;
}

void math::vector_angles( const vec3_t& vecForward, vec3_t& vecAngles )
{
	vec3_t vecView;
	if ( vecForward[ 1 ] == 0.f && vecForward[ 0 ] == 0.f )
	{
		vecView[ 0 ] = 0.f;
		vecView[ 1 ] = 0.f;
	}
	else
	{
		vecView[ 1 ] = atan2( vecForward[ 1 ], vecForward[ 0 ] ) * 180.f / 3.14159265358979323846f;

		if ( vecView[ 1 ] < 0.f )
			vecView[ 1 ] += 360.f;

		vecView[ 2 ] = sqrt( vecForward[ 0 ] * vecForward[ 0 ] + vecForward[ 1 ] * vecForward[ 1 ] );

		vecView[ 0 ] = atan2( vecForward[ 2 ], vecView[ 2 ] ) * 180.f / 3.14159265358979323846f;
	}

	vecAngles[ 0 ] = -vecView[ 0 ];
	vecAngles[ 1 ] = vecView[ 1 ];
	vecAngles[ 2 ] = 0.f;
}

float math::distance( vec2_t point1, vec2_t point2 )
{
	float diffY = point1.y - point2.y;
	float diffX = point1.x - point2.x;
	return sqrt( ( diffY * diffY ) + ( diffX * diffX ) );
}

float math::GRD_TO_BOG( float GRD ) {
	return ( M_PI / 180 ) * GRD;
}


void math::angle_vectors( const vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up )
{
	float sp, sy, sr, cp, cy, cr;

	sin_cos( grd_to_bog( angles.x ), &sp, &cp );
	sin_cos( grd_to_bog( angles.y ), &sy, &cy );
	sin_cos( grd_to_bog( angles.z ), &sr, &cr );

	if ( forward != nullptr )
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if ( right != nullptr )
	{
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if ( up != nullptr )
	{
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

vec3_t math::calc_angle_vec( const vec3_t& src, const vec3_t& dst )
{
	vec3_t ret;
	vector_angles( dst - src, ret );
	return ret;
}

vec3_t math::vector_approach( vec3_t target, vec3_t value, float speed )
{
	vec3_t diff = ( target - value );
	float delta = diff.length( );

	if ( delta > speed )
		value += diff.normalized( ) * speed;
	else if ( delta < -speed )
		value -= diff.normalized( ) * speed;
	else
		value = target;

	return value;
}
