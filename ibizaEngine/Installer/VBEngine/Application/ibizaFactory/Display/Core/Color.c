#include "Color.h"

ColorRGBA ColorRGBAInit(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	ColorRGBA color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

ColorHexRGBA ColorRGBAToColorHexRGBA(ColorRGBA color) {
	return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

ColorRGBA ColorHexRGBAToRGBAColor(ColorHexRGBA color) {
	return ColorRGBAInit((color & 0xFF000000) >> 24, 
						 (color & 0x00FF0000) >> 16, 
						 (color & 0x0000FF00) >> 8, 
						 (color & 0x000000FF) >> 0);
}

bool ColorRGBAIsEqual(ColorRGBA color1, ColorRGBA color2) {
	if(color1.r != color2.r)
		return false;
	if(color1.g != color2.g)
		return false;
	if(color1.b != color2.b)
		return false;
	if(color1.a != color2.a)
		return false;
	return true;
}