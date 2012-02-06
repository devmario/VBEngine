#ifdef __ANDROID__

#include "PlatformFunctions.h"

VBImage* PlatformGetTextImageWithSize(const char* _txt, const char* _fontName, float _text_size, int _width, int _height) {
    return VBImageInitAndClear(VBImageAlloc(), VBColorType_RGBA, 8, _width, _height);
}

//로그인 되어있나 검사
bool PlatformGameCenterIsLogIn() {
    return false;
}

//로그인 시작
//리턴 true: 로그인 작동 성공
//리턴 false: 로그인 작동 실패(이미 로그인 작동중일때)
//_callback: 애플 게임센터서버에서 처리후 리턴된 값이 날라올때 실행하는 콜백(콜백함수 + 유저포인터)
bool PlatformGameCenterLogIn(PlatformCallback _callback) {
    return false;
}

bool PlatformFacebookIsLogIn() {
    return false;
}

bool PlatformFacebookLogIn(PlatformCallback _callback) {
    return false;
}

bool PlatformFacebookLogOut(PlatformCallback _callback) {
    return false;
}


bool PlatformFacebookRequestGraphPath(PlatformFacebookGraphPath _path, PlatformCallback _callback) {
    return false;
}

bool PlatformFacebookAppRequest(const char* _messege, const char* _to, const char* _notification_text, PlatformCallback _callback) {
    return false;
}

bool PlatformFacebookFeed(const char* _name, const char* _caption, const char* _description, const char* _link, const char* _picture, PlatformCallback _callback) {
    return false;
}

bool PlatformMobageLogIn(PlatformCallback _callback) {
    return false;
}

bool PlatformTwitterLogin(PlatformCallback _callback) {
    return false;
}

#endif
