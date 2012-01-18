#ifndef __VBAABB_H__
#define __VBAABB_H__

#include "../../VBType.h"
#include "VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct VBAABB VBAABB;
    struct VBAABB {
        VBFloat l, t, r, b;
    };
    
    VBAABB VBAABBCreateWithVertex(VBVector2D* _vtx, VBULong _vtx_len);
    
    float VBAABBGetWidth(VBAABB _aabb);
    
    float VBAABBGetHeight(VBAABB _aabb);
    
    VBAABB VBAABBLoadIndentity(void);
    
    VBAABB VBAABBCreate(VBFloat _l, VBFloat _t, VBFloat _r, VBFloat _b);
    
    VBBool VBAABBHitTestWithVector2D(VBAABB _aabb, VBVector2D _position);
    
    VBBool VBAABBHitTest(VBAABB _aabb1, VBAABB _aabb2);
    
    VBAABB VBAABBMerge(VBAABB _aabb1, VBAABB _aabb2);
    
    VBBool VBAABBIsIn(VBAABB _aabb1, VBAABB _aabb2);

#ifdef __cplusplus
}
#endif

#endif