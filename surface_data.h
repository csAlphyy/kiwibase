#pragma once

struct surfacephysicsparams_t
{
    float   friction;
    float   elasticity; // collision elasticity - used to compute coefficient of restitution
    float   density;        // physical density (in kg / m^3)
    float   thickness;      // material thickness if not solid (sheet materials) in inches
    float   dampening;
};

struct surfaceaudioparams_t
{
    float   reflectivity;                   // like elasticity, but how much sound should be reflected by this surface
    float   hardness;                 // like elasticity, but only affects impact sound choices
    float   roughness;                // like friction, but only affects scrape sound choices
    float   rough_treshhold;                 // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
    float   hard_threshhold;                  // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
    float   hard_velocity_treshhold;  // collision velocity > this causes "hard" impacts, < this causes "soft" impacts       	
    float    high_occlusion;       //a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
    float    mid_occlusion;
    float    low_occlusion;
};

struct surfacesoundnames_t
{
    unsigned short  step_left;
    unsigned short  step_right;
    unsigned short  impact_soft;
    unsigned short  impact_hard;
    unsigned short  scrape_smooth;
    unsigned short  scrape_rough;
    unsigned short  bullet_impact;
    unsigned short  rolling;
    unsigned short  break_sound;
    unsigned short  strain_sound;
};

struct surfacegameprops_t
{
public:
    float           max_speed_factor;
    float           jump_factor;
    int             _pad;
    float           penetration_modifier;
    float           damage_modifier;
    unsigned short  material;
    unsigned char   _pad2 [ 3 ];
};

struct surfacedata_t
{
    surfacephysicsparams_t	physics;
    surfaceaudioparams_t	audio;
    surfacesoundnames_t		sounds;
    surfacegameprops_t		game;
};