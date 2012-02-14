#ifdef __ANDROID__

#include "PlatformFunctions.h"
#include "AndroidNative.h"

VBImage* PlatformGetTextImageWithSize(const char* _txt, const char* _fontName, float _text_size, int _width, int _height) {
    return VBImageInitAndClear(VBImageAlloc(), VBColorType_RGBA, 8, _width, _height);
}

VBImage* PlatformGetTextImageWithSizeDetail(const char* _txt, const char* _fontName, float _text_size, int _width, int _height, const char* _colorCode, const char* _shadowColorCode, VBVector2D _shadowOffset, int align, int _is_line) {
	return GetTextImageWithSizeDetail(_txt, _fontName, _text_size, _width, _height, _colorCode, _shadowColorCode, _shadowOffset, align);
}

bool PlatformIsHaveFont(const char* fontName)
{
	return false;
}

const char* PlatformGetLanguage()
{
	return "default";
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

// fb 로그인확인 <자바에서 확인>
bool PlatformFacebookIsLogIn() {
    return facebookIsLogin();
}

// session check -> java 에서 페이스북 서버 연결 체크 확
bool PlatformFacebookLogIn(PlatformCallback _callback) {
	return facebookLogin(_callback);

}

// fb 로그아웃 시키는 함수 -> java
bool PlatformFacebookLogOut(PlatformCallback _callback) {
	return facebookLogout(_callback);
}

// "me/frends" = 0 , 1 , 2
bool PlatformFacebookRequestGraphPath(PlatformFacebookGraphPath _path, PlatformCallback _callback) {
	facebookRequestGraphPath(_path, _callback);
	return true;
}

// "Message~!!", "User id" , "앱 요청 보낼때 친구 추가 어찌고저찌고 붙음.."
bool PlatformFacebookAppRequest(const char* _messege, const char* _to, const char* _notification_text, PlatformCallback _callback) {
	facebookAppRequest(_messege, _to, _notification_text, _callback);
    return true;
}

// "http ~ .jpg" , ASCI , UTF8
bool PlatformFacebookFeed(const char* _name, const char* _caption, const char* _description, const char* _link, const char* _picture, PlatformCallback _callback) {
	facebookFeed(_name, _caption, _description, _link, _picture, _callback);
    return true;
}

bool PlatformMobageLogIn(PlatformCallback _callback) {
    return false;
}

bool PlatformTwitterLogin(PlatformCallback _callback) {
    return false;
}

#endif
