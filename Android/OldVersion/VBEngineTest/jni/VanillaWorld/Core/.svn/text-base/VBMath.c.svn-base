#include "VBMath.h"
#include "../IO/VBSystem.h"
#include "VBArrayVector.h"
#include <math.h>
#include "../VBEngine.h"

VBMathFxFloat* _VBMathFxFloatAlloc(void);
VBMathFxFloat* _VBMathFxFloatInit(VBMathFxFloat* _fx);
VBMathFxFloat* _VBMathFxFloatInitWithNaNType(VBMathFxFloat* _fx);
VBMathFxFloat* _VBMathFxFloatInitWithRealType(VBMathFxFloat* _fx, VBFloat _x);
VBMathFxFloat* _VBMathFxFloatInitWithComplexType(VBMathFxFloat* _fx, VBFloat _real_x, VBFloat _imaginary_x);
VBMathFxFloat* _VBMathFxFloatInitWithImaginaryType(VBMathFxFloat* _fx, VBFloat _imaginary_x);
void _VBMathFxFloatFree(VBMathFxFloat** _fx);

VBFloat _VBMathCubeRoot(VBFloat _x);

VBMathFxFloatSet* VBMathFxFloatSetAlloc(void) {
    VBMathFxFloatSet* _fxs = VBSystemCalloc(1, sizeof(VBMathFxFloatSet));
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatSetAlloc() - 메모리를 할당할 수 없습니다.");
#endif
    _fxs->fx = VBArrayVectorAlloc();
    return _fxs;
}

VBMathFxFloatSet* VBMathFxFloatSetInit(VBMathFxFloatSet* _fxs) {
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatSetInit() - ");
#endif

    while(VBArrayVectorGetLength(_fxs->fx)) {
        VBMathFxFloat* _fx = VBArrayVectorRemoveBack(_fxs->fx);
        _VBMathFxFloatFree(&_fx);
    }
    _fxs->fx = VBArrayVectorInit(_fxs->fx);
    return _fxs;
}

void VBMathFxFloatSetFree(VBMathFxFloatSet** _fxs) {
#ifdef _VB_DEBUG_
    if(*_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatSetFree() - ");
#endif
    
    *_fxs = VBMathFxFloatSetInit(*_fxs);
    VBArrayVectorFree(&(*_fxs)->fx);
    VBSystemFree(*_fxs);
    *_fxs = VBNull;
}

VBULong VBMathFxFloatSetGetLength(VBMathFxFloatSet* _fxs) {
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatSetGetLength() - ");
#endif
    
    return VBArrayVectorGetLength(_fxs->fx);
}

VBMathFxFloat* VBMathFxFloatSetGetFxAt(VBMathFxFloatSet* _fxs, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatSetGetFxAt() - ");
#endif
    
    return VBArrayVectorGetDataAt(_fxs->fx, _at);
}

VBMathFxFloat* _VBMathFxFloatAlloc(void) {
    VBMathFxFloat* _fx = VBSystemCalloc(1, sizeof(VBMathFxFloat));
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatAlloc() - ");
#endif
    
    return _fx;
}

VBMathFxFloat* _VBMathFxFloatInit(VBMathFxFloat* _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatInit() - ");
#endif

    _fx->type = VBMathFxFloatType_None;
    _fx->x.real = 0.0f;
    return _fx;
}

VBMathFxFloat* _VBMathFxFloatInitWithNaNType(VBMathFxFloat* _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatInitWithNaNType() - ");
#endif

    _fx = _VBMathFxFloatInit(_fx);
    _fx->type = VBMathFxFloatType_NaN;
    return _fx;
}

VBMathFxFloat* _VBMathFxFloatInitWithRealType(VBMathFxFloat* _fx, VBFloat _x) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatInitWithRealType() - ");
#endif

    _fx = _VBMathFxFloatInit(_fx);
    _fx->type = VBMathFxFloatType_Real;
    _fx->x.real = _x;
    return _fx;
}

VBMathFxFloat* _VBMathFxFloatInitWithComplexType(VBMathFxFloat* _fx, VBFloat _real_x, VBFloat _imaginary_x) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatInitWithComplexType() - ");
#endif

    _fx = _VBMathFxFloatInit(_fx);
    _fx->type = VBMathFxFloatType_Complex;
    _fx->x.real = _real_x;
    _fx->x.imag = _imaginary_x;
    return _fx;
}

VBMathFxFloat* _VBMathFxFloatInitWithImaginaryType(VBMathFxFloat* _fx, VBFloat _imaginary_x) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatInitWithImaginaryType() - ");
#endif

    _fx = _VBMathFxFloatInit(_fx);
    _fx->type = VBMathFxFloatType_Imaginary;
    _fx->x.imag = _imaginary_x;
    return _fx;
}

void _VBMathFxFloatFree(VBMathFxFloat** _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: _VBMathFxFloatFree() - ");
#endif

    VBSystemFree(*_fx);
    *_fx = VBNull;
}

VBMathFxFloatType VBMathFxFloatGetType(VBMathFxFloat* _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatGetType() - ");
#endif

    return _fx->type;
}

VBFloat VBMathFxFloatGetFxReal(VBMathFxFloat* _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatGetFxReal() - ");
#endif

    return _fx->x.real;
}

VBFloat VBMathFxFloatGetFxImagenary(VBMathFxFloat* _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatGetFxImagenary() - ");
#endif

    return _fx->x.imag;
}

VBFloatComplex VBMathFxFloatGetFxComplex(VBMathFxFloat* _fx) {
#ifdef _VB_DEBUG_
    if(_fx == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathFxFloatGetFxComplex() - ");
#endif

    return _fx->x;
}

void VBMathLinearEquationGetFx(VBFloat _a, VBFloat _b, VBMathFxFloatSet* _fxs) {
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathLinearEquationGetFx() - ");
#endif

    VBMathFxFloatSetInit(_fxs);
    VBMathFxFloat* _x = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), -_b / _a);
    VBArrayVectorAddBack(_fxs->fx, _x);
}

void VBMathQuadraticEquationGetFx(VBFloat _a, VBFloat _b, VBFloat _c, VBMathFxFloatSet* _fxs) {
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathQuadraticEquationGetFx() - ");
#endif

    VBMathFxFloatSetInit(_fxs);
    VBFloat _d = _b * _b - 4.0f * _a * _c;
    if(_d >= 0.0f) {
        VBFloat _r = sqrtf(_d);
        VBMathFxFloat* _x1 = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), (-_b / (2.0f * _a)) + (_r / (2.0f * _a)));
        VBArrayVectorAddBack(_fxs->fx, _x1);
        VBMathFxFloat* _x2 = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), (-_b / (2.0f * _a)) - (_r / (2.0f * _a)));
        VBArrayVectorAddBack(_fxs->fx, _x2);
    } else {
        VBFloat _r = sqrtf(-_d);
        VBFloat _v1 = -_b / (2.0f * _a);
        VBFloat _v2 = _r / (2.0f * _a);
        if(_v2 >= 0.0f) {
            VBMathFxFloat* _x1 = _VBMathFxFloatInitWithComplexType(_VBMathFxFloatAlloc(), _v1, _v2);
            VBArrayVectorAddBack(_fxs->fx, _x1);
            VBMathFxFloat* _x2 = _VBMathFxFloatInitWithComplexType(_VBMathFxFloatAlloc(), _v1, -_v2);
            VBArrayVectorAddBack(_fxs->fx, _x2);
        } else {
            _v2 = -_v2;
            VBMathFxFloat* _x1 = _VBMathFxFloatInitWithComplexType(_VBMathFxFloatAlloc(), _v1, -_v2);
            VBArrayVectorAddBack(_fxs->fx, _x1);
            VBMathFxFloat* _x2 = _VBMathFxFloatInitWithComplexType(_VBMathFxFloatAlloc(), _v1, _v2);
            VBArrayVectorAddBack(_fxs->fx, _x2);
        }
    }
}

VBFloat _VBMathCubeRoot(VBFloat _x) {
    if(_x < 0)
        return -powf(-_x, 1.0f / 3.0f);
    else
        return powf(_x, 1.0f / 3.0f);
}

void VBMathCubicEquationGetFx(VBFloat _a, VBFloat _b, VBFloat _c, VBFloat _d, VBMathFxFloatSet* _fxs) {
#ifdef _VB_DEBUG_
    if(_fxs == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBMathCubicEquationGetFx() - ");
#endif

    VBMathFxFloatSetInit(_fxs);
    VBFloat _f, _g, _h;
    _f = (3.0f * _c / _a - powf(_b, 2.0f) / powf(_a, 2.0f)) / 3.0f;
    _g = (2.0f * powf(_b, 3.0f) / powf(_a, 3.0f) - 9.0f * _b * _c / powf(_a, 2.0f) + 27.0f * _d / _a) / 27.0f;
    _h = powf(_g, 2.0f) / 4.0f + powf(_f, 3.0f) / 27.0f;
    
    if(_f == 0.0f && _g == 0.0f && _h == 0.0f) {
        VBMathFxFloat* _x = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), -_VBMathCubeRoot(_d / _a));
        VBArrayVectorAddBack(_fxs->fx, _x);
    } else if(_h <= 0) {
        VBFloat _i, _j, _k, _m, _n, _p;
        _i = powf(powf(_g, 2.0f) / 4.0f - _h, 0.5f);
        _j = _VBMathCubeRoot(_i);
        _k = acosf(-(_g / (2.0f * _i)));
        _m = cosf(_k / 3.0f);
        _n = sqrtf(3.0f) * sinf(_k / 3.0f);
        _p = -(_b / (3.0f * _a));
        VBMathFxFloat* _x1 = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), 2.0f * _j * _m + _p);
        VBArrayVectorAddBack(_fxs->fx, _x1);
        VBMathFxFloat* _x2 = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), -_j * (_m + _n) + _p);
        VBArrayVectorAddBack(_fxs->fx, _x2);
        VBMathFxFloat* _x3 = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), -_j * (_m - _n) + _p);
        VBArrayVectorAddBack(_fxs->fx, _x3);
    } else if(_h > 0) {
        VBFloat _r, _s, _t, _u, _p;
        _r = -(_g / 2.0f) + powf(_h, 0.5f);
        _s = _VBMathCubeRoot(_r);
        _t = -(_g / 2.0f) - powf(_h, 0.5f);
        _u = _VBMathCubeRoot(_t);
        _p = -(_b / (3.0f * _a));
        VBMathFxFloat* _x1 = _VBMathFxFloatInitWithRealType(_VBMathFxFloatAlloc(), (_s + _u) + _p);
        VBArrayVectorAddBack(_fxs->fx, _x1);
        VBMathFxFloat* _x2 = _VBMathFxFloatInitWithComplexType(_VBMathFxFloatAlloc(), -(_s + _u) / 2.0f + _p, (_s - _u) * sqrtf(3.0f) / 2.0f);
        VBArrayVectorAddBack(_fxs->fx, _x2);
        VBMathFxFloat* _x3 = _VBMathFxFloatInitWithComplexType(_VBMathFxFloatAlloc(), -(_s + _u) / 2.0f + _p, -(_s - _u) * sqrtf(3.0f) / 2.0f);
        VBArrayVectorAddBack(_fxs->fx, _x3);
    }
}