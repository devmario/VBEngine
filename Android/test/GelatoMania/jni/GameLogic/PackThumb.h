#ifndef gelatomania_PackThumb_h
#define gelatomania_PackThumb_h

#include "VBModel.h"
#include "NumberText.h"
#include "cocos2d.h"

using namespace cocos2d;

class PackThumb : public VBModel {
public:
    int packIdx;
    VBModel* pack;
    
    VBTexture* texTitle;
    VBModel* modelTitle;
    
    VBTexture* texClear;
    VBModel* modelClear;
    
    VBTexture* texStar;
    VBModel* modelStar;
    
    VBTexture* texTime;
    VBModel* modelTime;
    
    PackThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx);
    ~PackThumb();
    
    void Reset();
};

#endif
