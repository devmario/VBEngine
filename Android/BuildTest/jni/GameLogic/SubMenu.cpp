#include "SubMenu.h"
#include "ShareData.h"

void ChangeView(void* _ref);

SubMenu::SubMenu(int _packID, int _stageID) {
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
    
    packView = new PackSelect(packObj, packTex, fontObj, fontTex, ShareDataGetPackLength());
    ((CCSprite*)top)->addChild((CCSprite*)packView->top);
    packView->pss = this;
    packView->selectedFunc = ChangeView;
    
    stageView = new StageSelect(stageObj, stageTex, fontObj, fontTex, 2);
    ((CCSprite*)top)->addChild((CCSprite*)stageView->top);
    
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
    
    if(_stageID >= 0) {
        stageView->SetPack(_packID);
        stageView->GoPage(_stageID, NULL, NULL);
        currentPage = (Pages*)stageView;
    } else {
        packView->GoPage(_packID, NULL, NULL);
        currentPage = (Pages*)packView;
    }
}

SubMenu::~SubMenu() {
    top->removeChild(packView->top, false);
    delete packView;
    top->removeChild(stageView->top, false);
    delete stageView;
    
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
    
    //shop
    top->removeChild(shopMaskBg, false);
    top->removeChild(shopMaskMask, false);
    delete shopMaskMask;
    delete shopMaskBg;
    VBObjectFile2DFree(&shopObj);
    VBTextureFree(&shopTex);
    VBObjectFile2DFree(&shopMaskObj);
    VBTextureFree(&shopMaskTex);
    top->removeChild(shopView->top, false);
    delete shopView;
    
    //View::~View();
}

void SubMenu::Update(float _deltaTime) {
    packView->Update(_deltaTime);
    stageView->Update(_deltaTime);
    shopView->Update(_deltaTime);
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
    if(pss->currentPage == pss->packView) {
        int _stagePage = 0;
        for(int i = 0; i < ShareDataGetStageLength(pss->packView->preIdx); i++) {
            if(ShareDataGetStageLockAt(pss->packView->preIdx, i) == false) {
                _stagePage = floorf(i / 18.0);
            } else {
                break;
            }
        }
        pss->stageView->GoPage(_stagePage, NULL, NULL);
        pss->stageView->SetPack(pss->packView->preIdx);
        pss->currentPage = pss->stageView;
    } else if(pss->currentPage == pss->stageView) {
        pss->packView->GoPage(pss->stageView->packIdx, NULL, NULL);
        pss->packView->Reset();
        pss->currentPage = pss->packView;
    } else if(pss->currentPage == pss->shopView) {
        pss->top->removeChild(pss->shopMaskMask, false);
        pss->top->removeChild(pss->shopMaskBg, false);
        pss->top->removeChild(pss->shopView->top, false);
        pss->packView->GoPage(1, NULL, NULL);
        pss->packView->Reset();
        pss->currentPage = pss->packView;
    }
}

void GotoShop(void* _ref) {
    SubMenu *pss = (SubMenu *)_ref;
    
    pss->top->addChild((CCSprite*)pss->shopMaskBg);
    pss->top->addChild((CCSprite*)pss->shopView->top);
    pss->top->addChild((CCSprite*)pss->shopMaskMask);
    pss->shopView->GoPage(0, NULL, NULL);
    pss->currentPage = pss->shopView;
}

void SubMenu::packSelect(int _pack) {
    currentPage->GoPage(-1, ChangeView, this);
}

void SubMenu::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(btBackTouch, btBack, _location, _touch, 
               if(currentPage == packView) {
                   currentPage->GoPage(-1, ChangeView, this);
                   ShareDataGetRoot()->ShowLoading(MainMenuPage);
               } else if(currentPage == stageView) {
                   currentPage->GoPage(-1, ChangeView, this);
               } else if(currentPage == shopView) {
                   currentPage->GoPage(-1, ChangeView, this);
               },
               btBack->gotoAndStop(0););
    TOUCHENDBT(btGiftTouch, btGift, _location, _touch, ShareDataGetRoot()->OpenPopup(rand() % 2, rand() % 4, rand() % 99999), btGift->gotoAndStop(0));
    
    TOUCHENDBT(btShopTouch, btShop, _location, _touch, currentPage->GoPage(-1, GotoShop, this), btShop->gotoAndStop(0));
//    TOUCHENDBT(btShopTouch, btShop, _location, _touch, ShareDataGetRoot()->OpenPopup(rand() % 2, rand() % 4, rand() % 99999), btShop->gotoAndStop(0));
    
    TOUCHENDBT(btFreeTouch, btFree, _location, _touch, ShareDataGetRoot()->OpenPopup(rand() % 2, rand() % 4, rand() % 99999), btFree->gotoAndStop(0));
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