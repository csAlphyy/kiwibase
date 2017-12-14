#include "common.h"
#include "csgo.h"

// ================================================
//  forward declarations
// ================================================

HINSTANCE instance_for_unhooking;
void initialize( void );

// ================================================
//  dllmain export and entry-point
// ================================================

bool __stdcall DllMain( HINSTANCE instance, unsigned long reason, void* reserved )
{
    // makes the file smaller by removing DLL_THREAD_* calls, thanks @gavreel for explaining this to me in-depth :)
    DisableThreadLibraryCalls( instance );

    switch ( reason )
    {
        case DLL_PROCESS_ATTACH:
        {
            // let's store our instance for unhooking later, perhaps?
            instance_for_unhooking = instance;

            // run our thread
            CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) initialize, 0, 0, 0 );
        }break;

        default:
            break;
    }

    return TRUE;
}

// ================================================
//  initialization thread
// ================================================

void initialize( void )
{
    // initialize all the necessary interfaces, etc
    csgo.hook( );

    // signalize injection
    Beep( 495, 100 );

    // wait for uninjection, you can change this to a var if you want to
    while ( !GetAsyncKeyState( VK_DELETE ) )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
    }

    // self-explanatory
    csgo.unhook( );

    Beep( 495, 100 );

    // you should always allow a certain time limit for hooks to finish
    // if you are crashing upon unhooking, try increasing the delay
    // as some hooks are more time expensive (although this is often not the case)
    std::this_thread::sleep_for( std::chrono::seconds( 2 ) );

    // unload our library from the game's PEB if we have injected with a LoadLibraryA injector
    FreeLibraryAndExitThread( instance_for_unhooking, 0 );
}