#include "MainMenu.h"
#include "VBEngine.h"
#include "ShareData.h"
#include "SubMenu.h"
#include "vbHTTP.h"
#include "PlatformFunctions.h"

MainMenu::MainMenu() {
    //View::View();
    
    touchSocial = touchSetting = touchMobage = touchPlayBT = NULL;
    touchArch = touchRank = touchFB = touchFriend = NULL;
    
    //타이틀 화면
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "title.obj");
    titleintroObj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
    VBStringFree(&_str);
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "title.png");
    titleintroTex = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    
    _str = VBStringInitWithCString(VBStringAlloc(), "_dynamic/dyMom_title");
    VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByName(titleintroObj, _str);
    VBStringFree(&_str);
    
    titlebg = new VBModel(titleintroObj, _library_name_id, titleintroTex, true);
    ((CCSprite*)top)->addChild((CCSprite*)titlebg);
    
    OBJLOAD(objTitleUi, "title_ui.obj", _str);
    TEXLOAD(texTitleUI, "title_ui.png", _str);
    
    LIBNAMEFIND(_library_name_id, objTitleUi, "ui", _str);
    
    titleui = new VBModel(objTitleUi, _library_name_id, texTitleUI, true);
    ((CCSprite*)top)->addChild((CCSprite*)titleui);
    
    playBT = titleui->getVBModelByInstanceName("playBT");
    playBT->setIsPlayLoop(false);
    playBT->gotoAndStop(0);
    
    OBJLOAD(objBT, "root_ui.obj", _str);
    TEXLOAD(texBT, "root_ui.png", _str);
    
    LIBNAMEFIND(_library_name_id, objBT, "mainUI", _str);
    modelBTUI = new VBModel(objBT, _library_name_id, texBT, true);
    top->addChild(modelBTUI);
    modelBTUI->setIsPlayLoop(false);
    modelBTUI->stop();
    
    openSocial = false;
    VBModel* socialBTTop = modelBTUI->getVBModelByInstanceName("btSocial");
    VBModel* socialIn = socialBTTop->getVBModelByInstanceName("btIn");
    frameModel = new FrameTweenController(socialIn);
    socialBT = socialBTTop->getVBModelByInstanceName("bt");
    settingBT = modelBTUI->getVBModelByInstanceName("btOption");
    settingBT->stop();
    mobageBT = modelBTUI->getVBModelByInstanceName("btMobage");
    mobageBT->stop();
    
    btArch = socialIn->getVBModelByInstanceName("bt1");
    btArch->stop();
    btRank = socialIn->getVBModelByInstanceName("bt2");
    btRank->stop();
    btFB = socialIn->getVBModelByInstanceName("bt3");
    btFB->stop();
    btFriend = socialIn->getVBModelByInstanceName("bt4");
    btFriend->stop();
}

MainMenu::~MainMenu() {
    delete frameModel;
    top->removeChild(modelBTUI, false);
    delete modelBTUI;
    top->removeChild(titlebg, false);
    delete titlebg;
    top->removeChild(titleui, false);
    delete titleui;
    VBObjectFile2DFree(&titleintroObj);
    VBTextureFree(&titleintroTex);
    VBObjectFile2DFree(&objTitleUi);
    VBTextureFree(&texTitleUI);
    VBObjectFile2DFree(&objBT);
    VBTextureFree(&texBT);
    //View::~View();
}

void MainMenu::Update(float _deltaTime) {
    frameModel->Update(_deltaTime);
}

void MainMenu::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(touchPlayBT == NULL) {
        if(playBT->checkCollisionWithButton(_location)) {
            playBT->gotoAndStop(1);
            touchPlayBT = _touch;
        }
    }
    
    TOUCHBEGINBT(touchSocial, socialBT, _location, _touch, socialBT->gotoAndStop(1););
    TOUCHBEGINBT(touchSetting, settingBT, _location, _touch, settingBT->gotoAndStop(1););
    TOUCHBEGINBT(touchMobage, mobageBT, _location, _touch, mobageBT->gotoAndStop(1););
    
    if(!frameModel->getIsRun() && openSocial) {
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
    }
}

void MainMenu::touchMove(CCTouch* _touch, CCPoint _location) {
    
}

void MainMenu::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(touchPlayBT == _touch) {
        if(playBT->checkCollisionWithButton(_location)) {
            ShareDataGetRoot()->ChangePage(5, LoadingTypeFull, PopupTypeNone, RootPageTypeSubMenu, SubMenuTypePackSelect, 0);
        }
        playBT->gotoAndStop(0);
        touchPlayBT = NULL;
    }
    
    TOUCHENDBT(touchSocial, socialBT, _location, _touch,
               openSocial = !openSocial;
               frameModel->playTo((openSocial ? 29.0 : 0.0), 1.0, 0.0, EXPO, EASE_OUT, NULL, NULL);,
               socialBT->gotoAndStop(0););
    TOUCHENDBT(touchSetting, settingBT, _location, _touch, ,settingBT->gotoAndStop(0););
    TOUCHENDBT(touchMobage, mobageBT, _location, _touch, ,mobageBT->gotoAndStop(0););
    
    if(!frameModel->getIsRun() && openSocial) {
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

void MainMenu::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}

void MainMenu::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}


