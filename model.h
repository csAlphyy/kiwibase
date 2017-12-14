#pragma once
#include "common.h"
#include "trace.h"

// ===================================================
//  this is probably the only pasted thing in the sdk
// ===================================================

#define MAX_QPATH  260

#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1        0x00000800    
#define BONE_USED_BY_VERTEX_LOD2        0x00001000  
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		128		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32


enum modtype_t
{
    mod_bad = 0,
    mod_brush,
    mod_sprite,
    mod_studio
};


struct mstudiobone_t
{
    int     sznameindex;
    int     parent;		// parent bone
    int     bonecontroller [ 6 ];	// bone controller index, -1 == none
    vec3_t  pos;
    VectorAligned  quat;
    vec3_t rot;
    vec3_t      posscale;
    vec3_t      rotscale;

    matrix_t posetobone;
    VectorAligned  qalignment;
    int					flags;
};


struct mstudiobbox_t
{
    int         bone;
    int         group;
    vec3_t      bbmin;
    vec3_t      bbmax;
    int         szhitboxnameindex;
    int32_t     m_ipad01 [ 3 ];
    float       m_flradius;
    int32_t     m_ipad02 [ 4 ];

    const char* getname( )
    {
        if ( !szhitboxnameindex ) return nullptr;
        return ( const char* ) ( ( uint8_t* ) this + szhitboxnameindex );
    }
};

struct mstudiohitboxset_t
{
    int    sznameindex;
    int    numhitboxes;
    int    hitboxindex;

    const char* get_name( )
    {
        if ( !sznameindex ) return nullptr;
        return ( const char* ) ( ( uint8_t* ) this + sznameindex );
    }

    mstudiobbox_t* get_hitbox( int i )
    {
        if ( i > numhitboxes ) return nullptr;
        return ( mstudiobbox_t* ) ( ( uint8_t* ) this + hitboxindex ) + i;
    }
};

struct model_t
{
    void*   fnhandle;               //0x0000 
    char    szname [ 260 ];            //0x0004 
    __int32 nloadflags;             //0x0108 
    __int32 nservercount;           //0x010c 
    __int32 type;                   //0x0110 
    __int32 flags;                  //0x0114 
    vec3_t  vecmins;                //0x0118 
    vec3_t  vecmaxs;                //0x0124 
    float   radius;                 //0x0130 
    char    pad [ 0x1c ];              //0x0134
};//size=0x0150

  // sequence descriptions
struct mstudioseqdesc_t
{
    int	szlabelindex;
    inline char * const psz_label( void ) const
    {
        return ( ( char * ) this ) + szlabelindex;
    }

    int	szactivitynameindex;
    inline char * const psz_activit_yname( void ) const
    {
        return ( ( char * ) this ) + szactivitynameindex;
    }

    int	flags;		// looping/non-looping flags

    int	activity;	// initialized at loadtime to game dll values
    int	actweight;

    int	numevents;
    int	eventindex;
    inline void *pevent( int i ) const
    {
        return ( ( ( byte * ) this ) + eventindex ) + i;
    };

    vec3_t	bbmin;		// per sequence bounding box
    vec3_t	bbmax;

    //-------------------------------------------------------------------------
    // purpose: returns a model animation from the sequence group size and
    //          blend index
    // note: this replaces getanimvalue() that was previously in bone_setup
    // note: this also acts as a setanimvalue() as it returns a reference to
    //       the anim value in question
    //-------------------------------------------------------------------------
    inline unsigned short& panimvalue( int nindex0, int nindex1 ) const
    {
        // clamp indexes
        if ( nindex0 >= groupsize [ 0 ] )
            nindex0 = groupsize [ 0 ] - 1;

        if ( nindex1 >= groupsize [ 1 ] )
            nindex1 = groupsize [ 1 ] - 1;

        return *pblend( nindex1 * groupsize [ 0 ] + nindex0 );
    }

    int	numblends;

    int blendindex;
    inline unsigned short *pblend( int i ) const
    {
        return ( unsigned short * ) ( ( ( byte * ) this ) + blendindex ) + i;
    };

    int seqgroup; // sequence group for demand loading

    int	groupsize [ 2 ];
    int	paramindex [ 2 ];	// x, y, z, xr, yr, zr
    float	paramstart [ 2 ];	// local (0..1) starting value
    float	paramend [ 2 ];	// local (0..1) ending value
    int	paramparent;

    float	fadeintime;	// ideal cross fate in time (0.2 default)
    float	fadeouttime;	// ideal cross fade out time (0.2 default)

    int	entrynode;	// transition node at entry
    int	exitnode;	// transition node at exit
    int	nodeflags;	// transition rules

    float	entryphase;	// used to match entry gait
    float	exitphase;	// used to match exit gait

    float	lastframe;	// frame that should generation endofsequence

    int	nextseq;	// auto advancing sequences
    int	pose;		// index of delta animation between end and nextseq

    int	numikrules;

    int	numautolayers;
    int	autolayerindex;
    inline void *pautolayer( int i ) const
    {
        return ( ( ( byte * ) this ) + autolayerindex ) + i;
    };

    int	weightlistindex;
    float	*pboneweight( int i ) const
    {
        return ( ( float * ) ( ( ( byte * ) this ) + weightlistindex ) + i );
    };
    float	weight( int i ) const
    {
        return *( pboneweight( i ) );
    };

    int	posekeyindex;
    float				*pposekey( int iparam, int ianim ) const
    {
        return ( float * ) ( ( ( byte * ) this ) + posekeyindex ) + iparam * groupsize [ 0 ] + ianim;
    }
    float				posekey( int iparam, int ianim ) const
    {
        return *( pposekey( iparam, ianim ) );
    }

    int	numiklocks;
    int	iklockindex;
    inline void *piklock( int i ) const
    {
        return ( ( ( byte * ) this ) + iklockindex ) + i;
    };

    // key values
    int	keyvalueindex;
    int	keyvaluesize;
    inline const char * keyvaluetext( void ) const
    {
        return keyvaluesize != 0 ? ( ( char * ) this ) + keyvalueindex : NULL;
    }

    int	unused [ 3 ];		// remove/add as appropriate
};

struct studiohdr_t
{
    int	id;
    int	version;

    long checksum;	// this has to be the same in the phy and vtx files to load!

    char name [ 64 ];
    int	length;

    vec3_t	eyeposition;	// ideal eye position

    vec3_t	illumposition;	// illumination center

    vec3_t	hull_min;	// ideal movement hull size
    vec3_t	hull_max;

    vec3_t	view_bbmin;	// clipping bounding box
    vec3_t	view_bbmax;

    int	flags;

    int	numbones;	// bones
    int	boneindex;
    inline mstudiobone_t *pbone( int i ) const
    {
        return ( mstudiobone_t * ) ( ( ( byte * ) this ) + boneindex ) + i;
    };

    int	numbonecontrollers;	// bone controllers
    int	bonecontrollerindex;
    inline void *pbonecontroller( int i ) const
    {
        return ( ( ( byte * ) this ) + bonecontrollerindex ) + i;
    };

    int	numhitboxsets;
    int	hitboxsetindex;

    // look up hitbox set by index
    mstudiohitboxset_t  *phitboxset( int i ) const
    {
        return ( mstudiohitboxset_t * ) ( ( ( byte * ) this ) + hitboxsetindex ) + i;
    };

    // calls through to hitbox to determine size of specified set
    inline mstudiobbox_t *phitbox( int i, int set ) const
    {
        mstudiohitboxset_t *s = phitboxset( set );

        if ( !s )
            return NULL;

        return s->get_hitbox( i );
    };

    // calls through to set to get hitbox count for set
    inline int  ihitboxcount( int set ) const
    {
        mstudiohitboxset_t const *s = phitboxset( set );
        if ( !s )
            return 0;

        return s->numhitboxes;
    };

    int	numanim;	// animations/poses
    int	animdescindex;	// animation descriptions
    inline void *panimdesc( int i ) const
    {
        return ( ( ( byte * ) this ) + animdescindex ) + i;
    };

    int 	numanimgroup;
    int 	animgroupindex;
    inline  void *panimgroup( int i ) const
    {
        return ( ( ( byte * ) this ) + animgroupindex ) + i;
    };

    int 	numbonedesc;
    int 	bonedescindex;
    inline  void *pbonedesc( int i ) const
    {
        return ( ( ( byte * ) this ) + bonedescindex ) + i;
    };

    int	numseq;		// sequences
    int	seqindex;
    inline mstudioseqdesc_t *pseqdesc( int i ) const
    {
        if ( i < 0 || i >= numseq ) i = 0; return ( mstudioseqdesc_t * ) ( ( ( byte * ) this ) + seqindex ) + i;
    };
    int	sequencesindexed;	// initialization flag - have the sequences been indexed?

    int	numseqgroups;		// demand loaded sequences
    int	seqgroupindex;
    inline  void *pseqgroup( int i ) const
    {
        return ( ( ( byte * ) this ) + seqgroupindex ) + i;
    };

    int	numtextures;		// raw textures
    int	textureindex;
    inline void *ptexture( int i ) const
    {
        return ( ( ( byte * ) this ) + textureindex ) + i;
    };

    int	numcdtextures;		// raw textures search paths
    int	cdtextureindex;
    inline char			*pcdtexture( int i ) const
    {
        return ( ( ( char * ) this ) + *( ( int * ) ( ( ( byte * ) this ) + cdtextureindex ) + i ) );
    };

    int	numskinref;		// replaceable textures tables
    int	numskinfamilies;
    int	skinindex;
    inline short		*pskinref( int i ) const
    {
        return ( short * ) ( ( ( byte * ) this ) + skinindex ) + i;
    };

    int	numbodyparts;
    int	bodypartindex;
    inline void	*pbodypart( int i ) const
    {
        return ( ( ( byte * ) this ) + bodypartindex ) + i;
    };

    int	numattachments;		// queryable attachable points
    int	attachmentindex;
    inline void	*pattachment( int i ) const
    {
        return ( ( ( byte * ) this ) + attachmentindex ) + i;
    };

    int	numtransitions;		// animation node to animation node transition graph
    int	transitionindex;
    inline byte	*ptransition( int i ) const
    {
        return ( byte * ) ( ( ( byte * ) this ) + transitionindex ) + i;
    };

    int	numflexdesc;
    int	flexdescindex;
    inline void *pflexdesc( int i ) const
    {
        return ( ( ( byte * ) this ) + flexdescindex ) + i;
    };

    int	numflexcontrollers;
    int	flexcontrollerindex;
    inline void *pflexcontroller( int i ) const
    {
        return ( ( ( byte * ) this ) + flexcontrollerindex ) + i;
    };

    int	numflexrules;
    int	flexruleindex;
    inline void *pflexrule( int i ) const
    {
        return ( ( ( byte * ) this ) + flexruleindex ) + i;
    };

    int	numikchains;
    int	ikchainindex;
    inline void *pikchain( int i ) const
    {
        return ( ( ( byte * ) this ) + ikchainindex ) + i;
    };

    int	nummouths;
    int	mouthindex;
    inline void *pmouth( int i ) const
    {
        return ( ( ( byte * ) this ) + mouthindex ) + i;
    };

    int	numposeparameters;
    int	poseparamindex;
    inline void *pposeparameter( int i ) const
    {
        return ( ( ( byte * ) this ) + poseparamindex ) + i;
    };

    int	surfacepropindex;
    inline char * const pszsurfaceprop( void ) const
    {
        return ( ( char * ) this ) + surfacepropindex;
    }

    // key values
    int	keyvalueindex;
    int	keyvaluesize;
    inline const char * keyvaluetext( void ) const
    {
        return keyvaluesize != 0 ? ( ( char * ) this ) + keyvalueindex : NULL;
    }

    int	numikautoplaylocks;
    int	ikautoplaylockindex;
    inline void *pikautoplaylock( int i ) const
    {
        return ( ( ( byte * ) this ) + ikautoplaylockindex ) + i;
    };

    float mass;		// the collision model mass that jay wanted
    int	contents;
    int	unused [ 9 ];	// remove as appropriate
};