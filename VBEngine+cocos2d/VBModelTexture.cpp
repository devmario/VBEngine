#include "VBModel.h"

void VBModel::ReloadTexture() {
    if(tex) {
    }
}

void VBModel::SetTexture(VBTexture* _tex) {
    tex = _tex;
    
    if(_tex) {
        is_bitmap = true;
    } else {
        is_bitmap = false;
    }
    
    if(tex) {
        setTextureRect(CCRect((((float)_tex->shiftX / (float)_tex->width) * (float)_tex->width) / CCDirector::sharedDirector()->getContentScaleFactor(),
                              (((float)_tex->shiftY / (float)_tex->height) * (float)_tex->height) / CCDirector::sharedDirector()->getContentScaleFactor(),
                              ((1.0f - (((float)_tex->shiftX * 2.0f) / (float)_tex->width)) * (float)_tex->width) / CCDirector::sharedDirector()->getContentScaleFactor(),
                              ((1.0f - (((float)_tex->shiftY * 2.0f) / (float)_tex->height)) * (float)_tex->height) / CCDirector::sharedDirector()->getContentScaleFactor()));
    }
}