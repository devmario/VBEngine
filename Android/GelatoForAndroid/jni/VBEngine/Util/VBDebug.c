#include "VBDebug.h"
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "../VBConfig.h"
#include "../IO/VBSystem.h"

VBDebug* VBDebugAlloc(void) {
#ifdef _VB_DEBUG_
	return VBSystemCalloc(1, sizeof(VBDebug));
#else
    return VBNull;
#endif
}

VBDebug* VBDebugInitWithLogFilePath(VBDebug* _debug, const VBChar* _log_file_path) {
#ifdef _VB_DEBUG_
    if(_debug == VBNull)
		VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 초기화 하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.");
    
    if(_debug->path) {
        VBSystemFree(_debug->path);
    }
    _debug->path = VBSystemCalloc(strlen(_log_file_path) + 1, sizeof(VBChar));
    sprintf(_debug->path, "%s", _log_file_path);
    
    if(_debug->file) {
        fclose(_debug->file);
        _debug->file = VBNull;
    }
    _debug->file = fopen(_debug->path, "a+");
    if(_debug->file == VBNull) {
        VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: 디버거의 로그파일 생성에 실패하였습니다. 퍼미션이 존재하는 정확한 경로를 사용하세요.(문제가 발생한 파일경로: %s)", _debug->path);
    } else {
        VBChar _tmp_str[_VB_DEBUG_PRINT_BUFFER_SIZE_] = {0x00,};
        sprintf(_tmp_str, "\n--------------------VBDebugInit--------------------\n\n");
        fwrite(_tmp_str, sizeof(VBChar), strlen(_tmp_str), _debug->file);
    }
	return _debug;
#else
    return _debug;
#endif
}

void VBDebugFree(VBDebug** _debug) {
#ifdef _VB_DEBUG_
    if(*_debug == VBNull)
		VBDebugPrintAbort(*_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 Free 하려고 합니다. VBDebugAlloc하지 않은 디버거이거나 이미 Free했을 수 있습니다.");
    
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
#endif
}

void VBDebugAbort(VBDebug* _debug, VBBool _isAbort) {
#ifdef _VB_DEBUG_
    if(_isAbort)
        abort();
#endif
}

void VBDebugPrintAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
    va_list _args;
    va_start(_args, _str);
    
    vprintf((const VBChar*)_str, _args);
    printf("\n");
    
    va_end(_args);
    
    VBDebugAbort(_debug, _isAbort);
#endif
}

void VBDebugPrint(VBDebug* _debug, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
    va_list _args;
    va_start(_args, _str);
    
    vprintf((const VBChar*)_str, _args);
    printf("\n");
    
    va_end(_args);
#endif
}

void VBDebugLogFileClear(VBDebug* _debug) {
#ifdef _VB_DEBUG_
    if(_debug == VBNull)
        VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.VBDebugLogFileClear()은 VBNull인 디버거를 사용할 수 없습니다.");
    
    //로그파일 열려 있으면 파일 닫고 삭제
    if(_debug->file) {
        fclose(_debug->file);
        _debug->file = VBNull;
    }
    remove(_debug->path);
    
    VBChar* _path = VBSystemCalloc(sizeof(VBChar), strlen(_debug->path) + 1);
    sprintf(_path, "%s", _debug->path);
    //초기화(파일 다시열기)
    VBDebugInitWithLogFilePath(_debug, _path);
    VBSystemFree(_path);
#endif
}

void VBDebugPrintLogFile(VBDebug* _debug, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
    if(_debug == VBNull)
        VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.VBDebugPrintLogFile()은 VBNull인 디버거를 사용할 수 없습니다.");
    
    VBChar _tmp_str[_VB_DEBUG_PRINT_BUFFER_SIZE_] = {0x00,};
    
    va_list _args;
    va_start(_args, _str);
    vsprintf((char*)_tmp_str, (const char*)_str, _args);
    
    VBChar _return = '\n';
    fwrite(_tmp_str, sizeof(VBChar), strlen(_tmp_str), _debug->file);
    fwrite(&_return, sizeof(VBChar), 1, _debug->file);
    
    va_end(_args);
#endif
}

void VBDebugPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
    if(_debug == VBNull)
        VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.VBDebugPrintLogFileAbort()은 VBNull인 디버거를 사용할 수 없습니다.");
    
    VBChar _tmp_str[_VB_DEBUG_PRINT_BUFFER_SIZE_] = {0x00,};
    
    va_list _args;
    va_start(_args, _str);
    vsprintf((char*)_tmp_str, (const char*)_str, _args);
    
    VBChar _return = '\n';
    fwrite(_tmp_str, sizeof(VBChar), strlen(_tmp_str), _debug->file);
    fwrite(&_return, sizeof(VBChar), 1, _debug->file);
    
    va_end(_args);
    
    VBDebugAbort(_debug, _isAbort);
#endif
}

void VBDebugPrintAndPrintLogFile(VBDebug* _debug, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
    if(_debug == VBNull)
        VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.VBDebugPrintAndPrintLogFile()은 VBNull인 디버거를 사용할 수 없습니다.");
    
    VBChar _tmp_str[_VB_DEBUG_PRINT_BUFFER_SIZE_] = {0x00,};
    
    va_list _args;
    va_start(_args, _str);
    
    vprintf((const VBChar*)_str, _args);
    printf("\n");
    
    vsprintf((char*)_tmp_str, (const char*)_str, _args);
    
    VBChar _return = '\n';
    fwrite(_tmp_str, sizeof(VBChar), strlen(_tmp_str), _debug->file);
    fwrite(&_return, sizeof(VBChar), 1, _debug->file);
    
    va_end(_args);
#endif
}

void VBDebugPrintAndPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...) {
#ifdef _VB_DEBUG_
    if(_debug == VBNull)
        VBDebugPrintAbort(_debug, VBTrue, "VBEngine Log: VBNull인 디버거를 사용하려고 합니다. VBDebugAlloc하지 않은 디버거를 사용했을 수 있습니다.VBDebugPrintAndPrintLogFileAbort()은 VBNull인 디버거를 사용할 수 없습니다.");
    
    VBChar _tmp_str[_VB_DEBUG_PRINT_BUFFER_SIZE_] = {0x00,};
    
    va_list _args;
    va_start(_args, _str);
    
    vprintf((const VBChar*)_str, _args);
    printf("\n");
    
    vsprintf((char*)_tmp_str, (const char*)_str, _args);
    
    VBChar _return = '\n';
    fwrite(_tmp_str, sizeof(VBChar), strlen(_tmp_str), _debug->file);
    fwrite(&_return, sizeof(VBChar), 1, _debug->file);
    
    va_end(_args);
    
    if(_isAbort)
        abort();
#endif
}
