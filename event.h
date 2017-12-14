#pragma once
#include "common.h"

// ======================================================
//  event class - no need for const/destructors in a cpp
// ======================================================

class event_t
{
public:
    virtual ~event_t( ) = 0;
    virtual const char*     get_name( ) const = 0;

    virtual bool            is_reliable( ) const = 0;
    virtual bool            is_local( ) const = 0;
    virtual bool            is_empty( const char *keyName = nullptr ) = 0;

    virtual bool            get_bool( const char *keyName = nullptr, bool defaultValue = false ) = 0;
    virtual int             get_int( const char *keyName = nullptr, int defaultValue = 0 ) = 0;
    virtual uint64_t        get_uint( const char *keyName = nullptr, unsigned long defaultValue = 0 ) = 0;
    virtual float           get_float( const char *keyName = nullptr, float defaultValue = 0.0f ) = 0;
    virtual const char*     get_string( const char *keyName = nullptr, const char *defaultValue = "" ) = 0;
    virtual const wchar_t*  get_wide_string( const char *keyName, const wchar_t *defaultValue = L"" ) = 0;

    virtual void            set_bool( const char *keyName, bool value ) = 0;
    virtual void            set_int( const char *keyName, int value ) = 0;
    virtual void            set_uint( const char *keyName, unsigned long value ) = 0;
    virtual void            set_float( const char *keyName, float value ) = 0;
    virtual void            set_string( const char *keyName, const char *value ) = 0;
    virtual void            set_wide_string( const char *keyName, const wchar_t *value ) = 0;
};