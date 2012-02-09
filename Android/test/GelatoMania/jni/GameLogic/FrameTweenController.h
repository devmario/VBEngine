//
//  FrameTweenController.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 9..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_FrameTweenController_h
#define gelatomania_FrameTweenController_h

#include "Tweener.h"
#include "VBModel.h"

class FrameTweenController {
    float frame;
    VBModel* model;
    TweenerWrapper* tween;
public:
    FrameTweenController(VBModel* _m);
    ~FrameTweenController();
    
    void playTo(float end, float duration, float delay, short ptransition, short pequation, void(*callBackFunc)(void* callBackObj), void* callBackObj);
    void Update(float _delta);
    
    bool getIsRun();
};

#endif
