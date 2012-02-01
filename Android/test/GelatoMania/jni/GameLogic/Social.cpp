#include "Social.h"
#include "PlatformFunctions.h"
#include "vbHTTP.h"
#include "ShareData.h"

Social* _s_root = NULL;

cJSON* create_cjson_string(cJSON* _js, const char* _name) {
    if(cJSON_GetObjectItem(_js, _name)) {
        if(cJSON_GetObjectItem(_js, _name)->valuestring) {
            return cJSON_CreateString(cJSON_GetObjectItem(_js, _name)->valuestring);
        } else {
            return cJSON_CreateNull();
        }
    }
    return cJSON_CreateNull();
}

void NewUserComplete(VBHTTP* _http) {
    char* _ptr = CutHeader(_http->response);
    cJSON* _ret = cJSON_Parse(_ptr);
    
    cJSON* _usr = cJSON_GetObjectItem(_ret, "user");
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "_id", create_cjson_string(_usr, "_id"));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "fb", create_cjson_string(_usr, "fb"));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "tw", create_cjson_string(_usr, "tw"));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "gc", create_cjson_string(_usr, "gc"));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "mbg", create_cjson_string(_usr, "mbg"));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "money", cJSON_CreateNumber(cJSON_GetObjectItem(_usr, "money")->valueint));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "num_play_count", cJSON_CreateNumber(cJSON_GetObjectItem(_usr, "num_play_count")->valueint));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "date_first", create_cjson_string(_usr, "date_first"));
    cJSON_ReplaceItemInObject(ShareDataGetUser(), "date_last", create_cjson_string(_usr, "date_last"));
    cJSON_Delete(_ret);
    ShareDataSaveUser();
    printf("등록성공\n");
    printf("%s\n", cJSON_Print(ShareDataGetUser()));
}

void NewUserError(VBHTTP* _http, unsigned char error_code) {
    printf("등록실패\n");
}

void CheckHaveGameCenterIDSuccess(VBHTTP* _http) {
    char* _ptr = CutHeader(_http->response);
    cJSON* _ret = cJSON_Parse(_ptr);
    cJSON* _usr = cJSON_GetObjectItem(_ret, "users");
    if(cJSON_GetArraySize(_usr) > 0) {
        //게임센터 아이디가 서버에 있을때
        if(cJSON_GetArraySize(_usr) == 1) {
            printf("%s 게임센터 아이디를 쓰고있는 아이디 검색 성공\n", cJSON_GetObjectItem(_s_root->gameCenterInfo, "playerID")->valuestring);
            printf("%s\n", cJSON_Print(cJSON_GetArrayItem(_usr, 0)));
            if(strcmp(cJSON_GetObjectItem(ShareDataGetUser(), "_id")->valuestring, cJSON_GetObjectItem(cJSON_GetArrayItem(_usr, 0), "_id")->valuestring) == 0) {
                printf("등록된 아이디와 같으므로 인증완료\n");
            } else {
                printf("등록된 아이디와 다르므로 선택해야함\n");
            }
        } else {
            printf("유저가 %s 게임센터 아이디를 쓰고있는 다음의 아이디중 하나를 선택할수 있게\n", cJSON_GetObjectItem(_s_root->gameCenterInfo, "playerID")->valuestring);
            printf("%s\n", cJSON_Print(_usr));
        }
    } else {
        //게임센터 아이디가 서버에 없을때
        cJSON* _usr_tk = cJSON_GetObjectItem(ShareDataGetUser(), "_id");
        if(strcmp(_usr_tk->valuestring, "") == 0) {
            //아직 로칼 유저셋팅이 안됬을때
            printf("%s 게임센터 아이디가 서버에 없고 유니크 게임 아이디가 로칼에도 없으므로 유저등록\n", cJSON_GetObjectItem(_s_root->gameCenterInfo, "playerID")->valuestring);
            char _buf[0xFF] = {'\0',};
            sprintf(_buf, "setUser?gc=%s", cJSON_GetObjectItem(_s_root->gameCenterInfo, "playerID")->valuestring);
            VBHTTPCreateByJS("user.js", _buf, NewUserError, NewUserComplete);
        } else {
            //로칼 유저셋팅이 이미 완료됬을때
            _usr_tk = cJSON_GetObjectItem(ShareDataGetUser(), "gc");
            if(strcmp(_usr_tk->valuestring, cJSON_GetObjectItem(_s_root->gameCenterInfo, "playerID")->valuestring) == 0) {
                printf("기존 쓰고있는 게임센터 아이디와 동일하므로 인증완료\n");
            } else {
                printf("기존 쓰고있는 게임센터 아이디와 다르므로 게임센터 아이디 변경및 인증완료\n");
                cJSON_ReplaceItemInObject(ShareDataGetUser(), "gc", cJSON_CreateString(cJSON_GetObjectItem(_s_root->gameCenterInfo, "playerID")->valuestring));
                ShareDataSaveUser();
            }
        }
        //새로운 유저 등록 또는 기존 아이디와 병합할껀지 선택하여야 함
    }
    cJSON_Delete(_ret);
}

void CheckHaveGameCenterIDError(VBHTTP* _http, unsigned char error_code) {
    printf("게임센터 아이디 등록확인 실패: %i\n", error_code);
}

void GameCenterLoginComplete(cJSON* _info) {
    _s_root->gameCenterInfo = _info;
    if(_info) {
        if(cJSON_GetObjectItem(_info, "success")->type == 1) {
            printf("게임센터 로그인 성공\n%s\n", cJSON_Print(_info));
            cJSON* _pid = cJSON_GetObjectItem(_info, "playerID");
            if(_pid) {
                char _buf[0xFF] = {'\0',};
                sprintf(_buf, "getUser?gc=%s", _pid->valuestring);
                VBHTTPCreateByJS("user.js", _buf, CheckHaveGameCenterIDError, CheckHaveGameCenterIDSuccess);
            }
        } else {
            printf("게임센터 로그인 실패\n%s\n", cJSON_Print(_info));
        }
    }
}

void FacebookLoginComplete(cJSON* _info) {
}

Social::Social() {
    _s_root = this;
}

Social::~Social() {
    _s_root = NULL;
}

void Social::LoginGameCenter() {
#ifdef _VB_IPHONE_
    PlatformGameCenterLogin(GameCenterLoginComplete);
#endif
}

void Social::LoginFacebook() {
    PlatformFacebookLogin(FacebookLoginComplete);
}