#ifndef gelatomania_ToppingContainer_h
#define gelatomania_ToppingContainer_h

#include "ScrollerContainer.h"
#include "IceCream.h"

typedef struct ToppingContainerCellData {
    int type;
    
    VBString* texPath;
    VBObjectFile2D* obj;
    VBObjectFile2DLibraryNameID* name_id;
    VBTexture* tex;
    
    VBModel* model;
    CCTouch* touch;
    
    int step;
    int stepTotal;
    VBModel* innerModel;
} ToppingContainerCellData;

ToppingContainerCellData* ToppingContainerCellDataInit(int _type, int _stepTotal);
void ToppingContainerCellDataReset(ToppingContainerCellData* _data);
void ToppingContainerCellDataFree(ToppingContainerCellData** _data);

class ToppingContainer : public ScrollerContainer {
private:
    Tweener* selectTweener;
    TweenerParam* selectTweenerParam;
    float selectTweenerTime;
    float selectTweenerTimeCount;
    float selectTweenerValue;
    VBModel* selectModel;
    VBModel* selectInnerModel;
    
    void ClearSelectTween();
    void BeginSelectTween(float _value, float _time, bool _is_ease_out);
    void UpdateSelectTween(float _deltaTime);
    
    IceCream* iceCream;
    
public:
    virtual void ResetData();
    
    ToppingContainer(VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data, IceCream* _iceCream);
    ~ToppingContainer();
    
    void SetCook(IceCream* _iceCream);
    
    float getToppingPositionX(int itemIdx);
    
    virtual void Update(float _deltaTime);
    
    virtual void CellAlloc(CellData* _cell);
    virtual void CellFree(CellData* _cell);
    virtual void CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellUpdate(CellData *_cell, float _deltaTime);
};

#endif
