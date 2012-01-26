#ifndef __TypoGraphyMotionSample_H__
#define __TypoGraphyMotionSample_H__

#include "VBEngine.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct TypoGraphyMotionSample TypoGraphyMotionSample;
    
    struct TypoGraphyMotionSample {
        //에니메이션및 레이아웃 obj파일
        VBObjectFile2D* obj_2d;
        //텍스쳐 png파일
        VBTexture* texure;
        //최상위 모델
        VBModel2D* top_model;
        
        //타이틀 모델
        VBModel2D* title;
        //텍스트 모델
        VBModel2D* text;
        //그라데이션 그림자 모델
        VBModel2D* shadow;
        
        //문자열 배열
        VBArrayVector* scripts;
        //에니메이션이 진행될때 화면에 보여질 문자모델들의 배열
        VBArrayVector* char_models;
        
        //현재 진행되고 있는 에니메이션의 문자열 배열 인덱스
        VBUChar cur_idx;
        //에니메이션 끝난후 경과시간
        VBFloat cur_time;
        //하나의 문자별로 화면에 붙혀진뒤의 경과시간
        VBFloat cur_char_time;
        //현재 에니메이션되고있는 문자열의 문자 위치 인덱스
        VBULong cur_char_idx;
        //문자의 넓이
        VBFloat char_width;
        //문자열의 위치
        VBFloat container_x;
        //문자열이 이동해야할 위치
        VBFloat container_dest_x;
    };
    
    //메모리 할당
    TypoGraphyMotionSample* TypoGraphyMotionSampleAlloc();
    
    //리소스에 접근할수 있는 디렉토리 경로와 해상도를 넘겨서 초기화
    TypoGraphyMotionSample* TypoGraphyMotionSampleInit(TypoGraphyMotionSample* _typo_graphy, VBUShort _w, VBUShort _h);
    
    //메모리 해제
    void TypoGraphyMotionSampleFree(TypoGraphyMotionSample** _typo_graphy);
    
    //결과 모델 가져오기
    VBModel2D* TypoGraphyMotionSampleGetTopModel(TypoGraphyMotionSample* _typo_graphy);
    
    //타이포 그라피 에니메이션 업데이트
    void TypoGraphyMotionSampleUpdate(TypoGraphyMotionSample* _typo_graphy, VBFloat _time);
    
    //문자열 에니메이션 다음으로 넘기고 리셋
    void TypoGraphyMotionSampleSetNextAnimation(TypoGraphyMotionSample* _typo_graphy);
    
#ifdef __cplusplus
}
#endif

#endif