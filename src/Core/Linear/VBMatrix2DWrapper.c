#include "VBMatrix2DWrapper.h"
#include <math.h>

VBMatrix2DWrapper VBMatrix2DWrapperLoadIdentity(void) {
	VBMatrix2DWrapper _wrapp;
	
	_wrapp.mat = VBMatrix2DLoadIdentity();
	
	_wrapp.need_update = VBFalse;
	
	_wrapp.position = VBVector2DCreate(0.0f, 0.0f);
	_wrapp.anchor = VBVector2DCreate(0.0f, 0.0f);
	_wrapp.scale = VBVector2DCreate(1.0f, 1.0f);
	_wrapp.shear = VBVector2DCreate(0.0f, 0.0f);
	_wrapp.rotation = 0.0f;
	
	return _wrapp;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetPosition(VBMatrix2DWrapper _wrapp, VBVector2D _pos) {
	_wrapp.position = _pos;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBVector2D VBMatrix2DWrapperGetPosition(VBMatrix2DWrapper _wrapp) {
	return _wrapp.position;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetX(VBMatrix2DWrapper _wrapp, VBFloat _x) {
	_wrapp.position.x = _x;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetX(VBMatrix2DWrapper _wrapp) {
	return _wrapp.position.x;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetY(VBMatrix2DWrapper _wrapp, VBFloat _y) {
	_wrapp.position.y = _y;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetY(VBMatrix2DWrapper _wrapp) {
	return _wrapp.position.y;
}


VBMatrix2DWrapper VBMatrix2DWrapperSetAnchor(VBMatrix2DWrapper _wrapp, VBVector2D _anchor) {
	_wrapp.anchor = _anchor;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBVector2D VBMatrix2DWrapperGetAnchor(VBMatrix2DWrapper _wrapp) {
	return _wrapp.anchor;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetAnchorX(VBMatrix2DWrapper _wrapp, VBFloat _ax) {
    _wrapp.anchor.x = _ax;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetAnchorX(VBMatrix2DWrapper _wrapp) {
    return _wrapp.anchor.x;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetAnchorY(VBMatrix2DWrapper _wrapp, VBFloat _ay) {
    _wrapp.anchor.y = _ay;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetAnchorY(VBMatrix2DWrapper _wrapp) {
    return _wrapp.anchor.y;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetScale(VBMatrix2DWrapper _wrapp, VBVector2D _scale) {
	_wrapp.scale = _scale;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBVector2D VBMatrix2DWrapperGetScale(VBMatrix2DWrapper _wrapp) {
	return _wrapp.scale;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetXScale(VBMatrix2DWrapper _wrapp, VBFloat _xs) {
	_wrapp.scale.x = _xs;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetXScale(VBMatrix2DWrapper _wrapp) {
	return _wrapp.scale.x;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetYScale(VBMatrix2DWrapper _wrapp, VBFloat _ys) {
	_wrapp.scale.y = _ys;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetYScale(VBMatrix2DWrapper _wrapp) {
	return _wrapp.scale.x;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetShear(VBMatrix2DWrapper _wrapp, VBVector2D _shear) {
	_wrapp.shear = _shear;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBVector2D VBMatrix2DWrapperGetShear(VBMatrix2DWrapper _wrapp) {
	return _wrapp.shear;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetXShear(VBMatrix2DWrapper _wrapp, VBFloat _sx) {
	_wrapp.shear.x = _sx;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetXShear(VBMatrix2DWrapper _wrapp) {
	return _wrapp.shear.x;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetYShear(VBMatrix2DWrapper _wrapp, VBFloat _sy) {
	_wrapp.shear.y = _sy;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetYShear(VBMatrix2DWrapper _wrapp) {
	return _wrapp.shear.y;
}

VBMatrix2DWrapper VBMatrix2DWrapperSetRotation(VBMatrix2DWrapper _wrapp, VBFloat _rotation) {
	_wrapp.rotation = _rotation;
	
	_wrapp.need_update = VBTrue;
	return _wrapp;
}

VBFloat VBMatrix2DWrapperGetRotation(VBMatrix2DWrapper _wrapp) {
	return _wrapp.rotation;
}

VBMatrix2DWrapper VBMatrix2DWrapperUpdate(VBMatrix2DWrapper _wrapp) {
	if(_wrapp.need_update) {
		_wrapp.mat = VBMatrix2DLoadIdentity();
		
		_wrapp.mat = VBMatrix2DTranslateV(_wrapp.mat, _wrapp.position);
        
        _wrapp.mat = VBMatrix2DScaleV(_wrapp.mat, _wrapp.scale);
        
        if(!isnan(_wrapp.rotation)) {
            _wrapp.mat = VBMatrix2DRotate(_wrapp.mat, _wrapp.rotation);
        } else {
            _wrapp.mat = VBMatrix2DShearV(_wrapp.mat, _wrapp.shear);
        }
		
		_wrapp.mat = VBMatrix2DTranslateV(_wrapp.mat, VBVector2DSubtract(VBVector2DZero(), _wrapp.anchor));
		
		_wrapp.need_update = VBFalse;
	}
	return _wrapp;
}

VBMatrix2D VBMatrix2DWrapperGetMatrix(VBMatrix2DWrapper _wrapp) {
    return VBMatrix2DWrapperUpdate(_wrapp).mat;
}

VBMatrix2DWrapper VBMatrix2DWrapperInterpolate(VBMatrix2DWrapper _wrapp1, VBMatrix2DWrapper _wrapp2, VBFloat _num) {
    VBMatrix2DWrapper _wrapp;
    _wrapp.position = VBVector2DInterpolate(VBMatrix2DWrapperGetPosition(_wrapp1), VBMatrix2DWrapperGetPosition(_wrapp2), _num);
    if(_num >= 1.0) {
        _wrapp.anchor = _wrapp2.anchor;
    } else {
        _wrapp.anchor = _wrapp1.anchor;
    }
    _wrapp.scale = VBVector2DInterpolate(VBMatrix2DWrapperGetScale(_wrapp1), VBMatrix2DWrapperGetScale(_wrapp2), _num);
    _wrapp.rotation = VBMatrix2DWrapperGetRotation(_wrapp1) + (VBMatrix2DWrapperGetRotation(_wrapp2) - VBMatrix2DWrapperGetRotation(_wrapp1)) * _num;
    _wrapp.shear = VBVector2DInterpolate(VBMatrix2DWrapperGetShear(_wrapp1), VBMatrix2DWrapperGetShear(_wrapp2), _num);
    _wrapp.need_update = VBTrue;
	return _wrapp;
}

VBBool VBMatrix2DWrapperGetIsNeedUpdate(VBMatrix2DWrapper _wrapp) {
    return _wrapp.need_update;
}
