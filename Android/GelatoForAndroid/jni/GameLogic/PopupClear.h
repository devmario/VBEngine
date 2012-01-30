#ifndef gelatomania_PopupClear_h
#define gelatomania_PopupClear_h

#include "Popup.h"
#include "NumberText.h"

class PopupClear : public Popup {
public:
    int starScore;
    int score;
    bool initedPopupClear;
    
    VBObjectFile2D* fontObj;
    VBTexture* fontTex;
    NumberText* scoreText;
    
    VBModel* fbBT;
    VBModel* fbM;
    CCTouch* fbTouch;
    float fbX;
    
    VBModel* twBT;
    VBModel* twM;
    CCTouch* twTouch;
    float twX;
    
    VBModel* star[3];
    VBModel* starSmall[3];
    VBModel* starBig[3];
    
    Tweener clearTween;
    TweenerParam fbParam;
    TweenerParam* runfbParam;
    TweenerParam twParam;
    TweenerParam* runtwParam;
    
    TweenerParam starParam;
    TweenerParam* runstarParam;
    float scoreCount;
    
    TweenerParam numParam;
    TweenerParam* runnumParam;
    float numCount;
    int numCountTime;
    
    CCTouch* numTouch;
    
    bool isRunStar[3];
    bool isBig[3];
    
    PopupClear(VBObjectFile2D* _obj, VBTexture* _tex, VBModel* _topView, int _starScore, int _score, VBObjectFile2D* _fontObj, VBTexture* _fontTex);
    ~PopupClear();
    
    virtual void init();
    
    void NumEnd();
    
    virtual void Update(float _deltaTime);
    
    virtual void Open(void (*_closeFunc)(void* _closeFuncRef), void* _closeFuncRef);
    virtual void Close();
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual const char* ObjName() {return "popup_clear.obj";};
    virtual const char* TexName() {return "popup_clear.png";};
};

#endif
