#include "VBArrayVector.h"
#include "../IO/VBSystem.h"
#include "../VBEngine.h"
#include <stdlib.h>
#include <limits.h>

#define _STEPSIZE_ 50

VBArrayVector* VBArrayVectorAlloc(void) {
	VBArrayVector* _vec = (VBArrayVector*)VBSystemCalloc(1, sizeof(VBArrayVector));
    
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
	return _vec;
}


VBArrayVector* VBArrayVectorInitWithStepSize(VBArrayVector* _vec, VBLong _ss) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorInitWithStepSize() - 초기화에 실패하였습니다.");
    if(_ss == 0)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorInitWithStepSize() - Step Size가 없는 Vector는 초기화 할 수 없습니다.");
    
#endif
    
    if(_vec) {
        _vec->stepSize = _ss;
        if(_vec->data) {
            _vec->data = (void**)VBSystemRealloc(_vec->data, sizeof(void*) * _vec->stepSize);
        } else {
            _vec->data = (void**)VBSystemCalloc(sizeof(void*), _vec->stepSize);
        }
        _vec->len = 0;
    }
    
	return _vec;
}

VBArrayVector* VBArrayVectorInit(VBArrayVector* _vec) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorInit() - 초기화에 실패하였습니다.");
#endif
    
	_vec = VBArrayVectorInitWithStepSize(_vec, _STEPSIZE_);
	return _vec;
}

void VBArrayVectorFree(VBArrayVector** _vec) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorFree() - VBNull인 Vector는 해제 할수 없습니다. VBArrayVectorInit()하지 않았거나 이미 VBArrayVectorFree()했을 수 있습니다.");
#endif
    
	if(*_vec) {
        if((*_vec)->data && (*_vec)->stepSize) {
            VBSystemFree((*_vec)->data);
            (*_vec)->data = VBNull;
        }
        VBSystemFree(*_vec);
		*_vec = VBNull;
	}
}

void* VBArrayVectorGetDataAt(VBArrayVector* _vec, VBULong _at) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorGetDataAt() - VBNull인 Vector요소의 데이터의 위치를 구할 수 없습니다. VBArrayVectorAlloc()하지 않았을 수 있습니다.");
#endif
    
	if(_at > _vec->len - 1)
		_at = _vec->len - 1;
	return *(_vec->data + _at);
}

void VBArrayVectorAddBack(VBArrayVector* _vec, void* _data) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorAddBack() - VBNull인 Vector에 Data를 삽입할 수 없습니다. VBArrayVectorAlloc()하지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorAddBack() - VBNull인 Data는 Vector에 추가할 수 없습니다.");
#endif
    
    if(_vec->len > _vec->stepSize) {
        _vec->stepSize = _vec->len + _STEPSIZE_;
        _vec->data = (void**)VBSystemRealloc(_vec->data, sizeof(void*) * _vec->stepSize);
    }
    void** _in_data = _vec->data;
    _in_data += _vec->len;
    *_in_data = _data;
    _vec->len++;
}

void VBArrayVectorAddFront(VBArrayVector* _vec, void* _data) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorAddFront() - VBNull인 Vector에 Data를 삽입할 수 없습니다. VBArrayVectorAlloc()하지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorAddFront() - VBNull인 Data는 Vector에 추가할 수 없습니다.");
#endif
    
    VBArrayVectorAddAt(_vec, _data, 0);
}

void VBArrayVectorAddAt(VBArrayVector* _vec, void* _data, VBULong _at) {
#ifdef _VB_DEBUG_
	if(_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayVectorAddAt() - VBNull인 Vector에 Data를 삽입할 수 없습니다. VBArrayVectorAlloc()하지 않았을 수 있습니다.");
#endif
    
    _vec->len++;
    if(_at > _vec->len) 
        _at = _vec->len - 1;
    if(_vec->len > _vec->stepSize) {
        _vec->stepSize = _vec->len + _STEPSIZE_;
        _vec->data = (void**)VBSystemRealloc(_vec->data, sizeof(void*) * _vec->stepSize);
    }
        
    for(VBLongLong _i = _vec->len - 1; _i >= 0; _i--) {
        if(_i > _at) 
            _vec->data[_i] = _vec->data[_i - 1];
    }
    _vec->data[_at] = _data;
}

void* VBArrayVectorRemoveBack(VBArrayVector* _vec) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorRemoveBack() - VBNull인 Vector에 Data를 삭제할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif

	if(_vec->len)
		return VBArrayVectorRemoveAt(_vec, _vec->len - 1);
	return VBNull;
}

void* VBArrayVectorRemoveFront(VBArrayVector* _vec) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorRemoveFront() - VBNull인 Vector에 Data를 삭제할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	if(_vec->len)
		return VBArrayVectorRemoveAt(_vec, 0);
	return VBNull;
}

void* VBArrayVectorRemove(VBArrayVector* _vec, void* _data) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorRemove() - VBNull인 Vector에 Data를 삭제할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorRemove() - VBNull인 Data는 Vector에서 삭제할 수 없습니다.");
#endif
    VBULong _i;
    for(_i = 0; _i < _vec->len; _i++) {
        if(_data == VBArrayVectorDataAtIndex(_vec, _i)) {
            return VBArrayVectorRemoveAt(_vec, _i);        
        }
    }
    return VBNull;
}

void* VBArrayVectorRemoveAt(VBArrayVector* _vec, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorRemoveAt() - VBNull인 Vector에서 Data를 삭제할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
    void* _returnData = VBArrayVectorDataAtIndex(_vec, _at);
    VBLong i;
    if(_at > _vec->len) 
        _at = _vec->len - 1;
    for(i = _at; i < _vec->len - 1; i++) {
          _vec->data[i] = _vec->data[i + 1];
    }
    _vec->len--;
    //데이터가 없어도 프리하지 않고 데이터는 벡터를 소멸시킬때 한번에 소멸한다.
//    if(_vec->len < 1) {
//        if(_vec->data) {
//            VBSystemFree(_vec->data);
//            _vec->data = VBNull;
//        }
//    }
    return _returnData;
}

void* VBArrayVectorDataAtIndex(VBArrayVector* _vec, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorDataAtIndex() - VBNull인 Vector에서 Data를 구할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
    if(_vec->data) {
        if(_at < _vec->len) {
            return _vec->data[_at];
        } else {
            return VBNull;
        }
    } else {
        return VBNull;
    }
}

VBLong VBArrayVectorIndexAtData(VBArrayVector* _vec, void* _data) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorIndexAtData() - VBNull인 Vector에서 Index를 구할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorIndexAtData() - VBNull인 Data는 Vector에서 구할 수 없습니다.");
#endif
    
    VBULong _i;
    for(_i = 0; _i < _vec->len; _i++) {
        if(_vec->data[_i] == _data) 
            return _i;
    }
    return -1;
}

void VBArrayVectorReplaceAt(VBArrayVector* _vec, void* _data, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorReplaceAt() - VBNull인 Vector에서 Data를 교환할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorReplaceAt() - VBNull인 Data는 Vector에서 교환할 수 없습니다.");
#endif
    
	void** newData = VBArrayVectorGetDataAt(_vec, _at);
	if (*newData) {
		*newData = _data;
	}
}

void VBArrayVectorSwapAt(VBArrayVector* _vec, VBULong _at_1, VBULong _at_2) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorSwapAt() - VBNull인 Vector에서 지정된 2개의 Data를 Swap할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	if (_at_1 != _at_2) {
		VBLong _len = VBArrayVectorGetLength(_vec);
		if (_at_1 < _len && _at_2 < _len) {
			void* _data_1;
			void* _data_2;
			VBULong _max = _at_1 > _at_2 ? _at_1 : _at_2;
			VBULong _i;
			VBArrayVector** _vec_data = *_vec->data;
			for (_i = 0; _i < _max; _i++) {
				if (_i == _at_1) {
					_vec_data = _data_1;
				} else if (_i == _at_2) {
					_vec_data = _data_2;
				}
				_vec_data = *_vec->data;
			}
			VBArrayVectorSwapData(_vec, _data_1, _data_2);
		}
	}
}

void VBArrayVectorSwapData(VBArrayVector* _vec, void* _data_1, void* _data_2) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorSwapData() - VBNull인 Vector에서 Data를 Swap할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
    if(_data_1 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorSwapData() - VBNull인 첫 번쨰 Data는 Vector에서 교환할 수 없습니다.");
    if(_data_2 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorSwapData() - VBNull인 두 번쨰 Data는 Vector에서 교환할 수 없습니다.");
#endif
    
	if (_data_1 && _data_2) {
		void* _tmp_data = _data_1;
		_data_1 = _data_2;
		_data_2 = _tmp_data;	
	}
}

VBULong VBArrayVectorGetLength(VBArrayVector* _vec) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorGetLength() - VBNull인 Vector의 길이를 구할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
    return _vec->len;
}

void VBArrayVectorQuickSort(VBArrayVector* _vec, VBArrayVectorSortFunc _func) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorQuickSort() - VBNull인 Vector의 Data를 정렬할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
    if(_func == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorQuickSort() - VBNull인 SortFuncion을 사용할 수 없습니다.");
#endif
    
    qsort(_vec->data, _vec->len, sizeof(void*), (int (*)(const void*, const void*))_func);
}

void VBArrayVectorReverse(VBArrayVector* _vec) {
#ifdef _VB_DEBUG_
    if(_vec == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayVectorReverse() - VBNull인 Vector의 Data는 Reverse할 수 없습니다. VBArrayVectorAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	VBLong _i;
	VBLong* _temp;
	for (_i = 0; _i < _vec->len / 2; _i++) {
		_temp = _vec->data[_vec->len - 1 - _i];
        _vec->data[_vec->len - 1 - _i] = _vec->data[_i];
		_vec->data[_i] = _temp;
    }
}





