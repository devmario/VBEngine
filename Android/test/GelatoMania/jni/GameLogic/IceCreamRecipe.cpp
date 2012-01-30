#include "IceCream.h"
#include "GameMain.h"

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
                gameMain->iceCreamMaskCallBack(_rmV->idx);
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
        int mixFirst = 1;
        int bitmaskType = 0;
        int mixType = 0;
        while(_bitLoop <= bitmaskMerge) {
            if(_bitLoop & bitmaskMerge) {
                mixType = bitmaskType - 1;
                if(mixFirst) {
                    FillCream(_rm->img, _rm->aabb, NULL, VBAABBLoadIndentity(), bitmaskMerge, hexToInt(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "fill"), bitmaskType)->valuestring));
                    mixFirst = 0;
                } else {
                    FillCream(_rm->img, _rm->aabb, _rm->imgMask[mixType], _rm->aabbMask[mixType], bitmaskMerge, hexToInt(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "fill"), mixType)->valuestring));
                }
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