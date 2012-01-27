#ifndef gelatomania_Scroller_h
#define gelatomania_Scroller_h

#include "VBModel.h"

class Scroller : public VBModel {
    void SetHeight(float _height);
public:
    VBModel* modelThumbTop;
    VBModel* modelThumb;
    VBModel* modelThumbBottom;
    
    VBModel* modelBGThumbTop;
    VBModel* modelBGThumb;
    VBModel* modelBGThumbBottom;
    
    VBAABB thumbBGSizeTop;
    VBAABB thumbBGSize;
    VBAABB thumbBGSizeBottom;
    
    VBAABB thumbSizeTop;
    VBAABB thumbSize;
    VBAABB thumbSizeBottom;
    
    float inScrollerX;
    
    float height;
    float maxHeight;
    
    Scroller(VBObjectFile2D* _objScroller, VBTexture* _texScroller, float _maxHeight);
    ~Scroller();
    
    void SetScroll(float _pageHeight, float _pageY);
};

#endif
