#include "Button.h"
#include <stdlib.h>

void _ButtonTouchEvent(void* userReference, ModelEventTouchArgument argument) {
	Button* button = (Button*)userReference;
	if((button->touchID == NULL) && (argument.touchType == TouchTypeBegan) && argument.isHit) {
		button->touchID = argument.touchID;
	}
	if(button->touchID == argument.touchID) {
		TouchType type = argument.touchType;
		switch(type) {
			case TouchTypeBegan:
				type = ButtonEventTypeClickStart;
				break;
			case TouchTypeMove:
				if(argument.isHit)
					type = ButtonEventTypeFocusOn;
				else
					type = ButtonEventTypeFocusOff;
				break;
			default:
				if(argument.isHit)
					type = ButtonEventTypeClick;
				else
					type = ButtonEventTypeClickOff;
				break;
		}
		button->event.event(button->event.userReference, type);
		if(argument.touchType == TouchTypeEnd || argument.touchType == TouchTypeCancel)
			button->touchID = NULL;
	}
}

ButtonEvent ButtonEventInit(void* userReference, void (*event)(void* userReference, ButtonEventType eventType)) {
	ButtonEvent buttonEvent;
	buttonEvent.userReference = userReference;
	buttonEvent.event = event;
	return buttonEvent;
}

bool ButtonInitVertex(Button* button, Vector3D* vtx, int vertexLength, unsigned char polyLen) {
	button->model = malloc(sizeof(Model));
	ModelInitDefault(button->model);
	
	button->touchID = NULL;
	
	button->hitVertexPolygonLength = polyLen;
	button->hitVertex = vtx;
	
	ModelSetVertex(button->model, button->hitVertex, vertexLength);
	button->model->vertex = NULL;
	return true;
}

bool ButtonInit2D(Button* button, float width, float height) {
	button->model = malloc(sizeof(Model));
	ModelInitDefault(button->model);
	
	button->touchID = NULL;
	
	button->hitVertexPolygonLength = 2;
	button->hitVertex = malloc(sizeof(Vector3D) * 4);
	button->hitVertex[0] = Vector3DInit(0.0,	0.0,	0.0);
	button->hitVertex[1] = Vector3DInit(width,	0.0,	0.0);
	button->hitVertex[2] = Vector3DInit(0.0,	height,	0.0);
	button->hitVertex[3] = Vector3DInit(width,	height,	0.0);
	
	ModelSetVertex(button->model, button->hitVertex, 4);
	button->model->vertex = NULL;
	//ModelInitWithVertex(button->model, 4, button->hitVertex, NULL, NULL, 0, NULL, 0);
	
	return true;
}

bool ButtonInit3D(Button* button, float width, float height, float depth) {
	button->model = malloc(sizeof(Button));
	ModelInitDefault(button->model);
	
	button->hitVertexPolygonLength = 12;
	button->hitVertex = malloc(sizeof(Vector3D) * 14);
	
	//front
	button->hitVertex[0] =	Vector3DInit(0.0,	0.0,	0.0);
	button->hitVertex[1] =	Vector3DInit(width,	0.0,	0.0);
	button->hitVertex[2] =	Vector3DInit(0.0,	height,	0.0);
	button->hitVertex[3] =	Vector3DInit(width,	height,	0.0);
	
	//bottom
	button->hitVertex[4] =	Vector3DInit(0.0,	height,	depth);
	button->hitVertex[5] =	Vector3DInit(width,	height,	depth);
	
	//right
	button->hitVertex[6] =	Vector3DInit(width,	0.0,	0.0);
	button->hitVertex[7] =	Vector3DInit(width,	0.0,	depth);
	
	//back
	button->hitVertex[8] =	Vector3DInit(0.0,	height,	depth);
	button->hitVertex[9] =	Vector3DInit(0.0,	0.0,	depth);
	
	//left
	button->hitVertex[10] =	Vector3DInit(0.0,	height,	0.0);
	button->hitVertex[11] =	Vector3DInit(0.0,	0.0,	0.0);
	
	//top
	button->hitVertex[12] =	Vector3DInit(0.0,	height,	0.0);
	button->hitVertex[13] =	Vector3DInit(0.0,	0.0,	0.0);
	
	ModelSetVertex(button->model, button->hitVertex, 14);
	button->model->vertex = NULL;
	
	return true;
}

bool ButtonFree(Button* button) {
	free(button->hitVertex);
	
	ModelFree(button->model);
	free(button->model);
	
	return true;
}

Model* ButtonGetModel(Button* button) {
	return button->model;
}

bool ButtonAddEvent(Button* button, ButtonEvent event) {
	button->event = event;
	button->touchID = NULL;
	
	ModelAddEventTouch(button->model, ModelEventTouchTinyInit(button, _ButtonTouchEvent), button->hitVertexPolygonLength, button->hitVertex, false, false, false, false);
	return true;
}

bool ButtonRemoveEvent(Button* button) {
	button->event.event = NULL;
	button->event.userReference = NULL;
	button->touchID = NULL;
	
	ModelRemoveEventTouch(button->model);
	return true;
}