#include "RecipeContainer.h"
#include "ShareData.h"
#include "GameMain.h"

void RecipeContainer::CellAlloc(CellData* _data) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    _recipe->shelf = new VBModel(objShelf, nameIdShelf, texShelf, true);
    _recipe->shelf->setPosition(CCPointMake(41, -85+12.5));
    _data->modelCell->addChild(_recipe->shelf);
    
    FILE* _decompFile = fopen(VBStringGetCString(_recipe->texPath), "rb");
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
    _recipe->tex = VBTextureInitAndLoadWithImage(VBTextureAlloc(), _img);
    VBImageFree(&_img);
    
    _recipe->model = new VBModel(_recipe->obj, _recipe->name_id, _recipe->tex, true);
    _recipe->model->stop();
    _data->modelCell->addChild(_recipe->model);
    _recipe->model->setPosition(CCPointMake(41, -85+12.5));
}

void RecipeContainer::CellUpdate(CellData* _data, float _deltaTime) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    if(hitTarget->IsPossibleRecipe(_recipe->recipeIdx)) {
        _recipe->status = 0;
        _recipe->model->gotoAndStop(0);
    } else {
        _recipe->status = 1;
        _recipe->model->gotoAndStop(1);
    }
}

void RecipeContainer::CellFree(CellData* _data) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    _data->modelCell->removeChild(_recipe->model, false);
    delete _recipe->model;
    _recipe->model = NULL;
    
    _data->modelCell->removeChild(_recipe->shelf, false);
    delete _recipe->shelf;
    _recipe->shelf = NULL;
    
    VBTextureFree(&_recipe->tex);
}

void RecipeContainer::CellTouchBegin(CellData* _data, CCTouch* _touch, CCPoint _location) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    if(_recipe->status == 0) {
        TOUCHBEGINBT(_recipe->touch, _data->modelCell, _location, _touch, 
                     _recipe->startVec = VBVector2DCreate(_location.x, _location.y);
                     _recipe->preVec = VBVector2DCreate(_location.x, _location.y);
                     _recipe->swipe = 0.0;
                     );
    }
}

void RecipeContainer::CellTouchMove(CellData* _data, CCTouch* _touch, CCPoint _location) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    if(_recipe->touch == _touch) {
        _recipe->subVec = VBVector2DSubtract(VBVector2DCreate(_location.x, _location.y), _recipe->startVec);
        VBVector2D stepVec = VBVector2DSubtract(VBVector2DCreate(_location.x, _location.y), _recipe->preVec);
        _recipe->swipe += VBVector2DLength(stepVec);
        if(_recipe->swipe > 0.0) {
            float angle = VBVector2DAngle(_recipe->subVec);
            if((angle > M_PI - M_PI_4 && angle <= M_PI) || (angle < -M_PI + M_PI_4 && angle >= -M_PI)) {
                //Drag시작
                SetEnable(false);
                pour = new VBModel(_recipe->obj, _recipe->name_id, _recipe->tex, true);
                pour->is_use_animation = false;
                pour->color.a = 0xFF;
                pour->stop();
                pourTarget->addChild(pour);
                selectedRecipe = _recipe;
            }
            _recipe->touch = NULL;
        }
        _recipe->preVec = VBVector2DCreate(_location.x, _location.y);
    }
}

void RecipeContainer::CellTouchEnd(CellData* _data, CCTouch* _touch, CCPoint _location) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    TOUCHENDBT(_recipe->touch, _data->modelCell, _location, _touch, , );
    SetEnable(true);
}

void RecipeContainer::CellTouchCancel(CellData* _data, CCTouch* _touch, CCPoint _location) {
    RecipeContainerCellData* _recipe = (RecipeContainerCellData*)_data->data;
    TOUCHENDBT(_recipe->touch, _data->modelCell, _location, _touch, , );
    SetEnable(true);
}

RecipeContainerCellData* RecipeContainerCellDataInit(int _recipeIdx) {
    RecipeContainerCellData* _data = (RecipeContainerCellData*)calloc(1, sizeof(RecipeContainerCellData));
    VBString* _str;
    
    _data->recipeIdx = _recipeIdx;
    
    char* _recipe_name = cJSON_GetArrayItem(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "recipe"), _recipeIdx), 0)->valuestring;
    
    _data->texPath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/decomp_%s.png", VBStringGetCString(VBEngineGetDocumentPath()), _recipe_name);


    if(access(VBStringGetCString(_data->texPath), F_OK) != 0) {

        _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s.png", VBStringGetCString(VBEngineGetResourcePath()), _recipe_name);
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
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s.obj", VBStringGetCString(VBEngineGetResourcePath()), _recipe_name);
    _data->obj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
    VBStringFree(&_str);
    
    LIBNAMEFIND(_data->name_id, _data->obj, "obj", _str);
    
    return _data;
}

void RecipeContainerCellDataFree(RecipeContainerCellData** _ptr) {
    if(*_ptr) {
        VBObjectFile2DFree(&(*_ptr)->obj);
        remove(VBStringGetCString((*_ptr)->texPath));
        VBStringFree(&(*_ptr)->texPath);
        free(*_ptr);
        *_ptr = NULL;
    }
}

RecipeContainer::RecipeContainer(VBObjectFile2D* _objShelf, VBTexture* _texShelf, VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data, GameMain *_gameMain, VBModel* _pourTarget, IceCream* _hitTarget, void (*_hitFunc)(RecipeContainerCellData* _data)) : ScrollerContainer(_objScroller, _texScroller, _data, 85, 81, 280, 5) {
    objShelf = _objShelf;
    texShelf = _texShelf;
    gameMain = _gameMain;
    pourTarget = _pourTarget;
    hitTarget = _hitTarget;
    hitFunc = _hitFunc;
    VBString* _str;
    LIBNAMEFIND(nameIdShelf, objShelf, "Shelf", _str);
    
    recipeLen = VBArrayVectorGetLength(_data);
    recipeIndex = (int*)malloc(sizeof(int)*recipeLen);
    
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellAlloc(_cellData);
        }
    }
    
    for (int i=0; i<VBArrayVectorGetLength(_data); i++) {
        RecipeContainerCellData* _cellData = (RecipeContainerCellData*)VBArrayVectorGetDataAt(_data, i);
        recipeIndex[i] = _cellData->recipeIdx;
    }
    
    //printf("recipeIndex: ");
    //for (int i=0; i<recipeLen; i++) {
    //    printf("%d ", recipeIndex[i]);
    //}
    //printf("\n");
    
    pour = NULL;
    selectedRecipe = NULL;
    printf("new recipe container\n");
}

RecipeContainer::~RecipeContainer() {
    for(int i = 0; i < VBArrayVectorGetLength(cell); i++) {
        CellData* _cellData = (CellData*)VBArrayVectorGetDataAt(cell, i);
        if(_cellData->index >= 0 && _cellData->index < VBArrayVectorGetLength(data)) {
            CellFree(_cellData);
        }
    }
    free(recipeIndex);
    printf("delete recipe container\n");
}

void RecipeContainer::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    ScrollerContainer::touchEndAndCancel(_touch, _location);
    
    if(pour) {
        if(pour->hitTest(hitTarget)) {
            hitTarget->AddRecipe(selectedRecipe->recipeIdx);
            gameMain->recipeContainerCallBack(selectedRecipe->recipeIdx);
        }
        selectedRecipe = NULL;
        pourTarget->removeChild(pour, false);
        delete pour;
        pour = NULL;
    }
}

void RecipeContainer::touchMove(CCTouch* _touch, CCPoint _location) {
    ScrollerContainer::touchMove(_touch, _location);
    
    if(pour) {
        pour->setPosition(CCPointMake(_location.x, _location.y-320.0));
        if(pour->hitTest(hitTarget)) {
            pour->color.a = 0xFF;
        } else {
            pour->color.a = 0x88;
        }
    }
}

float RecipeContainer::getItemPositionY(int itemIdx)
{
    static int tempIdx = 0;
    static int tempValue = 0;
    if (itemIdx != tempValue) {
        int i=0;
        for (; i<recipeLen; i++) {
            if (itemIdx == recipeIndex[i]) {
                tempIdx = i;
                tempValue = recipeIndex[i];
                break;
            }
        }
    }
    
    return (-1 * (pageValue + tempIdx*cellSize));
}


