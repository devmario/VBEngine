#include "EngineSample.h"
#include <stdlib.h>
#ifdef _VB_ANDROID_
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "libnav", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "libnav", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "libnav", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "libnav", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav", __VA_ARGS__)
#endif

void _EngineSampleReset(EngineSample* _engine_sample);

void _EngineSampleTouchListClear(EngineSample* _engine_sample);

void _EngineSampleReset(EngineSample* _engine_sample) {
    _EngineSampleTouchListClear(_engine_sample);
    
    while(VBModel2DGetChildNum(VBDisplay2DGetTopModel(_engine_sample->display_2d))) {
        VBModel2DRemoveChildModelAt(VBDisplay2DGetTopModel(_engine_sample->display_2d), 0);
    }
    
    if(_engine_sample->typography_motion)
        TypoGraphyMotionSampleFree(&_engine_sample->typography_motion);
    if(_engine_sample->color_transition)
        ColorTransitionSampleFree(&_engine_sample->color_transition);
}

void _EngineSampleTouchListClear(EngineSample* _engine_sample) {
    VBArrayListNode* _node = VBArrayListGetFirstNode(_engine_sample->touch_list);
    while(_node) {
        VBTouch* _touch =  (VBTouch*)VBArrayListNodeGetData(_node);
        VBTouchFree(&_touch);
        VBArrayListRemoveFront(_engine_sample->touch_list);
        _node = VBArrayListGetFirstNode(_engine_sample->touch_list);
    }
}

EngineSample* EngineSampleAlloc() {
    EngineSample* _engine_sample = (EngineSample*)VBSystemCalloc(1, sizeof(EngineSample));
    _engine_sample->display_2d = VBDisplay2DAlloc();
    _engine_sample->resource_path = VBStringAlloc();
    _engine_sample->touch_list = VBArrayListAlloc();
    return _engine_sample;
}

EngineSample* EngineSampleInit(EngineSample* _engine_sample, VBString* _resource_path, VBUShort _width, VBUShort _height) {
    _engine_sample->width = _width;
    _engine_sample->height = _height;
    _engine_sample->display_2d = VBDisplay2DInitWithScreenSize(_engine_sample->display_2d, _width, _height);
    _engine_sample->resource_path = VBStringInitWithCString(_engine_sample->resource_path, VBStringGetCString(_resource_path));
    _engine_sample->touch_list = VBArrayListInit(_engine_sample->touch_list);
    
   //EngineSampleChangeType(_engine_sample, EngineSampleType_TypoGraphy);
	EngineSampleChangeType(_engine_sample, EngineSampleType_ColorTransition);
    
    return _engine_sample;
}

void EngineSampleChangeType(EngineSample* _engine_sample, EngineSampleType _type) {
    _EngineSampleReset(_engine_sample);
    
    _engine_sample->type = _type;
    
    if(_type == EngineSampleType_TypoGraphy) {
        VBColorRGBAf _clear_color = {0.0, 0.0, 0.0, 1.0};
        VBEngineSetClearColor(_clear_color);
        _engine_sample->typography_motion = TypoGraphyMotionSampleInit(TypoGraphyMotionSampleAlloc(), _engine_sample->width, _engine_sample->height);
        VBModel2DAddChildModel(VBDisplay2DGetTopModel(_engine_sample->display_2d), TypoGraphyMotionSampleGetTopModel(_engine_sample->typography_motion));
    } else if(_type == EngineSampleType_ColorTransition) {
        VBColorRGBAf _clear_color = {0.8, 0.8, 0.8, 1.0};
        VBEngineSetClearColor(_clear_color);
        _engine_sample->color_transition = ColorTransitionSampleInit(ColorTransitionSampleAlloc(), _engine_sample->resource_path, _engine_sample->width, _engine_sample->height);
        VBModel2DAddChildModel(VBDisplay2DGetTopModel(_engine_sample->display_2d), ColorTransitionSampleGetScreenModel(_engine_sample->color_transition));
    } else if(_type == EngineSampleType_Quadtree) {
        
    }
}

void EngineSampleFree(EngineSample** _engine_sample) {
    _EngineSampleReset(*_engine_sample);
    VBArrayListFree(&(*_engine_sample)->touch_list);
    VBDisplay2DFree(&(*_engine_sample)->display_2d);
    VBStringFree(&(*_engine_sample)->resource_path);
    //VBSystemFree(*_engine_sample); // error 더이상 free 할 자원이 없음
    *_engine_sample = VBNull;
}

void EngineSampleUpdateAndDraw(EngineSample* _engine_sample, VBFloat _time) {

    VBDisplay2DUpdate(_engine_sample->display_2d, _time);
    
    VBULong _touch_length_by_frame = 0;
    VBTouch* _touch_by_frame[0xFF];
    VBArrayListNode* _node = VBArrayListGetFirstNode(_engine_sample->touch_list);
    VBULong _i;
    while(_node) {
        VBTouch* _touch =  (VBTouch*)VBArrayListNodeGetData(_node);
        VBBool is_exist_equal_touch = VBFalse;
        for(_i = 0; _i < _touch_length_by_frame; _i++) {
            if(_touch_by_frame[_i]->touch_id == _touch->touch_id) {
                _touch_by_frame[_i] = _touch;
                is_exist_equal_touch = VBTrue;
                break;
            }
        }
        if(is_exist_equal_touch == false) {
            _touch_by_frame[_touch_length_by_frame] = _touch;
            _touch_length_by_frame++;
        }
        _node = VBArrayListNodeGetNextNode(_node);
    }
    for(_i = 0; _i < _touch_length_by_frame; _i++) {
        if(_engine_sample->type == EngineSampleType_TypoGraphy) {
            if(_touch_by_frame[_i]->type == VBTouchType_End) {
                TypoGraphyMotionSampleSetNextAnimation(_engine_sample->typography_motion);
            }
        } else if(_engine_sample->type == EngineSampleType_ColorTransition) {
            ColorTransitionSampleTouch(_engine_sample->color_transition, _touch_by_frame[_i]->type, _touch_by_frame[_i]->touch_id, _touch_by_frame[_i]->tab_count, _touch_by_frame[_i]->position);
        }
    }
    _EngineSampleTouchListClear(_engine_sample);
    
    if(_engine_sample->type == EngineSampleType_TypoGraphy)
        TypoGraphyMotionSampleUpdate(_engine_sample->typography_motion, _time);
    else if(_engine_sample->type == EngineSampleType_ColorTransition)
        ColorTransitionSampleUpdate(_engine_sample->color_transition, _time);
    
    VBEngineClearDisplay();
    VBDisplay2DDraw(_engine_sample->display_2d);
}

void EngineSampleTouch(EngineSample* _engine_sample, VBTouchType _type, void* _touch_id, VBChar _tab_count, VBVector2D _position) {
    VBTouch* _touch = VBTouchInitWithData(VBTouchAlloc(), _type, _touch_id, _tab_count, _position);
    VBArrayListAddBack(_engine_sample->touch_list, _touch);
}
