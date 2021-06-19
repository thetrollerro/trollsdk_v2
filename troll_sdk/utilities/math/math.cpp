#include "math.hpp"
#include "../../main.hpp"

namespace math {

	void angle_matrix( const vec3_t& ang, matrix_t& out ) {
		float sr, sp, sy, cr, cp, cy;

		sin_cos( deg2rad( ang.y ), &sy, &cy );
		sin_cos( deg2rad( ang.x ), &sp, &cp );
		sin_cos( deg2rad( ang.z ), &sr, &cr );

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

	void MatrixCopy( const matrix_t& in, matrix_t& out ) {
		std::memcpy( out.base( ), in.base( ), sizeof( matrix_t ) );
	}

	void concat_transforms( const matrix_t& in1, const matrix_t& in2, matrix_t& out ) {
		if ( &in1 == &out ) {
			matrix_t in1b;
			MatrixCopy( in1, in1b );
			concat_transforms( in1b, in2, out );
			return;
		}

		if ( &in2 == &out ) {
			matrix_t in2b;
			MatrixCopy( in2, in2b );
			concat_transforms( in1, in2b, out );
			return;
		}

		out[ 0 ][ 0 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 0 ];
		out[ 0 ][ 1 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 1 ];
		out[ 0 ][ 2 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 2 ];
		out[ 0 ][ 3 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 0 ][ 3 ];

		out[ 1 ][ 0 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 0 ];
		out[ 1 ][ 1 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 1 ];
		out[ 1 ][ 2 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 2 ];
		out[ 1 ][ 3 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 1 ][ 3 ];

		out[ 2 ][ 0 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 0 ];
		out[ 2 ][ 1 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 1 ];
		out[ 2 ][ 2 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 2 ];
		out[ 2 ][ 3 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 2 ][ 3 ];
	}

	static vec3_t vector_rotate( vec3_t& in1, matrix_t& in2 ) {
		return vec3_t( in1.dot( in2[ 0 ] ), in1.dot( in2[ 1 ] ), in1.dot( in2[ 2 ] ) );
	}

	vec3_t vector_rotate( vec3_t& in1, vec3_t& in2 ) {
		matrix_t m;
		angle_matrix( in2, m );
		return vector_rotate( in1, m );
	}

	void angle_matrix( const vec3_t& ang, const vec3_t& pos, matrix_t& out ) {
		angle_matrix( ang, out );
		out.set_origin( pos );
	}

	void sin_cos( float rad, float* sine, float* cosine ) {
		*sine = std::sinf( rad );
		*cosine = std::cosf( rad );
	}

	float normalize_yaw( float yaw ) {
		while ( yaw > 180 )
			yaw -= 360.f;

		while ( yaw < -180 )
			yaw += 360.f;

		return yaw;
	}

	float normalize_pitch( float pitch ) {
		while ( pitch > 89.0f )
			pitch -= 180.0f;

		while ( pitch < -89.0f )
			pitch += 180.0f;

		return pitch;
	}

	vec3_t angle_normalization( vec3_t angle ) {
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

	bool intersect_line_with_bb( vec3_t& start, vec3_t& end, vec3_t& min, vec3_t& max ) {
		float d1, d2, f;
		auto start_solid = true;
		auto t1 = -1.0f, t2 = 1.0f;

		const float s[ 3 ] = { start.x, start.y, start.z };
		const float e[ 3 ] = { end.x, end.y, end.z };
		const float mi[ 3 ] = { min.x, min.y, min.z };
		const float ma[ 3 ] = { max.x, max.y, max.z };

		for ( auto i = 0; i < 6; i++ ) {
			if ( i >= 3 ) {
				const auto j = i - 3;

				d1 = s[ j ] - ma[ j ];
				d2 = d1 + e[ j ];
			}
			else {
				d1 = -s[ i ] + mi[ i ];
				d2 = d1 - e[ i ];
			}

			if ( d1 > 0.0f && d2 > 0.0f )
				return false;

			if ( d1 <= 0.0f && d2 <= 0.0f )
				continue;

			if ( d1 > 0 )
				start_solid = false;

			if ( d1 > d2 ) {
				f = d1;
				if ( f < 0.0f )
					f = 0.0f;

				f /= d1 - d2;
				if ( f > t1 )
					t1 = f;
			}
			else {
				f = d1 / ( d1 - d2 );
				if ( f < t2 )
					t2 = f;
			}
		}

		return start_solid || ( t1 < t2&& t1 >= 0.0f );
	}

	float get_fov( const vec3_t& viewAngle, const vec3_t& aimAngle ) {
		vec3_t ang, aim;

		angle_vectors( viewAngle, aim );
		angle_vectors( aimAngle, ang );

		return math::rad2deg( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
	}

	void random_seed( int seed ) {
		static auto fn = ( decltype( &random_seed ) ) ( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomSeed" ) );
		return fn( seed );
	}

	void get_shotgun_spread( int a1, int a2, int a3, float* a4, float* a5 ) {
		using GetShotgunSpread_t = void( __stdcall* )( int, int, int, float*, float* );
		static auto fn = ( GetShotgunSpread_t ) utils::find_sig_ida( "client.dll", "55 8B EC 83 EC 10 56 8B 75 08 8D 45 F4 50 B9 ? ? ? ?" );
		return fn( a1, a2, a3, a4, a5 );
	}

	float rad2deg( float rad ) {
		float result = rad * ( 180.0f / M_PI );
		return result;
	}

	float deg2rad( float deg ) {
		float result = deg * ( M_PI / 180.0f );
		return result;
	}

	float grd_to_bog( float grd ) {
		return ( M_PI / 180 ) * grd;
	}

	vec3_t angle_vector( vec3_t angles ) {
		auto sy = sin( angles.y / 180.f * static_cast< float >( M_PI ) );
		auto cy = cos( angles.y / 180.f * static_cast< float >( M_PI ) );

		auto sp = sin( angles.x / 180.f * static_cast< float >( M_PI ) );
		auto cp = cos( angles.x / 180.f * static_cast< float >( M_PI ) );

		return vec3_t( cp * cy, cp * sy, -sp );
	}

	void angle_vectors( const vec3_t& angles, vec3_t& forward ) {
		float sp, sy, cp, cy;

		sin_cos( deg2rad( angles[ 1 ] ), &sy, &cy );
		sin_cos( deg2rad( angles[ 0 ] ), &sp, &cp );

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	float random_float( float min, float max ) {
		static auto random_float = reinterpret_cast< float( * )( float, float ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomFloat" ) );
		return random_float( min, max );
	}

	void vector_transform( const vec3_t in1, const matrix_t in2, vec3_t& out ) {
		out[ 0 ] = math::dot_product( in1, vec3_t( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
		out[ 1 ] = math::dot_product( in1, vec3_t( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
		out[ 2 ] = math::dot_product( in1, vec3_t( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
	}

	void angle_vectors( const vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up ) {
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

	void angle_vectors( const vec3_t& angles, vec3_t& forward, vec3_t& right, vec3_t& up ) {
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

	void vector_angles( const vec3_t& vecForward, vec3_t& vecAngles ) {
		vec3_t vecView;
		if ( vecForward[ 1 ] == 0.f && vecForward[ 0 ] == 0.f )
		{
			vecView[ 0 ] = 0.f;
			vecView[ 1 ] = 0.f;
		}
		else
		{
			vecView[ 1 ] = atan2( vecForward[ 1 ], vecForward[ 0 ] ) * 180.f / M_PI;

			if ( vecView[ 1 ] < 0.f )
				vecView[ 1 ] += 360.f;

			vecView[ 2 ] = sqrt( vecForward[ 0 ] * vecForward[ 0 ] + vecForward[ 1 ] * vecForward[ 1 ] );

			vecView[ 0 ] = atan2( vecForward[ 2 ], vecView[ 2 ] ) * 180.f / M_PI;
		}

		vecAngles[ 0 ] = -vecView[ 0 ];
		vecAngles[ 1 ] = vecView[ 1 ];
		vecAngles[ 2 ] = 0.f;
	}

	void vector_angles( const vec3_t& forward, vec3_t& up, vec3_t& angles ) {
		vec3_t left = math::cross_product( up, forward );
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

	vec3_t calc_angle( const vec3_t& vecSource, const vec3_t& vecDestination ) {
		vec3_t angles;
		vec3_t delta = vec3_t( ( vecSource[ 0 ] - vecDestination[ 0 ] ), ( vecSource[ 1 ] - vecDestination[ 1 ] ), ( vecSource[ 2 ] - vecDestination[ 2 ] ) );
		float hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
		angles[ 0 ] = ( float ) ( atan( delta[ 2 ] / hyp ) * ( 180.0f / M_PI ) );
		angles[ 1 ] = ( float ) ( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0f / M_PI ) );
		angles[ 2 ] = 0.f;
		if ( delta[ 0 ] >= 0.f )
			angles[ 1 ] += 180.f;

		return angles;
	}

	vec3_t vector_approach( vec3_t target, vec3_t value, float speed ) {
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

	float segment_to_segment( const vec3_t s1, const vec3_t s2, const vec3_t k1, const vec3_t k2 ) {
		static auto constexpr epsilon = 0.00000001;

		auto u = s2 - s1;
		auto v = k2 - k1;
		const auto w = s1 - k1;

		const auto a = u.dot( u );
		const auto b = u.dot( v );
		const auto c = v.dot( v );
		const auto d = u.dot( w );
		const auto e = v.dot( w );
		const auto D = a * c - b * b;
		float sn, sd = D;
		float tn, td = D;

		if ( D < epsilon ) {
			sn = 0.0;
			sd = 1.0;
			tn = e;
			td = c;
		}
		else {
			sn = b * e - c * d;
			tn = a * e - b * d;

			if ( sn < 0.0 ) {
				sn = 0.0;
				tn = e;
				td = c;
			}
			else if ( sn > sd ) {
				sn = sd;
				tn = e + b;
				td = c;
			}
		}

		if ( tn < 0.0 ) {
			tn = 0.0;

			if ( -d < 0.0 )
				sn = 0.0;
			else if ( -d > a )
				sn = sd;
			else {
				sn = -d;
				sd = a;
			}
		}
		else if ( tn > td ) {
			tn = td;

			if ( -d + b < 0.0 )
				sn = 0;
			else if ( -d + b > a )
				sn = sd;
			else {
				sn = -d + b;
				sd = a;
			}
		}

		const float sc = abs( sn ) < epsilon ? 0.0 : sn / sd;
		const float tc = abs( tn ) < epsilon ? 0.0 : tn / td;

		m128 n;
		auto dp = w + u * sc - v * tc;
		n.f[ 0 ] = dp.dot( dp );
		const auto calc = sqrt_ps( n.v );
		return reinterpret_cast< const m128* >( &calc )->f[ 0 ];

	}

	void vector_i_transform( const vec3_t& in, const matrix_t& matrix, vec3_t& out ) {
		vec3_t diff;

		diff = {
			in.x - matrix[ 0 ][ 3 ],
			in.y - matrix[ 1 ][ 3 ],
			in.z - matrix[ 2 ][ 3 ]
		};

		out = {
			diff.x * matrix[ 0 ][ 0 ] + diff.y * matrix[ 1 ][ 0 ] + diff.z * matrix[ 2 ][ 0 ],
			diff.x * matrix[ 0 ][ 1 ] + diff.y * matrix[ 1 ][ 1 ] + diff.z * matrix[ 2 ][ 1 ],
			diff.x * matrix[ 0 ][ 2 ] + diff.y * matrix[ 1 ][ 2 ] + diff.z * matrix[ 2 ][ 2 ]
		};
	}

}