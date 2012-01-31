#include "MainMenu.h"
#include "VBEngine.h"
#include "ShareData.h"
#include "SubMenu.h"
#include "vbHTTP.h"

MainMenu::MainMenu() {
    //View::View();
    
    touchPlayBT = NULL;
    touchRank = NULL;
    touchArch = NULL;
    touchInfo = NULL;
    
    //타이틀 화면
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "titleintro.obj");
    titleintroObj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
    VBStringFree(&_str);
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "titleintro.png");
    titleintroTex = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    
    _str = VBStringInitWithCString(VBStringAlloc(), "_dynamic/dyMom_title");
    VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByName(titleintroObj, _str);
    VBStringFree(&_str);
    
    titlebg = new VBModel(titleintroObj, _library_name_id, titleintroTex, true);
    ((CCSprite*)top)->addChild((CCSprite*)titlebg);
    
    //타이틀위에놓을 UI
    //로딩이 다른곳이랑 공유되기 때문에 ShareData로 접근
    VBObjectFile2D* _objFile = ShareDataGetTitleObjFile();
    VBTexture* _texFile = ShareDataGetTitleTexture();
    
    _str = VBStringInitWithCString(VBStringAlloc(), "_dynamic/dyMom_title");
    _library_name_id = VBObjectFile2DGetLibraryNameIDByName(_objFile, _str);
    VBStringFree(&_str);
    
    titleui = new VBModel(_objFile, _library_name_id, _texFile, true);
    ((CCSprite*)top)->addChild((CCSprite*)titleui);
    
    playBT = titleui->getVBModelByName((char*)"_dynamic/dy_title_btnPlay");
    playBT->setIsPlayLoop(false);
    playBT->gotoAndStop(0);
    
    rankBT = titleui->getVBModelByName((char*)"_dynamic/dy_title_btnLeaderboard");
    rankBT->setIsPlayLoop(false);
    rankBT->gotoAndStop(0);
    
    archBT = titleui->getVBModelByName((char*)"_dynamic/dy_title_btnAchivement");
    archBT->setIsPlayLoop(false);
    archBT->gotoAndStop(0);
    
    infoBT = titleui->getVBModelByName((char*)"_dynamic/dy_title_btnInfo");
    infoBT->setIsPlayLoop(false);
    infoBT->gotoAndStop(0);
}

MainMenu::~MainMenu() {
    top->removeChild(titlebg, false);
    delete titlebg;
    top->removeChild(titleui, false);
    delete titleui;
    VBObjectFile2DFree(&titleintroObj);
    VBTextureFree(&titleintroTex);
    //View::~View();
}

void MainMenu::Update(float _deltaTime) {
    if(touchPlayBT && (playBT->cur_frame + _deltaTime) > 6)
        playBT->gotoAndStop(6);
}

void MainMenu::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(touchPlayBT == NULL) {
        if(titleui->getVBModelByName((char*)"image/title_btnPlay")->checkCollisionWithButton(_location)) {
            playBT->gotoAndPlay(0);
            touchPlayBT = _touch;
        }
    }
    
    TOUCHBEGINBT(touchRank, rankBT, _location, _touch, rankBT->gotoAndStop(1));
    TOUCHBEGINBT(touchArch, archBT, _location, _touch, archBT->gotoAndStop(1));
    TOUCHBEGINBT(touchInfo, infoBT, _location, _touch, infoBT->gotoAndStop(1));
}

void MainMenu::touchMove(CCTouch* _touch, CCPoint _location) {
    
}

void ErrorHTTP(unsigned char _code);
void SuccessHTTP(void);

void ErrorHTTP(unsigned char _code) {
	LOGD("ErrorHTTP");
    printf("\n\nErrorHTTP\n");
}

void SuccessHTTP(void) {
	LOGD("SuccessHTTP");
    printf("\n\nSuccessHTTP\n");
}

void MainMenu::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(touchPlayBT == _touch) {
        playBT->gotoAndPlay(6);
        touchPlayBT = NULL;
        ShareDataGetRoot()->ChangePage(5, LoadingTypeFull, PopupTypeNone, RootPageTypeSubMenu, SubMenuTypePackSelect, 0);
        VBHTTP* http = VBHTTPCreateByJS("user.js", ErrorHTTP, SuccessHTTP);
        while(!http->complete) {
        }
        LOGD("HTTP RESPONSE : %s", http->response);
        VBHTTPRelease(&http);
    }
    
    TOUCHENDBT(touchRank, rankBT, _location, _touch, ,rankBT->gotoAndStop(0));
    TOUCHENDBT(touchArch, archBT, _location, _touch, ,archBT->gotoAndStop(0));
    TOUCHENDBT(touchInfo, infoBT, _location, _touch, ,infoBT->gotoAndStop(0));
}

void MainMenu::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}

void MainMenu::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}

