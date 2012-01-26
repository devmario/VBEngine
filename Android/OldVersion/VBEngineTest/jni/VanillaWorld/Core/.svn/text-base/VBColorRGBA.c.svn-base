#include "VBColorRGBA.h"

VBColorRGBA VBColorRGBACreate(VBUChar _r, VBUChar _g, VBUChar _b, VBUChar _a) {
	VBColorRGBA _color;
	
	_color.r = _r;
	_color.g = _g;
	_color.b = _b;
	_color.a = _a;
	
	return _color;
}

VBColorRGBA VBColorRGBACreateWithColorCode(VBULong _hex) {
	return VBColorRGBACreate((_hex & 0xFF000000) >> 0x18, 
							 (_hex & 0x00FF0000) >> 0x10, 
							 (_hex & 0x0000FF00) >> 0x08, 
							 (_hex & 0x000000FF) >> 0x00);
}

VBULong VBColorRGBAGetColorCode(VBColorRGBA _color) {
	return (_color.r << 0x18) | (_color.g << 0x10) | (_color.b << 0x08) | _color.a;
}

VBUChar VBColorRGBAGetR(VBColorRGBA _color) {
	return _color.r;
}

VBUChar VBColorRGBAGetG(VBColorRGBA _color) {
	return _color.g;
}

VBUChar VBColorRGBAGetB(VBColorRGBA _color) {
	return _color.b;
}

VBUChar VBColorRGBAGetA(VBColorRGBA _color) {
	return _color.a;
}

VBColorRGBA VBColorRGBAInterpolate(VBColorRGBA _color1, VBColorRGBA _color2, VBFloat _num) {
    VBColorRGBA _color;
    _color.r = _color1.r + (_color2.r - _color1.r) * _num;
    _color.g = _color1.g + (_color2.g - _color1.g) * _num;
    _color.b = _color1.b + (_color2.b - _color1.b) * _num;
    _color.a = _color1.a + (_color2.a - _color1.a) * _num;
    return _color;
}

VBColorRGBA VBColorRGBAMultiply(VBColorRGBA _color1, VBColorRGBA _color2) {
    VBColorRGBA _color;
    _color.r = _color1.r * ((float)_color2.r / 0xFF);
    _color.g = _color1.g * ((float)_color2.g / 0xFF);
    _color.b = _color1.b * ((float)_color2.b / 0xFF);
    _color.a = _color1.a * ((float)_color2.a / 0xFF);
    return _color;
}
