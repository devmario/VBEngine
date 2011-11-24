#include "VBPNGFile.h"
#include "VBSystem.h"
#include "../VBEngine.h"
#include "../Other/png/png.h"

VBPNGFile* VBPNGFileAlloc(void) {
	VBPNGFile* _png = VBSystemCalloc(1, sizeof(VBPNGFile));
	if(_png == VBNull) {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileAlloc() - 메모리 할당에 실패하였습니다.");
#endif
	}
	return _png;
}

VBPNGFile* VBPNGFileInit(VBPNGFile* _png) {
	if(_png) {
		VBPNGFileUnload(_png);
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileInit() - VBNull인 PNG파일을 초기화 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
	return _png;
}

VBPNGFile* VBPNGFileInitWithFilePath(VBPNGFile* _png, VBString* _path) {
#ifdef _VB_DEBUG_
    if(_path == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileInitWithFilePath() - VBNull인 파일경로 정보를 사용할 수 없습니다.");
#endif
	if(_png) {
		_png = VBPNGFileInit(_png);
		VBPNGFileLoad(_png, _path);
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileInitWithFilePath() - VBNull인 PNG파일을 초기화 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
	return _png;
}

void VBPNGFileFree(VBPNGFile** _png) {
	if(*_png) {
		VBPNGFileUnload(*_png);
		
		VBSystemFree(*_png);
		*_png = VBNull;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileFree() - VBNull인 PNG파일을 Free하려고 합니다. 이미 VBPNGFileFree하였거나 VBPNGFileAlloc하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
}

void VBPNGFileLoad(VBPNGFile* _png, VBString* _path) {
#ifdef _VB_DEBUG_
    if(_path == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBPNGFileLoad() - VBNull인 파일 경로를 사용할 수 없습니다.");
#endif 
    
	if(_png) {
		if(_png->loaded) {
			VBPNGFileUnload(_png);
		} else {
			_png->path = VBStringInitWithCString(VBStringAlloc(), VBStringGetCString(_path));
			
			FILE* _file = fopen(VBStringGetCString(_png->path), "r");
			if(_file == VBNull) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
												 "VBEngine Log: VBPNGFileLoad() - PNG파일이 열리지 않습니다. 경로나 퍼미션을 확인해 주세요. %s", VBStringGetCString(_path));
#endif
            }
			
			VBUChar _header[8] = {0,};
			fread(_header, sizeof(VBUChar), 8, _file);
			if(png_sig_cmp(_header, 0, 8)) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
												 "VBEngine Log: VBPNGFileLoad() - PNG파일이 아닙니다.");
#endif
            }
			
			png_structp _png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, VBNull, VBNull, VBNull);
			if(!_png_ptr) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
												 "VBEngine Log: VBPNGFileLoad() - PNG파일의 Read Struct생성이 실패하였습니다.");
#endif
            }
			
			png_infop _info_ptr = png_create_info_struct(_png_ptr);
			if(!_info_ptr) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
												 "VBEngine Log: VBPNGFileLoad() - PNG파일의 이미지의 정보를 불러올때 문제가 발생 했습니다.");
#endif
            }
			
			if(setjmp(png_jmpbuf(_png_ptr))) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
												 "VBEngine Log: VBPNGFileLoad() - PNG파일을 읽는중 이미지의 입출력에 문제가 발생 했습니다.");
#endif
            }
			
			png_init_io(_png_ptr, _file);
			png_set_sig_bytes(_png_ptr, 8);
			
			png_read_info(_png_ptr, _info_ptr);
			
			VBUChar _type = png_get_color_type(_png_ptr, _info_ptr);
			switch(_type) {
				case PNG_COLOR_TYPE_GRAY:
					_png->color_type = VBColorType_G;
					break;
				case PNG_COLOR_TYPE_GA:
					_png->color_type = VBColorType_GA;
					break;
				case PNG_COLOR_TYPE_RGB:
					_png->color_type = VBColorType_RGB;
					break;
				case PNG_COLOR_TYPE_RGBA:
					_png->color_type = VBColorType_RGBA;
					break;
				default:
#ifdef _VB_DEBUG_
					VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
													 "VBEngine Log: VBPNGFileLoad() - PNG파일의 해당 PNG가 엔진에서 지원하는 칼라타입을 사용하지 않습니다.(지원타입:G,GA,RGB,RGBA)");
#endif
					break;
			}
			_png->color_bit = png_get_bit_depth(_png_ptr, _info_ptr);
			_png->width = png_get_image_width(_png_ptr, _info_ptr);
			_png->height = png_get_image_height(_png_ptr, _info_ptr);
			
			VBShort _interlace = png_set_interlace_handling(_png_ptr);
			if(_interlace == 7) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
												 "VBEngine Log: VBPNGFileLoad() - PNG파일의 해당 PNG가 Interlacing입니다. 엔진에서 지원하지 않습니다.");
#endif
            }
			
			png_read_update_info(_png_ptr, _info_ptr);
			
			if(setjmp(png_jmpbuf(_png_ptr))) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
												 "VBEngine Log: VBPNGFileLoad() - PNG파일을 읽는중 이미지의 입출력에 문제가 발생 했습니다.");
#endif
            }
			
			png_bytep* _row_pointers = (png_bytep*)VBSystemMalloc(sizeof(png_bytep) * _png->height);
			VBULong _y;
			for(_y = 0; _y < _png->height; _y++)
				_row_pointers[_y] = (png_byte*)VBSystemMalloc(png_get_rowbytes(_png_ptr, _info_ptr));
			
			png_read_image(_png_ptr, _row_pointers);
			
			VBChar _color_byte = _png->color_bit / 8 * VBColorTypeGetSize(_png->color_type);
			_png->data_size = _png->width * _png->height * _color_byte;
			_png->data = VBSystemMalloc(_png->data_size);
			VBChar* _data_ptr = _png->data;
			for(_y = 0; _y < _png->height; _y++) {
				png_byte* _row = _row_pointers[_y];
				VBULong _cpy_size = sizeof(VBUChar) * _png->width * _color_byte;
				memcpy(_data_ptr, _row, _cpy_size);
				_data_ptr += _cpy_size;
				VBSystemFree(_row_pointers[_y]);
			}
			VBSystemFree(_row_pointers);
			
			png_destroy_read_struct(&_png_ptr, &_info_ptr, VBNull);
			
			fclose(_file);
			
			_png->loaded = VBTrue;
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileLoad() - VBNull인 PNG파일을 Load 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
}

void VBPNGFileUnload(VBPNGFile* _png) {
	if(_png) {
		if(_png->loaded) {
			if(_png->path)
				VBStringFree(&_png->path);
			_png->color_type = VBColorType_None;
			_png->color_bit = 0;
			_png->width = 0;
			_png->height = 0;
			
			_png->data_size = 0;
			if(_png->data)
				VBSystemFree(_png->data);
			
			_png->loaded = VBFalse;
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileUnload() - VBNull인 PNG파일을 Unload 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
}

VBBool VBPNGFilgGetIsLoaded(VBPNGFile* _png) {
	if(_png) {
		return _png->loaded;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFilgGetIsLoaded() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return VBFalse;
	}
}

VBString* VBPNGFileGetPath(VBPNGFile* _png) {
	if(_png) {
		return _png->path;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetPath() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return VBNull;
	}
}

VBColorType VBPNGFileGetColorType(VBPNGFile* _png) {
	if(_png) {
		return _png->color_type;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetColorType() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBUChar VBPNGFileGetColorBit(VBPNGFile* _png) {
	if(_png) {
		return _png->color_bit;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetColorBit() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBUShort VBPNGFileGetWidth(VBPNGFile* _png) {
	if(_png) {
		return _png->width;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetWidth() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBUShort VBPNGFileGetHeight(VBPNGFile* _png) {
	if(_png) {
		return _png->height;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetHeight() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBULong VBPNGFileGetDataSize(VBPNGFile* _png) {
	if(_png) {
		return _png->data_size;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetDataSize() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

void* VBPNGFileGetData(VBPNGFile* _png) {
	if(_png) {
		return _png->data;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBPNGFileGetData() - VBNull인 PNG파일을 접근 하려고 합니다. VBPNGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return VBNull;
	}
}
