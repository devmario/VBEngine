#include "SelectUser.h"
#include "ShareData.h"
#include "User.h"

void SelectUser::Init() {
    if(isInited == false) {
        VBString* _str;
        OBJLOAD(objUI, "SelectUser.obj", _str);
        OBJLOAD(objScroll, "scroller.obj", _str);
        TEXLOAD(texUI, "SelectUser.png", _str);
        TEXLOAD(texScroll, "scroller.png", _str);
        VBObjectFile2DLibraryNameID* _name_id;
        LIBNAMEFIND(_name_id, objUI, "popup", _str);
        modelUI = new VBModel(objUI, _name_id, texUI, true);
        
        table = new SelectUserTable(objUI, texUI, objScroll, texScroll, data, this);
        modelUI->getVBModelByInstanceName("cell")->addChild(table);
        modelUI->stop();
        topModel->addChild(modelUI);
        
        VBImage* closeImage = PlatformGetTextImageWithSize("Close", "MarkerFelt-Thin", 18, 62, 23);
        texClose = VBTextureInitAndLoadWithImage(VBTextureAlloc(), closeImage);
        VBImageFree(&closeImage);
        
        modelClose = new VBModel(texClose);
        modelUI->getVBModelByInstanceName("bt")->addChild(modelClose);
        modelClose->setPosition(CCPointMake(-(float)texClose->shiftX + 10, (float)texClose->shiftY + 2));
        
        VBString* title = VBStringInitWithCStringFormat(VBStringAlloc(), "로그인된 게임센터 아이디를 쓰는 유저가\n%ld명 있습니다.선택하여 주세요", VBArrayVectorGetLength(data));
        VBImage* titleImage = PlatformGetTextImageWithSize(VBStringGetCString(title), "MarkerFelt-Thin", 12, 230, 50);
        VBStringFree(&title);
        texTitle = VBTextureInitAndLoadWithImage(VBTextureAlloc(), titleImage);
        VBImageFree(&titleImage);
        
        modelTitle = new VBModel(texTitle);
        modelTitle->color.r = modelTitle->color.g = modelTitle->color.b = 0x00;
        modelUI->addChild(modelTitle);
        modelTitle->setPosition(CCPointMake(-(float)texTitle->shiftX + 85, (float)texTitle->shiftY - 42));
        
        isInited = true;
    }
}

void SelectUser::Free() {
    if(isInited == true) {
        modelUI->removeChild(modelTitle, false);
        delete modelTitle;
        VBTextureFree(&texTitle);
        modelUI->getVBModelByInstanceName("bt")->removeChild(modelClose, false);
        delete modelClose;
        modelClose = NULL;
        VBTextureFree(&texClose);
        modelUI->getVBModelByInstanceName("cell")->removeChild(table, false);
        delete table;
        table = NULL;
        while(VBArrayVectorGetLength(data)) {
            cJSON_Delete((cJSON*)VBArrayVectorRemoveBack(data));
        }
        VBArrayVectorFree(&data);
        VBTextureFree(&texScroll);
        VBTextureFree(&texUI);
        VBObjectFile2DFree(&objScroll);
        VBObjectFile2DFree(&objUI);
        topModel->removeChild(modelUI, false);
        delete modelUI;
        modelUI = NULL;
        isInited = false;
        protocol->SelectUserNeedDelete();
    }
}

void SelectUser::GameCenterAuthComplete(bool success, SocialError error) {
    if(success) {
        printf("%s",cJSON_Print(User::localUser()->GetJSON()));
        protocol->SelectUserCallback(User::localUser()->GetJSON());
    }
}

void SelectUser::SelectUserTableSelectCell(cJSON* user) {
    printf("%s",cJSON_Print(user));
    printf("%s",cJSON_Print(id_info));
    if(strcmp(cJSON_GetString(cJSON_GetObjectItem(user, "_id")), User::localUser()->GetID()) == 0) {
        if(strcmp(id_name, "gameCenterID") == 0) {
            cJSON_ReplaceItemInObject(user, "gameCenterID", cJSON_CreateString(cJSON_GetString(cJSON_GetObjectItem(id_info, "playerID"))));
            cJSON_ReplaceItemInObject(user, "gameCenterAlias", cJSON_CreateString(cJSON_GetString(cJSON_GetObjectItem(id_info, "alias"))));
            Social::localSocial()->UpdateUserByGameCenterID(this, id_info);
        }
    } else {
        protocol->SelectUserCallback(user);
    }
}

SelectUser::SelectUser(cJSON* _users, VBModel* _topModel, SelectUserProtocol* _protocol, const char* _id_name, cJSON* _id_info) {
    isInited = false;
    isShow = false;
    protocol = _protocol;
    objUI = NULL;
    texUI = NULL;
    objScroll = NULL;
    texScroll = NULL;
    modelUI = NULL;
    data = NULL;
    texClose = NULL;
    modelClose = NULL;
    touchClose = NULL;
    id_name = NULL;
    id_info = NULL;
    SetUsers(_users, _id_name, _id_info);
    topModel = _topModel;
}

SelectUser::~SelectUser() {
    cJSON_Delete(id_info);
    free(id_name);
    Free();
}

void SelectUser::SetUsers(cJSON* _users, const char* _id_name, cJSON* _id_info) {
    if(id_name)
        free(id_name);
    if(id_info)
        cJSON_Delete(id_info);
    asprintf(&id_name, "%s", _id_name);
    id_info = cJSON_Copy(_id_info);
    if(isInited) {
        table->ResetData();
    } else {
        data = VBArrayVectorInit(VBArrayVectorAlloc());
        for(int i = 0; i < cJSON_GetArraySize(_users); i++) {
            VBArrayVectorAddBack(data, cJSON_Copy(cJSON_GetArrayItem(_users, i)));
        }
    }
}

void SelectUser::Update(float _deltaTime) {
    if(isShow != isInited) {
        if(isShow) {
            Init();
        } else {
            Free();
        }
    }
    if(table)
        table->Update(_deltaTime);
}

void SelectUser::Show() {
    isShow = true;
}

void SelectUser::Hide() {
    isShow = false;
}

void SelectUser::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(table)
        table->touchBegin(_touch, _location);
    if(modelClose) {
        TOUCHBEGINBT(touchClose, modelClose, _location, _touch, );
    }
}

void SelectUser::touchMove(CCTouch* _touch, CCPoint _location) {
    if(table)
        table->touchMove(_touch, _location);
}

void SelectUser::touchEnd(CCTouch* _touch, CCPoint _location) {
    if(table)
        table->touchEnd(_touch, _location);
    touchEndAndCancel(_touch, _location);
}

void SelectUser::touchCancel(CCTouch* _touch, CCPoint _location) {
    if(table)
        table->touchCancel(_touch, _location);
    touchEndAndCancel(_touch, _location);
}

void SelectUser::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(modelClose) {
        TOUCHENDBT(touchClose, modelClose, _location, _touch, Hide(), );
    }
}