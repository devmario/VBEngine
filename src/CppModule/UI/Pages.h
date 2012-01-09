#ifndef gelatomania_Pages_h
#define gelatomania_Pages_h

#include "View.h"
#include "CppTweener.h"

//실시간 메모리관리 구현 안됨

using namespace cocos2d;
using namespace tween;

class PagesTweenListener;

class Pages : public View {
public:
    int totalIdx;
    int idx;
    int preIdx;
    
    VBObjectFile2D* obj;
    VBTexture* tex;
    
    VBModel* thumb;
    VBModel* slideM;
    
    float elapseTime;
    
    Tweener slideTween;
    TweenerParam param;
    TweenerParam* runparam;
    
    PagesTweenListener* listener;
    
    float elapseTimeThumb;
    
    Tweener slideTweenThumb;
    TweenerParam paramThumb;
    TweenerParam* runparamThumb;
    
    CCTouch* touchSlide;
    float touchX;
    float slideX;
    float force;
    float targetX;
    float startX;
    float endX;
    float startY;
    float pageTh;
    float thumbX;
    float thumbY;
    float slideXThumb;
	
    Pages(VBObjectFile2D* _obj, VBTexture* _tex, 
          int _totalIdx, float _startX, float _endX, float _startY, float _pageTh,
          float _thumbX, float _thumbY);
    ~Pages();
    
    void* pageFuncRef;
    void (*pageFunc)(void* _pageFuncRef);
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

class PagesTweenListener : public TweenerListener {
public:
    Pages* page;
    
    PagesTweenListener(Pages* _page) {
        page = _page;
    };
    
    void onStart(TweenerParam& param) {
        
    }
    
    void onStep(TweenerParam& param) {
        
    }
    
    void onComplete(TweenerParam& param) {
        if(page->idx < 0) {
            ((CCSprite*)page->top)->removeChild((CCSprite*)page->slideM, false);
            ((CCSprite*)page->top)->removeChild((CCSprite*)page->thumb, false);
        }
        if(page->pageFunc)
            page->pageFunc(page->pageFuncRef);
    };
};

#endif
