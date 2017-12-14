#pragma once
#include "common.h"
#include "sdk.h"

// CBaseEntity::m_fFlags
// PLAYER SPECIFIC FLAGS FIRST BECAUSE WE USE ONLY A FEW BITS OF NETWORK PRECISION
// This top block is for singleplayer games only....no HL2:DM (which defines HL2_DLL)
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_ANIMDUCKING			(1<<2)	// Player flag -- Player is in the process of crouching or uncrouching but could be in transition
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<10)	// In water
#define PLAYER_FLAG_BITS		11
#define	FL_FLY					(1<<11)	// Changes the SV_Movestep() behavior to not need to be on ground
#define	FL_SWIM					(1<<12)	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define	FL_CONVEYOR				(1<<13)
#define	FL_NPC					(1<<14)
#define	FL_GODMODE				(1<<15)
#define	FL_NOTARGET				(1<<16)
#define	FL_AIMTARGET			(1<<17)	// set if the crosshair needs to aim onto the entity
#define	FL_PARTIALGROUND		(1<<18)	// not all corners are valid
#define FL_STATICPROP			(1<<19)	// Eetsa static prop!		
#define FL_GRAPHED				(1<<20) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE				(1<<21)
#define FL_STEPMOVEMENT			(1<<22)	// Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH			(1<<23)	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
#define FL_BASEVELOCITY			(1<<24)	// Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_WORLDBRUSH			(1<<25)	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_OBJECT				(1<<26) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME				(1<<27)	// This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE				(1<<28)	// You know...
#define FL_DISSOLVING			(1<<29) // We're dissolving!
#define FL_TRANSRAGDOLL			(1<<30) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1<<31) // pusher that can't be blocked by the player


// edict->movetype values
enum movetype_t
{
    MOVETYPE_NONE = 0,	// never moves
    MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
    MOVETYPE_WALK,				// Player only - moving on the ground
    MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
    MOVETYPE_FLY,				// No gravity, but still collides with stuff
    MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
    MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
    MOVETYPE_PUSH,				// no clip to world, push and crush
    MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
    MOVETYPE_LADDER,			// Used by players only when going onto a ladder
    MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
    MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
};

class collideable_t
{
public:
    vec3_t& mins( )
    {
        typedef vec3_t&( __thiscall *function )( void* );
        return call_virtual<function>( this, 1 )( this );
    }
    vec3_t& maxs( )
    {
        typedef vec3_t&( __thiscall *function )( void* );
        return call_virtual<function>( this, 2 )( this );
    }
};

class weapon_t;
class entity_t
{
public:

    void* animating( )
    {
        return reinterpret_cast< void* >( ( uintptr_t ) this + 0x4 );
    }

    void* networkable( )
    {
        return reinterpret_cast< void* >( ( uintptr_t ) this + 0x8 );
    }

    const unsigned long& ref_handle( void );
    collideable_t* collideable( void );
    clientclass_t* client_class( void );
    bool setup_bones( matrix_t*, int, int, float );
    bool is_player( void );
    bool is_weapon( void );
    int index( void );
    weapon_t* weapon( void );
    model_t* model( void );
    vec3_t hitbox( int );

    void update( void );

    float c4_time( void );

    vec3_t& absolute_origin( void );
    vec3_t& absolute_angles( void );

    netvar_fn( int, health, "DT_CSPlayer", "m_iHealth" );
    netvar_fn( int, team, "DT_CSPlayer", "m_iTeamNum" );
    netvar_fn( int, flags, "DT_CSPlayer", "m_fFlags" );
    netvar_fn( int, tick_base, "DT_CSPlayer", "m_nTickBase" );
    netvar_fn( int, shots_fired, "DT_CSPlayer", "m_iShotsFired" );
    netvar_fn( int, move_type, "DT_CSPlayer", "m_nMoveType" );
    netvar_fn( int, model_index, "DT_BasePlayer", "m_nModelIndex" );
    netvar_fn( int, hitbox_set, "DT_BasePlayer", "m_nHitboxSet" );
    netvar_fn( int, armor, "DT_CSPlayer", "m_ArmorValue" );
    netvar_fn( int, collision_group, "DT_CSPlayer", "m_CollisionGroup" );
    netvar_fn( int, glow_index, "DT_CSPlayer", "m_iGlowIndex" );
    netvar_fn( int, life_state, "DT_CSPlayer", "m_lifeState" );

    netvar_fn( float, flash_duration, "DT_CSPlayer", "m_flFlashDuration" );
    netvar_fn( float, simulation_time, "DT_CSPlayer", "m_flSimulationTime" );
    netvar_fn( float, lower_body_yaw, "DT_CSPlayer", "m_flLowerBodyYawTarget" );

    netvar_fn( unsigned long, owner_handle, "DT_CSPlayer", "m_hOwnerEntity" );
    netvar_fn( unsigned long, observer_target, "DT_CSPlayer", "m_hObserverTarget" );

    netvar_fn( bool, immune, "DT_CSPlayer", "m_bGunGameImmunity" );
    offset_fn( bool, dormant, 0xE9 );
    netvar_fn( bool, broken, "DT_BreakableSurface", "m_bIsBroken" );
    netvar_fn( bool, has_helmet, "DT_CSPlayer", "m_bHasHelmet" );

    netvar_fn( vec3_t, origin, "DT_BasePlayer", "m_vecOrigin" );
    netvar_fn( vec3_t, view_offset, "DT_BasePlayer", "m_vecViewOffset[0]" );
    netvar_fn( vec3_t, velocity, "DT_BasePlayer", "m_vecVelocity[0]" );
    netvar_fn( vec3_t, mins, "DT_BasePlayer", "m_vecMins" );
    netvar_fn( vec3_t, maxs, "DT_BasePlayer", "m_vecMaxs" );

    netvar_fn( vec3_t, eye_angles, "DT_CSPlayer", "m_angEyeAngles" );
    netvar_fn( const char*, last_place_name, "DT_BasePlayer", "m_szLastPlaceName" );
    netvar_fn( unsigned long, active_weapon_handle, "DT_CSPlayer", "m_hActiveWeapon" );

    netvar_fn( bool, heavy, "DT_CSPlayer", "m_bHasHeavyArmor" );

    netvar_fn( vec3_t, aim_punch, "DT_BasePlayer", "m_aimPunchAngle" );
    netvar_fn( vec3_t, view_punch, "DT_BasePlayer", "m_viewPunchAngle" );

    using flArr24 = std::array<float, 24>;
    netvar_fn( flArr24, pose_parameter, "DT_CSPlayer", "m_flPoseParameter" );

    anetvar_fn( vec3_t, networked_origin, "DT_CSPlayer", "m_flFriction", -0x000C );
};