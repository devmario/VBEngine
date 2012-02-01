#ifndef gelatomania_Root_h
#define gelatomania_Root_h

#include "cocos2d.h"
#include "VBModel.h"
#include "View.h"
#include "PopupClear.h"
#include <time.h>
#include <stdarg.h>
#include "Social.h"

using namespace cocos2d;

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

bool IsEqualHistory(history* _h0, history* _h1);

class Root : public cocos2d::CCLayer {
private:
    Social* social;
    
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
public:
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
    
	LAYER_NODE_FUNC(Root);
};

#endif
