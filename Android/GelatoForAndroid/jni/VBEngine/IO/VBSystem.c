#include "VBSystem.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../Util/VBArrayList.h"
#include "../VBConfig.h"
#include "../VBEngine.h"


VBSystemEndian _system_endian_type = VBSystemEndian_None;

VBSystemEndian VBSystemGetEndian(void) {
	if(_system_endian_type == VBSystemEndian_None) {
		VBShort _check_endian = 1;
		if(*(VBChar *)&_check_endian == 1) {
			_system_endian_type = VBSystemEndian_Little;
		} else {
			_system_endian_type = VBSystemEndian_Big;
		}
	}
	return _system_endian_type;
}

void VBSystemEndianSwap(void* _ptr, VBUShort _size) {
    if(_ptr == VBNull) {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBSystemEndianSwap() - 주소가 VBNull인 메모리 포인터는 사용할 수 없습니다.");
    }
    
	register VBByte* _p = (VBByte*)_ptr;
	register VBByte* _q = ((VBByte*)_ptr) + _size - 1;
	
	while(_p < _q) {
		VBByte _tmp = *_p;
		
		*_p = *_q;
		*_q = _tmp;
		
		_p++;
		_q--;
	}
}

void* VBSystemCalloc(VBSize _size, VBSize _count) {
    void* _ptr = calloc(_size, _count);
    if(!_ptr)
        VBDebugPrintAbort(VBEngineGetDefaultDebuger(), VBTrue, "VBEngine Log: VBSystemCalloc() - 메모리 할당에 실폐하였습니다.");
    return _ptr;
}

void* VBSystemMalloc(VBSize _size) {
    void* _ptr = malloc(_size);
    if(!_ptr)
        VBDebugPrintAbort(VBEngineGetDefaultDebuger(), VBTrue, "VBEngine Log: VBSystemMalloc() - 메모리 할당에 실폐하였습니다.");
    return _ptr;
}

void* VBSystemRealloc(void* _re_ptr, VBSize _size) {
    void* _ptr = realloc(_re_ptr, _size);
    if(!_ptr)
        VBDebugPrintAbort(VBEngineGetDefaultDebuger(), VBTrue, "VBEngine Log: VBSystemRealloc() - 메모리 할당에 실폐하였습니다.");
    return _ptr;
}

void* VBSystemMemorySet(void* _ptr, VBLong _hex, VBSize _set_size) {
    return memset(_ptr, _hex, _set_size);
}

VBLong VBSystemUSleep(VBULong _m_sec) {
    return usleep(_m_sec);
}

void* VBSystemMemoryCopy(void* _dest_ptr, const void* _src_ptr, VBSize _copy_size) {
    return memcpy(_dest_ptr, _src_ptr, _copy_size);
}

void VBSystemFree(void* _ptr) {
    if(_ptr) {
        free(_ptr);
    } else {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBSystemFree() - 값이 VBNull인 포인터를 free할 수 없습니다.");
    }
}
