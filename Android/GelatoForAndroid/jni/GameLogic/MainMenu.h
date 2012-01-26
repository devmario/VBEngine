#ifndef gelatomania_MainMenu_h
#define gelatomania_MainMenu_h

#include "View.h"

using namespace cocos2d;

class MainMenu : public View {
    void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
public:
    VBObjectFile2D* titleintroObj;
    VBTexture* titleintroTex;
    
    VBModel* titlebg;
    VBModel* titleui;
    
    VBModel* playBT;
    VBModel* rankBT;
    VBModel* archBT;
    VBModel* infoBT;
    
    CCTouch* touchPlayBT;
    CCTouch* touchRank;
    CCTouch* touchArch;
    CCTouch* touchInfo;
	
    MainMenu();
	~MainMenu();
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
