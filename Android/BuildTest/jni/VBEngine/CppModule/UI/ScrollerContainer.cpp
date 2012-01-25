#include "ScrollerContainer.h"
#include "ShareData.h"

ScrollerContainer::ScrollerContainer(VBObjectFile2D* _objScroller, VBTexture* _texScroller,
                                     void (*_allocFunc)(CellData*), 
                                     void (*_freeFunc)(CellData*), 
                                     void (*_touchBeginFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                                     void (*_touchMoveFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                                     void (*_touchEndFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                                     void (*_touchCancelFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                                     void (*_updateFunc)(CellData* _data, float _deltaTime), 
                                     VBArrayVector* _data, float _cellHeight, float _width, float _height, float _margin) : VBModel() {
    allocFunc = _allocFunc;
    freeFunc = _freeFunc;
    touchBeginFunc = _touchBeginFunc;
    touchMoveFunc = _touchMoveFunc;
    touchEndFunc = _touchEndFunc;
    touchCancelFunc = _touchCancelFunc;
    updateFunc = _updateFunc;
    data = _data;
    cellHeight = _cellHeight;
    width = _width;
    height = _height;
    forceY = 0.0;
    pageY = 0.0;
    pageHeight = VBArrayVectorGetLength(data) * cellHeight;
    maxPageY = -pageHeight + height;
    alphaScroll = 1.0;
    showScrollerCount = 0.5;
    isShowScroll = false;
    margin = _margin;
    
    VBString* _str;
    VBObjectFile2DLibraryNameID* _name_id;
    LIBNAMEFIND(_name_id, _objScroller, "bg.png", _str);
    container = new VBModel(_objScroller, _name_id, _texScroller, true);
    container->color.a = 0x00;
    addChild(container);
    container->setScaleX(width);
    container->setScaleY(height);
    
    cell = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < (height / cellHeight) + 1; i++) {
        VBModel* _modelCell = new VBModel();
        _modelCell->setPosition(CCPointMake(0, -cellHeight * i));
        addChild(_modelCell);
        CellData* _cellData = (CellData*)calloc(sizeof(CellData), 1);
        _cellData->modelCell = _modelCell;
        _cellData->data = VBArrayVectorGetDataAt(data, i);
        _cellData->index = i;
        VBArrayVectorAddBack(cell, _cellData);
        if(i < VBArrayVectorGetLength(data)) {
            allocFunc(_cellData);
        }
    }
    
    scroller = new Scroller(_objScroller, _texScroller, height - margin * 2.0);
    VBAABB _scrollAABB = scroller->getVBModelSize();
    addChild(scroller);
    scroller->setPosition(CCPointMake(width - (_scrollAABB.r - _scrollAABB.l) - margin, -margin));
    
    enable = true;
    touchScroller = NULL;
}

ScrollerContainer::~ScrollerContainer() {
    while(VBArrayVectorGetLength(cell)) {
        CellData* _cellData = (CellData*)VBArrayVectorRemoveBack(cell);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
            freeFunc(_cellData);
        removeChild(_cellData->modelCell, false);
        delete _cellData->modelCell;
        free(_cellData);
    }
    VBArrayVectorFree(&cell);
    
    removeChild(container, false);
    delete container;
    
    removeChild(scroller, false);
    delete scroller;
}

bool ScrollerContainer::GetEnable() {
    return enable;
}

void ScrollerContainer::SetEnable(bool _enable) {
    if(enable != _enable) {
        enable = _enable;
        if(enable == false) {
            forceY = 0.0;
        }
    }
}

bool ScrollerContainer::NextPage() {
    return false;
}

bool ScrollerContainer::PrevPage() {
    return false;
}

void ScrollerContainer::ReloadData() {
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->modelCell->getPosition().y > cellHeight) {
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) 
                freeFunc(_cellData);
            while(_cellData->modelCell->getPosition().y > cellHeight) {
                _cellData->modelCell->setPosition(CCPointMake(0, _cellData->modelCell->getPosition().y - (cellHeight * VBArrayVectorGetLength(cell))));
                _cellData->index += VBArrayVectorGetLength(cell);
                _cellData->data = VBArrayVectorGetDataAt(data, _cellData->index);
            }
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                allocFunc(_cellData);
        } else if(_cellData->modelCell->getPosition().y < -height) {
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) 
                freeFunc(_cellData);
            while(_cellData->modelCell->getPosition().y < -height) {
                _cellData->modelCell->setPosition(CCPointMake(0, _cellData->modelCell->getPosition().y + (cellHeight * VBArrayVectorGetLength(cell))));
                _cellData->index -= VBArrayVectorGetLength(cell);
                _cellData->data = VBArrayVectorGetDataAt(data, _cellData->index);
            }
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                allocFunc(_cellData);
        }
    }
}

void ScrollerContainer::Update(float _deltaTime) {
    float _marginX2 = margin * 2.0;
    if(touchScroller == NULL) {
        float _prePageY = pageY;
        if(enable) {
            forceY *= 0.95;
            pageY += forceY;
            if(pageY < maxPageY) {
                if(pageHeight <= height) {
                    pageY += (0.0 - pageY) * 0.25;
                } else {
                    pageY += (maxPageY - pageY) * 0.25;
                }
            } else if(pageY > 0.0) {
                pageY += (0.0 - pageY) * 0.25;
            }
        }
        float mY = pageY - _prePageY;
        if(enable) {
            for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                _cellData->modelCell->setPosition(CCPointMake(0, _cellData->modelCell->getPosition().y - mY));
            }
        }
        if(fabsf(forceY) < 0.1 && mY < 0.1)
            isShowScroll = false;
    } else {
        isShowScroll = true;
    }
    scroller->SetScroll(pageHeight <= height ? height - _marginX2 : pageHeight - _marginX2, pageY);
    if(enable) {
        ReloadData();
    }
    if(showScrollerCount < 0.0) {
        if(isShowScroll) {
            alphaScroll += _deltaTime * 20.0;
            if(alphaScroll > 1.0)
                alphaScroll = 1.0;
        } else {
            alphaScroll -= _deltaTime * 10.0;
            if(alphaScroll < 0.0)
                alphaScroll = 0.0;
        }
        scroller->color.a = alphaScroll * 0xFF;
    } else {
        showScrollerCount -= _deltaTime;
    }
    if(updateFunc) {
        for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
            CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
            if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                updateFunc(_cellData, _deltaTime);
        }
    }
}

void ScrollerContainer::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == NULL) {
        if(container->checkCollisionWithButton(_location)) {
            touchScroller = _touch;
            if(enable) {
                forceY = 0.0;
                touchY = _location.y;
            }
            if(touchBeginFunc) {
                for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                    CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                    if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                        touchBeginFunc(_cellData, _touch, _location);
                }
            }
        }
    }
}

void ScrollerContainer::touchMove(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        if(touchMoveFunc) {
            for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                    touchMoveFunc(_cellData, _touch, _location);
            }
        }
        if(enable) {
            forceY = touchY - _location.y;
            float _prePageY = pageY;
            pageY += forceY;
            for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                _cellData->modelCell->setPosition(CCPointMake(0, _cellData->modelCell->getPosition().y - (pageY - _prePageY)));
            }
            touchY = _location.y;
            ReloadData();
        }
    }
}

void ScrollerContainer::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        touchScroller = NULL;
    }
}

void ScrollerContainer::touchEnd(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        if(touchEndFunc) {
            for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                    touchEndFunc(_cellData, _touch, _location);
            }
        }
    }
    touchEndAndCancel(_touch, _location);
}

void ScrollerContainer::touchCancel(CCTouch* _touch, CCPoint _location) {
    if(touchScroller == _touch) {
        if(touchCancelFunc) {
            for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
                CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
                if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data))
                    touchCancelFunc(_cellData, _touch, _location);
            }
        }
    }
    touchEndAndCancel(_touch, _location);
}