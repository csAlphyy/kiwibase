#pragma once
#include "common.h"
#include "recvprop.h"

// shoutout to pycache
class netvar_t
{
public:
    void get( void );
    uintptr_t get_offset( const char*, const char* );
    recvproxyfn hook_netvar( const char*, const char*, recvproxyfn );

    ~netvar_t( void );
private:
    uintptr_t get_prop( const char*, const char*, recvprop_t** );
    uintptr_t get_prop( recvtable_t*, const char*, recvprop_t** );
    recvtable_t* get_table( const char* );
    std::vector<recvtable_t*> m_tables = { };
}; extern netvar_t* netvar;
