#include "cJSON.h"
#include "PlatformFunctions.h"

#ifndef gelatomania_Social_h
#define gelatomania_Social_h

#define HTTP_DEBUG_PRINT

typedef enum SocialError {
    //성공
    SocialErrorNone                             =   0x00,
    //게임센터 인증 실패
    SocialErrorGameCenterAuthFail               =   0x01,
    //게임센터 지원 불가
    SocialErrorGameCenterNotFoundAPI            =   0x02,
    //서버에서 게임센터아이디로 유저 검색 실패
    SocialErrorGameCenterIDCheckSearchFail      =   0x03,
    //게임센터 아이디로 새로운 유저 만들기 실패
    SocialErrorNewIDByGameCenterIDFail          =   0x04,
    //게임센터 아이디를 현재 유저개정에 셋팅 실패
    SocialErrorSetGameCenterIDFail              =   0x05,
} SocialError;

class SocialProtocol {
public:
    
    //게임센터 로그인이 결과 리턴
    virtual void LogInGameCenterComplete(bool success, SocialError error) {};
    
    //매니아 서버에서 게임센터아이디 확인을 마추고 확인결과 해당 게임센터 아이디를 쓰는 유저가 여러명이거나 현재 설정된 유저와 다른 아이디일때
    //즉 유저가 매니아서버의 여러유저 목록에서 하나를 골라야 할때
    //Social::localSocil()->SelectUserByID 로 해당 유저를 선택해 주어야 함
    virtual void GameCenterIDCheckNeedSelect(bool success, SocialError error, 
                                             cJSON* users, cJSON* gameCenterInfo) {};
    
    //게임센터 아이디 확인결과 리턴
    virtual void GameCenterIDCheckComplete(bool success, SocialError error) {};
    
    //게임센터 아이디로 현재 아이디 인증이 성공했을 경우 리턴
    virtual void GameCenterAuthComplete(bool success, SocialError error) {};
    
    virtual void LogInFacebookComplete(bool success, SocialError error) {};
    virtual void LogOutFacebookComplete(bool success, SocialError error) {};
    
    virtual void SendFriendRequestComplete(bool success, SocialError error) {};
    virtual void GetFriendRequestListComplete(bool success, SocialError error) {};
    virtual void AcceptFriendComplete(bool success, SocialError error) {};
    virtual void DisacceptFriendComplete(bool success, SocialError error) {};
    virtual void GetFriendListComplete(bool success, SocialError error) {};
    
    virtual void BuyItemComplete(bool success, SocialError error) {};
    
    virtual void IsNewSocialMissionComplete(bool success, SocialError error) {};
    virtual void GetSocialMissionScoreListComplete(bool success, SocialError error) {};
    
    //유저가 로그인이 성공됬을때
    virtual void LogInUserComplete(bool success, SocialError error) {};
    
};

class Social : public SocialProtocol {
protected:
    SocialProtocol* callback;
    
public:
    
    static Social* localSocial();
    
    Social();
    ~Social();
    
    //게임센터 로그인하기
    void LogInGameCenter(SocialProtocol* _protocol);
    
    void UpdateUserByGameCenterID(SocialProtocol* _protocol, cJSON* _gameCenterInfo);
    
    //만약에 유저의 모든 정보를 가지고 있으면 HTTP request를 진행하지않고 바로 설정됨
    void SelectUserByID(cJSON* _user);
    
    //로그인 되어있는지 확인
    bool IsLogIn();
    
    bool IsLogInFacebook();
    //페이스북 로그인 하기
    bool LogInFacebook(SocialProtocol* _protocol);
    bool LogOutFacebook(SocialProtocol* _protocol);
    
    //친구요청 보내기
    void SendFriendRequest(const char* res_id, SocialProtocol* _protocol);
    //요청리스트 보기
    void GetFriendRequestList(SocialProtocol* _protocol);
    //수락
    void AcceptFriend(const char* friend_id, SocialProtocol* _protocol);
    //거절
    void DisacceptFriend(const char* friend_id, SocialProtocol* _protocol);
    //친구리스트 보기
    void GetFriendList(SocialProtocol* _protocol);

    //아이템 구입
    void BuyItem(int item_id, SocialProtocol* _protocol);
    
    //새로운 미션이 올라왔는지 확인
    void IsNewFriendMission(SocialProtocol* _protocol);
    //미션의 스코어보드 보기
    void GetFriendlMissionScoreList(SocialProtocol* _protocol);
    
    //새로운 미션이 올라왔는지 확인
    void IsNewRandomFriendMission(SocialProtocol* _protocol);
    //미션의 스코어보드 보기
    void GetRandomFriendlMissionScoreList(SocialProtocol* _protocol);
};

#endif
