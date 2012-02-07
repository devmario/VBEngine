#include "VBAABB.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

VBAABB* VBAABBMemResizeAndSet(VBAABB* aabb, VBAABB aabbVal, int idx, int size) {
    if(aabb == NULL)
        aabb = malloc(sizeof(VBAABB) * size);
    else
        aabb = realloc(aabb, sizeof(VBAABB) * size);
    aabb[idx] = aabbVal;
    return aabb;
}

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

float VBAABBGetWidth(VBAABB _aabb) {
    return _aabb.r - _aabb.l;
}

float VBAABBGetHeight(VBAABB _aabb) {
    return _aabb.b - _aabb.t;
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

VBAABB VBAABBShift(VBAABB _aabb, VBVector2D _vec) {
    _aabb.l += _vec.x;
    _aabb.t += _vec.y;
    _aabb.r += _vec.x;
    _aabb.b += _vec.y;
    return _aabb;
}

float VBAABBGetAmount(VBAABB _aabb) {
    return VBAABBGetWidth(_aabb) * VBAABBGetHeight(_aabb);
}

bool VBAABBGetHitAABB(VBAABB _aabb1, VBAABB _aabb2, VBAABB* _hitAABB) {
    bool isHit = VBAABBHitTest(_aabb1, _aabb2);
    if(isHit) {
        _hitAABB->l = fmaxf(_aabb1.l, _aabb2.l);
        _hitAABB->t = fmaxf(_aabb1.t, _aabb2.t);
        _hitAABB->r = fminf(_aabb1.r, _aabb2.r);
        _hitAABB->b = fminf(_aabb1.b, _aabb2.b);
    }
    return isHit;
}

bool VBAABBIsEqual(VBAABB _aabb1, VBAABB _aabb2) {
    if(_aabb1.l != _aabb2.l)
        return false;
    if(_aabb1.t != _aabb2.t)
        return false;
    if(_aabb1.r != _aabb2.r)
        return false;
    if(_aabb1.b != _aabb2.b)
        return false;
    return true;
}

float VBAABBGetAmountAtManyBox(int count, VBAABB* _aabb) {
    if(count == 0 || _aabb == NULL)
        return 0;
    
    //가장마지막 검사인지 확인
    //    int idx = 1;
    //    bool isLast = true;
    //    while(idx < count) {
    //        if(VBAABBIsEqual(_aabb[idx], _aabb[idx - 1]) == false) {
    //            isLast = false;
    //            break;
    //        }
    //        idx++;
    //    }
    //    if(isLast)
    //        return VBAABBGetAmount(_aabb[0]);
    
    //넓이 구하기 루프
    VBAABB* hitaabb = NULL;
    int hitaabbIdx = 0;
    float _amount = 0;
    for(int i = 0; i < count; i++) {
        _amount += VBAABBGetAmount(_aabb[i]);
        if(i != 0) {
            VBAABB hit;
            if(VBAABBGetHitAABB(_aabb[i], _aabb[i - 1], &hit)) {
                hitaabb = VBAABBMemResizeAndSet(hitaabb, hit, hitaabbIdx, ++hitaabbIdx);
            }
        }
    }
    
    //충돌되는 영역이 있을경우
    if(hitaabb) {
        _amount -= VBAABBGetAmountAtManyBox(hitaabbIdx, hitaabb);
        free(hitaabb);
    }
    
    return _amount;
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