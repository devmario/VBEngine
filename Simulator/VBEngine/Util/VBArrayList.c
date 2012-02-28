#include "VBArrayList.h"
#include "../IO/VBSystem.h"
#include "../VBEngine.h"

void q_sort(VBArrayList* _list, VBArrayListNode* left, VBArrayListNode* right, int li, int ri, VBArrayListSortFunc _func);
void quickSort(VBArrayList* _list, VBArrayListSortFunc _func);

VBArrayList* VBArrayListAlloc(void) {
	VBArrayList* _list = VBSystemCalloc(1, sizeof(VBArrayList));
    
#ifdef _VB_DEBUG_
	if(_list == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayListAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
	return _list;
}

VBArrayList* VBArrayListInit(VBArrayList* _list) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListInit() - 초기화에 실패하였습니다.");
    
#endif
    
	VBArrayListNode* _node = _list->s_node;
	while(_node) {
		VBArrayListNode* _tmpNode = _node->next;
		VBSystemFree(_node);
		_node = _tmpNode;
	}
	_list->s_node = VBNull;
	_list->e_node = VBNull;
	_list->len = 0;
	
	return _list;
}

void VBArrayListFree(VBArrayList** _list) {
#ifdef _VB_DEBUG_
	if(*_list == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBArrayListFree() - VBNull인 List요소는 해제 할수 없습니다. VBArrayListAlloc하지 않았거나 이미 VBArrayListFree했을 수 있습니다.");
#endif
    
	if(*_list) {
		VBArrayListInit(*_list);
		VBSystemFree(*_list);
		*_list = VBNull;
	}
}

void VBArrayListAddBack(VBArrayList* _list, void* _data) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListAddBack() - VBNull인 List요소에 데이터를 추가할 수 없습니다. VBArrayListAlloc하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListAddBack() - VBNull인 Data는 List에 추가할 수 없습니다.");

#endif
    
	VBArrayListNode* _node = (VBArrayListNode*)VBSystemMalloc(sizeof(VBArrayListNode));
	_node->data = _data;
	if(_list->len == 0){
		_node->prev = VBNull;
		_node->next = VBNull;
		
		_list->e_node = _node;
		_list->s_node = _node;
	} else {
		VBArrayListNode* _pre = _list->e_node;
		_node->prev = _pre;
		_node->next = VBNull;
		_pre->next = _node;
		
		_list->e_node = _node;
	}
	_list->len++;
}

void VBArrayListAddFront(VBArrayList* _list, void* _data) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListAddFront() - VBNull인 List요소에 데이터를 추가할 수 없습니다. VBArrayListAlloc하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListAddFront() - VBNull인 Data는 List에 추가할 수 없습니다.");
#endif
    
	VBArrayListNode* _node = (VBArrayListNode*)VBSystemMalloc(sizeof(VBArrayListNode));
	_node->data = _data;
	if(_list->len == 0){
		_node->prev = VBNull;
		_node->next = VBNull;
		
		_list->e_node = _node;
		_list->s_node = _node;
	} else {
		VBArrayListNode* _next = _list->s_node;
		_node->prev = VBNull;
		_node->next = _next;
		_next->prev = _node;
		
		_list->s_node = _node;
	}
	_list->len++;
}

void VBArrayListAddAt(VBArrayList* _list, void* _data, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListAddAt() - VBNull인 List요소에 데이터를 추가할 수 없습니다. VBArrayListAlloc하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListAddAt() - VBNull인 Data는 List에 추가할 수 없습니다.");
#endif

	if(_at == 0) {
		VBArrayListAddFront(_list, _data);
	} else if(_at < _list->len) {
		VBArrayListNode* _pre = VBArrayListGetNodeAt(_list, _at - 1);
		VBArrayListNode* _node = (VBArrayListNode*)VBSystemMalloc(sizeof(VBArrayListNode));
		VBArrayListNode* _next = VBArrayListGetNodeAt(_list, _at);
		_pre->next = _node;
		_node->prev = _pre;
		_node->data = _data;
		_node->next = _next;
		_next->prev = _node;
	} else {
		VBArrayListAddBack(_list, _data);
	}
	_list->len++;
}

void* VBArrayListRemoveNode(VBArrayList* _list, VBArrayListNode* _node) {
    VBArrayListNode* _prev = _node->prev;
    VBArrayListNode* _next = _node->next;
    if(_prev)
        _prev->next = _next;
    else
        _list->s_node = _next;
    
    if(_next)
        _next->prev = _prev;
    else
        _list->e_node = _prev;
    
    void* _node_data = _node->data;
    
    VBSystemFree(_node);
    _list->len--;
    
    return _node_data;
}

void* VBArrayListRemove(VBArrayList* _list, void* _data) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListRemove() - VBNull인 List요소에 데이터를 추가할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListRemove() - VBNull인 Data는 List에 추가할 수 없습니다.");
#endif
    
	VBArrayListNode* _node = _list->s_node;
	while(_node) {
		if(_node->data == _data) {
			return VBArrayListRemoveNode(_list, _node);
		}
		_node = _node->next;
	}
	return VBNull;
}

void* VBArrayListRemoveBack(VBArrayList* _list) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListRemoveBack() - VBNull인 List요소의 Data를 삭제할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	if(_list->e_node) {
		void* _data = _list->e_node->data;
		VBArrayListNode* _prev = _list->e_node->prev;
		
		VBSystemFree(_list->e_node);
		
		_list->e_node = _prev;
        if(_list->e_node)
            _list->e_node->next = VBNull;
        _list->len--;
        if(_list->len == 0) {
            _list->s_node = VBNull;
        }
		return _data;
	}
	return VBNull;
}

void* VBArrayListRemoveFront(VBArrayList* _list) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListRemoveFront() - VBNull인 List요소의 Data를 삭제할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	if(_list->s_node) {
		void* _data = _list->s_node->data;
		VBArrayListNode* _next = _list->s_node->next;
		
		VBSystemFree(_list->s_node);
		
		_list->s_node = _next;
        if(_list->s_node)
            _list->s_node->prev = VBNull;
        _list->len--;
		return _data;
	}
	return VBNull;
}

void* VBArrayListRemoveAt(VBArrayList* _list, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListRemoveAt() - VBNull인 List요소의 Data를 삭제할 수 없습니다. VBArrayListAlloc()지 않지 않았을 수 있습니다.");
#endif
    
	if(_at == 0) {
		return VBArrayListRemoveFront(_list);
	} else if(_list->len > 0) {
		VBArrayListNode* _node = VBArrayListGetNodeAt(_list, _at);
		if(_at < _list->len - 1) {
			_node->prev = _node->next;
		} else {
			_node->prev->next = VBNull;
			_list->e_node = _node->prev;
		}
		
		void* _data = _node->data;
		VBSystemFree(_node);
		_list->len--;
		return _data;
	} else {
		return VBNull;
	}
}

void* VBArrayListDataAtIndex(VBArrayList* _list, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListDataAtIndex() - VBNull인 List요소의 Data를 가져올 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	VBArrayListNode* _node = VBArrayListGetNodeAt(_list, _at);
	if(_node)
		return _node->data;
	return VBNull;
}

VBLongLong VBArrayListIndexAtData(VBArrayList* _list, void* _data) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListIndexAtData() - VBNull인 List요소의 Index를 가져올 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListIndexAtData() - VBNull인 Data요소의 사용할 수 없습니다.");
#endif
    
	VBArrayListNode* _node = _list->s_node;
	VBLongLong _result = 0;
	while(_node) {
		if(_node->data == _data) {
			return _result;
		}
		_node = _node->next;
		_result++;
	}
	return -1;
}

void VBArrayListReplaceAt(VBArrayList* _list, void* _data, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListReplaceAt() - VBNull인 List요소의 Data를 교환할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
    if(_data == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListReplaceAt() - VBNull인 Data요소의 사용할 수 없습니다.");
#endif
    
	VBArrayListNode* _node = VBArrayListGetNodeAt(_list, _at);
	if(_node)
		_node->data = _data;
}

void VBArrayListSwapAt(VBArrayList* _list, VBULong _at_1, VBULong _at_2) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapAt() - VBNull인 List요소의 Data를 Swap할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	if(_at_1 != _at_2) {
		VBULong _len = VBArrayListGetLength(_list);
		if(_at_1 < _len && _at_2 < _len) {
			VBArrayListNode* _node_1;
			VBArrayListNode* _node_2;
			VBULong _max = _at_1 > _at_2 ? _at_1 : _at_2;
			VBULong _i;
			VBArrayListNode* _node = _list->s_node;
			for(_i = 0; _i < _max; _i++) {
				if(_i == _at_1) {
					_node_1 = _node;
				} else if(_i == _at_2) {
					_node_2 = _node;
				}
				_node = _node->next;
			}
			VBArrayListSwapNode(_list, _node_1, _node_2);
		}
	}
}

void VBArrayListSwapData(VBArrayList* _list, void* _data_1, void* _data_2) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapData() - VBNull인 List요소의 Data를 교환할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
    if(_data_1 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapData() - VBNull인 첫 번째 Data요소를 사용할 수 없습니다.");
    if(_data_2 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapData() - VBNull인 두 번째 Data요소를 사용할 수 없습니다.");
#endif
    
	if(_data_1 != _data_2) {
		VBULong _len = VBArrayListGetLength(_list);
		if(_len) {
			VBArrayListNode* _node_1;
			VBArrayListNode* _node_2;
			VBULong _i;
			VBArrayListNode* _node = _list->s_node;
			for(_i = 0; _i < _len; _i++) {
				if(_node->data == _data_1) {
					_node_1 = _node;
				} else if(_node->data == _data_2) {
					_node_2 = _node;
				}
				_node = _node->next;
			}
			VBArrayListSwapNode(_list, _node_1, _node_2);
		}
	}
}

void VBArrayListSwapNode(VBArrayList* _list, VBArrayListNode* _node_1, VBArrayListNode* _node_2) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapNode() - VBNull인 List요소의 Data를 교환할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
    if(_node_1 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapNode() - VBNull인 첫 번째 Node를 사용할 수 없습니다.");
    if(_node_2 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListSwapNode() - VBNull인 두 번째 Node를 사용할 수 없습니다.");
#endif
    
	if(_node_1 && _node_2) {
		void* _tmp_data = _node_1->data;
		_node_1->data = _node_2->data;
		_node_2->data = _tmp_data;
	}
}

VBULong VBArrayListGetLength(VBArrayList *_list) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListGetLength() - VBNull인 List요소의 길이를 구할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	return _list->len;
}

VBArrayListNode* VBArrayListGetNodeAt(VBArrayList* _list, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListGetNodeAt() - VBNull인 List요소의 Node를 가져올 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
#endif
    
	VBULong _i;
	VBArrayListNode* _node = _list->s_node;
	for(_i = 0 ; _i < _at ; _i++) {
		_node = _node->next;
		if(!_node)
			return VBNull;
	}
	return _node;
}

VBArrayListNode* VBArrayListGetFirstNode(VBArrayList* _list) {
    return _list->s_node;
}

VBArrayListNode* VBArrayListGetEndNode(VBArrayList* _list) {
    return _list->e_node;
}

VBArrayListNode* VBArrayListNodeGetNextNode(VBArrayListNode* _node) {
#ifdef _VB_DEBUG_
    if(_node == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListNodeGetNextNode() - VBNull인 Node요소의 다음 Node를 가져올 수 없습니다.");
#endif
    
	return _node->next;
}

VBArrayListNode* VBArrayListNodeGetPrevNode(VBArrayListNode* _node) {
#ifdef _VB_DEBUG_
    if(_node == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListNodeGetPrevNode() - VBNull인 Node요소의 이전 Node를 가져올 수 없습니다.");
#endif
    
	return _node->prev;
}

void* VBArrayListNodeGetData(VBArrayListNode* _node) {
#ifdef _VB_DEBUG_
    if(_node == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListNodeGetData() - VBNull인 Node요소의 Data를 가져올 수 없습니다.");
#endif
    
	return _node->data;
}

void q_sort(VBArrayList* _list, VBArrayListNode* left, VBArrayListNode* right, int li, int ri, VBArrayListSortFunc _func) {
	VBArrayListNode* pivot;
	VBArrayListNode* l_hold = left;
	VBArrayListNode* r_hold = right;
	int lih = li;
	int rih = ri;
	pivot = left;
	while (li < ri)
	{
		while(_func(right->data, pivot->data) && (li < ri)) {
			right = right->prev;
			ri--;
		}
		if (li != ri)
		{
			left->data = right->data;
			
			left = left->next;
			li++;
		}
		while (_func(pivot->data, left->data) && (li < ri)) {
			left = left->next;
			li++;
		}
		if (li != ri)
		{
			right->data = left->data;
			right = right->prev;
			ri--;
		}
	}
	left->data = pivot->data;
	pivot = left;
	
	left = l_hold;
	right = r_hold;
	
	if (lih < li && pivot->prev != NULL)
		q_sort(_list, left, pivot->prev, lih, li - 1, _func);
	if (rih > li && pivot->next != NULL)
		q_sort(_list, pivot->next, right, li + 1, rih, _func);
}

void quickSort(VBArrayList* _list, VBArrayListSortFunc _func) {
	q_sort(_list, _list->s_node, _list->e_node, VBArrayListIndexAtData(_list, _list->s_node->data), VBArrayListIndexAtData(_list, _list->e_node->data),  _func);
}



void VBArrayListQuickSort(VBArrayList* _list, VBArrayListSortFunc _func) {
#ifdef _VB_DEBUG_
    if(_list == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListQuickSort() - VBNull인 List요소의 Data를 정렬할 수 없습니다. VBArrayListAlloc()하지 않지 않았을 수 있습니다.");
    if(_func == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBArrayListQuickSort() - VBNull인 SortFunction을 사용할 수 없습니다.");
#endif
    
	quickSort(_list, _func);
}

