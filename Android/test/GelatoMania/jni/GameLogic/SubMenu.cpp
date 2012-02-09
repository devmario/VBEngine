#include "SubMenu.h"
#include "ShareData.h"

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
    OBJLOAD(objRootUI, "root_ui.obj", _str);
    TEXLOAD(texRootUI, "root_ui.png", _str);
    
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
    ui = new VBModel();
    ((CCSprite*)top)->addChild((CCSprite*)ui);
    
    
    LIBNAMEFIND(_library_name_id, objRootUI, "subUI", _str);
    modelRootUI = new VBModel(objRootUI, _library_name_id, texRootUI, true);
    modelRootUI->stop();
    top->addChild(modelRootUI);
    
    btBack = modelRootUI->getVBModelByInstanceName("btBack");
    btBack->gotoAndStop(0);
    btBackTouch = NULL;
    
    VBModel* shopM = modelRootUI->getVBModelByInstanceName("shop");
    frameCTR_shop = new FrameTweenController(shopM);
    
    VBModel* socialM = modelRootUI->getVBModelByInstanceName("social");
    VBModel* socialBT = socialM->getVBModelByInstanceName("btSocial");
    VBModel* socialBTTop = socialBT->getVBModelByInstanceName("btIn");
    frameCTR_social = new FrameTweenController(socialBTTop);
    
    touchArch = touchRank = touchFB = touchFriend = NULL;
    
    btArch = socialBTTop->getVBModelByInstanceName("bt1");
    btArch->stop();
    btRank = socialBTTop->getVBModelByInstanceName("bt2");
    btRank->stop();
    btFB = socialBTTop->getVBModelByInstanceName("bt3");
    btFB->stop();
    btFriend = socialBTTop->getVBModelByInstanceName("bt4");
    btFriend->stop();
    
    btSocial = socialBT->getVBModelByInstanceName("bt");
    btSocial->gotoAndStop(0);
    btSocialTouch = NULL;
    isOpenSocial = false;
    
    btGift = shopM->getVBModelByInstanceName("gift");
    btGift->gotoAndStop(0);
    btGiftTouch = NULL;
    
    btShop = shopM->getVBModelByInstanceName("btShop");
    btShop->gotoAndStop(0);
    btShopTouch = NULL;
    
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
    delete frameCTR_social;
    delete frameCTR_shop;
    
    if(currentPage)
        ui->removeChild(currentPage->top, false);
    
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
    
    top->removeChild(modelRootUI, false);
    delete modelRootUI;
    VBObjectFile2DFree(&objRootUI);
    VBTextureFree(&texRootUI);
    
    //View::~View();
}

void SubMenu::Update(float _deltaTime) {
    if(currentPage)
        currentPage->Update(_deltaTime);
    frameCTR_shop->Update(_deltaTime);
    frameCTR_social->Update(_deltaTime);
}

void SubMenu::touchBegin(CCTouch* _touch, CCPoint _location) {
    TOUCHBEGINBT(btBackTouch, btBack, _location, _touch, btBack->gotoAndStop(1));
    TOUCHBEGINBT(btGiftTouch, btGift, _location, _touch, btGift->gotoAndStop(1));
    TOUCHBEGINBT(btShopTouch, btShop, _location, _touch, btShop->gotoAndStop(1));
    TOUCHBEGINBT(btSocialTouch, btSocial, _location, _touch, btSocial->gotoAndStop(1));
//    TOUCHBEGINBT(btFreeTouch, btFree, _location, _touch, btFree->gotoAndStop(1));
    
    
    if(!frameCTR_social->getIsRun() && isOpenSocial) {
        TOUCHBEGINBT(touchArch, btArch, _location, _touch, btArch->gotoAndStop(1););
        if(touchArch)
            return;
        TOUCHBEGINBT(touchRank, btRank, _location, _touch, btRank->gotoAndStop(1););
        if(touchRank)
            return;
        TOUCHBEGINBT(touchFB, btFB, _location, _touch, btFB->gotoAndStop(1););
        if(touchFB)
            return;
        TOUCHBEGINBT(touchFriend, btFriend, _location, _touch, btFriend->gotoAndStop(1););
        if(touchFriend)
            return;
    }
    
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btSocialTouch != _touch) {
        currentPage->touchBegin(_touch, _location);
    }
}

void SubMenu::touchMove(CCTouch* _touch, CCPoint _location) {
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btSocialTouch != _touch &&
       touchArch != _touch && touchRank != _touch && touchFB != _touch && touchFriend != _touch) {
        currentPage->touchMove(_touch, _location);
    }
}

void ChangeView(void* _ref) {
    SubMenu* pss = (SubMenu*)_ref;
    printf("set sub menu type callback: %i %i %i\n", pss->type, pss->arg0, pss->arg1);
    
    if(pss->currentPage) {
        pss->ui->removeChild(pss->currentPage->top, false);
        pss->currentPage = NULL;
    }
    
    switch (pss->type) {
        case SubMenuTypePackSelect:
            pss->packView->Reset();
            pss->packView->GoPage(pss->arg0, NULL, NULL);
            pss->currentPage = pss->packView;
            pss->ui->addChild(pss->currentPage->top,0);
            break;
        case SubMenuTypeStageSelect:
            pss->stageView->SetPack(pss->arg0);
            pss->stageView->GoPage(pss->arg1, NULL, NULL);
            pss->currentPage = pss->stageView;
            pss->ui->addChild(pss->currentPage->top,0);
            break;
        case SubMenuTypeShop:
            
#ifndef SHOP_EMPTY
            pss->shopView->GoPage(pss->arg0, NULL, NULL);
            pss->currentPage = pss->shopView;
            pss->ui->addChild(pss->currentPage->top,0);
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

void SubMenu::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(btBackTouch, btBack, _location, _touch, 
               ShareDataGetRoot()->PrevPage(1);
               if(currentPage == shopView) {
                   frameCTR_shop->playTo(0, 0.7, 0, EXPO, EASE_OUT, NULL, NULL);
               },
               btBack->gotoAndStop(0););
    TOUCHENDBT(btGiftTouch, btGift, _location, _touch, , btGift->gotoAndStop(0));
    
    TOUCHENDBT(btShopTouch, btShop, _location, _touch, 
               ShareDataGetRoot()->ChangePage(4, LoadingTypeNone, PopupTypeNone, RootPageTypeSubMenu, SubMenuTypeShop);
               frameCTR_shop->playTo(29, 0.7, 0, EXPO, EASE_OUT, NULL, NULL);
               , btShop->gotoAndStop(0));
    
    TOUCHENDBT(btSocialTouch, btSocial, _location, _touch,
               isOpenSocial = !isOpenSocial;
               frameCTR_social->playTo(isOpenSocial ? 29 : 0, 1.0, 0, EXPO, EASE_OUT, NULL, NULL);
               , btSocial->gotoAndStop(0));
    
    if(!frameCTR_social->getIsRun() && isOpenSocial) {
        TOUCHENDBT(touchArch, btArch, _location, _touch, ,btArch->gotoAndStop(0););
        TOUCHENDBT(touchRank, btRank, _location, _touch, ,btRank->gotoAndStop(0););
        TOUCHENDBT(touchFB, btFB, _location, _touch, ,btFB->gotoAndStop(0););
        TOUCHENDBT(touchFriend, btFriend, _location, _touch, ,btFriend->gotoAndStop(0););
    } else {
        touchArch = NULL;
        touchRank = NULL;
        touchFB = NULL;
        touchFriend = NULL;
        btArch->gotoAndStop(0);
        btRank->gotoAndStop(0);
        btFB->gotoAndStop(0);
        btFriend->gotoAndStop(0);
    }
//    TOUCHENDBT(btShopTouch, btShop, _location, _touch, ShareDataGetRoot()->OpenPopup(rand() % 2 + 1, rand() % 4, rand() % 99999), btShop->gotoAndStop(0));
    
    //TOUCHENDBT(btFreeTouch, btFree, _location, _touch, , btFree->gotoAndStop(0));
}

void SubMenu::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btSocialTouch != _touch &&
       touchArch != _touch && touchRank != _touch && touchFB != _touch && touchFriend != _touch) {
        currentPage->touchEnd(_touch, _location);
    }
}

void SubMenu::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
    if(btBackTouch != _touch && btGiftTouch != _touch && btShopTouch != _touch && btSocialTouch != _touch &&
       touchArch != _touch && touchRank != _touch && touchFB != _touch && touchFriend != _touch) {
        currentPage->touchCancel(_touch, _location);
    }
}