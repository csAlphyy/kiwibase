#pragma once

// ================================================
//  imports
// ================================================

#include "common.h"
#include "sdk.h"
#include "viewsetup.h"

// ================================================
//  this is where the main stuff happens
// ================================================

// typedefs
using fn_create_move = bool( __stdcall* )( float, usercmd_t* );

extern recvproxyfn fn_did_smoke_effect;

namespace hook_manager
{
    // prototypes
    bool __stdcall create_move( float, usercmd_t* );
}

class csgo_t
{
public:
    // misc stuff
    HWND m_hwnd;

    // hooks
    hook_t* m_clientmode;
    void hook( void );
    void unhook( void );

    engine m_engine;
    client m_client;

    render m_render;

    // remember that the sendpacket should be true initially
    // not setting it as such causes a bug similar to airstuck
    bool m_sendpacket = true;
    
    entity_t* m_localplayer;
    usercmd_t* m_cmd;
    memalloc_t* m_memalloc;
};

extern csgo_t csgo;
