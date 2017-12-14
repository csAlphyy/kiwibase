#pragma once
#include "common.h"
#include "trace.h"
#include "event.h"
#include "playerinfo.h"
#include "cvar.h"
#include "model.h"
#include "surface_data.h"
#include "netchannel.h"

// ======================================================
//  engine.dll based class
// ======================================================

class clientstate_t
{
public:
    offset_fn( csnetchannel_t*, get_net_channel, 0x009C );
    offset_fn( int, get_current_sequence, 0x011C );
    offset_fn( int, get_delta_tick, 0x0174 );
    offset_fn( int, get_max_clients, 0x0310 );
    offset_fn( vec3_t, get_view_angles, 0x4D10 );
};

class engine
{
public:
    void* engine_dll; //
    void* engine_trace; //
    void* debug_overlay; //
    void* game_events;
    void* model_info; //
    void* console; //
    void* physprops; //
    void* engine_vgui; //
    clientstate_t** clientstate;//

    engine( void );
    ~engine( void );

    void get( void );

    int get_point_contents( const vec3_t&, int, entity_t* ); // 0
    model_t* get_model( int ); // 2
    int get_model_index( const char* ); // 3 
    void clip_ray_to_entity( const ray_t&, unsigned int, entity_t*, trace_t* ); // 3
    const char* get_model_name( const model_t* ); // 4
    void trace_ray( const ray_t&, unsigned int, ITraceFilter*, trace_t* ); // 5
    void get_screen_size( int&, int& ); // 5
    void get_player_info( int, playerinfo_t* ); // 8
    int get_player_userid( int ); // 9
    int get_local_player( void ); // 12
    bool world_to_screen( const vec3_t&, vec3_t& ); // 13 ;; output != 1
    float get_last_time_stamp( void ); // 14
    cvar_t* get_convar( const char* ); // 16
    void get_view_angles( vec3_t& ); // 18
    void set_view_angles( vec3_t& ); // 19
    bool is_in_game( void ); // 26
    bool is_connected( void ); // 27
    studiohdr_t* get_studio_model( const model_t* ); // 31
    void exec( const char* ); // 108
    surfacedata_t* get_surface_data( int ); //
    netchannel_t* get_network_data( void ); // 78
};