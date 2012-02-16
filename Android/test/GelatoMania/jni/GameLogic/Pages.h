#ifndef gelatomania_Pages_h
#define gelatomania_Pages_h

#include "View.h"
#include "Tweener.h"

//실시간 메모리관리 구현 안됨

using namespace cocos2d;
using namespace tween;

class Pages : public View {
public:
    int totalIdx;
    int idx;
    int preIdx;
    
    float widthThumbs;
    
    VBObjectFile2D* obj;
    VBTexture* tex;
    
    VBModel* thumb;
    
    VBModel* thumb_left;
    VBModel* thumb_center;
    VBModel* thumb_right;
    VBArrayVector* arr_thumbs;
    
    VBModel* slideM;
    
    TweenerWrapper *slideTween;
    TweenerWrapper *slideTweenThumb;
    
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

#endif
