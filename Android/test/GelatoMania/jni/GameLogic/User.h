//
//  User.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 2..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_User_h
#define gelatomania_User_h

#include "cJSON.h"

class User {
protected:
    char* m_id;
    char* m_facebookID;
    char* m_gameCenterID;
    char* m_gameCenterAlias;
    char* m_mobageID;
    int m_money;
    
    void SetString(char** ptr, const char* name, const char* str);
public:
    cJSON* json;
    
    void Init();
    
    User();
    ~User();
    
    static User* localUser();
    
    cJSON* GetJSON();
    void SetJSON(cJSON* _json);
    
    void Save();
    
    char* GetID();
    void SetID(char* _id);
    
    char* GetFacebookID();
    void SetFacebookID(char* _id);
    
    char* GetGameCenterID();
    void SetGameCenterID(char* _id);
    
    char* GetGameCenterAlias();
    void SetGameCenterAlias(char* _id);
    
    char* GetMobageID();
    void SetMobageID(char* _id);
    
    int GetMoney();
    void SetMoney(int _value);
};

#endif
