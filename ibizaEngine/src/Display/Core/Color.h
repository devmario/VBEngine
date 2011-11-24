#ifndef __COLOR_H__
#define __COLOR_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
	typedef struct ColorRGBA ColorRGBA;
	
	typedef unsigned int ColorHexRGBA;
	
	struct ColorRGBA {
		unsigned char r, g, b, a;
	};
	
	ColorRGBA ColorRGBAInit(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	ColorHexRGBA ColorRGBAToColorHexRGBA(ColorRGBA color);
	ColorRGBA ColorHexRGBAToRGBAColor(ColorHexRGBA color);
	bool ColorRGBAIsEqual(ColorRGBA color1, ColorRGBA color2);
	
#ifdef __cplusplus
}
#endif

#endif
