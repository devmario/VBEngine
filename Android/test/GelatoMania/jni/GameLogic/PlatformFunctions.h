#ifndef gelatomania_PlatformFunctions_h
#define gelatomania_PlatformFunctions_h

#include "VBEngine.h"
#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /*****************TextImage*****************/
    
    VBImage* PlatformGetTextImageWithSize(const char* _txt, const char* _fontName, float _text_size, int _width, int _height);
    
    
    /*****************Callback*****************/
    
    typedef enum PlatformError {
        PlatformErrorNone                           =   0x00,
        PlatformErrorGameCenterNotFoundAPI          =   0x01,
        PlatformErrorGameCenterAuthFail             =   0x02,
        PlatformErrorFacebookAuthFail               =   0x03,
        PlatformErrorFacebookGetUserFail            =   0x04,
        PlatformErrorFacebookGraphPathRequestFail   =   0x05
    } PlatformError;
    
    /*
     _json의 success: true이면 성공 false이면 실패(Bool)
     _json의 error: 에러코드(Number)
     _json의 data: 필요하면 리턴해주는 결과 데이터(Object)
     
     _reference: PlatformCallback 스트럭처의 reference
    */
    typedef void (*PlatformCallbackFunction)(cJSON* _json, void* _reference);
    
    //콜백함수 + 유저포인터
    typedef struct PlatformCallback {
        //유저를 위한 포인터
        void*  reference;
        //콜백 함수
        PlatformCallbackFunction function;
    } PlatformCallback;
    
    //콜백함수 + 유저포인터 생성
    PlatformCallback PlatformCallbackCreate(void* _reference, PlatformCallbackFunction _function);
    
    //데이터에서 성공결과 가져오기
    //0 :false
    //1 :true
    //-1:_json에 success데이터가 없음
    int PlatformReturnIsSuccess(cJSON* _json);
    
    //데이터에서 에러코드 가져오기
    //-1을 리턴하면 _json에 error데이터가 없음
    PlatformError PlatformReturnError(cJSON* _json);
    
    
    /*****************GameCenter*****************/
    
    //로그인 되어있나 검사
    bool PlatformGameCenterIsLogIn();
    
    //로그인 시작
    //리턴 true: 로그인 작동 성공
    //리턴 false: 로그인 작동 실패(이미 로그인 작동중일때)
    //_callback: 애플 게임센터서버에서 처리후 리턴된 값이 날라올때 실행하는 콜백(콜백함수 + 유저포인터)
    bool PlatformGameCenterLogIn(PlatformCallback _callback);
    
    
    
    /*****************facebook*****************/
    
#ifdef _VB_IPHONE_
    void* PlatformGetFacebookInstance();
#endif
    
    bool PlatformFacebookIsLogIn();
    bool PlatformFacebookLogIn(PlatformCallback _callback);
    bool PlatformFacebookLogOut(PlatformCallback _callback);
    
    typedef enum PlatformFacebookGraphPath {
        //me: 내정보
        PlatformFacebookGraphPathMe                 =   0x00,
        //platform/posts: facebook앱정보?(확인필요)
        PlatformFacebookGraphPathPlatformPosts      =   0x01,
        //me/friends: 나와 친구정보
        PlatformFacebookGraphPathMeFriends          =   0x02
    } PlatformFacebookGraphPath;
    
    bool PlatformFacebookRequestGraphPath(PlatformFacebookGraphPath _path, PlatformCallback _callback);
    
    bool PlatformFacebookAppRequest(const char* _messege, const char* _to, const char* _notification_text, PlatformCallback _callback);
    bool PlatformFacebookFeed(const char* _name, const char* _caption, const char* _description, const char* _link, const char* _picture, PlatformCallback _callback);
    
    
    
    /*****************Mobage*****************/
    
    bool PlatformMobageLogIn(PlatformCallback _callback);
    
    
    
    /*****************Twitter*****************/
    
    bool PlatformTwitterLogin(PlatformCallback _callback);
    
#ifdef __cplusplus
}
#endif

#endif
