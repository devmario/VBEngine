#include "Root.h"
#include "VBEngine.h"
#include "ShareData.h"
#include "MainMenu.h"
#include "SubMenu.h"
#include "GameMain.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "PlatformFunctions.h"
#include "User.h"

bool IsEqualHistory(history* _h0, history* _h1) {
    if(_h0 == NULL || _h1 == NULL)
        return false;
    if(_h0->count != _h1->count)
        return false;
    for(int i = 0; i < _h0->count; i++) {
        if(_h0->args[i] != _h1->args[i])
            return false;
    }
    return true;
}

using namespace cocos2d;

void PopupClose(void* _ref) {
    Root* _root = (Root*)_ref;
    _root->popupClear = true;
}

void Root::OpenPopupAlloc(int _type, int _star, int _score) {
    popupType = _type;
    switch (_type) {
        case PopupTypePause:
            popup = new Popup(NULL, NULL, top);
            break;
        case PopupTypeClear:
            popup = new PopupClear(NULL, NULL, top, _star, _score, NULL, NULL);
            break;
    }
    popup->Open(PopupClose, this);
    popupClear = false;
    
}

void Root::OpenPopup(int _type, int _star, int _score) {
    OpenPopupAlloc(_type, _star, _score);
    
    history* _h = GetLastHistory();
    
    history _newH;
    _newH.count = _h->count + (_type == PopupTypeClear ? 2 : 0);
    
    _newH.args = (int*)malloc(sizeof(int) * _newH.count);
    
    int _idx = 0;
    int _pidx = 0;
    _newH.args[_idx] = _type;
    _idx++;
    _pidx++;
    
    if(_type == PopupTypeClear) {
        _newH.args[_idx] = _star;
        _newH.args[_idx + 1] = _score;
        _idx += 2;
    }
    
    for(; _pidx < _h->count; _pidx++) {
        _newH.args[_idx] = _h->args[_pidx];
        _idx++;
    }
    
    PushHistory(&_newH);
    
    free(_newH.args);
    
//    printf("history len:%i %i %i %i\n", vecHistory->len, _idx, _pidx, _newH.count);
}

void Root::ClosePopup() {
    popup->Close();
    PopHistory(vecHistory->len - 1);
    printf("history len:%i\n", vecHistory->len);
}

void Root::SelectUserCallback(cJSON* user) {
    if(selectUser) {
        User::localUser()->SetJSON(user);
        selectUser->Hide();
    }
}

void Root::SelectUserNeedDelete() {
    if(selectUser) {
        delete selectUser;
        selectUser = NULL;
    }
}

void Root::GameCenterIDCheckNeedSelect(bool success,
                                       SocialError error, 
                                       cJSON* users, cJSON* gameCenterInfo) {
    if(selectUser == NULL) {
        selectUser = new SelectUser(users, top, this, "gameCenterID", gameCenterInfo);
    } else {
        selectUser->SetUsers(users, "gameCenterID", gameCenterInfo);
    }
    selectUser->Show();
}

Root::Root() {
    gameMainHistory = GameMainHistory();
    gameMainHistory.historyEnable = false;
    
    selectUser = NULL;
    /* facebook off
    PlatformGameCenterLogin(RootGameCenterLoginComplete);
    
    PlatformFacebookLogin(RootFacebookLoginComplete);
    */
    
    backHistory = false;
    //CCLayer();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    loading = NULL;
    loadFlag = 0;
    view = NULL;
    top = NULL;
    
    //    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    //    NSString* documentDirectory = [paths objectAtIndex:0];
    
    // instead of nsdocumentdirectory
    // get resource, document path
#ifdef __ANDROID__
    // VBEngineStart("/mnt/sdcard/GelatoMania/resource", "/mnt/sdcard/GelatoMania/document", 800, 480, 480, 320);
    VBEngineStart("/data/data/com.vanillabreeze.gelatomania/files/resource", "/data/data/com.vanillabreeze.gelatomania/files/document", 800, 480, 480, 320);
#else
    const char* appName = "GelatoMania.app";
    int appNameLen = strlen(appName);
    
    const char* tempPath = CCFileUtils::fullPathFromRelativePath("Info.plist");
    int tempLen = strlen(tempPath);
    
    //get resource path
    char* resourcePath = (char*)malloc(sizeof(char)*(tempLen-10));
    strncpy(resourcePath, tempPath, tempLen-11);
    resourcePath[tempLen-11] = '\0';
    int resourceLen = strlen(resourcePath);
    //    cout << resourcePath << '\n';
    
    //get document path
    char* documentsPath = (char*)malloc(sizeof(char)*(resourceLen-appNameLen+9));
    strncpy(documentsPath, resourcePath, resourceLen-appNameLen);
    documentsPath[resourceLen-appNameLen] = '\0';
    strcat(documentsPath, "Documents");
    //    cout << documentsPath << '\n';
    
    VBEngineStart(resourcePath, documentsPath, CCDirector::sharedDirector()->getDisplaySizeInPixels().width, CCDirector::sharedDirector()->getDisplaySizeInPixels().height, 480, 320);
    
    free(resourcePath);
    free(documentsPath);
#endif
    
    gettimeofday(&curTime, NULL);
    
    top = new VBModel();
	top->setScale(CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320);

	this->addChild((CCLayer*)top);

	((CCSprite*)top)->setPosition(ccp(0, CCDirector::sharedDirector()->getDisplaySizeInPixels().height));

	//top->setScaleY(768.0/320.0);
    //top->setScaleX(1024.0/480.0);
    
    this->setIsTouchEnabled(true);
    this->schedule(schedule_selector(Root::Update), 1.f/GAME_FRAME);
    
    vecHistory = VBArrayVectorInit(VBArrayVectorAlloc());
    
    historyNext.count = 0;
    historyNext.args = NULL;
    
    ChangePage(3, LoadingTypeNone, PopupTypeNone, RootPageTypeMainMenu);
    
    Social::localSocial()->LogInGameCenter(this);
    
    popup = NULL;
}

Root::~Root() {
    
    if(selectUser)
        delete selectUser;
    
    ResetHistory();
    VBArrayVectorFree(&vecHistory);
    
    top->removeChild(view->top, false);
    delete view;
    this->removeChild(top, false);
    delete top;
    
    VBEngineShutdown();
    
    //cocos2d::CCLayer::~CCLayer();
}

CCScene* Root::scene() {
	CCScene *scene = CCScene::node();
	Root *layer = ShareDataGetRoot();
	scene->addChild(layer);
	return scene;
}

void Root::Update() {
    
    struct timeval nextTime;
    gettimeofday(&nextTime, NULL);
    
    float _deltaTime = (((nextTime.tv_sec * 1000000.0) + nextTime.tv_usec) - ((curTime.tv_sec * 1000000.0) + curTime.tv_usec)) / 1000000.0;
    
    if(loading) {
        if(loadFlag == 1) {
            if(loading->cur_frame + _deltaTime > 15) {
                loading->gotoAndStop(15);
                loadFlag++;
            }
        } else if(loadFlag == 2) {
            /*
             loadingFlag가 2로 넘어오면서 loading->is_play가 false로 바뀜.
             */
            ChangePageARGSonUpdate();
            loading->gotoAndPlay(15);
            loadFlag++;
        } else if(loadFlag == 3) {
            if(!loading->is_play) {
                ((CCSprite*)top)->removeChild((CCSprite*)loading, false);
                loading = NULL;
                loadFlag = 0;
            } else {
                printf("loading...\n");
            }
        }
    }
    if(view)
        view->Update(_deltaTime);
    if(popup) {
        popup->Update(_deltaTime);
        
        if(popupClear) {
            top->removeChild(popup->top, false);
            if(popupType == PopupTypePause) {
                delete (Popup*)popup;
            } else if(popupType == PopupTypeClear) {
                delete (PopupClear*)popup;
            }
            popup = NULL;
            popupClear = false;
        }
    }
    if(selectUser) {
        selectUser->Update(_deltaTime);
    }
    
    top->VBModelUpdate(_deltaTime);
    top->VBModelUpdateColor(VBColorRGBALoadIdentity());
    
    curTime = nextTime;
}

bool Root::init() {
	if(!CCLayer::init()) {
		return false;
	}
    
	
	return true;
}

void Root::ccTouchesBegan( CCSet *touches, CCEvent *event) {
    if(loading)
        return;
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
//    location.x *= CCDirector::sharedDirector()->getContentScaleFactor();
//    location.y *= CCDirector::sharedDirector()->getContentScaleFactor();
//    printf("%f %f\n", location.x, location.y);
//    float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
//    location.x /= scale;
//    location.y /= scale;
    
    if(selectUser)
        selectUser->touchBegin(touch, location);
    else if(popup)
        popup->touchBegin(touch, location);
    else
        view->touchBegin(touch, location);
}

void Root::ccTouchesMoved( CCSet *touches, CCEvent *event) {
    if(loading)
        return;
    
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
//    location.x *= CCDirector::sharedDirector()->getContentScaleFactor();
//    location.y *= CCDirector::sharedDirector()->getContentScaleFactor();
    
    
//    float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
//    location.x /= scale;
//    location.y /= scale;
    
    if(selectUser)
        selectUser->touchMove(touch, location);
    else if(popup)
        popup->touchMove(touch, location);
    else
        view->touchMove(touch, location);
}

void Root::ccTouchesEnded( CCSet *touches, CCEvent *event) {
    if(loading)
        return;
    
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
//    location.x *= CCDirector::sharedDirector()->getContentScaleFactor();
//    location.y *= CCDirector::sharedDirector()->getContentScaleFactor();
    
//    float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
//    location.x /= scale;
//    location.y /= scale;
    
    
    
    if(selectUser)
        selectUser->touchEnd(touch, location);
    else if(popup)
        popup->touchEnd(touch, location);
    else
        view->touchEnd(touch, location);
}

void Root::ccTouchesCanceled( CCSet *touches, CCEvent *event) {
    if(loading)
        return;
    
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
    
    float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    if(!CCDirector::sharedDirector()->isRetinaDisplay())
        scale *= (CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320);
    location.x /= scale;
    location.y /= scale;
    
    
    if(selectUser)
        selectUser->touchCancel(touch, location);
    else if(popup)
        popup->touchCancel(touch, location);
    else
        view->touchCancel(touch, location);
}

void Root::ResetHistory() {
    while (VBArrayVectorGetLength(vecHistory)) {
        history* _h = (history*)VBArrayVectorRemoveBack(vecHistory);
        if(_h) {
            if(_h->args)
                free(_h->args);
            free(_h);
        }
    }
}

void Root::PushHistory(history* _h) {
    
    history* _ptr = (history*)calloc(1, sizeof(history));
    
    _ptr->count = _h->count;
    _ptr->args = (int*)calloc(sizeof(int), _ptr->count);
    
    for(int i = 0; i < _ptr->count; i++) {
        _ptr->args[i] = _h->args[i];
    }
    
    VBArrayVectorAddBack(vecHistory, _ptr);
}

void Root::PopHistory(int _idx) {
    history* _h = (history*)VBArrayVectorRemoveAt(vecHistory, _idx);
    if(_h) {
        if(_h->args) {
            free(_h->args);
        }
        free(_h);
    }
}

history* Root::GetLastHistory() {
    return (history*)VBArrayVectorGetDataAt(vecHistory, vecHistory->len - 1);
}

void Root::SetLastHistory(history* _h) {
    history* _nh = (history*)VBArrayVectorGetDataAt(vecHistory, vecHistory->len - 1);
    _nh->count = _h->count;
    _nh->args = (int*)realloc(_nh->args, sizeof(int) * _nh->count);
    for(int i = 0; i < _nh->count; i++) {
        _nh->args[i] = _h->args[i];
    }
}

bool Root::IsGameMainHistory(int _h_idx) {
    history* _h = (history*)VBArrayVectorGetDataAt(vecHistory, _h_idx);
    int _idx = 0;
    if(_h->args[_idx] == PopupTypeClear)
        _idx += 3;
    else
        _idx++;
    if(_h->args[_idx] == RootPageTypeGameMain) {
        return true;
    }
    return false;
}

void Root::ChangePageARGSonUpdate() {
    //기존 마지막 히스토리 가져오기
    history* _ptr = GetLastHistory();
    
    //새로운 인자 인덱스
    int _argIdx = 0;
    //이전인자 인덱스
    int _preIdx = 0;
    
    int _prePopupType = 0;
    if(_ptr)
        _prePopupType = _ptr->args[_preIdx];
    int _nextPopupType = historyNext.args[_argIdx];
    if(_prePopupType != _nextPopupType) {
        //팝업상태가 틀릴때
        switch(_prePopupType) {
            case PopupTypePause:
            {
                if(popup) {
                    top->removeChild(popup->top, false);
                    delete (Popup*)popup;
                    popup = NULL;
                    popupClear = false;
                    popupType = PopupTypeNone;
                }
            }
                break;
            case PopupTypeClear:
            {
                if(popup) {
                    top->removeChild(popup->top, false);
                    delete (PopupClear*)popup;
                    popup = NULL;
                    popupClear = false;
                    popupType = PopupTypeNone;
                }
            }
                break;
        }
        switch(_nextPopupType) {
            case PopupTypePause:
            {
                OpenPopupAlloc(historyNext.args[_argIdx], 0, 0);
//                top->removeChild(popup->top, false);
//                top->addChild(popup->top);
            }
                break;
            case PopupTypeClear:
            {
                OpenPopupAlloc(historyNext.args[_argIdx], historyNext.args[_argIdx + 1], historyNext.args[_argIdx + 2]);
//                top->removeChild(popup->top, false);
//                top->addChild(popup->top);

            }
                break;
        }
    } else if(_nextPopupType == PopupTypeClear) {
        //팝업상태는 같지만 인자가 틀릴경우(Clear일 경우 점수가 틀릴수 있음)
    }
    
    //인자 인덱스 증가
    if(_prePopupType == PopupTypeClear)
        _preIdx += 3;
    else
        _preIdx++;
    
    if(_nextPopupType == PopupTypeClear)
        _argIdx += 3;
    else
        _argIdx++;
    
    bool _needAdd = false;
    bool _needRemove = false;
    int prePage = RootPageTypeNone;
    if(_ptr)
        prePage = _ptr->args[_preIdx];
    int newPage = historyNext.args[_argIdx];
    if(_ptr) {
        if(prePage != newPage) {
            //페이지 상태가 틀릴때
            _needRemove = true;
            _needAdd = true;
        }
    } else {
        //최초
        _needAdd = true;
    }
    if(_needRemove) {
        if(view) {
            top->removeChild(view->top, false);
            if(prePage == RootPageTypeMainMenu)
                delete (MainMenu*)view;
            else if(prePage == RootPageTypeSubMenu)
                delete (SubMenu*)view;
            else if(prePage == RootPageTypeGameMain) {
                if (historyNext.args[_argIdx+1] == SubMenuTypeShop) {
                    pushGameMainToHistory();
                    
                }
                delete (GameMain*)view;
            }
            view = NULL;
        }
    }
    if(_needAdd) {
        switch(newPage) {
            case RootPageTypeMainMenu:
                view = (View*)new MainMenu();
                break;
            case RootPageTypeSubMenu:
                view = (View*)new SubMenu();
                break;
            case RootPageTypeGameMain:
                if (gameMainHistory.historyEnable) {
                    view = (View*)popGameMainFromHistory(historyNext.args[_argIdx + 1], historyNext.args[_argIdx + 2]);
                } else {
                    view = (View*)new GameMain(historyNext.args[_argIdx + 1], historyNext.args[_argIdx + 2]);
                }
                break;
        }
        if(view)
            top->addChild(view->top, -1);
    }
    if (!_needRemove && !_needAdd && prePage == newPage) {
        if (newPage == RootPageTypeGameMain) {
            GameMain *gameMain = (GameMain*)view;
            gameMain->resetOtherStage(historyNext.args[_argIdx + 1], historyNext.args[_argIdx + 2]);
            PopHistory(vecHistory->len - 1);
            PopHistory(vecHistory->len - 1);
        }
    }
    //인자 인덱스 증가
    _preIdx++;
    _argIdx++;
    
    if(_argIdx < historyNext.count) {
        //페이지 관련인자 이후
        switch(historyNext.args[_argIdx - 1]) {
            case RootPageTypeSubMenu:
            {
                int _arg0 = 0;
                if(_argIdx < historyNext.count)
                    _arg0 = historyNext.args[_argIdx];
                
                int _arg1 = 0;
                if(_argIdx + 1 < historyNext.count)
                    _arg1 = historyNext.args[_argIdx + 1];
                
                int _arg2 = 0;
                if(_argIdx + 2 < historyNext.count)
                    _arg2 = historyNext.args[_argIdx + 2];
                
                ((SubMenu*)view)->SetMenuType((SubMenuType)(_arg0), _arg1, _arg2);
            }
                break;
            case RootPageTypeGameMain:
                break;
        }
    }
    
    PushHistory(&historyNext);
    
    if(backHistory) {
        for(int i = 0; i < backHistoryStep; i++) {
            PopHistory(vecHistory->len - 2);
        }
        PopHistory(vecHistory->len - 2);
        backHistoryStep = 0;
        backHistory = false;
    }
    printf("history len:%i\n", vecHistory->len);
}

void Root::ChangePageVALIST(int _count, int* _args) {
    int _loadingType = _args[0];
    if(_loadingType == LoadingTypeFull) {
        if(loading == NULL) {
            loading = ShareDataGetLoadingModel();
            ((CCSprite*)top)->addChild((CCSprite*)loading);
        }
        loading->setIsPlayLoop(false);
        loading->gotoAndPlay(0.0);
        loadFlag = 1;
    }
    
    if(historyNext.args)
        free(historyNext.args);
    historyNext.count = _count - 1;
    historyNext.args = (int*)malloc(sizeof(int) * historyNext.count);
    
    for(int i = 0; i < historyNext.count; i++)
        historyNext.args[i] = _args[i + 1];
    /*
    printf("change page valist args :");
    for(int i = 0; i < historyNext.count; i++) {
        printf("%i ", historyNext.args[i]);
    }
    printf("\n");
    */
    if(_loadingType == LoadingTypeNone) {
        ChangePageARGSonUpdate();
    }
}

void Root::ChangePage(int _count, ...) {
    va_list ap;
    va_start(ap, _count);
    int _args[_count];
//    printf("change page args :");
    for(int i = 0; i < _count; i++) {
        _args[i] = va_arg(ap, int);
//        printf("%i ", _args[i]);
    }
//    printf("\n");
    ChangePageVALIST(_count, _args);
    va_end(ap);
}

void Root::OutGoingAtGameMain() {
    int _idx = 1;
    while(IsGameMainHistory(vecHistory->len - _idx)) {
        _idx++;
    }
    if(_idx - 1 > 0)
        PrevPage(_idx - 1);
}

void Root::PrevPage(int _step) {
    if(vecHistory->len > _step) {
        //이전 히스토리
        int _preIdx = vecHistory->len - 1 - _step;
        history* _preHistory = (history*)VBArrayVectorGetDataAt(vecHistory, _preIdx);
        int _pi = 0;
        
        //현재 히스토리
        int _curIdx = vecHistory->len - 1;
        history* _curHistory = (history*)VBArrayVectorGetDataAt(vecHistory, _curIdx);
        int _ci = 0;
        
        //Popup관련 인자 통과
        if(_preHistory->args[_pi] == PopupTypeClear)
            _pi += 3;
        else
            _pi++;
        
        //Popup관련 인자 통과
        if(_curHistory->args[_ci] == PopupTypeClear)
            _ci += 3;
        else
            _ci++;
        
        int _h[_preHistory->count + 1];
        if(_preHistory->args[_pi] != _curHistory->args[_ci]) {
            //페이지가 다르면 로딩시작
            _h[0] = LoadingTypeFull;
        } else {
            _h[0] = LoadingTypeNone;
        }
        for(int i = 0; i < _preHistory->count; i++)
            _h[i + 1] = _preHistory->args[i];
        
        backHistory = true;
        backHistoryStep = _step;
        ChangePageVALIST(_preHistory->count + 1, _h);
    }
}

void Root::goFowardStage()
{
    history* _ptr = GetLastHistory();
    if (_ptr) {
        int pageStateIndex = 0;
        switch (_ptr->args[0]) {
            case PopupTypeNone:case PopupTypePause:
                pageStateIndex = 1;
                break;
            case PopupTypeClear:
                pageStateIndex = 3;
                break;
            default: break;
        }
        if (_ptr->args[pageStateIndex] == RootPageTypeGameMain) {
            
            if (_getpid() == ShareDataGetNextPack()) {
                //reset
                _setsid(_getsid()+1);
                ChangePage(5, LoadingTypeFull, PopupTypeNone, RootPageTypeGameMain, _getpid(), _getsid());
            } else {
                //new
                _setpid(_getpid()+1);
                _setsid(0);
                ChangePage(5, LoadingTypeFull, PopupTypeNone, RootPageTypeGameMain, _getpid(), _getsid());
            }
        }
    }
    
    PopupClose(this);
}

void Root::pushGameMainToHistory()
{
    GameMain *gameMain = (GameMain*)view;
    gameMainHistory.baseIceCream = gameMain->baseIceCream;
    gameMainHistory.iceCream = gameMain->iceCream;
    gameMainHistory.nextIceCream = gameMain->nextIceCream;
    gameMainHistory.historyEnable = true;
    gameMain->retainIceCream();
    
    gameMainHistory.rdTd = gameMain->rdTd;
    gameMain->rdTd->retain();
    
    gameMainHistory.hintViewer = gameMain->hintViewer;
    gameMain->hintViewer->retain();
    
    gameMainHistory.isRecipeMode = gameMain->IsRecipeMode();
}

GameMain* Root::popGameMainFromHistory(int packIdx, int stageIdx)
{
    GameMain* gameMain = new GameMain(packIdx, stageIdx, gameMainHistory.baseIceCream, gameMainHistory.iceCream, gameMainHistory.nextIceCream, gameMainHistory.rdTd, gameMainHistory.hintViewer, gameMainHistory.isRecipeMode);
    gameMainHistory.historyEnable = false;
    gameMainHistory.baseIceCream = gameMainHistory.iceCream = gameMainHistory.nextIceCream = NULL;
    gameMainHistory.rdTd = NULL;
    gameMainHistory.hintViewer = NULL;
    return gameMain;
}
