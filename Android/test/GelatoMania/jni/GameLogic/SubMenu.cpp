#include "SubMenu.h"
#include "ShareData.h"
#include "PlatformFunctions.h"

#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#define LOG_TAG  "SubMenu"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

void ChangeView(void* _ref);

SubMenu::SubMenu() {
    //View::View();
    
    VBString* _str = NULL;
    OBJLOAD(stageObj, "stage_select.obj", _str);
    OBJLOAD(packObj, "pack_select.obj", _str);
    TEXLOAD(stageTex, "stage_select.png", _str);
    TEXLOAD(packTex, "pack_select.png", _str);
    OBJLOAD(fontObj, "font.obj", _str);
    TEXLOAD(fontTex, "font.png", _str);
    
    VBObjectFile2DLibraryNameID* _library_name_id = NULL;
    LIBNAMEFIND(_library_name_id, stageObj, "_dynamic/dy_menu_stage0_bg", _str);
    bg = new VBModel(stageObj, _library_name_id, stageTex, true);
    ((CCSprite*)top)->addChild((CCSprite*)bg);
    
    packView = new PackSelect(packObj, packTex, fontObj, fontTex, ShareDataGetPackLength(), this);
    stageView = new StageSelect(stageObj, stageTex, fontObj, fontTex, 2);
    
#ifndef SHOP_EMPTY
    //add shop
    OBJLOAD(shopMaskObj, "shop_mask.obj", _str);
    TEXLOAD(shopMaskTex, "shop_mask.png", _str);
    LIBNAMEFIND(_library_name_id, shopMaskObj, "bg", _str);
    shopMaskBg = new VBModel(shopMaskObj, _library_name_id, shopMaskTex, true);
    LIBNAMEFIND(_library_name_id, shopMaskObj, "mask", _str);
    shopMaskMask = new VBModel(shopMaskObj, _library_name_id, shopMaskTex, true);
    vtShopBack = shopMaskMask->getVBModelByName((char*)"buttonBack");
    
    OBJLOAD(shopObj, "shop.obj", _str);
    TEXLOAD(shopTex, "shop.png", _str);
    shopView = new Shop(shopObj, shopTex);
    //
#endif
    
    LIBNAMEFIND(_library_name_id, packObj, "Menu", _str);
    ui = new VBModel(packObj, _library_name_id, packTex, true);
    ((CCSprite*)top)->addChild((CCSprite*)ui);
    
    btBack = ui->getVBModelByName((char*)"dy_menu_arrow");
    btBack->setIsPlayLoop(false);
    btBack->gotoAndStop(1);
    btBackTouch = NULL;
    
    btGift = ui->getVBModelByName((char*)"dy_menu_gift");
    btGift->setIsPlayLoop(false);
    btGift->gotoAndStop(0);
    btGiftTouch = NULL;
    
    btShop = ui->getVBModelByName((char*)"dy_menu_shop");
    btShop->setIsPlayLoop(false);
    btShop->gotoAndStop(0);
    btShopTouch = NULL;
    
    btFree = ui->getVBModelByName((char*)"dy_menu_freerecipe");
    btFree->setIsPlayLoop(false);
    btFree->gotoAndStop(0);
    btFreeTouch = NULL;
    
    type = SubMenuTypeNone;
    arg0 = -1;
    arg1 = -1;
    currentPage = NULL;
}


void SubMenu::SetMenuType(SubMenuType _type, int _arg0, int _arg1) {
    printf("set sub menu type: %i %i %i\n", _type, _arg0, _arg1);
    if(type != _type || arg0 != _arg0 || arg1 != _arg1) {
        switch (type) {
            case SubMenuTypePackSelect:
                if(type != _type)
                    packView->GoPage(-1, ChangeView, this);
                break;
            case SubMenuTypeStageSelect:
                if(type != _type)
                    stageView->GoPage(-1, ChangeView, this);
                break;
            case SubMenuTypeShop:
#ifndef SHOP_EMPTY
                if(type != _type)
                    shopView->GoPage(-1, ChangeView, this);
#endif
                break;
            default:
                break;
        }
        type = _type;
        arg0 = _arg0;
        arg1 = _arg1;
        if(currentPage == NULL)
            ChangeView(this);
    }
}

SubMenu::~SubMenu() {
    if(currentPage)
        top->removeChild(currentPage->top, false);
    
    delete packView;
    delete stageView;
    
    //shop
    //top->removeChild(shopMaskBg, false);
    //top->removeChild(shopMaskMask, false);
#ifndef SHOP_EMPTY
    delete shopMaskMask;
    delete shopMaskBg;
    VBObjectFile2DFree(&shopObj);
    VBTextureFree(&shopTex);
    VBObjectFile2DFree(&shopMaskObj);
    VBTextureFree(&shopMaskTex);
    
    delete shopView;
#endif
    
    top->removeChild(ui, false);
    delete ui;
    top->removeChild(bg, false);
    delete bg;
    
    VBObjectFile2DFree(&stageObj);
    VBTextureFree(&stageTex);
    VBObjectFile2DFree(&packObj);
    VBTextureFree(&packTex);
    VBObjectFile2DFree(&fontObj);
    VBTextureFree(&fontTex);
    
    //View::~View();
}

void SubMenu::Update(float _deltaTime) {
    if(currentPage)
        currentPage->Update(_deltaTime);
}

void SubMenu::touchBegin(CCTouch* _touch, CCPoint _location) {
    TOUCHBEGINBT(btBackTouch, btBack, _location, _touch, btBack->gotoAndStop(1));
    TOUCHBEGINBT(btGiftTouch, btGift, _location, _touch, btGift->gotoAndStop(1));
    TOUCHBEGINBT(btShopTouch, btShop, _location, _touch, btShop->gotoAndStop(1));
    TOUCHBEGINBT(btFreeTouch, btFree, _location, _touch, btFree->gotoAndStop(1));
    
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btFreeTouch != _touch) {
        currentPage->touchBegin(_touch, _location);
    }
}

void SubMenu::touchMove(CCTouch* _touch, CCPoint _location) {
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btFreeTouch != _touch) {
        currentPage->touchMove(_touch, _location);
    }
}

void ChangeView(void* _ref) {
    SubMenu* pss = (SubMenu*)_ref;
    printf("set sub menu type callback: %i %i %i\n", pss->type, pss->arg0, pss->arg1);
    
    if(pss->currentPage) {
        pss->top->removeChild(pss->currentPage->top, false);
        pss->currentPage = NULL;
    }
    
    switch (pss->type) {
        case SubMenuTypePackSelect:
            pss->packView->Reset();
            pss->packView->GoPage(pss->arg0, NULL, NULL);
            pss->currentPage = pss->packView;
            pss->top->addChild(pss->currentPage->top);
            break;
        case SubMenuTypeStageSelect:
            pss->stageView->SetPack(pss->arg0);
            pss->stageView->GoPage(pss->arg1, NULL, NULL);
            pss->currentPage = pss->stageView;
            pss->top->addChild(pss->currentPage->top);
            break;
        case SubMenuTypeShop:
            
#ifndef SHOP_EMPTY
            pss->shopView->GoPage(pss->arg0, NULL, NULL);
            pss->currentPage = pss->shopView;
            pss->top->addChild(pss->currentPage->top);
#endif
            break;
        default:
            break;
    }
}

void GotoShop(void* _ref) {
    SubMenu *pss = (SubMenu *)_ref;
#ifndef SHOP_EMPTY
    
    pss->top->addChild((CCSprite*)pss->shopMaskBg);
    pss->top->addChild((CCSprite*)pss->shopView->top);
    pss->top->addChild((CCSprite*)pss->shopMaskMask);
    pss->shopView->GoPage(0, NULL, NULL);
    pss->currentPage = pss->shopView;
#endif
}

/*
 * 	페이스북 연동 테스트 콜백 함수
 */
void SubMenuFacebookLogOutComplete(cJSON* _json, void* _reference) {
	LOGD("#@@# SubMenuFacebookLogOutComplete _json: %x, _reference:%x", _json, _reference);
}

void SubMenuFacebookRequestGraphPathComplete(cJSON* _json, void* _reference) {
	LOGD("#@@# SubMenuFacebookRequestGraphPathComplete _json: %x, _reference:%x", _json, _reference);
	char* test = cJSON_Print(_json);
	LOGD("#@@# SubMenuFacebookRequestGraphPathComplete %s", test);
}

void SubMenuFacebookAppRequestComplete(cJSON* _json, void* _reference) {
	LOGD("#@@# SubMenuFacebookAppRequestComplete _json: %x, _reference:%x", _json, _reference);
}

void SubMenuFacebookFeedComplete(cJSON* _json, void* _reference) {
	LOGD("#@@# SubMenuFacebookFeedComplete _json: %x, _reference:%x", _json, _reference);
}

/*
 * 	페이스북 연동 테스트 함수
 */
void facebookLogout(SubMenu* _this) {
	LOGD("#@@# facebook logout!");
	PlatformFacebookLogOut(PlatformCallbackCreate(_this, SubMenuFacebookLogOutComplete));
}

void facebookRequestGraphPath(SubMenu* _this) {
	LOGD("#@@# facebook request graph path!");
	PlatformFacebookRequestGraphPath(PlatformFacebookGraphPathMe, PlatformCallbackCreate(_this, SubMenuFacebookRequestGraphPathComplete));
}

void facebookAppRequest(SubMenu* _this) {
	LOGD("#@@# facebook app request!");
	PlatformFacebookAppRequest("Message~!!", "" , "앱 요청 보낼때 친구 추가 어찌고저찌고 붙음..", PlatformCallbackCreate(_this, SubMenuFacebookAppRequestComplete));
}

void facebookFeed(SubMenu* _this) {
	LOGD("#@@# facebook feed!");
	PlatformFacebookFeed("test name~", "test caption~", "test description~", "test link~", "test picture~", PlatformCallbackCreate(_this, SubMenuFacebookFeedComplete));
}

void SubMenu::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(btBackTouch, btBack, _location, _touch, 
               //ShareDataGetRoot()->PrevPage(1);,
    			facebookLogout(this);,
               btBack->gotoAndStop(0););
    
    TOUCHENDBT(btGiftTouch, btGift, _location, _touch,
    		facebookRequestGraphPath(this);,
    		btGift->gotoAndStop(0));

    TOUCHENDBT(btShopTouch, btShop, _location, _touch, 
               //ShareDataGetRoot()->ChangePage(4, LoadingTypeNone, PopupTypeNone, RootPageTypeSubMenu, SubMenuTypeShop);
    		facebookAppRequest(this);
               , btShop->gotoAndStop(0));
//    TOUCHENDBT(btShopTouch, btShop, _location, _touch, ShareDataGetRoot()->OpenPopup(rand() % 2 + 1, rand() % 4, rand() % 99999), btShop->gotoAndStop(0));
    
    TOUCHENDBT(btFreeTouch, btFree, _location, _touch,
    		facebookFeed(this);,
    		btFree->gotoAndStop(0));
}

void SubMenu::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btFreeTouch != _touch) {
        currentPage->touchEnd(_touch, _location);
    }
}

void SubMenu::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btFreeTouch != _touch) {
        currentPage->touchCancel(_touch, _location);
    }
}
