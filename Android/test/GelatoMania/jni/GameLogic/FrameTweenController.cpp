#include "FrameTweenController.h"

FrameTweenController::FrameTweenController(VBModel* _m) {
    model = _m;
    tween = new TweenerWrapper();
    frame = model->cur_frame;
}

FrameTweenController::~FrameTweenController() {
    delete tween;
}

void FrameTweenController::playTo(float end, float duration, float delay, short ptransition, short pequation, void(*callBackFunc)(void* callBackObj), void* callBackObj) {
//    delete tween;
//    tween = new TweenerWrapper();
    tween->begin(&frame, end, duration, delay, ptransition, pequation, callBackFunc, callBackObj);
}

void FrameTweenController::Update(float _delta) {
    tween->update(_delta);
//    printf("%f\n", frame);
    model->gotoAndStop(frame);
}

bool FrameTweenController::getIsRun() {
    return tween->onGoing;
}