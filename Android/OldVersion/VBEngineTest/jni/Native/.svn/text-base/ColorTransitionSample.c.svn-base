#include "ColorTransitionSample.h"


#define __ColorScrollSpeed__ 0.2f
#define __ColorButtonSpeed__ 0.08f
#define __ColorSelecGray__ 1.0f
#define __ColorNoSelecGray__ -0.3f

ColorTransitionSample* ColorTransitionSampleAlloc() {
    ColorTransitionSample* _color_transition = (ColorTransitionSample*)VBSystemCalloc(1, sizeof(ColorTransitionSample));
    _color_transition->obj_2d = VBObjectFile2DAlloc();
    _color_transition->texure = VBTextureAlloc();
    _color_transition->color_motion = VBModel2DAlloc();
    return _color_transition;
}

ColorTransitionSample* ColorTransitionSampleInit(ColorTransitionSample* _color_transition,
                                                 VBString* _res_path, 
                                                 VBUShort _w, VBUShort _h) {
    VBString* _obj2D_path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(_res_path), "ColorTransitionSample.obj");
    _color_transition->obj_2d = VBObjectFile2DInitAndLoad(_color_transition->obj_2d, _obj2D_path);
    VBStringFree(&_obj2D_path);
    
    VBString* _png_path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/ColorTransitionSample_%d_%d.png", VBStringGetCString(_res_path), _w, _h);
    _color_transition->texure = VBTextureInitAndLoadWithImagePath(_color_transition->texure, _png_path);
    VBStringFree(&_png_path);
    
    VBString* _library_name = VBStringInitWithCString(VBStringAlloc(), "Screen");
    _color_transition->color_motion = VBModel2DInitWithLibraryNameAndTexture(_color_transition->color_motion, _color_transition->obj_2d, _library_name, _color_transition->texure, VBTrue);
    VBStringFree(&_library_name);
    
    VBModel2DStop(_color_transition->color_motion);
    
    VBULong _i;
    for(_i = 0; _i < __ColorPicNumber__; _i++) {
        VBString* _instance_name = VBStringInitWithCStringFormat(VBStringAlloc(), "bt%d", _i);
        _color_transition->button[_i] = VBModel2DGetChildModelByInstanceName(_color_transition->color_motion, _instance_name);
        VBModel2DSetIsUseAnimation(_color_transition->button[_i], VBFalse); 
        VBStringFree(&_instance_name);
    }
    
    for(_i = 0; _i < __ColorPicNumber__; _i++) {
        if(_i == 0)
            _color_transition->button_gray[_i] = _color_transition->button_dest_gray[_i] = __ColorSelecGray__;
        else
            _color_transition->button_gray[_i] = _color_transition->button_dest_gray[_i] = __ColorNoSelecGray__;
    }
    
    return _color_transition;
}

void ColorTransitionSampleFree(ColorTransitionSample** _color_transition) {
    VBModel2DFree(&(*_color_transition)->color_motion);
    
    VBObjectFile2DFree(&(*_color_transition)->obj_2d);
    
    VBTextureFree(&(*_color_transition)->texure);
    
    VBSystemFree(*_color_transition);
    *_color_transition = VBNull;
}

VBModel2D* ColorTransitionSampleGetScreenModel(ColorTransitionSample* _color_transition) {
    return _color_transition->color_motion;
}

void ColorTransitionSampleTouch(ColorTransitionSample* _color_transition, VBTouchType _type, void* _touch_id, VBChar _tab_count, VBVector2D _position) {
    if(_type == VBTouchType_End) {
        VBULong _i, _j, _k;
        for(_i = 0; _i < __ColorPicNumber__; _i++) {
            VBModel2D* _bmp = VBModel2DGetChildModelAt(_color_transition->button[_i], 0);
            VBDrawable2D* _drawable =  (VBDrawable2D*) VBModel2DGetDrawable(_bmp);
            VBTriangle2D _tri;
            VBVector2D* _vtx = VBDrawable2DGetVertex(_drawable);
            VBVector2D* _vtx_ptr = _vtx;
            for(_j = 0; _j < VBDrawable2DGetPolygonLength(_drawable) - 2; _j++) {
                _tri.a = *_vtx;
                _vtx_ptr++;
                _tri.b = *_vtx_ptr;
                _tri.c = *(_vtx_ptr + 1);
                if(VBTriangle2DCheckCollisionWithPoint(_tri, _position)) {
                    for(_k = 0; _k < __ColorPicNumber__; _k++) {
                        if(_i == _k)
                            _color_transition->button_dest_gray[_k] = __ColorSelecGray__;
                        else
                            _color_transition->button_dest_gray[_k] = __ColorNoSelecGray__;
                    }
                    _color_transition->dest_frame = (VBModel2DGetTotalFrame(_color_transition->color_motion) - 1.0f) * ((VBFloat)_i / ((VBFloat)__ColorPicNumber__ - 1.0f));
                    break;
                }
            }
        }
    }
}

void ColorTransitionSampleUpdate(ColorTransitionSample* _color_transition, VBFloat _time) {
    _color_transition->cur_frame += (_color_transition->dest_frame - _color_transition->cur_frame) * __ColorScrollSpeed__;
    VBModel2DGoToAndStop(_color_transition->color_motion, _color_transition->cur_frame);
    
    VBULong _i;
    for(_i = 0; _i < __ColorPicNumber__; _i++) {
        _color_transition->button_gray[_i] += (_color_transition->button_dest_gray[_i] - _color_transition->button_gray[_i]) * __ColorButtonSpeed__;
        VBColorAdvanced _color = VBColorAdvancedCreate(100, 100, 100, 100, 
                                                       _color_transition->button_gray[_i] * 0xFF,
                                                       _color_transition->button_gray[_i] * 0xFF,
                                                       _color_transition->button_gray[_i] * 0xFF,
                                                       0);
	    
        VBModel2DSetColorAdvanced(_color_transition->button[_i], _color);
    }
}