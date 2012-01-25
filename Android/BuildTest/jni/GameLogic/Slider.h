#ifndef gelatomania_Slider_h
#define gelatomania_Slider_h

#include "VBModel.h"
#include "CppTweener.h"

using namespace tween;

enum SliderDir {
    SliderDir_Horizontal    =   0x01,
    SliderDir_Vertical      =   0x02,
    SliderDir_LT            =   0x04,
    SliderDir_RB            =   0x08,
    SliderDir_Horizontal_L  =   SliderDir_Horizontal    |   SliderDir_LT,
    SliderDir_Horizontal_R  =   SliderDir_Horizontal    |   SliderDir_RB,
    SliderDir_Vertical_T    =   SliderDir_Vertical      |   SliderDir_LT,
    SliderDir_Vertical_B    =   SliderDir_Vertical      |   SliderDir_RB,
};

class Slider {
public:
    Slider(VBModel* _sliderModel, bool _enable = true,
           float _enableValue = 0.0, float _disableValue = -100.0, float _slideValue = 50.0, float _maxSlideValue = 100.0, 
           SliderDir _dir = SliderDir_Horizontal_L, 
           void* _callbackObj = NULL,
           void (*_slideCompleteCallback)(void* _obj) = NULL, 
           void (*_enableCompleteCallback)(void* _obj) = NULL, 
           void (*_disableCompleteCallback)(void* _obj) = NULL);
    ~Slider();
    
    bool GetEnable();
    void SetEnable(bool _enable, float _delayTime = 0.0);
    
    void Update(float _deltaTime);
    void TouchBegin(CCTouch* _touch, CCPoint _location);
    void TouchMove(CCTouch* _touch, CCPoint _location);
    void TouchEnd(CCTouch* _touch, CCPoint _location);
    void TouchCancel(CCTouch* _touch, CCPoint _location);
    
    bool GetIsMovement();
    
private:
    
    bool enable;
    SliderDir dir;
    
    VBModel* sliderModel;
    
    void* callbackObj;
    void (*slideCompleteCallback)(void* _obj);
    bool readyTweenCompleteCallback;
    void (*enableCompleteCallback)(void* _obj);
    void (*disableCompleteCallback)(void* _obj);
    
    float enableValue;
    float disableValue;
    float slideValue;
    float maxSlideValue;
    
    void ClearSliderTween();
    void BeginSliderTween(float _value, float _time, bool _is_elastic, bool _use_callback, float _delayTime = 0.0);
    void UpdateSliderTween(float _deltaTime);
    
    Tweener* sliderTweener;
    TweenerParam* sliderTweenerParam;
    float sliderTweenerTime;
    float sliderTweenerTimeCount;
    
    CCTouch* touch;
    CCPoint preLocation;
    
    float value;
    
    bool IsHorizontal();
    bool IsLT();
    bool GetValueDir();
    
    void SetSlideValue(float _value);
    float GetSlideValue();
};

#endif
