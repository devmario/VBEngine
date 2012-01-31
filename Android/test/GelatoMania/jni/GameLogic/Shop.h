#ifndef gelatomania_Shop_h
#define gelatomania_Shop_h

#include "Pages.h"
#include "ShopScrollContainer.h"

class Shop : public Pages {
private:  
    VBTexture *backgroundTexture;
    
    VBModel *backgroundModel;
    VBModel *containerModel;
    VBObjectFile2D *objScroll;
    VBTexture *texScroll;
    
public:
    ShopScrollerContainer *container;
    VBArrayVector *inAppDataVector;
    
    Shop(VBObjectFile2D* _obj, VBTexture* _tex);
    ~Shop();
    
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};


#endif