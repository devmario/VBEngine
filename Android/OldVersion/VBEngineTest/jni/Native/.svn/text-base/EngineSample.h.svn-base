#ifndef __EngineSample_H__
#define __EngineSample_H__

#include "VBEngine.h"
#include "TypoGraphyMotionSample.h"
#include "ColorTransitionSample.h"
#include "QuadtreeMapSample.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    //샘플타입
    enum {
        EngineSampleType_TypoGraphy         =   0x00,
        EngineSampleType_ColorTransition    =   0x01,
        EngineSampleType_ImageControl       =   0x02,
        EngineSampleType_Quadtree           =   0x03,
    };
    typedef VBUChar EngineSampleType;
    
    typedef struct EngineSample EngineSample;
    
    //샘플
    struct EngineSample {
        //엔진 Display
        VBDisplay2D* display_2d;
        //스크린 사이즈
        VBUShort width, height;
        //리소스 패스
        VBString* resource_path;
        //타이포그라피 샘플
        TypoGraphyMotionSample* typography_motion;
        //칼라트랜지션 샘플
        ColorTransitionSample* color_transition;
        //터치 이벤트 리스트
        VBArrayList* touch_list;
        
        EngineSampleType type;
    };
    
    //메모리 생성
    EngineSample* EngineSampleAlloc();
    
    //초기화
    EngineSample* EngineSampleInit(EngineSample* _engine_sample, VBString* _resource_path, VBUShort _width, VBUShort _height);
    
    //샘플 바꾸기
    void EngineSampleChangeType(EngineSample* _engine_sample, EngineSampleType _type);
    
    //메모리 해제
    void EngineSampleFree(EngineSample** _engine_sample);
    
    //업데이트 및 그리기
    void EngineSampleUpdateAndDraw(EngineSample* _engine_sample, VBFloat _time);
    
    //터치 이벤트 받기
    void EngineSampleTouch(EngineSample* _engine_sample, VBTouchType _type, void* _touch_id, VBChar _tab_count, VBVector2D _position);

#ifdef __cplusplus
}
#endif

#endif