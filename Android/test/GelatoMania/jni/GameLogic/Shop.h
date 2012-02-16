#ifndef gelatomania_Shop_h
#define gelatomania_Shop_h

#include "Pages.h"
#include "ShopScrollContainer.h"
#include "Text.h"

class Shop : public Pages {
private:  
    VBObjectFile2D *shopObj;
    VBTexture *shopTex;
    
    Text* textTap[3];
    CCTouch* touchTap[3];
    
    VBTexture *backgroundTexture;
    
    VBModel *backgroundModel;
    VBModel *containerModel;
    VBObjectFile2D *objScroll;
    VBTexture *texScroll;
    
    VBModel* modelTap;
    
    Text* starCount;
    Text* undoCount;
    Text* hintCount;
public:
    
    int tapIdx;
    ShopScrollerContainer *container;
    VBArrayVector *inAppDataVector;
    
    Shop(VBObjectFile2D** objSubMenuContainer, VBTexture** texSubMenuContainer, int _tapidx);
    ~Shop();
    
    void SetTap(int _idx);
    
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};


#endif
