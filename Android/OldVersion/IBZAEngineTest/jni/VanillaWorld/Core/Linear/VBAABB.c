#include "VBAABB.h"
#include <limits.h>

VBAABB VBAABBCreateWithVertex(VBVector2D* _vtx, VBULong _vtx_len) {
    VBULong _i;
    VBVector2D* _vtx_ptr = _vtx;
    VBAABB _aabb = VBAABBLoadIndentity();
    for(_i = 0; _i < _vtx_len; _i++) {
        if(_vtx_ptr->x < _aabb.l)
            _aabb.l = _vtx_ptr->x;
        if(_vtx_ptr->y < _aabb.t)
            _aabb.t = _vtx_ptr->y;
        if(_vtx_ptr->x > _aabb.r)
            _aabb.r = _vtx_ptr->x;
        if(_vtx_ptr->y > _aabb.b)
            _aabb.b = _vtx_ptr->y;
        _vtx_ptr++;
    }
    return _aabb;
}

VBAABB VBAABBLoadIndentity(void) {
    return VBAABBCreate(__FLT_MAX__, __FLT_MAX__, __FLT_MIN__, __FLT_MIN__);
}

VBAABB VBAABBCreate(VBFloat _l, VBFloat _t, VBFloat _r, VBFloat _b) {
    VBAABB _aabb;
    _aabb.l = _l;
    _aabb.t = _t;
    _aabb.r = _r;
    _aabb.b = _b;
    return _aabb;
}

VBBool VBAABBHitTestWithVector2D(VBAABB _aabb, VBVector2D _position) {
    if(_position.x < _aabb.l)
        return VBFalse;
    if(_position.x > _aabb.r)
        return VBFalse;
    if(_position.y < _aabb.t)
        return VBFalse;
    if(_position.y > _aabb.b)
        return VBFalse;
    return VBTrue;
}

VBBool VBAABBHitTest(VBAABB _aabb1, VBAABB _aabb2) {
    if(_aabb1.r < _aabb2.l)
        return VBFalse;
    if(_aabb1.l > _aabb2.r)
        return VBFalse;
    if(_aabb1.b < _aabb2.t)
        return VBFalse;
    if(_aabb1.t > _aabb2.b)
        return VBFalse;
    return VBTrue;
}

VBAABB VBAABBMerge(VBAABB _aabb1, VBAABB _aabb2) {
    if(_aabb1.l > _aabb2.l)
        _aabb1.l = _aabb2.l;
    if(_aabb1.r < _aabb2.r)
        _aabb1.r = _aabb2.r;
    if(_aabb1.t > _aabb2.t)
        _aabb1.t = _aabb2.t;
    if(_aabb1.b < _aabb2.b)
        _aabb1.b = _aabb2.b;
    
    return _aabb1;
}

VBBool VBAABBIsIn(VBAABB _aabb1, VBAABB _aabb2) {
    if(_aabb1.l > _aabb2.l)
        return VBFalse;
    if(_aabb1.r < _aabb2.r)
        return VBFalse;
    if(_aabb1.t > _aabb2.t)
        return VBFalse;
    if(_aabb1.b < _aabb2.b)
        return VBFalse;
    return VBTrue;
}