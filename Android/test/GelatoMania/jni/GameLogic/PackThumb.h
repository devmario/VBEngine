#ifndef gelatomania_PackThumb_h
#define gelatomania_PackThumb_h

#include "VBModel.h"
#include "NumberText.h"
#include "cocos2d.h"
#include "Text.h"

using namespace cocos2d;

class PackThumb : public VBModel {
public:
    int packIdx;
    VBModel* pack;
    
    Text* textTitle;
    Text* textClear;
    Text* textStar;
    Text* textTime;
    
    PackThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx);
    ~PackThumb();
    
    void Reset();
};

#endif
