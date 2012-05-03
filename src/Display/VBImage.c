#include "VBImage.h"
#include <stdlib.h>
#include <string.h>
#include "../VBEngine.h"

VBImage* VBImageAlloc(void) {
	VBImage* _img = VBSystemCalloc(1, sizeof(VBImage));
    
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageAlloc() - 메모리 할당에 실패하였습니다.");
#endif
		
	return _img;
}

VBImage* VBImageInit(VBImage* _img) {
#ifdef _VB_DEBUG_
    if(_img == VBNull) {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageInit() - VBNull인 이미지를 초기화 하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
    }
#endif
    
	if(_img) {
		_img->color_type = VBColorType_None;
		_img->color_bit = 0;
		_img->width = 0;
		_img->height = 0;
        _img->is_loaded = VBFalse;
		
		if(_img->data) {
			VBSystemFree(_img->data);
            _img->data = VBNull;
		}
	}
	
	return _img;
}

VBImage* VBImageInitWithData(VBImage* _img, VBColorType _color_type, VBUChar _color_bit, VBULong _width, VBULong _height, void* _data) {
#ifdef _VB_DEBUG_
    if(_img == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBImageInitWithData() - VBNull인 이미지를 초기화 하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBImageInitWithData() - 이미지 데이터 주소가 VBNull 입니다. 이미지를 초기화를 할수 없습니다.");
#endif
    
	if(_img) {
		VBImageInit(_img);
		
		_img->color_type = _color_type;
		_img->color_bit = _color_bit;
		_img->width = _width;
		_img->height = _height;
		
		VBULong _size = (_color_bit / 8 * VBColorTypeGetSize(_color_type)) * _width * _height;
#ifdef _VB_DEBUG_
		if(_size < _color_bit / 8 * VBColorTypeGetSize(_color_type))
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
											 "VBEngine Log: VBImageInitWithData() - 이미지 사이즈가 1픽셀 이미지 보다 작습니다. 이미지를 초기화를 할수 없습니다.");
#endif
		
		if(_img->data) {
			_img->data = realloc(_img->data, _size);
		} else {
			_img->data = malloc(_size);
		}
		
#ifdef _VB_DEBUG_
		if(_img->data == VBNull)
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
											 "VBEngine Log: VBImageInitWithData() - 메모리 할당에 실패하였습니다.");
#endif
        
		memcpy(_img->data, _data, _size);
        
        _img->is_loaded = VBTrue;
	} 
    
	return _img;
}

VBImage* VBImageInitWithPath(VBImage* _img, VBString* _path) {
#ifdef _VB_DEBUG_
    if(_img == VBNull) {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBImageInitWithPath() - VBNull인 이미지를 초기화 하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
    }
    if(_path == VBNull) {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBImageInitWithPath() - VBNull인 이미지 경로를 사용할 수 없습니다. 경로명을 지정해 주세요.");
    }
#endif
	if(_img) {
//		VBImageInit(_img);          //VBImageLoad에서 수행함.
		VBImageLoad(_img, _path);
	}
	
	return _img;
}

VBImage* VBImageInitAndClear(VBImage* _img, VBColorType _color_type, VBUChar _color_bit, VBULong _width, VBULong _height) {
#ifdef _VB_DEBUG_
    if(_img == VBNull) {
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageInitAndClear() - VBNull인 이미지를 초기화 하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
	}
#endif
    
	if(_img) {
		VBImageInit(_img);
		
		VBULong _size = (_color_bit / 2) * _width * _height;
#ifdef _VB_DEBUG_
		if(_size < _color_bit / 2)
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
											 "VBEngine Log: VBImageInitAndClear() - 이미지 사이즈가 1픽셀 이미지 보다 작습니다. 이미지를 초기화를 할수 없습니다.");
#endif
		
		_img->color_type = _color_type;
		_img->color_bit = _color_bit;
		_img->width = _width;
		_img->height = _height;
		
		_img->data = VBSystemMalloc(_size);
        
#ifdef _VB_DEBUG_
		if(_img->data == VBNull)
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
											 "VBEngine Log: VBImageInitAndClear() - 메모리 할당에 실패하였습니다.");
#endif
		
		VBImageClearPixel(_img);
	} 
	
	return _img;
}

void VBImageFree(VBImage** _img) {
#ifdef _VB_DEBUG_
    if(*_img == VBNull) {
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBImageFree() - VBNull인 이미지를 Free하려고 합니다. 이미 VBImageFree하였거나 VBImageAlloc하지 않은 파일을 사용했을 수 있습니다.");
	}
#endif
    
	if(*_img) {
		*_img = VBImageInit(*_img);
		
		VBSystemFree(*_img);
		*_img = VBNull;
	} 
}

VBImage* VBImageCopy(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageCopy() - VBNull인 이미지를 카피하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	return VBImageInitWithData(VBImageAlloc(), _img->color_type, _img->color_bit, _img->width, _img->height, _img->data);
}

void VBImageLoad(VBImage* _img, VBString* _path) {
#ifdef _VB_DEBUG_
    if(_img == VBNull) {
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageLoad() - VBNull에 이미지를 로드 하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
	}
#endif
    
	if(_img) {
		VBImageInit(_img);
		
		VBLong _index = VBStringLastIndexOfCString(_path, ".") + 1;
		VBString* _ext = VBStringSliceAndCopy(_path, _index, VBStringGetLength(_path));
		VBStringUpperCase(_ext);
		
		if(VBStringIsEqualToCString(_ext, "PNG")) {
			VBPNGFile* _png = VBPNGFileInitWithFilePath(VBPNGFileAlloc(), _path);
			
			_img->color_type = VBPNGFileGetColorType(_png);
			_img->color_bit = VBPNGFileGetColorBit(_png);
			_img->width = VBPNGFileGetWidth(_png);
			_img->height = VBPNGFileGetHeight(_png);
			
			VBULong _size = VBPNGFileGetDataSize(_png);
			void* _data = VBPNGFileGetData(_png);
			
			_img->data = VBSystemCalloc(1, _size);
			memcpy(_img->data, _data, _size);
			
			VBPNGFileFree(&_png);
		} else {
#ifdef _VB_DEBUG_
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
											 "VBEngine Log: VBImageLoad() - VBEngine이 지원하는 이미지 확장자가 아닙니다. PNG를 이용하세요.(대소문자 무시)");
#endif
		}
		
		VBStringFree(&_ext);
        _img->is_loaded = VBTrue;
	} 
}

VBULong VBImageGetImageDataSize(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetImageDataSize() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
    
	return (_img->color_bit / 2) * _img->width * _img->height;
}

void* VBImageGetImageData(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetImageData() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
    
	return _img->data;
}

VBColorType VBImageGetColorType(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetColorType() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
    
	return _img->color_type;
}

VBUChar VBImageGetColorBit(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetColorBit() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
    
	return _img->color_bit;
}

VBULong VBImageGetWidth(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetWidth() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
    
	return _img->width;
}

VBULong VBImageGetHeight(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetHeight() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
    
	return _img->height;
}

void* VBImageGetPixelColor(VBImage* _img, VBULong _x, VBULong _y) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetPixelColor() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
    
	if(_x >= _img->width || _y >= _img->height)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageGetPixelColor() - 가져오려는 픽셀이 이미지 사이즈보다 큽니다.");
#endif
	
	if(_x >= _img->width || _y >= _img->height)
        return NULL;
	return _img->data + ( _img->color_bit / 8 * VBColorTypeGetSize(_img->color_type) * _y * _img->width) + ( _img->color_bit / 8 * VBColorTypeGetSize(_img->color_type) * _x);
}

void VBImageSetPixelColor(VBImage* _img, VBULong _x, VBULong _y, void* _color) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageSetPixelColor() - VBNull인 이미지에 접근하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	void* _data_ptr = VBImageGetPixelColor(_img, _x, _y);
	memcpy(_data_ptr, _color, _img->color_bit / 8 * VBColorTypeGetSize(_img->color_type));
}

void VBImageClearPixel(VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageClearPixel() - VBNull인 이미지를 Clear하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
	
	if(_img->data)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageClearPixel() - 픽셀 데이터가 없는 이미지를 Clear하려고 합니다.");
#endif
	
	memset(VBImageGetImageData(_img), 0x00, VBImageGetImageDataSize(_img));
}

void VBImageClearPixelAtBox(VBImage* _img, VBULong _x, VBULong _y, VBULong _width, VBULong _height) {
#ifdef _VB_DEBUG_
	if(_img == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageClearPixelAtBox() - VBNull인 이미지를 Clear하려고 합니다. VBImageAlloc하지 않은 이미지를 사용했을 수 있습니다.");
	
	if(_img->data)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageClearPixelAtBox() - 픽셀 데이터가 없는 이미지를 Clear하려고 합니다.");
	
	if(_img->width < _x && _img->height < _y && _img->width <= _x + _width && _img->height <= _y + _height)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBImageClearPixelAtBox() - 픽셀 데이터가 없는 곳의 위치를 Clear하려고 합니다.");
#endif
	
	for(VBULong _i = _y; _i < _y + _height; _i++) {
		for(VBULong _j = _x; _j < _x + _width; _i++) {
			void* _data_ptr = VBImageGetPixelColor(_img, _j, _i);
			memset(_data_ptr, 0x00, _img->color_bit / 2);
		}
	}
}

VBBool VBImageGetIsLoaded(VBImage* _img) {
    return _img->is_loaded;
}

