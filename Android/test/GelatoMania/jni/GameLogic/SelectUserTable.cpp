#include "SelectUserTable.h"
#include "PlatformFunctions.h"
#include <stdlib.h>
#include "ShareData.h"
#include "User.h"
#include "cJSON.h"
#include <string.h>

SelectUserCell::SelectUserCell(cJSON* _user, SelectUserTableProtocol* _protocol) {
    protocol = _protocol;
    char* jsonCode = cJSON_Print(_user);
    user = cJSON_Parse(jsonCode);
    char* jsonCodePtr = jsonCode;
    int jsonLength = 0;
    while(*jsonCodePtr != '\0') {
        if(!(*jsonCodePtr == '\t' || *jsonCodePtr == '\n')) {
            jsonLength++;
        }
        jsonCodePtr++;
    }
    char* jsonSmall = (char*)calloc(jsonLength + 1, 1);
    char* jsonSmallPtr = jsonSmall;
    jsonCodePtr = jsonCode;
    while(*jsonCodePtr != '\0') {
        if(!(*jsonCodePtr == '\t' || *jsonCodePtr == '\n')) {
            *jsonSmallPtr = *jsonCodePtr;
            jsonSmallPtr++;
        }
        jsonCodePtr++;
    }
    
    VBImage* img = PlatformGetTextImageWithSize(jsonSmall, "MarkerFelt-Thin", 18, 280, 100);
    free(jsonSmall);
    free(jsonCode);
    
    tex = VBTextureInitAndLoadWithImage(VBTextureAlloc(), img);
    VBImageFree(&img);
    
    model = new VBModel(tex);
    if(strcmp(cJSON_GetString(cJSON_GetObjectItem(_user, "_id")), User::localUser()->GetID()) == 0) {
        model->color.g = model->color.b = 0x00;
    }
    model->setPosition(CCPointMake(-(float)tex->shiftX, (float)tex->shiftY - 15));
    addChild(model);
    
    touch = NULL;
}

SelectUserCell::~SelectUserCell() {
    cJSON_Delete(user);
    removeChild(model, false);
    delete model;
    VBTextureFree(&tex);
}

void SelectUserCell::TouchBegin(CCTouch* _touch, CCPoint _location) {
    TOUCHBEGINBT(touch, this, _location, _touch, 
                 color.a = 0x88;
                 );
}

void SelectUserCell::TouchMove(CCTouch* _touch, CCPoint _location) {
    touch = NULL;
    color.a = 0xFF;
}

void SelectUserCell::TouchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(touch, this, _location, _touch, 
               protocol->SelectUserTableSelectCell(user);
               , 
               color.a = 0xFF);
}

void SelectUserTable::CellAlloc(CellData* _data) {
    VBObjectFile2DLibraryNameID* _name_id;
    VBString* _str;
    LIBNAMEFIND(_name_id, objCell, "cell", _str);
    _data->modelCell->addChild(new VBModel(objCell, _name_id, texCell, true));
    if(_data->data)
        _data->modelCell->addChild(new SelectUserCell((cJSON*)_data->data, protocol));
}

void SelectUserTable::CellFree(CellData* _data) {
    if(_data->data) {
        SelectUserCell* cellModel = (SelectUserCell*)_data->modelCell->getChildren()->objectAtIndex(1);
        _data->modelCell->removeChild(cellModel, false);
        delete cellModel;
    }
    VBModel* cellBackground = (VBModel*)_data->modelCell->getChildren()->objectAtIndex(0);
    _data->modelCell->removeChild(cellBackground, false);
    delete cellBackground;
}

void SelectUserTable::CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    if(_cell->data) {
        SelectUserCell* cellModel = (SelectUserCell*)_cell->modelCell->getChildren()->objectAtIndex(1);
        cellModel->TouchBegin(_touch, _location);
    }
}

void SelectUserTable::CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    if(_cell->data) {
        SelectUserCell* cellModel = (SelectUserCell*)_cell->modelCell->getChildren()->objectAtIndex(1);
        cellModel->TouchMove(_touch, _location);
    }
}

void SelectUserTable::CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    if(_cell->data) {
        SelectUserCell* cellModel = (SelectUserCell*)_cell->modelCell->getChildren()->objectAtIndex(1);
        cellModel->TouchEndAndCancel(_touch, _location);
    }
}

void SelectUserTable::CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    if(_cell->data) {
        SelectUserCell* cellModel = (SelectUserCell*)_cell->modelCell->getChildren()->objectAtIndex(1);
        cellModel->TouchEndAndCancel(_touch, _location);
    }
}

SelectUserTable::SelectUserTable(VBObjectFile2D* _objCell, 
                                 VBTexture* _texCell, 
                                 VBObjectFile2D* _objScroller,
                                 VBTexture* _texScroller, 
                                 VBArrayVector* _data,
                                 SelectUserTableProtocol* _protocol) : ScrollerContainer(_objScroller, _texScroller, _data, 130, 300, 196){
    objCell = _objCell;
    texCell = _texCell;
    protocol = _protocol;
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellAlloc(_cellData);
        }
    }
}

SelectUserTable::~SelectUserTable() {
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellFree(_cellData);
        }
    }
}