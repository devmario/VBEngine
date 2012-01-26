#ifndef __VBAABB_H__
#define __VBAABB_H__

#include "../VBType.h"
#include "VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct VBAABB VBAABB;
    struct VBAABB {
        VBFloat l, t, r, b;
    };
    
    VBAABB VBAABBCreate(VBFloat _l, VBFloat _t, VBFloat _r, VBFloat _b);
    
    VBBool VBAABBHitTestWithVector2D(VBAABB _aabb, VBVector2D _position);

#ifdef __cplusplus
}
#endif

#endif