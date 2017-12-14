#pragma once
#include <Windows.h>

class color_t
{
private:
    unsigned char _col [ 4 ];
public:
    color_t( void );
    ~color_t( void );
    color_t( int, int, int, int );
    color_t( float, float, float, float );

    int r( void );
    int g( void );
    int b( void );
    int a( void );
};