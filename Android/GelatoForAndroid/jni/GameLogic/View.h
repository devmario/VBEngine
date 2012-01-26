#ifndef gelatomania_View_h
#define gelatomania_View_h

#include "cocos2d.h"
#include "VBModel.h"
#include "VBEngine.h"

using namespace cocos2d;

class View {
public:
    VBModel* top;
	
    View();
	~View();
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
