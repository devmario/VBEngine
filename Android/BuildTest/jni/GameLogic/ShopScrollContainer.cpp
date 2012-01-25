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

/*
 * cell functions
 */
void ShopScrollerContainer::CellAlloc(CellData *data) {
    ShopCellData *cellData = (ShopCellData *)data->data;
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
        
        cellData->thumbnailModel = new VBModel(cellData->thumbnailObj, cellData->thumbnailLibNameId, cellData->thumbnailTex, true);
        cellData->thumbnailModel->stop();
        data->modelCell->addChild(cellData->thumbnailModel);
        cellData->thumbnailModel->setPosition(CCPointMake(13.5, -18));
        
    }
}
void ShopScrollerContainer::CellUpdate(CellData *data, float time) {
    
}
void ShopScrollerContainer::CellFree(CellData *data) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if (cellData->container) {
        ShopScrollerContainer *_container = cellData->container;
        
        data->modelCell->removeChild(cellData->thumbnailModel, false);
        delete cellData->thumbnailModel;
        cellData->thumbnailModel = NULL;
        VBTextureFree(&cellData->thumbnailTex);
        
        data->modelCell->removeChild(cellData->bgModel, false);
        delete cellData->bgModel;
        cellData->bgModel = NULL;
        
        _container = NULL;
    }
}
void ShopScrollerContainer::CellTouchBegin(CellData *data, CCTouch *touch, CCPoint location) {
    ShopCellData *cellData = (ShopCellData *)data->data;
    if (cellData->container) {
        TOUCHBEGINBT(cellData->touch, data->modelCell, location, touch, cellData->scrollFlag=false;);
    }
}
void ShopScrollerContainer::CellTouchMove(CellData *data, CCTouch *touch, CCPoint location) {
    ShopCellData *cellData = (ShopCellData *)data->data;
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
    if (cellData->container) {
        TOUCHENDBT(cellData->touch, data->modelCell, location, touch, printf("%d", cellData->idx);, );
    }
}
void ShopScrollerContainer::CellTouchCancel(CellData *data, CCTouch *touch, CCPoint location) {
    CellTouchEnd(data, touch, location);
}

ShopCellData* ShopCellDataInit(int idx, VBObjectFile2D *_obj, VBTexture *_tex) {
    VBString *_str;
    
    ShopCellData *data = (ShopCellData *)calloc(1, sizeof(ShopCellData));
    
    data->idx = idx;
    cJSON *inAppCellData = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetInApp(), "items"), idx);
    char *thumbFileName = cJSON_GetArrayItem(inAppCellData, 0)->valuestring;
    char *cellTitle = cJSON_GetArrayItem(inAppCellData, 1)->valuestring;
    int cellPrice = cJSON_GetArrayItem(inAppCellData, 2)->valueint;
    char *cellDescription = cJSON_GetArrayItem(inAppCellData, 3)->valuestring;
    
    /*
     // for localication
     int localization_idx;
     char *cellDescription = cJSON_GetArrayItem(inAppCellData, 3+localization_idx)->valuestring;
     */
    data->thumbnailPath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/decomp_%s.png", VBStringGetCString(VBEngineGetDocumentPath()), thumbFileName);
#ifdef _ANDROID_
    if(VBStringGetCString(data->thumbnailPath) == 0) {
#else
    if(access(VBStringGetCString(data->thumbnailPath), F_OK) != 0) {
#endif
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
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s.obj", VBStringGetCString(VBEngineGetResourcePath()), thumbFileName);
    data->thumbnailObj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
    VBStringFree(&_str);
    
    LIBNAMEFIND(data->thumbnailLibNameId, data->thumbnailObj, "obj", _str);
    
    data->price = cellPrice;
    data->title = VBStringInitWithCString(VBStringAlloc(), cellTitle);
    data->description = VBStringInitWithCString(VBStringAlloc(), cellDescription);
    
    
    
    return data;
}

void ShopCellDataFree(ShopCellData **data) {
    if (*data) {
        VBObjectFile2DFree(&(*data)->thumbnailObj);
        remove(VBStringGetCString((*data)->thumbnailPath));
        VBStringFree(&(*data)->thumbnailPath);
        VBStringFree(&(*data)->title);
        VBStringFree(&(*data)->description);
        free(*data);
        *data = NULL;
        
    }
}


/*
 * scroller container class
 */

ShopScrollerContainer::
ShopScrollerContainer(VBObjectFile2D *_obj, VBTexture *_tex, VBObjectFile2D *_objScroller, VBTexture *_texScroller, VBArrayVector *_data) 
: ScrollerContainer(_objScroller, _texScroller, _data, 105, 296, 224, 5) {
    //cellHeight, width, height, margin
    
    VBString *_str;
    cellBgObj = _obj;
    cellBgTex = _tex;
    LIBNAMEFIND(cellLibNameId, cellBgObj, "bt.png", _str);
    
    for (int i=0; i<VBArrayVectorGetLength(_data); i++) {
        ShopCellData *cellData = (ShopCellData *)VBArrayVectorGetDataAt(_data, i);
        cellData->container = this;
    }
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellAlloc(_cellData);
        }
    }
    
}

ShopScrollerContainer::~ShopScrollerContainer() {
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellFree(_cellData);
        }
    }
}



