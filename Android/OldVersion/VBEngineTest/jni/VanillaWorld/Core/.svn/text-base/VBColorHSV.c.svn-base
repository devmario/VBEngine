#include "VBColorHSV.h"
#include <math.h>

VBColorHSV VBColorHSVCreate(VBFloat _h, VBFloat _s, VBFloat _v) {
	VBColorHSV _color;
	
	if(_h > 360.0f) {
		_h = 360.0f;
	} else if(_h < 0.0f) {
		_h = 0.0f;
	}
	
	if(_s > 1.0f) {
		_s = 1.0f;
	} else if(_s < 0.0f) {
		_s = 0.0f;
	}
	
	if(_v > 1.0f) {
		_v = 1.0f;
	} else if(_v < 0.0f) {
		if(_s == 0.0f) {
			_v = -1.0f;
		} else {
			_v = 0.0f;
		}
	}
	
	_color.h = _h;
	_color.s = _s;
	_color.v = _v;
	
	return _color;
}

VBFloat VBColorHSVGetH(VBColorHSV _color) {
	return _color.h;
}

VBFloat VBColorHSVGetS(VBColorHSV _color) {
	return _color.s;
}

VBFloat VBColorHSVGetV(VBColorHSV _color) {
	return _color.v;
}

VBColorHSV VBColorHSVInterpolate(VBColorHSV _color1, VBColorHSV _color2, VBFloat _num) {
    VBColorHSV _color;
    _color.h = _color1.h + (_color2.h - _color1.h) * _num;
    _color.s = _color1.s + (_color2.s - _color1.s) * _num;
    _color.v = _color1.v + (_color2.v - _color1.v) * _num;
    return _color;
}