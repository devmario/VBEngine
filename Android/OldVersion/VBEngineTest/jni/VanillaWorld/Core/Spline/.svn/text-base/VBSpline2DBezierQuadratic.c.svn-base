#include "VBSpline2DBezierQuadratic.h"
#include "../../IO/VBSystem.h"
#include <float.h>
#include "../VBMath.h"

VBSpline2DBezierQuadratic* VBSpline2DBezierQuadraticAlloc(void) {
    VBSpline2DBezierQuadratic* _bezier = VBSystemCalloc(1, sizeof(VBSpline2DBezierQuadratic));
    return _bezier;
}

VBSpline2DBezierQuadratic* VBSpline2DBezierQuadraticInit(VBSpline2DBezierQuadratic* _bezier) {
    if(_bezier) {
        _bezier->begin = VBVector2DCreate(0.0f, 0.0f);
        _bezier->control = VBVector2DCreate(0.0f, 0.0f);
        _bezier->end = VBVector2DCreate(0.0f, 0.0f);
    }
    return _bezier;
}

VBSpline2DBezierQuadratic* VBSpline2DBezierQuadraticInitWithVector(VBSpline2DBezierQuadratic* _bezier,
                                                                   VBVector2D _begin,
                                                                   VBVector2D _control,
                                                                   VBVector2D _end) {
    _bezier = VBSpline2DBezierQuadraticInit(_bezier);
    _bezier->begin = _begin;
    _bezier->control = _control;
    _bezier->end = _end;
    return _bezier;
}

void VBSpline2DBezierQuadraticFree(VBSpline2DBezierQuadratic** _bezier) {
    *_bezier = VBSpline2DBezierQuadraticInit(*_bezier);
    if(*_bezier) {
        VBSystemFree(*_bezier);
        *_bezier = VBNull;
    }
}

VBVector2D VBSpline2DBezierQuadraticGetVector2D(VBSpline2DBezierQuadratic* _bezier, VBFloat _t) {
    VBVector2D _b_control_multi = VBVector2DMultiply(_bezier->control, 2);
    VBVector2D _b1 = VBVector2DMultiply(VBVector2DMultiply(VBVector2DAdd(VBVector2DSubtract(_bezier->begin, _b_control_multi), _bezier->end), _t), _t);
    VBVector2D _b2 = VBVector2DMultiply(VBVector2DSubtract(_b_control_multi, VBVector2DMultiply(_bezier->begin, 2)), _t);
    
    return VBVector2DAdd(VBVector2DAdd(_b1, _b2), _bezier->begin);
}

VBBool VBSpline2DBezierQuadraticIsNearestCollisionLine2D(VBSpline2DBezierQuadratic* _bezier, VBLine2D _line, VBVector2D* _collision_vector) {
    //베지어곡선 점3개
    VBVector2D _p[3];
    _p[0] = _bezier->begin;
    _p[1] = _bezier->control;
    _p[2] = _bezier->end;
    
    //베지어곡선 2차방정식 정리
    //2차 베지어곡선 공식:(1-_t)*(1-_t)*_p[0]+2*(1-_t)*_t*_p[1]+_t*_t*_p[2]
    //2차방정식 정리:_v[0]*_t*_t+_v[1]*_t+_v[2]
    VBVector2D _v[3];
    _v[0] = VBVector2DAdd(VBVector2DSubtract(_p[0], VBVector2DMultiply(_p[1], 2.0f)), _p[2]);
    _v[1] = VBVector2DSubtract(VBVector2DMultiply(_p[1], 2.0f), VBVector2DMultiply(_p[0], -2.0f));
    _v[2] = _p[0];
    
    //베지어곡선 2차방정식과 라인의 1차방정식의 충돌검출위한 정리
    //_a:라인의 길이벡터
    //_b:시작지점
    //_s:라인충돌지점
    //_v[0]*_t*_t+_v[1]*_t+_v[2]=_b+_a*_s
    //일때
    //(_v[0].x*_t*_t+_v[1].x*_t+_v[2].x-_b.x)/_a.x=(_v[0].y*_t*_t+_v[1].y*_t+_v[2].y-_b.y)/_a.y
    //에서 우변을 모두 좌변으로 이동하고 다시 3차방정식 정리:_abc[0]*_t*_t+_abc[1]*_t+_abc[2]
    VBVector2D _a = VBVector2DSubtract(_line.end, _line.begin);
    VBVector2D _b = _line.begin;
    VBFloat _abc[3];
    _abc[0] = _a.y * _v[0].x - _a.x * _v[0].y;
    _abc[1] = _a.y * _v[1].x - _a.x * _v[1].y;
    _abc[2] = _a.y * _v[2].x - _a.x * _v[2].y - _a.y * _b.x + _a.x * _b.y;
    
    //시작지점에 가장가까운 _s
    VBFloat _min_s = FLT_MAX;
    VBBool _is_found_result = VBFalse;
    
    //근의 공식을 이용한 베지어곡선의 t구하기
    VBMathFxFloatSet* _fxs = VBMathFxFloatSetInit(VBMathFxFloatSetAlloc());
    if(_abc[0] != 0.0f) {
        VBMathQuadraticEquationGetFx(_abc[0], _abc[1], _abc[2], _fxs);
    } else if(_abc[1] != 0.0f) {
        VBMathLinearEquationGetFx(_abc[1], _abc[2], _fxs);
    } else if(_abc[2] != 0.0f) {
        return VBFalse;
    } else {
        //_t가 0이고
        //_v[0]*_t*_t+_v[1]*_t+_v[2]=_b+_a*_s이므로 _s는
        VBFloat _s = (_v[2].x - _b.x) / _a.x;
        //_s가 라인을 벗어날경우 제외
        if(_s >= 0.0f && _s <= 1.0f) {
            //시작지점에서 가장 가까운 점 검출
            if(_s < _min_s) {
                _min_s = _s;
                _is_found_result = VBTrue;
            }
        }
    }
    
    //베지어곡선이나 라인의 시작과 끝점을 벗어나는 값은 제외시키고 라인의 시작점과 가장가까운 값 검출
    VBULong _i;
    for(_i = 0; _i < VBMathFxFloatSetGetLength(_fxs); _i++) {
        //해가 실수가 아닌경우 제외
        VBMathFxFloat* _fx =  VBMathFxFloatSetGetFxAt(_fxs, _i);
        if(VBMathFxFloatGetType(_fx) != VBMathFxFloatType_Real)
            continue;
        
        VBFloat _t = VBMathFxFloatGetFxReal(_fx);
        //_t가 곡선을 벗어날경우 제외
        if(_t < 0.0f || _t > 1.0f)
            continue;
        
        //_v[0]*_t*_t+_v[1]*_t+_v[2]=_b+_a*_s이므로 _s는
        VBFloat _s = (_v[0].x * _t * _t + _v[1].x * _t + _v[2].x - _b.x) / _a.x;
        
        //_s가 라인을 벗어날경우 제외
        if(_s < 0.0f || _s > 1.0f)
            continue;
        
        //시작지점에서 가장 가까운 점 검출
        if(_s < _min_s) {
            _min_s = _s;
            _is_found_result = VBTrue;
        }
    }
    VBMathFxFloatSetFree(&_fxs);
    
    //값을찾지 못했으므로 충돌하지 않았다
    if(!_is_found_result) {
        return VBFalse;
    }
    
    //검출된 _s값으로 라인위의점 가져옴
    *_collision_vector = VBLine2DGetVector2D(_line, _min_s);
    return VBTrue;
}