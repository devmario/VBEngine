#include "VBObjectFile2DTransition.h"
#include "VBSystem.h"

VBObjectFile2DTransition* VBObjectFile2DTransitionAlloc(void) {
    VBObjectFile2DTransition* _transition = VBSystemCalloc(1, sizeof(VBObjectFile2DTransition));
    
    _transition->single_transition_bezier = VBArrayVectorInit(VBArrayVectorAlloc());
    
    _transition->position_transition_bezier = VBArrayVectorInit(VBArrayVectorAlloc());
    _transition->rotation_transition_bezier = VBArrayVectorInit(VBArrayVectorAlloc());
    _transition->scale_transition_bezier = VBArrayVectorInit(VBArrayVectorAlloc());
    _transition->color_transition_bezier = VBArrayVectorInit(VBArrayVectorAlloc());
    
    return _transition;
}

VBObjectFile2DTransition* VBObjectFile2DTransitionInit(VBObjectFile2DTransition* _transition) {
    _transition->type = VBObjectFile2DTransitionType_None;
    
    _VBObjectFile2DTransitionResetBezier(_transition->single_transition_bezier);
    
    _VBObjectFile2DTransitionResetBezier(_transition->position_transition_bezier);
    _VBObjectFile2DTransitionResetBezier(_transition->rotation_transition_bezier);
    _VBObjectFile2DTransitionResetBezier(_transition->scale_transition_bezier);
    _VBObjectFile2DTransitionResetBezier(_transition->color_transition_bezier);
    
    return _transition;
}

VBObjectFile2DTransition* VBObjectFile2DTransitionInitWithMultiData(VBObjectFile2DTransition* _transition,
                                                                    VBULong _position_bezier_vector_length,
                                                                    VBVector2D* _position_bezier_vector,
                                                                    VBULong _rotation_bezier_vector_length,
                                                                    VBVector2D* _rotation_bezier_vector,
                                                                    VBULong _scale_bezier_vector_length,
                                                                    VBVector2D* _scale_bezier_vector,
                                                                    VBULong _color_bezier_vector_length,
                                                                    VBVector2D* _color_bezier_vector) {
    _transition = VBObjectFile2DTransitionInit(_transition);
    
    _transition->type = VBObjectFile2DTransitionType_MultiBezier;
    
    _VBObjectFile2DTransitionSetBezier(_transition->position_transition_bezier, _position_bezier_vector_length, _position_bezier_vector);
    _VBObjectFile2DTransitionSetBezier(_transition->rotation_transition_bezier, _rotation_bezier_vector_length, _rotation_bezier_vector);
    _VBObjectFile2DTransitionSetBezier(_transition->scale_transition_bezier, _scale_bezier_vector_length, _scale_bezier_vector);
    _VBObjectFile2DTransitionSetBezier(_transition->color_transition_bezier, _color_bezier_vector_length, _color_bezier_vector);
    
    return _transition;
}

VBObjectFile2DTransition* VBObjectFile2DTransitionInitWithSingleData(VBObjectFile2DTransition* _transition,
                                                                     VBULong _single_bezier_vector_length,
                                                                     VBVector2D* _single_bezier_vector) {
    _transition = VBObjectFile2DTransitionInit(_transition);
    
    _transition->type = VBObjectFile2DTransitionType_SingleBezier;
    
    _VBObjectFile2DTransitionSetBezier(_transition->single_transition_bezier, _single_bezier_vector_length, _single_bezier_vector);
    
    return _transition;
}

void VBObjectFile2DTransitionFree(VBObjectFile2DTransition** _transition) {
    VBObjectFile2DTransitionInit(*_transition);
    VBArrayVectorFree(&(*_transition)->single_transition_bezier);
    VBArrayVectorFree(&(*_transition)->position_transition_bezier);
    VBArrayVectorFree(&(*_transition)->rotation_transition_bezier);
    VBArrayVectorFree(&(*_transition)->scale_transition_bezier);
    VBArrayVectorFree(&(*_transition)->color_transition_bezier);
    VBSystemFree(*_transition);
    *_transition = VBNull;
}

VBObjectFile2DTransitionType VBObjectFile2DTransitionGetType(VBObjectFile2DTransition* _transition) {
    return _transition->type;
}

VBFloat VBObjectFile2DTransitionGetSingleValue(VBObjectFile2DTransition* _transition, VBFloat _time) {
    if(_transition->single_transition_bezier->len)
        return _VBObjectFile2DTransitionGetValue(_transition->single_transition_bezier, _time);
    else
        return _time;
}

VBFloat VBObjectFile2DTransitionGetPositionValue(VBObjectFile2DTransition* _transition, VBFloat _time) {
    if(_transition->position_transition_bezier->len)
        return _VBObjectFile2DTransitionGetValue(_transition->position_transition_bezier, _time);
    else
        return _time;
}

VBFloat VBObjectFile2DTransitionGetRotationValue(VBObjectFile2DTransition* _transition, VBFloat _time) {
    if(_transition->rotation_transition_bezier->len)
        return _VBObjectFile2DTransitionGetValue(_transition->rotation_transition_bezier, _time);
    else
        return _time;
}

VBFloat VBObjectFile2DTransitionGetScaleValue(VBObjectFile2DTransition* _transition, VBFloat _time) {
    if(_transition->scale_transition_bezier->len)
        return _VBObjectFile2DTransitionGetValue(_transition->scale_transition_bezier, _time);
    else
        return _time;
}

VBFloat VBObjectFile2DTransitionGetColorValue(VBObjectFile2DTransition* _transition, VBFloat _time) {
    if(_transition->color_transition_bezier->len)
        return _VBObjectFile2DTransitionGetValue(_transition->color_transition_bezier, _time);
    else
        return _time;
}

void _VBObjectFile2DTransitionResetBezier(VBArrayVector* _bezier) {
    while(VBArrayVectorGetLength(_bezier)) {
        VBSpline2DBezierCubic* _cubic = VBArrayVectorRemoveBack(_bezier);
        VBSpline2DBezierCubicFree(&_cubic);
    }
}

void _VBObjectFile2DTransitionSetBezier(VBArrayVector* _bezier, VBULong _bezier_vector_length, VBVector2D* _bezier_vector) {
    VBULong _i;
    if(_bezier_vector_length) {
        for(_i = 0; _i < _bezier_vector_length - 1; _i += 3) {
            VBArrayVectorAddBack(_bezier, VBSpline2DBezierCubicInitWithVector(VBSpline2DBezierCubicAlloc(), _bezier_vector[_i], _bezier_vector[_i + 1], _bezier_vector[_i + 2], _bezier_vector[_i + 3]));
        }    
    }
}

VBSpline2DBezierCubic* _VBObjectFile2DTransitionGetCurrentBezier(VBArrayVector* _bezier, VBFloat _time) {
    VBULong _i;
    for(_i = 0; _i < VBArrayVectorGetLength(_bezier); _i++) {
        VBSpline2DBezierCubic* _temp_bezier = VBArrayVectorGetDataAt(_bezier, _i);
        if(_temp_bezier->begin.x <= _time && _temp_bezier->end.x >= _time) {
            return VBArrayVectorGetDataAt(_bezier, _i);
        }
    }
    return VBNull;
}

VBFloat _VBObjectFile2DTransitionGetValue(VBArrayVector* _bezier, VBFloat _time) {
    VBSpline2DBezierCubic* _current_bezier = _VBObjectFile2DTransitionGetCurrentBezier(_bezier, _time);
    return VBSpline2DBezierCubicGetBtyByT(_current_bezier, VBSpline2DBezierCubicGetTByBtx(_current_bezier, _time));
}
