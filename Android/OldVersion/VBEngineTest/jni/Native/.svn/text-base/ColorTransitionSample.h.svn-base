#ifndef __ColorTransitionSample_H__
#define __ColorTransitionSample_H__

#include "VBEngine.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define __ColorPicNumber__ 6
    
    typedef struct ColorTransitionSample ColorTransitionSample;
    
    struct ColorTransitionSample {
        VBObjectFile2D* obj_2d;
        VBTexture* texure;
        VBModel2D* color_motion;
        
        VBModel2D* button[__ColorPicNumber__];
        
        VBFloat button_dest_gray[__ColorPicNumber__];
        VBFloat button_gray[__ColorPicNumber__];
        
        VBFloat dest_frame;
        VBFloat cur_frame;
    };
    
    ColorTransitionSample* ColorTransitionSampleAlloc();
    
    ColorTransitionSample* ColorTransitionSampleInit(ColorTransitionSample* _color_transition,
                                                     VBString* _res_path, 
                                                     VBUShort _w, VBUShort _h);
    
    void ColorTransitionSampleFree(ColorTransitionSample** _color_transition);
    
    VBModel2D* ColorTransitionSampleGetScreenModel(ColorTransitionSample* _color_transition);
    
    void ColorTransitionSampleTouch(ColorTransitionSample* _color_transition, VBTouchType _type, void* _touch_id, VBChar _tab_count, VBVector2D _position);
    
    void ColorTransitionSampleUpdate(ColorTransitionSample* _color_transition, VBFloat _time);
    
#ifdef __cplusplus
}
#endif

#endif