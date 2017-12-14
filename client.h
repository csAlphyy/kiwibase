#pragma once
#include "common.h"
#include "recvprop.h"
#include "entity.h"
#include "color.h"

// ======================================================
//  framestagenotify shit
// ======================================================

enum framestage_t
{
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END
};

// ======================================================
//  globals struct
// ======================================================

class globals_t
{
public:
    float     realtime;                     // 0x0000
    int       framecount;                   // 0x0004
    float     absoluteframetime;            // 0x0008
    float     absoluteframestarttime;		// 0x000C
    float     curtime;                      // 0x0010
    float     frametime;                    // 0x0014
    int       max_clients;                   // 0x0018
    int       tickcount;                    // 0x001C
    float     interval_per_tick;            // 0x0020
    float     interpolation_amount;         // 0x0024
    int       sim_ticks_this_frame;            // 0x0028
    int       network_protocol;             // 0x002C
    void*     save_data;                    // 0x0030
    bool      client;                    // 0x0031
    bool      remote_client;              // 0x0032

private:
    int       time_stamp_networking_base;
    int       time_stamp_randomise_window;
};

// ======================================================
//  input class
// ======================================================

class input_t
{
public:
    bool                track_ir_available;             //0x04
    bool                mouse_is_initialized;           //0x05
    bool                mouse_is_active;                //0x06
    bool                joystick_advanced_init;         //0x07
private:
    char                pad_0x08 [ 0x2C ];                 //0x08
public:
    void*               keys;                           //0x34
private:
    char                pad_0x38 [ 0x64 ];                 //0x38
public:
    bool                camera_intercepting_mouse;      //0x9C
    bool                camera_in_third_person;         //0x9D
    bool                camera_moving_with_mouse;       //0x9E
    vec3_t              camera_offset;                  //0xA0
    bool                camera_distance_move;           //0xAC
    int                 camera_old_x;                   //0xB0
    int                 camera_old_y;                   //0xB4
    int                 camera_x;                       //0xB8
    int                 camera_y;                       //0xBC
    bool                camera_is_ortographic;          //0xC0
    vec3_t              previous_view_angles;           //0xC4
    vec3_t              previous_view_angles_tilted;    //0xD0
    float               last_forward_move;              //0xDC
    int                 clear_input_state;              //0xE0
private:
    char                pad_0xE4 [ 0x8 ];                  //0xE4
};

// ======================================================
//  client.dll based class
// ======================================================

class client
{
public:
    void* client_dll;
    void* entity_list;
    void* panel;
    void* surface;
    void* prediction;
    void* move_helper;
    void* game_movement;

    client( void );
    ~client( void );

    void get( void );

    globals_t* m_globals;
    input_t* m_input;

    clientclass_t* get_all_classes( void ); // index 8
    entity_t* get_entity( int ); // index 3
    entity_t* get_entity( uintptr_t ); // index 4
    int max_entities( void ); // index 6

    const char* get_panel_name( int ); // 36
    void set_draw_color( color_t ); // 14
    void draw_filled( vec2_t, vec2_t ); // 16
    void draw_line( vec2_t, vec2_t ); // 19
    void draw_outlined( vec2_t, vec2_t ); // 18
    void set_draw_text_font( uintptr_t ); // 23
    void set_draw_text_color( color_t ); // 24
    void set_draw_text_pos( vec2_t ); // 26
    void draw_string( wchar_t*, int, int ); // 28
    bool get_text_size( uintptr_t, const wchar_t*, int&, int& ); // 79
    uintptr_t create_font( void ); // 71
    bool create_font( uintptr_t, const char*, int, int, int, int, int, int, int ); // 72

    void set_prediction_host( entity_t* ); // 1
    void setup_move( entity_t*, usercmd_t*, void*, void* ); // 20
    void finish_move( entity_t*, usercmd_t*, void* ); // 21
    void process_movement( entity_t*, void* ); // 1
    void start_tracking_errors( entity_t* ); // 3
    void finish_tracking_errors( entity_t* ); // 4
};