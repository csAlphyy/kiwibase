#pragma once
#include "common.h"

class memalloc_t
{
public:
    virtual void *alloc( size_t nSize ) = 0;
    virtual void *re_alloc( void *pMem, size_t nSize ) = 0;
    virtual void free( void *pMem ) = 0;
};