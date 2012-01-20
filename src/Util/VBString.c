#include "VBString.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "../IO/VBSystem.h"
#include "../VBEngine.h"

VBString* VBStringAlloc(void) {
	VBString* _str = (VBString*)VBSystemCalloc(sizeof(VBString), 1);
    
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
	return _str;
}

VBString* VBStringInit(VBString* _str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringInit() - 초기화에 실패하였습니다.");
#endif
    
	_str->len = 0;
	if(_str->data) {
		VBSystemFree(_str->data);
		_str->data = VBNull;
	}
	return _str;
}

VBString* VBStringInitWithCString(VBString* _str, const VBChar* _cstr) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringInitWithCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_cstr == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringInitWithCString() - 두번째 파라메터 _cstr에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBStringSetCString(_str, _cstr);
	return _str;
}

VBString* VBStringInitWithCStringFormat(VBString* _str, const VBChar* _fmt, ...) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringInitWithCStringFormat() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_fmt == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringInitWithCStringFormat() - 두번째 파라메터 _fmt에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBChar _tmp_str[USHRT_MAX] = {0,};
	
	va_list _ap;
	va_start(_ap, _fmt);
	vsprintf(_tmp_str, _fmt, _ap);
	va_end(_ap);
    	
	VBStringSetCString(_str, _tmp_str);
    
	return _str;
}

void VBStringFree(VBString** _str) {
#ifdef _VB_DEBUG_
	if(*_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringFree() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다. VBString*의 주소값을 지정해 주세요.");
#endif
    
	if(*_str) {
		if((*_str)->data) {
			VBSystemFree((*_str)->data);
			(*_str)->data = VBNull;
		}
		VBSystemFree(*_str);
		*_str = VBNull;
	}
}

VBString* VBStringCopy(VBString* _str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringCopy() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	return VBStringInitWithCString(VBStringAlloc(), VBStringGetCString(_str));
}

void VBStringSetCString(VBString* _str, const VBChar* _cstr) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSetCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_cstr == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSetCString() - 두번째 파라메터 _cstr에 VBNull을 지정할 수 없습니다.");
#endif
    
    if(_str && _cstr) {
        _str->len = strlen((const char*)_cstr);
        if(_str->data) {
            _str->data = VBSystemRealloc(_str->data, sizeof(VBChar) * (_str->len + 1));
        } else {
            _str->data = VBSystemCalloc(_str->len + 1, sizeof(VBChar));
        }
        strncpy(_str->data, (const char*)_cstr, _str->len);   
        ((VBChar*)_str->data)[_str->len] = '\0';
    }
}

void VBStringAddCString(VBString* _str, const VBChar* _cstr) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringAddCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_cstr == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringAddCString() - 두번째 파라메터 _cstr에 VBNull을 지정할 수 없습니다.");
#endif
    
	if(_str->data) {
		VBULong _tmp_len = _str->len;
		VBULong _len = strlen((const char*)_cstr);
		_str->len += _len;
		
		void* _str_ptr = _str->data = VBSystemRealloc(_str->data, (_str->len + 1) * sizeof(VBChar));
		
		_str_ptr += _tmp_len;
		memset(_str_ptr, 0x00, sizeof(VBChar) * (_len + 1));
		
		strncpy(_str_ptr, (const char*)_cstr, _len);
	} else {
		VBStringSetCString(_str, _cstr);
	}
}

void VBStringSetCStringFormat(VBString* _str, const VBChar* _fmt, ...) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSetCStringFormat() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_fmt == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSetCStringFormat() - 두번째 파라메터 _fmt에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBChar _tmp_str[USHRT_MAX] = {0,};
	
	va_list _ap;
	va_start(_ap, _fmt);
	vsprintf(_tmp_str, _fmt, _ap);
	va_end(_ap);
	
	VBStringSetCString(_str, _tmp_str);
}

void VBStringAddCStringFormat(VBString* _str, const VBChar* _fmt, ...) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringAddCStringFormat() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_fmt == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringAddCStringFormat() - 두번째 파라메터 _fmt에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBChar _tmp_str[USHRT_MAX] = {0,};
	
	va_list _ap;
	va_start(_ap, _fmt);
	vsprintf((char*)_tmp_str, (const char*)_fmt, _ap);
	va_end(_ap);
	
	VBStringAddCString(_str, _tmp_str);
}

VBChar* VBStringGetCString(VBString* _str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringGetCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	return (VBChar*)_str->data;
}

VBUShort VBStringGetLength(VBString* _str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringGetLength() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	return _str->len;
}

VBChar VBStringGetCharAt(VBString* _str, VBUShort _at) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringGetCharAt() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	if(_str->data) {
		VBChar* _tmpStr = _str->data;
		if(_at < _str->len) {
			return _tmpStr[_at];
		} else {
			return '\0';
		}
	} else {
		return '\0';
	}
}

void VBStringSetCharAt(VBString* _str, VBUShort _at, VBChar _char) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSetCharAt() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	if(_str->data) {
		VBChar* _tmpStr = _str->data;
		if(_at < _str->len) {
			_tmpStr[_at] = _char;
		}
	}
}

VBBool VBStringIsEqual(VBString* _str_1, VBString* _str_2) {
#ifdef _VB_DEBUG_
	if(_str_1 == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIsEqual() - 첫번째 파라메터 _str_1에 VBNull을 지정할 수 없습니다.");
    if(_str_2 == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIsEqual() - 두번째 파라메터 _str_2에 VBNull을 지정할 수 없습니다.");
#endif
    
	if(!strcmp(VBStringGetCString(_str_1), VBStringGetCString(_str_2))) {
		return VBTrue;
	} else {
		return VBFalse;
	}
}

VBBool VBStringIsEqualToCString(VBString* _str, const VBChar* _cstr) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIsEqualToCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_cstr == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIsEqualToCString() - 두번째 파라메터 _cstr에 VBNull을 지정할 수 없습니다.");
#endif
    
	if(!strcmp(VBStringGetCString(_str), _cstr)) {
		return VBTrue;
	} else {
		return VBFalse;
	}
}

VBLong VBStringIndexOf(VBString* _str, VBString* _of_str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIndexOf() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_of_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIndexOf() - 두번째 파라메터 _of_str에 VBNull을 지정할 수 없습니다.");
#endif
    
	return VBStringIndexOfCString(_str, VBStringGetCString(_of_str));
}

VBLong VBStringIndexOfCString(VBString* _str, const VBChar* _of_cstr) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIndexOfCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_of_cstr == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringIndexOfCString() - 두번째 파라메터 _of_str에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBUShort _size = VBStringGetLength(_str);
	VBUShort _csize = strlen(_of_cstr);
	if(_size < _csize)
		return -1;
	VBLong _ci = 0;
	for(VBLong _i = 0; _i < _size; _i++) {
		if(VBStringGetCharAt(_str, _i) == _of_cstr[_ci]) {
			_ci++;
		} else if(_ci == _csize) {
			return _i - _csize;
		} else if(_ci != 0) {
			_ci = 0;
		}
	}
	return -1;
}

VBLong VBStringLastIndexOf(VBString* _str, VBString* _of_str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringLastIndexOf() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_of_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringLastIndexOf() - 두번째 파라메터 _of_str에 VBNull을 지정할 수 없습니다.");
#endif
    
	return VBStringLastIndexOfCString(_str, VBStringGetCString(_of_str));
}

VBLong VBStringLastIndexOfCString(VBString* _str, const VBChar* _of_cstr) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringLastIndexOfCString() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
    if(_of_cstr == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringLastIndexOfCString() - 두번째 파라메터 _of_str에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBUShort _size = VBStringGetLength(_str);
	VBUShort _csize = strlen(_of_cstr);
	if(_size < _csize)
		return -1;
	VBLong _ci = _csize - 1;
	for(VBLong _i = _size - 1; _i >= 0; _i--) {
		if(VBStringGetCharAt(_str, _i) == _of_cstr[_ci]) {
			_ci--;
		} else if(_ci < 0) {
			return _i + 1;
		} else if(_ci != _csize - 1) {
			_ci = _csize - 1;
		}
	}
	return -1;
}

void VBStringSlice(VBString* _str, VBUShort _start, VBUShort _end) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSlice() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBUShort _len = VBStringGetLength(_str);
	if(_start <= _len) {
		if(_end <= _len) {
			if(_start < _end) {
				VBChar _tmp[USHRT_MAX] = {0,};
				VBChar* _tmp_ptr = _tmp;
				for(VBUShort _i = _start; _i < _end; _i++) {
					*_tmp_ptr = VBStringGetCharAt(_str, _i);
					_tmp_ptr++;
				}
				VBStringSetCString(_str, _tmp);
			}
		}
	}
}

VBString* VBStringSliceAndCopy(VBString* _str, VBUShort _start, VBUShort _end) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSliceAndCopy() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	VBString* _to_str = VBStringCopy(_str);
	VBStringSlice(_to_str, _start, _end);
	return _to_str;
}

void VBStringLowerCase(VBString* _str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringLowerCase() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	for(VBUShort _i = 0; _i < VBStringGetLength(_str); _i++) {
		VBChar _char = VBStringGetCharAt(_str, _i);
		if(_char >= 'A' && _char <= 'Z') {
			_char += 'a' - 'A';
			VBStringSetCharAt(_str, _i, _char);
		}
	}
}

void VBStringUpperCase(VBString* _str) {
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringUpperCase() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
	for(VBUShort _i = 0; _i < VBStringGetLength(_str); _i++) {
		VBChar _char = VBStringGetCharAt(_str, _i);
		if(_char >= 'a' && _char <= 'z') {
			_char -= 'a' - 'A';
			VBStringSetCharAt(_str, _i, _char);
		}
	}
}

void VBStringSubstr(VBString* _str, VBUShort _start, VBUShort _len) { 
#ifdef _VB_DEBUG_
	if(_str == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBStringSubstr() - 첫번째 파라메터 _str에 VBNull을 지정할 수 없습니다.");
#endif
    
    _len = VBStringGetLength(_str);
    if (_start <= _len) {
        VBChar _tmp[USHRT_MAX] = {0,};
        VBChar* _tmp_ptr = _tmp;
        for (VBShort _i = _start; _i < _len; _i++) {
            *_tmp_ptr = VBStringGetCharAt(_str, _i);
            _tmp_ptr++;
        }
        VBStringSetCString(_str, _tmp);
    }
}


