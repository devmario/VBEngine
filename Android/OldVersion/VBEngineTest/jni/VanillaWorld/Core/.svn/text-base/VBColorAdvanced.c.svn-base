#include "VBColorAdvanced.h"

VBColorAdvanced VBColorAdvancedLoadIdentity() {
    return VBColorAdvancedCreate(100, 100, 100, 100, 0, 0, 0, 0);
}

VBColorAdvanced VBColorAdvancedCreate(VBChar _red_percent, VBChar _green_percent, VBChar _blue_percent, VBChar _alpha_percent, VBShort _red_amount, VBShort _green_amount, VBShort _blue_amount, VBShort _alpha_amount) {
    VBColorAdvanced _color;
    _color.red_percent = _red_percent;
    _color.green_percent = _green_percent;
    _color.blue_percent = _blue_percent;
    _color.alpha_percent = _alpha_percent;
    _color.red_amount = _red_amount;
    _color.green_amount = _green_amount;
    _color.blue_amount = _blue_amount;
    _color.alpha_amount = _alpha_amount;
    return _color;
}

VBColorAdvanced VBColorAdvancedInterpolate(VBColorAdvanced _color1, VBColorAdvanced _color2, VBFloat _num) {
    VBColorAdvanced _color;
    _color.red_percent = _color1.red_percent + (_color2.red_percent - _color1.red_percent) * _num;
    _color.green_percent = _color1.green_percent + (_color2.green_percent - _color1.green_percent) * _num;
    _color.blue_percent = _color1.blue_percent + (_color2.blue_percent - _color1.blue_percent) * _num;
    _color.alpha_percent = _color1.alpha_percent + (_color2.alpha_percent - _color1.alpha_percent) * _num;
    _color.red_amount = _color1.red_amount + (_color2.red_amount - _color1.red_amount) * _num;
    _color.green_amount = _color1.green_amount + (_color2.green_amount - _color1.green_amount) * _num;
    _color.blue_amount = _color1.blue_amount + (_color2.blue_amount - _color1.blue_amount) * _num;
    _color.alpha_amount = _color1.alpha_amount + (_color2.alpha_amount - _color1.alpha_amount) * _num;
    return _color;
}

VBColorAdvanced VBColorAdvancedMultiply(VBColorAdvanced _color1, VBColorAdvanced _color2) {
    VBColorAdvanced _color;
    _color.red_percent = (char)((float)_color1.red_percent * ((float)_color2.red_percent / 100.0));
    _color.green_percent = (char)((float)_color1.green_percent * ((float)_color2.green_percent / 100.0));
    _color.blue_percent = (char)((float)_color1.blue_percent * ((float)_color2.blue_percent / 100.0));
    _color.alpha_percent = (char)((float)_color1.alpha_percent * ((float)_color2.alpha_percent / 100.0));
    _color.red_amount = (short)((_color1.red_amount | _color2.red_amount));
    _color.green_amount = (short)((_color1.green_amount | _color2.green_amount));
    _color.blue_amount = (short)((_color1.blue_amount | _color2.blue_amount));
    _color.alpha_amount = (short)((_color1.alpha_amount | _color2.alpha_amount));
    return _color;
}