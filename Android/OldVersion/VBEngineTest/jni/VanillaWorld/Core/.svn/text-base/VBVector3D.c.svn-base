#include "VBVector3D.h"
#include <math.h>

VBVector3D VBVector3DCreate(VBFloat _x, VBFloat _y, VBFloat _z) {
	VBVector3D _vec3D;
	_vec3D.x = _x;
	_vec3D.y = _y;
	_vec3D.z = _z;
	
	return _vec3D;
}

VBFloat VBVector3DGetX(VBVector3D _vec3D) {
	return _vec3D.x;
}

VBFloat VBVector3DGetY(VBVector3D _vec3D) {
	return _vec3D.y;
}

VBFloat VBVector3DGetZ(VBVector3D _vec3D) {
	return _vec3D.z;
}

VBBool VBVector3DIsEqual(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
	if (_vec3D_1.x != _vec3D_2.x) 
		return VBFalse;
	if (_vec3D_1.y != _vec3D_2.y) 
		return VBFalse;
	if (_vec3D_1.z != _vec3D_2.z) 
		return VBFalse;
	return VBTrue;
}

VBVector3D VBVector3DNormal(VBVector3D _vec3D) {
	VBFloat _len = VBVector3DLength(_vec3D);
	_vec3D.x /= _len;
	_vec3D.y /= _len;
	_vec3D.z /= _len;
	return _vec3D;
}

VBVector3D VBVector3DAdd(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
	return VBVector3DCreate(_vec3D_1.x + _vec3D_2.x, 
							_vec3D_1.y + _vec3D_2.y, 
							_vec3D_1.z + _vec3D_2.z);
}

VBVector3D VBVector3DSubtract(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
	return VBVector3DCreate(_vec3D_1.x - _vec3D_2.x, 
							_vec3D_1.y - _vec3D_2.y, 
							_vec3D_1.z - _vec3D_2.z);	
}

VBVector3D VBVector3DMultiply(VBVector3D _vec3D, VBFloat _num) {
	return VBVector3DCreate(_vec3D.x * _num, _vec3D.y * _num, _vec3D.z * _num);
}

VBVector3D VBVector3DDivide(VBVector3D _vec3D, VBFloat _num) {
	return VBVector3DCreate(_vec3D.x / _num, _vec3D.y / _num, _vec3D.z / _num);
}

VBFloat VBVector3DDotProduct(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
	return _vec3D_1.x * _vec3D_2.x + _vec3D_1.y * _vec3D_2.y + _vec3D_1.z * _vec3D_2.z; 
}

VBVector3D VBVector3DCrossProduct(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
	return VBVector3DCreate(_vec3D_1.y * _vec3D_2.z - _vec3D_1.z * _vec3D_2.y, 
							_vec3D_1.z * _vec3D_2.x - _vec3D_1.x * _vec3D_2.z, 
							_vec3D_1.x * _vec3D_2.y - _vec3D_1.y * _vec3D_2.x);
}

VBFloat VBVector3DLength(VBVector3D _vec3D) {
	return sqrtf(VBVector3DDotProduct(_vec3D, _vec3D));
}

VBFloat VBVector3DDistance(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
	return VBVector3DLength(VBVector3DSubtract(_vec3D_1, _vec3D_2));
}

VBFloat VBVector3DAngle(VBVector3D _vec3D) {
    VBFloat angle;
    return angle;
}

VBFloat VBVector3DAngleTo(VBVector3D _vec3D_1, VBVector3D _vec3D_2) {
    VBFloat angle;
    
    
    
    return angle;
}

VBVector3D VBVector3DInterpolate(VBVector3D _vec3D_1, VBVector3D _vec3D_2, VBFloat _num) {
    VBVector3D _tVec3D;
    
    _tVec3D.x = _vec3D_1.x + (_vec3D_2.x * _num);
    _tVec3D.y = _vec3D_1.y + (_vec3D_2.y * _num);
    _tVec3D.z = _vec3D_1.z + (_vec3D_2.z * _num);
    
    return _tVec3D;
}

VBVector3D VBVector3DPolar(VBFloat _len, VBFloat _theta, VBFloat _phi) {
    VBVector3D _tVec3D;
    
    _tVec3D.x = _len * sinf(_phi) * cosf(_theta);
    _tVec3D.y = _len * sinf(_phi) * sinf(_theta);
    _tVec3D.z = _len * cosf(_phi);
    
    return _tVec3D;
}







