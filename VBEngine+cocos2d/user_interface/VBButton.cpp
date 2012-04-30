#include "VBButton.h"

VBButton::VBButton(VBModel* _model, VBButtonProtocol* _protocol) : VBResponder() {
    model = _model;
    model_area = _model->GetChildByInstanceName("area");
    if(!model_area)
        model_area = model;
    touch = NULL;
    protocol = _protocol;
}

VBButton::~VBButton() {
}

bool VBButton::GetIsDown() {
    return touch != NULL;
}

CCTouch* VBButton::GetTouch() {
    return touch;
}

VBModel* VBButton::GetModel() {
	return model;
}

void VBButton::TouchBegin(CCTouch* _touch) {
	VBResponder::TouchBegin(_touch);
    if(!protocol)
        return;
    if(!model)
        return;
    if(touch)
        return;
    bool _hit = model_area->IsHitByPoint(_touch->locationInView());
    if(_hit)
    	touch = _touch;
    protocol->ButtonTouchDown(this, _hit);
}

void VBButton::TouchEnd(CCTouch* _touch) {
	VBResponder::TouchEnd(_touch);
    if(!protocol)
        return;
    if(!model)
        return;
    if(_touch != touch)
        return;
    protocol->ButtonTouchUp(this, model_area->IsHitByPoint(_touch->locationInView()));
    touch = NULL;
}