#include "VBMatrix3D.h"
#include <math.h>

VBMatrix3D VBMatrix3DCreate(VBFloat _m11, VBFloat _m12, VBFloat _m13, VBFloat _m14,
							VBFloat _m21, VBFloat _m22, VBFloat _m23, VBFloat _m24,
							VBFloat _m31, VBFloat _m32, VBFloat _m33, VBFloat _m34,
							VBFloat _m41, VBFloat _m42, VBFloat _m43, VBFloat _m44) {
	
	VBMatrix3D _mat;
	
	_mat.m11 = _m11;	_mat.m12 = _m12;	_mat.m13 = _m13;	_mat.m14 = _m14;
	_mat.m21 = _m21;	_mat.m22 = _m22;	_mat.m23 = _m23;	_mat.m24 = _m24;
	_mat.m31 = _m31;	_mat.m32 = _m32;	_mat.m33 = _m33;	_mat.m34 = _m34;
	_mat.m41 = _m41;	_mat.m42 = _m42;	_mat.m43 = _m43;	_mat.m44 = _m44;
	
	return _mat;
}

VBBool VBMatrix3DIsEqual(VBMatrix3D _mat3D_1, VBMatrix3D _mat3D_2) {
    if(_mat3D_1.m11 != _mat3D_2.m11) 
        return VBFalse;
    if(_mat3D_1.m12 != _mat3D_2.m12)  
        return VBFalse;
    if(_mat3D_1.m13 != _mat3D_2.m13)
        return VBFalse;
    if(_mat3D_1.m14 != _mat3D_2.m14)
        return VBFalse;

    if(_mat3D_1.m21 != _mat3D_2.m21) 
        return VBFalse;
    if(_mat3D_1.m22 != _mat3D_2.m22)  
        return VBFalse;
    if(_mat3D_1.m23 != _mat3D_2.m23)
        return VBFalse;
    if(_mat3D_1.m24 != _mat3D_2.m24)
        return VBFalse;

    if(_mat3D_1.m31 != _mat3D_2.m31) 
        return VBFalse;
    if(_mat3D_1.m32 != _mat3D_2.m32)  
        return VBFalse;
    if(_mat3D_1.m33 != _mat3D_2.m33)
        return VBFalse;
    if(_mat3D_1.m34 != _mat3D_2.m34)
        return VBFalse;

    if(_mat3D_1.m41 != _mat3D_2.m41) 
        return VBFalse;
    if(_mat3D_1.m42 != _mat3D_2.m42)  
        return VBFalse;
    if(_mat3D_1.m43 != _mat3D_2.m43)
        return VBFalse;
    if(_mat3D_1.m44 != _mat3D_2.m44)
        return VBFalse;
    
    return VBTrue;
}

VBMatrix3D VBMatrix3DLoadIdentity(void) {
	VBMatrix3D _mat3D;
	
	_mat3D.m11 = 1.0;	_mat3D.m12 = 0.0;	_mat3D.m13 = 0.0;	_mat3D.m14 = 0.0;
	_mat3D.m21 = 0.0;	_mat3D.m22 = 1.0;	_mat3D.m23 = 0.0;	_mat3D.m24 = 0.0;
	_mat3D.m31 = 0.0;	_mat3D.m32 = 0.0;	_mat3D.m33 = 1.0;	_mat3D.m34 = 0.0;
	_mat3D.m41 = 0.0;	_mat3D.m42 = 0.0;	_mat3D.m43 = 0.0;	_mat3D.m44 = 1.0;
	
	return _mat3D;
}


VBFloat VBMatrix3DDeterminant(VBMatrix3D _mat3D) {
    return 
    _mat3D.m11 * _mat3D.m22 * _mat3D.m33 * _mat3D.m44 -
    _mat3D.m11 * _mat3D.m22 * _mat3D.m34 * _mat3D.m43 -
    _mat3D.m11 * _mat3D.m32 * _mat3D.m23 * _mat3D.m44 +
    _mat3D.m11 * _mat3D.m32 * _mat3D.m24 * _mat3D.m43 +
    _mat3D.m11 * _mat3D.m42 * _mat3D.m23 * _mat3D.m34 -
    _mat3D.m11 * _mat3D.m42 * _mat3D.m24 * _mat3D.m33 -
    
    _mat3D.m21 * _mat3D.m12 * _mat3D.m33 * _mat3D.m44 +
    _mat3D.m21 * _mat3D.m12 * _mat3D.m34 * _mat3D.m43 +
    _mat3D.m21 * _mat3D.m32 * _mat3D.m13 * _mat3D.m44 -
    _mat3D.m21 * _mat3D.m32 * _mat3D.m14 * _mat3D.m43 -
    _mat3D.m21 * _mat3D.m42 * _mat3D.m13 * _mat3D.m34 +
    _mat3D.m21 * _mat3D.m42 * _mat3D.m14 * _mat3D.m33 +
    
    _mat3D.m31 * _mat3D.m12 * _mat3D.m23 * _mat3D.m44 -
    _mat3D.m31 * _mat3D.m12 * _mat3D.m24 * _mat3D.m43 -
    _mat3D.m31 * _mat3D.m22 * _mat3D.m13 * _mat3D.m44 +
    _mat3D.m31 * _mat3D.m22 * _mat3D.m14 * _mat3D.m43 +
    _mat3D.m31 * _mat3D.m42 * _mat3D.m13 * _mat3D.m24 -
    _mat3D.m31 * _mat3D.m42 * _mat3D.m14 * _mat3D.m23 -
    
    _mat3D.m41 * _mat3D.m12 * _mat3D.m23 * _mat3D.m34 +
    _mat3D.m41 * _mat3D.m12 * _mat3D.m24 * _mat3D.m33 +
    _mat3D.m41 * _mat3D.m22 * _mat3D.m13 * _mat3D.m34 -
    _mat3D.m41 * _mat3D.m22 * _mat3D.m14 * _mat3D.m33 -
    _mat3D.m41 * _mat3D.m32 * _mat3D.m13 * _mat3D.m24 +
    _mat3D.m41 * _mat3D.m32 * _mat3D.m14 * _mat3D.m23;
}

VBMatrix3D VBMatrix3DInverse(VBMatrix3D _mat3D) {
    VBFloat _det = VBMatrix3DDeterminant(_mat3D);
    VBBool _success = !(fabsf(_det) < 1.0e-8);
    
    if(_success) {
        
        
        
    }
    return _mat3D;
}

VBMatrix3D VBMatrix3DMultiply(VBMatrix3D _mat3D_1, VBMatrix3D _mat3D_2) {
	VBMatrix3D _result;
	
	_result.m11 = _mat3D_1.m11 * _mat3D_2.m11 + _mat3D_1.m21 * _mat3D_2.m12 + _mat3D_1.m31 * _mat3D_2.m13 + _mat3D_1.m41 * _mat3D_2.m14;
	_result.m12 = _mat3D_1.m12 * _mat3D_2.m11 + _mat3D_1.m22 * _mat3D_2.m12 + _mat3D_1.m32 * _mat3D_2.m13 + _mat3D_1.m42 * _mat3D_2.m14;
	_result.m13 = _mat3D_1.m13 * _mat3D_2.m11 + _mat3D_1.m23 * _mat3D_2.m12 + _mat3D_1.m33 * _mat3D_2.m13 + _mat3D_1.m43 * _mat3D_2.m14;
	_result.m14 = _mat3D_1.m14 * _mat3D_2.m11 + _mat3D_1.m24 * _mat3D_2.m12 + _mat3D_1.m34 * _mat3D_2.m13 + _mat3D_1.m44 * _mat3D_2.m14;
	
	_result.m21 = _mat3D_1.m11 * _mat3D_2.m21 + _mat3D_1.m21 * _mat3D_2.m22 + _mat3D_1.m31 * _mat3D_2.m23 + _mat3D_1.m41 * _mat3D_2.m24;
	_result.m22 = _mat3D_1.m12 * _mat3D_2.m21 + _mat3D_1.m22 * _mat3D_2.m22 + _mat3D_1.m32 * _mat3D_2.m23 + _mat3D_1.m42 * _mat3D_2.m24;
	_result.m23 = _mat3D_1.m13 * _mat3D_2.m21 + _mat3D_1.m23 * _mat3D_2.m22 + _mat3D_1.m33 * _mat3D_2.m23 + _mat3D_1.m43 * _mat3D_2.m24;
	_result.m24 = _mat3D_1.m14 * _mat3D_2.m21 + _mat3D_1.m24 * _mat3D_2.m22 + _mat3D_1.m34 * _mat3D_2.m23 + _mat3D_1.m44 * _mat3D_2.m24;
	
	_result.m31 = _mat3D_1.m11 * _mat3D_2.m31 + _mat3D_1.m21 * _mat3D_2.m32 + _mat3D_1.m31 * _mat3D_2.m33 + _mat3D_1.m41 * _mat3D_2.m34;
	_result.m32 = _mat3D_1.m12 * _mat3D_2.m31 + _mat3D_1.m22 * _mat3D_2.m32 + _mat3D_1.m32 * _mat3D_2.m33 + _mat3D_1.m42 * _mat3D_2.m34;
	_result.m33 = _mat3D_1.m13 * _mat3D_2.m31 + _mat3D_1.m23 * _mat3D_2.m32 + _mat3D_1.m33 * _mat3D_2.m33 + _mat3D_1.m43 * _mat3D_2.m34;
	_result.m34 = _mat3D_1.m14 * _mat3D_2.m31 + _mat3D_1.m24 * _mat3D_2.m32 + _mat3D_1.m34 * _mat3D_2.m33 + _mat3D_1.m44 * _mat3D_2.m34;
	
	_result.m41 = _mat3D_1.m11 * _mat3D_2.m41 + _mat3D_1.m21 * _mat3D_2.m42 + _mat3D_1.m31 * _mat3D_2.m43 + _mat3D_1.m41 * _mat3D_2.m44;
	_result.m42 = _mat3D_1.m12 * _mat3D_2.m41 + _mat3D_1.m22 * _mat3D_2.m42 + _mat3D_1.m32 * _mat3D_2.m43 + _mat3D_1.m42 * _mat3D_2.m44;
	_result.m43 = _mat3D_1.m13 * _mat3D_2.m41 + _mat3D_1.m23 * _mat3D_2.m42 + _mat3D_1.m33 * _mat3D_2.m43 + _mat3D_1.m43 * _mat3D_2.m44;
	_result.m44 = _mat3D_1.m14 * _mat3D_2.m41 + _mat3D_1.m24 * _mat3D_2.m42 + _mat3D_1.m34 * _mat3D_2.m43 + _mat3D_1.m44 * _mat3D_2.m44;
	
	return _result;
}

VBMatrix3D VBMatrix3DTranslate(VBMatrix3D _mat3D, VBFloat _x, VBFloat _y, VBFloat _z) {
	VBMatrix3D _tMat3D = _mat3D;
	
	_tMat3D.m14 += _mat3D.m11 * _x + _mat3D.m12 * _y + _mat3D.m13 * _z;
	_tMat3D.m24 += _mat3D.m21 * _x + _mat3D.m22 * _y + _mat3D.m23 * _z;
	_tMat3D.m34 += _mat3D.m31 * _x + _mat3D.m32 * _y + _mat3D.m33 * _z;
	_tMat3D.m44 += _mat3D.m41 * _x + _mat3D.m42 * _y + _mat3D.m43 * _z;
	
	return _tMat3D;
}

VBMatrix3D VBMatrix3DTranslateX(VBMatrix3D _mat3D, VBFloat _x) {
	VBMatrix3D _tMat3D = _mat3D;
	
	_tMat3D.m14 += _mat3D.m11 * _x;
	_tMat3D.m24 += _mat3D.m21 * _x;
	_tMat3D.m34 += _mat3D.m31 * _x;
	_tMat3D.m44 += _mat3D.m41 * _x;
	
	return _tMat3D;
}

VBMatrix3D VBMatrix3DTranslateY(VBMatrix3D _mat3D, VBFloat _y) {
	VBMatrix3D _tMat3D = _mat3D;
	
	_tMat3D.m14 += _mat3D.m12 * _y;
	_tMat3D.m24 += _mat3D.m22 * _y;
	_tMat3D.m34 += _mat3D.m32 * _y;
	_tMat3D.m44 += _mat3D.m42 * _y;
	
	return _tMat3D;
}

VBMatrix3D VBMatrix3DTranslateZ(VBMatrix3D _mat3D, VBFloat _z) {
	VBMatrix3D _tMat3D = _mat3D;
	
	_tMat3D.m14 += _mat3D.m13 * _z;
	_tMat3D.m24 += _mat3D.m23 * _z;
	_tMat3D.m34 += _mat3D.m33 * _z;
	_tMat3D.m44 += _mat3D.m43 * _z;
	
	return _tMat3D;
}

VBMatrix3D VBMatrix3DTranslateV(VBMatrix3D _mat3D, VBVector3D _vec3D) {
	VBMatrix3D _tMat3D = _mat3D;
	
	_tMat3D.m14 += _mat3D.m11 * _vec3D.x + _mat3D.m12 * _vec3D.y + _mat3D.m13 * _vec3D.z;
	_tMat3D.m24 += _mat3D.m21 * _vec3D.x + _mat3D.m22 * _vec3D.y + _mat3D.m23 * _vec3D.z;
	_tMat3D.m34 += _mat3D.m31 * _vec3D.x + _mat3D.m32 * _vec3D.y + _mat3D.m33 * _vec3D.z;
	_tMat3D.m44 += _mat3D.m41 * _vec3D.x + _mat3D.m42 * _vec3D.y + _mat3D.m43 * _vec3D.z; 
	
	return _tMat3D;
}

VBMatrix3D VBMatrix3DScale(VBMatrix3D _mat3D, VBFloat _sx, VBFloat _sy, VBFloat _sz) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m11 *= _sx;
	_sMat3D.m21 *= _sx;
	_sMat3D.m31 *= _sx;
	_sMat3D.m41 *= _sx;
	
	_sMat3D.m12 *= _sy;
	_sMat3D.m22 *= _sy;
	_sMat3D.m32 *= _sy;
	_sMat3D.m42 *= _sy;
	
	_sMat3D.m13 *= _sz;
	_sMat3D.m23 *= _sz;
	_sMat3D.m33 *= _sz;
	_sMat3D.m43 *= _sz;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DScaleX(VBMatrix3D _mat3D, VBFloat _sx) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m11 *= _sx;
	_sMat3D.m21 *= _sx;
	_sMat3D.m31 *= _sx;
	_sMat3D.m41 *= _sx;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DScaleY(VBMatrix3D _mat3D, VBFloat _sy) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m12 *= _sy;
	_sMat3D.m22 *= _sy;
	_sMat3D.m32 *= _sy;
	_sMat3D.m42 *= _sy;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DScaleZ(VBMatrix3D _mat3D, VBFloat _sz) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m13 *= _sz;
	_sMat3D.m23 *= _sz;
	_sMat3D.m33 *= _sz;
	_sMat3D.m43 *= _sz;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DScaleV(VBMatrix3D _mat3D, VBVector3D _vec3D) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m11 *= _vec3D.x;
	_sMat3D.m21 *= _vec3D.x;
	_sMat3D.m31 *= _vec3D.x;
	_sMat3D.m41 *= _vec3D.x;
	
	_sMat3D.m12 *= _vec3D.y;
	_sMat3D.m22 *= _vec3D.y;
	_sMat3D.m32 *= _vec3D.y;
	_sMat3D.m42 *= _vec3D.y;
	
	_sMat3D.m13 *= _vec3D.z;
	_sMat3D.m23 *= _vec3D.z;
	_sMat3D.m33 *= _vec3D.z;
	_sMat3D.m43 *= _vec3D.z;
	
	return _sMat3D;
}

//TODO: Rotation 어떻게??
VBMatrix3D VBMatrix3DRotate(VBMatrix3D _mat3D, VBFloat _angle) {
	VBMatrix3D _rMat3D = _mat3D;
	
	//	VBFloat _cos = cosf(_angle);
	//	VBFloat _sin = sinf(_angle);
	
	
	
	return _rMat3D;
}

VBMatrix3D VBMatrix3DShear(VBMatrix3D _mat3D, VBFloat _sx, VBFloat _sy, VBFloat _sz) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m13 += _mat3D.m11 * _sx;
	_sMat3D.m23 += _mat3D.m21 * _sx;
	_sMat3D.m33 += _mat3D.m31 * _sx;
	_sMat3D.m43 += _mat3D.m41 * _sx;
	
	_sMat3D.m12 += _mat3D.m12 * _sy;
	_sMat3D.m22 += _mat3D.m22 * _sy;
	_sMat3D.m32 += _mat3D.m32 * _sy;
	_sMat3D.m42 += _mat3D.m42 * _sy;
	
	_sMat3D.m11 += _mat3D.m13 * _sz;
	_sMat3D.m21 += _mat3D.m23 * _sz;
	_sMat3D.m31 += _mat3D.m33 * _sz;
	_sMat3D.m41 += _mat3D.m43 * _sz;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DShearX(VBMatrix3D _mat3D, VBFloat _sx) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m13 += _mat3D.m11 * _sx;
	_sMat3D.m23 += _mat3D.m21 * _sx;
	_sMat3D.m33 += _mat3D.m31 * _sx;
	_sMat3D.m43 += _mat3D.m41 * _sx;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DShearY(VBMatrix3D _mat3D, VBFloat _sy) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m12 += _mat3D.m12 * _sy;
	_sMat3D.m22 += _mat3D.m22 * _sy;
	_sMat3D.m32 += _mat3D.m32 * _sy;
	_sMat3D.m42 += _mat3D.m42 * _sy;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DShearZ(VBMatrix3D _mat3D, VBFloat _sz) {
	VBMatrix3D _sMat3D = _mat3D;
	
	_sMat3D.m11 += _mat3D.m13 * _sz;
	_sMat3D.m21 += _mat3D.m23 * _sz;
	_sMat3D.m31 += _mat3D.m33 * _sz;
	_sMat3D.m41 += _mat3D.m43 * _sz;
	
	return _sMat3D;
}

VBMatrix3D VBMatrix3DShearV(VBMatrix3D _mat3D, VBVector3D _vec3D) {
    VBMatrix3D _sMat3D = _mat3D;
    
    _sMat3D.m13 += _mat3D.m11 * _vec3D.x;
    _sMat3D.m23 += _mat3D.m21 * _vec3D.x;
    _sMat3D.m33 += _mat3D.m31 * _vec3D.x;
    _sMat3D.m43 += _mat3D.m41 * _vec3D.x;
    
    _sMat3D.m12 += _mat3D.m12 * _vec3D.y;
    _sMat3D.m22 += _mat3D.m22 * _vec3D.y;
    _sMat3D.m32 += _mat3D.m32 * _vec3D.y;
    _sMat3D.m42 += _mat3D.m42 * _vec3D.y;

    _sMat3D.m11 += _mat3D.m13 * _vec3D.z;
    _sMat3D.m21 += _mat3D.m23 * _vec3D.z;
    _sMat3D.m31 += _mat3D.m33 * _vec3D.z;
    _sMat3D.m41 += _mat3D.m43 * _vec3D.z;

    return _sMat3D;
}


VBVector3D VBMatrix3DMultiplyVBVector3D(VBMatrix3D _mat3D, VBVector3D _vec3D) {
	VBVector3D _result;
	_result.x = _mat3D.m11 * _vec3D.x + _mat3D.m21 * _vec3D.y + _mat3D.m31 * _vec3D.z + _mat3D.m41;
	_result.y = _mat3D.m12 * _vec3D.x + _mat3D.m22 * _vec3D.y + _mat3D.m32 * _vec3D.z + _mat3D.m42;
	_result.z = _mat3D.m13 * _vec3D.x + _mat3D.m23 * _vec3D.y + _mat3D.m33 * _vec3D.z + _mat3D.m43;
	
	return _result;
}

