#include "VBModel.h"

VBColorRGBA VBModel::GetColor() {
    return color;
}

void VBModel::SetColor(VBColorRGBA _color) {
    color = _color;
}

unsigned char VBModel::GetAlpha() {
    return color.a;
}

void VBModel::SetAlpha(unsigned char _alpha) {
    color.a = _alpha;
}

void VBModel::SetBrightness(unsigned char _brightness) {
    color.r = _brightness;
    color.g = _brightness;
    color.b = _brightness;
}

unsigned char VBModel::GetBrightness() {
    return color.r;
}

void VBModel::SetUseMixColor(bool _value) {
	use_mix_color = _value;
}