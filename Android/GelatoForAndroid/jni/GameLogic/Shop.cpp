#include "Shop.h"
#include "Scroller.h"
#include "ShareData.h"

Shop::Shop(VBObjectFile2D* _obj, VBTexture* _tex) : Pages(_obj, _tex, 1, 0.0, 600.0, 0, 357, 240-85, -280) {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    
    LIBNAMEFIND(_library_name_id, _obj, "shop", _str);
    
    backgroundModel = new VBModel(_obj, _library_name_id, _tex, true);
    slideM->addChild(backgroundModel);
    backgroundModel->setPosition(CCPointMake(0, 0));
    
    OBJLOAD(objScroll, "scroller.obj", _str);
    TEXLOAD(texScroll, "scroller.png", _str);
    int inAppCount = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetInApp(), "items"));
    inAppDataVector = VBArrayVectorInit(VBArrayVectorAlloc());
    for (int i=0; i<inAppCount; i++) {
        VBArrayVectorAddBack(inAppDataVector, ShopCellDataInit(i, _obj, _tex));
    }
    container = new ShopScrollerContainer(_obj, _tex, objScroll, texScroll, inAppDataVector);
    containerModel = backgroundModel->getVBModelByInstanceName("container");
    containerModel->addChild(container);
    
    
}

Shop::~Shop() {
    containerModel->removeChild(container, false);
    delete container;
    slideM->removeChild(backgroundModel, false);
    delete backgroundModel;
    
    VBTextureFree(&texScroll);
    VBObjectFile2DFree(&objScroll);
    
    while (VBArrayVectorGetLength(inAppDataVector)) {
        ShopCellData* _cellData = (ShopCellData*)VBArrayVectorRemoveBack(inAppDataVector);
        ShopCellDataFree(&_cellData);
    }
    VBArrayVectorFree(&inAppDataVector);
    
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
    //Pages::touchBegin(_touch, _location);
    container->touchBegin(_touch, _location);
}

void Shop::touchMove(CCTouch* _touch, CCPoint _location) {
    //Pages::touchMove(_touch, _location);
    container->touchMove(_touch, _location);
}

void Shop::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    //Pages::touchEndAndCancel(_touch, _location);
}

void Shop::touchEnd(CCTouch* _touch, CCPoint _location) {
    //Pages::touchEnd(_touch, _location);
    container->touchEnd(_touch, _location);
}

void Shop::touchCancel(CCTouch* _touch, CCPoint _location) {
    //Pages::touchCancel(_touch, _location);
    container->touchCancel(_touch, _location);
}

