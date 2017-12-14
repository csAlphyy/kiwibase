#pragma once
#include "common.h"

// ================================================
//  player info struct
//  credits: https://github.com/AimTuxOfficial/AimTux/blob/master/src/SDK/IEngineClient.h#L6
// ================================================

typedef struct player_info_s
{
    int64_t pad;
    union
    {
        int64_t xuid;
        struct
        {
            int xuid_low;
            int xuid_high;
        };
    };
    char name [ 128 ];
    int user_id;
    char guid [ 33 ];
    unsigned int friends_id;
    char friends_name [ 128 ];
    bool is_fake_player;
    bool is_hltv;
    unsigned int custom_files [ 4 ];
    unsigned char files_downloaded;
} playerinfo_t;