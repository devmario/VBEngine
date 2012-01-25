#ifndef gelatomania_SubMenu_h
#define gelatomania_SubMenu_h

#include "View.h"
#include "PackSelect.h"
#include "StageSelect.h"
#include "Shop.h"

using namespace cocos2d;

class SubMenu : public View {
    void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    
public:
    VBObjectFile2D* stageObj;
    VBObjectFile2D* packObj;
    VBTexture* stageTex;
    VBTexture* packTex;
    VBObjectFile2D* fontObj;
    VBTexture* fontTex;
    
    VBModel* bg;
    VBModel* ui;
    
    VBModel* btBack;
    VBModel* btGift;
    VBModel* btShop;
    VBModel* btFree;
    
    CCTouch* btBackTouch;
    CCTouch* btGiftTouch;
    CCTouch* btShopTouch;
    CCTouch* btFreeTouch;
    
    PackSelect* packView;
    StageSelect* stageView;
    Pages* currentPage;
	
    //shop
    VBObjectFile2D *shopMaskObj;
    VBTexture *shopMaskTex;
    VBModel *shopMaskMask;
    VBModel *shopMaskBg;
    VBObjectFile2D *shopObj;
    VBTexture *shopTex;
    Shop* shopView;
    
    VBModel *vtShopBack;
    VBModel *vtShopRecipe;
	//
    
    SubMenu(int _packID, int _stageID);
    ~SubMenu();
    
    void packSelect(int _pack);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
