#include "VBColorGA.h"

VBColorGA VBColorGACreate(VBUChar _g, VBUChar _a) {
    VBColorGA _color;
    _color.g = _g;
    _color.a = _a;
    return _color;
}

VBUChar VBColorGAGetG(VBColorGA _color) {
    return _color.g;
}

VBUChar VBColorGAGetA(VBColorGA _color) {
    return _color.a;
}

VBColorGA VBColorGASetG(VBColorGA _color, VBUChar _g) {
    _color.g = _g;
    return _color;
}

VBColorGA VBColorGASetA(VBColorGA _color, VBUChar _a) {
    _color.a = _a;
    return _color;
}

VBColorGA VBColorGAInterpolate(VBColorGA _color1, VBColorGA _color2, VBFloat _num) {
    VBColorGA _color;
    _color.g = _color1.g + (_color2.g - _color1.g) * _num;
    _color.a = _color1.a + (_color2.a - _color1.a) * _num;
    return _color;
}