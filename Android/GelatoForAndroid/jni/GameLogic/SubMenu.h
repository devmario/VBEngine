#ifndef gelatomania_SubMenu_h
#define gelatomania_SubMenu_h

#include "View.h"
#include "PackSelect.h"
#include "StageSelect.h"
#include "Shop.h"

//#define SHOP_EMPTY

using namespace cocos2d;

typedef enum SubMenuType {
    SubMenuTypeNone = 0,
    SubMenuTypePackSelect = 1,
    SubMenuTypeStageSelect = 2,
    SubMenuTypeShop = 3
} SubMenuType;

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
	
#ifndef SHOP_EMPTY
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
#endif
    
    SubMenuType type;
    int arg0;
    int arg1;
    
    SubMenu();
    ~SubMenu();
    
    void SetMenuType(SubMenuType _type, int _arg0, int _arg1);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
