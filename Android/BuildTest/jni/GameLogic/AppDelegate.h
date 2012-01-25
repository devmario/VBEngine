#ifndef  gelatomania_AppDelegate_h
#define  gelatomania_AppDelegate_h

#include "CCApplication.h"

class  AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();
    virtual bool initInstance();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};

#endif // gelatomania_AppDelegate_h

