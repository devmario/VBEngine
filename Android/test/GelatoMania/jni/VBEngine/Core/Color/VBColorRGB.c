#include "VBColorRGB.h"


VBColorRGB VBColorRGBCreate(VBUChar _r, VBUChar _g, VBUChar _b) {
	VBColorRGB _color;
	
	_color.r = _r;
	_color.g = _g;
	_color.b = _b;
	
	return _color;
}

VBColorRGB VBColorRGBCreateWithColorCode(VBULong _hex) {
	return VBColorRGBCreate((_hex & 0x00FF0000) >> 0x10, 
							(_hex & 0x0000FF00) >> 0x08, 
							(_hex & 0x000000FF) >> 0x00);
}

VBULong VBColorRGBGetColorCode(VBColorRGB _color) {
	return (_color.r << 0x10) | (_color.g << 0x08) | _color.b;
}

VBUChar VBColorRGBGetR(VBColorRGB _color) {
	return _color.r;
}

VBUChar VBColorRGBGetG(VBColorRGB _color) {
	return _color.g;
}

VBUChar VBColorRGBGetB(VBColorRGB _color) {
	return _color.b;
}

VBColorRGB VBColorRGBInterpolate(VBColorRGB _color1, VBColorRGB _color2, VBFloat _num) {
    VBColorRGB _color;
    _color.r = _color1.r + (_color2.r - _color1.r) * _num;
    _color.g = _color1.g + (_color2.g - _color1.g) * _num;
    _color.b = _color1.b + (_color2.b - _color1.b) * _num;
    return _color;
}