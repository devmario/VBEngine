#include "Popup.h"
#include <stdlib.h>

bool PopupInit(Popup* popup, Object2DSeries* skin, Model* content, Model* parent, 
			   ModelManager* modelManager, TweenManager* tweenManager,
			   unsigned short transitionFrame, unsigned short delayFrame, TweenTrasitionType transition, TweenEquationType equation) {
	popup->bg = malloc(sizeof(Model));
	popup->L = malloc(sizeof(Model));
	popup->T = malloc(sizeof(Model));
	popup->R = malloc(sizeof(Model));
	popup->B = malloc(sizeof(Model));
	
	popup->model = malloc(sizeof(Model));
	
	popup->tween = malloc(sizeof(Tween));
	TweenInit(popup->tween, transitionFrame, delayFrame, transition, equation);
	
	popup->parent = parent;
	popup->modelManager = modelManager;
	popup->tweenManager = tweenManager;
	
	return true;
}

bool PopupFree(Popup* popup) {
	free(popup->bg);
	free(popup->L);
	free(popup->T);
	free(popup->R);
	free(popup->B);
	free(popup->model);
	TweenFree(popup->tween);
	free(popup->tween);
	return true;
}

bool PopupShow(Popup* popup) {
	return true;
}

bool PopupHide(Popup* popup) {
	return true;
}