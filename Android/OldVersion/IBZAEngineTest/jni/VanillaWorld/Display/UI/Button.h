#ifndef __BUTTON_H__
#define __BUTTON_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "../Object/Model.h"
#include "../../Util/Tween.h"
	
	enum {
		ButtonEventTypeClickStart = 0x00,
		ButtonEventTypeFocusOn =	0x01,
		ButtonEventTypeFocusOff =	0x02,
		ButtonEventTypeClick =		0x03,
		ButtonEventTypeClickOff =	0x04
	};
	typedef unsigned char ButtonEventType;
	
	typedef struct Button Button;
	typedef struct ButtonEvent ButtonEvent;
	struct ButtonEvent {
		void* userReference;
		void (*event)(void* userReference, ButtonEventType eventType);
	};
	
	struct Button {
		Model* model;
		
		void* touchID;
		
		unsigned char hitVertexPolygonLength;
		Vector3D* hitVertex;
		
		ButtonEvent event;
	};
	
	ButtonEvent ButtonEventInit(void* userReference, void (*event)(void* userReference, ButtonEventType eventType));
	
	bool ButtonInitVertex(Button* button, Vector3D* vtx, int vertexLength, unsigned char polyLen);
	bool ButtonInit2D(Button* button, float width, float height);
	bool ButtonInit3D(Button* button, float width, float height, float depth);
	bool ButtonFree(Button* button);
	
	Model* ButtonGetModel(Button* button);
	
	bool ButtonAddEvent(Button* button, ButtonEvent event);
	bool ButtonRemoveEvent(Button* button);
	
#ifdef __cplusplus
}
#endif

#endif