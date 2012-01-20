#include "VBColorG.h"

VBColorG VBColorGInterpolate(VBColorG _color1, VBColorG _color2, VBFloat _num) {
    VBColorG _color;
    _color = _color1 + (_color2 - _color1) * _num;
    return _color;
}