#include "entity.h"
#include "weapon.h"
#include "csgo.h"

const unsigned long & entity_t::ref_handle( void )
{
    typedef const unsigned long&( __thiscall* function )( void* );
    return call_virtual<function>( this, 2 )( this );
}

clientclass_t* entity_t::client_class( void )
{
    typedef clientclass_t*( __thiscall* function )( void* );
    return call_virtual<function>( networkable( ), 2 )( networkable( ) );
}

collideable_t* entity_t::collideable( void )
{
    typedef collideable_t*( __thiscall* function )( void* );
    return call_virtual<function>( this, 3 )( this );
}

int entity_t::index( void )
{
    typedef int( __thiscall* function )( void* );
    return call_virtual<function>( networkable( ), 10 )( networkable( ) );
}

bool entity_t::setup_bones( matrix_t* out, int max_bones, int mask, float time )
{
    if ( !this )
    {
        return false;
    }

    typedef bool( __thiscall* function )( void*, matrix_t*, int, int, float );
    return call_virtual<function>( animating( ), 13 )( animating( ), out, max_bones, mask, time );
}

weapon_t* entity_t::weapon( void )
{
    uintptr_t handle = active_weapon_handle( );

    return ( weapon_t* ) csgo.m_client.get_entity( handle );
}

bool entity_t::is_player( void )
{
    // xref: "effects/nightvision"
    return call_virtual<bool( __thiscall* )( void* )>( this, 152 )( this );
}

bool entity_t::is_weapon( void )
{
    // xref: "CNewParticleEffect::DrawModel"
    return call_virtual<bool( __thiscall* )( void* )>( this, 160 )( this );
}

model_t* entity_t::model( void )
{
    typedef model_t*( __thiscall* function )( void* );
    return call_virtual<function>( animating( ), 8 )( animating( ) );
}

vec3_t entity_t::hitbox( int i )
{
    matrix_t matrix [ 128 ];

    if ( setup_bones( matrix, 128, 0x100, 0.0f ) )
    {
        auto studio_hdr = csgo.m_engine.get_studio_model( model( ) );

        if ( !studio_hdr )
        {
            return vec3_t( 0, 0, 0 );
        }

        auto hitbox_set = studio_hdr->phitboxset( 0 );

        if ( !hitbox_set )
        {
            return vec3_t( 0, 0, 0 );
        }

        auto hitbox = hitbox_set->get_hitbox( i );

        if ( hitbox )
        {
            vec3_t min, max, centre;

            valve.transform_vector( hitbox->bbmin, matrix [ hitbox->bone ], min );
            valve.transform_vector( hitbox->bbmax, matrix [ hitbox->bone ], max );

            centre = ( ( valve.vector_add( min, max ) ) * 0.5f );

            return centre;
        }
    }

    return { 0.0f, 0.0f, 0.0f };
}

void entity_t::update( void )
{
    call_virtual<void( __thiscall* )( void* )>( this, 218 )( this );
}

float entity_t::c4_time( void )
{
    static auto offset = netvar->get_offset( "DT_PlantedC4", "m_flC4Blow" );

    auto bomb_time = *( float* ) ( ( uintptr_t ) this + offset );
    auto cur_time = csgo.m_client.m_globals->curtime;

    auto return_time = bomb_time - cur_time;

    return ( return_time <= 0.0f ) ? 0.0f : return_time;
}

// iirc you can only use these to get the origin/angles
vec3_t& entity_t::absolute_origin( void )
{
    typedef vec3_t&( __thiscall* function )( void* );
    return call_virtual<function>( this, 10 )( this );
}

vec3_t& entity_t::absolute_angles( void )
{
    typedef vec3_t&( __thiscall* function )( void* );
    return call_virtual<function>( this, 11 )( this );
}