#include "weapon.h"

weapondata_t* weapon_t::weapon_data( void )
{
    return call_virtual<weapondata_t*( __thiscall* )( void* )>( this, 446 )( this );
}

float weapon_t::spread( void )
{
    return call_virtual<float( __thiscall* )( void* )>( this, 439 )( this );
}

float weapon_t::inaccuracy( void )
{
    return call_virtual<float( __thiscall* )( void* )>( this, 469 )( this );
}

void weapon_t::update( void )
{
    call_virtual<void( __thiscall* )( void* )>( this, 470 )( this );
}

// very gay function, credits to A5 or whoever originally went through the pain of making this 
bool weapon_t::ballistic( void )
{
    if ( !this )
    {
        return false;
    }

    auto i = this->id( );

    switch ( i )
    {
        case WEAPON_DEAGLE:
        case WEAPON_ELITE:
        case WEAPON_FIVESEVEN:
        case WEAPON_GLOCK:
        case WEAPON_AK47:
        case WEAPON_AUG:
        case WEAPON_AWP:
        case WEAPON_FAMAS:
        case WEAPON_G3SG1:
        case WEAPON_GALILAR:
        case WEAPON_M249:
        case WEAPON_M4A1:
        case WEAPON_MAC10:
        case WEAPON_P90:
        case WEAPON_UMP45:
        case WEAPON_XM1014:
        case WEAPON_BIZON:
        case WEAPON_MAG7:
        case WEAPON_NEGEV:
        case WEAPON_SAWEDOFF:
        case WEAPON_TEC9:
            return true;
        case WEAPON_TASER:
            return false;
        case WEAPON_HKP2000:
        case WEAPON_MP7:
        case WEAPON_MP9:
        case WEAPON_NOVA:
        case WEAPON_P250:
        case WEAPON_SCAR20:
        case WEAPON_SG556:
        case WEAPON_SSG08:
            return true;
        case WEAPON_KNIFE:
        case WEAPON_FLASHBANG:
        case WEAPON_HEGRENADE:
        case WEAPON_SMOKEGRENADE:
        case WEAPON_MOLOTOV:
        case WEAPON_DECOY:
        case WEAPON_INCGRENADE:
        case WEAPON_C4:
        case WEAPON_KNIFE_T:
            return false;
        case WEAPON_M4A1_SILENCER:
        case WEAPON_USP_SILENCER:
        case WEAPON_CZ75A:
        case WEAPON_REVOLVER:
            return true;
        default:
            return false;
    }
}