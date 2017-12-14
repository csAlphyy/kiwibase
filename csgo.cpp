#include "csgo.h"

// ================================================
//  resolving externals
// ================================================
csgo_t csgo;

// ================================================
//  functions
// ================================================

void csgo_t::hook( void )
{
    // find game window first
    while ( !( m_hwnd = FindWindowA( "Valve001", NULL ) ) )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    // serverbrowser.dll signalizes that the game is ready, at least for our needs
    while ( !GetModuleHandleA( "serverbrowser.dll" ) )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    // grab out interface pointers first
    m_client.get( );
    m_engine.get( );

    // initialize our drawing manager
    m_render.get( );

    // quick fix coz i dont wanna recompile
    csgo.m_sendpacket = true;

    // initialize and grab our netvar manager instance
    // yeah this is REALLY gay, change it to a singleton if you're nitpicky
    netvar = new netvar_t( );
    netvar->get( );

    // get our g_pMemAlloc ptr
    m_memalloc = ( memalloc_t* ) GetProcAddress( GetModuleHandleA( "tier0.dll" ), "g_pMemAlloc" );

    // get client mode 
    auto clientmode = **( uintptr_t*** ) ( ( *( uintptr_t** ) m_client.client_dll ) [ 10 ] + 0x5 );

    // client mode hooks are special snowflakes uwu
    m_clientmode = new hook_t( clientmode );

    // apply the hooks
    m_clientmode->hook_index( hook_manager::create_move, 24 );
}

void csgo_t::unhook( void )
{
    m_clientmode->unhook_index( 24 );
}