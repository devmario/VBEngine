#ifndef gelatomania_SubMenu_h
#define gelatomania_SubMenu_h

#include "View.h"
#include "PackSelect.h"
#include "StageSelect.h"
#include "Shop.h"
#include "FrameTweenController.h"
#include "Friends.h"

//#define SHOP_EMPTY
VBObjectFile2D* LoadThumbObj(VBObjectFile2D** _obj);
VBTexture* LoadThumbTex(VBTexture** _tex);

using namespace cocos2d;

typedef enum SubMenuType {
    SubMenuTypeNone = 0,
    SubMenuTypePackSelect = 1,
    SubMenuTypeStageSelect = 2,
    SubMenuTypeShop = 3,
    SubMenuTypeFriends = 4
} SubMenuType;

class SubMenu : public View {
    void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    
public:
    bool isSetLayout;
    bool is_need_new_page;
    bool is_need_pop_root_history;
    bool is_sub_menu_transition;
    
    VBTexture* texPageThumbs;
    VBObjectFile2D* objPageThumbs;
    
    VBObjectFile2D* objSubMenu;
    VBTexture* texSubMenu;
    
    VBObjectFile2D* objSubMenuContainer;
    VBTexture* texSubMenuContainer;
    
    VBObjectFile2D* objRootUI;
    VBTexture* texRootUI;
    
    VBModel* bg;
    VBModel* ui;
    
    VBModel* bgT;
    VBModel* bgB;
    
    VBModel* shopM;
    
    VBModel* modelRootUI;
    FrameTweenController* frameCTR_friend;
    FrameTweenController* frameCTR_social;
    FrameTweenController* frameCTR_shop;
    
    VBModel* btBack;
    VBModel* btGift;
    VBModel* btShop;
    VBModel* btSocial;
    bool isOpenSocial;
    
    CCTouch* btBackTouch;
    CCTouch* btGiftTouch;
    CCTouch* btShopTouch;
    CCTouch* btSocialTouch;
    
    
    VBModel* btArch;
    CCTouch* touchArch;
    VBModel* btRank;
    CCTouch* touchRank;
    VBModel* btFB;
    CCTouch* touchFB;
    VBModel* btFriend;
    CCTouch* touchFriend;
    
    PackSelect* packView;
    StageSelect* stageView;
    Pages* currentPage;
	
#ifndef SHOP_EMPTY
    //shop
    Shop* shopView;
    
    Friends* friendsView;
    
    VBModel *vtShopBack;
    VBModel *vtShopRecipe;
	//
#endif
    
    SubMenuType type;
    int arg0;
    int arg1;
    
    SubMenuType next_type;
    int next_arg0;
    int next_arg1;
    
    SubMenu();
    ~SubMenu();
    
    void SetMenuType(SubMenuType _type, int _arg0, int _arg1);
    
    void BackPage();
    void ChangePage(SubMenuType _type, int _arg0, int _arg1);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
