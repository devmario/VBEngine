#include "VBDebug.h"
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "../VBConfig.h"
#include "../IO/VBSystem.h"


#ifdef _VB_ANDROID_
#include <android/log.h>
#define LOG_TAG    "Android_Native_Log"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "libnav", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "libnav", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "libnav", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "libnav", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav", __VA_ARGS__)
#endif

VBDebug* VBDebugAlloc(void) {
#ifdef _VB_DEBUG_
	VBDebug* _debug = VBSystemCalloc(1, sizeof(VBDebug));
	if(_debug == VBNull)
		VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: 메모리할당에 실패하였습니다.");
	return _debug;
#endif
	
#ifndef _VB_DEBUG_
	return VBNull;
#endif
}

VBDebug* VBDebugInit(VBDebug* _debug, const VBChar* _log_file_path) {
#ifdef _VB_DEBUG_
	if(_debug) {
		_debug->path = VBSystemCalloc(strlen(_log_file_path) + 1, sizeof(VBChar));
		if(_debug->path == VBNull) {
			VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: 메모리할당에 실패하였습니다.");
		} else {
			sprintf(_debug->path, "%s", _log_file_path);
			
			if(_debug->file) {
				fclose(_debug->file);
				_debug->file = VBNull;
			}
			_debug->file = fopen(_debug->path, "a+");
			if(_debug->file == VBNull) {
				VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: 디버거의 로그파일 생성에 실패하였습니다. 퍼미션이 존재하는 정확한 경로를 사용하세요.");
			}
		}
	} else {
		VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 초기화 하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.");
	}
	return _debug;
#endif
	
#ifndef _VB_DEBUG_
	return VBNull;
#endif
}

void VBDebugFree(VBDebug** _debug) {
#ifdef _VB_DEBUG_
	if(*_debug) {
		if((*_debug)->path) {
			VBSystemFree((*_debug)->path);
			(*_debug)->path = VBNull;
		}
		if((*_debug)->file) {
			fclose((*_debug)->file);
			(*_debug)->file = VBNull;
		}
		VBSystemFree(*_debug);
		*_debug = VBNull;
	} else {
		VBDebugPrintAbort(*_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 Free 하려고 합니다. VBDebugAlloc하지 않은 디버거이거나 이미 Free했을 수 있습니다.");
	}
#endif
}

void VBDebugAbort(VBDebug* _debug, VBBool _isAbort) {
#ifdef _VB_DEBUG_
	if(_debug) {
		if(_isAbort)
			abort();
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugPrintAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
	if(_debug) {
		va_list _args;
		va_start(_args, _str);
		
		VBDebugPrint(_debug, _str, _args);
		
		va_end(_args);
		
		VBDebugAbort(_debug, _isAbort);
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugPrint(VBDebug* _debug, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
	if(_debug) {
		va_list _args;
		va_start(_args, _str);
		
		vprintf((const VBChar*)_str, _args);
		printf("\n");
		
		va_end(_args);
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugLogFileClear(VBDebug* _debug) {
#ifdef _VB_DEBUG_
	if(_debug) {
		if(_debug->file) {
			fclose(_debug->file);
			_debug->file = NULL;
		}
		remove(_debug->path);
		
		VBDebugInit(_debug, _debug->path);
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugPrintLogFile(VBDebug* _debug, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
	if(_debug) {
		if(_debug->file) {
			VBChar _tmp_str[USHRT_MAX] = {0,};
			
			va_list _args;
			va_start(_args, _str);
			vsprintf((char*)_tmp_str, (const char*)_str, _args);
			
			VBChar _return = '\n';
			fwrite(_tmp_str, sizeof(VBChar), strlen(_tmp_str), _debug->file);
			fwrite(&_return, sizeof(VBChar), 1, _debug->file);
			
			va_end(_args);
		} else {
			VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: 디버거의 로그파일이 존재하지 않습니다. VBDebugInit가 실행되지 않을 수 있습니다.");
		}
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
	if(_debug) {
		va_list _args;
		va_start(_args, _str);
		
		VBDebugPrintLogFile(_debug, _str, _args);
		
		va_end(_args);
		
		VBDebugAbort(_debug, _isAbort);
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugPrintAndPrintLogFile(VBDebug* _debug, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
	if(_debug) {
		va_list _args;
		va_start(_args, _str);
		
		VBDebugPrint(_debug, _str, _args);
		
		VBDebugPrintLogFile(_debug, _str, _args);
		
		va_end(_args);
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}

void VBDebugPrintAndPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
	if(_debug) {
		va_list _args;
		va_start(_args, _str);
		
		VBDebugPrint(_debug, _str, _args);
		
		VBDebugPrintLogFileAbort(_debug, _isAbort, _str, _args);
		
		va_end(_args);
	} else {
		printf("VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.\n");
		abort();
	}
#endif
}
