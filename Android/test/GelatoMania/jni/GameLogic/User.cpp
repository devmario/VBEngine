#include <iostream>
#include "User.h"
#include "VBEngine.h"

User* rootUser = NULL;

User* User::localUser() {
    if(rootUser == NULL)
        rootUser = new User();
    return rootUser;
}

void User::Init() {
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetDocumentPath()), "user.json");
    if(access(VBStringGetCString(_str), F_OK) != 0) {
        VBString* _tmpStr = VBStringCopy(_str);
        VBStringFree(&_str);
        _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "user.json");
        FILE* _originF = fopen(VBStringGetCString(_str), "r");
        FILE* _cpF = fopen(VBStringGetCString(_tmpStr), "w");
        fseek(_originF, 0, SEEK_END);
        fseek(_cpF, 0, SEEK_END);
        size_t _originLen = ftell(_originF);
        fseek(_originF, 0, SEEK_SET);
        fseek(_cpF, 0, SEEK_SET);
        void* buf = malloc(_originLen);
        fread(buf, 1, _originLen, _originF);
        fwrite(buf, 1, _originLen, _cpF);
        fclose(_originF);
        fclose(_cpF);
    }
    
    FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
    VBStringFree(&_str);
    
    fseek(_jSONFile, 0, SEEK_END);
    size_t _len = ftell(_jSONFile);
    fseek(_jSONFile, 0, SEEK_SET);
    
    char* _jSONData = (char*)calloc(1, _len + 1);
    fread(_jSONData, 1, _len, _jSONFile);
    
    fclose(_jSONFile);
    
    json = cJSON_Parse(_jSONData);
    free(_jSONData);
    
    if(json == NULL) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
        remove(VBStringGetCString(_str));
        Init();
        return;
    }
    
    if(m_id)
        free(m_id);
    m_id = (char*)calloc(1, 1);
    
    if(m_facebookID)
        free(m_facebookID);
    m_facebookID = (char*)calloc(1, 1);
    
    if(m_gameCenterID)
        free(m_gameCenterID);
    m_gameCenterID = (char*)calloc(1, 1);
    
    if(m_gameCenterAlias)
        free(m_gameCenterAlias);
    m_gameCenterAlias = (char*)calloc(1, 1);
    
    if(m_mobageID)
        free(m_mobageID);
    m_mobageID = (char*)calloc(1, 1);
    
    m_money = 0;
    
    SetJSON(json);
    
    Save();
}

User::User() {
    m_id = NULL;
    m_gameCenterID = NULL;
    m_facebookID = NULL;
    m_gameCenterAlias = NULL;
    m_mobageID = NULL;
    json = NULL;
    Init();
}

User::~User() {
    Save();
    cJSON_Delete(json);
    free(m_id);
    free(m_facebookID);
    free(m_gameCenterID);
    free(m_mobageID);
    free(m_gameCenterAlias);
}

void User::Save() {
    if(json) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/tmp_%s", VBStringGetCString(VBEngineGetDocumentPath()), "user.json");
        FILE* _jSONFile = fopen(VBStringGetCString(_str), "w");
        
        char* _json_str = cJSON_Print(json);
        fwrite(_json_str, 1, strlen(_json_str), _jSONFile);
        free(_json_str);
        
        fclose(_jSONFile);
        
        VBString* _dirStr = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetDocumentPath()), "user.json");
        rename(VBStringGetCString(_str), VBStringGetCString(_dirStr));
        VBStringFree(&_str);
        VBStringFree(&_dirStr);
    }
}

cJSON* User::GetJSON() {
    return json;
}

void User::SetJSON(cJSON* _json) {
    SetID(cJSON_GetString(cJSON_GetObjectItem(_json, "_id")));
    SetFacebookID(cJSON_GetString(cJSON_GetObjectItem(_json, "facebookID")));
    SetGameCenterID(cJSON_GetString(cJSON_GetObjectItem(_json, "gameCenterID")));
    SetGameCenterAlias(cJSON_GetString(cJSON_GetObjectItem(_json, "gameCenterAlias")));
    SetMobageID(cJSON_GetString(cJSON_GetObjectItem(_json, "mobageID")));
    SetMoney(cJSON_GetInt(cJSON_GetObjectItem(_json, "money")));
}

void User::SetString(char **ptr, const char* _name, const char *str) {
    if(str) {
        if(strcmp(*ptr, str) != 0) {
            int len = strlen(str);
            *ptr = (char*)realloc(*ptr, len + 1);
            strcpy(*ptr, str);
            (*ptr)[len] = '\0';
            cJSON_ReplaceItemInObject(json, _name, cJSON_CreateString(str));
            Save();
        }
    } else {
        cJSON_ReplaceItemInObject(json, _name, cJSON_CreateNull());
    }
}

char* User::GetID() {
    return m_id;
}

void User::SetID(char* _id) {
    SetString(&m_id, "_id", _id);
}

char* User::GetFacebookID() {
    return m_facebookID;
}

void User::SetFacebookID(char* _id) {
    SetString(&m_facebookID, "facebookID", _id);
}

char* User::GetGameCenterID() {
    return m_gameCenterID;
}

void User::SetGameCenterID(char* _id) {
    SetString(&m_gameCenterID, "gameCenterID", _id);
}

char* User::GetGameCenterAlias() {
    return m_gameCenterAlias;
}

void User::SetGameCenterAlias(char* _id) {
    SetString(&m_gameCenterAlias, "gameCenterAlias", _id);
}

char* User::GetMobageID() {
    return m_mobageID;
}

void User::SetMobageID(char* _id) {
    SetString(&m_mobageID, "mobageID", _id);
}

int User::GetMoney() {
    return m_money;
}

void User::SetMoney(int _value) {
    if(_value != m_money) {
        m_money = _value;
        cJSON_ReplaceItemInObject(json, "money", cJSON_CreateNumber(_value));
        Save();
    }
}