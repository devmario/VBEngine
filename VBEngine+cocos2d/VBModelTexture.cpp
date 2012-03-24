#include "VBModel.h"

void VBModel::ReloadTexture() {
    if(tex && vb_tex) {
        tex->m_uName = vb_tex->tid;
    }
}

void VBModel::SetTexture(VBTexture* _tex) {
    vb_tex = _tex;
    
    if(_tex) {
        is_bitmap = true;
        
        if(tex == NULL)
            tex = new cocos2d::CCTexture2D();
        
        tex->m_bPVRHaveAlphaPremultiplied = false;
        tex->m_bHasPremultipliedAlpha = false;
        
        if(_tex->color_type == VBColorType_RGBA)
            tex->m_ePixelFormat = kCCTexture2DPixelFormat_RGBA8888;
        else if(_tex->color_type == VBColorType_RGB)
            tex->m_ePixelFormat = kCCTexture2DPixelFormat_RGB888;
        tex->m_uName = _tex->tid;
        tex->m_uPixelsWide = _tex->width;
        tex->m_uPixelsHigh = _tex->height;
        tex->m_tContentSize.width = _tex->width;
        tex->m_tContentSize.height = _tex->height;
        tex->m_fMaxS = 1.0;
        tex->m_fMaxT = 1.0;
        
    } else {
        is_bitmap = false;
        
        if(tex)
            tex->release();
        tex = NULL;
    }
    
    setTexture(tex);
    
    if(tex) {
        setTextureRect(CCRect((((float)_tex->shiftX / (float)_tex->width) * (float)_tex->width) / CCDirector::sharedDirector()->getContentScaleFactor(),
                              (((float)_tex->shiftY / (float)_tex->height) * (float)_tex->height) / CCDirector::sharedDirector()->getContentScaleFactor(),
                              ((1.0f - (((float)_tex->shiftX * 2.0f) / (float)_tex->width)) * (float)_tex->width) / CCDirector::sharedDirector()->getContentScaleFactor(),
                              ((1.0f - (((float)_tex->shiftY * 2.0f) / (float)_tex->height)) * (float)_tex->height) / CCDirector::sharedDirector()->getContentScaleFactor()));
    }
}