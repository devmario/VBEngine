#include "Pages.h"
#include "ShareData.h"

#define SLIDE_TOUCH_TH 5

void tweenCallback(void* obj);

Pages::Pages(VBObjectFile2D* _obj, VBTexture* _tex, 
             int _totalIdx, float _startX, float _endX, float _startY, float _pageTh,
             float _thumbX, float _thumbY) : View() {
    slideTween = slideTweenThumb = NULL;
    
    touchSlide = NULL;
    force = 0;
    endX = _endX;
    slideXThumb = targetX = slideX = endX;
    totalIdx = _totalIdx;
    preIdx = idx = -1;
    elapseTimeTotal = elapseTime = 0.0;
    elapseTimeThumbTotal = elapseTimeThumb = 0.0;
    listener = NULL;
    pageFunc = NULL;
    pageFuncRef = NULL;
    startX = _startX;
    startY = _startY;
    pageTh = _pageTh;
    thumbX = _thumbX;
    thumbY = _thumbY;
    
    obj = _obj;
    tex = _tex;
    
    slideM = new VBModel();
    ((CCSprite*)slideM)->setPosition(CCPointMake(slideX, startY));
    
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    LIBNAMEFIND(_library_name_id, _obj, "thumb", _str);
    if(_library_name_id) {
        thumb = new VBModel(obj, _library_name_id, tex, true);
        thumb->setPosition(CCPointMake(slideXThumb, thumbY));
        thumb->stop();
    } else {
        thumb = NULL;
    }
}

Pages::~Pages() {
    if (slideTween) {
        delete slideTween;
    }
    if (slideTweenThumb) {
        delete slideTweenThumb;
    }
    
    if(top->getChildren()) {
        if(top->getChildren()->containsObject(thumb)) {
            if(thumb)
                top->removeChild(thumb, false);
        }
        if(top->getChildren()->containsObject(slideM))
            top->removeChild(slideM, false);
    }
    if(thumb)
        delete thumb;
    delete slideM;
}

void Pages::GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef) {
    pageFunc = _pageFunc;
    pageFuncRef = _pageFuncRef;
    
    if(idx != _idx)
        preIdx = idx;
    idx = _idx;
    
    if(totalIdx <= idx)
        idx = totalIdx - 1;
    
    if(idx < 0)
        targetX = endX;
    else
        targetX = startX - pageTh * idx;
    
    if (slideTween) {
        delete slideTween;
        slideTween = NULL;
    }
    if (slideTweenThumb) {
        delete slideTweenThumb;
        slideTweenThumb = NULL;
    }
    
    
    elapseTime = 0.0;
    elapseTimeTotal = _idx < 0 ? 0.25 : 0.5;
    
    TweenerParam *param = new TweenerParam(1000 * elapseTimeTotal, EXPO, _idx < 0 ? EASE_IN : EASE_OUT);
    
    slideTween = new TweenerWrapper();
    
    last = targetX;
    slideTween->setParamAndBegin(param, &slideX, last, tweenCallback, this);
    
    if(idx < 0) {
        listener = new PagesTweenListener(this);
        slideTween->addListener(listener);
    }
    
    slideTweenThumb = new TweenerWrapper();
    
    elapseTimeThumb = 0.0;
    elapseTimeThumbTotal = _idx < 0 ? 0.25 : 0.5;
    TweenerParam *paramThumb = new TweenerParam(1000 * elapseTimeThumbTotal, EXPO, _idx < 0 ? EASE_IN : EASE_OUT);
    lastThumb = _idx < 0 ? endX : thumbX;
    
    slideTweenThumb->setParamAndBegin(paramThumb, &slideXThumb, lastThumb);
    
    if(idx >= 0 && totalIdx > idx) {
        if(thumb)
            thumb->gotoAndStop(idx);
    }
    if(idx >= 0) {
        if(top->getChildren()) {
            if(!top->getChildren()->containsObject(slideM)) {
                top->addChild(slideM);
            }
            if(thumb) {
                if(!top->getChildren()->containsObject(thumb)) {
                    top->addChild(thumb);
                }
            }
        } else {
            top->addChild(slideM);
            if(thumb)
                top->addChild(thumb);
        }
    }
}

void Pages::Update(float _deltaTime) {
    if(touchSlide == NULL) {
        if (slideTween->onGoing) {
            slideTween->update(_deltaTime);
            slideM->setPosition(CCPointMake(slideX, startY));
        }
    }
    if(slideTweenThumb) {
        slideTweenThumb->update(_deltaTime);
        if(thumb)
            thumb->setPosition(CCPointMake(slideXThumb, thumbY));
    }
}

void Pages::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchSlide == NULL) {
        force = 0.0;
        touchX = _location.x;
        touchSlide = _touch;
    }
}

void Pages::touchMove(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchSlide == _touch) {
        force = _location.x - touchX;
        slideX += force;
        touchX = _location.x;
        ((CCSprite*)slideM)->setPosition(CCPointMake(slideX, startY));
    }
}

void Pages::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchSlide == _touch) {
        int nextIdx = idx;
        if(fabsf(force) > SLIDE_TOUCH_TH) {
            if(force < 0) {
                if(nextIdx < totalIdx - 1)
                    nextIdx++;
            } else {
                if(nextIdx > 0)
                    nextIdx--;
            }
        } else {
            float _f = FLT_MAX;
            for(int i = 0; i < totalIdx; i++) {
                float _th = slideX - startX + (i * pageTh);
                if(_f > fabsf(_th)) {
                    _f = fabsf(_th);
                    nextIdx = i;
                }
            }
        }
        GoPage(nextIdx, NULL, NULL);
        
        touchSlide = NULL;
    }
}

void Pages::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}

void Pages::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}


void tweenCallback(void* obj)
{
    Pages *page = (Pages*)obj;
    if(page->idx < 0) {
        ((CCSprite*)page->top)->removeChild((CCSprite*)page->slideM, false);
        ((CCSprite*)page->top)->removeChild((CCSprite*)page->thumb, false);
    }
    if(page->pageFunc)
        page->pageFunc(page->pageFuncRef);
}
