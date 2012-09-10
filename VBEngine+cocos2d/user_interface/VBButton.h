#ifndef VBButton_h
#define VBButton_h

#include "VBModel.h"
#include "VBResponder.h"

class VBButton;

class VBButtonProtocol {
public:
    virtual void ButtonTouchDown(VBButton* _button, bool _is_inside) {};
    virtual void ButtonTouchUp(VBButton* _button, bool _is_inside) {};
};

class VBButton : public VBResponder {
protected:
    VBButtonProtocol* protocol;
    VBModel* model;
    VBModel* model_area;
    CCTouch* touch;
    
public:
    VBButton(VBModel* _model, VBButtonProtocol* _protocol, std::string _responder_tag = "");
    ~VBButton();
    
    bool GetIsDown();
    CCTouch* GetTouch();
	VBModel* GetModel();
    
    virtual void TouchBegin(CCTouch* _touch);
    virtual void TouchEnd(CCTouch* _touch);
};

#endif
