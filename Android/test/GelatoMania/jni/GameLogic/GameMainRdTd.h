//
//  GameMainRdTd.h
//  gelatomania
//
//  Created by Kyung Gak Nam on 12. 2. 7..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_GameMainRdTd_h
#define gelatomania_GameMainRdTd_h

#include "ShareData.h"
#include "RecipeAndToppingData.h"

struct cookRdTd {
    int** rtc;
    int* rtcArrLen;
    int rtcLen;
    int* tc;
    int tcLen;
};

class GameMainRdTd {
    unsigned int retainCount;
    
    int *rd;
    int *td;
    int rdLen;
    int tdLen;
    
    
    
public:
    cookRdTd cook;
    VBArrayVector *rdVec;
    VBArrayVector *tdVec;
    
    GameMainRdTd(int _packIdx, int _stageIdx);
    ~GameMainRdTd();
    void retain();
    void release();
    
//    VBArrayVector* rdVec();
//    VBArrayVector* tdVec();
    
};

#endif
