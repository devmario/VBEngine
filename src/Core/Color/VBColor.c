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
	}
	return _color_size;
}
