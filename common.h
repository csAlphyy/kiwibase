#pragma once
// ================================================
//  system imports
// ================================================

#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <Psapi.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <assert.h>

// ================================================
//  util imports
// ================================================

#include "hook.h"

// ================================================
//  util functions
// ================================================

#include "singleton.h"

template <typename t>
t call_virtual( void* ptr, size_t idx )
{
    size_t* vtable( *( size_t** ) ptr );
    size_t address( vtable [ idx ] );
    return ( t ) ( address );
}

uintptr_t find_pattern( std::string module, std::string pattern );

// creates a fn for the netvar
#define netvar_fn( t, f, a, b )\
t& f( void )\
{\
static uintptr_t o = netvar->get_offset( a, b );\
return *( t* ) ( ( uintptr_t ) this + o );\
}

// creates a fn for the netvar, and then adds the desired offset
// note to whoever didnt do 6th grade math, adding negative numbers = subtracting
#define anetvar_fn( t, f, a, b, d )\
t& f( void )\
{\
static uintptr_t o = netvar->get_offset( a, b );\
return *( t* ) ( ( uintptr_t ) ( this + o ) + d );\
}

// creates a fn based on a static offset
// note from fluc: ur REALLY gay if u use this.
#define offset_fn( t, f, o )\
t& f( void )\
{\
return *( t* )( ( uintptr_t ) this + o );\
}