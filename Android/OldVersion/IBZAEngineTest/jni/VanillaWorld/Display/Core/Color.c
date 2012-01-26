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

ColorRGB ColorRGBInit(unsigned char r, unsigned char g, unsigned char b) {
	ColorRGB color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}

bool ColorRGBIsEqual(ColorRGB color1, ColorRGB color2) {
	if(color1.r != color2.r)
		return false;
	if(color1.g != color2.g)
		return false;
	if(color1.b != color2.b)
		return false;
	return true;
}

ColorHexRGB ColorRGBToColorHexRGB(ColorRGB color) {
	return (color.r << 16) | (color.g << 8) | color.b;
}

ColorRGB ColorHexRGBToRGBColor(ColorHexRGB color) {
	return ColorRGBInit((color & 0xFF0000) >> 16, 
						(color & 0x00FF00) >> 8, 
						(color & 0x0000FF) >> 0);
}