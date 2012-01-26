#include "VBVector2D.h"
#include "../VBEngine.h"
#include <math.h>
#include <stdio.h>

VBVector2D VBVector2DCreate(VBFloat _x, VBFloat _y) {
	VBVector2D _vec2D;
	_vec2D.x = _x;
	_vec2D.y = _y;
	return _vec2D;
}

VBFloat VBVector2DGetX(VBVector2D _vec2D) {
	return _vec2D.x;
}

VBFloat VBVector2DGetY(VBVector2D _vec2D) {
	return _vec2D.y;
}

VBBool VBVector2DIsEqual(VBVector2D _vec2D_1, VBVector2D _vec2D_2) {
	if (_vec2D_1.x != _vec2D_2.x)
		return VBFalse;
	if (_vec2D_1.y != _vec2D_2.y)
		return VBFalse;
	return VBTrue;
}

VBVector2D VBVector2DNormal(VBVector2D _vec2D, VBFloat _thickness) {
	return VBVector2DDivide(_vec2D, VBVector2DLength(_vec2D) / _thickness);
}

VBVector2D VBVector2DAdd(VBVector2D _vec2D_1, VBVector2D _vec2D_2) {
	return VBVector2DCreate(_vec2D_1.x + _vec2D_2.x, 
							_vec2D_1.y + _vec2D_2.y);
}

VBVector2D VBVector2DSubtract(VBVector2D _vec2D_1, VBVector2D _vec2D_2) {
	return VBVector2DCreate(_vec2D_1.x - _vec2D_2.x, 
							_vec2D_1.y - _vec2D_2.y);
}

VBVector2D VBVector2DMultiply(VBVector2D _vec2D, VBFloat _num) {
	return VBVector2DCreate(_vec2D.x * _num, _vec2D.y * _num);
}

VBVector2D VBVector2DDivide(VBVector2D _vec2D, VBFloat _num) {
	return VBVector2DCreate(_vec2D.x / _num, _vec2D.y / _num);
}

VBFloat VBVector2DDotProduct(VBVector2D _vec2D_1, VBVector2D _vec2D_2) {
	return _vec2D_1.x * _vec2D_2.x + _vec2D_1.y * _vec2D_2.y;
}

VBFloat VBVector2DLength(VBVector2D _vec2D) {
	return sqrtf(VBVector2DDotProduct(_vec2D, _vec2D));
}

VBFloat VBVector2DDistance(VBVector2D _vec2D_1, VBVector2D _vec2D_2) {
	return VBVector2DLength(VBVector2DSubtract(_vec2D_1, _vec2D_2));
}

VBFloat VBVector2DAngle(VBVector2D _vec2D) {
	return atan2f(_vec2D.y, _vec2D.x);
}

VBFloat VBVector2DAngleTo(VBVector2D _vec2D_1, VBVector2D _vec2D_2) {
	return VBVector2DAngle(VBVector2DSubtract(_vec2D_2, _vec2D_1));
}

VBVector2D VBVector2DInterpolate(VBVector2D _vec2D_1, VBVector2D _vec2D_2, VBFloat _num) {
	VBVector2D _dir = VBVector2DSubtract(_vec2D_2, _vec2D_1);
	return VBVector2DCreate(_num * _dir.x + _vec2D_1.x, _num * _dir.y + _vec2D_1.y);
}

VBVector2D VBVector2DPolar(VBFloat _len, VBFloat _angle) {
	return VBVector2DCreate(_len * cosf(_angle), _len * sinf(_angle));
}

void VBVector2DToString(VBVector2D _vec, VBString* _str) {
#ifdef _VB_DEBUG_
    if(_str == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBVector2DToString() - 두번쨰 파라메터에 VBNull을 지정할 수 없습니다. VBStringAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBChar _tmp_str[256] = {0,};
    sprintf(_tmp_str, "%f %f", _vec.x, _vec.y);
    VBStringSetCString(_str, _tmp_str);
}

VBVector2D VBVector2DZero(void) {
    return VBVector2DCreate(0.0f, 0.0f);
}

