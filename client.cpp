#include "client.h"

// ======================================================
//  const/destructors
// ======================================================

client::client( void )
{
};
client::~client( void )
{
};

// ======================================================
//  functions
// ======================================================

void client::get( void )
{
    auto get_interface = [ & ] ( std::string module, std::string interface_name )
    {
        // define the interface
        typedef void*( *interface_t )( const char* name, int ret );
        interface_t interface_factory( reinterpret_cast< interface_t >( GetProcAddress( GetModuleHandleA( module.c_str( ) ), "CreateInterface" ) ) );

        // return interface
        return interface_factory( interface_name.c_str( ), 0 );
    };

    this->client_dll = get_interface( "client.dll", "VClient018" );
    this->entity_list = get_interface( "client.dll", "VClientEntityList003" );
    this->m_globals = **reinterpret_cast< globals_t*** >( ( *reinterpret_cast< uintptr_t** >( this->client_dll ) [ 0 ] + 0x1B ) );

    // xref: "CScriptedIconLesson::FireGameEvent", scroll down, mov ecx, g_pInput
    this->m_input = *reinterpret_cast< input_t** >( find_pattern( "client.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) + 0x1 );

    this->surface = get_interface( "vguimatsurface.dll", "VGUI_Surface031" );
    this->panel = get_interface( "vgui2.dll", "VGUI_Panel009" );

    // xref: "Player.Swim", mov ecx, g_pMoveHelper, first 0x2 bytes are irrelevant to the pattern
    // fluc note: disregard the above, i haven't had luck finding the sig, just get it in runcommand
    this->move_helper = nullptr; // *reinterpret_cast< uintptr_t** >( find_pattern( "client.dll", "8B 0D ? ? ? ? 8B 46 08 68" ) + 0x2 );

    this->prediction = get_interface( "client.dll", "VClientPrediction001" );
    this->game_movement = get_interface( "client.dll", "GameMovement001" );
}

clientclass_t* client::get_all_classes( void )
{
    typedef clientclass_t*( __thiscall* function )( void* );
    return call_virtual<function>( this->client_dll, 8 )( this->client_dll );
}

entity_t* client::get_entity( int index )
{
    typedef entity_t*( __thiscall* function )( void*, int );
    return call_virtual<function>( this->entity_list, 3 )( this->entity_list, index );
}

entity_t* client::get_entity( uintptr_t handle )
{
    typedef entity_t*( __thiscall* function )( void*, uintptr_t );
    return call_virtual<function>( this->entity_list, 4 )( this->entity_list, handle );
}

const char* client::get_panel_name( int index ) // 36
{
    typedef const char*( __thiscall* function )( void*, int );
    return call_virtual<function>( this->panel, 36 )( this->panel, index );
}

void client::set_draw_color( color_t color ) // 14
{
    typedef void( __thiscall* function )( void*, color_t );
    call_virtual<function>( this->surface, 14 )( this->surface, color );
}

int client::max_entities( void ) // index 6
{
    typedef int( __thiscall* function )( void* );
    return call_virtual<function>( this->entity_list, 6 )( this->entity_list );
}

void client::draw_filled( vec2_t start, vec2_t end ) // 16
{
    typedef void( __thiscall* function )( void*, int, int, int, int );
    call_virtual<function>( this->surface, 16 )( this->surface, static_cast< int >( start.x ), static_cast< int >( start.y ), static_cast< int >( end.x ), static_cast< int >( end.y ) );
}

void client::draw_line( vec2_t start, vec2_t end ) // 19
{
    typedef void( __thiscall* function )( void*, int, int, int, int );
    call_virtual<function>( this->surface, 19 )( this->surface, static_cast< int >( start.x ), static_cast< int >( start.y ), static_cast< int >( end.x ), static_cast< int >( end.y ) );
}

void client::draw_outlined( vec2_t start, vec2_t end ) // 18
{
    typedef void( __thiscall* function )( void*, int, int, int, int );
    call_virtual<function>( this->surface, 18 )( this->surface, static_cast< int >( start.x ), static_cast< int >( start.y ), static_cast< int >( end.x ), static_cast< int >( end.y ) );
}

void client::set_draw_text_font( uintptr_t font ) // 23
{
    typedef void( __thiscall* function )( void*, uintptr_t );
    call_virtual<function>( this->surface, 23 )( this->surface, font );
}

void client::set_draw_text_color( color_t color ) // 24
{
    typedef void( __thiscall* function )( void*, color_t );
    call_virtual<function>( this->surface, 24 )( this->surface, color );
}

void client::set_draw_text_pos( vec2_t position ) // 26
{
    typedef void( __thiscall* function )( void*, int, int );
    call_virtual<function>( this->surface, 26 )( this->surface, static_cast< int >( position.x ), static_cast< int >( position.y ) );
}

void client::draw_string( wchar_t* input, int length, int type = 0 ) // 28
{
    typedef void( __thiscall* function )( void*, wchar_t*, int, int );
    call_virtual<function>( this->surface, 28 )( this->surface, input, length, type );
}

bool client::get_text_size( uintptr_t font, const wchar_t* in, int& out_w, int& out_h ) // 79
{
    typedef bool( __thiscall* function )( void*, uintptr_t, const wchar_t*, int&, int& );
    return call_virtual<function>( this->surface, 79 )( this->surface, font, in, out_w, out_h );
}

uintptr_t client::create_font( void ) // 71
{
    typedef uintptr_t( __thiscall* function )( void* );
    return call_virtual<function>( this->surface, 71 )( this->surface );
}

bool client::create_font( uintptr_t font, const char* windows_font_name, int tall, int weight, int blur, int scan_lines, int flags, int range_min = 0, int range_max = 0 ) // 72
{
    typedef bool( __thiscall* function )( void*, uintptr_t, const char*, int, int, int, int, int, int, int );
    return call_virtual<function>( this->surface, 72 )( this->surface, font, windows_font_name, tall, weight, blur, scan_lines, flags, range_min, range_max );
}

void client::set_prediction_host( entity_t* entity ) // 1
{
    typedef void( __thiscall* function )( void*, entity_t* );
    call_virtual<function>( this->move_helper, 1 )( this->move_helper, entity );
}

void client::setup_move( entity_t* entity, usercmd_t* ucmd, void* movehelper, void* movedata ) // 20
{
    typedef void( __thiscall* function )( void*, entity_t*, usercmd_t*, void*, void* );
    call_virtual<function>( this->prediction, 20 )( this->prediction, entity, ucmd, movehelper, movedata );
}

void client::finish_move( entity_t* entity, usercmd_t* ucmd, void* movedata ) // 21
{
    typedef void( __thiscall* function )( void*, entity_t*, usercmd_t*, void* );
    call_virtual<function>( this->prediction, 21 )( this->prediction, entity, ucmd, movedata );
}

void client::process_movement( entity_t* entity, void* movedata ) // 1
{
    typedef void( __thiscall* function )( void*, entity_t*, void* );
    call_virtual<function>( this->game_movement, 1 )( this->game_movement, entity, movedata );
}

void client::start_tracking_errors( entity_t* entity ) // 3
{
    typedef void( __thiscall* function )( void*, entity_t* );
    call_virtual<function>( this->game_movement, 3 )( this->game_movement, entity );
}

void client::finish_tracking_errors( entity_t* entity ) // 4
{
    typedef void( __thiscall* function )( void*, entity_t* );
    call_virtual<function>( this->game_movement, 4 )( this->game_movement, entity );
}
