#ifndef gelatomania_SocialFacebookCallback_h
#define gelatomania_SocialFacebookCallback_h

#include "VBHTTP.h"
#include "cJSON.h"

//페이스북 로그인 응답
void SocialFacebookLogInComplete(cJSON* _json, void* _reference);
//페이스북 로그아웃 응답
void SocialFacebookLogOutComplete(cJSON* _json, void* _reference);

#endif
