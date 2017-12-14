#pragma once
#include "common.h"
#include "vec.h"
#include "color.h"

/* poop pasted renderer, works quite well idk */

enum renderside_t
{
    RENDER_LEFT = 0,
    RENDER_CENTERED,
    RENDER_RIGHT
};

class render
{
public:
    render( void );
    ~render( void );

    struct
    {
        uintptr_t esp = 0;
    }font;

    void get( void );

    void string( uintptr_t, vec2_t, color_t, uintptr_t, const char*, ... );
    void fill( vec2_t, vec2_t, color_t );
    void outline( vec2_t, vec2_t, color_t );
    void line( vec2_t, vec2_t, color_t );
    vec2_t get_font_bounds( uintptr_t, const char*, ... );
};