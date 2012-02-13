#include "SubMenu.h"
#include "ShareData.h"

void ChangeView(void* _ref) {
    SubMenu* _sub_menu = (SubMenu*)_ref;
    _sub_menu->is_need_new_page = true;
}

SubMenu::SubMenu() {
    is_need_new_page = false;
    isSetLayout = false;
    is_need_pop_root_history = false;
    
    VBString* _str = NULL;
    OBJLOAD(objRootUI, "root_ui.obj", _str);
    TEXLOAD(texRootUI, "root_ui.png", _str);
    OBJLOAD(objSubMenu, "sub_menu.obj", _str);
    TEXLOAD(texSubMenu, "sub_menu.png", _str);
    
    OBJLOAD(objPageThumbs, "page_thumbs.obj", _str);
    TEXLOAD(texPageThumbs, "page_thumbs.png", _str);
    
    VBObjectFile2DLibraryNameID* _library_name_id = NULL;
    LIBNAMEFIND(_library_name_id, objSubMenu, "bg", _str);
    bg = new VBModel(objSubMenu, _library_name_id, texSubMenu, true);
    ((CCSprite*)top)->addChild((CCSprite*)bg);
    bg->stop();
    
    bgT = bg->getVBModelByInstanceName("T");
    bgB = bg->getVBModelByInstanceName("B");
    
    packView = NULL;
    stageView = NULL;
    shopView = NULL;
    
    ui = new VBModel();
    ((CCSprite*)top)->addChild((CCSprite*)ui);
    
    
    LIBNAMEFIND(_library_name_id, objRootUI, "subUI", _str);
    modelRootUI = new VBModel(objRootUI, _library_name_id, texRootUI, true);
    modelRootUI->stop();
    top->addChild(modelRootUI);
    
    btBack = modelRootUI->getVBModelByInstanceName("btBack");
    btBack->gotoAndStop(0);
    btBackTouch = NULL;
    
    shopM = modelRootUI->getVBModelByInstanceName("shop");
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
    next_type = SubMenuTypeNone;
    next_arg0 = -1;
    next_arg1 = -1;
    currentPage = NULL;
}

SubMenu::~SubMenu() {
    delete frameCTR_social;
    delete frameCTR_shop;
    
    if(currentPage)
        ui->removeChild(currentPage->top, false);
    
    if(packView)
        delete packView;
    if(stageView)
        delete stageView;
    if(shopView)
        delete shopView;
    
    top->removeChild(ui, false);
    delete ui;
    top->removeChild(bg, false);
    delete bg;
    
    VBObjectFile2DFree(&objPageThumbs);
    VBTextureFree(&texPageThumbs);
    
    top->removeChild(modelRootUI, false);
    delete modelRootUI;
    VBObjectFile2DFree(&objRootUI);
    VBTextureFree(&texRootUI);
    VBObjectFile2DFree(&objSubMenu);
    VBTextureFree(&texSubMenu);
}


void SubMenu::SetMenuType(SubMenuType _type, int _arg0, int _arg1) {
    SubMenuType pre_type = type;
    if(type != _type) {
        if(currentPage) {
            ui->removeChild(currentPage->top, false);
            currentPage = NULL;
            switch (type) {
                case SubMenuTypePackSelect:
                    delete packView;
                    packView = NULL;
                    break;
                case SubMenuTypeStageSelect:
                    delete stageView;
                    stageView = NULL;
                    break;
                case SubMenuTypeShop:
                    delete shopView;
                    shopView = NULL;
                    break;
                default:
                    break;
            }
        }
        
        type = _type;
        
        switch (type) {
            case SubMenuTypePackSelect:
                packView = new PackSelect(objPageThumbs, texPageThumbs, ShareDataGetPackLength(), this);
                currentPage = packView;
                ui->addChild(currentPage->top,0);
                break;
            case SubMenuTypeStageSelect:
                stageView = new StageSelect(objPageThumbs, texPageThumbs, 2);
                currentPage = stageView;
                ui->addChild(currentPage->top,0);
                break;
            case SubMenuTypeShop:
                shopView = new Shop(_arg0);
                currentPage = shopView;
                ui->addChild(currentPage->top,0);
                break;
            default:
                break;
        }
        
        float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
        float x = CCDirector::sharedDirector()->getDisplaySizeInPixels().width / scale;
        currentPage->top->setPosition(CCPointMake(x * 0.5, 0));
        currentPage->top->setPosition(CCPointMake(x * 0.5, 0));
    }
    
    if(pre_type != _type || _arg0 != arg0 || _arg1 != arg1) {
        arg0 = _arg0;
        arg1 = _arg1;
        
        switch (_type) {
            case SubMenuTypePackSelect:
                packView->GoPage(_arg0, NULL, NULL);
                break;
            case SubMenuTypeStageSelect:
                stageView->SetPack(_arg0);
                stageView->GoPage(_arg1, NULL, NULL);
                break;
            case SubMenuTypeShop:
                shopView->SetTap(_arg0);
                shopView->GoPage(0, NULL, NULL);
                break;
            default:
                break;
        }
    }
    
    if(is_need_pop_root_history) {
        ShareDataGetRoot()->PopHistory(ShareDataGetRoot()->vecHistory->len - 1);
        ShareDataGetRoot()->PopHistory(ShareDataGetRoot()->vecHistory->len - 1);
        is_need_pop_root_history = false;
    }
}

void SubMenu::ChangePage(SubMenuType _type, int _arg0, int _arg1) {
    next_type = _type;
    next_arg0 = _arg0;
    next_arg1 = _arg1;
    
    if(type != _type) {
        if(currentPage) {
            switch (type) {
                case SubMenuTypePackSelect:
                    packView->GoPage(-1, ChangeView, this);
                    break;
                case SubMenuTypeStageSelect:
                    stageView->GoPage(-1, ChangeView, this);
                    break;
                case SubMenuTypeShop:
                    shopView->GoPage(-1, ChangeView, this);
                    break;
                default:
                    break;
            }
        } else {
            ChangeView(this);
        }
    } else if(arg0 != _arg0 || arg1 != _arg1) {
        ShareDataGetRoot()->ChangePage(6, LoadingTypeNone, PopupTypeNone, RootPageTypeSubMenu, next_type, next_arg0, next_arg1);
    }
}

void SubMenu::BackPage() {
    history* pre = (history*)ShareDataGetRoot()->vecHistory->data[ShareDataGetRoot()->vecHistory->len - 2];
    int* args = pre->args;
    
    //Popup관련 인자 통과
    int i = 0;
    if(args[i] == PopupTypeClear)
        i += 3;
    else
        i++;
    
    if(args[i] != RootPageTypeSubMenu) {
        ShareDataGetRoot()->PrevPage(1);
    } else {
        i++;
        if(args[i] != type) {
            SubMenuType _type = (SubMenuType)(args[i]);
            i++;
            int _arg0 = 0;
            if(i < pre->count)
                _arg0 = args[i];
            i++;
            int _arg1 = 0;
            if(i < pre->count)
                _arg1 = args[i];
            is_need_pop_root_history = true;
            ChangePage(_type, _arg0, _arg1);
        }
    }
}

void SubMenu::Update(float _deltaTime) {
    if(!isSetLayout) {
        float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
        float x = CCDirector::sharedDirector()->getDisplaySizeInPixels().width / scale;
        float shiftX = -(480 - x);
        shopM->setPosition(CCPointMake(shopM->getPosition().x + shiftX, shopM->getPosition().y));
        bg->setPosition(CCPointMake(x * 0.5, 0));
        
        float cur_aspec = (CCDirector::sharedDirector()->getDisplaySizeInPixels().width / CCDirector::sharedDirector()->getDisplaySizeInPixels().height);
        float origin_aspec = 480.0/320.0;
        if(origin_aspec < cur_aspec) {
            bgT->setScale(bgT->getScale() / (origin_aspec / cur_aspec));
            bgB->setScale(bgB->getScale() / (origin_aspec / cur_aspec));
        }
        isSetLayout = true;
    }
    
    if(currentPage)
        currentPage->Update(_deltaTime);
    frameCTR_shop->Update(_deltaTime);
    frameCTR_social->Update(_deltaTime);
    
    if(is_need_new_page) {
        ShareDataGetRoot()->ChangePage(6, LoadingTypeSmall, PopupTypeNone, RootPageTypeSubMenu, next_type, next_arg0, next_arg1);
        is_need_new_page = false;
    }
}

void SubMenu::touchBegin(CCTouch* _touch, CCPoint _location) {
    TOUCHBEGINBT(btBackTouch, btBack, _location, _touch, btBack->gotoAndStop(1));
    TOUCHBEGINBT(btGiftTouch, btGift, _location, _touch, btGift->gotoAndStop(1));
    TOUCHBEGINBT(btShopTouch, btShop, _location, _touch, btShop->gotoAndStop(1));
    TOUCHBEGINBT(btSocialTouch, btSocial, _location, _touch, btSocial->gotoAndStop(1));
    
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

void SubMenu::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(btBackTouch, btBack, _location, _touch, 
               BackPage();
               if(currentPage == shopView) {
                   frameCTR_shop->playTo(0, 0.7, 0, EXPO, EASE_OUT, NULL, NULL);
               },
               btBack->gotoAndStop(0););
    TOUCHENDBT(btGiftTouch, btGift, _location, _touch, , btGift->gotoAndStop(0));
    
    TOUCHENDBT(btShopTouch, btShop, _location, _touch, 
               ChangePage(SubMenuTypeShop, 0, 0);
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