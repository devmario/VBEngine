#include "Tweener.h"

TweenerWrapper::TweenerWrapper() : tween::Tweener()
{
    param = NULL;
    listener = NULL;
    callBack = NULL;
    callBackObject = NULL;
    
    onGoing = false;
    _currentPosition = NULL;
}

TweenerWrapper::~TweenerWrapper()
{
    clear();
}

void TweenerWrapper::begin(float *currentPosition, float end, float duration, float delay, bool isElastic, void(*callBackFunc)(void* callBackObj), void* callBackObj, bool easeOut)
{
    begin(currentPosition, end, duration, delay, isElastic?ELASTIC:EXPO, easeOut?EASE_OUT:EASE_IN, callBackFunc, callBackObj);
    
}

void TweenerWrapper::begin(float *currentPosition, float end, float duration, float delay, short ptransition, short pequation, void(*callBackFunc)(void* callBackObj), void* callBackObj)
{
    clear();
    _currentPosition = currentPosition;
    _end = end;
    _elapsedTime = 0.0f;
    _duration = (duration+delay)*1000.0f;
    _delay = delay*1000.0f;
    
    param = new TweenerParam(duration * 1000.0, ptransition, pequation, delay * 1000.0);
    param->addProperty(currentPosition, end);
    addTween(*param);
    if (callBackFunc) {
        callBack = callBackFunc;
    }
    if (callBackObj) {
        callBackObject = callBackObj;
    }
    
    onGoing = true;
    
}

void TweenerWrapper::setParamAndBegin(TweenerParam *wrapperParam, float *currentPosition, float end, void(*callBackFunc)(void* callBackObj), void* callBackObj)
{
    clear();
    
    param = wrapperParam;
    _currentPosition = currentPosition;
    _end = end;
    _duration = param->time;
    _delay = param->delay;
    
    param->addProperty(currentPosition, end);
    addTween(*param);
    if (callBackFunc) {
        callBack = callBackFunc;
    }
    if (callBackObj) {
        callBackObject = callBackObj;
    }
    
    onGoing = true;
}

void TweenerWrapper::update(float deltaTime)
{
    if (onGoing) {
        _elapsedTime += (deltaTime*1000.0f);
        if (_delay > _elapsedTime) {
            return;
        }
        if (_elapsedTime >= _duration) {
            *_currentPosition = _end;
            if (listener) {
                listener->onComplete(*param);
            }
            clear();
            if (callBack) {
                callBack(callBackObject);
                callBack = NULL;
                callBackObject = NULL;
            }
        } else {
            step((long)_elapsedTime);
        }
    }
}

void TweenerWrapper::clear()
{
    _start = 0.0f;
    _end = 0.0f;
    _elapsedTime = 0.0f;
    _duration = 0.0f;
    _delay = 0.0f;
    if (param) {
        removeTween(param);
        delete param;
        param = NULL;
        _currentPosition = NULL;
        onGoing = false;
    }
    lastTime = 0;
    
    removeListener();
}


void TweenerWrapper::addListener(tween::TweenerListener *wrapperListener) {
    removeListener();
    listener = wrapperListener;
    Tweener::addListener(listener);
}

void TweenerWrapper::removeListener()
{
    if (listener) {
        Tweener::removeListener(listener);
        delete listener;
        listener = NULL;
    }
}
