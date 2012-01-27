#ifndef gelatomania_StageThumb_h
#define gelatomania_StageThumb_h

#include "VBModel.h"
#include "NumberText.h"
#include "cocos2d.h"

using namespace cocos2d;

class StageThumb : public VBModel {
    void CleanThumb();
public:
    int packIdx;
    int stageIdx;
    VBModel* stage;
    NumberText* label;
    VBModel* star;
    VBObjectFile2D* fontObj;
    VBTexture* fontTex;
    VBObjectFile2D* obj;
    VBTexture* tex;
    
    StageThumb(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex, int _packIdx, int _stageIdx);
    ~StageThumb();
    
    void Reset(int _packIdx, int _stageIdx);
};

#endif
