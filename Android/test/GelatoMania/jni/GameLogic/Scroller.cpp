#include "Scroller.h"
#include "ShareData.h"

Scroller::Scroller(VBObjectFile2D* _objScroller, VBTexture* _texScroller, float _maxHeight) : VBModel() {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _name_id;
    
    maxHeight = _maxHeight;
    
    LIBNAMEFIND(_name_id, _objScroller, "bgTop", _str);
    if(_name_id) {
        modelBGThumbTop = new VBModel(_objScroller, _name_id, _texScroller, true);
        addChild(modelBGThumbTop);
        thumbBGSizeTop = modelBGThumbTop->getVBModelSize();
    } else {
        modelBGThumbTop = NULL;
    }
    
    LIBNAMEFIND(_name_id, _objScroller, "bgMiddle", _str);
    if(_name_id) {
        modelBGThumb = new VBModel(_objScroller, _name_id, _texScroller, true);
        addChild(modelBGThumb);
        thumbBGSize = modelBGThumb->getVBModelSize();
    } else {
        modelBGThumb = NULL;
    }
    
    LIBNAMEFIND(_name_id, _objScroller, "bgBottom", _str);
    if(_name_id) {
        modelBGThumbBottom = new VBModel(_objScroller, _name_id, _texScroller, true);
        addChild(modelBGThumbBottom);
        thumbBGSizeBottom = modelBGThumbBottom->getVBModelSize();
        
        modelBGThumb->setPosition(CCPointMake(0, modelBGThumbTop->getPosition().y - (thumbBGSizeTop.b - thumbBGSizeTop.t)));
        float middleH = _maxHeight - (thumbBGSizeTop.b - thumbBGSizeTop.t) - (thumbBGSizeBottom.b - thumbBGSizeBottom.t);
        if(middleH < 0.0)
            middleH = 0.0;
        modelBGThumb->setScaleY(middleH);
        
        modelBGThumbBottom->setPosition(CCPointMake(0, modelBGThumb->getPosition().y - middleH));
    } else {
        modelBGThumbBottom = NULL;
    }
    
    LIBNAMEFIND(_name_id, _objScroller, "top", _str);
    modelThumbTop = new VBModel(_objScroller, _name_id, _texScroller, true);
    addChild(modelThumbTop);
    
    LIBNAMEFIND(_name_id, _objScroller, "middle", _str);
    modelThumb = new VBModel(_objScroller, _name_id, _texScroller, true);
    addChild(modelThumb);
    
    LIBNAMEFIND(_name_id, _objScroller, "bottom", _str);
    modelThumbBottom = new VBModel(_objScroller, _name_id, _texScroller, true);
    addChild(modelThumbBottom);
    
    thumbSizeTop = modelThumbTop->getVBModelSize();
    thumbSize = modelThumb->getVBModelSize();
    thumbSizeBottom = modelThumbBottom->getVBModelSize();
    
    if(modelBGThumbTop) {
        inScrollerX = (thumbBGSizeTop.r - thumbBGSizeTop.l) * 0.5 - (thumbSizeTop.r - thumbSizeTop.l) * 0.5;
    } else {
        inScrollerX = 0.0;
    }
    
    height = 0;
}

Scroller::~Scroller() {
    removeChild(modelThumbTop, false);
    removeChild(modelThumb, false);
    removeChild(modelThumbBottom, false);
    
    if(modelBGThumbTop)
        removeChild(modelBGThumbTop, false);
    if(modelBGThumb)
        removeChild(modelBGThumb, false);
    if(modelBGThumbBottom)
        removeChild(modelBGThumbBottom, false);

    delete modelThumbTop;
    delete modelThumb;
    delete modelThumbBottom;
    
    if(modelBGThumbTop)
        delete modelBGThumbTop;
    if(modelBGThumb)
        delete modelBGThumb;
    if(modelBGThumbBottom)
        delete modelBGThumbBottom;
}

void Scroller::SetHeight(float _height) {
    height = _height;
    float thumbHT = thumbSizeTop.b - thumbSizeTop.t;
    float thumbHB = thumbSizeBottom.b - thumbSizeBottom.t;
    
    modelThumb->setPosition(CCPointMake(inScrollerX, modelThumbTop->getPosition().y - thumbHT));
    float middleH = _height - thumbHT - thumbHB;
    if(middleH < 0.0)
        middleH = 0.0;
    modelThumb->setScaleY(middleH);
    
    modelThumbBottom->setPosition(CCPointMake(inScrollerX, modelThumb->getPosition().y - middleH));
}

void Scroller::SetScroll(float _pageHeight, float _pageY) {
    float thumbHT = thumbSizeTop.b - thumbSizeTop.t; //위패턴사이즈
    float thumbHB = thumbSizeBottom.b - thumbSizeBottom.t; //아래패턴사이즈
    
    float _maxH = maxHeight - inScrollerX * 2.0; //최대 스크롤 크기
    float _p = maxHeight / _pageHeight; //스크롤러와 페이지 크기의 비율
    float _h = _p * _maxH; //스크롤러의 크기
    float _maxY = _maxH - thumbHT - thumbHB; //최대 스크롤 위치
    float _y = (maxHeight - thumbHT - thumbHB) * (_pageY / _pageHeight); //스크롤러의 위치
    if(_y > 0) {
        _h -= _y;
        _y = 0;
    } else if(-_y > _maxH - _h) {
        if(-_y > _maxY) {
            _y = -_maxY;
            _h = 0.0;
        } else {
            _h += _maxH - _h + _y;
        }
    }
    
    modelThumbTop->setPosition(CCPointMake(inScrollerX, _y - inScrollerX));
    SetHeight(_h);
}
