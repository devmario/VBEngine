#include "FriendScrollContainer.h"
#include "FriendScrollCell.h"
#include "ShareData.h"

FriendScrollContainer::FriendScrollContainer(VBObjectFile2D* _objRope, VBTexture* _texRope, VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data) : ScrollerContainer(_objScroller, _texScroller, _data, 60, 310, 224, 5) {
    objRope = _objRope;
    texRope = _texRope;
    
    VBString* _str;
    LIBNAMEFIND(nameRope, objRope, "rope", _str);
    
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellAlloc(_cellData);
        }
    }
    arr_rope = VBArrayVectorInit(VBArrayVectorAlloc());
    ResetRope();
}

void FriendScrollContainer::ResetRope() {
    while (arr_rope->len) {
        VBModel* _m = (VBModel*)VBArrayVectorRemoveBack(arr_rope);
        removeChild(_m, false);
        delete _m;
    }
    for(int i = 0; i < VBArrayVectorGetLength(data) - 1; i++) {
        VBModel* ropeL = new VBModel(objRope, nameRope, texRope, true);
        ropeL->setPosition(CCPoint(123/2 + 7, -110/2-(i*this->cellSize)));
        addChild(ropeL);
        VBModel* ropeR = new VBModel(objRope, nameRope, texRope, true);
        ropeR->setPosition(CCPoint(123/2 + 350/2 + 7, -110/2-(i*this->cellSize)));
        addChild(ropeR);
        VBArrayVectorAddBack(arr_rope, ropeL);
        VBArrayVectorAddBack(arr_rope, ropeR);
    }
}

void FriendScrollContainer::ResetData() {
    cellSizeTotal = VBArrayVectorGetLength(data) * cellSize;
    pageValueMin = -cellSizeTotal + size;
    pageValue = 0;
    forceValue = 0;
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        CellFree(_cellData);
        _cellData->data = VBArrayVectorGetDataAt(data, _cellData->index);
        
        if(_cellData->data){
            CellAlloc(_cellData);
        }
    }
    ResetRope();
}

FriendScrollContainer::~FriendScrollContainer() {
    while (arr_rope->len) {
        VBModel* _m = (VBModel*)VBArrayVectorRemoveBack(arr_rope);
        removeChild(_m, false);
        delete _m;
    }
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellFree(_cellData);
        }
    }
}
void FriendScrollContainer::Update(float _deltaTime) {
    ScrollerContainer::Update(_deltaTime);
    for(int i = 0; i < arr_rope->len; i++) {
        VBModel* _m = (VBModel*)arr_rope->data[i];
        _m->setPosition(CCPoint(_m->getPosition().x,-110/2-(i/2*this->cellSize) - pageValue));
    }
}

void FriendScrollContainer::CellAlloc(CellData* _cell) {
    FriendScrollCell* _data = (FriendScrollCell*)_cell->data;
    if(_data)
        _data->AllocCell(_cell);
}

void FriendScrollContainer::CellFree(CellData* _cell) {
    FriendScrollCell* _data = (FriendScrollCell*)_cell->data;
    if(_data)
        _data->FreeCell(_cell);
}

void FriendScrollContainer::CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    
}

void FriendScrollContainer::CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    
}

void FriendScrollContainer::CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    
}

void FriendScrollContainer::CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    
}

void FriendScrollContainer::CellUpdate(CellData* _cell, float _deltaTime) {
    
}