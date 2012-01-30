#include "ToppingContainer.h"
#include "ShareData.h"

void ToppingContainer::ResetData() {
    if(data) {
        for(int i = 0; i < data->len; i++) {
            ToppingContainerCellDataReset((ToppingContainerCellData*)data->data[i]);
        }
    }
    ScrollerContainer::ResetData();
}

ToppingContainerCellData* ToppingContainerCellDataInit(int _type, int _stepTotal) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)calloc(1, sizeof(ToppingContainerCellData));
    VBString* _str;
    _data->type = _type;
    char* _topping_name = cJSON_GetArrayItem(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "topping"), _data->type), 0)->valuestring;
    _data->texPath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/decomp_%s.png", VBStringGetCString(VBEngineGetDocumentPath()), _topping_name);
    if(access(VBStringGetCString(_data->texPath), F_OK) != 0) {
        _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s.png", VBStringGetCString(VBEngineGetResourcePath()), _topping_name);
        VBImage* _img = VBImageInitWithPath(VBImageAlloc(), _str);
        VBStringFree(&_str);
        
        int texW = VBImageGetWidth(_img);
        int texH = VBImageGetHeight(_img);
        int colorBit = VBImageGetColorBit(_img);
        int colorType = VBImageGetColorType(_img);
        
        FILE* _decompFile = fopen(VBStringGetCString(_data->texPath), "w");
        fwrite(&texW, 1, sizeof(int), _decompFile);
        fwrite(&texH, 1, sizeof(int), _decompFile);
        fwrite(&colorBit, 1, sizeof(int), _decompFile);
        fwrite(&colorType, 1, sizeof(int), _decompFile);
        fwrite(VBImageGetImageData(_img), 1, VBImageGetImageDataSize(_img), _decompFile);
        fclose(_decompFile);
        
        VBImageFree(&_img);
    }
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s.obj", VBStringGetCString(VBEngineGetResourcePath()), _topping_name);
    _data->obj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
    VBStringFree(&_str);
    
    LIBNAMEFIND(_data->name_id, _data->obj, "obj", _str);
    
    _data->stepTotal = _stepTotal;
    
    return _data;
}

void ToppingContainerCellDataReset(ToppingContainerCellData* _data) {
    _data->step = 0;
}

void ToppingContainerCellDataFree(ToppingContainerCellData** _data) {
    VBObjectFile2DFree(&(*_data)->obj);
    remove(VBStringGetCString((*_data)->texPath));
    VBStringFree(&(*_data)->texPath);
    free(*_data);
    *_data = NULL;
}

void ToppingContainer::CellAlloc(CellData* _cell) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)_cell->data;
    if(_data->model == NULL) {
        FILE* _decompFile = fopen(VBStringGetCString(_data->texPath), "rb");
        fseek(_decompFile, 0, SEEK_END);
        size_t _decompFileSize = ftell(_decompFile);
        fseek(_decompFile, 0, SEEK_SET);
        int _w, _h, _b, _t;
        fread(&_w, 1, sizeof(int), _decompFile);
        fread(&_h, 1, sizeof(int), _decompFile);
        fread(&_b, 1, sizeof(int), _decompFile);
        fread(&_t, 1, sizeof(int), _decompFile);
        void* _imgData = malloc(_decompFileSize - sizeof(int) * 4);
        fread(_imgData, 1, _decompFileSize - sizeof(int) * 4, _decompFile);
        fclose(_decompFile);
        
        VBImage* _img = VBImageInitWithData(VBImageAlloc(), _t, _b, _w, _h, _imgData);
        free(_imgData);
        _data->tex = VBTextureInitAndLoadWithImage(VBTextureAlloc(), _img);
        VBImageFree(&_img);
        
        _data->model = new VBModel(_data->obj, _data->name_id, _data->tex, true);
        _data->model->gotoAndStop(0);
        _data->model->setIsPlayLoop(false);
        _data->model->setPosition(CCPointMake(cellSize * 0.5, 0));
        _cell->modelCell->addChild(_data->model);
        
        _data->innerModel = _data->model->getVBModelByInstanceName("inner");
        
        if(_data->step > 0) {
            if(_data->innerModel == NULL) {
                _data->model->gotoAndStop(_data->model->frame->total_frame - 1.0);
            } else {
                _data->innerModel->gotoAndStop(_data->step);
            }
        }
    }
}

void ToppingContainer::CellFree(CellData* _cell) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)_cell->data;
    if(_data->model) {
        _cell->modelCell->removeChild(_data->model, false);
        delete _data->model;
        _data->model = NULL;
        
        VBTextureFree(&_data->tex);
    }
}

void ToppingContainer::CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)_cell->data;
    TOUCHBEGINBT(_data->touch, _data->model, _location, _touch, 
                 );
}

void ToppingContainer::CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)_cell->data;
    _data->touch = NULL;
}

void ToppingContainer::CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)_cell->data;
    
    TOUCHENDBT(_data->touch, _data->model, _location, _touch, 
               if(selectModel == NULL && _data->step < _data->stepTotal && iceCream->IsPossibleTopping(_data->type)) {
                   _data->step++;
                   selectInnerModel = _data->innerModel;
                   if(_data->innerModel) {
                       if(_data->innerModel->cur_frame == selectInnerModel->frame->total_frame - 1) {
                           
                       } else {
                           SetEnable(false);
                           selectModel = _data->model;
                           float _at = (size * 0.5 - 10) - (_cell->modelCell->getPosition().x + cellSize * 0.5);
                           BeginSelectTween(_at, fabsf(_at / (size * 0.5) * 0.75), true);
                       }
                   } else {
                       if(_data->model->cur_frame == _data->model->frame->total_frame - 1) {
                           
                       } else {
                           SetEnable(false);
                           selectModel = _data->model;
                           float _at = (size * 0.5 - 10) - (_cell->modelCell->getPosition().x + cellSize * 0.5);
                           BeginSelectTween(_at, fabsf(_at / (size * 0.5) * 0.75), true);
                       }
                   }
               }
               , );
}

void ToppingContainer::CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location) {
    CellTouchEnd(_cell, _touch, _location);
}

void ToppingContainer::CellUpdate(CellData *_cell, float _deltaTime) {
    ToppingContainerCellData* _data = (ToppingContainerCellData*)_cell->data;
    if(selectModel == _data->model) {
        _data->model->color.r = _data->model->color.g = _data->model->color.b = 0xFF;
    } else {
        _data->model->color.r = _data->model->color.g = _data->model->color.b = (iceCream->IsPossibleTopping(_data->type) && _data->step < _data->stepTotal) ? 0xFF : 0x88;
    }
    if(selectModel == _data->model && selectTweener == NULL) {
        if(!selectModel->is_play) {
            iceCream->AddTopping(_data->type);
            iceCream->GetClear();
            selectModel = NULL;
            SetEnable(true);
        } else {
            if(selectModel->cur_frame > 18) {
                if(selectInnerModel) {
                    selectInnerModel->gotoAndStop(selectInnerModel->cur_frame + 1);
                    selectInnerModel = NULL;
                }
            }
        }
    }
}

void ToppingContainer::ClearSelectTween() {
    if(selectTweenerParam) {
        if(selectTweener)
            selectTweener->removeTween(selectTweenerParam);
        delete selectTweenerParam;
    }
    selectTweenerParam = NULL;
    if(selectTweener) {
        delete selectTweener;
    }
    selectTweener = NULL;
    selectTweenerTimeCount = 0.0;
}

void ToppingContainer::UpdateSelectTween(float _deltaTime) {
    if(selectTweener) {
        selectTweenerTimeCount += _deltaTime;
        float _preValue = selectTweenerValue;
        selectTweener->step(selectTweenerTimeCount * 1000);
        pageValue += selectTweenerValue - _preValue;
        if(selectTweenerTimeCount > selectTweenerTime) {
            ClearSelectTween();
            if(selectModel) {
                selectModel->gotoAndPlay(0.0);
                if(selectInnerModel) {
                    selectInnerModel->stop();
                }
            }
        }
    }
}

void ToppingContainer::BeginSelectTween(float _value, float _time, bool _is_ease_out) {
    ClearSelectTween();
    selectTweener = new Tweener();
    selectTweenerTime = _time;
    selectTweenerValue = 0;
    ShowScrollBarMoment(_time);
    selectTweenerParam = new TweenerParam(selectTweenerTime * 1000, CUBIC, _is_ease_out ? EASE_IN_OUT : EASE_IN_OUT);
    selectTweenerParam->addProperty(&selectTweenerValue, _value);
    selectTweener->addTween(*selectTweenerParam);
}

void ToppingContainer::Update(float _deltaTime) {
    ScrollerContainer::Update(_deltaTime);
    UpdateSelectTween(_deltaTime);
}

ToppingContainer::ToppingContainer(VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data, IceCream* _iceCream) : ScrollerContainer(_objScroller, _texScroller, _data, 80, 270, 90, 5, 5, 5, ScrollerContainerAlign_HI, _data->len * 80 < 270) {
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellAlloc(_cellData);
        }
    }
    selectTweenerTime = selectTweenerTimeCount = 0.0;
    selectTweener = NULL;
    selectTweenerParam = NULL;
    selectInnerModel = selectModel = NULL;
    SetCook(_iceCream);
        
    printf("new topping container\n");
}

void ToppingContainer::SetCook(IceCream* _iceCream) {
    iceCream = _iceCream;
}

ToppingContainer::~ToppingContainer() {
    ClearSelectTween();
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellFree(_cellData);
        }
    }
    printf("topping container free\n");
}

float ToppingContainer::getToppingPositionX(int itemIdx)
{
    return (pageValue + itemIdx*cellSize);
}

