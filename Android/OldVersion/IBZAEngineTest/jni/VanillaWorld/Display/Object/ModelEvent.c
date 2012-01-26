#include "Model.h"

#include <stdlib.h>

#include <string.h>

#pragma mark -
#pragma mark Model 이벤트

ModelEventRender ModelEventRenderInit(void* userReference, ModelEventRenderArgument argument, void (*event)(void* userReference, ModelEventRenderArgument argument)) {
	ModelEventRender returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.argument = argument;
	returnEvent.event = event;
	return returnEvent;
}

ModelEventTouch ModelEventTouchTinyInit(void* userReference, void (*event)(void* userReference, ModelEventTouchArgument argument)) {
	ModelEventTouch returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.event = event;
	return returnEvent;
}

ModelEventTouch ModelEventTouchInit(void* userReference, ModelEventTouchArgument argument, void (*event)(void* userReference, ModelEventTouchArgument argument)) {
	ModelEventTouch returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.argument = argument;
	returnEvent.event = event;
	return returnEvent;
}

bool ModelAddEventTouch(Model* model, ModelEventTouch event, 
						unsigned long hitTrianglePolygonLength, Vector3D* hitVertex,
						bool isNeedTouchVector, bool isAlsoHitTouchVector, 
						bool isNeedTouchVectorGlobal, bool isAlsoHitTouchVectorGlobal) {
	model->touchEvent = event;
	model->hitTrianglePolygonLength = hitTrianglePolygonLength;
	model->hitVertex = hitVertex;
	model->isNeedTouchVector = isNeedTouchVector;
	if(isNeedTouchVector) {
		if(!model->touchVector) {
			model->touchVector = malloc(sizeof(Vector3D));
		}
	} else {
		if(model->touchVector) {
			free(model->touchVector);
			model->touchVector = NULL;
		}
	}
	model->isAlsoHitTouchVector = isAlsoHitTouchVector;
	model->isNeedTouchVectorGlobal = isNeedTouchVectorGlobal;
	if(isNeedTouchVectorGlobal) {
		if(!model->touchVectorGlobal) {
			model->touchVectorGlobal = malloc(sizeof(Vector3D));
		}
	} else {
		if(model->touchVectorGlobal) {
			free(model->touchVectorGlobal);
			model->touchVectorGlobal = NULL;
		}
	}
	model->isAlsoHitTouchVectorGlobal = isAlsoHitTouchVectorGlobal;
	return true;
}

bool ModelAddEventTouchAlsoIsHit(Model* model, ModelEventTouch event, unsigned long hitTrianglePolygonLength, Vector3D* hitVertex) {
	return ModelAddEventTouch(model, event, hitTrianglePolygonLength, hitVertex, 
							  false, false, false, false);
}

bool ModelAddEventTouchNeedVector(Model* model, ModelEventTouch event, unsigned long hitTrianglePolygonLength, Vector3D* hitVertex) {
	return ModelAddEventTouch(model, event, hitTrianglePolygonLength, hitVertex, 
							  true, false, false, false);
}

bool ModelAddEventTouchNeedGlobalVector(Model* model, ModelEventTouch event, unsigned long hitTrianglePolygonLength, Vector3D* hitVertex) {
	return ModelAddEventTouch(model, event, hitTrianglePolygonLength, hitVertex, 
							  false, false, true, false);
}

bool ModelRemoveEventTouch(Model* model) {
	model->touchEvent.event = NULL;
	model->touchEvent.userReference = NULL;
	memset(&model->touchEvent.argument, 0, sizeof(ModelEventTouchArgument));
	model->hitTrianglePolygonLength = 0;
	model->hitVertex = NULL;
	model->isNeedTouchVector = false;
	if(model->touchVector) {
		free(model->touchVector);
		model->touchVector = NULL;
	}
	model->isAlsoHitTouchVector = false;
	model->isNeedTouchVectorGlobal = false;
	if(model->touchVectorGlobal) {
		free(model->touchVectorGlobal);
		model->touchVectorGlobal = NULL;
	}
	model->isAlsoHitTouchVectorGlobal = false;
	return true;
}

bool ModelAddEventRender(Model* model, ModelEventRender event) {
	model->renderEvent = event;
	return true;
}

bool ModelRemoveEventRender(Model* model) {
	model->renderEvent.event = NULL;
	model->renderEvent.userReference = NULL;
	memset(&model->renderEvent.argument, 0, sizeof(ModelEventRenderArgument));
	return true;
}

