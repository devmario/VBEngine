/**
 @file Core/VBArrayList.h
 @brief VBEngine의 VBArrayList 구조체타입과 여러 함수들.
 @author 
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section Lisence
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBArrayList_H__
#define __VBArrayList_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief 정렬 관련 함수 타입.
	 */
	typedef VBLong (*VBArrayListSortFunc)(const void* _a, const void* _b);
	
	/**
	 @brief Node 관련 VBArrayListNode 구조체타입.
	 
	 VBArrayListNode 구조체는 Node의 위치가 데이터를 나타냅니다. \n
	 여기서 prev는 이전 Node, next는 이후 Node, data는 노드의 데이터를 나타냅니다.
	 */
	typedef struct VBArrayListNode VBArrayListNode;
	
	/**
	 @brief ArrayList 관련 VBArrayList 구조체타입.
	 
	 VBArrayList의 구조체는 VBArrayList안의 Node 정보를 나타냅니다.
	 여기서 s_node는 시작 Node, e_node는 끝 Node 그리고 len은 VBArrayList의 길이를 나타냅니다. 
	 */
	typedef struct VBArrayList VBArrayList;
	
	/**
	 @brief Node 관련 VBArrayList 구조체.
	 
	 VBArrayListNode 구조체는 Node의 위치와 데이터를 나타냅니다. \n
	 여기서 prev는 이전 Node, next는 이후 Node, data는 노드의 데이터를 나타냅니다.
	 */
	struct VBArrayListNode {
		/*!
		 이전 Node의 포인터
		 */
		VBArrayListNode* prev;
		/*!
		 데이터
		 */
		void* data;
		/*!
		 이후 Node의 포인터
		 */
		VBArrayListNode* next;
	};
	
	/**
	 @brief ArrayList 관련 VBArrayList 구조체
	 
	 VBArrayList의 구조체는 VBArrayList안 Node의 정보를 나타냅니다.
	 여기서 s_node는 시작 Node, e_node는 끝 Node 그리고 len은 VBArrayList의 길이를 나타냅니다. 
	 */
	struct VBArrayList {
		/*!
		 VBArrayList의 길이
		 */
		VBShort len;
		/*!
		 시작 Node의 포인터
		 */
		VBArrayListNode* s_node;
		/*!
		 끝 Node의 포인터
		 */
		VBArrayListNode* e_node;
	};
	
	/**
	 @brief VBArrayList의 메모리를 할당합니다.
	 @return _list 메모리가 할당된 VBArrayList를 반환합니다.
	 */
	VBArrayList* VBArrayListAlloc(void);
	
	/**
	 @brief VBArrayList를 초기화합니다.
	 
	 list에 기존에 존재하던 node들은 전부 메모리 해제 시키고 길이를 0으로 초기화합니다. 
	 
	 @param _list 메모리가 할당된 VBArrayList*
     @return 초기화된 VBArrayList* 를 반환합니다.
	 */
	VBArrayList* VBArrayListInit(VBArrayList* _list);
	
	/**
	 @brief VBArrayList의 메모리를 해제합니다.
     
     list에 존재하는 node들과 list를 전부 메모리 해제시키고 _list를 null로 만듭니다.
     
	 @param _list 메모리가 할당된 VBArrayList**
	 */
	void VBArrayListFree(VBArrayList** _list);
	
	/**
	 @brief VBArrayList의 뒤로부터 데이터를 삽입합니다.
	 
	 VBArrayList에 데이터가 존재하는 경우에는 가장 뒤쪽으로부터 데이터가 삽입됩니다.\n
	 VBArrayList에 데이터가 존재하지 않는 경우에는 선행 데이터가 됩니다.
	 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _data VBArrayList에 삽입하려는 데이터.
	 */
	void VBArrayListAddBack(VBArrayList* _list, void* _data);
	
	/**
	 @brief VBArrayList의 앞으로부터 데이터를 삽입합니다. 
	 
	 VBArrayList에 데이터가 존재하는 경우에는 가장 앞으로부터 데이터 삽입되고 시작 노드가 됩니다.\n
	 VBArrayList에 데이터가 존재하지 않는 경우에도 시작 노드가 됩니다.
	 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _data VBArrayList에 삽입하려는 데이터.
	 */
	void VBArrayListAddFront(VBArrayList* _list, void* _data);
	
	/**
	 @brief VBArrayList에서 지정된 위치에 데이터를 삽입합니다. 
	 
	 VBArrayList에 삽입되는 데이터의 지정된 위치가 시작 노드의 위치와 일치할 경우 시작 노드가 됩니다. \n
	 VBArrayList에 삽입되는 데이터의 지정된 위치가 끝 노드의 위치와 일치할 경우 끝 노드가 됩니다. \n
	 위의 두 경우를 제외하면 지정된 위치에 데이터를 삽입합니다. 
	 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _data VBArrayList에 추가하려는 데이터.
	 @param _at VBArrayList에 추가하려는 데이터의 위치.
	 */
	void VBArrayListAddAt(VBArrayList* _list, void* _data, VBULong _at);
	
	/**
	 @brief VBArrayList에서 데이터를 제거합니다.
     
     _list에서 _data와 같은 데이터를 가진 node를 찾아 제거합니다.
     
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _data VBArrayList에서 제거하려는 데이터.
     @return 삭제될 node가 가진 데이터를 리턴합니다.
	 */
	void* VBArrayListRemove(VBArrayList* _list, void* _data);
	
	/**
	 @brief VBArrayList의 끝에 위치해 있는 데이터를 제거합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
     @return 삭제될 node가 가진 데이터를 리턴합니다.
	 */
	void* VBArrayListRemoveBack(VBArrayList* _list);
	
	/**
	 @brief VBArrayList의 시작에 위치해 있는 데이터를 제거합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
     @return 삭제될 node가 가진 데이터를 리턴합니다.
	 */
	void* VBArrayListRemoveFront(VBArrayList* _list);
	
	/**
	 @brief VBArrayList에서 지정된 위치의 데이터를 제거합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _at VBArrayList에서 제거하려는 데이터의 위치.
     @return 삭제될 node가 가진 데이터를 리턴합니다.
	 */
	void* VBArrayListRemoveAt(VBArrayList* _list, VBULong _at);
	
	/**
	 @brief VBArrayList에서 지정된 위치의 데이터를 구합니다.
	 @param _list 메모리가 할당된 VBArrayList*
     @param _at VBArrayList에서 제거하려는 데이터의 위치.
	 @return 지정된 위치의 데이터를 반환합니다. 
	 */
	void* VBArrayListDataAtIndex(VBArrayList* _list, VBULong _at);
	
	/**
	 @brief VBArrayList에서 지정된 데이터의 위치를 구합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
     @param _data 리스트에서 가져오고 싶은 위치의 데이터
	 @return 지정된 데이터의 위치를 반환합니다. 
	 */
	VBLongLong VBArrayListIndexAtData(VBArrayList* _list, void* _data);
	
	/**
	 @brief VBArrayList에서 특정 데이터를 다른 데이터로 교환합니다.
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _data 원 데이터와 교환하려는 데이터.
	 @param _at 원 데이터의 위치.
	 */
	void VBArrayListReplaceAt(VBArrayList* _list, void* _data, VBULong _at);
	
	/**
	 @brief VBArrayList에서 데이터 2개의 위치를 지정해 교환합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _at_1 교환할 데이터의 첫 번쨰 위치.
	 @param _at_2 교환할 데이터의 두 번쨰 위치.
	 */
	void VBArrayListSwapAt(VBArrayList* _list, VBULong _at_1, VBULong _at_2);
	
	/** 
	 @brief VBArrayList에서 2개의 데이터 위치를 교환합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _data_1 교환할 첫 번째 데이터.
	 @param _data_2 교환할 두 번째 데이터.
	 */
	void VBArrayListSwapData(VBArrayList* _list, void* _data_1, void* _data_2);
	
	/**
	 @brief VBArrayList에서 2개의 Node를 교환합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _node_1 교환할 첫 번째 Node.
	 @param _node_2 교환할 두 번째 Node.
	 */
	void VBArrayListSwapNode(VBArrayList* _list, VBArrayListNode* _node_1, VBArrayListNode* _node_2);
	
	/**
	 @brief VBArrayList의 길이를 구합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
	 @return VBArrayList의 길이를 반환합니다. 
	 */
	VBULong VBArrayListGetLength(VBArrayList* _list);
	
	/**
	 @brief VBArrayList의 데이터에서 해당 위치의 Node를 구합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
     @param _at 리스트에서 가져올 node의 위치
	 @return node를 반환합니다.
	 */
	VBArrayListNode* VBArrayListGetNodeAt(VBArrayList* _list, VBULong _at);
    
    VBArrayListNode* VBArrayListGetFirstNode(VBArrayList* _list);
    
    VBArrayListNode* VBArrayListGetEndNode(VBArrayList* _list);
	
	/**
	 @brief VBArrayList의 데이터에서 다음 Node를 구합니다.
	 @param _node VBArrayListNode.
	 @return 다음 Node를 반환합니다.
	 */
	VBArrayListNode* VBArrayListNodeGetNextNode(VBArrayListNode* _node);
	
	/**
	 @brief VBArrayList의 데이터에서 이전 Node를 구합니다.
	 @param _node VBArrayListNode.
	 @return 이전 Node를 반환합니다. 
	 */
	VBArrayListNode* VBArrayListNodeGetPrevNode(VBArrayListNode* _node);
	
	/**
	 @brief VBArrayList데이터안의 Node에 저장된 데이터를 구합니다. 
	 @param _node VBArrayListNode.
	 @return Node에 저장된 데이터를 반환합니다. 
	 */
	void* VBArrayListNodeGetData(VBArrayListNode* _node);
	
	/**
	 @brief VBArrayList의 데이터를 Quicksort를 이용해 정렬합니다. 
	 @param _list 메모리가 할당된 VBArrayList*
	 @param _func 정렬을 수행할 함수.
	*/
	void VBArrayListQuickSort(VBArrayList* _list, VBArrayListSortFunc _func);
	
#ifdef __cplusplus
}
#endif

#endif