#ifndef gelatomania_StageThumb_h
#define gelatomania_StageThumb_h

#include "VBModel.h"
#include "NumberText.h"
#include "cocos2d.h"
#include "Text.h"

using namespace cocos2d;

class StageThumb : public VBModel {
    void CleanThumb();
public:
    int packIdx;
    int stageIdx;
    
    bool locked;
    
    VBModel* stage;
    VBObjectFile2D* obj;
    VBTexture* tex;
    
    Text* textStage;
    Text* textComplete;
    Text* textTime;
    
    StageThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx, int _stageIdx);
    ~StageThumb();
    
    void Reset(int _packIdx, int _stageIdx);
};

#endif
