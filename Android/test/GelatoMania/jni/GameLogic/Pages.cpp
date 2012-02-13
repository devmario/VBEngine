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
    
    arr_thumbs = VBArrayVectorInit(VBArrayVectorAlloc());
    thumb = new VBModel();
    
    thumb_left = NULL;
    thumb_center = NULL;
    thumb_right = NULL;
    
    float _thumb_tick = 15;
    float _thumb_left_tick = 10;
    float _thumb_right_tick = 10;
    float _size_left;
    float _size_right;
    float _size = _thumb_tick * _totalIdx + _thumb_left_tick + _thumb_right_tick;
    
    widthThumbs = 0.0;
    
    if(_obj && _tex) {
        LIBNAMEFIND(_library_name_id, _obj, "pageLeft", _str);
        if(_library_name_id) {
            thumb_left = new VBModel(_obj, _library_name_id, _tex, true);
            thumb->addChild(thumb_left);
            _size_left = VBAABBGetWidth(thumb_left->getVBModelSize());
        }
        
        LIBNAMEFIND(_library_name_id, _obj, "pageRight", _str);
        if(_library_name_id) {
            thumb_right = new VBModel(_obj, _library_name_id, _tex, true);
            thumb->addChild(thumb_right);
            _size_right = VBAABBGetWidth(thumb_right->getVBModelSize());
            thumb_right->setPosition(CCPoint(_size - _size_right, 0));
        }
        
        LIBNAMEFIND(_library_name_id, _obj, "pagePattern", _str);
        if(_library_name_id) {
            thumb_center = new VBModel(_obj, _library_name_id, _tex, true);
            thumb_center->setPosition(CCPoint(_size_left, 0));
            thumb_center->setScaleX(_size - _size_left - _size_right);
            thumb->addChild(thumb_center);
        }
        
        for(int i = 0; i < _totalIdx; i++) {
            char buf[0xFF] = {'\0'};
            sprintf(buf, "id_mom_page%02d", i+1);
            LIBNAMEFIND(_library_name_id, _obj, buf, _str);
            VBModel* _thumb = NULL;
            if(_library_name_id) {
                _thumb = new VBModel(_obj, _library_name_id, _tex, true);
                _thumb->gotoAndStop(0);
                thumb->addChild(_thumb);
                float _height_thumb = VBAABBGetHeight(_thumb->getVBModelSize());
                _thumb->setPosition(CCPoint(_thumb_left_tick + i * _thumb_tick, _height_thumb - 4));
            }
            VBArrayVectorAddBack(arr_thumbs, _thumb);
        }
        widthThumbs = _size;
        thumb->setPosition(CCPointMake(slideXThumb - widthThumbs * 0.5, thumbY));
    }
}

Pages::~Pages() {
    if(thumb_center) {
        thumb->removeChild(thumb_center, false);
        delete thumb_center;
    }
    if(thumb_left) {
        thumb->removeChild(thumb_left, false);
        delete thumb_left;
    }
    if(thumb_right) {
        thumb->removeChild(thumb_right, false);
        delete thumb_right;
    }
    while (VBArrayVectorGetLength(arr_thumbs)) {
        VBModel* _thumb = (VBModel*)VBArrayVectorRemoveBack(arr_thumbs);
        if(_thumb) {
            thumb->removeChild(_thumb, false);
            delete _thumb;
        }
    }
    VBArrayVectorFree(&arr_thumbs);
    
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
        if(thumb) {
            for(int i = 0; i < totalIdx; i++) {
                VBModel* _thumb = (VBModel*)VBArrayVectorGetDataAt(arr_thumbs, i);
                if(_thumb) {
                    _thumb->gotoAndStop(i == idx ? 0 : 1);
                }
            }
        }
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
        if(slideTween) {
            if (slideTween->onGoing) {
                slideTween->update(_deltaTime);
                slideM->setPosition(CCPointMake(slideX, startY));
            }
        }
    }
    if(slideTweenThumb) {
        slideTweenThumb->update(_deltaTime);
        if(thumb)
            thumb->setPosition(CCPointMake(slideXThumb - widthThumbs * 0.5, thumbY));
    }
}

void Pages::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchSlide == NULL) {
        force = 0.0;
        float scale = 1.0;
        if(CCDirector::sharedDirector()->isRetinaDisplay() == false)
            scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
        touchX = _location.x / scale;
        touchSlide = _touch;
    }
}

void Pages::touchMove(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchSlide == _touch) {
        float scale = 1.0;
        if(CCDirector::sharedDirector()->isRetinaDisplay() == false)
            scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
        force = _location.x / scale - touchX;
        slideX += force;
        touchX = _location.x / scale;
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
