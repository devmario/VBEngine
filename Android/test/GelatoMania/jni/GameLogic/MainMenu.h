#ifndef gelatomania_MainMenu_h
#define gelatomania_MainMenu_h

#include "View.h"
#include "Social.h"
#include "FrameTweenController.h"

using namespace cocos2d;

class MainMenu : public View, public SocialProtocol {
    void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
public:
    VBObjectFile2D* titleintroObj;
    VBTexture* titleintroTex;
    VBObjectFile2D* objTitleUi;
    VBTexture* texTitleUI;
    VBObjectFile2D* objBT;
    VBTexture* texBT;
    
    VBModel* modelBTUI;
    VBModel* socialBT;
    CCTouch* touchSocial;
    VBModel* mobageBT;
    CCTouch* touchMobage;
    VBModel* settingBT;
    CCTouch* touchSetting;
    
    VBModel* btArch;
    CCTouch* touchArch;
    VBModel* btRank;
    CCTouch* touchRank;
    VBModel* btFB;
    CCTouch* touchFB;
    VBModel* btFriend;
    CCTouch* touchFriend;
    
    FrameTweenController* frameModel;
    bool openSocial;
    
    VBModel* titlebg;
    VBModel* titleui;
    
    VBModel* playBT;
    
    CCTouch* touchPlayBT;
	
    MainMenu();
	~MainMenu();
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
