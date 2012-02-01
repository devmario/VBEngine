#ifndef gelatomania_PlatformFunctions_h
#define gelatomania_PlatformFunctions_h

#include "VBEngine.h"
#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    VBImage* PlatformGetTextImage(const char* _txt, const char* _fontName, float _size);
    
    
    
/********GameCenter*****************/
    
#define GameCenterErrorCodeNone 0
#define GameCenterErrorCodeDontHaveAPI 1
#define GameCenterErrorCodeAuthFail 2
    int PlatformGameCenterIsSigned();
    void PlatformGameCenterLogin(void (*_completeCallback)(cJSON*));
    
    
    
    /********Facebook*****************/
    
#define FacebookLoginErrorCodeNone 0
#define FacebookLoginErrorCodeAuthFail 1
#define FacebookLoginErrorCodeGetMeFail 2
    void* _getFB();
    int PlatformFacebookIsSigned();
    void PlatformFacebookLogin(void (*_completeCallback)(cJSON*));
    
#define FacebookGraphPathRequestErrorCodeNone 0
#define FacebookGraphPathRequestErrorCodeFail 1
    
    //me 내정보
    //platform/posts facebook앱정보?(확인필요)
    //me/friends 나와 친구정보
#define FacebookGraphPathRequestTypeMe "me"
#define FacebookGraphPathRequestTypePlatformPosts "platform/posts"
#define FacebookGraphPathRequestTypeMeFriends "me/friends"
    void PlatformFacebookRequestGraphPath(const char* _path, void (*_completeCallback)(cJSON*));
    
    void PlatformFacebookAppRequest(const char* _msg, const char* _to, const char* _notification_text, void (*_completeCallback)(cJSON*));
    
    void PlatformFacebookFeed(const char* _name, const char* _caption, const char* _description, const char* _link, const char* _picture, void (*_completeCallback)(cJSON*));
    
    
    
    void PlatformMobageLogin(void (*_completeCallback)(cJSON*));
    
    
    
    void PlatformTwitterLogin(void (*_completeCallback)(cJSON*));
    
    
    
    
#ifdef __cplusplus
}
#endif

#endif
