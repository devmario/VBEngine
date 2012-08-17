#include "VBColorRGBA.h"

VBColorRGBA VBColorRGBALoadIdentity(void) {
    return VBColorRGBACreate(0xFF, 0xFF, 0xFF, 0xFF);
}

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



VBColorRGBA VBColorRGBADraw_ONE_MINUS_SRC_ALPHA(VBColorRGBA _src, VBColorRGBA _dst) {
	float _as = 1.0;
	float _ad = 1.0 - ((float)_dst.a / (float)0xFF);
    
    float _r = _ad * _src.r + _dst.r * _as;
    float _g = _ad * _src.g + _dst.g * _as;
    float _b = _ad * _src.b + _dst.b * _as;
	
	_src.r = _r > 0xFF ? 0xFF : _r;
	_src.g = _g > 0xFF ? 0xFF : _g;
	_src.b = _b > 0xFF ? 0xFF : _b;
	_src.a = _src.a > _dst.a ? _src.a : _dst.a;
    
    return _src;
}

VBColorRGBA VBColorRGBADraw_SRC_ALPHA(VBColorRGBA _src, VBColorRGBA _dst) {
    float _ad = (float)_dst.a / ((float)_src.a + ((float)_dst.a / (float)0xFF) * ((float)0xFF - (float)_src.a));
    float _as = 1.0 - _ad;
    
    _src.r = (_dst.r * _ad) + (_src.r * _as);
    _src.g = (_dst.g * _ad) + (_src.g * _as);
    _src.b = (_dst.b * _ad) + (_src.b * _as);
    
    return _src;
}

VBColorRGBA VBColorRGBADrawColor(VBColorRGBA _color1, int _hex, int _maxDark, int _minDark) {
    VBUChar r = (_hex & 0xFF0000) >> 16;
    VBUChar g = (_hex & 0x00FF00) >> 8;
    VBUChar b = (_hex & 0x0000FF);
    
    float _miRGB = _minDark - _maxDark;
    
    int ir = r + (((_color1.r - _maxDark) / _miRGB) * (_minDark - r));
    int ig = g + (((_color1.g - _maxDark) / _miRGB) * (_minDark - g));
    int ib = b + (((_color1.b - _maxDark) / _miRGB) * (_minDark - b));
    _color1.r = ir > 0xFF ? 0xFF : (ir < 0x00 ? 0x00 : ir);
    _color1.g = ig > 0xFF ? 0xFF : (ig < 0x00 ? 0x00 : ig);
    _color1.b = ib > 0xFF ? 0xFF : (ib < 0x00 ? 0x00 : ib);
    return _color1;
}
