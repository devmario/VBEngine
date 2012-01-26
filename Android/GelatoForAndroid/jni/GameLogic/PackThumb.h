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
    NumberText* scoreText;
    NumberText* starText;
    
    PackThumb(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex, int _packIdx);
    ~PackThumb();
    
    void Reset();
};

#endif
