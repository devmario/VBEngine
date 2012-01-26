#ifndef __COLOR_H__
#define __COLOR_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
	typedef struct ColorRGBA ColorRGBA;
	
	typedef unsigned int ColorHexRGBA;
	
	typedef struct ColorRGB ColorRGB;
	
	typedef unsigned int ColorHexRGB;
	
	struct ColorRGB {
		unsigned char r, g, b;
	};
	
	struct ColorRGBA {
		unsigned char r, g, b, a;
	};
	
	ColorRGBA ColorRGBAInit(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	ColorHexRGBA ColorRGBAToColorHexRGBA(ColorRGBA color);
	ColorRGBA ColorHexRGBAToRGBAColor(ColorHexRGBA color);
	
	ColorRGB ColorRGBInit(unsigned char r, unsigned char g, unsigned char b);
	bool ColorRGBIsEqual(ColorRGB color1, ColorRGB color2);
	ColorHexRGB ColorRGBToColorHexRGB(ColorRGB color);
	ColorRGB ColorHexRGBToRGBColor(ColorHexRGB color);
	
#ifdef __cplusplus
}
#endif

#endif
