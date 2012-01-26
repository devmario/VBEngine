#include "VBArray.h"

void VBArrayListToVector(VBArrayList* _list, VBArrayVector* _vec) {
	VBArrayVectorInit(_vec);
	VBArrayListNode* _node = VBArrayListGetNodeAt(_list, 0);
	while(_node) {
		VBArrayVectorAddBack(_vec, _node->data);
		_node = VBArrayListNodeGetNextNode(_node);
	}
}

void VBArrayVectorToList(VBArrayVector* _vec, VBArrayList* _list) {
	VBArrayListInit(_list);
	VBULong _i;
	for(_i = 0; _i < VBArrayVectorGetLength(_vec); _i++) {
		VBArrayListAddBack(_list, VBArrayVectorDataAtIndex(_vec, _i));
	}
}

