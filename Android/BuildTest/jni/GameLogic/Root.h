#ifndef gelatomania_Root_h
#define gelatomania_Root_h

#include "cocos2d.h"
#include "VBModel.h"
#include "View.h"
#include "PopupClear.h"
#include <time.h>

enum Page {
    NonPage,
    MainMenuPage,
    PackAndStageSelectPage,
    GameMainPage
};

using namespace cocos2d;

class Root : public cocos2d::CCLayer {
public:
    VBModel* top;
    
    View* view;
    VBModel* loading;
    
    Page currentPage;
    Page nextPage;
    
    int loadFlag;
    
    Popup* popup;
    int popupType;
    bool popupClear;
	
    struct timeval curTime;
    
    Root();
	virtual ~Root();
	
    static cocos2d::CCScene* scene();
    
    void Update();
	
    virtual bool init();
    
    virtual void ccTouchesBegan(CCSet *touches, CCEvent *event);
    virtual void ccTouchesMoved(CCSet *touches, CCEvent *event);
    virtual void ccTouchesEnded(CCSet *touches, CCEvent *event);
    virtual void ccTouchesCanceled(CCSet *touches, CCEvent *event);
    
    void ChangePage(Page _page);
    void ShowLoading(Page _page);
    
    void OpenPopup(int _type, int _star, int _score);
    
	LAYER_NODE_FUNC(Root);
};

#endif
