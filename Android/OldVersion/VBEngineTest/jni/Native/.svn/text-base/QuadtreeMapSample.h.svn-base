#ifndef __QuadtreeMapSample_H__
#define __QuadtreeMapSample_H__

#include "VBEngine.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define kQuadtreeMapSpeed 1.0
#define kQuadtreeMapMaxTouch 5
    
    enum {
        QuadtreeMapTouchType_Begin      =   0x00,
        QuadtreeMapTouchType_Move       =   0x01,
        QuadtreeMapTouchType_End        =   0x02,
        QuadtreeMapTouchType_Cancel     =   0x03
    };
    typedef VBUChar QuadtreeMapTouchType;
    
    typedef struct QuadtreeMapTouch QuadtreeMapTouch;
    
    struct QuadtreeMapTouch {
        void* touch_id;
        QuadtreeMapTouchType type;
        VBVector2D postion;
    };
    
    typedef struct QuadtreeMapSample QuadtreeMapSample;
    
    struct QuadtreeMapSample {
        VBString* resource_path;
        
        VBUShort screen_width;
        VBUShort screen_height;
        
        VBVector2D slide;
        
        VBFloat scale;
        
        VBMatrix2D camera;
        
        VBModel2D* map_model;
        
        VBDisplay2D* display2D;
        
        VBQuadtree* quadtree;
        
        VBArrayList* touch_list;
    };
    
    QuadtreeMapSample* QuadtreeMapSampleAlloc();
    
    QuadtreeMapSample* QuadtreeMapSampleInit(QuadtreeMapSample* _quadtree_map,
                                             const VBChar* _res_path, 
                                             VBUShort _w, VBUShort _h,
                                             VBColorRGBA _bg_color);
    
    void QuadtreeMapSampleFree(QuadtreeMapSample** _quadtree_map);
    
    void QuadtreeMapSampleDraw(QuadtreeMapSample* _quadtree_map);
    
    void QuadtreeMapSampleTouchBegin(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y);
    
    void QuadtreeMapSampleTouchMove(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y);
    
    void QuadtreeMapSampleTouchEnd(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y);
    
    void QuadtreeMapSampleTouchCancel(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y);
    
#ifdef __cplusplus
}
#endif

#endif