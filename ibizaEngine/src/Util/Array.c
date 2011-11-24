#include "Array.h"

#include <stdlib.h>
#include <string.h>

Array* ArrayInit(void) {
	Array* array = calloc(1, sizeof(Array));
	array->data = NULL;
	array->length = 0;
	return array;
}

void ArrayFree(Array** array) {
	if(array[0]) {
		if(array[0]->data) {
			free(array[0]->data);
			array[0]->data = NULL;
		}
		array[0]->length = 0;
		free(array[0]);
		array[0] = NULL;
	}
}

void ArrayPushObject(Array* array, void* object) {
	ArrayPushObjectAtIndex(array, object, array->length);
}

void ArrayPushObjectAtIndex(Array* array, void* object, unsigned short index) {
	signed long i;
	array->length++;
	if(index > array->length)
		index = array->length - 1;
	array->data = (void**)realloc(array->data, sizeof(void*) * array->length);
	for(i = array->length - 1; i >= 0; i--) {
		if(i > index)
			array->data[i] = array->data[i - 1];
	}
	array->data[index] = object;
}

void* ArrayPopObject(Array* array, void* object) {
	for(int i = 0; i < array->length; i++) {
		if(object == ArrayObjectAtIndex(array, i)) {
			return ArrayPopObjectAtIndex(array, i);
		}
	}
	return NULL;
}

void* ArrayPopObjectAtIndex(Array* array, unsigned short index) {
	void* returnData = ArrayObjectAtIndex(array, index);
	signed long i;
	if(index > array->length)
		index = array->length - 1;
	for(i = index; i < array->length - 1; i++) {
		array->data[i] = array->data[i + 1];
	}
	array->length--;
	if(array->length < 1) {
		if(array->data) {
			free(array->data);
			array->data = NULL;
		}
	} else {
		array->data = (void**)realloc(array->data, sizeof(void*) * array->length);
	}
	return returnData;
}

void* ArrayObjectAtIndex(Array* array, unsigned short index) {
	if(array->data) {
		if(index < array->length) {
			return array->data[index];
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

signed long ArrayIndexAtObject(Array* array, void* object) {
	unsigned short i;
	for(i = 0; i < array->length; i++) {
		if(array->data[i] == object)
			return i;
	}
	return -1;
}

unsigned short ArrayLength(Array* array) {
	return array->length;
}

void ArraySort(Array* array, ArraySortFunc func) {
	qsort(array->data, array->length, sizeof(void*), func);
}
