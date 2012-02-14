#include "VBFile.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../VBEngine.h"

VBFile* VBFileAlloc(void) {
	VBFile* _file = VBSystemCalloc(1, sizeof(VBFile));
    
#ifdef _VB_DEBUG_
	if(_file == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBFileAlloc() - 메모리할?�에 ?�패?��??�니??");
#endif
    
	return _file;
}

VBFile* VBFileInit(VBFile* _file) {
	if(_file) {
		_file->mode = VBFileMode_None;
		_file->endian = VBSystemEndian_None;
		
		if(_file->file) {
			fclose(_file->file);
			_file->file = VBNull;
		}
		
		_file->size = 0;
		_file->offset = 0;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBFalse, 
										 "VBEngine Log: VBFileInit() - VBNull???�일??초기???�려�??�니?? VBFileAlloc?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
	return _file;
}

VBFile* VBFileInitWithOpen(VBFile* _file, VBString* _path, VBFileMode _mode) {
	_file = VBFileInit(_file);
	VBFileOpen(_file, _path, _mode);
	return _file;
}

void VBFileFree(VBFile** _file) {
	if(*_file) {
		*_file = VBFileInit(*_file);
		VBSystemFree(*_file);
		*_file = VBNull;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileInitWithOpen() - VBNull???�일??Free?�려�??�니?? ?��? VBFileFree?��?거나 VBFileAlloc?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
}

void VBFileOpen(VBFile* _file, VBString* _path, VBFileMode _mode) {
	if(_file) {
		if(_file->file == VBNull) {
			switch(_mode) {
				case VBFileMode_Read:
#ifdef __ANDROID__
					_file->file = android_fopen(VBStringGetCString(_path), "r");
#else
					_file->file = fopen(VBStringGetCString(_path), "r");
#endif
					break;
				case VBFileMode_Write:
#ifdef __ANDROID__
					_file->file = android_fopen(VBStringGetCString(_path), "w");
#else
					_file->file = fopen(VBStringGetCString(_path), "w");
#endif
					break;
				case VBFileMode_ReadWrite:
#ifdef __ANDROID__
					_file->file = android_fopen(VBStringGetCString(_path), "a+");
#else
					_file->file = fopen(VBStringGetCString(_path), "a+");
#endif
					break;
				case VBFileMode_None:
#ifdef _VB_DEBUG_
					VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
													 VBFalse,
													 "VBEngine Log: VBFileOpen() - VBFileMode_None모드로는 ?�일???????�습?�다.");
#endif
					break;
				default:
#ifdef _VB_DEBUG_
					VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
													 VBFalse,
													 "VBEngine Log: VBFileOpen() - VBFileMode??지?�되지 ?��? 모드�??�용?�여???�일???????�습?�다.");
#endif
					break;
					
			}
			
			if(_file->file) {
				_file->mode = _mode;
				_file->endian = VBSystemGetEndian();
				
				fseek(_file->file, 0, SEEK_END);
				_file->size = ftell(_file->file);
				fseek(_file->file, 0, SEEK_SET);
				_file->offset = 0;
			} else {
				_file->file = VBNull;
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
												 VBFalse, 
												 "VBEngine Log: VBFileOpen() - ?�일???�리지 ?�습?�다. 경로??권한??문제가 ?�을 ???�습?�다.");
#endif
			}
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileOpen() - VBNull???�일??Open?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
#ifdef __ANDROID__
	if (_file->file != VBNull || _mode != VBFileMode_Read)
		return;

	VBArrayVector* vector = VBEngineFileInfoGetVector();
	int i = 0;
	VBUShort _fd = 0;
	VBSize _off = 0;
	VBSize _size = 0;
	VBUShort vectorLen = vector->len;
	if (vectorLen < 1) {
		_file->file = VBNull;
		return;
	}
	for (i; i < vectorLen; i++) {
		VBEngineFileInfo* info = (VBEngineFileInfo*) VBArrayVectorGetDataAt(vector, i);
		if (info != VBNull && VBStringIsEqual(_path, info->path)) {
			_fd = dup(info->fd);
			_off = info->off;
			_size = info->len;	
			break;	
		}
	}
	if(_fd == 0) {
		_file->file = VBNull;
		return;
	}
	if (_file) {
		if (_file->file == VBNull) {
			switch (_mode) {
			case VBFileMode_Read:
				_file->file = fdopen(_fd, "r");
				break;
			case VBFileMode_Write:
				_file->file = fdopen(_fd, "w");
				break;
			case VBFileMode_ReadWrite:
				_file->file = fdopen(_fd, "a+");
				break;
			case VBFileMode_None:
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
						VBFalse,
						"VBEngine Log: VBFileOpen() - VBFileMode_None모드로는 ?�일???????�습?�다.");
#endif
				break;
			default:
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
						VBFalse,
						"VBEngine Log: VBFileOpen() - VBFileMode??지?�되지 ?��? 모드�??�용?�여???�일???????�습?�다.");
#endif
				break;

			}

			if (_file->file) {
				_file->mode = _mode;
				_file->endian = VBSystemGetEndian();

				_file->size = _size;
				fseek(_file->file, _off, SEEK_SET);
				_file->offset = 0;
			} else {
				_file->file = VBNull;
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
						VBFalse,
						"VBEngine Log: VBFileOpen() - ?�일???�리지 ?�습?�다. 경로??권한??문제가 ?�을 ???�습?�다.");
#endif
			}
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileOpen() - VBNull???�일??Open?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
#endif
}

void VBFileClose(VBFile* _file) {
	if(_file) {
		if(_file->file == VBNull)
#ifdef _VB_DEBUG_
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
											 VBFalse,
											 "VBEngine Log: VBFileClose() - ?�려?��? ?��? ?�일??Close?�려�??�니??\n");
#endif
		_file = VBFileInit(_file);
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse,
										 "VBEngine Log: VBFileClose() - VBNull???�일??Close?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
}

VBBool VBFileGetIsOpen(VBFile* _file) {
	if(_file) {
		if(_file->file)
			return VBTrue;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileGetIsOpen() - VBNull???�일??Open?��?�?가?�오?�고 ?�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
	return VBFalse;
}

VBFileMode VBFileGetMode(VBFile* _file) {
	if(_file) {
		return _file->mode;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileGetMode() - VBNull???�일??모드�?가?�오?�고 ?�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
	return VBFileMode_None;
}

void VBFileSetEndian(VBFile* _file, VBSystemEndian _endian) {
	if(_file) {
		_file->endian = _endian;
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileSetEndian() - VBNull???�일???�디?�을 ?�정?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
}

VBSystemEndian VBFileGetEndian(VBFile* _file) {
	if(_file) {
		return _file->endian;
	} else {
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileGetEndian() - VBNull???�일???�디?�을 가?�오?�고 ?�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
	}
	return VBSystemEndian_None;
}

void VBFileSetOffset(VBFile* _file, VBUShort _offset) {
	if(_file) {
		if(_file->file) {
			if(_offset < _file->size) {
				fseek(_file->file, _offset, SEEK_SET);
				_file->offset = _offset;
			} else {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
												 VBFalse,
												 "VBEngine Log: VBFileSetOffset() - ?�일???�이즈�? 벗어?�는 ?�프?�을 ?�정?��??�니??(?�경???�프?�의 변?�는 ?�습?�다.)");
#endif
			}
		} else {
#ifdef _VB_DEBUG_
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
											 VBFalse,
											 "VBEngine Log: VBFileSetOffset() - ?�일???�려?�어???�니??");
#endif
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileSetOffset() - VBNull???�일???�프?�을 ?�정?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
}

VBUShort VBFileGetOffset(VBFile* _file) {
	if(_file)
		return _file->offset;
	else
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileGetOffset() - VBNull???�일???�프?�을 가?�오?�고 ?�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
	return 0;
}

VBUShort VBFileGetSize(VBFile* _file) {
	if(_file)
		return _file->size;
	else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileGetSize() - VBNull???�일???�이즈�? 가?�오?�고 ?�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
    }
	return 0;
}

VBUShort VBFileWrite(VBFile* _file, void* _ptr, VBUShort _size, VBUShort _len) {
	if(_file) {
		if(_file->file) {
			if(_file->mode == VBFileMode_Write || _file->mode == VBFileMode_ReadWrite) {
				if(VBSystemGetEndian() != _file->endian)
					VBSystemEndianSwap(_ptr, _size * _len);
				VBUShort _w_size = fwrite(_ptr, _size, _len, _file->file);
				_file->offset += _w_size;
				_file->size += _w_size;
				return _w_size;
			} else {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
												 VBFalse, 
												 "VBEngine Log: VBFileWrite() - Write?????�습?�다. ?�일모드 ?�인???�주?�요.");
#endif
			}
		} else {
#ifdef _VB_DEBUG_
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
											 VBFalse, 
											 "VBEngine Log: VBFileWrite() - ?�려?��? ?��? ?�일??Write?????�습?�다.");
#endif
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileWrite() - VBNull???�일??Write?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
	return 0;
}

VBUShort VBFileRead(VBFile* _file, void* _ptr, VBUShort _size, VBUShort _len) {
	if(_file) {
		if(_file->file) {
			if(_file->mode == VBFileMode_Read || _file->mode == VBFileMode_ReadWrite) {
				VBUShort _r_size = fread(_ptr, _size, _len, _file->file);
				if(VBSystemGetEndian() != _file->endian)
					VBSystemEndianSwap(_ptr, _size * _len);
				_file->offset += _r_size;
				return _r_size;
			} else {
#ifdef _VB_DEBUG_
				VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
												 VBFalse, 
												 "VBEngine Log: VBFileRead() - Write?????�습?�다. ?�일모드 ?�인???�주?�요.");
#endif
			}
		} else {
#ifdef _VB_DEBUG_
			VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
											 VBFalse, 
											 "VBEngine Log: VBFileRead() - ?�려?��? ?��? ?�일?� Read?????�습?�다.");
#endif
		}
	} else {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileRead() - VBNull???�일??Read?�려�??�니?? VBFileInit(VBFileAlloc())?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	}
	return 0;
}

void VBFileCopy(VBString* _src, VBString* _des) {

	VBFile* _fsrc = VBFileInit(VBFileAlloc()); // src stream open -> read mode
	VBFile* _fdes = VBFileInit(VBFileAlloc()); // des stream open -> write mode

	VBFileOpen(_fsrc, _src, VBFileMode_Read);
	VBFileOpen(_fdes, _des, VBFileMode_Write);

	if (_fsrc->file == VBNull) {
		VBFileFree(&_fsrc);
		VBFileFree(&_fdes);
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileCopy() - _src(source file) VBFileOpen???�패?��??�니??");
#endif
		return;
	}

	VBSize read_size = 0;
	long fileSize = _fsrc->size;
	VBChar* buffer = (VBChar*) VBSystemMalloc(sizeof(VBChar) * 1024);
	VBUShort typeSize = sizeof(VBChar);
	VBUShort bufferSize = 1024 / typeSize;
	while (1) {
		if ((fileSize -= bufferSize) > 0) {
			read_size = VBFileRead(_fsrc, buffer, typeSize, bufferSize);
			VBFileWrite(_fdes, buffer, typeSize, read_size);
		} else {
			if ((fileSize += bufferSize) > 0) {
				read_size = VBFileRead(_fsrc, buffer, typeSize, fileSize);
				VBFileWrite(_fdes, buffer, typeSize, read_size);
			}
			break;
		}
	}
	VBSystemFree(buffer);
	VBFileFree(&_fsrc);
	VBFileFree(&_fdes);
}

VBSize VBFileCopyToMemory(VBString* _src, void** _buffer) {
	VBFile* _fsrc = VBFileInit(VBFileAlloc()); // src stream open -> read mode
	VBFileOpen(_fsrc, _src, VBFileMode_Read);
	if (_fsrc->file == VBNull) {
		VBFileFree(&_fsrc);
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileCopyToMemory() - _src(source file) VBFileOpen???�패?��??�니??");
#endif
		return 0;
	}
	VBSize fileSize = _fsrc->size;
	VBSize read_size = 0;
	*_buffer = VBSystemMalloc(fileSize);
	VBUShort typeSize = sizeof(void);
	VBUShort bufferSize = fileSize / typeSize;
	if ((read_size = VBFileRead(_fsrc, *_buffer, typeSize, bufferSize)) < 1) {
#ifdef _VB_DEBUG_
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(),
										 VBFalse, 
										 "VBEngine Log: VBFileCopyToMemory() - _src(source file) VBFileRead???�패?��??�니??");
#endif
		return 0;
	}

	VBFileFree(&_fsrc);
	return fileSize;
}
VBUShort VBFileWriteByte(VBFile* _file, VBByte _byte) {
	return VBFileWrite(_file, &_byte, sizeof(VBByte), 1);
}

VBUShort VBFileReadByte(VBFile* _file, VBByte* _byte) {
	return VBFileRead(_file, _byte, sizeof(VBByte), 1);
}

VBUShort VBFileWriteBytes(VBFile* _file, VBByte* _bytes, VBUShort _len) {
	return VBFileWrite(_file, _bytes, sizeof(VBByte), _len);
}

VBUShort VBFileReadBytes(VBFile* _file, VBByte* _bytes, VBUShort _len) {
	return VBFileRead(_file, _bytes, sizeof(VBByte), _len);
}

VBUShort VBFileWriteChar(VBFile* _file, VBChar _char) {
	return VBFileWrite(_file, &_char, sizeof(VBChar), 1);
}

VBUShort VBFileReadChar(VBFile* _file, VBChar* _char) {
	return VBFileRead(_file, _char, sizeof(VBChar), 1);
}

VBUShort VBFileWriteUChar(VBFile* _file, VBUChar _char) {
	return VBFileWrite(_file, &_char, sizeof(VBUChar), 1);
}

VBUShort VBFileReadUChar(VBFile* _file, VBUChar* _char) {
	return VBFileRead(_file, _char, sizeof(VBChar), 1);
}

VBUShort VBFileWriteShort(VBFile* _file, VBShort _short) {
	return VBFileWrite(_file, &_short, sizeof(VBShort), 1);
}

VBUShort VBFileReadShort(VBFile* _file, VBShort* _short) {
	return VBFileRead(_file, _short, sizeof(VBShort), 1);
}

VBUShort VBFileWriteUShort(VBFile* _file, VBUShort _short) {
	return VBFileWrite(_file, &_short, sizeof(VBUShort), 1);
}

VBUShort VBFileReadUShort(VBFile* _file, VBUShort* _short) {
	return VBFileRead(_file, _short, sizeof(VBUShort), 1);
}

VBUShort VBFileWriteLong(VBFile* _file, VBLong _long) {
	return VBFileWrite(_file, &_long, sizeof(VBLong), 1);
}

VBUShort VBFileReadLong(VBFile* _file, VBLong* _long) {
	return VBFileRead(_file, _long, sizeof(VBLong), 1);
}

VBUShort VBFileWriteULong(VBFile* _file, VBULong _long) {
	return VBFileWrite(_file, &_long, sizeof(VBULong), 1);
}

VBUShort VBFileReadULong(VBFile* _file, VBULong* _long) {
	return VBFileRead(_file, _long, sizeof(VBULong), 1);
}

VBUShort VBFileWriteLongLong(VBFile* _file, VBLongLong _longlong) {
	return VBFileWrite(_file, &_longlong, sizeof(VBLongLong), 1);
}

VBUShort VBFileReadLongLong(VBFile* _file, VBLongLong* _longlong) {
	return VBFileRead(_file, _longlong, sizeof(VBLongLong), 1);
}

VBUShort VBFileWriteULongLong(VBFile* _file, VBULongLong _longlong) {
	return VBFileWrite(_file, &_longlong, sizeof(VBULongLong), 1);
}

VBUShort VBFileReadULongLong(VBFile* _file, VBULongLong* _longlong) {
	return VBFileRead(_file, _longlong, sizeof(VBULongLong), 1);
}

VBUShort VBFileReadFloat(VBFile* _file, VBFloat* _float) {
	return VBFileRead(_file, _float, sizeof(VBFloat), 1);
}

VBUShort VBFileReadDouble(VBFile* _file, VBDouble* _float) {
	return VBFileRead(_file, _float, sizeof(VBDouble), 1);
}
