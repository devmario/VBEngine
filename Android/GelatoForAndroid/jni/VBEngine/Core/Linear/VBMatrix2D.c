#include "VBMatrix2D.h"
#include <math.h>

VBMatrix2D VBMatrix2DCreate(VBFloat _m11, VBFloat _m12, VBFloat _m13, 
							VBFloat _m21, VBFloat _m22, VBFloat _m23,
							VBFloat _m31, VBFloat _m32, VBFloat _m33) {
	VBMatrix2D _mat;
	
	_mat.m11 = _m11;	_mat.m12 = _m12;	_mat.m13 = _m13;
	_mat.m21 = _m21;	_mat.m22 = _m22;	_mat.m23 = _m23;
	_mat.m31 = _m31;	_mat.m32 = _m32;	_mat.m33 = _m33;
	
	return _mat;
}

VBBool VBMatrix2DIsEqual(VBMatrix2D _mat2D_1, VBMatrix2D _mat2D_2) {
	if(_mat2D_1.m11 != _mat2D_2.m11)
		return VBFalse;
	if(_mat2D_1.m12 != _mat2D_2.m12)
		return VBFalse;
	if(_mat2D_1.m13 != _mat2D_2.m13)
		return VBFalse;
	
	if(_mat2D_1.m21 != _mat2D_2.m21)
		return VBFalse;
	if(_mat2D_1.m22 != _mat2D_2.m22)
		return VBFalse;
	if(_mat2D_1.m23 != _mat2D_2.m23)
		return VBFalse;
	
	if(_mat2D_1.m31 != _mat2D_2.m31)
		return VBFalse;
	if(_mat2D_1.m32 != _mat2D_2.m32)
		return VBFalse;
	if(_mat2D_1.m33 != _mat2D_2.m33)
		return VBFalse;
	
	return VBTrue;
}

VBMatrix2D VBMatrix2DLoadIdentity(void) {
	VBMatrix2D _mat2D;
	
	_mat2D.m11 = 1.0;	_mat2D.m12 = 0.0;	_mat2D.m13 = 0.0;
	_mat2D.m21 = 0.0;	_mat2D.m22 = 1.0;	_mat2D.m23 = 0.0;
	_mat2D.m31 = 0.0;	_mat2D.m32 = 0.0;	_mat2D.m33 = 1.0;
	
	return _mat2D;
}

VBFloat VBMatrix2DDeterminant(VBMatrix2D _mat2D) {
	return
	_mat2D.m11 * _mat2D.m22 * _mat2D.m33 - 
	_mat2D.m11 * _mat2D.m23 * _mat2D.m32 + 
	_mat2D.m12 * _mat2D.m23 * _mat2D.m31 - 
	_mat2D.m12 * _mat2D.m21 * _mat2D.m33 + 
	_mat2D.m13 * _mat2D.m21 * _mat2D.m32 - 
	_mat2D.m13 * _mat2D.m22 * _mat2D.m31;
}

VBMatrix2D VBMatrix2DInverse(VBMatrix2D _mat2D) {
    VBMatrix2D _invMat2D;
	VBFloat _det = VBMatrix2DDeterminant(_mat2D);
	VBBool _success = !(fabsf(_det) < 1.0e-8);
	
	if(_success) {
		_invMat2D.m11 = -_mat2D.m23 * _mat2D.m32 + _mat2D.m22 * _mat2D.m33;
		_invMat2D.m12 =  _mat2D.m13 * _mat2D.m32 - _mat2D.m12 * _mat2D.m33;
		_invMat2D.m13 = -_mat2D.m13 * _mat2D.m22 + _mat2D.m12 * _mat2D.m23;
		
		_invMat2D.m21 =  _mat2D.m23 * _mat2D.m31 - _mat2D.m21 * _mat2D.m33;
		_invMat2D.m22 = -_mat2D.m13 * _mat2D.m31 + _mat2D.m11 * _mat2D.m33;
		_invMat2D.m23 =  _mat2D.m13 * _mat2D.m21 - _mat2D.m11 * _mat2D.m23;
		
		_invMat2D.m31 = -_mat2D.m22 * _mat2D.m31 + _mat2D.m21 * _mat2D.m32;
		_invMat2D.m32 =  _mat2D.m12 * _mat2D.m31 - _mat2D.m11 * _mat2D.m32;
		_invMat2D.m33 = -_mat2D.m12 * _mat2D.m21 + _mat2D.m11 * _mat2D.m22;
		
		_det = 1.0 / _det;
		_invMat2D.m11 *= _det;
		_invMat2D.m12 *= _det;
		_invMat2D.m13 *= _det;
		_invMat2D.m21 *= _det;
		_invMat2D.m22 *= _det;
		_invMat2D.m23 *= _det;
		_invMat2D.m31 *= _det;
		_invMat2D.m32 *= _det;
		_invMat2D.m33 *= _det;
	}
    return _invMat2D;
}

VBMatrix2D VBMatrix2DMultiply(VBMatrix2D _mat2D_1, VBMatrix2D _mat2D_2) {
	VBMatrix2D _mat2D;
	
	_mat2D.m11 = _mat2D_1.m11 * _mat2D_2.m11 + _mat2D_1.m12 * _mat2D_2.m21 + _mat2D_1.m13 * _mat2D_2.m31;
	_mat2D.m12 = _mat2D_1.m11 * _mat2D_2.m12 + _mat2D_1.m12 * _mat2D_2.m22 + _mat2D_1.m13 * _mat2D_2.m32;
	_mat2D.m13 = _mat2D_1.m11 * _mat2D_2.m13 + _mat2D_1.m12 * _mat2D_2.m23 + _mat2D_1.m13 * _mat2D_2.m33;
	
	_mat2D.m21 = _mat2D_1.m21 * _mat2D_2.m11 + _mat2D_1.m22 * _mat2D_2.m21 + _mat2D_1.m23 * _mat2D_2.m31;
	_mat2D.m22 = _mat2D_1.m21 * _mat2D_2.m12 + _mat2D_1.m22 * _mat2D_2.m22 + _mat2D_1.m23 * _mat2D_2.m32;
	_mat2D.m23 = _mat2D_1.m21 * _mat2D_2.m13 + _mat2D_1.m22 * _mat2D_2.m23 + _mat2D_1.m23 * _mat2D_2.m33;
	
	_mat2D.m31 = _mat2D_1.m31 * _mat2D_2.m11 + _mat2D_1.m32 * _mat2D_2.m21 + _mat2D_1.m33 * _mat2D_2.m31;
	_mat2D.m32 = _mat2D_1.m31 * _mat2D_2.m12 + _mat2D_1.m32 * _mat2D_2.m22 + _mat2D_1.m33 * _mat2D_2.m32;
	_mat2D.m33 = _mat2D_1.m31 * _mat2D_2.m13 + _mat2D_1.m32 * _mat2D_2.m23 + _mat2D_1.m33 * _mat2D_2.m33;
	
	return _mat2D;
}

VBMatrix2D VBMatrix2DTranslate(VBMatrix2D _mat2D, VBFloat _x, VBFloat _y) {
	VBMatrix2D _tMat2D = _mat2D;
	
	_tMat2D.m13 += _mat2D.m11 * _x + _mat2D.m12 * _y;
	_tMat2D.m23 += _mat2D.m21 * _x + _mat2D.m22 * _y;
	_tMat2D.m33 += _mat2D.m31 * _x + _mat2D.m32 * _y;
	
	return _tMat2D;
}

VBMatrix2D VBMatrix2DTranslateX(VBMatrix2D _mat2D, VBFloat _x) {
	VBMatrix2D _tMat2D = _mat2D;
	
	_tMat2D.m13 += _mat2D.m11 * _x;
	_tMat2D.m23 += _mat2D.m21 * _x;
	_tMat2D.m33 += _mat2D.m31 * _x;
	
	return _tMat2D;
}

VBMatrix2D VBMatrix2DTranslateY(VBMatrix2D _mat2D, VBFloat _y) {
	VBMatrix2D _tMat2D = _mat2D;
	
	_tMat2D.m13 += _mat2D.m12 * _y;
	_tMat2D.m23 += _mat2D.m22 * _y;
	_tMat2D.m33 += _mat2D.m32 * _y;
	
	return _tMat2D;
}

VBMatrix2D VBMatrix2DTranslateV(VBMatrix2D _mat2D, VBVector2D _vec2D) {
	VBMatrix2D _tMat2D = VBMatrix2DLoadIdentity();
	
    _tMat2D.m13 = _vec2D.x;
    _tMat2D.m23 = _vec2D.y;
	
	return VBMatrix2DMultiply(_mat2D, _tMat2D);
}

VBMatrix2D VVBMatrix2DTranslateVA(VBMatrix2D _mat2D, VBVector2D _vec2D) {
	VBMatrix2D _tMat2D = VBMatrix2DLoadIdentity();
	
    _tMat2D.m13 = _vec2D.x;
    _tMat2D.m23 = _vec2D.y;
	
	return VBMatrix2DMultiply(_tMat2D,_mat2D);
}


VBMatrix2D VBMatrix2DScale(VBMatrix2D _mat2D, VBFloat _sx, VBFloat _sy) {
	VBMatrix2D _sMat2D = _mat2D;
	
	_sMat2D.m11 *= _sx;
	_sMat2D.m21 *= _sx;
	_sMat2D.m31 *= _sx;
	
	_sMat2D.m12 *= _sy;
	_sMat2D.m22 *= _sy;
	_sMat2D.m32 *= _sy;
	
	return _sMat2D;
}

VBMatrix2D VBMatrix2DScaleX(VBMatrix2D _mat2D, VBFloat _sx) {
	VBMatrix2D _sMat2D = _mat2D;
	
	_sMat2D.m11 *= _sx;
	_sMat2D.m21 *= _sx;
	_sMat2D.m31 *= _sx;
	
	return _sMat2D;
}

VBMatrix2D VBMatrix2DScaleY(VBMatrix2D _mat2D, VBFloat _sy) {
	VBMatrix2D _sMat2D = _mat2D;
	
	_sMat2D.m12 *= _sy;
	_sMat2D.m22 *= _sy;
	_sMat2D.m32 *= _sy;
	
	return _sMat2D;
}

VBMatrix2D VBMatrix2DScaleV(VBMatrix2D _mat2D, VBVector2D _vec2D) {
	VBMatrix2D _sMat2D = VBMatrix2DLoadIdentity();
	
    _sMat2D.m11 = _vec2D.x;
    _sMat2D.m22 = _vec2D.y;
	
	return VBMatrix2DMultiply(_mat2D, _sMat2D);
}

VBMatrix2D VBMatrix2DRotate(VBMatrix2D _mat2D, VBFloat _angle) {
	VBMatrix2D _rMat2D = VBMatrix2DLoadIdentity();
	
	VBFloat _cos = cosf(_angle);
	VBFloat _sin = sinf(_angle);
    
    _rMat2D.m11 = _cos;
    _rMat2D.m12 = -_sin;
    _rMat2D.m21 = _sin;
    _rMat2D.m22 = _cos;
	
	return VBMatrix2DMultiply(_mat2D, _rMat2D);
}

VBMatrix2D VBMatrix2DShear(VBMatrix2D _mat2D, VBFloat _sx, VBFloat _sy) {
	VBMatrix2D _sMat2D = VBMatrix2DLoadIdentity();
	
    _sMat2D.m11 = cosf(_sy);
	_sMat2D.m12 = -sinf(_sx);
	_sMat2D.m21 = sinf(_sy);
    _sMat2D.m22 = cosf(_sx);
	
	return _sMat2D;
}

VBMatrix2D VBMatrix2DShearX(VBMatrix2D _mat2D, VBFloat _sx) {
	VBMatrix2D _sMat2D = VBMatrix2DLoadIdentity();
	
	_sMat2D.m12 = -sinf(_sx);
    _sMat2D.m22 = cosf(_sx);
	
	return _sMat2D;
}

VBMatrix2D VBMatrix2DShearY(VBMatrix2D _mat2D, VBFloat _sy) {
	VBMatrix2D _sMat2D = VBMatrix2DLoadIdentity();
	
    _sMat2D.m11 = cosf(_sy);
    _sMat2D.m21 = sinf(_sy);
	
	return _sMat2D;
}

VBMatrix2D VBMatrix2DShearV(VBMatrix2D _mat2D, VBVector2D _vec2D) {
	VBMatrix2D _sMat2D = VBMatrix2DLoadIdentity();
	
    _sMat2D.m11 = cosf(_vec2D.y);
	_sMat2D.m12 = -sinf(_vec2D.x);
	_sMat2D.m21 = sinf(_vec2D.y);
    _sMat2D.m22 = cosf(_vec2D.x);
	
	return VBMatrix2DMultiply(_mat2D, _sMat2D);
}

VBVector2D VBMatrix2DMultiplyVBVector2D(VBMatrix2D _mat2D, VBVector2D _vec2D) {
	VBVector2D _mVec2D;
	
	VBFloat _invZ = 1.0 / (_vec2D.x * _mat2D.m31 + _vec2D.y * _mat2D.m32 + _mat2D.m33);
	_mVec2D.x = (_mat2D.m11 * _vec2D.x + _mat2D.m12 * _vec2D.y + _mat2D.m13) * _invZ;
	_mVec2D.y = (_mat2D.m21 * _vec2D.x + _mat2D.m22 * _vec2D.y + _mat2D.m23) * _invZ;
	
	return _mVec2D;
}

VBVector2D VBMatrix2DMultiplyDeltaVBVector2D(VBMatrix2D _mat2D, VBVector2D _vec2D) {
	VBVector2D _mVec2D;
	
	VBFloat _invZ = 1.0 / (_vec2D.x * _mat2D.m31 + _vec2D.y * _mat2D.m32 + _mat2D.m33);
	_mVec2D.x = (_mat2D.m11 * _vec2D.x + _mat2D.m12 * _vec2D.y) * _invZ;
	_mVec2D.y = (_mat2D.m21 * _vec2D.x + _mat2D.m22 * _vec2D.y) * _invZ;
	
	return _mVec2D;
}

VBMatrix2D VBMatrix2DInterpolate(VBMatrix2D _fromMat2D, VBMatrix2D _toMat2D, VBFloat _num) {
	VBMatrix2D _tMat2D;
    _tMat2D.m11 = _fromMat2D.m11 + (_toMat2D.m11 - _fromMat2D.m11) * _num;
    _tMat2D.m12 = _fromMat2D.m12 + (_toMat2D.m12 - _fromMat2D.m12) * _num;
    _tMat2D.m13 = _fromMat2D.m13 + (_toMat2D.m13 - _fromMat2D.m13) * _num;
    _tMat2D.m21 = _fromMat2D.m21 + (_toMat2D.m21 - _fromMat2D.m21) * _num;
    _tMat2D.m22 = _fromMat2D.m22 + (_toMat2D.m22 - _fromMat2D.m22) * _num;
    _tMat2D.m23 = _fromMat2D.m23 + (_toMat2D.m23 - _fromMat2D.m23) * _num;
    _tMat2D.m31 = _fromMat2D.m31 + (_toMat2D.m31 - _fromMat2D.m31) * _num;
    _tMat2D.m32 = _fromMat2D.m32 + (_toMat2D.m32 - _fromMat2D.m32) * _num;
    _tMat2D.m33 = _fromMat2D.m33 + (_toMat2D.m33 - _fromMat2D.m33) * _num;
    
	return _tMat2D;
}
