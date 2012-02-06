#ifndef gelatomania_SocialGameCenter_h
#define gelatomania_SocialGameCenter_h

#include "cJSON.h"
#include "VBHTTP.h"

//게임센터 로그인 응답
void SocialGameCenterLogInComplete(cJSON* _json, void* _reference);
//게임센터유저가 서버에 있는지 확인할때 응답
void SocialGameCenterIDCheckComplete(VBHTTP* _http, VBHTTPError _error, void* _reference);
//게임센터 아이디를 매니아 서버에 셋팅하고 나서 응답
void SocialSetGameCenterID(VBHTTP* _http, VBHTTPError _error, void* _reference);
//게임센터 아이디로 새로운 매니아 유저를 만들고 나서 응답
void SocialNewIDByGameCenterID(VBHTTP* _http, VBHTTPError _error, void* _reference);

#endif
