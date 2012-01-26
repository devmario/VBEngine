#include "VBTouch.h"
#include "VBSystem.h"

VBTouch* VBTouchAlloc(void) {
    return VBSystemCalloc(1, sizeof(VBTouch));
}

VBTouch* VBTouchInitWithData(VBTouch* _touch, VBTouchType _type, void* _touch_id, VBChar _tab_count, VBVector2D _position) {
    _touch->type = _type;
    _touch->touch_id = _touch_id;
    _touch->tab_count = _tab_count;
    _touch->position = _position;
    return _touch;
}

void VBTouchFree(VBTouch** _touch) {
    VBSystemFree(*_touch);
    *_touch = VBNull;
}
