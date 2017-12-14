#include "color.h"

// ======================================================
//  const/destructors
// ======================================================

color_t::color_t( void )
{
    memset( _col, 0, sizeof( _col ) );
}

color_t::~color_t( void )
{
}

color_t::color_t( int r, int g, int b, int a = 255 )
{
    _col [ 0 ] = static_cast< unsigned char >( r );
    _col [ 1 ] = static_cast< unsigned char >( g );
    _col [ 2 ] = static_cast< unsigned char >( b );
    _col [ 3 ] = static_cast< unsigned char >( a );
}

color_t::color_t( float r, float g, float b, float a = 1.0f )
{
    _col [ 0 ] = static_cast< unsigned char >( static_cast< int >( r * 255.0f ) );
    _col [ 1 ] = static_cast< unsigned char >( static_cast< int >( g * 255.0f ) );
    _col [ 2 ] = static_cast< unsigned char >( static_cast< int >( b * 255.0f ) );
    _col [ 3 ] = static_cast< unsigned char >( static_cast< int >( a * 255.0f ) );
}


int color_t::r( void )
{
    return static_cast< int >( _col [ 0 ] );
}

int color_t::g( void )
{
    return static_cast< int >( _col [ 1 ] );
}

int color_t::b( void )
{
    return static_cast< int >( _col [ 2 ] );
}

int color_t::a( void )
{
    return static_cast< int >( _col [ 3 ] );
}