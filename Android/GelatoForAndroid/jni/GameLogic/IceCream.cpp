#include "IceCream.h"
#include "ShareData.h"
#include "png.h"
#include "zlib.h"
#include "GameMain.h"

typedef struct TS_idx {
    ToppingSpuit* _t;
    int _idx;
    VBAABB _aabb;
} TS_idx;

void IceCream::VBModelUpdate(float _tick) {
    Reshape();
}

IceCream::IceCream(GameMain *_gameMain, VBArrayVector* _rdVec, VBArrayVector* _tdVec, IceCream* _baseIceCream, int* _recipe, int _recipe_len) : VBModel(NULL) {
    
#ifdef TEST_AABB_AMOUNT
    VBAABB test1 = {0, 0, 10, 10};
    VBAABB test2 = {5, 5, 15, 15};
    VBAABB test3 = {5, 5, 15, 15};
    VBAABB test[3] = {test1, test2, test3};
    cout << VBAABBGetAmount(test1) << "\n";
    cout << VBAABBGetAmount(test2) << "\n";
    cout << VBAABBGetAmount(test3) << "\n";
    cout << "\n";
    
    VBAABB hit;
    bool isHit = VBAABBGetHitAABB(test1, test2, &hit);
    cout << isHit << "," << hit.l << "," << hit.t << "," << hit.r << "," << hit.b << "\n";
    cout << VBAABBGetAmount(hit) << "\n";
    cout << "\n";
    
    isHit = VBAABBGetHitAABB(test2, test3, &hit);
    cout << isHit << "," << hit.l << "," << hit.t << "," << hit.r << "," << hit.b << "\n";
    cout << VBAABBGetAmount(hit) << "\n";
    cout << "\n";
    
    isHit = VBAABBGetHitAABB(test1, test3, &hit);
    cout << isHit << "," << hit.l << "," << hit.t << "," << hit.r << "," << hit.b << "\n";
    cout << VBAABBGetAmount(hit) << "\n";
    cout << "\n";
    
    cout << VBAABBGetAmountAtManyBox(3, test) << "\n";
#endif
    
    gameMain = _gameMain;
    rdVec = _rdVec;
    tdVec = _tdVec;
    
    baseIceCream = _baseIceCream;
    isClear = 0;
    totalClear = 0;
    
    VBString* _str;
    cJSON* _js;
    
    VBAABB aabb = VBAABBLoadIndentity();
    _js = ShareDataGetTemplateData(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "base"), 0));
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_js, "path")->valuestring);
    imgBGOrigin = VBImageInitWithPath(VBImageAlloc(), _str);
    imgBG = VBImageInitAndClear(VBImageAlloc(), imgBGOrigin->color_type, imgBGOrigin->color_bit, imgBGOrigin->width, imgBGOrigin->height);
    texBG = VBTextureInitAndLoadWithImage(VBTextureAlloc(), imgBG);
    VBStringFree(&_str);
    modelBG = new VBModel(texBG);
    aabb = aabbBitmask = aabbBG = JStoAABB(_js);
    modelBG->setPosition(CCPointMake(aabb.l - texBG->shiftX, -aabb.t + texBG->shiftY));
    
    _js = ShareDataGetTemplateData(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "base"), 1));
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_js, "path")->valuestring);
    texBgOutline = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    modelBgOutline = new VBModel(texBgOutline);
    aabb = JStoAABB(_js);
    modelBgOutline->setPosition(CCPointMake(aabb.l - texBgOutline->shiftX, -aabb.t + texBgOutline->shiftY));
    
    _js = ShareDataGetTemplateData(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "base"), 2));
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_js, "path")->valuestring);
    imgBridgeOrigin = VBImageInitWithPath(VBImageAlloc(), _str);
    imgBridge = VBImageInitAndClear(VBImageAlloc(), imgBridgeOrigin->color_type, imgBridgeOrigin->color_bit, imgBridgeOrigin->width, imgBridgeOrigin->height);
    texBridge = VBTextureInitAndLoadWithImage(VBTextureAlloc(), imgBridge);
    VBStringFree(&_str);
    modelBridge = new VBModel(texBridge);
    aabb = aabbBridge = JStoAABB(_js);
    modelBridge->setPosition(CCPointMake(aabb.l - texBridge->shiftX, -aabb.t + texBridge->shiftY));
    
    _js = ShareDataGetTemplateData(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "base"), 3));
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_js, "path")->valuestring);
    texBridgeOutline = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    modelBridgeOutline = new VBModel(texBridgeOutline);
    aabb = JStoAABB(_js);
    modelBridgeOutline->setPosition(CCPointMake(aabb.l - texBridgeOutline->shiftX, -aabb.t + texBridgeOutline->shiftY));
    
    addChild(modelBgOutline);
    addChild(modelBG);
    
    imgBitmask = VBImageInitAndClear(VBImageAlloc(), VBColorType_RGBA, 8, VBAABBGetWidth(aabbBitmask), VBAABBGetHeight(aabbBitmask));
    bitmaskMerge = 0;
    
    mask = VBArrayVectorInit(VBArrayVectorAlloc());
    
    modelLastRecipe = NULL;
    modelLastRecipeBridge = NULL;
    
    subTopping = VBArrayVectorInit(VBArrayVectorAlloc());
    VBArrayVectorAddBack(subTopping, NULL);
    VBArrayVectorAddBack(subTopping, NULL);
    VBArrayVectorAddBack(subTopping, NULL);
    
    subToppingFlow = VBArrayVectorInit(VBArrayVectorAlloc());
    VBArrayVectorAddBack(subToppingFlow, VBArrayVectorInit(VBArrayVectorAlloc()));
    VBArrayVectorAddBack(subToppingFlow, VBArrayVectorInit(VBArrayVectorAlloc()));
    VBArrayVectorAddBack(subToppingFlow, VBArrayVectorInit(VBArrayVectorAlloc()));
    
    toppingSpuitL = VBArrayVectorInit(VBArrayVectorAlloc());
    toppingSpuitR = VBArrayVectorInit(VBArrayVectorAlloc());
    toppingFlow = VBArrayVectorInit(VBArrayVectorAlloc());
    toppingCream = NULL;
    toppingCherry = NULL;
    
    thumbs = VBArrayVectorInit(VBArrayVectorAlloc());
    
    modelTop = NULL;
    
    next = NULL;
    prev = NULL;
    
    need_update_pixel = false;
    need_update_bitmask = false;
    need_update_model = false;
    
    if(_recipe) {
        for(int i = 0; i < _recipe_len; i++)
            AddRecipe(_recipe[i]);
    } else {
        AddRecipe(0);
    }
}

IceCream::~IceCream() {
    if(getChildren()) {
        while(getChildren()->count()) {
            removeChild((VBModel*)getChildren()->objectAtIndex(0), false);
        }
    }
    
    if(next) {
        delete next;
        next = NULL;
    }
    
    while(VBArrayVectorGetLength(subToppingFlow)) {
        VBArrayVector* _vec = (VBArrayVector*)VBArrayVectorRemoveBack(subToppingFlow);
        VBArrayVectorFree(&_vec);
    }
    VBArrayVectorFree(&subToppingFlow);
    
    VBArrayVectorFree(&subTopping);
    
    while (VBArrayVectorGetLength(toppingSpuitL)) {
        free((void*)VBArrayVectorRemoveBack(toppingSpuitL));
    }
    VBArrayVectorFree(&toppingSpuitL);
    while (VBArrayVectorGetLength(toppingSpuitR)) {
        free((void*)VBArrayVectorRemoveBack(toppingSpuitR));
    }
    VBArrayVectorFree(&toppingSpuitR);
    
    VBArrayVectorFree(&toppingFlow);
    
    ClearMask(NULL, -1);
    VBArrayVectorFree(&mask);
    
    while(VBArrayVectorGetLength(thumbs)) {
        Thumbs* _t = (Thumbs*)VBArrayVectorRemoveBack(thumbs);
        ThumbsFree(&_t);
    }
    VBArrayVectorFree(&thumbs);
    
    VBImageFree(&imgBitmask);
    
    delete modelBridge;
    delete modelBridgeOutline;
    VBTextureFree(&texBridge);
    VBImageFree(&imgBridge);
    VBTextureFree(&texBridgeOutline);
    
    delete modelBG;
    delete modelBgOutline;
    
    VBTextureFree(&texBG);
    VBImageFree(&imgBG);
    VBTextureFree(&texBgOutline);
    VBImageFree(&imgBridgeOrigin);
    VBImageFree(&imgBGOrigin);
    
    if(modelLastRecipe)
        delete modelLastRecipe;
    if(modelLastRecipeBridge)
        delete modelLastRecipeBridge;
}

void IceCream::Reshape() {
    if(next)
        next->Reshape();
    else {
        
        if(need_update_bitmask) {
            bitmaskMerge = 0;
            
            isClear = 0;
            totalClear = 0;
            
            for(int i = 0; i < VBImageGetWidth(imgBitmask); i++) {
                for(int j = 0; j < VBImageGetHeight(imgBitmask); j++) {
                    unsigned long* _bm = (unsigned long*)VBImageGetPixelColor(imgBitmask, i, j);
                    bitmaskMerge |= *_bm;
                    if(*_bm != 0)
                        totalClear++;
                    if(baseIceCream) {
                        unsigned long* _base_bm = (unsigned long*)VBImageGetPixelColor(baseIceCream->imgBitmask, i, j);
                        if(*_base_bm != 0 && *_bm != 0) {
                            if(*_bm == *_base_bm)
                                isClear++;
                        }
                    }
                }
            }
            
            need_update_bitmask = false;
        }
        
        if(need_update_pixel) {
            VBTextureUnload(texBG);
            VBTextureLoadImage(texBG, imgBG);
            modelBG->SetTexture(texBG);
            
            VBTextureUnload(texBridge);
            VBTextureLoadImage(texBridge, imgBridge);
            modelBridge->SetTexture(texBridge);
            
            need_update_pixel = false;
        }
        
        if(need_update_model) {
            if(getChildren()) {
                while(getChildren()->count()) {
                    removeChild((VBModel*)getChildren()->objectAtIndex(0), false);
                }
            }
            addChild(modelBgOutline);
            addChild(modelBG);
            
            if(modelLastRecipe) {
                addChild(modelLastRecipe);
            }
            
            for(int i = 0; i < VBArrayVectorGetLength(thumbs); i++) {
                Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
                if(_t->attach)
                    addChild(_t->model);
            }
            
            need_update_model = false;
        }
    }
}

int GetToppingSpuitLastIdx(VBArrayVector* _vec, ToppingSpuit* _t) {
    int idx = -1;
    for (int i = 0; i < _vec->len; i++) {
        if(_t == _vec->data[i])
            idx++;
    }
    return idx;
}

float IceCream::GetClear() {
    cout << "\n";
    
    VBAABB* aabb = NULL;
    int aabbIdx = 0;
    
    /*******************bg***********************/
    cout << "\n";
    cout << "< GetClear bg >\n";
    
    Reshape();
    
    unsigned long _clear = 0;
    unsigned long _totalClear = 0;
    
    IceCream* _link = this;
    IceCream* _linkBase = baseIceCream;
    
    VBVector2D _vec = VBVector2DCreate(0, 0);
    
    while(_link || _linkBase) {
//        if(_link)
//            aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_link->aabbBG, _vec), aabbIdx, ++aabbIdx);
        if(_linkBase)
            aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_linkBase->aabbBG, _vec), aabbIdx, ++aabbIdx);
        
        if(_link)
            _clear += _link->isClear;
        _totalClear += _link ? _link->totalClear : _linkBase->totalClear;
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float bg_amount = VBAABBGetAmountAtManyBox(aabbIdx, aabb);
    
    float _bgPer = (float)_clear / _totalClear;
    _bgPer = isnan(_bgPer) ? 0 : _bgPer;
    cout << "_bgPer:" << _bgPer << "\n";
    
    
    
    /*******************maskThumb***********************/
    cout << "\n";
    cout << "< GetClear maskThumb >\n";
    
    VBAABB* mask_aabb = NULL;
    int mask_aabbIdx = 0;
    
    unsigned long _maskThumb = 0;
    unsigned long _maskThumbTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        for(int i = 0; i < MAX((_link ? _link->mask->len : 0), (_linkBase ? _linkBase->mask->len : 0)); i++) {
            void* _data = NULL;
            if(i < (_link ? _link->mask->len : 0)) {
                _data = _link->mask->data[i];
//                RecipeMask* _r = (RecipeMask*)_data;
//                aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_r->aabbThumb, _vec), aabbIdx, ++aabbIdx);
//                mask_aabb = VBAABBMemResizeAndSet(mask_aabb, VBAABBShift(_r->aabbThumb, _vec), mask_aabbIdx, ++mask_aabbIdx);
            }
            void* _dataBase = NULL;
            if(i < (_linkBase ? _linkBase->mask->len : 0)) {
                _dataBase = _linkBase->mask->data[i];
                RecipeMask* _r = (RecipeMask*)_dataBase;
                aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_r->aabbThumb, _vec), aabbIdx, ++aabbIdx);
                mask_aabb = VBAABBMemResizeAndSet(mask_aabb, VBAABBShift(_r->aabbThumb, _vec), mask_aabbIdx, ++mask_aabbIdx);
            }
            if(_data && _dataBase) {
                if(_data == _dataBase)
                    _maskThumb++;
            }
            _maskThumbTotal++;
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float mask_amount = VBAABBGetAmountAtManyBox(mask_aabbIdx, mask_aabb);
    
    float _maskThumbPer = (float)_maskThumb / (float)_maskThumbTotal;
    _maskThumbPer = isnan(_maskThumbPer) ? 0 : _maskThumbPer;
    cout << "_maskThumbPer:" << _maskThumbPer << ", _maskThumb:" << _maskThumb << ", _maskThumbTotal:" << _maskThumbTotal << "\n";
    
    if(mask_aabb)
        free(mask_aabb);
    
    
    /*******************subTopping***********************/
    cout << "\n";
    cout << "< GetClear subTopping >\n";
    
    VBAABB* subTopping_aabb = NULL;
    int subTopping_aabbIdx = 0;
    
    unsigned long _subTopping = 0;
    unsigned long _subToppingTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        for(int i = MAX((_link ? _link->subTopping->len : 0), (_linkBase ? _linkBase->subTopping->len : 0)) - 1; i > -1 ; i--) {
            void* _data = NULL;
            if(i < (_link ? _link->subTopping->len : 0)) {
                _data = _link->subTopping->data[i];
            }
            void* _dataBase = NULL;
            if(i < (_linkBase ? _linkBase->subTopping->len : 0)) {
                _dataBase = _linkBase->subTopping->data[i];
            }
            if(_data) {
//                RecipeSubTopping* _r = (RecipeSubTopping*)_data;
//                aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_r->aabbThumb, _vec), aabbIdx, ++aabbIdx);
//                subTopping_aabb = VBAABBMemResizeAndSet(subTopping_aabb, VBAABBShift(_r->aabbThumb, _vec), subTopping_aabbIdx, ++subTopping_aabbIdx);
            }
            if(_dataBase) {
                RecipeSubTopping* _r = (RecipeSubTopping*)_dataBase;
                aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_r->aabbThumb, _vec), aabbIdx, ++aabbIdx);
                subTopping_aabb = VBAABBMemResizeAndSet(subTopping_aabb, VBAABBShift(_r->aabbThumb, _vec), subTopping_aabbIdx, ++subTopping_aabbIdx);
            }
            if(_data && _dataBase) {
                if(_data == _dataBase)
                    _subTopping++;
            }
            _subToppingTotal++;
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float subTopping_amount = VBAABBGetAmountAtManyBox(subTopping_aabbIdx, subTopping_aabb);
    
    float _subToppingPer = (float)_subTopping / (float)_subToppingTotal;
    _subToppingPer = isnan(_subToppingPer) ? 0 : _subToppingPer;
    cout << "_subToppingPer:" << _subToppingPer << ", _subTopping:" << _subTopping << ", _subToppingTotal:" << _subToppingTotal << "\n";
    
    if(subTopping_aabb)
        free(subTopping_aabb);
    
    
    /*******************subToppingFlow***********************/
    cout << "\n";
    cout << "< GetClear subToppingFlow >\n";
    
    VBAABB* subToppingFlow_aabb = NULL;
    int subToppingFlow_aabbIdx = 0;
    
    unsigned long _subToppingFlow = 0;
    unsigned long _subToppingFlowTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        for(int i = 0; i < MAX((_link ? _link->subToppingFlow->len : _linkBase->subToppingFlow->len), (_linkBase ? _linkBase->subToppingFlow->len : _link->subToppingFlow->len)); i++) {
            VBArrayVector* _arr = NULL;
            if(_link)
                _arr = (VBArrayVector*)VBArrayVectorGetDataAt(_link->subToppingFlow, i);
            VBArrayVector* _arrBase = NULL;
            if(_linkBase)
                _arrBase = (VBArrayVector*)VBArrayVectorGetDataAt(_linkBase->subToppingFlow, i);
            for(int j = 0; j < MAX((_arr ? _arr->len : 0), (_arrBase ? _arrBase->len : 0)); j++) {
                void* _data = NULL;
                if(j < (_arr ? _arr->len : 0)) {
                    _data = _arr->data[j];
                    //                    RecipeSubToppingFlow* _r = (RecipeSubToppingFlow*)_data;
                    //                    aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_r->aabbThumb[j], _vec), aabbIdx, ++aabbIdx);
                    //                    subToppingFlow_aabb = VBAABBMemResizeAndSet(subToppingFlow_aabb, VBAABBShift(_r->aabbThumb[j], _vec), subToppingFlow_aabbIdx, ++subToppingFlow_aabbIdx);
                }
                void* _dataBase = NULL;
                if(j < (_arrBase ? _arrBase->len : 0)) {
                    _dataBase = _arrBase->data[j];
                    RecipeSubToppingFlow* _r = (RecipeSubToppingFlow*)_dataBase;
                    aabb = VBAABBMemResizeAndSet(aabb, VBAABBShift(_r->aabbThumb[j], _vec), aabbIdx, ++aabbIdx);
                    subToppingFlow_aabb = VBAABBMemResizeAndSet(subToppingFlow_aabb, VBAABBShift(_r->aabbThumb[j], _vec), subToppingFlow_aabbIdx, ++subToppingFlow_aabbIdx);
                }
                //cout << j << ":" << _data << ", " << _dataBase;
                if(_data && _dataBase) {
                    if(_data == _dataBase) {
                        _subToppingFlow++;
                        //cout << " is Equal";
                    }
                }
                //cout << "\n";
                _subToppingFlowTotal++;
            }
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float subToppingFlow_amount = VBAABBGetAmountAtManyBox(subToppingFlow_aabbIdx, subToppingFlow_aabb);
    
    float _subToppingFlowPer = (float)_subToppingFlow / (float)_subToppingFlowTotal;
    _subToppingFlowPer = isnan(_subToppingFlowPer) ? 0 : _subToppingFlowPer;
    cout << "_subToppingFlowPer:" << _subToppingFlowPer << ", _subToppingFlow:" << _subToppingFlow << ", _subToppingFlowTotal:" << _subToppingFlowTotal << "\n";
    
    if(subToppingFlow_aabb)
        free(subToppingFlow_aabb);
//    
//    
//    while (_link || _linkBase) {
//        TS_idx _tiL[0xFF] = {NULL,};
//        int _tiL_idx = 0;
//        TS_idx _tiLBase[0xFF] = {NULL,};
//        int _tiLBase_idx = 0;
//        
//        TS_idx _tiR[0xFF] = {NULL,};
//        int _tiR_idx = 0;
//        TS_idx _tiRBase[0xFF] = {NULL,};
//        int _tiRBase_idx = 0;
//        
//        int _lid = 0;
//        int _rid = 0;
//        
//        if(_link) {
//            _lid = 0;
//            for(int i = _link->toppingSpuitL->len - 1; i < -1; i--) {
//                TS_idx* _ti = (TS_idx*)_link->toppingSpuitL->data[i];
//                if(_lid < _ti->_idx) {
//                    _lid = _ti->_idx;
//                    _tiL[_tiL_idx] = *_ti;
//                    _tiL_idx++;
//                }
//            }
//            _rid = 0;
//            for(int i = _link->toppingSpuitR->len - 1; i < -1; i--) {
//                TS_idx* _ti = (TS_idx*)_link->toppingSpuitR->data[i];
//                if(_rid < _ti->_idx) {
//                    _rid = _ti->_idx;
//                    _tiR[_tiR_idx] = *_ti;
//                    _tiR_idx++;
//                }
//            }
//        }
//        
//        if(_linkBase) {
//            _lid = 0;
//            for(int i = _linkBase->toppingSpuitL->len - 1; i < -1; i--) {
//                TS_idx* _ti = (TS_idx*)_linkBase->toppingSpuitL->data[i];
//                if(_lid < _ti->_idx) {
//                    _lid = _ti->_idx;
//                    _tiLBase[_tiLBase_idx] = *_ti;
//                    _tiLBase_idx++;
//                }
//            }
//            _rid = 0;
//            for(int i = _linkBase->toppingSpuitR->len - 1; i < -1; i--) {
//                TS_idx* _ti = (TS_idx*)_linkBase->toppingSpuitR->data[i];
//                if(_rid < _ti->_idx) {
//                    _rid = _ti->_idx;
//                    _tiRBase[_tiRBase_idx] = *_ti;
//                    _tiRBase_idx++;
//                }
//            }
//        }
//    }
//    
//    
    
    float amount = VBAABBGetAmountAtManyBox(aabbIdx, aabb);
    if(aabb)
        free(aabb);
    
    
    
    
    /*******************print***********************/
    cout << "\n";
    int sum = bg_amount + subToppingFlow_amount + subTopping_amount + mask_amount;
    cout << amount << ", " << bg_amount << ", " << subToppingFlow_amount << ", " << subTopping_amount << ", " << mask_amount << "\n";
    
    cout << "아이스크림 기본 색상 칼라 일치율:" << _bgPer * 100 << "%, 해답에서의 영역비율:" << (100 * (bg_amount / sum)) << "%\n";
    cout << "여러개 쌓을수 있는 작은 아이스크림 일치율:" << _subToppingFlowPer * 100 << "%, 해답에서의 영역비율:" << (100 * (subToppingFlow_amount / sum)) << "%\n";
    cout << "한개만 쌓을수 있는 작은 쿠키 일치율:" << _subToppingPer * 100 << "%, 해답에서의 영역비율:" << (100 * (subTopping_amount / sum)) << "%\n";
    cout << "마스크 올라간 상태 일치율:" << _maskThumbPer * 100 << "%, 해답에서의 영역비율:" << (100 * (mask_amount / sum)) << "%\n";
    
    return _bgPer;
}

unsigned int IceCream::GetHeight() {
    unsigned int _h = 0;
    IceCream* _link = this;
    while(_link) {
        if(_link->prev) {
            _h += NEXT_ICECREAM_Y;
        } else {
            _h += VBTextureGetHeight(_link->texBG);
        }
        _link = _link->next;
    }
    return _h;
}

bool IceCream::IsEqual(IceCream* _other) {
    return false;
}

void IceCream::SaveImage(char* _fileName) {
    /*
    unsigned int _w = VBTextureGetWidth(tex);
    unsigned int _h = GetHeight();
    
    VBImage* _writeImg = VBImageInitAndClear(VBImageAlloc(), VBColorType_RGBA, VBImageGetColorBit(iceCream), _w, _h);
    IceCream* _link = this;
    
    float y = _h;
    
    while(_link) {
        _link->Reshape();
        VBColorRGBA* _iceCreamBridge = NULL;
        if(_link->prev) {
            y -= NEXT_ICECREAM_Y;
            _iceCreamBridge = (VBColorRGBA*)VBImageGetImageData(_link->prev->imgBridge);
        } else {
            y -= VBTextureGetHeight(_link->tex);
        }
        
        VBColorRGBA* _iceCream = (VBColorRGBA*)VBImageGetImageData(_link->texImage);
        for(int j = 0; j < VBImageGetHeight(_link->texImage); j++) {
            for(int i = 0; i < VBImageGetWidth(_link->texImage); i++) {
                VBColorRGBA* _color = (VBColorRGBA*)VBImageGetPixelColor(_writeImg, i, y + j);
                *_color = VBColorRGBADrawNormal(*_color, *_iceCream);
                _iceCream++;
            }
        }
        
        if(_iceCreamBridge) {
            for(int j = 0; j < VBImageGetHeight(_link->texImage); j++) {
                for(int i = 0; i < VBImageGetWidth(_link->texImage); i++) {
                    float yBridge = y + NEXT_ICECREAM_Y;
                    VBColorRGBA* _color = (VBColorRGBA*)VBImageGetPixelColor(_writeImg, i, yBridge + j);
                    if(_iceCreamBridge) {
                        *_color = VBColorRGBADrawNormal(*_color, *_iceCreamBridge);
                        _iceCreamBridge++;
                    }
                }
            }
        }
        _link = _link->next;
    }
    
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetDocumentPath()), _fileName);
    FILE* _file = fopen(VBStringGetCString(_str), "w+");
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t __x, __y;
    png_byte ** row_pointers = NULL;
    */
    
    /* "status" contains the return value of this function. At first
     it is set to a value which means 'failure'. When the routine
     has finished its work, it is set to a value which means
     'success'. */
    //int status = -1;
    /* The following number is set by trial and error only. I cannot
     see where it it is documented in the libpng manual.
     */
    /*
    int depth = 8;
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf (png_ptr));
    png_set_IHDR(png_ptr,
                 info_ptr,
                 _w,
                 _h,
                 depth,
                 PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    
    row_pointers = (png_byte**)png_malloc (png_ptr, _h * sizeof(png_byte*));
    for (__y = 0; __y < _h; __y++) {
        png_byte *row =  (png_byte *)png_malloc(png_ptr, _w * sizeof(unsigned char) * 4);
        row_pointers[__y] = row;
        for (__x = 0; __x < _w; __x++) {
            VBColorRGBA * pixel = (VBColorRGBA *)VBImageGetPixelColor(_writeImg, __x, __y);
            *row++ = pixel->r;
            *row++ = pixel->g;
            *row++ = pixel->b;
            *row++ = pixel->a;
        }
    }
    
    png_init_io (png_ptr, _file);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    status = 0;
    
    for (__y = 0; __y < _h; __y++) {
        png_free (png_ptr, row_pointers[__y]);
    }
    png_free (png_ptr, row_pointers);
    
    png_destroy_write_struct (&png_ptr, &info_ptr);
    
    fclose(_file);
    
    VBImageFree(&_writeImg);
    VBStringFree(&_str);
     */
}

void IceCream::FillCream(VBImage* _imgArea, VBAABB _aabbArea, VBImage* _imgMask, VBAABB _aabbMask, int _shiftBit, int _hex) {
    if(next) {
        FillCream(_imgArea, _aabbArea, _imgMask, _aabbMask, _shiftBit, _hex);
    } else {
        VBColorRGBA* _src = (VBColorRGBA*)VBImageGetImageData(imgBGOrigin);
        VBColorRGBA* _dst = (VBColorRGBA*)VBImageGetImageData(imgBG);
        
        for(int j = 0; j < VBImageGetHeight(imgBGOrigin); j++) {
            for(int i = 0; i < VBImageGetWidth(imgBGOrigin); i++) {
                VBUChar _a = 0xFF;
                
                if(VBAABBHitTest(aabbBG, _aabbArea)) {
                    VBColorRGBA* _mc = (VBColorRGBA*)VBImageGetPixelColor(_imgArea, (float)i + (aabbBG.l - _aabbArea.l), (float)j + (aabbBG.t - _aabbArea.t));
                    if(_mc)
                        _a = _a * ((float)_mc->a/0xFF);
                    else
                        _a = 0x00;
                } else {
                    _a = 0x00;
                }
                
                if(_imgMask) {
                    if(VBAABBHitTest(aabbBG, _aabbMask)) {
                        VBColorRGBA* _mc = (VBColorRGBA*)VBImageGetPixelColor(_imgMask, (float)i + (aabbBG.l - _aabbMask.l), (float)j + (aabbBG.t - _aabbMask.t));
                        if(_mc)
                            _a = _a * ((float)_mc->a/0xFF);
                        else
                            _a = 0x00;
                    } else {
                        _a = 0x00;
                    }
                }
                
                for(int k = 0; k < VBArrayVectorGetLength(mask); k++) {
                    RecipeMask* _mask = (RecipeMask*)VBArrayVectorGetDataAt(mask, k);
                    if(VBAABBHitTest(aabbBG, _mask->aabbMask)) {
                        VBColorRGBA* _mc = (VBColorRGBA*)VBImageGetPixelColor(_mask->imgMask, i + (aabbBG.l - _mask->aabbMask.l), j + (aabbBG.t - _mask->aabbMask.t));
                        if(_mc)
                            _a = _a * ((float)_mc->a/0xFF);
                        else
                            _a = 0x00;
                    } else {
                        _a = 0x00;
                    }
                }
                VBColorRGBA _tmp = VBColorRGBADrawColor(*_src, _hex, 0x9E, 0xEE);
                _tmp.a = (_tmp.a / (float)0xFF) * (_a / (float)0xFF) * 0xFF;
                *_dst = VBColorRGBADrawNormal(*_dst, _tmp);
                
                //비트마스크 덮을때(믹스할때) 마스크영역 무시하고 해야함(필요하다면) : FillCream 인자가 하나 더 필요 할 수도
                
                unsigned long* _bmColor = (unsigned long*)VBImageGetPixelColor(imgBitmask, i, j);
                if(_tmp.a > 0x88)
                    *_bmColor = _shiftBit;
                
                _src++;
                _dst++;
            }
        }
        
        VBColorRGBA* _srcBrd = (VBColorRGBA*)VBImageGetImageData(imgBridgeOrigin);
        VBColorRGBA* _dstBrd = (VBColorRGBA*)VBImageGetImageData(imgBridge);
        
        for(int j = 0; j < VBImageGetHeight(imgBridgeOrigin); j++) {
            for(int i = 0; i < VBImageGetWidth(imgBridgeOrigin); i++) {
                VBUChar _a = 0xFF;
                
                if(VBAABBHitTest(aabbBridge, _aabbArea)) {
                    VBColorRGBA* _mc = (VBColorRGBA*)VBImageGetPixelColor(_imgArea, (float)i + (aabbBridge.l - _aabbArea.l), (float)j + (aabbBridge.t - _aabbArea.t));
                    if(_mc)
                        _a = _a * ((float)_mc->a/0xFF);
                    else
                        _a = 0x00;
                } else {
                    _a = 0x00;
                }
                
                if(_imgMask) {
                    if(VBAABBHitTest(aabbBridge, _aabbMask)) {
                        VBColorRGBA* _mc = (VBColorRGBA*)VBImageGetPixelColor(_imgMask, (float)i + (aabbBridge.l - _aabbMask.l), (float)j + (aabbBridge.t - _aabbMask.t));
                        if(_mc)
                            _a = _a * ((float)_mc->a/0xFF);
                        else
                            _a = 0x00;
                    } else {
                        _a = 0x00;
                    }
                }
                
                for(int k = 0; k < VBArrayVectorGetLength(mask); k++) {
                    RecipeMask* _mask = (RecipeMask*)VBArrayVectorGetDataAt(mask, k);
                    if(VBAABBHitTest(aabbBridge, _mask->aabbMask)) {
                        VBColorRGBA* _mc = (VBColorRGBA*)VBImageGetPixelColor(_mask->imgMask, i + (aabbBridge.l - _mask->aabbMask.l), j + (aabbBridge.t - _mask->aabbMask.t));
                        if(_mc)
                            _a = _a * ((float)_mc->a/0xFF);
                        else
                            _a = 0x00;
                    } else {
                        _a = 0x00;
                    }
                }
                VBColorRGBA _tmp = VBColorRGBADrawColor(*_srcBrd, _hex, 0x9E, 0xEE);
                _tmp.a = (_tmp.a / (float)0xFF) * (_a / (float)0xFF) * 0xFF;
                *_dstBrd = VBColorRGBADrawNormal(*_dstBrd, _tmp);
                
                _srcBrd++;
                _dstBrd++;
            }
        }
    }
}

void IceCream::FillCream(RecipeFill* _rf, int _isMix) {
    if(next) {
        next->FillCream(_rf, _isMix);
    } else {
        FillCream(_rf->imgMask, _rf->aabb, NULL, VBAABBLoadIndentity(), 0x01 << _rf->idx, _rf->colorHex);
    }
}

void IceCream::AddMask(RecipeMask* _rm) {
    if(next) {
        next->AddMask(_rm);
    } else {
        VBArrayVectorAddBack(thumbs, ThumbsInit(_rm->texThumb, _rm->aabbThumb, 1, _rm, true));
        VBArrayVectorAddBack(mask, _rm);
    }
}

int IceCream::ClearMask(RecipeMask* _rm, int _num) {
    if(next) {
        return next->ClearMask(_rm, _num);
    } else {
        int _removed = 0;
        _num = _num < 0 ? VBArrayVectorGetLength(mask) : _num;
        for(int i = VBArrayVectorGetLength(mask) - 1; i > -1; i--) {
            RecipeMask* _rmV = (RecipeMask*)VBArrayVectorGetDataAt(mask, i);
            if(_rm == _rmV || _rm == NULL) {
                for(int j = 0; j < VBArrayVectorGetLength(thumbs); j++) {
                    Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, j);
                    if(_t->targ == _rmV) {
                        if(getChildren()) {
                            if(getChildren()->indexOfObject(_t->model) != UINT_MAX)
                                removeChild(_t->model, false);
                        }
                        VBArrayVectorRemoveAt(thumbs, j);
                        ThumbsFree(&_t);
                        break;
                    }
                }
                VBArrayVectorRemoveAt(mask, i);
                _removed++;
                if(_removed >= _num)
                    break;
            }
        }
        return _removed;
    }
}

bool IceCream::AddSubTopping(RecipeSubTopping* _rst) {
    if(next) {
        return next->AddSubTopping(_rst);
    } else {
        VBArrayVector* _vec = (VBArrayVector*)VBArrayVectorGetDataAt(subToppingFlow, _rst->idx);
        if(VBArrayVectorGetDataAt(subTopping, _rst->idx) == NULL && VBArrayVectorGetLength(_vec) == 0) {
            VBArrayVectorAddBack(thumbs, ThumbsInit(_rst->texThumb, _rst->aabbThumb, 3, _rst, true));
            VBArrayVectorReplaceAt(subTopping, _rst, _rst->idx);
            return true;
        } else {
            return false;
        }
    }
}

bool IceCream::AddSubToppingFlow(RecipeSubToppingFlow* _rstf) {
    if(next) {
        return next->AddSubToppingFlow(_rstf);
    } else {
        VBArrayVector* _vec = (VBArrayVector*)VBArrayVectorGetDataAt(subToppingFlow, _rstf->idx);
        if(_vec->len < _rstf->len && VBArrayVectorGetDataAt(subTopping, _rstf->idx) == NULL) {
            VBArrayVectorAddBack(thumbs, ThumbsInit(_rstf->texThumb[_vec->len], _rstf->aabbThumb[_vec->len], 2, _rstf, true));
            VBArrayVectorAddBack(_vec, _rstf);
            return true;
        } else {
            return false;
        }
    }
}

void IceCream::Mix(RecipeMix* _rm) {
    if(next) {
        next->Mix(_rm);
    } else {
        unsigned long _bitLoop = 0x01;
        int mixMaskType = 0;
        int bitmaskType = 0;
        while(_bitLoop <= bitmaskMerge) {
            if(_bitLoop & bitmaskMerge) {
                if(mixMaskType == 0) {
                    FillCream(_rm->img, _rm->aabb, NULL, VBAABBLoadIndentity(), bitmaskMerge, hexToInt(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "fill"), bitmaskType)->valuestring));
                } else {
                    FillCream(_rm->img, _rm->aabb, _rm->imgMask[mixMaskType], _rm->aabbMask[mixMaskType], bitmaskMerge, hexToInt(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "fill"), bitmaskType)->valuestring));
                }
                mixMaskType++;
            }
            bitmaskType++;
            _bitLoop = _bitLoop << 1;
        }
        
    }
}

void IceCream::SetLast(RecipeLast* _rl) {
    if(next) {
        next->SetLast(_rl);
    } else {
        modelLastRecipe = new VBModel(_rl->tex);
        modelLastRecipe->setPosition(CCPointMake(_rl->aabb.l - _rl->tex->shiftX, -_rl->aabb.t + _rl->tex->shiftY));
        
        modelLastRecipeBridge = new VBModel(_rl->texBridge);
        modelLastRecipeBridge->setPosition(CCPointMake(_rl->aabbBridge.l - _rl->texBridge->shiftX, -_rl->aabbBridge.t + _rl->texBridge->shiftY));
    }
}

bool IceCream::AddRecipe(int _recipe) {
    if(next) {
        return next->AddRecipe(_recipe);
    } else {
        RT* _rtF = NULL;
        for(int i = 0; i < VBArrayVectorGetLength(rdVec); i++) {
            RT* _rt = (RT*)VBArrayVectorGetDataAt(rdVec, i);
            if(_rt->idx == _recipe) {
                _rtF = _rt;
                break;
            }
        }
        
        if(_rtF) {
            switch(_rtF->type) {
                case 0: 
                {
                    RecipeFill* _rf = (RecipeFill*)_rtF->data;
                    FillCream(_rf, false);
                    need_update_pixel = true;
                    need_update_bitmask = true;
                    Reshape();
                }
                    break;
                case 1:
                {
                    RecipeMask* _rmk = (RecipeMask*)_rtF->data;
                    if(ClearMask(_rmk, 1) == 0)
                        AddMask(_rmk);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 2:
                {
                    RecipeSubToppingFlow* _rstf = (RecipeSubToppingFlow*)_rtF->data;
                    AddSubToppingFlow(_rstf);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 3:
                {
                    RecipeSubTopping* _rst = (RecipeSubTopping*)_rtF->data;
                    AddSubTopping(_rst);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 4:
                {
                    RecipeMix* _rm = (RecipeMix*)_rtF->data;
                    Mix(_rm);
                    need_update_pixel = true;
                    need_update_bitmask = true;
                    Reshape();
                }
                    break;
                case 5:
                {
                    RecipeLast* _rl = (RecipeLast*)_rtF->data;
                    SetLast(_rl);
                    need_update_model = true;
                    Reshape();
                }
                    break;
            }
        }
        return true;
    }
}

bool IceCream::IsHaveSubTopping() {
    for(int i = 0; i < VBArrayVectorGetLength(subTopping); i++) {
        if(VBArrayVectorGetDataAt(subTopping, i) != NULL)
            return true;
    }
    for(int i = 0; i < VBArrayVectorGetLength(subToppingFlow); i++) {
        if(VBArrayVectorGetLength((VBArrayVector*)VBArrayVectorGetDataAt(subToppingFlow, i)) > 0)
            return true;
    }
    return false;
}

bool IceCream::IsPossibleRecipe(int _recipe) {
    if(next) {
        return next->IsPossibleRecipe(_recipe);
    } else {
//        if(modelLastRecipe)
//            return false;
        
        RT* _rtF = NULL;
        for(int i = 0; i < VBArrayVectorGetLength(rdVec); i++) {
            RT* _rt = (RT*)VBArrayVectorGetDataAt(rdVec, i);
            if(_rt->idx == _recipe) {
                _rtF = _rt;
                break;
            }
        }
        
        if(_rtF) {
            switch(_rtF->type) {
                case 0:
                {
                    if(modelLastRecipe)
                        return false;
//                    if(IsHaveSubTopping())
//                        return false;
                }
                    break;
                case 1: 
                {
                    if(modelLastRecipe)
                        return false;
//                    if(IsHaveSubTopping())
//                        return false;
                    RecipeMask* _rm = (RecipeMask*)_rtF->data;
                    for(int i = 0; i < VBArrayVectorGetLength(mask); i++) {
                        RecipeMask* _rmCompare = (RecipeMask*)VBArrayVectorGetDataAt(mask, i);
                        if(_rm->idx == _rmCompare->idx) {
                            return false;
                        }
                    }
                }
                    break;
                case 2:
                {
//                    if(VBArrayVectorGetLength(mask))
//                        return false;
                    RecipeSubToppingFlow* _rstf = (RecipeSubToppingFlow*)_rtF->data;
                    if(VBArrayVectorGetDataAt(subTopping, _rstf->idx) != NULL)
                        return false;
                    if(VBArrayVectorGetLength((VBArrayVector*)VBArrayVectorGetDataAt(subToppingFlow, _rstf->idx)) > _rstf->len - 1)
                        return false;
                }
                    break;
                case 3:
                {
//                    if(VBArrayVectorGetLength(mask))
//                        return false;
                    RecipeSubTopping* _rst = (RecipeSubTopping*)_rtF->data;
                    if(VBArrayVectorGetDataAt(subTopping, _rst->idx) != NULL)
                        return false;
                    if(VBArrayVectorGetLength((VBArrayVector*)VBArrayVectorGetDataAt(subToppingFlow, _rst->idx)) > 0)
                        return false;
                }
                    break;
                case 4:
                {
                    if(modelLastRecipe)
                        return false;
                    if(VBArrayVectorGetLength(mask))
                        return false;
//                    if(IsHaveSubTopping())
//                        return false;
                }
                    break;
                case 5:
                {
                    if(modelLastRecipe)
                        return false;
                    if(VBArrayVectorGetLength(mask))
                        return false;
//                    if(IsHaveSubTopping())
//                        return false;
                }
                    break;
            }
        }
        return true;
    }
}

bool IceCream::IsPossibleTopping(int _topping) {
    if(next) {
        return next->IsPossibleTopping(_topping);
    } else {
        
        RT* _rtF = NULL;
        for(int i = 0; i < VBArrayVectorGetLength(tdVec); i++) {
            RT* _rt = (RT*)VBArrayVectorGetDataAt(tdVec, i);
            if(_rt->idx == _topping) {
                _rtF = _rt;
                break;
            }
        }
        
        if(_rtF) {
            switch(_rtF->type) {
                case 0:
                {
                }
                    break;
                case 1:
                {
                }
                    break;
                case 2:
                {
                }
                    break;
                case 3:
                {
                }
                    break;
            }
        }
        
        return true;
    }
}

bool IceCream::IsPossibleNext() {
    if(next) {
        return next->IsPossibleNext();
    } else {
        return true;
    }
}

void IceCream::AddToppingSpuit(ToppingSpuit* _ts) {
    if(next) {
        next->AddToppingSpuit(_ts);
    } else {
        int _l_count = 0;
        int _r_count = 0;
        for(int i = 0; i < toppingSpuitL->len; i++) {
            if(VBArrayVectorGetDataAt(toppingSpuitL, i) == _ts) {
                _l_count++;
            }
        }
        for(int i = 0; i < toppingSpuitR->len; i++) {
            if(VBArrayVectorGetDataAt(toppingSpuitR, i) == _ts) {
                _r_count++;
            }
        }
        if(_l_count + _r_count < _ts->len) {
            int _idx = _l_count + _r_count;
            VBAABB _aabb = _ts->aabbThumb[_idx];
            VBArrayVectorAddBack(thumbs, ThumbsInit(_ts->texThumb[_idx], _aabb, 0, _ts, false));
            TS_idx* _ti = (TS_idx*)malloc(sizeof(TS_idx));
            _ti->_t = _ts;
            _ti->_idx = _idx;
            _ti->_aabb = _aabb;
            if(_idx % 2) {
                VBArrayVectorAddBack(toppingSpuitR, _ti);
            } else {
                VBArrayVectorAddBack(toppingSpuitL, _ti);
            }
        }
    }
}

void IceCream::AddToppingFlow(ToppingFlow* _tf) {
    if(next) {
        next->AddToppingFlow(_tf);
    } else {
        int _rs_count = 0;
        for(int i = 0; i < toppingFlow->len; i++) {
            if(VBArrayVectorGetDataAt(toppingFlow, i) == _tf) {
                _rs_count++;
            }
        }
        if(_rs_count < _tf->len) {
            VBArrayVectorAddBack(thumbs, ThumbsInit(_tf->texThumb[_rs_count], _tf->aabbThumb[_rs_count], 1, _tf, false));
            VBArrayVectorAddBack(toppingFlow, _tf);
        }
    }
}

void IceCream::AddToppingCream(ToppingCream* _tc) {
    if(next) {
        next->AddToppingCream(_tc);
    } else {
        int _rs_count = 0;
        int _t_count = 0;
        for(int i = 0; i < thumbs->len; i++) {
            Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
            if(_t->targ == _tc) {
                _rs_count++;
            }
            if(_t->isR == false && _t->type == 3) {
                _t_count++;
            }
        }
        if(_rs_count < 1 && _t_count == 0) {
            VBArrayVectorAddBack(thumbs, ThumbsInit(_tc->texThumb, _tc->aabbThumb, 2, _tc, false));
            toppingCream = _tc;
        }
    }
}

void IceCream::AddToppingCherry(ToppingCherry* _tc) {
    if(next) {
        AddToppingCherry(_tc);
    } else {
        int _rs_count = 0;
        int _t_count = 0;
        Thumbs* _tt = NULL;
        for(int i = 0; i < thumbs->len; i++) {
            Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
            if(_t->targ == _tc) {
                _rs_count++;
            }
            if(_t->isR == false && _t->type == 2) {
                _tt = _t;
                _t_count++;
            }
        }
        if(_rs_count == 0) {
            if(_t_count > 0 && _tt) {
                if(getChildren()) {
                    if(getChildren()->indexOfObject(_tt->model) != UINT_MAX)
                        removeChild(_tt->model, false);
                }
                VBArrayVectorRemove(thumbs, _tt);
                ThumbsFree(&_tt);
            }
            VBArrayVectorAddBack(thumbs, ThumbsInit(_tc->texThumb[_t_count], _tc->aabbThumb[_t_count], 3, _tc, false));
            toppingCherry = _tc;
        }
    }
}

bool IceCream::AddTopping(int _topping) {
    if(next)
        return next->AddTopping(_topping);
    else {
        RT* _rtF = NULL;
        for(int i = 0; i < VBArrayVectorGetLength(tdVec); i++) {
            RT* _rt = (RT*)VBArrayVectorGetDataAt(tdVec, i);
            if(_rt->idx == _topping) {
                _rtF = _rt;
                break;
            }
        }
        
        if(_rtF) {
            switch(_rtF->type) {
                case 0:
                {
                    ToppingSpuit* _ts = (ToppingSpuit*)_rtF->data;
                    AddToppingSpuit(_ts);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 1: 
                {
                    ToppingFlow* _tf = (ToppingFlow*)_rtF->data;
                    AddToppingFlow(_tf);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 2: 
                {
                    ToppingCream* _tc = (ToppingCream*)_rtF->data;
                    AddToppingCream(_tc);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 3: 
                {
                    ToppingCherry* _tch = (ToppingCherry*)_rtF->data;
                    AddToppingCherry(_tch);
                    need_update_model = true;
                    Reshape();
                }
                    break;
            }
        }
        return true;
    }
}

bool IceCream::AddNextIceCream(int* _recipe, int _recipe_len) {
    if(next)
        return next->AddNextIceCream(_recipe, _recipe_len);
    else {
        if(baseIceCream)
            return AddNextIceCream(new IceCream(gameMain, rdVec, tdVec, baseIceCream->next, _recipe, _recipe_len));
        else
            return AddNextIceCream(new IceCream(gameMain, rdVec, tdVec, NULL, _recipe, _recipe_len));
    }
}

bool IceCream::AddNextIceCream(IceCream* _other) {
    if(next)
        return next->AddNextIceCream(_other);
    else {
        next = _other;
        next->baseIceCream = baseIceCream;
        next->prev = this;
        
        addChild(next);
        addChild(modelBridgeOutline);
        addChild(modelBridge);
        if(modelLastRecipeBridge) {
            addChild(modelLastRecipeBridge);
        }
        next->setPosition(CCPointMake(0, NEXT_ICECREAM_Y));
        return true;
    }
}

VBModel* IceCream::DragStartMount(VBModel* _topView) {
    if(next)
        return next->DragStartMount(_topView);
    else {
        if(VBArrayVectorGetLength(mask)) {
            RecipeMask* _masking = (RecipeMask*)VBArrayVectorGetDataAt(mask, VBArrayVectorGetLength(mask) - 1);
            if(_masking) {
                for(int i = 0; i < VBArrayVectorGetLength(thumbs); i++) {
                    Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
                    if(_masking == _t->targ) {
                        _t->attach = 0;
                        modelTop = _topView;
                        
                        need_update_model = true;
                        Reshape();
                        
                        _t->model->setScale(0.5);
                        _t->model->setPosition(CCPointMake(-((float)_masking->texThumb->width - (float)_masking->texThumb->shiftX) * 0.25, ((float)_masking->texThumb->height - (float)_masking->texThumb->shiftY) * 0.25));
                        modelTop->addChild(_t->model);
                        return _t->model;
                    }
                }
            }
        }
        return NULL;
    }
}

void IceCream::DragEndMount(bool _success) {
    if(next) {
        next->DragEndMount(_success);
    } else {
        if(VBArrayVectorGetLength(mask)) {
            RecipeMask* _masking = (RecipeMask*)VBArrayVectorGetDataAt(mask, VBArrayVectorGetLength(mask) - 1);
            if(_masking) {
                for(int i = 0; i < VBArrayVectorGetLength(thumbs); i++) {
                    Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
                    if(_masking == _t->targ) {
                        _t->attach = 1;
                        if(modelTop) {
                            if(modelTop->getChildren()) {
                                if(modelTop->getChildren()->indexOfObject(_t->model) != UINT_MAX)
                                    modelTop->removeChild(_t->model, false);
                            }
                            _t->model->setScale(1.0);
                            _t->model->setPosition(CCPointMake(_masking->aabbThumb.l - _masking->texThumb->shiftX, -_masking->aabbThumb.t + _masking->texThumb->shiftY));
                            modelTop = NULL;
                        }
                        
                        if(_success) {
                            ClearMask(NULL, 1);
                            gameMain->iceCreamMaskCallBack();
                        }
                        
                        need_update_model = true;
                        Reshape();
                        return;
                    }
                }
            }
        }
    }
}