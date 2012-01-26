#ifndef __POPUP_H__
#define __POPUP_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
#include "../Object/Model.h"
#include "../../Util/Tween.h"
	
	typedef struct Popup Popup;
	
	struct Popup {
		Model* bg;
		Model* L;
		Model* T;
		Model* R;
		Model* B;
		
		Model* model;
		
		Tween* tween;
		
		Model* parent;
		ModelManager* modelManager;
		TweenManager* tweenManager;
	};
	
	bool PopupInit(Popup* popup, Object2DSeries* skin, Model* content, Model* parent, 
				   ModelManager* modelManager, TweenManager* tweenManager,
				   unsigned short transitionFrame, unsigned short delayFrame, TweenTrasitionType transition, TweenEquationType equation);
	bool PopupFree(Popup* popup);
	
	bool PopupShow(Popup* popup);
	bool PopupHide(Popup* popup);
	
#ifdef __cplusplus
}
#endif

#endif
