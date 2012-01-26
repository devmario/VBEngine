#ifndef gelatomania_RecipeAndToppingData_h
#define gelatomania_RecipeAndToppingData_h

#include "VBEngine.h"
#include "cJSON.h"
#include "VBModel.h"

typedef struct Thumbs {
    VBModel* model;
    int attach;
    void* targ;
    int type;
    bool isR;
} Thumbs;

Thumbs* ThumbsInit(VBTexture* _tex, VBAABB _aabb, int _type, void* _targ, bool _isR);
void ThumbsFree(Thumbs** _t);

typedef struct RT {
    int isR;
    int idx;
    int type;
    void* data;
} RT;
RT* RTInit(int _isR, int _idx, int _type, void* _data);
void RTFree(RT** _rt);

typedef struct RecipeFill {
    cJSON* js;
    VBImage* imgMask;
    VBAABB aabb;
    int colorHex;
    int idx;
} RecipeFill;
RecipeFill* RecipeFillInit(cJSON* _js, int _cHx, int _idx);
void RecipeFillFree(RecipeFill** _rf);

typedef struct RecipeMask {
    cJSON* maskJs;
    cJSON* thumbJs;
    VBImage* imgMask;
    VBTexture* texThumb;
    VBAABB aabbMask;
    VBAABB aabbThumb;
    int idx;
} RecipeMask;
RecipeMask* RecipeMaskInit(cJSON* _maskJs, cJSON* _thumbJs, int _idx);
void RecipeMaskFree(RecipeMask** _rm);

typedef struct RecipeSubToppingFlow {
    cJSON* js;
    VBTexture** texThumb;
    VBAABB* aabbThumb;
    int len, idx;
} RecipeSubToppingFlow;
RecipeSubToppingFlow* RecipeSubToppingFlowInit(cJSON* _js, int _idx);
void RecipeSubToppingFlowFree(RecipeSubToppingFlow** _rstf);

typedef struct RecipeSubTopping {
    cJSON* js;
    VBTexture* texThumb;
    VBAABB aabbThumb;
    int idx;
} RecipeSubTopping;
RecipeSubTopping* RecipeSubToppingInit(cJSON* _js, int _idx);
void RecipeSubToppingFree(RecipeSubTopping** _rst);

typedef struct RecipeMix {
    cJSON* js;
    cJSON** mixJS;
    VBImage** imgMask;
    VBAABB* aabbMask;
    VBImage* img;
    VBAABB aabb;
    int len;
} RecipeMix;
RecipeMix* RecipeMixInit(cJSON* _js, cJSON* _mixJS);
void RecipeMixFree(RecipeMix** _rm);

typedef struct RecipeLast {
    cJSON* js;
    cJSON* jsBridge;
    VBTexture* tex;
    VBTexture* texBridge;
    VBAABB aabb;
    VBAABB aabbBridge;
} RecipeLast;
RecipeLast* RecipeLastInit(cJSON* _js, cJSON* _jsBridge);
void RecipeLastFree(RecipeLast** _rl);

typedef struct ToppingSpuit {
    cJSON** js;
    VBTexture** texThumb;
    VBAABB* aabbThumb;
    int len;
} ToppingSpuit;
ToppingSpuit* ToppingSpuitInit(cJSON* _js);
void ToppingSpuitFree(ToppingSpuit** _ts);

typedef struct ToppingFlow {
    cJSON** js;
    VBTexture** texThumb;
    VBAABB* aabbThumb;
    int len;
} ToppingFlow;
ToppingFlow* ToppingFlowInit(cJSON* _js);
void ToppingFlowFree(ToppingFlow** _tf);

typedef struct ToppingCream {
    cJSON* js;
    VBTexture* texThumb;
    VBAABB aabbThumb;
} ToppingCream;
ToppingCream* ToppingCreamInit(cJSON* _js);
void ToppingCreamFree(ToppingCream** _tc);

typedef struct ToppingCherry {
    cJSON* js[2];
    VBTexture* texThumb[2];
    VBAABB aabbThumb[2];
} ToppingCherry;
ToppingCherry* ToppingCherryInit(cJSON* _js0, cJSON* _js1);
void ToppingCherryFree(ToppingCherry** _tc);

#endif
