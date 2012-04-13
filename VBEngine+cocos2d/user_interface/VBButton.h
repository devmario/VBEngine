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
public:
    VBButtonProtocol* protocol;
    VBModel* model;
    VBModel* model_area;
    CCTouch* touch;
    
    VBButton(VBModel* _model, VBButtonProtocol* _protocol);
    ~VBButton();
    
    bool GetIsDown();
    CCTouch* GetTouch();
    
    virtual void TouchBegin(CCTouch* _touch);
    virtual void TouchEnd(CCTouch* _touch);
};

#endif
