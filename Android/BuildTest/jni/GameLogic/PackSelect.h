#ifndef gelatomania_PackSelect_h
#define gelatomania_PackSelect_h

#include "View.h"
#include "CppTweener.h"
#include "Pages.h"
#include "NumberText.h"

using namespace cocos2d;

class PackSelect : public Pages {
public:
    VBArrayVector* packs;
    
    CCTouch* touchM;
    
    VBModel* touchMd;
    
    int selectedIdx;
    
    PackSelect(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex,
               int _totalIdx);
    ~PackSelect();
    
    void* pss;
    void (*selectedFunc)(void* _pss);
    
    void Reset();
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
};

#endif
