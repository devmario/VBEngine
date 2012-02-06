#include "SocialGameCenterCallback.h"
#include "Social.h"
#include "User.h"

//게임센터 로그인 응답
void SocialGameCenterLogInComplete(cJSON* _json, void* _reference) {
    SocialProtocol* _protocol = (Social*)_reference;
    if(PlatformReturnIsSuccess(_json) > 0) {
        cJSON* gameCenterInfo = cJSON_Copy(cJSON_GetObjectItem(_json, "data"));
        
        if(strcmp(cJSON_GetString(cJSON_GetObjectItem(gameCenterInfo, "playerID")), User::localUser()->GetGameCenterID()) == 0) {
            //로그인 됬고 현재 유저 게임센터 아이디랑 같으면 성공
            _protocol->LogInGameCenterComplete(1, SocialErrorNone);
            _protocol->GameCenterAuthComplete(true, SocialErrorNone);
            cJSON_Delete(gameCenterInfo);
        } else {
            //로그인 됬고 현재 유저 게임센터 아이디랑 다르면 서버에 유저 확인
            VBArrayVector* vector = VBArrayVectorInit(VBArrayVectorAlloc());
            VBArrayVectorAddBack(vector, _protocol);
            VBArrayVectorAddBack(vector, gameCenterInfo);
            VBHTTPCreateByJS("user.js", vector, SocialGameCenterIDCheckComplete, "getUser?gameCenterID=%s", cJSON_GetString(cJSON_GetObjectItem(gameCenterInfo, "playerID")));
        }
    } else {
        //로그인 되어있지 않으면 결과 리턴
        //이때 매니아 서버에 게임센터아이디를 ""로 업데이트 하여야 함
        if(Social::localSocial()->IsLogIn()) {
            VBHTTPCreateByJS("user.js", _protocol, SocialSetGameCenterID, "updateUser?_id=%s&gameCenterID=%s&gameCenterAlias=%s", 
                             User::localUser()->GetID(), "", "");
        }
        
        PlatformError error = PlatformReturnError(_json);
        SocialError social_error = SocialErrorNone;
        
        if(error == PlatformErrorGameCenterAuthFail)
            social_error = SocialErrorGameCenterAuthFail;
        else if(error == PlatformErrorGameCenterNotFoundAPI)
            social_error = SocialErrorGameCenterNotFoundAPI;
        
        _protocol->LogInGameCenterComplete(0, social_error);
    }
}

//게임센터유저가 서버에 있는지 확인할때 응답
void SocialGameCenterIDCheckComplete(VBHTTP* _http, VBHTTPError _error, void* _reference) {
    SocialProtocol* _protocol = (Social*)VBArrayVectorGetDataAt((VBArrayVector*)_reference, 0);
    cJSON* gameCenterInfo = (cJSON*)VBArrayVectorGetDataAt((VBArrayVector*)_reference, 1);
    if(_error != VBHTTPErrorNone) {
        _protocol->GameCenterIDCheckComplete(false, SocialErrorGameCenterIDCheckSearchFail);
        cJSON_Delete(gameCenterInfo);
        VBArrayVectorFree((VBArrayVector**)&_reference);
        return;
    }
    
    char* body = VBHTTPCutHeader(_http->response);
    cJSON* value = cJSON_Parse(body);
    if(value) {
        cJSON* users = cJSON_GetObjectItem(value, "users");
        int users_length = cJSON_GetArraySize(users);
        if(users_length == 0) {
            //서버에 해당 게임센터아이디를 가진 유저가 없을때
            if(Social::localSocial()->IsLogIn()) {
                //로그인 되어있을 경우 게임센터 아이디 변경
                VBHTTPCreateByJS("user.js", _protocol, SocialSetGameCenterID, "updateUser?_id=%s&gameCenterID=%s&gameCenterAlias=%s", 
                                 User::localUser()->GetID(), 
                                 cJSON_GetString(cJSON_GetObjectItem(gameCenterInfo, "playerID")), 
                                 cJSON_GetString(cJSON_GetObjectItem(gameCenterInfo, "alias")));
            } else {
                //로그인 되어있지 않을경우 새로운 아이디 생성
                VBHTTPCreateByJS("user.js", _protocol, SocialNewIDByGameCenterID, "newUser?gameCenterID=%s&gameCenterAlias=%s", 
                                 cJSON_GetString(cJSON_GetObjectItem(gameCenterInfo, "playerID")),
                                 cJSON_GetString(cJSON_GetObjectItem(gameCenterInfo, "alias")));
            }
        } else if(users_length == 1) {
            cJSON* user = cJSON_GetArrayItem(users, 0);
            //서버에 해당 게임센터아이디를 가진 유저가 한명일때
            if(Social::localSocial()->IsLogIn()) {
                //현재 로그인되어있는 아이디랑 검색된 아이디랑 다르므로 선택할수 있도록 프로토콜에 전달(선택한 하면 선택한 유저 아이디가 설정되고 설정되닜는 유저를 선택하면 게임센터 아이디를 업데이트함)
                cJSON_AddItemToArray(users, cJSON_Copy(User::localUser()->GetJSON()));
                _protocol->GameCenterIDCheckNeedSelect(true, SocialErrorNone, users, gameCenterInfo);
            } else {
                //검색된 유저가 한명이고 현재 로그인 되어있지 않을때 유저를 검색된 유저로 바꾸어줌(인증 성공)
                User::localUser()->SetJSON(user);
                _protocol->GameCenterAuthComplete(true, SocialErrorNone);
            }
        } else {
            //현재 로그인되어있는 아이디랑 검색된 아이디랑 다르므로 선택할수 있도록 프로토콜에 전달(선택한 하면 선택한 유저 아이디가 설정되고 이미 설정되있는 유저를 선택하면 게임센터 아이디를 업데이트함)
            if(Social::localSocial()->IsLogIn()) {
                cJSON_AddItemToArray(users, cJSON_Copy(User::localUser()->GetJSON()));
                _protocol->GameCenterIDCheckNeedSelect(true, SocialErrorNone, cJSON_GetObjectItem(value, "users"), gameCenterInfo);
            } else {
                _protocol->GameCenterIDCheckNeedSelect(true, SocialErrorNone, cJSON_GetObjectItem(value, "users"), gameCenterInfo);
            }
        }
    } else {
        _protocol->GameCenterIDCheckComplete(false, SocialErrorGameCenterIDCheckSearchFail);
    }
    cJSON_Delete(value);
    
    cJSON_Delete(gameCenterInfo);
    VBArrayVectorFree((VBArrayVector**)&_reference);
}

//게임센터 아이디를 매니아 서버에 셋팅하고 나서 응답
void SocialSetGameCenterID(VBHTTP* _http, VBHTTPError _error, void* _reference) {
    SocialProtocol* _protocol = (Social*)_reference;
    
    if(_error != VBHTTPErrorNone) {
        _protocol->GameCenterIDCheckComplete(false, SocialErrorSetGameCenterIDFail);
        return;
    }
    
    char* body = VBHTTPCutHeader(_http->response);
    cJSON* value = cJSON_Parse(body);
    if(value) {
        cJSON* user = cJSON_GetObjectItem(value, "user");
        if(user) {
            User::localUser()->SetJSON(user);
            _protocol->GameCenterAuthComplete(true, SocialErrorNone);
        } else {
            _protocol->GameCenterIDCheckComplete(false, SocialErrorSetGameCenterIDFail);
        }
    } else {
        _protocol->GameCenterIDCheckComplete(false, SocialErrorSetGameCenterIDFail);
    }
    cJSON_Delete(value);
}

//게임센터 아이디로 새로운 매니아 유저를 만들고 나서 응답
void SocialNewIDByGameCenterID(VBHTTP* _http, VBHTTPError _error, void* _reference) {
    SocialProtocol* _protocol = (Social*)_reference;
    
    if(_error != VBHTTPErrorNone) {
        _protocol->GameCenterIDCheckComplete(false, SocialErrorNewIDByGameCenterIDFail);
        return;
    }
    
    char* body = VBHTTPCutHeader(_http->response);
    cJSON* value = cJSON_Parse(body);
    if(value) {
        cJSON* user = cJSON_GetObjectItem(value, "user");
        if(user) {
            User::localUser()->SetJSON(user);
            _protocol->GameCenterAuthComplete(true, SocialErrorNone);
        } else {
            _protocol->GameCenterIDCheckComplete(false, SocialErrorSetGameCenterIDFail);
        }
    } else {
        _protocol->GameCenterIDCheckComplete(false, SocialErrorSetGameCenterIDFail);
    }
    cJSON_Delete(value);
}