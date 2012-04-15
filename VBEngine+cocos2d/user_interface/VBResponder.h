#ifndef VBResponder_h
#define VBResponder_h

#include "cocos2d.h"
#include <list>

using namespace cocos2d;

class VBResponder {
private:
	list<VBResponder*>::iterator responder_iterator;
public:
	void RegistResponder();
	void UnregistResponder();
	
	virtual void TouchBegin(CCTouch* _touch) {};
	virtual void TouchMove(CCTouch* _touch) {};
	virtual void TouchEnd(CCTouch* _touch) {};
	virtual void TouchCancel(CCTouch* _touch) {};
};

void VBResponderTouchBegin(CCTouch* _touch);
void VBResponderTouchMove(CCTouch* _touch);
void VBResponderTouchEnd(CCTouch* _touch);
void VBResponderTouchCancel(CCTouch* _touch);

#endif