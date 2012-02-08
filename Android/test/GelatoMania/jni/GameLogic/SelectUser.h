//
//  SelectUser.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 3..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_SelectUser_h
#define gelatomania_SelectUser_h

#include "cJSON.h"
#include "VBModel.h"
#include "SelectUserTable.h"
#include "Social.h"

class SelectUserProtocol {
public:
    //유저선택시
    virtual void SelectUserCallback(cJSON* user) {};
    //유아이 삭제가 필요할때
    virtual void SelectUserNeedDelete() {};
};

class SelectUser : public SelectUserTableProtocol, public SocialProtocol {
protected:
    cJSON* users;
    VBModel* topModel;
    
    void Init();
    void Free();
    
    bool isInited;
    bool isShow;
    
    SelectUserProtocol* protocol;
    
    VBObjectFile2D* objUI;
    VBTexture* texUI;
    
    VBObjectFile2D* objScroll;
    VBTexture* texScroll;
    
    VBModel* modelUI;
    SelectUserTable* table;
    
    VBArrayVector* data;
    
    VBTexture* texClose;
    VBModel* modelClose;
    
    CCTouch* touchClose;
    
    VBTexture* texTitle;
    VBModel* modelTitle;
    
    char* id_name;
    cJSON* id_info;
public:
    virtual void GameCenterAuthComplete(bool success, SocialError error);
    virtual void SelectUserTableSelectCell(cJSON* user);
    
    SelectUser(cJSON* _users, VBModel* _topModelcopup, SelectUserProtocol* _protocol, const char* _id_name, cJSON* _id_info);
    ~SelectUser();
    
    void SetUsers(cJSON* _users, const char* _id_name, cJSON* _id_info);
    
    void Update(float _deltaTime);
    
    void Show();
    void Hide();
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
};

#endif
