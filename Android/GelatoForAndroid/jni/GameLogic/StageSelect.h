#ifndef gelatomania_StageSelect_h
#define gelatomania_StageSelect_h

#include "View.h"
#include "CppTweener.h"
#include "Pages.h"

using namespace cocos2d;

class StageSelect : public Pages {
public:
    VBArrayVector* stages;
    int packIdx;
    CCTouch* touchM;
    VBModel* touchMd;
    
    VBObjectFile2D* fontObj;
    VBTexture* fontTex;
    
    VBModel* bg[2];
    
    StageSelect(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex, 
                int _totalIdx);
    ~StageSelect();
    
    void SetPack(int _idx);
    
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
};

#endif
