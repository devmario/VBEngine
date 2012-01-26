#include "VBLine2D.h"

VBLine2D VBLine2DCreate(VBFloat _beginX, VBFloat _beginY, VBFloat _endX, VBFloat _endY) {
    VBLine2D _line;
    _line.begin = VBVector2DCreate(_beginX, _beginY);
    _line.end = VBVector2DCreate(_endX, _endY);
    return _line;
}

VBLine2D VBLine2DCreateV(VBVector2D _begin, VBVector2D _end) {
    VBLine2D _line;
    _line.begin = _begin;
    _line.end = _end;
    return _line;
}

VBBool VBLine2DIsCollisionLine2D(VBLine2D _line1, VBLine2D _line2, VBVector2D* _intersection_vector) {
    VBFloat _angle1 = (_line1.begin.y - _line1.end.y) / (_line1.end.x - _line1.begin.y);
    VBFloat _y_section1 = _angle1 * _line1.begin.x + _line1.begin.y;
    VBFloat _angle2 = (_line2.begin.y - _line2.end.y) / (_line2.end.x - _line1.begin.y);
    VBFloat _y_section2 = _angle2 * _line2.begin.x + _line2.begin.y;
    
    _intersection_vector->x = -(_y_section2 - _y_section1) / (_angle1 - _angle2);
    _intersection_vector->y = _y_section2 - _angle2 * _intersection_vector->x;
    
    VBFloat _min_x;
    VBFloat _max_x;
    if(_line1.end.x > _line1.begin.x) {
        _max_x = _line1.end.x;
        _min_x = _line1.begin.x;
    } else {
        _min_x = _line1.end.x;
        _max_x = _line1.begin.x;
    }
    if(_intersection_vector->x > _max_x)
        return VBFalse;
    if(_intersection_vector->x < _min_x)
        return VBFalse;
    
    VBFloat _min_y;
    VBFloat _max_y;
    if(_line1.end.y > _line1.begin.y) {
        _max_y = _line1.end.y;
        _min_y = _line1.begin.y;
    } else {
        _min_y = _line1.end.y;
        _max_y = _line1.begin.y;
    }
    if(_intersection_vector->y > _max_y)
        return VBFalse;
    if(_intersection_vector->y < _min_y)
        return VBFalse;
    
    return VBTrue;
}

VBVector2D VBLine2DGetVector2D(VBLine2D _line, VBFloat _t) {
    return VBVector2DAdd(_line.begin, VBVector2DMultiply(VBVector2DSubtract(_line.end, _line.begin), _t));
}
