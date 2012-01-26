#include "CoverFlow.h"
#include <stdlib.h>
#include <math.h>

CoverFlowEvent CoverFlowEventInit(void* userReference,
								  void (*selectEvent)(Cover* cover, void* data),
								  void (*addEvent)(Cover* cover, void* data),
								  void (*removeEvent)(Cover* cover, void* data)) {
	CoverFlowEvent event;
	event.userReference = userReference;
	event.selectEvent = selectEvent;
	event.addEvent = addEvent;
	event.removeEvent = removeEvent;
	return event;
}

void _coverFlowRender(void* userReference, ModelEventRenderArgument argument) {
}

void _coverFlowTouch(void* userReference, ModelEventTouchArgument argument) {
	CoverFlow* coverFlow = (CoverFlow*)userReference;
	if(coverFlow->touchID == NULL && (argument.isHit == true && argument.touchType == TouchTypeBegan)) {
		coverFlow->touchID = argument.touchID;
		coverFlow->preTouchX = coverFlow->touchX = argument.hitVector->x;
		coverFlow->stepTouchX = 0.0;
	}
	
	if(coverFlow->touchID == argument.touchID) {
		coverFlow->touchX = argument.hitVector->x;
		coverFlow->stepTouchX += coverFlow->touchX - coverFlow->preTouchX;
		coverFlow->preTouchX = coverFlow->touchX;
		if(argument.touchType == TouchTypeEnd || argument.touchType == TouchTypeCancel) {
			coverFlow->touchX = argument.hitVector->x;
			coverFlow->stepTouchX += coverFlow->touchX - coverFlow->preTouchX;
			coverFlow->preTouchX = coverFlow->touchX;
			coverFlow->touchID = NULL;
		}
	}
}

#define MULTXSIZE 60.0
#define FORCEDECREASE 0.3
#define REWINDSPEED 0.2
#define ANGLESPEED 0.1
#define ZSPEED 0.1
#define XSPEED 0.1

bool CoverFlowInit(CoverFlow* coverFlow, Array* data, CoverFlowEvent event, 
				   unsigned short width, unsigned short height, unsigned char visibleCoverLength) {
	ModelInitDefault(&coverFlow->model);
	
	coverFlow->coverFlowHitVertex[2].x = coverFlow->coverFlowHitVertex[0].x = -width * 0.5;
	coverFlow->coverFlowHitVertex[1].x = coverFlow->coverFlowHitVertex[3].x = width * 0.5;
	coverFlow->coverFlowHitVertex[0].y = coverFlow->coverFlowHitVertex[1].y = -height * 0.5;
	coverFlow->coverFlowHitVertex[2].y = coverFlow->coverFlowHitVertex[3].y = height * 0.5;
	coverFlow->coverFlowHitVertex[0].z = coverFlow->coverFlowHitVertex[1].z = 
	coverFlow->coverFlowHitVertex[2].z = coverFlow->coverFlowHitVertex[3].z = 0.0;
	
	ModelEventRender renderEvent;
	renderEvent.userReference = coverFlow;
	renderEvent.event = _coverFlowRender;
	ModelAddEventRender(&coverFlow->model, renderEvent);
	
	ModelEventTouch touchEvent;
	touchEvent.userReference = coverFlow;
	touchEvent.event = _coverFlowTouch;
	ModelAddEventTouch(&coverFlow->model, touchEvent, 2, coverFlow->coverFlowHitVertex, true, true, false, false);
	
	coverFlow->event = event;
	
	coverFlow->data = data;
	
	coverFlow->width = width;
	coverFlow->height = height;
	
	coverFlow->visibleCoverLength = visibleCoverLength;
	
	ArrayInit(&coverFlow->visibleCovers);
	
	int i = 0;
	for(; i < coverFlow->visibleCoverLength * 2 + 1; i++) {
		Cover* cover = malloc(sizeof(Cover));
		cover->data = (void*)ArrayObjectAtIndex(coverFlow->data, i);
		cover->index = i;
		cover->parentCoverFlow = coverFlow;
		cover->selected = false;
		cover->userReference = NULL;
		ModelInitDefault(&cover->bundle);
		ModelAddAt(&coverFlow->model, &cover->bundle, 0);
		ModelInitDefault(&cover->model);
		ModelSetIsLighting(&cover->model, false);
		ArrayPushObject(&coverFlow->visibleCovers, cover);
		ModelAdd(&cover->bundle, &cover->model);
		coverFlow->event.addEvent(cover, coverFlow->event.userReference);
		
		int centerIndex = 0;
		if(cover->index < centerIndex) {
			cover->x = (-120.0 + (30.0 * (cover->index - centerIndex)));
			cover->angle = -M_PI * 0.4;
			cover->z = 170.0;
		} else if(cover->index > centerIndex) {
			cover->x = (120.0 + (30.0 * (cover->index - centerIndex)));
			cover->angle = M_PI * 0.4;
			cover->z = 170.0;
		} else {
			cover->x = 0.0;
			cover->angle = 0.0;
			cover->z = 0.0;
		}
	}
	
	coverFlow->touchID = NULL;
	coverFlow->force = 0.0;
	coverFlow->x = 0.0;
	coverFlow->preTouchX = 0.0;
	coverFlow->touchX = 0.0;
	coverFlow->stepTouchX = 0.0;
	coverFlow->selectedIndex = 0;
	
	return true;
}

bool CoverFlowFree(CoverFlow* coverFlow) {
	int i = 0;
	for(; i < coverFlow->visibleCoverLength; i++) {
		coverFlow->event.removeEvent(ArrayObjectAtIndex(&coverFlow->visibleCovers, i), coverFlow->event.userReference);
	}
	
	while(coverFlow->visibleCovers.length) {
		Cover* cover = ArrayPopObjectAtIndex(&coverFlow->visibleCovers, 0);
		ModelFree(&cover->model);
		free(cover);
	}
	
	ArrayFree(&coverFlow->visibleCovers);
	
	ModelFree(&coverFlow->model);
	
	return true;
}

void CoverFlowUpdate(CoverFlow* coverFlow) {
	if(coverFlow->touchID) {
		coverFlow->x += coverFlow->stepTouchX;
		coverFlow->stepTouchX = 0.0;
	} else {
		coverFlow->force += coverFlow->stepTouchX;
		coverFlow->stepTouchX = 0.0;
		coverFlow->force *= FORCEDECREASE;
		coverFlow->x += coverFlow->force;
		if(coverFlow->x < -((coverFlow->data->length - 1) * MULTXSIZE)) {
			coverFlow->x += ((float)(-(coverFlow->data->length - 1) * MULTXSIZE) - coverFlow->x) * REWINDSPEED;
		} else if(coverFlow->x > 0.0) {
			coverFlow->x += (0.0 - coverFlow->x) * REWINDSPEED;
		}
	}
	
	float ci = -coverFlow->x / MULTXSIZE;
	int centerIndex = roundf(ci);
	bool resort = false;
	if(coverFlow->selectedIndex != centerIndex) {
		coverFlow->selectedIndex = centerIndex;
		resort = true;
	}
	
	int i = 0;
	for(; i < coverFlow->visibleCovers.length ; i++) {
		Cover* cover = ArrayObjectAtIndex(&coverFlow->visibleCovers, i);
		
		bool newPos = false;
		if(cover->index < centerIndex - coverFlow->visibleCoverLength) {
			coverFlow->event.removeEvent(cover, coverFlow->event.userReference);
			cover->index += coverFlow->visibleCoverLength * 2 + 1;
			cover->data = ArrayObjectAtIndex(coverFlow->data, cover->index);
			coverFlow->event.addEvent(cover, coverFlow->event.userReference);
			newPos = true;
		} else if(cover->index > centerIndex + coverFlow->visibleCoverLength) {
			coverFlow->event.removeEvent(cover, coverFlow->event.userReference);
			cover->index -= coverFlow->visibleCoverLength * 2 + 1;
			cover->data = ArrayObjectAtIndex(coverFlow->data, cover->index);
			coverFlow->event.addEvent(cover, coverFlow->event.userReference);
			newPos = true;
		}
		
		if(newPos) {
			if(cover->index < centerIndex) {
				cover->x = (-120.0 + (30.0 * (cover->index - ci)));
				cover->angle = -M_PI * 0.4;
				cover->z = 200.0;
			} else if(cover->index > centerIndex) {
				cover->x = (120.0 + (30.0 * (cover->index - ci)));
				cover->angle = M_PI * 0.4;
				cover->z = 200.0;
			} else {
				cover->x = (40.0 * (cover->index - ci));
				cover->angle = 0.0;
				cover->z = 0.0;
			}
		} else {
			if(cover->index < centerIndex) {
				cover->x += ((-120.0 + (30.0 * (cover->index - ci))) - cover->x) * XSPEED;
				cover->angle += (-M_PI * 0.4 - cover->angle) * ANGLESPEED;
				cover->z += (200.0 - cover->z) * ZSPEED;
			} else if(cover->index > centerIndex) {
				cover->x += ((120.0 + (30.0 * (cover->index - ci))) - cover->x) * XSPEED;
				cover->angle += (M_PI * 0.4 - cover->angle) * ANGLESPEED;
				cover->z += (200.0 - cover->z) * ZSPEED;
			} else {
				cover->x += ((40.0 * (cover->index - ci)) - cover->x) * XSPEED;
				cover->angle += (0.0 - cover->angle) * ANGLESPEED;
				cover->z += (0.0 - cover->z) * ZSPEED;
			}
		}
		
		*cover->bundle.matrix = Matrix3DLoadIdentity();
		*cover->model.matrix = Matrix3DLoadIdentity();
		
		*cover->bundle.matrix = Matrix3DTranslate(*cover->bundle.matrix, Vector3DInit(cover->x, 0.0, cover->z));
		*cover->model.matrix = Matrix3DRotate(*cover->model.matrix, Vector3DInit(0.0, 1.0, 0.0), cover->angle);
	}
}
