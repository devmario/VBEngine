//
//  ShopScrollContainer.cpp
//  gelatomania
//
//  Created by Kyung Gak Nam on 12. 1. 11..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//
#include "ShopScrollContainer.h"
#include "Scroller.h"
#include "ShareData.h"
#include "Language.h"

/*
 * cell functions
 */
void ShopScrollerContainer::CellAlloc(CellData *data) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if(cellData == NULL)
        return;
    if (cellData->container) {
        ShopScrollerContainer *_container = cellData->container;
        cellData->bgModel = new VBModel(_container->cellBgObj, _container->cellLibNameId, _container->cellBgTex, true);
        data->modelCell->addChild(cellData->bgModel);
        
        FILE* _decompFile = fopen(VBStringGetCString(cellData->thumbnailPath), "rb");
        fseek(_decompFile, 0, SEEK_END);
        size_t _decompFileSize = ftell(_decompFile);
        fseek(_decompFile, 0, SEEK_SET);
        
        int width, height, colorBit, colorType;
        fread(&width, 1, sizeof(int), _decompFile);
        fread(&height, 1, sizeof(int), _decompFile);
        fread(&colorBit, 1, sizeof(int), _decompFile);
        fread(&colorType, 1, sizeof(int), _decompFile);
        void* _imgData = malloc(_decompFileSize - sizeof(int)*4);
        fread(_imgData, 1, _decompFileSize - sizeof(int)*4, _decompFile);
        fclose(_decompFile);
        
        VBImage *_img = VBImageInitWithData(VBImageAlloc(), colorType, colorBit, width, height, _imgData);
        free(_imgData);
        cellData->thumbnailTex = VBTextureInitAndLoadWithImage(VBTextureAlloc(), _img);
        VBImageFree(&_img);
        
        cellData->thumbnailModel = new VBModel(cellData->thumbnailTex);
        cellData->thumbnailModel->setScale(0.5);
        data->modelCell->addChild(cellData->thumbnailModel);
        cellData->thumbnailModel->setPosition(CCPointMake(2, 4));
        
        Language* l = Language::shareLanguage();
        cellData->textTitle = new Text();
        cellData->textTitle->SetText(cellData->title, l->GetFontName("type0"), 20, 216/2, 40/2, "350803FF", "FFFFFFFF", VBVector2DCreate(1, 1), 0);
        cellData->textTitle->setPosition(CCPoint(222/2 + 2, -54/2));
        cellData->textDescript = new Text();
        cellData->textDescript->SetText(cellData->descript, l->GetFontName("type0"), 8, 324/2-2, 66/2, "FFFFFFFF", "000000FF", VBVector2DCreate(-1, -1), 0, 1);
        cellData->textDescript->setPosition(CCPoint(222/2 + 2, -115/2-1));
        cellData->textMoney = new Text();
        cellData->textMoney->SetText(cellData->money, l->GetFontName("type0"), 15, 43+1, 16, "350803FF", "FFFFFFFF", VBVector2DCreate(1, 1), 0);
        cellData->textMoney->setPosition(CCPoint(455/2 + 2, -60/2));
        data->modelCell->addChild(cellData->textTitle);
        data->modelCell->addChild(cellData->textDescript);
        data->modelCell->addChild(cellData->textMoney);
        
    }
}
void ShopScrollerContainer::CellUpdate(CellData *data, float time) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if(cellData == NULL)
        return;
    if (cellData->container) {
    }
    
}
void ShopScrollerContainer::CellFree(CellData *data) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if(cellData == NULL)
        return;
    if (cellData->container) {
        ShopScrollerContainer *_container = cellData->container;
        
        data->modelCell->removeChild(cellData->textTitle, false);
        data->modelCell->removeChild(cellData->textDescript, false);
        data->modelCell->removeChild(cellData->textMoney, false);
        
        data->modelCell->removeChild(cellData->thumbnailModel, false);
        
        data->modelCell->removeChild(cellData->bgModel, false);
        _container = NULL;
    }
    delete cellData->textTitle;
    delete cellData->textDescript;
    delete cellData->textMoney;
    delete cellData->thumbnailModel;
    VBTextureFree(&cellData->thumbnailTex);
    delete cellData->bgModel;
}
void ShopScrollerContainer::CellTouchBegin(CellData *data, CCTouch *touch, CCPoint location) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if(cellData == NULL)
        return;
    if (cellData->container) {
        TOUCHBEGINBT(cellData->touch, data->modelCell, location, touch, cellData->scrollFlag=false;);
    }
}
void ShopScrollerContainer::CellTouchMove(CellData *data, CCTouch *touch, CCPoint location) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if(cellData == NULL)
        return;
    if (cellData->container) {
        if (cellData->touch == touch) {
            if (!cellData->scrollFlag) {
                cellData->scrollFlag = true;
            } else {
                cellData->touch = NULL;
            }
        }
    }
}
void ShopScrollerContainer::CellTouchEnd(CellData *data, CCTouch *touch, CCPoint location) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if(cellData == NULL)
        return;
    if (cellData->container) {
        TOUCHENDBT(cellData->touch, data->modelCell, location, touch, printf("%d", cellData->idx);, );
    }
}
void ShopScrollerContainer::CellTouchCancel(CellData *data, CCTouch *touch, CCPoint location) {
    CellTouchEnd(data, touch, location);
}

ShopCellData* ShopCellDataInit(cJSON* parent, int idx, VBObjectFile2D *_obj, VBTexture *_tex) {
    VBString *_str;
    
    ShopCellData *data = (ShopCellData *)calloc(1, sizeof(ShopCellData));
    
    data->idx = idx;
    
    
    
    
    cJSON *inAppCellData = cJSON_GetArrayItem(parent, idx);
    char *thumbFileName = cJSON_GetArrayItem(inAppCellData, 0)->valuestring;
    
    Language* l = Language::shareLanguage();
    char* buf = (char*)l->GetString("ssss", 4, "itemInfo", parent->string, cJSON_GetArrayItem(inAppCellData, 1)->valuestring, "title");
    data->title = (char*)calloc(strlen(buf) + 1, 1);
    sprintf(data->title, "%s", buf);
    
    buf = (char*)l->GetString("ssss", 4, "itemInfo", parent->string, cJSON_GetArrayItem(inAppCellData, 1)->valuestring, "descript");
    data->descript = (char*)calloc(strlen(buf) + 1, 1);
    sprintf(data->descript, "%s", buf);
    
    char char_buf[0xFF] = {'\0',};
    sprintf(char_buf, "$ %s", cJSON_GetArrayItem(inAppCellData, 2)->valuestring);
    data->money = (char*)calloc(strlen(char_buf) + 1, 1);
    sprintf(data->money, "%s", char_buf);
    
    data->money_unit = atof(cJSON_GetArrayItem(inAppCellData, 2)->valuestring);
    
    data->thumbnailPath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/decomp_%s.png", VBStringGetCString(VBEngineGetDocumentPath()), thumbFileName);
    if(access(VBStringGetCString(data->thumbnailPath), F_OK) != 0) {
        _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s.png", VBStringGetCString(VBEngineGetResourcePath()), thumbFileName);
        VBImage *_img = VBImageInitWithPath(VBImageAlloc(), _str);
        VBStringFree(&_str);
        
        int width = VBImageGetWidth(_img);
        int height = VBImageGetHeight(_img);
        int colorBit = VBImageGetColorBit(_img);
        int colorType = VBImageGetColorType(_img);
        
        FILE *_decompFile = fopen(VBStringGetCString(data->thumbnailPath), "w");
        fwrite(&width, 1, sizeof(int), _decompFile);
        fwrite(&height, 1, sizeof(int), _decompFile);
        fwrite(&colorBit, 1, sizeof(int), _decompFile);
        fwrite(&colorType, 1, sizeof(int), _decompFile);
        fwrite(VBImageGetImageData(_img), 1, VBImageGetImageDataSize(_img), _decompFile);
        fclose(_decompFile);
        
        VBImageFree(&_img);
    }
    
    
    
    return data;
}

void ShopScrollerContainer::ResetData() {
//    float pre = cellSizeTotal;
    cellSizeTotal = VBArrayVectorGetLength(data) * cellSize;
    pageValueMin = -cellSizeTotal + size;
//    pageValue = (cellSizeTotal / pre) * pageValue;
    //    CCPoint _scroll_position = scroller->getPosition();
    //    removeChild(scroller, false);
    //    delete scroller;
    //    scroller = new Scroller(objScroller, texScroller, size - marginDirBegin - marginDirEnd);
    //    addChild(scroller);
    //    scroller->setPosition(_scroll_position);
    
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        CellFree(_cellData);
        _cellData->data = VBArrayVectorGetDataAt(data, _cellData->index);
        
        if(_cellData->data){
            CellAlloc(_cellData);
        }
    }
}

void ShopCellDataFree(ShopCellData **data) {
    if (*data) {
        free((*data)->title);
        free((*data)->descript);
        free((*data)->money);
        remove(VBStringGetCString((*data)->thumbnailPath));
        VBStringFree(&(*data)->thumbnailPath);
        free(*data);
        *data = NULL;
        
    }
}

void ShopScrollerContainer::SetTapIdx(int _tapIdx) {
    if(tapIdx != _tapIdx) {
        if(tapIdx > -1)
            tap_pageValue[tapIdx] = pageValue > 0 ? 0 : (pageValue < pageValueMin ? pageValueMin : pageValue);
        tapIdx = _tapIdx;
        data = (VBArrayVector*)VBArrayVectorGetDataAt(topData, _tapIdx);
        forceValue = 0.0;
        pageValue = tap_pageValue[tapIdx];
        ResetData();
        ResetRope();
        ShowScrollBarMoment(0.5);
    }
}


/*
 * scroller container class
 */
void ShopScrollerContainer::Update(float _deltaTime) {
    ScrollerContainer::Update(_deltaTime);
    for(int i = 0; i < arr_rope->len; i++) {
        VBModel* _m = (VBModel*)arr_rope->data[i];
        _m->setPosition(CCPoint(_m->getPosition().x,-200/2-(i/2*this->cellSize) - pageValue));
    }
    
}

void ShopScrollerContainer::ResetRope() {
    while (arr_rope->len) {
        VBModel* _m = (VBModel*)VBArrayVectorRemoveBack(arr_rope);
        removeChild(_m, false);
        delete _m;
    }
    for(int i = 0; i < VBArrayVectorGetLength(data) - 1; i++) {
        VBModel* ropeL = new VBModel(this->cellBgObj, this->ropeLibNameId, this->cellBgTex, true);
        ropeL->setPosition(CCPoint(123/2 + 7, -200/2-(i*this->cellSize)));
        addChild(ropeL);
        VBModel* ropeR = new VBModel(this->cellBgObj, this->ropeLibNameId, this->cellBgTex, true);
        ropeR->setPosition(CCPoint(123/2 + 350/2 + 7, -200/2-(i*this->cellSize)));
        addChild(ropeR);
        VBArrayVectorAddBack(arr_rope, ropeL);
        VBArrayVectorAddBack(arr_rope, ropeR);
    }
}

ShopScrollerContainer::
ShopScrollerContainer(int _tapIdx, VBObjectFile2D *_obj_shop, VBTexture *_tex_shop, VBObjectFile2D *_objScroller, VBTexture *_texScroller, VBArrayVector *_data) 
: ScrollerContainer(_objScroller, _texScroller, (VBArrayVector*)VBArrayVectorGetDataAt(_data, _tapIdx), 105, 310, 224, 5) {
    //cellHeight, width, height, margin
    tapIdx = _tapIdx;
    topData = _data;
    arr_rope = VBArrayVectorInit(VBArrayVectorAlloc());
    
    VBString *_str;
    cellBgObj = _obj_shop;
    cellBgTex = _tex_shop;
    LIBNAMEFIND(cellLibNameId, cellBgObj, "cell", _str);
    LIBNAMEFIND(ropeLibNameId, cellBgObj, "rope", _str);
    
    for (int i=0; i<VBArrayVectorGetLength(topData); i++) {
        VBArrayVector* _vec = (VBArrayVector*)VBArrayVectorGetDataAt(topData, i);
        for(int j = 0; j < _vec->len; j++) {
            ShopCellData *cellData = (ShopCellData *)VBArrayVectorGetDataAt(_vec, j);
            cellData->container = this;
        }
    }
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellAlloc(_cellData);
        }
    }
    tap_pageValue[0] = 0;
    tap_pageValue[1] = 0;
    tap_pageValue[2] = 0;
    
    ResetRope();
    
}

ShopScrollerContainer::~ShopScrollerContainer() {
    while (arr_rope->len) {
        VBModel* _m = (VBModel*)VBArrayVectorRemoveBack(arr_rope);
        removeChild(_m, false);
        delete _m;
    }
    VBArrayVectorFree(&arr_rope);
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellFree(_cellData);
        }
    }
}



