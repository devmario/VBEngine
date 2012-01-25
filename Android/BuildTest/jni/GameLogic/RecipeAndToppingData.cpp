#include "RecipeAndToppingData.h"
#include <stdlib.h>
#include "ShareData.h"

Thumbs* ThumbsInit(VBTexture* _tex, VBAABB _aabb, int _type, void* _targ) {
    Thumbs* _t = (Thumbs*)malloc(sizeof(Thumbs));
    _t->attach = 1;
    _t->model = new VBModel(_tex);
    _t->model->setPosition(CCPointMake(_aabb.l - _tex->shiftX, -_aabb.t + _tex->shiftY));
    _t->targ = _targ;
    _t->type = _type;
    return _t;
}

void ThumbsFree(Thumbs** _t) {
    delete (*_t)->model;
    free(*_t);
    *_t = NULL;
}

RT* RTInit(int _isR, int _idx, int _type, void* _data) {
    RT* _rt = (RT*)malloc(sizeof(RT));
    _rt->isR = _isR;
    _rt->type = _type;
    _rt->data = _data;
    _rt->idx = _idx;
    return _rt;
}

void RTFree(RT** _rt) {
    free(*_rt);
    *_rt = NULL;
}

RecipeFill* RecipeFillInit(cJSON* _js, int _cHx, int _idx) {
    RecipeFill* _rf = (RecipeFill*)malloc(sizeof(RecipeFill));
    _rf->js = _js;
    _rf->colorHex = _cHx;
    _rf->idx = _idx;
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_js, "path")->valuestring);
    _rf->imgMask = VBImageInitWithPath(VBImageAlloc(), _str);
    _rf->aabb = JStoAABB(_js);
    VBStringFree(&_str);
    return _rf;
}

void RecipeFillFree(RecipeFill** _rf) {
    VBImageFree(&(*_rf)->imgMask);
    free(*_rf);
    *_rf = NULL;
}

RecipeMask* RecipeMaskInit(cJSON* _maskJs, cJSON* _thumbJs, int _idx) {
    RecipeMask* _rm = (RecipeMask*)malloc(sizeof(RecipeMask));
    _rm->maskJs = _maskJs;
    _rm->aabbMask = JStoAABB(_maskJs);
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_maskJs, "path")->valuestring);
    _rm->imgMask = VBImageInitWithPath(VBImageAlloc(), _str);
    VBStringFree(&_str);
    _rm->thumbJs = _thumbJs;
    _rm->aabbThumb = JStoAABB(_thumbJs);
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_thumbJs, "path")->valuestring);
    _rm->texThumb = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    _rm->idx = _idx;
    return _rm;
}

void RecipeMaskFree(RecipeMask** _rm) {
    VBImageFree(&(*_rm)->imgMask);
    VBTextureFree(&(*_rm)->texThumb);
    free(*_rm);
    *_rm = NULL;
}

RecipeSubToppingFlow* RecipeSubToppingFlowInit(cJSON* _js, int _idx) {
    RecipeSubToppingFlow* _rstf = (RecipeSubToppingFlow*)malloc(sizeof(RecipeSubToppingFlow));
    _rstf->js = _js;
    _rstf->idx = _idx;
    _rstf->len = cJSON_GetArraySize(_js);
    _rstf->texThumb = (VBTexture**)malloc(sizeof(VBTexture*) * _rstf->len);
    _rstf->aabbThumb = (VBAABB*)malloc(sizeof(VBAABB) * _rstf->len);
    for(int i = 0; i < _rstf->len; i++) {
        char _buf[0xF] = {NULL,};
        sprintf(_buf, "%i", i);
        cJSON* _it = cJSON_GetObjectItem(_js, _buf);
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()),  cJSON_GetObjectItem(_it, "path")->valuestring);
        _rstf->texThumb[i] = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
        VBStringFree(&_str);
        _rstf->aabbThumb[i] = JStoAABB(_it);
    }
    return _rstf;
}

void RecipeSubToppingFlowFree(RecipeSubToppingFlow** _rstf) {
    for(int i = 0; i < (*_rstf)->len; i++) {
        VBTextureFree(&(*_rstf)->texThumb[i]);
    }
    free((*_rstf)->aabbThumb);
    free((*_rstf)->texThumb);
    free(*_rstf);
    *_rstf = NULL;
}

RecipeSubTopping* RecipeSubToppingInit(cJSON* _js, int _idx) {
    RecipeSubTopping* _rst = (RecipeSubTopping*)malloc(sizeof(RecipeSubTopping));
    _rst->js = _js;
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()),  cJSON_GetObjectItem(_js, "path")->valuestring);
    _rst->texThumb = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    _rst->aabbThumb = JStoAABB(_js);
    _rst->idx = _idx;
    return _rst;
}

void RecipeSubToppingFree(RecipeSubTopping** _rst) {
    VBTextureFree(&(*_rst)->texThumb);
    free(*_rst);
    *_rst = NULL;
}

RecipeMix* RecipeMixInit(cJSON* _js, cJSON* _mixJS) {
    RecipeMix* _rm = (RecipeMix*)malloc(sizeof(RecipeMix));
    VBString* _str;
    _rm->js = ShareDataGetTemplateData(_js);
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()),  cJSON_GetObjectItem(_rm->js, "path")->valuestring);
    _rm->img = VBImageInitWithPath(VBImageAlloc(), _str);
    VBStringFree(&_str);
    _rm->aabb = JStoAABB(_rm->js);
    _rm->len = cJSON_GetArraySize(_mixJS);
    _rm->mixJS = (cJSON**)malloc(sizeof(cJSON*) * _rm->len);
    _rm->imgMask = (VBImage**)malloc(sizeof(VBImage*) * _rm->len);
    _rm->aabbMask = (VBAABB*)malloc(sizeof(VBAABB) * _rm->len);
    for(int i = 0; i < _rm->len; i++) {
        _rm->mixJS[i] = ShareDataGetTemplateData(cJSON_GetArrayItem(_mixJS, i)); 
        _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()),  cJSON_GetObjectItem(_rm->mixJS[i], "path")->valuestring);
        _rm->imgMask[i] = VBImageInitWithPath(VBImageAlloc(), _str);
        VBStringFree(&_str);
        _rm->aabbMask[i] = JStoAABB(_rm->mixJS[i]);
    }
    
    return _rm;
}

void RecipeMixFree(RecipeMix** _rm) {
    VBImageFree(&(*_rm)->img);
    for(int i = 0; i < (*_rm)->len; i++) {
        VBImageFree(&(*_rm)->imgMask[i]);
    }
    free((*_rm)->mixJS);
    free((*_rm)->imgMask);
    free((*_rm)->aabbMask);
    free(*_rm);
    *_rm = NULL;
}

RecipeLast* RecipeLastInit(cJSON* _js, cJSON* _jsBridge) {
    RecipeLast* _rl = (RecipeLast*)malloc(sizeof(RecipeLast));
    _rl->js = _js;
    _rl->jsBridge = _jsBridge;
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()),  cJSON_GetObjectItem(_js, "path")->valuestring);
    _rl->tex = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()),  cJSON_GetObjectItem(_jsBridge, "path")->valuestring);
    _rl->texBridge = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    _rl->aabb = JStoAABB(_js);
    _rl->aabbBridge = JStoAABB(_jsBridge);
    return _rl;
}

void RecipeLastFree(RecipeLast** _rl) {
    VBTextureFree(&(*_rl)->texBridge);
    VBTextureFree(&(*_rl)->tex);
    free(*_rl);
    *_rl = NULL;
}

ToppingSpuit* ToppingSpuitInit(cJSON* _js) {
    ToppingSpuit* _ts = (ToppingSpuit*)malloc(sizeof(ToppingSpuit));
    cJSON* _r = _js;
    _ts->len = cJSON_GetArraySize(_r);
    
    //printf("ToppingSpuitInit Length %i\n", _ts->len);
    _ts->js = (cJSON**)malloc(_ts->len * sizeof(cJSON*));
    _ts->aabbThumb = (VBAABB*)malloc(_ts->len * sizeof(VBAABB));
    _ts->texThumb = (VBTexture**)malloc(_ts->len * sizeof(VBTexture*));
    
    for(int i = 0; i < _ts->len; i++) {
        char _buf[0xF] = {NULL,};
        sprintf(_buf, "%i", i);
        
        _ts->js[i] = cJSON_GetObjectItem(_r, _buf);
        _ts->aabbThumb[i] = JStoAABB(_ts->js[i]);
        
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_ts->js[i], "path")->valuestring);
        //printf("ToppingSpuitInit Tex %s\n", _str->data);
        _ts->texThumb[i] = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
        VBStringFree(&_str);
    }
    return _ts;
}

void ToppingSpuitFree(ToppingSpuit** _ts) {
    for(int i = 0; i < (*_ts)->len; i++) {
        VBTextureFree(&((*_ts)->texThumb[i]));
    }
    free((*_ts)->texThumb);
    free((*_ts)->aabbThumb);
    free((*_ts)->js);
    free(*_ts);
    *_ts = NULL;
}

ToppingFlow* ToppingFlowInit(cJSON* _js) {
    ToppingFlow* _tf = (ToppingFlow*)malloc(sizeof(ToppingFlow));
    cJSON* _r = _js;
    _tf->len = cJSON_GetArraySize(_r);
    _tf->js = (cJSON**)malloc(_tf->len * sizeof(cJSON*));
    _tf->aabbThumb = (VBAABB*)malloc(_tf->len * sizeof(VBAABB));
    _tf->texThumb = (VBTexture**)malloc(_tf->len * sizeof(VBTexture*));
    for(int i = 0; i < _tf->len; i++) {
        char _buf[0xF] = {NULL,};
        sprintf(_buf, "%i", i);
        _tf->js[i] = cJSON_GetObjectItem(_r, _buf);
        _tf->aabbThumb[i] = JStoAABB(_tf->js[i]);
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_tf->js[i], "path")->valuestring);
        _tf->texThumb[i] = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
        VBStringFree(&_str);
    }
    return _tf;
}

void ToppingFlowFree(ToppingFlow** _tf) {
    for(int i = 0; i < (*_tf)->len; i++) {
        VBTextureFree(&((*_tf)->texThumb[i]));
    }
    free((*_tf)->texThumb);
    free((*_tf)->aabbThumb);
    free((*_tf)->js);
    free(*_tf);
    *_tf = NULL;
    
}

ToppingCream* ToppingCreamInit(cJSON* _js) {
    ToppingCream* _tc = (ToppingCream*)malloc(sizeof(ToppingCream));
    _tc->js = _js;
    _tc->aabbThumb = JStoAABB(_tc->js);
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_tc->js, "path")->valuestring);
    _tc->texThumb = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    return _tc;
}

void ToppingCreamFree(ToppingCream** _tc) {
    VBTextureFree(&(*_tc)->texThumb);
    free(*_tc);
    *_tc = NULL;
}

ToppingCherry* ToppingCherryInit(cJSON* _js0, cJSON* _js1) {
    ToppingCherry* _tc = (ToppingCherry*)malloc(sizeof(ToppingCherry));
    _tc->js[0] = _js0;
    _tc->aabbThumb[0] = JStoAABB(_tc->js[0]);
    
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_tc->js[0], "path")->valuestring);
    _tc->texThumb[0] = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    
    _tc->js[1] = _js1;
    _tc->aabbThumb[1] = JStoAABB(_tc->js[1]);
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), cJSON_GetObjectItem(_tc->js[1], "path")->valuestring);
    _tc->texThumb[1] = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
    VBStringFree(&_str);
    
    return _tc;
}

void ToppingCherryFree(ToppingCherry** _tc) {
    VBTextureFree(&(*_tc)->texThumb[0]);
    VBTextureFree(&(*_tc)->texThumb[1]);
    
    free(*_tc);
    *_tc = NULL;
}
