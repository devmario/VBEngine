#include "Friends.h"
#include "ShareData.h"
#include "Language.h"
#include "SubMenu.h"
#include "FriendScrollCell.h"
#include "User.h"

Friends::Friends(VBObjectFile2D** objSubMenuContainer, VBTexture** texSubMenuContainer, FriendsMenuType _type, VBModel* modelBottom, SubMenu* _subMenu) : Pages(NULL, NULL, 2, 0.0, 480, 0, 357, 240-85, -280) {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    
    subMenu = _subMenu;
    
    if(*objSubMenuContainer == NULL) {
        OBJLOAD(*objSubMenuContainer, "sub_menu_container.obj", _str);
    }
    if(*texSubMenuContainer == NULL) {
        TEXLOAD(*texSubMenuContainer, "sub_menu_container.png", _str);
    }
    
    LIBNAMEFIND(_library_name_id, *objSubMenuContainer, "container", _str);
    
    modelContainer = new VBModel(*objSubMenuContainer, _library_name_id, *texSubMenuContainer, true);
    slideM->addChild(modelContainer);
    modelContainer->stop();
    
    //add star, item count
    User* user = User::localUser();
    VBString* star = VBStringInitWithCStringFormat(VBStringAlloc(), "%03d", user->GetStar());
    VBString* undo = VBStringInitWithCStringFormat(VBStringAlloc(), "x %02d", user->GetUndo());
    VBString* hint = VBStringInitWithCStringFormat(VBStringAlloc(), "x %02d", user->GetHint());
    
    Language* l = Language::shareLanguage();
    
    starCount = new Text();
    starCount->SetText(VBStringGetCString(star), l->GetFontName("type0"), 20, 40, 20, "000000ff", "ffffffff", VBVector2DCreate(0, 0), -1);
    undoCount = new Text();
    undoCount->SetText(VBStringGetCString(undo), l->GetFontName("type0"), 20, 40, 20, "000000ff", "ffffffff", VBVector2DCreate(0, 0), -1);
    hintCount = new Text();
    hintCount->SetText(VBStringGetCString(hint), l->GetFontName("type0"), 20, 40, 20, "000000ff", "ffffffff", VBVector2DCreate(0, 0), -1);
    modelContainer->getVBModelByInstanceName("starCount")->addChild(starCount);
    modelContainer->getVBModelByInstanceName("undoCount")->addChild(undoCount);
    modelContainer->getVBModelByInstanceName("hintCount")->addChild(hintCount);
    
    OBJLOAD(objFriend, "friends.obj", _str);
    TEXLOAD(texFriend, "friends.png", _str);
    
    OBJLOAD(objScroll, "scroller.obj", _str);
    TEXLOAD(texScroll, "scroller.png", _str);
    
    data = VBArrayVectorInit(VBArrayVectorAlloc());

    //make friendsInfo
    friendsInfo = new cJSON();
    for (int i=0; i<7; i++) {
        cJSON* friendInfo = new cJSON();
        cJSON_AddItemToObject(friendInfo, "name", cJSON_CreateString("friend1"));
        cJSON_AddItemToObject(friendInfo, "information", cJSON_CreateString("friend information"));
        cJSON_AddItemToArray(friendsInfo, friendInfo);
        VBArrayVectorAddBack(data, new FriendScrollCell(objFriend, texFriend, friendInfo));
    }
    scrollContainer = new FriendScrollContainer(objFriend, texFriend, objScroll, texScroll, data);
    modelContainer->getVBModelByInstanceName("container")->addChild(scrollContainer);
    //
    
    LIBNAMEFIND(_library_name_id, objFriend, "title", _str);
    modelTitle = new VBModel(objFriend, _library_name_id, texFriend, true);
    modelTitle->stop();
    modelTitle->setPosition(CCPoint(-75,-5));
    
    textTitie = new Text();
    textTitie->setPosition(CCPoint(46,-23));
    modelTitle->addChild(textTitie);
    
    modelContainer->addChild(modelTitle);
    
    touchMsg = touchSearch = touchEdit = touchRe = NULL;
    modelMsg = modelBottom->getVBModelByInstanceName("msg");
    modelSearch = modelBottom->getVBModelByInstanceName("search");
    modelEdit = modelBottom->getVBModelByInstanceName("edit");
    modelRe = modelBottom->getVBModelByInstanceName("re");
    
    frameCTR_msg = new FrameTweenController(modelMsg);
    frameCTR_search = new FrameTweenController(modelSearch);
    frameCTR_edit = new FrameTweenController(modelEdit);
    frameCTR_re = new FrameTweenController(modelRe);
    
    modelMsg = modelMsg->getVBModelByInstanceName("msg");
    modelSearch = modelSearch->getVBModelByInstanceName("search");
    modelEdit = modelEdit->getVBModelByInstanceName("edit");
    modelRe = modelRe->getVBModelByInstanceName("re");
    
    type = FriendsMenuTypeNone;
}

Friends::~Friends() {
    delete frameCTR_msg;
    delete frameCTR_search;
    delete frameCTR_edit;
    delete frameCTR_re;
    
    modelContainer->getVBModelByInstanceName("starCount")->removeChild(starCount, false);
    modelContainer->getVBModelByInstanceName("undoCount")->removeChild(undoCount, false);
    modelContainer->getVBModelByInstanceName("hintCount")->removeChild(hintCount, false);
    delete starCount;
    delete undoCount;
    delete hintCount;
    
    modelTitle->removeChild(textTitie, false);
    delete textTitie;
    
    modelContainer->removeChild(modelTitle, false);
    delete modelTitle;
    
    VBObjectFile2DFree(&objFriend);
    VBTextureFree(&texFriend);
    
    while (data->len) {
        VBArrayVectorRemoveBack(data);
    }
    VBArrayVectorFree(&data);
    
    modelContainer->getVBModelByInstanceName("container")->removeChild(scrollContainer, false);
    delete scrollContainer;
    
    slideM->removeChild(modelContainer, false);
    delete modelContainer;
    
    VBObjectFile2DFree(&objScroll);
    VBTextureFree(&texScroll);
    cJSON_Delete(friendsInfo);
}

void ChangePageFriend(void* arg) {
    Friends* f = (Friends*)arg;
    
    f->textTitie->SetText(Language::shareLanguage()->GetString("si", 2, "friendMenu", f->type), 
                       Language::shareLanguage()->GetFontName("type0")
                       , 25, 135, 25, "FFFFFFFF", "000000FF", VBVector2DCreate(-1,-1), 0, false);
    f->frameCTR_msg->playTo(f->type == FriendsMenuTypeList ? 0 : 29, 0.75, 0, EXPO, EASE_OUT, NULL, NULL);
    f->frameCTR_search->playTo(f->type == FriendsMenuTypeList ? 0 : 29, 0.75, 0, EXPO, EASE_OUT, NULL, NULL);
    f->frameCTR_edit->playTo((f->type == FriendsMenuTypeList || f->type == FriendsMenuTypeMessage) ? 0 : 29, 0.75, 0, EXPO, EASE_OUT, NULL, NULL);
    f->frameCTR_re->playTo(f->type == FriendsMenuTypeSearch ? 29 : 0, 0.75, 0, EXPO, EASE_OUT, NULL, NULL);
    f->scrollContainer->ResetData();
    f->GoPage(0, NULL, NULL);
}

void Friends::SetType(FriendsMenuType _type) {
    if(type != _type) {
        type = _type;
        GoPage(-1, ChangePageFriend, this);
    }
}

void Friends::GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef) {
    if(_idx == 0)
        scrollContainer->ShowScrollBarMoment(1.0);
    Pages::GoPage(_idx, _pageFunc, _pageFuncRef);
}

void Friends::Update(float _deltaTime) {
    Pages::Update(_deltaTime);
    scrollContainer->Update(_deltaTime);
    frameCTR_msg->Update(_deltaTime);
    frameCTR_search->Update(_deltaTime);
    frameCTR_edit->Update(_deltaTime);
    frameCTR_re->Update(_deltaTime);
}

void Friends::touchBegin(CCTouch* _touch, CCPoint _location) {
    TOUCHBEGINBT(touchMsg, modelMsg, _location, _touch, modelMsg->gotoAndStop(1));
    TOUCHBEGINBT(touchSearch, modelSearch, _location, _touch, modelSearch->gotoAndStop(1));
    TOUCHBEGINBT(touchEdit, modelEdit, _location, _touch, modelEdit->gotoAndStop(1));
    TOUCHBEGINBT(touchRe, modelRe, _location, _touch, modelRe->gotoAndStop(1));
    scrollContainer->touchBegin(_touch, _location);
//    if(idx < 0)
//        return;
//    Pages::touchBegin(_touch, _location);
}

void Friends::touchMove(CCTouch* _touch, CCPoint _location) {
    scrollContainer->touchMove(_touch, _location);
//    if(idx < 0)
//        return;
//    Pages::touchMove(_touch, _location);
}

void Friends::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    
    TOUCHENDBT(touchMsg, modelMsg, _location, _touch, 
               subMenu->ChangePage(SubMenuTypeFriends, FriendsMenuTypeMessage, 0);
               , modelMsg->gotoAndStop(0));
    TOUCHENDBT(touchSearch, modelSearch, _location, _touch, 
               subMenu->ChangePage(SubMenuTypeFriends, FriendsMenuTypeSearch, 0);
               , modelSearch->gotoAndStop(0));
    TOUCHENDBT(touchEdit, modelEdit, _location, _touch, , modelEdit->gotoAndStop(0));
    TOUCHENDBT(touchRe, modelRe, _location, _touch, , modelRe->gotoAndStop(0));
//    if(idx < 0)
//        return;
    
}

void Friends::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
    scrollContainer->touchEnd(_touch, _location);
//    if(idx < 0)
//        return;
//    Pages::touchEnd(_touch, _location);
}

void Friends::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
    scrollContainer->touchCancel(_touch, _location);
//    if(idx < 0)
//        return;
//    Pages::touchCancel(_touch, _location);
}