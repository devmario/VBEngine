#include "VBMatrix.h"

VBMatrix3D VBMatrix2DGetVBMatrix3D(VBMatrix2D _mat2D) {
	VBMatrix3D _mat3D;
	
	_mat3D.m11	=	_mat2D.m11;		_mat3D.m12	=	_mat2D.m21;		_mat3D.m13	=	0.0;	_mat3D.m14	=	_mat2D.m31;
	_mat3D.m21	=	_mat2D.m12;		_mat3D.m22	=	_mat2D.m22;		_mat3D.m23	=	0.0;	_mat3D.m24	=	_mat2D.m32;
	_mat3D.m31	=	0.0;			_mat3D.m32	=	0.0;			_mat3D.m33	=	1.0;	_mat3D.m34	=	0.0;
	_mat3D.m41	=	_mat2D.m13;		_mat3D.m42	=	_mat2D.m23;		_mat3D.m43	=	0.0;	_mat3D.m44	=	_mat2D.m33;
	
	return _mat3D;
}