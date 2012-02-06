#include "Social.h"
#include "PlatformFunctions.h"
#include "VBHTTP.h"
#include "User.h"
#include "SocialGameCenterCallback.h"
#include "SocialFacebookCallback.h"

//친구수락하기: _id는 친구필드의 _id
//VBHTTPCreateByJS("user.js", "acceptFriend?_id=4f28f0fec0b9350236000053", ErrorHTTP, SuccessHTTP);

//친구거절하기: _id는 친구필드의 _id
//VBHTTPCreateByJS("user.js", "disacceptFriend?_id=4f28f0fec0b9350236000053", ErrorHTTP, SuccessHTTP);

//내 친구 목록 보기: _id는 내아이디
//VBHTTPCreateByJS("user.js", "showFriendList?_id=4f28cce5a36f8d6935000148", ErrorHTTP, SuccessHTTP);



Social* rootSocial = NULL;

Social* Social::localSocial() {
    if(!rootSocial)
        rootSocial = new Social();
    return rootSocial;
}

Social::Social() {
}

Social::~Social() {
}


bool Social::IsLogIn() {
    if(strlen(User::localUser()->GetID()) > 0) {
        return true;
    } else {
        return false;
    }
}


void Social::LogInGameCenter(SocialProtocol* _protocol) {
#ifdef _VB_IPHONE_
    PlatformGameCenterLogIn(PlatformCallbackCreate(_protocol, SocialGameCenterLogInComplete));
#endif
}

void Social::UpdateUserByGameCenterID(SocialProtocol* _protocol, cJSON* _gameCenterInfo) {
    VBHTTPCreateByJS("user.js", _protocol, SocialSetGameCenterID, "updateUser?_id=%s&gameCenterID=%s&gameCenterAlias=%s", 
                     User::localUser()->GetID(),
                     cJSON_GetString(cJSON_GetObjectItem(_gameCenterInfo, "playerID")), 
                     cJSON_GetString(cJSON_GetObjectItem(_gameCenterInfo, "alias")));
}

void Social::SelectUserByID(cJSON* _user) {
    
}

bool Social::IsLogInFacebook() {
    return PlatformFacebookIsLogIn();
}

bool Social::LogInFacebook(SocialProtocol* _protocol) {
    return PlatformFacebookLogIn(PlatformCallbackCreate(_protocol, SocialFacebookLogInComplete));
}

bool Social::LogOutFacebook(SocialProtocol* _protocol) {
    return PlatformFacebookLogOut(PlatformCallbackCreate(_protocol, SocialFacebookLogOutComplete));
}


