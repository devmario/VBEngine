#ifndef __VBTouch_H__
#define __VBTouch_H__

#include "../VBType.h"
#include "../Core/Linear/VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    enum {
        VBTouchType_Begin       =   0x00,
        VBTouchType_Move        =   0x01,
        VBTouchType_End         =   0x02,
        VBTouchType_Cancel      =   0x03
    };
    typedef VBUChar VBTouchType;
    
    typedef struct VBTouch VBTouch;
    
    struct VBTouch {
        VBTouchType type;
        void* touch_id;
        VBChar tab_count;
        VBVector2D position;
    };
    
    VBTouch* VBTouchAlloc(void);
    
    VBTouch* VBTouchInitWithData(VBTouch* _touch, VBTouchType _type, void* _touch_id, VBChar _tab_count, VBVector2D _position);
    
    void VBTouchFree(VBTouch** _touch);

#ifdef __cplusplus
}
#endif

#endif