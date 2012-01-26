#include "VBSpline2DBezierCubic.h"
#include "../../IO/VBSystem.h"
#include <float.h>
#include "../VBMath.h"
#include "../../VBEngine.h"

VBSpline2DBezierCubic* VBSpline2DBezierCubicAlloc(void) {
    VBSpline2DBezierCubic* _bezier = VBSystemCalloc(1, sizeof(VBSpline2DBezierCubic));
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicAlloc() - ");
#endif
    
    return _bezier;
}

VBSpline2DBezierCubic* VBSpline2DBezierCubicInit(VBSpline2DBezierCubic* _bezier) {
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicInit() - ");
#endif
    
    _bezier->begin = VBVector2DCreate(0.0f, 0.0f);
    _bezier->begin_control = VBVector2DCreate(0.0f, 0.0f);
    _bezier->end_control = VBVector2DCreate(0.0f, 0.0f);
    _bezier->end = VBVector2DCreate(0.0f, 0.0f);
    return _bezier;
}

VBSpline2DBezierCubic* VBSpline2DBezierCubicInitWithVector(VBSpline2DBezierCubic* _bezier,
                                                           VBVector2D _begin,
                                                           VBVector2D _begin_control,
                                                           VBVector2D _end_control,
                                                           VBVector2D _end) {
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicInitWithVector() - ");
#endif
    
    _bezier->begin = _begin;
    _bezier->begin_control = _begin_control;
    _bezier->end_control = _end_control;
    _bezier->end = _end;
    return _bezier;
}

void VBSpline2DBezierCubicFree(VBSpline2DBezierCubic** _bezier) {
#ifdef _VB_DEBUG_
    if(*_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicFree() - ");
#endif
    
    VBSystemFree(*_bezier);
    *_bezier = VBNull;
}

VBVector2D VBSpline2DBezierCubicGetVector2D(VBSpline2DBezierCubic* _bezier, VBFloat _t) {
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicGetVector2D() - ");
#endif
    
    VBFloat _tf = 1.0f - _t;
    VBFloat _tf2 = _tf * _tf;
    VBFloat _tf3 = _tf2 * _tf;
    VBFloat _t2 = _t * _t;
    VBFloat _t3 = _t2 * _t;
    
    VBFloat _tarr[4];
    _tarr[0] = _tf3;
    _tarr[1] = 3.0f * _tf2 * _t;
    _tarr[2] = 3.0f * _tf * _t2;
    _tarr[3] = _t3;
    
    VBVector2D _parr[4];
    _parr[0] = VBVector2DMultiply(_bezier->begin, _tarr[0]);
    _parr[1] = VBVector2DMultiply(_bezier->begin_control, _tarr[1]);
    _parr[2] = VBVector2DMultiply(_bezier->end_control, _tarr[2]);
    _parr[3] = VBVector2DMultiply(_bezier->end, _tarr[3]);
    
    return VBVector2DAdd(_parr[0], VBVector2DAdd(_parr[1], VBVector2DAdd(_parr[2], _parr[3])));
}

VBBool VBSpline2DBezierCubicIsNearestCollisionLine2D(VBSpline2DBezierCubic* _bezier, VBLine2D _line, VBVector2D* _collision_vector) {
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicIsNearestCollisionLine2D() - ");
    if(_collision_vector == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicIsNearestCollisionLine2D() - ");
#endif
    
    //베지어곡선 점4개
    VBVector2D _p[4];
    _p[0] = _bezier->begin;
    _p[1] = _bezier->begin_control;
    _p[2] = _bezier->end_control;
    _p[3] = _bezier->end;
    
    //베지어곡선 3차방정식 정리
    //3차 베지어곡선 공식:(1-t)*(1-t)*(1-t)*_p[0]+3*(1-t)*(1-t)*_t*_p[1]+3*(1-t)*_t*_t*_p[2]+_t*_t*_t*_p[3]
    //3차방정식 정리:_v[0]*_t*_t*_t+_v[1]*_t*_t+_v[2]*_t+_v[3]
    VBVector2D _v[4];
    _v[0].x = -_p[0].x + 3.0f * _p[1].x - 3.0f * _p[2].x + _p[3].x;
    _v[0].y = -_p[0].y + 3.0f * _p[1].y - 3.0f * _p[2].y + _p[3].y;
    _v[1].x = 3.0f * _p[0].x - 6.0f * _p[1].x + 3.0f * _p[2].x;
    _v[1].y = 3.0f * _p[0].y - 6.0f * _p[1].y + 3.0f * _p[2].y;
    _v[2].x = -3.0f * _p[0].x + 3.0f * _p[1].x;
    _v[2].y = -3.0f * _p[0].y + 3.0f * _p[1].y;
    _v[3] = _p[0];
    
    //베지어곡선 3차방정식과 라인의 1차방정식의 충돌검출위한 정리
    //_a:라인의 길이벡터
    //_b:시작지점
    //_s:라인충돌지점
    //_v[0]*_t*_t*_t+_v[1]*_t*_t+_v[2]*_t+_v[3]=_b+_a*_s
    //일때
    //(_v[0].x*_t*_t*_t+_v[1].x*_t*_t+_v[2].x*_t+_v[3].x-_b.x)/_a.x=(_v[0].y*_t*_t*_t+_v[1].y*_t*_t+_v[2].y*_t+_v[3].y-_b.y)/_a.y
    //에서 우변을 모두 좌변으로 이동하고 다시 3차방정식 정리:_abcd[0]*_t*_t*_t+_abcd[1]*_t*_t+_abcd[2]*_t+_abcd[3]
    VBVector2D _a = VBVector2DSubtract(_line.end, _line.begin);
    VBVector2D _b = _line.begin;
    VBFloat _abcd[4];
    _abcd[0] = _a.y * _v[0].x - _a.x * _v[0].y;
    _abcd[1] = _a.y * _v[1].x - _a.x * _v[1].y;
    _abcd[2] = _a.y * _v[2].x - _a.x * _v[2].y;
    _abcd[3] = _a.y * _v[3].x - _a.x * _v[3].y - _a.y * _b.x + _a.x * _b.y;
        
    //시작지점에 가장가까운 _s
    VBFloat _min_s = FLT_MAX;
    VBBool _is_found_result = VBFalse;
    
    //근의 공식을 이용한 베지어곡선의 t구하기
    VBMathFxFloatSet* _fxs = VBMathFxFloatSetInit(VBMathFxFloatSetAlloc());
    if(_abcd[0] != 0) {
        VBMathCubicEquationGetFx(_abcd[0], _abcd[1], _abcd[2], _abcd[3], _fxs);
    } else if(_abcd[1] != 0) {
        VBMathQuadraticEquationGetFx(_abcd[1], _abcd[2], _abcd[3], _fxs);
    } else if(_abcd[2] != 0) {
        VBMathLinearEquationGetFx(_abcd[2], _abcd[3], _fxs);
    } else if(_abcd[3] != 0) {
        return VBFalse;
    } else {
        //_t가 0이고
        //_v[0]*_t*_t*_t+_v[1]*_t*_t+_v[2]*_t+_v[3]=_b+_a*_s이므로 _s는
        VBFloat _s = (_v[3].x - _b.x) / _a.x;
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
                
        //_v[0]*_t*_t*_t+_v[1]*_t*_t+_v[2]*_t+_v[3]=_b+_a*_s이므로 _s는
        
        VBFloat _s;
        if(_a.x == 0)
            _s = (_v[0].y * _t * _t * _t + _v[1].y * _t * _t + _v[2].y * _t + _v[3].y - _b.y) / _a.y;
        else
            _s = (_v[0].x * _t * _t * _t + _v[1].x * _t * _t + _v[2].x * _t + _v[3].x - _b.x) / _a.x;
        
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

VBFloat VBSpline2DBezierCubicGetTByBtx(VBSpline2DBezierCubic* _bezier, VBFloat _btx) {
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicGetTByBtx() - ");
#endif
    
    //베지어 곡선의 x축만 가지고 있는 B(tX)의 해 t를 구한다.
    //B(tX) = (1-t)*(1-t)*(1-t)*_X[0]+3*(1-t)*(1-t)*_t*_X[1]+3*(1-t)*_t*_t*_X[2]+_t*_t*_t*_X[3]

    //베지어 곡선 점 4개
    VBVector2D _p[4];
    _p[0] = _bezier->begin;
    _p[1] = _bezier->begin_control;
    _p[2] = _bezier->end_control;
    _p[3] = _bezier->end;
    
    //x[0], x[1], x[2], x[3]의 값을 구한다
    //_b(tx) = _v[0].x * _t^3 + _v[1].x * _t^2 + _v[2].x * _t + _v[3].x
    VBVector2D _v[4];
    _v[0].x = -_p[0].x + 3.0f * _p[1].x - 3.0f * _p[2].x + _p[3].x;
    _v[1].x = 3.0f * _p[0].x - 6.0f * _p[1].x + 3.0f * _p[2].x;
    _v[2].x = -3.0f * _p[0].x + 3.0f * _p[1].x;
    _v[3].x = _p[0].x - _btx;
 
    VBMathFxFloatSet* _fxs = VBMathFxFloatSetInit(VBMathFxFloatSetAlloc());
    if(_v[0].x != 0) {
        VBMathCubicEquationGetFx(_v[0].x, _v[1].x, _v[2].x, _v[3].x, _fxs);
    }else if(_v[1].x != 0) {
        VBMathQuadraticEquationGetFx(_v[1].x, _v[2].x, _v[3].x, _fxs);
    }else if(_v[2].x != 0) {
        VBMathLinearEquationGetFx(_v[2].x, _v[3].x, _fxs);
    }
    
    VBFloat _t = 0;
    VBFloat _tmp = 0;
    VBMathFxFloat* _fx;
	VBLong i = 0;
    for(i; i < VBMathFxFloatSetGetLength(_fxs); i++) {
        _fx = VBMathFxFloatSetGetFxAt(_fxs, i);
        if(VBMathFxFloatGetType(_fx) != VBMathFxFloatType_Real)
            continue;
        _tmp = VBMathFxFloatGetFxReal(_fx);
        if(_tmp >= 0.0f && _tmp <= 1.0f) { // _t = 0.0f ~ 1.0f
            _t = _tmp;
        }
    }
    VBMathFxFloatSetFree(&_fxs);

    return _t;
}

VBFloat VBSpline2DBezierCubicGetBtyByT(VBSpline2DBezierCubic* _bezier, VBFloat _t) {    
#ifdef _VB_DEBUG_
    if(_bezier == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBSpline2DBezierCubicGetBtyByT() - ");
#endif
    
    //t를 구하면 y축 베지어 곡선의 B(ty)에 대입하여 y를 구한다
    //B(tY) = (1-t)*(1-t)*(1-t)*_Y[0]+3*(1-t)*(1-t)*_t*_Y[1]+3*(1-t)*_t*_t*_Y[2]+_t*_t*_t*_Y[3]
    
    //베지어 곡선 점 4개
    VBVector2D _p[4];
    _p[0] = _bezier->begin;
    _p[1] = _bezier->begin_control;
    _p[2] = _bezier->end_control;
    _p[3] = _bezier->end;
    
    VBVector2D _v[4];
    _v[0].y = (1.0f - _t) * (1.0f - _t) * (1.0f - _t) * _p[0].y;
    _v[1].y = 3.0f * (1.0f - _t) * (1.0f - _t) * _t * _p[1].y;
    _v[2].y = 3.0f * (1.0f - _t) * _t * _t * _p[2].y;
    _v[3].y = _t * _t * _t * _p[3].y;
    
    return _v[0].y + _v[1].y + _v[2].y + _v[3].y;
}


