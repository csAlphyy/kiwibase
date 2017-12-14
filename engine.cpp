#include "engine.h"

// ======================================================
//  const/destructors
// ======================================================

engine::engine( void )
{
};
engine::~engine( void )
{
};

// ======================================================
//  functions
// ======================================================

void engine::get( void )
{
    auto get_interface = [ & ] ( std::string module, std::string interface_name )
    {
        // define the interface
        typedef void*( *interface_t )( const char* name, int ret );
        interface_t interface_factory( reinterpret_cast< interface_t >( GetProcAddress( GetModuleHandleA( module.c_str( ) ), "CreateInterface" ) ) );

        // return interface
        return interface_factory( interface_name.c_str( ), 0 );
    };

    this->engine_dll = get_interface( "engine.dll", "VEngineClient014" );
    this->engine_trace = get_interface( "engine.dll", "EngineTraceClient004" );
    this->debug_overlay = get_interface( "engine.dll", "VDebugOverlay004" );
    this->model_info = get_interface( "engine.dll", "VModelInfoClient004" );
    this->console = get_interface( "vstdlib.dll", "VEngineCvar007" );
    this->game_events = get_interface( "engine.dll", "GAMEEVENTSMANAGER002" );
    this->physprops = get_interface( "vphysics.dll", "VPhysicsSurfaceProps001" );
    this->engine_vgui = get_interface( "engine.dll", "VEngineVGui001" );

    // note from fluc: remember to dereference clientstate like ( *csgo.m_engine->clientstate )->get_delta_tick( ) = -1;
    this->clientstate = *reinterpret_cast< clientstate_t*** >( call_virtual<uintptr_t>( this->engine_dll, 12 ) + 0x10 );
}

surfacedata_t* engine::get_surface_data( int index )
{
    typedef surfacedata_t*( __thiscall* function )( void*, int );
    return call_virtual<function>( this->physprops, 5 )( this->physprops, index );
}

int engine::get_point_contents( const vec3_t& in, int mask = MASK_ALL, entity_t* entity = nullptr ) // 0
{
    typedef int( __thiscall* function )( void*, const vec3_t&, int, entity_t* );
    return call_virtual<function>( this->engine_trace, 0 )( this->engine_trace, in, mask, entity );
}

model_t* engine::get_model( int in ) // 2
{
    typedef model_t*( __thiscall* function )( void*, int );
    return call_virtual<function>( this->model_info, 2 )( this->model_info, in );
}

int engine::get_model_index( const char* in ) // 3 
{
    typedef int( __thiscall* function )( void*, const char* );
    return call_virtual<function>( this->model_info, 3 )( this->model_info, in );
}

void engine::clip_ray_to_entity( const ray_t& ray, unsigned int mask, entity_t* entity, trace_t* trace ) // 3
{
    typedef void( __thiscall* function )( void*, const ray_t&, unsigned int, entity_t*, trace_t* );
    call_virtual<function>( this->engine_trace, 3 )( this->engine_trace, ray, mask, entity, trace ); // no need to return in a void 
}

const char* engine::get_model_name( const model_t* in ) // 4
{
    typedef const char*( __thiscall* function )( void*, const model_t* );
    return call_virtual<function>( this->model_info, 4 )( this->model_info, in );
}

void engine::trace_ray( const ray_t& ray, unsigned int mask, ITraceFilter* filter, trace_t* trace ) // 5
{
    typedef void( __thiscall* function )( void*, const ray_t&, unsigned int, ITraceFilter*, trace_t* );
    call_virtual<function>( this->engine_trace, 5 )( this->engine_trace, ray, mask, filter, trace );
}

netchannel_t* engine::get_network_data( void )
{
    typedef netchannel_t*( __thiscall* function )( void* );
    return call_virtual<function>( this->engine_dll, 78 )( this->engine_dll );
}

void engine::get_screen_size( int& w, int& h ) // 5
{
    typedef void( __thiscall* function )( void*, int&, int& );
    call_virtual<function>( this->engine_dll, 5 )( this->engine_dll, w, h );
}

void engine::get_player_info( int in, playerinfo_t* out ) // 8
{
    typedef void( __thiscall* function )( void*, int, playerinfo_t* );
    call_virtual<function>( this->engine_dll, 8 )( this->engine_dll, in, out );
}

int engine::get_player_userid( int in ) // 9
{
    typedef int( __thiscall* function )( void*, int );
    return call_virtual<function>( this->engine_dll, 9 )( this->engine_dll, in );
}

int engine::get_local_player( void ) // 12
{
    typedef int( __thiscall* function )( void* );
    return call_virtual<function>( this->engine_dll, 12 )( this->engine_dll );
}

bool engine::world_to_screen( const vec3_t& in, vec3_t& out ) // 13
{
    typedef int( __thiscall* function )( void*, const vec3_t&, vec3_t& );

    int return_value = call_virtual<function>( this->debug_overlay, 13 )( this->debug_overlay, in, out );

    return static_cast< bool >( return_value != 1 );
}

float engine::get_last_time_stamp( void ) // 14
{
    typedef float( __thiscall* function )( void* );
    return call_virtual<function>( this->engine_dll, 14 )( this->engine_dll );
}

cvar_t* engine::get_convar( const char* in ) // 16
{
    typedef cvar_t*( __thiscall* function )( void*, const char* );
    return call_virtual<function>( this->console, 16 )( this->console, in );
}

void engine::get_view_angles( vec3_t& out ) // 18
{
    typedef void( __thiscall* function )( void*, vec3_t& );
    call_virtual<function>( this->engine_dll, 18 )( this->engine_dll, out );
}

void engine::set_view_angles( vec3_t& in ) // 19
{
    typedef void( __thiscall* function )( void*, vec3_t& );
    call_virtual<function>( this->engine_dll, 19 )( this->engine_dll, in );
}

bool engine::is_in_game( void ) // 26
{
    typedef bool( __thiscall* function )( void* );
    return call_virtual<function>( this->engine_dll, 26 )( this->engine_dll );
}

bool engine::is_connected( void ) // 27
{
    typedef bool( __thiscall* function )( void* );
    return call_virtual<function>( this->engine_dll, 27 )( this->engine_dll );
}

studiohdr_t* engine::get_studio_model( const model_t* in ) // 31 //30 grrr
{
    typedef studiohdr_t*( __thiscall* function )( void*, const model_t* );
    return call_virtual<function>( this->model_info, 30 )( this->model_info, in );
}

void engine::exec( const char* in ) // 108
{
    typedef void( __thiscall* function )( void*, const char* );
    call_virtual<function>( this->engine_dll, 108 )( this->engine_dll, in );
}
