#ifndef gelatomania_Root_h
#define gelatomania_Root_h

#include "cocos2d.h"
#include "VBModel.h"
#include "View.h"
#include "PopupClear.h"
#include <time.h>
#include <stdarg.h>
#include "Social.h"
#include "SelectUser.h"

using namespace cocos2d;

class IceCream;
class GameMain;
class GameMainRdTd;
class HintViewer;

typedef enum RootPageType {
    RootPageTypeNone = 0,
    RootPageTypeMainMenu = 1,
    RootPageTypeSubMenu = 2,
    RootPageTypeGameMain = 3
} RootPageType;

typedef enum PopupType {
    PopupTypeNone = 0,
    PopupTypePause = 1,
    PopupTypeClear = 2
} PopupType;

typedef enum LoadingType {
    LoadingTypeNone = 0,
    LoadingTypeFull = 1
} LoadingType;

typedef struct history {
    int* args;
    int count;
} history;

typedef struct GameMainHistory {
    bool historyEnable;
    bool isRecipeMode;
    IceCream* baseIceCream;
    IceCream* iceCream;
    IceCream* nextIceCream;
    GameMainRdTd* rdTd;
    HintViewer* hintViewer;
} GameMainHistory;

bool IsEqualHistory(history* _h0, history* _h1);

class Root : public cocos2d::CCLayer, public SocialProtocol, public SelectUserProtocol {
private:
    View* view;
    VBModel* loading;
    
    int loadFlag;
	
    struct timeval curTime;
    
    VBArrayVector* vecHistory;
    history historyNext;
    bool backHistory;
    int backHistoryStep;
    
    void ChangePageARGSonUpdate();
    void ChangePageVALIST(int _count, int* _args);
    
    void OpenPopupAlloc(int _type, int _star, int _score);
    
    void pushGameMainToHistory();
    GameMain* popGameMainFromHistory(int packIdx, int stageIdx);
public:
    
    virtual void SelectUserCallback(cJSON* user);
    virtual void SelectUserNeedDelete();
    SelectUser* selectUser;
    
    //매니아 서버에서 게임센터아이디 확인을 마추고 확인결과 해당 게임센터 아이디를 쓰는 유저가 여러명이거나 현재 설정된 유저와 다른 아이디일때
    //즉 유저가 매니아서버의 여러유저 목록에서 하나를 골라야 할때
    //Social::localSocil()->SelectUserByID 로 해당 유저를 선택해 주어야 함
    virtual void GameCenterIDCheckNeedSelect(bool success, SocialError error, 
                                             cJSON* users, cJSON* gameCenterInfo);
    
    VBModel* top;
    
    
    
    Root();
	virtual ~Root();
	
    static cocos2d::CCScene* scene();
    
    void Update();
	
    virtual bool init();
    
    virtual void ccTouchesBegan(CCSet *touches, CCEvent *event);
    virtual void ccTouchesMoved(CCSet *touches, CCEvent *event);
    virtual void ccTouchesEnded(CCSet *touches, CCEvent *event);
    virtual void ccTouchesCanceled(CCSet *touches, CCEvent *event);
    
    void ResetHistory();
    void PushHistory(history* _h);
    void PopHistory(int _idx);
    history* GetLastHistory();
    void SetLastHistory(history* _h);
    bool IsGameMainHistory(int _h_idx);
    
    void ChangePage(int _count, ...);
    void PrevPage(int _step);
    void OutGoingAtGameMain();
    
    Popup* popup;
    int popupType;
    bool popupClear;
    
    void OpenPopup(int _type, int _star, int _score);
    void ClosePopup();
    
    void goFowardStage();
    GameMainHistory gameMainHistory;

#ifdef __ANDROID__
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);
#endif

	LAYER_NODE_FUNC(Root);
};

#endif
