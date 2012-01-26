#include "VBColor.h"
#include <math.h>

VBLong VBColorTypeGetSize(VBColorType _type) {
    
	VBLong _color_size = 0;
	switch(_type) {
		case VBColorType_G:
			_color_size = 1;
			break;
		case VBColorType_GA:
			_color_size = 2;
			break;
		case VBColorType_RGB:
			_color_size = sizeof(VBColorRGB);
			break;
		case VBColorType_RGBA:
			_color_size = sizeof(VBColorRGBA);
			break;
		case VBColorType_HSV:
			_color_size = sizeof(VBColorHSV);
			break;
		case VBColorType_Advanced:
			_color_size = sizeof(VBColorAdvanced);
			break;
	}
	return _color_size;
}

VBColorHSV VBColorRGBToHSV(VBColorRGB _color) {
	VBFloat _h, _s, _v;
	
	VBFloat _min, _max, _delta;
	
	VBFloat _r = (VBFloat)_color.r / 0xFF;
	VBFloat _g = (VBFloat)_color.g / 0xFF;
	VBFloat _b = (VBFloat)_color.b / 0xFF;
	
	_min =_r < _g ? (_r < _b ? _r : _b) : (_g < _b ? _g : _b);
	_max = _r > _g ? (_r > _b ? _r : _b) : (_g > _b ? _g : _b);
	
	_v = _max;
	
	_delta = _max - _min;
	if(_max != 0.0f) {
		_s = _delta / _max;
	} else {
		_s = 0.0f;
		_h = -1.0f;
		
		return VBColorHSVCreate(_h, _s, _v);
	}
	
	if(_r == _max) {
		_h = (_g - _b) / _delta;
	} else if(_g == _max) {
		_h = 2.0f + (_b - _r) / _delta;
	} else {
		_h = 4.0f + (_r - _g) / _delta;
	}
	_h *= 60.0f;
	if(_h < 0.0f) {
		_h += 360.0f;
	}
	
	return VBColorHSVCreate(_h, _s, _v);
}

VBColorRGB VBColorHSVToRGB(VBColorHSV _color) {
	VBFloat _r, _g, _b;
	
	VBLong _i;
	VBFloat _f, _p, _q, _t;
	
	VBFloat _h = _color.h;
	VBFloat _s = _color.s;
	VBFloat _v = _color.v;
    
	if(_s == 0.0f) {
		_r = _g = _b = _v;
		
		return VBColorRGBCreate((VBUChar)(_r * 0xFF), (VBUChar)(_g * 0xFF), (VBUChar)(_b * 0xFF));
	}
	_h /= 60.0f;
	_i = floorf(_h);
	_f = _h - (VBFloat)_i;
	_p = _v * (1.0f - _s);
	_q = _v * (1.0f - _s * _f );
	_t = _v * (1.0f - _s * (1.0f - _f));
	switch(_i) {
		case 0:
			_r = _v;
			_g = _t;
			_b = _p;
			break;
		case 1:
			_r = _q;
			_g = _v;
			_b = _p;
			break;
		case 2:
			_r = _p;
			_g = _v;
			_b = _t;
			break;
		case 3:
			_r = _p;
			_g = _q;
			_b = _v;
			break;
		case 4:
			_r = _t;
			_g = _p;
			_b = _v;
			break;
		default:
			_r = _v;
			_g = _p;
			_b = _q;
			break;
	}
	
	return VBColorRGBCreate((VBUChar)(_r * 0xFF), (VBUChar)(_g * 0xFF), (VBUChar)(_b * 0xFF));
}


