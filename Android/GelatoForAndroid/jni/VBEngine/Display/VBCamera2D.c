#include "../VBEngine.h"
#include <math.h>

VBCamera2D* VBCamera2DAlloc(void) {
    return VBSystemCalloc(1, sizeof(VBCamera2D));
}

VBCamera2D* VBCamera2DInit(VBCamera2D* _camera) {
    VBSystemMemorySet(_camera, 0x00, sizeof(VBCamera2D));
    _camera->zoom = 1.0f;
    _camera->is_need_update = VBTrue;
    return _camera;
}

VBCamera2D* VBCamera2DInitWithMode(VBCamera2D* _camera, VBCamera2DMode _mode) {
    _camera = VBCamera2DInit(_camera);
    VBCamera2DSetMode(_camera, _mode);
    return _camera;
}

void VBCamera2DFree(VBCamera2D** _camera) {
    VBSystemFree(*_camera);
    *_camera = VBNull;
}

void VBCamera2DSetMode(VBCamera2D* _camera, VBCamera2DMode _mode) {
    if(_camera->mode != _mode) {
        _camera->mode = _mode;
        switch(_mode) {
            case VBCamera2DMode_Default:
                VBCamera2DSetPosition(_camera, VBVector2DZero());
                VBCamera2DSetZoom(_camera, 1.0f);
                VBCamera2DSetRotation(_camera, 0.0f);
                break;
            case VBCamera2DMode_Left:
                VBCamera2DSetPosition(_camera, VBVector2DZero());
                VBCamera2DSetZoom(_camera, 1.0f);
                VBCamera2DSetRotation(_camera, 0.0f);
                break;
            case VBCamera2DMode_Right:
                VBCamera2DSetPosition(_camera, VBVector2DZero());
                VBCamera2DSetZoom(_camera, 1.0f);
                VBCamera2DSetRotation(_camera, 0.0f);
                break;
            case VBCamera2DMode_Reverse:
                VBCamera2DSetPosition(_camera, VBVector2DZero());
                VBCamera2DSetZoom(_camera, 1.0f);
                VBCamera2DSetRotation(_camera, 0.0f);
                break;
        }
        _camera->is_need_update = VBTrue;
    }
}

VBCamera2DMode VBCamera2DGetMode(VBCamera2D* _camera) {
    return _camera->mode;
}

void VBCamera2DSetPosition(VBCamera2D* _camera, VBVector2D _position) {
    if(!VBVector2DIsEqual(_camera->position, _position)) {
        _camera->position = _position;
        _camera->is_need_update = VBTrue;
    }
}

VBVector2D VBCamera2DGetPosition(VBCamera2D* _camera) {
    return _camera->position;
}

void VBCamera2DSetRotation(VBCamera2D* _camera, VBFloat _rotation) {
    if(_camera->rotation != _rotation) {
        _camera->rotation = _rotation;
        _camera->is_need_update = VBTrue;
    }
}

VBFloat VBCamera2DGetRotation(VBCamera2D* _camera) {
    return _camera->rotation;
}

void VBCamera2DSetZoom(VBCamera2D* _camera, VBFloat _zoom) {
    if(_camera->zoom != _zoom) {
        _camera->zoom = _zoom;
        _camera->is_need_update = VBTrue;
    }
}

VBFloat VBCamera2DGetZoom(VBCamera2D* _camera) {
    return _camera->zoom;
}

VBMatrix2D VBCamera2DGetMatrix(VBCamera2D* _camera) {
    if(_camera->is_need_update) {
        VBVector2D _screen = VBEngineGetScreenSize();
        VBVector2D _screen_center = VBVector2DMultiply(_screen, 0.5f);
        VBVector2D _model_view_position = VBVector2DSubtract(VBVector2DZero(), _camera->position);
        VBVector2D _default_screen = VBEngineGetDefaultResourceScreenSize();
        VBVector2D _default_screen_center = VBVector2DMultiply(_default_screen, 0.5f);
        VBFloat _rotation = -_camera->rotation;
        VBFloat _min_scale;
        if(_camera->mode == VBCamera2DMode_Left) {
            _rotation += M_PI * 0.5f;
            _min_scale = fminf(_screen.x / _default_screen.y, _screen.y / _default_screen.x);
        } else if(_camera->mode == VBCamera2DMode_Right) {
            _rotation += -M_PI * 0.5f;
            _min_scale = fminf(_screen.x / _default_screen.y, _screen.y / _default_screen.x);
        } else if(_camera->mode == VBCamera2DMode_Reverse) {
            _rotation += M_PI;
            _min_scale = fminf(_screen.x / _default_screen.x, _screen.y / _default_screen.y);
        } else {
            _min_scale = fminf(_screen.x / _default_screen.x, _screen.y / _default_screen.y);
        }
        VBVector2D _default_scale = VBVector2DCreate(_min_scale, _min_scale);
        
        VBVector2D _anchor = VBVector2DAdd(VBVector2DSubtract(VBVector2DZero(), _default_screen_center), _model_view_position);
        
        _camera->mat = VBMatrix2DLoadIdentity();
        _camera->mat = VBMatrix2DTranslateV(_camera->mat, _screen_center);
        _camera->mat = VBMatrix2DRotate(_camera->mat, _rotation);
        _camera->mat = VBMatrix2DScaleV(_camera->mat, VBVector2DMultiply(_default_scale, _camera->zoom));
        _camera->mat = VBMatrix2DTranslateV(_camera->mat, _anchor);
        
        _camera->is_need_update = VBFalse;
    }
    return _camera->mat;
}
