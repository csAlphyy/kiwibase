#include "csgo.h"

bool __stdcall hook_manager::create_move( float input_sample_time, usercmd_t* ucmd )
{
    // get global variables
    csgo.m_localplayer = csgo.m_client.get_entity( csgo.m_engine.get_local_player( ) );
    csgo.m_cmd = ucmd;

    // if you don't do this, you get a really gay "bug" during half-time
    if ( !ucmd || !ucmd->command_number )
    {
        return csgo.m_clientmode->get_original<fn_create_move>( 24 )( input_sample_time, ucmd );
    }

    uintptr_t* frame_ptr;
    // ebp is the frame pointer, let's move it so we can access it
    __asm mov frame_ptr, ebp;

    // set our send packet
    *( bool* ) ( *frame_ptr - 0x1C ) = csgo.m_sendpacket;

    // here, i popped in a basic bunnyhop coz im nice
    if ( ucmd->buttons & IN_JUMP )
    {
        if ( !( csgo.m_localplayer->flags( ) & FL_ONGROUND ) )
        {
            ucmd->buttons &= ~IN_JUMP;
        }
    }

    // fuck untrusted dude
    // note from fluc: i mean i never really tested the roll range, but you should be safe
    ucmd->view_angles.clamp( );
    ucmd->forward = clip_number( ucmd->forward, -450.0f, 450.0f );
    ucmd->side = clip_number( ucmd->side, -450.0f, 450.0f );
    ucmd->up = clip_number( ucmd->up, -320.0f, 320.0f );

    return false;
}