#ifndef gelatomania_Popup_h
#define gelatomania_Popup_h

#include "View.h"
#include "CppTweener.h"

using namespace tween;

class PopupTweenListener;

class Popup : public View {
    void ClearTween();
public:
    bool inited;
    
    VBModel* topView;
    
    VBModel* popup;
    VBModel* bg;
    
    VBModel* reBT;
    CCTouch* reTouch;
    
    VBModel* plBT;
    CCTouch* plTouch;
    
    VBModel* meBT;
    CCTouch* meTouch;
    
    VBModel* shBT;
    CCTouch* shTouch;
    
    VBModel* frBT;
    CCTouch* frTouch;
    
    float popupY;
    float bgAlpha;
    
    void* closeFuncRef;
    void (*closeFunc)(void* _closeFuncRef);
    
    bool isClosed;
    int closeCount;
    float elapseTime;
    Tweener showTween;
    TweenerParam slideParam;
    TweenerParam* runslideParam;
    TweenerParam alphaParam;
    TweenerParam* runalphaParam;
    PopupTweenListener* listner;
    
    VBObjectFile2D* obj;
    VBTexture* tex;
    
    VBObjectFile2D* objRes;
    VBTexture* texRes;
    
    Popup(VBObjectFile2D* _obj, VBTexture* _tex, VBModel* _topView);
    ~Popup();
    
    virtual void init();
    
    virtual void Update(float _deltaTime);
    
    virtual void Open(void (*_closeFunc)(void* _closeFuncRef), void* _closeFuncRef);
    virtual void Close();
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual const char* ObjName() {return "popup_pause.obj";};
    virtual const char* TexName() {return "popup_pause.png";};
};

class PopupTweenListener : public TweenerListener {
public:
    Popup* popup;
    
    PopupTweenListener(Popup* _popup) {
        popup = _popup;
    };
    
    void onStart(TweenerParam& param) {
        
    }
    
    void onStep(TweenerParam& param) {
        
    }
    
    void onComplete(TweenerParam& param) {
        if(popup->closeFunc)
            popup->closeFunc(popup->closeFuncRef);
    };
};

#endif
