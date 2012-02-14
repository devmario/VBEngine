#include "Shop.h"
#include "Scroller.h"
#include "ShareData.h"
#include "Language.h"
#include "User.h"

Shop::Shop(VBObjectFile2D** objSubMenuContainer, VBTexture** texSubMenuContainer, int _tapidx) : Pages(NULL, NULL, 1, 0.0, 480, 0, 357, 240-85, -280) {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    
    if(*objSubMenuContainer == NULL) {
        OBJLOAD(*objSubMenuContainer, "sub_menu_container.obj", _str);
    }
    if(*texSubMenuContainer == NULL) {
        TEXLOAD(*texSubMenuContainer, "sub_menu_container.png", _str);
    }
    
    OBJLOAD(shopObj, "shop.obj", _str);
    TEXLOAD(shopTex, "shop.png", _str);
    
    LIBNAMEFIND(_library_name_id, shopObj, "tap", _str);
    modelTap = new VBModel(shopObj, _library_name_id, shopTex, true);
    
    LIBNAMEFIND(_library_name_id, *objSubMenuContainer, "container", _str);
    
    backgroundModel = new VBModel(*objSubMenuContainer, _library_name_id, *texSubMenuContainer, true);
    backgroundModel->stop();
    slideM->addChild(backgroundModel);
    backgroundModel->setPosition(CCPointMake(0, 0));
    
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
    backgroundModel->getVBModelByInstanceName("starCount")->addChild(starCount);
    backgroundModel->getVBModelByInstanceName("undoCount")->addChild(undoCount);
    backgroundModel->getVBModelByInstanceName("hintCount")->addChild(hintCount);
    //
    
    
    backgroundModel->addChild(modelTap);
    modelTap->stop();
    modelTap->setPosition(CCPoint(35, -5));
    
    for(int i = 0; i < 3; i++) {
        textTap[i] = new Text();
        textTap[i]->setPosition(CCPoint(167 + (i*77) - 189.50 - 85.50 , -33));
        modelTap->addChild(textTap[i]);
        touchTap[i] = NULL;
    }
    
    OBJLOAD(objScroll, "scroller.obj", _str);
    TEXLOAD(texScroll, "scroller.png", _str);
    inAppDataVector = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < 3; i++) {
        VBArrayVector* _vec = VBArrayVectorInit(VBArrayVectorAlloc());
        int count;
        cJSON* js;
        if(i == 0)
            js = cJSON_GetObjectItem(ShareDataGetInApp(), "material");
        else if(i == 1)
            js = cJSON_GetObjectItem(ShareDataGetInApp(), "tool");
        else if(i == 2)
            js = cJSON_GetObjectItem(ShareDataGetInApp(), "factory");
        count = cJSON_GetArraySize(js);
        for(int j = 0; j < count; j++) {
            VBArrayVectorAddBack(_vec, ShopCellDataInit(js, j, shopObj, shopTex));
        }
        VBArrayVectorAddBack(inAppDataVector, _vec);
    }
    container = new ShopScrollerContainer(0, shopObj, shopTex, objScroll, texScroll, inAppDataVector);
    containerModel = backgroundModel->getVBModelByInstanceName("container");
    containerModel->addChild(container);
    
    tapIdx = -1;
    SetTap(_tapidx);
}

void Shop::SetTap(int _idx) {
    if(tapIdx != _idx) {
        tapIdx = _idx;
        Language* l = Language::shareLanguage();
        for(int i = 0; i < 3; i++) {
            textTap[i]->SetText(l->GetString("si", 2, "shop", i), l->GetFontName("type0"), 20, 63, 22, i == tapIdx ? "FFFFFFFF" : "000000FF", i != tapIdx ? "FFFFFFFF" : "000000FF", VBVector2DMultiply(VBVector2DCreate(-1, -1), i == tapIdx ? 1 : -1), 0);
        }
        container->SetTapIdx(_idx);
    }
}

Shop::~Shop() {
    
    for(int i = 0; i < 3; i++) {
        modelTap->removeChild(textTap[i], false);
        delete textTap[i];
    }
    
    backgroundModel->getVBModelByInstanceName("starCount")->removeChild(starCount, false);
    backgroundModel->getVBModelByInstanceName("undoCount")->removeChild(undoCount, false);
    backgroundModel->getVBModelByInstanceName("hintCount")->removeChild(hintCount, false);
    delete starCount;
    delete undoCount;
    delete hintCount;
    
    backgroundModel->removeChild(modelTap, false);
    delete modelTap;
    
    containerModel->removeChild(container, false);
    delete container;
    slideM->removeChild(backgroundModel, false);
    delete backgroundModel;
    
    VBTextureFree(&texScroll);
    VBObjectFile2DFree(&objScroll);
    
    while (VBArrayVectorGetLength(inAppDataVector)) {
        VBArrayVector* _vec = (VBArrayVector*)VBArrayVectorRemoveBack(inAppDataVector);
        while (VBArrayVectorGetLength(_vec)) {
            ShopCellData* _cellData = (ShopCellData*)VBArrayVectorRemoveBack(_vec);
            ShopCellDataFree(&_cellData);
        }
        VBArrayVectorFree(&_vec);
    }
    VBArrayVectorFree(&inAppDataVector);
    
    VBObjectFile2DFree(&shopObj);
    VBTextureFree(&shopTex);
    
    //printf("\nshop dealloc\n");
}

void Shop::GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef) {
    if(_idx == 0)
        container->ShowScrollBarMoment(1.0);
    Pages::GoPage(_idx, _pageFunc, _pageFuncRef);
}

void Shop::Update(float _deltaTime) {
    Pages::Update(_deltaTime);
    container->Update(_deltaTime);
}

void Shop::touchBegin(CCTouch* _touch, CCPoint _location) {
    container->touchBegin(_touch, _location);
    TOUCHBEGINBT(touchTap[0], textTap[0], _location, _touch, textTap[0]->color.a = 0x88);
    TOUCHBEGINBT(touchTap[1], textTap[1], _location, _touch, textTap[1]->color.a = 0x88);
    TOUCHBEGINBT(touchTap[2], textTap[2], _location, _touch, textTap[2]->color.a = 0x88);
    //Pages::touchBegin(_touch, _location);
}

void Shop::touchMove(CCTouch* _touch, CCPoint _location) {
    //Pages::touchMove(_touch, _location);
    container->touchMove(_touch, _location);
}

void Shop::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(touchTap[0], textTap[0], _location, _touch, SetTap(0), textTap[0]->color.a = 0xFF);
    TOUCHENDBT(touchTap[1], textTap[1], _location, _touch, SetTap(1), textTap[1]->color.a = 0xFF);
    TOUCHENDBT(touchTap[2], textTap[2], _location, _touch, SetTap(2), textTap[2]->color.a = 0xFF);
    //Pages::touchEndAndCancel(_touch, _location);
}

void Shop::touchEnd(CCTouch* _touch, CCPoint _location) {
    //Pages::touchEnd(_touch, _location);
    container->touchEnd(_touch, _location);
    touchEndAndCancel(_touch, _location);
}

void Shop::touchCancel(CCTouch* _touch, CCPoint _location) {
    //Pages::touchCancel(_touch, _location);
    container->touchCancel(_touch, _location);
    touchEndAndCancel(_touch, _location);
}

