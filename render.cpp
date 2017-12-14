#include "render.h"
#include "csgo.h"

render::render( void )
{
    // nothing rly neccessary in here
}

render::~render( void )
{
    // nothing rly neccessary in here
}

void render::get( void )
{
    csgo.m_client.create_font( font.esp = csgo.m_client.create_font( ), "Tahoma", 12, 300, 0, 0, 512, 0, 0 );
}

void render::string( uintptr_t font, vec2_t position, color_t color, uintptr_t align, const char* string, ... )
{
    va_list args;
    char buffer [ 1024 ];
    va_start( args, string );
    _vsnprintf_s( buffer, sizeof( buffer ), string, args );
    va_end( args );

    wchar_t wbuffer [ 1024 ];
    MultiByteToWideChar( CP_UTF8, 0, buffer, 256, wbuffer, 256 );

    int w, h;
    csgo.m_client.get_text_size( font, wbuffer, w, h );

    if ( align & RENDER_RIGHT )
        position.x -= w;

    if ( align & RENDER_CENTERED )
        position.x -= w / 2;

    csgo.m_client.set_draw_text_font( font );
    csgo.m_client.set_draw_text_pos( position );
    csgo.m_client.set_draw_text_color( color );
    csgo.m_client.draw_string( wbuffer, wcslen( wbuffer ), 0 );
}

void render::fill( vec2_t position, vec2_t size, color_t color )
{
    csgo.m_client.set_draw_color( color );
    csgo.m_client.draw_filled( position, { position.x + size.x, position.y + size.y } );
}

void render::outline( vec2_t position, vec2_t size, color_t color )
{
    csgo.m_client.set_draw_color( color );
    csgo.m_client.draw_outlined( position, { position.x + size.x, position.y + size.y } );
}

void render::line( vec2_t start, vec2_t end, color_t color )
{
    csgo.m_client.set_draw_color( color );
    csgo.m_client.draw_line( start, end );
}

vec2_t render::get_font_bounds( uintptr_t font, const char* string, ... )
{
    va_list args;

    char buffer [ 1024 ];

    va_start( args, string );
    _vsnprintf_s( buffer, sizeof( buffer ), string, args );
    va_end( args );

    wchar_t wbuffer [ 1024 ];
    MultiByteToWideChar( CP_UTF8, 0, buffer, 256, wbuffer, 256 );

    int w, h;
    csgo.m_client.get_text_size( font, wbuffer, w, h );

    return vec2_t( static_cast< float >( w ), static_cast< float >( h ) );
}