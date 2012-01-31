#include "Slider.h"

bool Slider::GetIsMovement() {
    return sliderTweener || touch;
}

void Slider::ClearSliderTween() {
    if(sliderTweenerParam) {
        if(sliderTweener)
            sliderTweener->removeTween(sliderTweenerParam);
        delete sliderTweenerParam;
    }
    sliderTweenerParam = NULL;
    if(sliderTweener) {
        delete sliderTweener;
    }
    sliderTweener = NULL;
}

void Slider::BeginSliderTween(float _value, float _time, bool _is_elastic, bool _use_callback, float _delayTime) {
    ClearSliderTween();
    sliderTweener = new Tweener();
    sliderTweenerTimeCount = 0.0;
    sliderTweenerTime = _time + _delayTime;
    sliderTweenerParam = new TweenerParam(sliderTweenerTime * 1000, _is_elastic ? ELASTIC : EXPO, EASE_OUT, _delayTime * 1000);
    valueLast = _value;
    sliderTweenerParam->addProperty(&value, valueLast);
    sliderTweener->addTween(*sliderTweenerParam);
    readyTweenCompleteCallback = _use_callback;
}

void Slider::UpdateSliderTween(float _deltaTime) {
    if(sliderTweener) {
        sliderTweenerTimeCount += _deltaTime;
        sliderTweener->step(sliderTweenerTimeCount * 1000);
        if(sliderTweenerTimeCount > sliderTweenerTime) {
            ClearSliderTween();
            value = valueLast;
            if(readyTweenCompleteCallback) {
                if(enable) {
                    if(enableCompleteCallback)
                        enableCompleteCallback(callbackObj);
                } else {
                    if(disableCompleteCallback)
                        disableCompleteCallback(callbackObj);
                }
            }
        }
    }
}


Slider::Slider(VBModel* _sliderModel, bool _enable,
               float _enableValue, float _disableValue, float _slideValue, float _maxSlideValue, 
               SliderDir _dir, 
               void* _callbackObj,
               void (*_slideCompleteCallback)(void* _obj),
               void (*_enableCompleteCallback)(void* _obj), 
               void (*_disableCompleteCallback)(void* _obj)) {
    sliderTweener = NULL;
    sliderTweenerParam = NULL;
    sliderModel = _sliderModel;
    enableValue = _enableValue;
    disableValue = _disableValue;
    slideValue = _slideValue;
    maxSlideValue = _maxSlideValue;
    dir = _dir;
    enable = _enable;
    callbackObj = _callbackObj;
    slideCompleteCallback = _slideCompleteCallback;
    enableCompleteCallback = _enableCompleteCallback;
    disableCompleteCallback = _disableCompleteCallback;
    touch = NULL;
    value = _enable ? _enableValue : _disableValue;
    //printf("0.1 ");
    SetSlideValue(value);
    //printf("0.2 ");
}

Slider::~Slider() {
    ClearSliderTween();
}

bool Slider::GetEnable() {
    return enable;
}

void Slider::SetEnable(bool _enable, float _delayTime) {
    if(enable != _enable) {
        enable = _enable;
        BeginSliderTween(_enable ? enableValue : disableValue, 0.5, _enable, true, _delayTime);
    }
}

void Slider::Update(float _deltaTime) {
    if(touch)
        SetSlideValue(GetSlideValue() + (value - GetSlideValue()) * 0.2);
    else {
        UpdateSliderTween(_deltaTime);
        SetSlideValue(value);
    }
}

void Slider::TouchBegin(CCTouch* _touch, CCPoint _location) {
    if(touch == NULL) {
        if(sliderModel->checkCollisionWithButton(_location)) {
            ClearSliderTween();
            touch = _touch;
            preLocation = _location;
        }
    }
}

void Slider::TouchMove(CCTouch* _touch, CCPoint _location) {
    if(touch == _touch) {
        float _sub = IsHorizontal() ? (_location.x - preLocation.x) : (_location.y - preLocation.y);
        bool _valueDir = GetValueDir();
        if(_valueDir ? (value + _sub > maxSlideValue) : (value + _sub < maxSlideValue)) {
            value = maxSlideValue;
        } else if(_valueDir ? (value + _sub < enableValue) : (value + _sub > enableValue)) {
            value = enableValue;
        } else {
            value += _sub;
        }
        SetSlideValue(value);
        preLocation = _location;
    }
}

void Slider::TouchEnd(CCTouch* _touch, CCPoint _location) {
    if(touch == _touch) {
        TouchMove(_touch, _location);
        touch = NULL;
        BeginSliderTween(enableValue, 0.5, true, false);
        bool _valueDir = GetValueDir();
        if(_valueDir ? GetSlideValue() > slideValue : GetSlideValue() < slideValue) {
            if(slideCompleteCallback)
                slideCompleteCallback(callbackObj);
        }
    }
}

void Slider::TouchCancel(CCTouch* _touch, CCPoint _location) {
    TouchEnd(_touch, _location);
}

bool Slider::IsHorizontal() {
    return dir & SliderDir_Horizontal;
}

bool Slider::IsLT() {
    return dir & SliderDir_LT;
}

bool Slider::GetValueDir() {
    bool _flag = IsHorizontal();
    _flag = IsLT() ? _flag : !_flag;
    return _flag;
}
void Slider::SetSlideValue(float _value) {
    if(IsHorizontal()) {
        sliderModel->setPosition(CCPointMake(_value, sliderModel->getPosition().y));
    } else {
        sliderModel->setPosition(CCPointMake(sliderModel->getPosition().x, _value));
    }
}

float Slider::GetSlideValue() {
    return IsHorizontal() ? sliderModel->getPosition().x : sliderModel->getPosition().y;
}
