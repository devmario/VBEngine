#ifndef gelatomania_ScrollerContainer_h
#define gelatomania_ScrollerContainer_h

#include "VBModel.h"
#include "Scroller.h"

typedef struct CellData {
    int index;
    void* data;
    VBModel* modelCell;
} CellData;

class ScrollerContainer : public VBModel {
    void ReloadData();
public:
    VBArrayVector* cell;
    VBArrayVector* data;
    
    Scroller* scroller;
    float alphaScroll;
    bool isShowScroll;
    float showScrollerCount;
    
    VBModel* container;
    
    CCTouch* touchScroller;
    
    float height;
    float width;
    float pageY;
    float pageHeight;
    float forceY;
    float cellHeight;
    float maxPageY;
    
    float touchY;
    
    float margin;
    
    void (*allocFunc)(CellData* _data);
    void (*freeFunc)(CellData* _data);
    void (*touchBeginFunc)(CellData* _data, CCTouch* _touch, CCPoint _location);
    void (*touchMoveFunc)(CellData* _data, CCTouch* _touch, CCPoint _location);
    void (*touchEndFunc)(CellData* _data, CCTouch* _touch, CCPoint _location);
    void (*touchCancelFunc)(CellData* _data, CCTouch* _touch, CCPoint _location);
    void (*updateFunc)(CellData* _data, float _deltaTime);
    
    ScrollerContainer(VBObjectFile2D* _objScroller, VBTexture* _texScroller, 
                      void (*_allocFunc)(CellData*), 
                      void (*_freeFunc)(CellData*), 
                      void (*_touchBeginFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                      void (*_touchMoveFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                      void (*_touchEndFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                      void (*_touchCancelFunc)(CellData* _data, CCTouch* _touch, CCPoint _location), 
                      void (*_updateFunc)(CellData* _data, float _deltaTime), 
                      VBArrayVector* _data, float _cellHeight, float _width, float _height, float _margin);
    ~ScrollerContainer();
    
    bool enable;
    
    bool GetEnable();
    void SetEnable(bool _enable);
    
    bool NextPage();
    bool PrevPage();
    
    virtual void Update(float _deltaTime);
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
};

#endif
