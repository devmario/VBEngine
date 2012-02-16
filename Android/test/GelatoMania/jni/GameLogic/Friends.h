//
//  Friends.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 13..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_Friends_h
#define gelatomania_Friends_h

#include "Pages.h"
#include "FriendScrollContainer.h"
#include "Text.h"
#include "FrameTweenController.h"
#include "cJSON.h"

class SubMenu;

typedef enum FriendsMenuType {
    FriendsMenuTypeNone = -1,
    FriendsMenuTypeList = 0,
    FriendsMenuTypeSearch = 1,
    FriendsMenuTypeMessage = 2
} FriendsMenuType;

class Friends : public Pages {
    cJSON* friendsInfo;
public:
    FriendsMenuType type;
    
    VBObjectFile2D* objFriend;
    VBTexture* texFriend;
    
    VBObjectFile2D* objScroll;
    VBTexture* texScroll;
    
    VBModel* modelContainer;
    VBModel* modelTitle;
    Text* textTitie;
    
    Text* starCount;
    Text* undoCount;
    Text* hintCount;
    
    FrameTweenController* frameCTR_msg;
    FrameTweenController* frameCTR_search;
    FrameTweenController* frameCTR_edit;
    FrameTweenController* frameCTR_re;
    VBModel* modelMsg;
    VBModel* modelSearch;
    VBModel* modelEdit;
    VBModel* modelRe;
    CCTouch* touchMsg;
    CCTouch* touchSearch;
    CCTouch* touchEdit;
    CCTouch* touchRe;
    
    FriendScrollContainer* scrollContainer;
    VBArrayVector* data;
    
    SubMenu* subMenu;
    
    Friends(VBObjectFile2D** objSubMenuContainer, VBTexture** texSubMenuContainer, FriendsMenuType _type, VBModel* modelBottom, SubMenu* _subMenu);
    ~Friends();
    
    void SetType(FriendsMenuType _type);
    
    virtual void GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
