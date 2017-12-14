#pragma once

/* cute singleton class ripped from perfecthook, credits to whoever made it */

template<typename T>
class singleton
{
protected:
    singleton( )
    {
    }
    ~singleton( )
    {
    }

    singleton( const singleton& ) = delete;
    singleton& operator=( const singleton& ) = delete;

    singleton( singleton&& ) = delete;
    singleton& operator=( singleton&& ) = delete;
public:
    static T& instance( )
    {
        static T inst {};
        return inst;
    }
};
