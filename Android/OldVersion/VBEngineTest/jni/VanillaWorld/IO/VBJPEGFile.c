#include "VBJPEGFile.h"
#include "VBSystem.h"
#include "../VBEngine.h"
#include "../Other/jpeg/jinclude.h"
#include "../Other/jpeg/jpeglib.h"


VBJPEGFile* VBJPEGFileAlloc(void) {
	VBJPEGFile* _jpeg = VBSystemCalloc(1, sizeof(VBJPEGFile));
	if (_jpeg == VBNull) {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileAlloc() - 메모리 할당에 실패하였습니다.");
#endif
	}
	return _jpeg;
}

VBJPEGFile* VBJPEGFileInit(VBJPEGFile* _jpeg) {
	if (_jpeg) {
		VBJPEGFileUnload(_jpeg);
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileInit() - VBNull인 JPEG파일을 초기화 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
	return _jpeg;
}

VBJPEGFile* VBJPEGFileInitWithFilePath(VBJPEGFile* _jpeg, VBString* _path) {
	if(_jpeg) {
		_jpeg = VBJPEGFileInit(_jpeg);
		VBJPEGFileLoad(_jpeg, _path);
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileInitWithFilePath() - VBNull인 JPEG파일을 초기화 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
	return _jpeg;
}

void VBJPEGFileFree(VBJPEGFile** _jpeg) {
	if (*_jpeg) {
		VBJPEGFileUnload(*_jpeg);
		
		VBSystemFree(*_jpeg);
		*_jpeg = VBNull;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileFree() - VBNull인 JPEG파일을 Free하려고 합니다. 이미 VBJPEGFileFree하였거나 VBJPEGFileAlloc하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
	
}

void VBJPEGFileLoad(VBJPEGFile* _jpeg, VBString* _path) {
	if (_jpeg) {
		if (_jpeg->loaded) {
			VBJPEGFileUnload(_jpeg);
		} else {
			_jpeg->path = VBStringInitWithCString(VBStringAlloc(), VBStringGetCString(_path));
			
			struct jpeg_decompress_struct _cInfo;
			struct jpeg_error_mgr _cErrMgr;
			
			FILE* _file = fopen(VBStringGetCString(_jpeg->path), "rb");
			if (_file == VBNull) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
												 "VBEngine Log: VBJPEGFileLoad() - JPEG파일이 열리지 않습니다. 경로나 퍼미션을 확인해 주세요.");
#endif
            }
			
			_cInfo.err = jpeg_std_error(&_cErrMgr);
			jpeg_create_decompress(&_cInfo);
			jpeg_stdio_src(&_cInfo, _file);
			
			VBUChar _header = jpeg_read_header(&_cInfo, VBTrue);
			if(!_header) {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
												 "VBEngine Log: VBJPEGFileLoad() - JPEG파일이 아닙니다.");
#endif
            }
			
			jpeg_start_decompress(&_cInfo);
			
			switch (_cInfo.out_color_space) {
				case JCS_GRAYSCALE:
					_jpeg->color_bit = _cInfo.data_precision;
					_jpeg->color_type = VBColorType_G;
					break;
				case JCS_RGB:
					_jpeg->color_bit = _cInfo.data_precision;
					_jpeg->color_type = VBColorType_RGB;
					break;
				default:
#ifdef _VB_DEBUG_
					VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue,
													 "VBEngine Log: VBJPEGFileLoad() - JPEG파일의 해당 JPEG가 엔진에서 지원하는 칼라타입을 사용하지 않습니다.(지원타입:G,RGB)");
#endif
					break;
			}
			
			_jpeg->width =  _cInfo.output_width;
			_jpeg->height =  _cInfo.output_height;
			
			VBSize _row_size = (_jpeg->color_bit / 8 * _cInfo.num_components) * _cInfo.output_width;
			_jpeg->data_size = _row_size * _cInfo.output_height;
			_jpeg->data = VBSystemMalloc(_jpeg->data_size);
			VBUChar* _dtptr = _jpeg->data;
			while (_cInfo.output_scanline < _cInfo.output_height) {
				jpeg_read_scanlines(&_cInfo, &_dtptr, 1);
				_dtptr += _row_size;
			}
			
			fclose(_file);
			
			jpeg_finish_decompress(&_cInfo);
			jpeg_destroy_decompress(&_cInfo);
			
			_jpeg->loaded = VBTrue;
		} 	
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileLoad() - VBNull인 JPEG파일을 Load 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
}


void VBJPEGFileUnload(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		if(_jpeg->loaded) {
			if(_jpeg->path)
				VBStringFree(&_jpeg->path);
			_jpeg->color_type = VBColorType_None;
			_jpeg->color_bit = 0;
			_jpeg->width = 0;
			_jpeg->height = 0;
			
			_jpeg->data_size = 0;
			if(_jpeg->data)
				VBSystemFree(_jpeg->data);
			
			_jpeg->loaded = VBFalse;
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileUnload() - VBNull인 JPEG파일을 Unload 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
	}
}

VBBool VBJPEGFileGetIsLoaded(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->loaded;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetIsLoaded() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return VBFalse;
	}
}

VBString* VBJPEGFileGetPath(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->path;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetPath() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return VBNull;
	}
}

VBColorType VBJPEGFileGetColorType(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->color_type;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetColorType() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBUChar VBJPEGFileGetColorBit(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->color_bit;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetColorBit() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBUShort VBJPEGFileGetWidth(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->width;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetWidth() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBUShort VBJPEGFileGetHeight(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->height;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetHeight() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

VBULong VBJPEGFileGetDataSize(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->data_size;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetDataSize() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return 0;
	}
}

void* VBJPEGFileGetData(VBJPEGFile* _jpeg) {
	if(_jpeg) {
		return _jpeg->data;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBJPEGFileGetData() - VBNull인 JPEG파일을 접근 하려고 합니다. VBJPEGFileAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
		return VBNull;
	}
}
