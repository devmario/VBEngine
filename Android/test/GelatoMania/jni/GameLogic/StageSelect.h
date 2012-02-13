#ifndef gelatomania_StageSelect_h
#define gelatomania_StageSelect_h

#include "View.h"
#include "Pages.h"

using namespace cocos2d;

class StageSelect : public Pages {
public:
    VBObjectFile2D* objStage;
    VBTexture* texStage;
    
    VBArrayVector* stages;
    int packIdx;
    CCTouch* touchM;
    VBModel* touchMd;
    
    VBModel* bg[2];
    
    CCPoint startLocation;
    
    StageSelect(VBObjectFile2D* _obj, VBTexture* _tex, 
                int _totalIdx);
    ~StageSelect();
    
    void SetPack(int _idx);
    
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
};

#endif
