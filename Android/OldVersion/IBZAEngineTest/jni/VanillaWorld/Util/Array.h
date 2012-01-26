#ifndef __ARRAY_H__
#define __ARRAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
	
	//솔트하는 콜백
	//a가 b보다 크면 0, a가 b보다 작거나 같으면 0보다 큰 수를 리턴하여야 한다.
	typedef int (*ArraySortFunc)(const void* a, const void* b);
	
	//배열
	typedef struct Array Array;
	struct Array {
		void** data;
		unsigned short length;
	};
	
	//생성,해제
	Array* ArrayInit(void);
	void ArrayFree(Array** array);
	
	//요소추가
	void ArrayPushObject(Array* array, void* object);
	void ArrayPushObjectAtIndex(Array* array, void* object, unsigned short index);
	
	//요소삭제(삭제된 요소 리턴)
	void* ArrayPopObject(Array* array, void* object);
	void* ArrayPopObjectAtIndex(Array* array, unsigned short index);
	
	//요소가져오기
	void* ArrayObjectAtIndex(Array* array, unsigned short index);
	signed long ArrayIndexAtObject(Array* array, void* object);
	
	//배열길이
	unsigned short ArrayLength(Array* array);

	//배열정렬
	void ArraySort(Array* array, ArraySortFunc func);


#ifdef __cplusplus
}
#endif

#endif
