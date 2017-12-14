#include "math.h"

math_t valve;

void __forceinline sin_cos( float r, float *s, float *c )
{
    *s = sin( r ); *c = cos( r );
}

void math_t::transform_vector( vec3_t& a, matrix_t& b, vec3_t& out )
{
    auto dot_product = [ & ] ( vec3_t& v, matrix_t& m, int i )
    {
        return( v.x * m [ i ] [ 0 ] + v.y * m [ i ] [ 1 ] + v.z * m [ i ] [ 2 ] );
    };

    out.x = dot_product( a, b, 0 ) + b [ 0 ] [ 3 ];
    out.y = dot_product( a, b, 1 ) + b [ 1 ] [ 3 ];
    out.z = dot_product( a, b, 2 ) + b [ 2 ] [ 3 ];
}

void math_t::vector_angles( vec3_t& forward, vec3_t& angles )
{
    if ( forward.y == 0.0f && forward.x == 0.0f )
    {
        angles.x = ( forward.z > 0.0f ) ? 270.0f : 90.0f; // Pitch (up/down)
        angles.y = 0.0f; //yaw left/right
    }
    else
    {
        angles.x = atan2( -forward.z, vec2_t( forward ).length( ) ) * -180 / pi( );
        angles.y = atan2( forward.y, forward.x ) * 180 / pi( );

        if ( angles.y > 90 )
            angles.y -= 180;
        else if ( angles.y < 90 )
            angles.y += 180;
        else if ( angles.y == 90 )
            angles.y = 0;
    }

    angles.z = 0.0f;
}

void math_t::angle_vectors( vec3_t& angles, vec3_t& forward )
{
    float sp, sy, cp, cy;

    sin_cos( static_cast< float >( deg_to_rad( angles.y ) ), &sy, &cy );
    sin_cos( static_cast< float >( deg_to_rad( angles.x ) ), &sp, &cp );

    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void math_t::angle_vectors( vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up )
{
    float sr, sp, sy, cr, cp, cy;

    sin_cos( static_cast< float >( deg_to_rad( angles.y ) ), &sy, &cy );
    sin_cos( static_cast< float >( deg_to_rad( angles.x ) ), &sp, &cp );
    sin_cos( static_cast< float >( deg_to_rad( angles.z ) ), &sr, &cr );

    if ( forward )
    {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    if ( right )
    {
        right->x = ( -1 * sr * sp * cy + -1 * cr * -sy );
        right->y = ( -1 * sr * sp * sy + -1 * cr * cy );
        right->z = -1 * sr * cp;
    }

    if ( up )
    {
        up->x = ( cr * sp * cy + -sr * -sy );
        up->y = ( cr * sp * sy + -sr * cy );
        up->z = cr * cp;
    }
}

vec3_t math_t::calculate_angle( vec3_t& a, vec3_t& b )
{
    vec3_t angles;

    vec3_t delta = a - b;

    vector_angles( delta, angles );

    return angles;
}

vec3_t math_t::vector_add( vec3_t& a, vec3_t& b )
{
    return vec3_t( a.x + b.x,
        a.y + b.y,
        a.z + b.z );
}

vec3_t math_t::vector_subtract( vec3_t& a, vec3_t& b )
{
    return vec3_t( a.x - b.x,
        a.y - b.y,
        a.z - b.z );
}

vec3_t math_t::vector_multiply( vec3_t& a, vec3_t& b )
{
    return vec3_t( a.x * b.x,
        a.y * b.y,
        a.z * b.z );
}

vec3_t math_t::vector_divide( vec3_t& a, vec3_t& b )
{
    return vec3_t( a.x / b.x,
        a.y / b.y,
        a.z / b.z );
}