#pragma once
#include "vec.h"

struct viewsetup_t
{
    char _0x0000 [ 16 ];
    __int32 x;
    __int32 x_old;
    __int32 y;
    __int32 y_old;
    __int32 width;
    __int32    width_old;
    __int32 height;
    __int32    height_old;
    char _0x0030 [ 128 ];
    float fov;
    float viewmodel_fov;
    vec3_t origin;
    vec3_t angles;
    float _near;
    float _far;
    float near_viewmodel;
    float far_viewmodel;
    float aspect_ratio;
    float near_blur_depth;
    float near_focus_depth;
    float near_far_focus_depth;
    float near_far_blur_depth;
    float near_blur_radius;
    float far_blur_radius;
    float dof_quality;
    __int32 motion_blur;
    char _0x0104 [ 68 ];
    __int32 edge_blur;
};