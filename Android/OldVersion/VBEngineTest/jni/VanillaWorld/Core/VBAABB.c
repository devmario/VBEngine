#include "VBAABB.h"

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