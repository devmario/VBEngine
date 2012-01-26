/**
 @file Core/VBArrayVector.h
 @brief VBEngine의 VBArrayVector 구조체타입과 여러 함수들.
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

#ifndef __VBArrayVector_H__
#define __VBArrayVector_H__

#include "VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief 정렬 관련 함수 타입.
	 */
	typedef int (*VBArrayVectorSortFunc)(const void* _a, const void* _b);
	
	/**
	 @brief VBArrayVector 관련 구조체 타입.
	 
	 VBArrayVector 구조체는 VBArrayVector의 데이터와 벡터의 길이 정보를 나타냅니다.\n
	 여기서 len은 VBArrayVector의 길이 그리고 data는 VBArrayVector에서 사용될 데이터를 나타냅니다. 
	 */
	typedef struct VBArrayVector VBArrayVector;
	
	/**
	 @brief VBArrayVector 관련 구조체.
	 
	 VBArrayVector 구조체는 VBArrayVector의 데이터와 벡터의 길이 정보를 나타냅니다.\n
	 여기서 len은 VBArrayVector의 길이 그리고 data는 VBArrayVector에서 사용될 데이터를 나타냅니다. 
	 */
	struct VBArrayVector {
		VBUShort len;
        VBUShort stepSize;
		void** data;
	};
	
	/**
	 @brief VBArrayVector의 메모리를 할당합니다.
	 @return _vec 메모리가 할당된 VBArrayVector를 반환합니다. 
	 */
	VBArrayVector* VBArrayVectorAlloc(void);

	/**
	 @brief VBArrayVector를 초기화합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
     @return 초기화된 VBArrayVector.
	 */
	VBArrayVector* VBArrayVectorInit(VBArrayVector* _vec);

    /**
	 @brief VBArrayVector를 미리 할당할 메모리의 크기로 초기화합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
     @param _ss 미리 할당할 메모리의 크기
     @return 초기화된 VBArrayVector.
	 */
    VBArrayVector* VBArrayVectorInitWithStepSize(VBArrayVector* _vec, VBLong _ss);
	
	/**
	 @brief VBArrayVector의 메모리를 해제합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
	 */
	void VBArrayVectorFree(VBArrayVector** _vec);
	
    //두번째 인자로온 포인터가 배열안에 몇개가 있나 갯수를 리턴
    int VBArrayVectorGetDataAmount(VBArrayVector* _vec, void* _data);
    
	/**
	 @brief VBArrayVector에서 지정된 위치의 데이터를 반환합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _at 반환할 데이터의 위치.
	 @return 데이터를 반환합니다.
	 */
	void* VBArrayVectorGetDataAt(VBArrayVector* _vec, VBULong _at);
	
	/**
	 @brief VBArrayVector의 뒤로부터 데이터를 삽입합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _data VBArrayVector에 삽입하려는 데이터.
	 */
	void VBArrayVectorAddBack(VBArrayVector* _vec, void* _data);
	
	/**
	 @brief VBArrayVector의 앞로부터 데이터를 삽입합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _data VBArrayVector에 삽입하려는 데이터.
	 */
	void VBArrayVectorAddFront(VBArrayVector* _vec, void* _data);
	
	/**
	 @brief VBArrayVector에서 지정된 위치에 데이터를 삽입합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _data VBArrayVector에 삽입하려는 데이터.
	 */
	void VBArrayVectorAddAt(VBArrayVector* _vec, void* _data, VBULong _at);
	
	/**
	 @brief VBArrayVector의 끝에 위치해 있는 데이터를 제거합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
     @return 제거된 node의 데이터
	 */
	void* VBArrayVectorRemoveBack(VBArrayVector* _vec);
	
	/**
	 @brief VBArrayVector의 시작에 위치해 있는 데이터를 제거합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
     @return 제거된 node의 데이터
	 */
	void* VBArrayVectorRemoveFront(VBArrayVector* _vec);
    
	/**
	 @brief VBArrayVector에서 데이터를 제거합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _at VBArrayVector에서 제거하려는 데이터.
     @return 제거된 node의 데이터
	 */
	void* VBArrayVectorRemove(VBArrayVector* _vec, void* _data);
	
	
    /**
	 @brief VBArrayVector에서 지정된 위치의 데이터를 제거합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _at VBArrayVector에서 제거하려는 데이터의 위치.
     @return 제거된 node의 데이터
	 */
	void* VBArrayVectorRemoveAt(VBArrayVector* _vec, VBULong _at);
	
	/**
	 @brief VBArrayVector에서 지정된 위치의 데이터를 구합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
     @param _at 가져올 데이터의 위치
	 @return 지정된 위치의 데이터
	 */
	void* VBArrayVectorDataAtIndex(VBArrayVector* _vec, VBULong _at);
	
	/**
	 @brief VBArrayVector에서 지정된 데이터의 위치를 반환합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
     @param _data 가져올 위치의 데이터
	 @return 지정된 데이터의 위치를 반환합니다. 
	 */
	VBLong VBArrayVectorIndexAtData(VBArrayVector* _vec, void* _data);
	
	/**
	 @brief VBArrayVector에서 특정 데이터를 다른 데이터로 교환합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _data 원 데이터와 교환하려는 데이터.
	 @param _at 원 데이터의 위치.
	 */
	void VBArrayVectorReplaceAt(VBArrayVector* _vec, void* _data, VBULong _at);
	
	/**
	 @brief VBArrayVector에서 2개의 데이터의 값의 위치를 확인한 후 두 값의 위치를 교환합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _at1 교환할 첫 번쨰 위치.
	 @param _at2 교환할 두 번쨰 위치.
	 */
	void VBArrayVectorSwapAt(VBArrayVector* _vec, VBULong _at1, VBULong _at2);
	
	/**
	 @brief VBArrayVector에서 2개의 데이터의 값을 확인한 후 두 데이터 값을 교환합니다.
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _data1 교환할 첫 번째 데이터.
	 @param _data2 교환할 두 번쨰 데이터.
	 */
	void VBArrayVectorSwapData(VBArrayVector* _vec, void* _data1, void* _data2);
	
	/**
	 @brief VBArrayVector의 길이를 구합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @return VBArrayVector의 길이
	 */
	VBULong VBArrayVectorGetLength(VBArrayVector* _vec);
	
	/**
	 @brief VBArrayVector의 데이터를 Quicksort를 이용해 정렬합니다. 
	 @param _vec 메모리가 할당된 VBArrayVector.
	 @param _func 정렬을 수행할 함수.
	 */
	void VBArrayVectorQuickSort(VBArrayVector* _vec, VBArrayVectorSortFunc _func);
	
	/**
	 @brief VBArrayVector 데이터의 순서를 뒤집습니다. 
     
     <b>Example</b>
	 <table bgcolor="#eeeeee" width="1225">
     <tr>
     <td>
     <i>VBArrayVector를 생성한 후 일정한 데이터를 입력한 뒤에 VBArrayVectorReverse함수를 호출합니다.</i> \n\n
     VBArrayVector* _vec = VBArrayVectorInit(VBArrayVectorAlloc());  \n
     
     int a = 10; \n
     int b = 20; \n
     int c = 30; \n
     VBArrayVectorAddBack(_vec, &a); \n
     VBArrayVectorAddBack(_vec, &b); \n
     VBArrayVectorAddBack(_vec, &c); \n
 
     VBArrayVectorReverse(_vec); \n
     
     for (i = 0; i < _len; i++) {  \n
     &nbsp;&nbsp; int* aptr = (int*)VBArrayVectorDataAtIndex(_vec, i); \n
     &nbsp;&nbsp; VBDebugPrint(VBEngineGetDefaultDebuger(), index %i address %i value %i", i, aptr, *aptr); \n
     } \n
     VBArrayVectorFree(&_vec); 

     참고 사항 \n
     <a href="file:///Users/welivehere/Desktop/VBEngine%20Doc/html/_v_b_array_vector_8h.html#a3fb260681759b2621ad01dd92bf32e33">VBArrayVectorAddBack</a> \n
     <a href="file:///Users/welivehere/Desktop/VBEngine%20Doc/html/_v_b_array_vector_8h.html#a1722f9089f0c1d7476ed602e434474af">VBArrayVectorDataAtIndex</a>
     </td>
     </tr>
	 </table>
     
	 @param vec VBArrayVector.
	 */
	void VBArrayVectorReverse(VBArrayVector* _vec);
        
#ifdef __cplusplus
}
#endif

#endif
