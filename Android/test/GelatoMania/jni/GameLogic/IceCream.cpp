#include "IceCream.h"
#include "ShareData.h"
#include "png.h"
#include "zlib.h"
#include "GameMain.h"

void IceCream::VBModelUpdate(float _tick) {
    Reshape();
}

IceCream::IceCream(GameMain *_gameMain, VBArrayVector* _rdVec, VBArrayVector* _tdVec, IceCream* _baseIceCream, int* _recipe, int _recipe_len) : VBModel(NULL) {
    
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
    
    while (VBArrayVectorGetLength(toppingFlow)) {
        free((void*)VBArrayVectorRemoveBack(toppingFlow));
    }
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

bool IceCream::IsPossibleNext() {
    if(next) {
        return next->IsPossibleNext();
    } else {
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