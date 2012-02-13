#ifndef gelatomania_PackSelect_h
#define gelatomania_PackSelect_h

#include "View.h"
#include "Pages.h"
#include "NumberText.h"

class SubMenu;

using namespace cocos2d;

class PackSelect : public Pages {
public:
    SubMenu* subMenu;
    
    VBArrayVector* packs;
    
    CCTouch* touchM;
    
    VBModel* touchMd;
    
    CCPoint startLocation;
    
    int selectedIdx;
    
    VBObjectFile2D* objPack;
    VBTexture* texPack;
    
    PackSelect(VBObjectFile2D* _thumbs_obj, VBTexture* _thumbs_tex, int _totalIdx, SubMenu* _subMenu);
    ~PackSelect();
    
    void Reset();
    
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
};

#endif
