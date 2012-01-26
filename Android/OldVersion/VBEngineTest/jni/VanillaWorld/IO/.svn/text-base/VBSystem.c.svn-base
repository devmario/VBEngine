 #include "VBSystem.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "../Core/VBArrayList.h"
#include "../VBConfig.h"
#include "../VBEngine.h"

VBSystemEndian _system_endian_type = VBSystemEndian_None;

typedef struct {
	void* ptr;
	VBSize mem;
} VBSystemMemory;

VBUShort _system_alloc_stack_count = 0;
VBSystemMemory _system_alloc_stack[USHRT_MAX];

VBUShort _system_alloc_num = 0;
VBSize _system_alloc_use_memory = 0;

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
#ifdef _VB_DEBUG_
    if(_ptr == VBNull) {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBSystemEndianSwap() - 첫번째 파라메터로 VBNull을 사용할 수 없습니다.");
    }
#endif
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
#ifdef _VB_DEBUG_
	while(_system_alloc_stack[_system_alloc_stack_count].ptr != VBNull) {
		_system_alloc_stack_count++;
		if(_system_alloc_stack_count == USHRT_MAX)
			_system_alloc_stack_count = 0;
	}
	
	void* _ptr = calloc(_size, _count);
	
	_system_alloc_num++;
	_system_alloc_use_memory += _size * _count;
	
	_system_alloc_stack[_system_alloc_stack_count].ptr = _ptr;
	_system_alloc_stack[_system_alloc_stack_count].mem = _size * _count;
	
	return _ptr;
#endif
	
#ifndef _VB_DEBUG_
	return calloc(_size, _count);
#endif
}

void* VBSystemMalloc(VBSize _size) {
#ifdef _VB_DEBUG_
	while(_system_alloc_stack[_system_alloc_stack_count].ptr != VBNull) {
		_system_alloc_stack_count++;
		if(_system_alloc_stack_count == USHRT_MAX)
			_system_alloc_stack_count = 0;
	}
	
	void* _ptr = malloc(_size);
	
	_system_alloc_num++;
	_system_alloc_use_memory += _size;
	
	_system_alloc_stack[_system_alloc_stack_count].ptr = _ptr;
	_system_alloc_stack[_system_alloc_stack_count].mem = _size;
	
	return _ptr;
#endif
	
#ifndef _VB_DEBUG_
	return malloc(_size);
#endif
}

void* VBSystemRealloc(void* _re_ptr, VBSize _size) {

#ifdef _VB_DEBUG_
	while(_system_alloc_stack[_system_alloc_stack_count].ptr != _re_ptr) {
		_system_alloc_stack_count++;
		if(_system_alloc_stack_count == USHRT_MAX)
			_system_alloc_stack_count = 0;
	}
	
	void* _ptr = realloc(_re_ptr, _size);
	
	_system_alloc_use_memory -= _system_alloc_stack[_system_alloc_stack_count].mem - _size;
	
	_system_alloc_stack[_system_alloc_stack_count].ptr = _ptr;
	_system_alloc_stack[_system_alloc_stack_count].mem = _size;
	
	return _ptr;
#endif
	
#ifndef _VB_DEBUG_
	return realloc(_re_ptr, _size);
#endif
}

void* VBSystemMemorySet(void* _ptr, VBLong _hex, VBSize _set_size) {
    return memset(_ptr, _hex, _set_size);
}

VBLong VBSystemUSleep(VBULong _m_sec) {
	#ifdef _VB_IPHONE_
		return usleep(_m_sec);
	#endif
	
	#ifdef _VB_ANDROID_
		usleep(_m_sec);
		return 0;
	#endif
}

void* VBSystemMemoryCopy(void* _dest_ptr, const void* _src_ptr, VBSize _copy_size) {
    return memcpy(_dest_ptr, _src_ptr, _copy_size);
}

void VBSystemFree(void* _ptr) {
#ifdef _VB_DEBUG_
    if(_ptr == VBNull) {
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBSystemFree() - 값이 VBNull인 포인터를 free할 수 없습니다.");
    }
    
	while(_system_alloc_stack[_system_alloc_stack_count].ptr != _ptr) {
		_system_alloc_stack_count++;
		if(_system_alloc_stack_count == USHRT_MAX)
			_system_alloc_stack_count = 0;
	}
	
	free(_ptr);
	
	_system_alloc_num--;
	_system_alloc_use_memory -= _system_alloc_stack[_system_alloc_stack_count].mem;
	
	_system_alloc_stack[_system_alloc_stack_count].ptr = VBNull;
	_system_alloc_stack[_system_alloc_stack_count].mem = 0;
#endif
	
#ifndef _VB_DEBUG_
	free(_ptr);
#endif
}

VBULongLong VBSystemGetUseMemory(void) {
#ifdef _VB_DEBUG_
	return _system_alloc_use_memory;
#endif
	
#ifndef _VB_DEBUG_
	return 0;
#endif
}

VBULong VBSystemGetAllocCount(void) {
#ifdef _VB_DEBUG_
	return _system_alloc_num;
#endif
	
#ifndef _VB_DEBUG_
	return 0;
#endif
}
