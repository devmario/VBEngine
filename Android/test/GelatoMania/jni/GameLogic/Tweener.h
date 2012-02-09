#ifndef gelatomania_Tweener_h
#define gelatomania_Tweener_h

#include "CppTweener.h"

using namespace tween;

class TweenerWrapper : public Tweener {
private:
    TweenerParam *param;
    TweenerListener *listener;
    void (*callBack)(void* something);
    void* callBackObject;
    
    float *_currentPosition;
    float _start;
    float _end;
    
    float _elapsedTime;
    float _duration;
    float _delay;
    
public:
    bool onGoing;
    
    TweenerWrapper();
    ~TweenerWrapper();
    void begin(float *currentPosition, float end, float duration, float delay, bool isElastic, void(*callBackFunc)(void* object)=NULL, void* callBackObj=NULL, bool easeOut=true);
    void begin(float *currentPosition, float end, float duration, float delay, short ptransition, short pequation, void(*callBackFunc)(void* callBackObj), void* callBackObj);
    void update(float deltaTime);
    void clear();
    
    void setParamAndBegin(TweenerParam *wrapperParam, float *currentPosition, float end, void(*callBackFunc)(void*)=NULL, void* callBackObj=NULL);
    
    void addProperty(float* valor, float valorFinal);
    
    virtual void addListener(TweenerListener* wrapperListener);
    virtual void removeListener();
};
#endif
