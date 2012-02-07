#include "ScrollerContainer.h"
#include "ShareData.h"

ScrollerContainer::ScrollerContainer(VBObjectFile2D* _objScroller, VBTexture* _texScroller,
                                     VBArrayVector* _data, float _cellHeight, float _width, float _height, 
                                     float _margin, float _marginDirBegin, float _marginDirEnd,
                                     ScrollerContainerAlign _align, bool _is_center_cell,
                                     bool _is_mask) : VBModel() {
    is_mask = _is_mask;
    data = _data;
    align = _align;
    cellSize = _cellHeight;
    width = _width;
    height = _height;
    forceValue = 0.0;
    pageValue = 0.0;
    cellSizeTotal = VBArrayVectorGetLength(data) * cellSize;
    scroller_alpha = 0.0;
    ShowScrollBarMoment(1.0);
    margin = _margin;
    marginDirBegin = _marginDirBegin;
    marginDirEnd = _marginDirEnd;
    
    VBString* _str;
    VBObjectFile2DLibraryNameID* _name_id;
    LIBNAMEFIND(_name_id, _objScroller, "bg.png", _str);
    container = new VBModel(_objScroller, _name_id, _texScroller, true);
    container->color.a = 0x00;
    addChild(container);
    container->setScaleX(width);
    container->setScaleY(height);
    
    size = IsVertical() ? height : width;
    pageValueMin = -cellSizeTotal + size;
    
    cell = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < (size / cellSize) + 1; i++) {
        VBModel* _modelCell = new VBModel();
        addChild(_modelCell);
        CellData* _cellData = (CellData*)calloc(sizeof(CellData), 1);
        _cellData->modelCell = _modelCell;
        _cellData->data = VBArrayVectorGetDataAt(data, i);
        _cellData->index = i;
        if(_is_center_cell) {
            SetCellValue(_cellData, cellSize * i + size * 0.5 - (cellSize * VBArrayVectorGetLength(_data) * 0.5));
        } else {
            SetCellValue(_cellData, cellSize * i);
        }
        VBArrayVectorAddBack(cell, _cellData);
    }
    
    scroller = new Scroller(_objScroller, _texScroller, size - marginDirBegin - marginDirEnd);
    VBAABB _scrollAABB = scroller->getVBModelSize();
    addChild(scroller);
    if(IsVertical()) {
        if(IsInner()) {
            scroller->setPosition(CCPointMake(margin, -marginDirBegin));
        } else {
            scroller->setPosition(CCPointMake(width - (_scrollAABB.r - _scrollAABB.l) - margin, -marginDirBegin));
        }
    } else {
        if(IsInner()) {
            scroller->setPosition(CCPointMake(marginDirBegin, -margin - (_scrollAABB.r - _scrollAABB.l)));
        } else {
            scroller->setPosition(CCPointMake(marginDirBegin, -size + margin));
        }
        scroller->setRotation(M_PI_2);
    }
    
    enable = true;
    touchScroller = NULL;
    elapseTime = 0.0;
    prePageValue = pageValue;
    slideTween = NULL;
}

ScrollerContainer::~ScrollerContainer() {
    while(VBArrayVectorGetLength(cell)) {
        CellData* _cellData = (CellData*)VBArrayVectorRemoveBack(cell);
        removeChild(_cellData->modelCell, false);
        delete _cellData->modelCell;
        free(_cellData);
    }
    VBArrayVectorFree(&cell);
    
    removeChild(container, false);
    delete container;
    
    removeChild(scroller, false);
    delete scroller;
    
    printf("delete ~ScrollerContainer\n");
}

bool ScrollerContainer::GetEnable() {
    return enable;
}

void ScrollerContainer::SetEnable(bool _enable) {
    if(enable != _enable) {
        enable = _enable;
        if(enable == false) {
            forceValue = 0.0;
        }
    }
}

void ScrollerContainer::CellAlloc(CellData* _cell){};
void ScrollerContainer::CellFree(CellData* _cell){};
void ScrollerContainer::CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location){};
void ScrollerContainer::CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location){};
void ScrollerContainer::CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location){};
void ScrollerContainer::CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location){};
void ScrollerContainer::CellUpdate(CellData *_cell, float _deltaTime){};

void ScrollerContainer::NextPage() {
    if(IsPossibleNextPage() == false)
        return;
    forceValue = 0.0;
    if (slideTween) {
        delete slideTween;
        slideTween = NULL;
    }
    slideTween = new TweenerWrapper();
    slideTween->begin(&pageValue, ((pageValue - size) < pageValueMin) ? pageValueMin : (pageValue - size), 0.5f, 0.0f, false);
    
    elapseTime = 0.0;
}

void ScrollerContainer::PrevPage() {
    if(IsPossiblePrevPage() == false)
        return;
    forceValue = 0.0;
    if (slideTween) {
        delete slideTween;
        slideTween = NULL;
    }
    slideTween = new TweenerWrapper();
    slideTween->begin(&pageValue, ((pageValue + size) > 0.0) ? 0.0 : (pageValue + size), 0.5f, 0.0f, false);
    elapseTime = 0.0;
}
bool ScrollerContainer::IsPossibleNextPage() {
    return pageValue >= pageValueMin + 1;
}

bool ScrollerContainer::IsPossiblePrevPage() {
    return pageValue <= -1;
}

bool ScrollerContainer::IsVertical() {
    return align & ScrollerContainerAlign_Vertical;
}

bool ScrollerContainer::IsInner() {
    return align & ScrollerContainerAlign_Inner;
}

void ScrollerContainer::ShowScrollBarMoment(float _time) {
    scroller_isShow = true;
    scroller_showTime = _time;
}

void ScrollerContainer::ResetData() {
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        _cellData->data = VBArrayVectorGetDataAt(data, i);
        CellFree(_cellData);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)){
            CellAlloc(_cellData);
        }
    }
}

void ScrollerContainer::ReloadData() {
    float _m = pageValue - prePageValue;
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(GetCellValue(_cellData) < -cellSize && _m < 0.0) {
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))  
                CellFree(_cellData);
            while(GetCellValue(_cellData) < -cellSize) {
                SetCellValue(_cellData, GetCellValue(_cellData) + cellSize * VBArrayVectorGetLength(cell));
                _cellData->index += VBArrayVectorGetLength(cell);
                _cellData->data = VBArrayVectorGetDataAt(data, _cellData->index);
            }
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                CellAlloc(_cellData);
        } else if(GetCellValue(_cellData) > size && _m > 0.0) {
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) 
                CellFree(_cellData);
            while(GetCellValue(_cellData) > size) {
                SetCellValue(_cellData, GetCellValue(_cellData) - cellSize * VBArrayVectorGetLength(cell));
                _cellData->index -= VBArrayVectorGetLength(cell);
                _cellData->data = VBArrayVectorGetDataAt(data, _cellData->index);
            }
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                CellAlloc(_cellData);
        }
    }
}

void ScrollerContainer::Update(float _deltaTime) {
    if(touchScroller == NULL) {
        if (slideTween && slideTween->onGoing) {
            slideTween->update(_deltaTime);
            scroller_isShow = true;
        } else {
            if(enable) {
                forceValue *= 0.95;
                pageValue += forceValue;
                if(pageValue < pageValueMin) {
                    if(cellSizeTotal <= size) {
                        pageValue += (0.0 - pageValue) * 0.25;
                    } else {
                        pageValue += (pageValueMin - pageValue) * 0.25;
                    }
                } else if(pageValue > 0.0) {
                    pageValue += (0.0 - pageValue) * 0.25;
                }
            }
            scroller_isShow = fabsf(forceValue) > 0.1 || fabsf(pageValue - prePageValue) > 0.1;
        }
    } else {
        scroller_isShow = true;
    }
    
    scroller->SetScroll(cellSizeTotal <= size ? size - (marginDirBegin + marginDirEnd) : cellSizeTotal - (marginDirBegin + marginDirEnd), pageValue);
    if(scroller_showTime > 0.0 || scroller_isShow) {
        scroller_showTime -= _deltaTime;
        scroller_alpha += _deltaTime * 20.0;
        if(scroller_alpha > 1.0)
            scroller_alpha = 1.0;
    } else {
        scroller_alpha -= _deltaTime * 10.0;
        if(scroller_alpha < 0.0)
            scroller_alpha = 0.0;
    }
    scroller->color.a = scroller_alpha * 0xFF;
    
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        SetCellValue(_cellData, GetCellValue(_cellData) + (pageValue - prePageValue));
    }
    ReloadData();
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
            CellUpdate(_cellData, _deltaTime);
    }
    
    prePageValue = pageValue;
}

void ScrollerContainer::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(!enable)
        return;
    if(touchScroller == NULL) {
        if(container->checkCollisionWithButton(_location)) {
            CCPoint _tmp = CCPointApplyAffineTransform(_location, worldToNodeTransform());
            if (slideTween && slideTween->onGoing) {
                delete slideTween;
                slideTween = NULL;
                slideTween = new TweenerWrapper();
            }
            touchScroller = _touch;
            if(enable) {
                forceValue = 0.0;
                touchY = IsVertical() ? _tmp.y : -_tmp.x;
            }
            for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                    CellTouchBegin(_cellData, _touch, _location);
            }
        }
    }
}

void ScrollerContainer::touchMove(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        CCPoint _tmp = CCPointApplyAffineTransform(_location, worldToNodeTransform());
        if (slideTween && slideTween->onGoing) {
            delete slideTween;
            slideTween = NULL;
            slideTween = new TweenerWrapper();
        }
        for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
            CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                CellTouchMove(_cellData, _touch, _location);
        }
        if(enable) {
            forceValue = touchY - (IsVertical() ? _tmp.y : -_tmp.x);
            pageValue += forceValue;
            touchY = IsVertical() ? _tmp.y : -_tmp.x;
        }
    }
}

void ScrollerContainer::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        if (slideTween && slideTween->onGoing) {
            delete slideTween;
            slideTween = NULL;
            slideTween = new TweenerWrapper();
        }
        touchScroller = NULL;
    }
}

void ScrollerContainer::touchEnd(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
            CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                CellTouchEnd(_cellData, _touch, _location);
        }
    }
    touchEndAndCancel(_touch, _location);
}

void ScrollerContainer::touchCancel(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
            CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                CellTouchCancel(_cellData, _touch, _location);
        }
    }
    touchEndAndCancel(_touch, _location);
}


void ScrollerContainer::SetCellValue(CellData* _cell, float _value) {
    if(IsVertical()) {
        _cell->modelCell->setPosition(CCPointMake(0, -_value));
    } else {
        _cell->modelCell->setPosition(CCPointMake(_value, 0));
    }
}

float ScrollerContainer::GetCellValue(CellData* _cell) {
    return IsVertical() ? -_cell->modelCell->getPosition().y : _cell->modelCell->getPosition().x;
}

void ScrollerContainer::visit(void) {
    if(is_mask) {
        glEnable(GL_SCISSOR_TEST);
        CCPoint zero = CCPointApplyAffineTransform(CCPointMake(0, 0), nodeToWorldTransform());
        //        printf("%f %f\n", zero.x, zero.y);
        float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
        glScissor(zero.x, (zero.y - height * scale), width * scale, height * scale);
    }
    VBModel::visit();
    if(is_mask)
        glDisable(GL_SCISSOR_TEST);
}