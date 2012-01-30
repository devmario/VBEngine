#ifndef gelatomania_ScrollerContainer_h
#define gelatomania_ScrollerContainer_h

#include "VBModel.h"
#include "Scroller.h"
#include "CppTweener.h"

using namespace tween;

typedef struct CellData {
    int index;
    void* data;
    VBModel* modelCell;
} CellData;

enum ScrollerContainerAlign{
    ScrollerContainerAlign_Vertical         =   0x01,
    ScrollerContainerAlign_Horizontal       =   0x02,
    ScrollerContainerAlign_Inner            =   0x02,
    ScrollerContainerAlign_Outter           =   0x04,
    ScrollerContainerAlign_VI               =   ScrollerContainerAlign_Vertical     | ScrollerContainerAlign_Inner,
    ScrollerContainerAlign_VO               =   ScrollerContainerAlign_Vertical     | ScrollerContainerAlign_Outter,
    ScrollerContainerAlign_HI               =   ScrollerContainerAlign_Horizontal   | ScrollerContainerAlign_Inner,
    ScrollerContainerAlign_HO               =   ScrollerContainerAlign_Horizontal   | ScrollerContainerAlign_Outter,
};

class ScrollerContainer : public VBModel {
    void ReloadData();
    void SetCellValue(CellData* _cell, float _value);
    float GetCellValue(CellData* _cell);
public:
    virtual void ResetData();
    
    //눈에 보이는 Cell: CellData*가 들어있음
    VBArrayVector* cell;
    //UserData
    VBArrayVector* data;
    
    //스크롤바
    Scroller* scroller;
    //스크롤러의 투명도
    float scroller_alpha;
    //스크롤바가 보이는지의 여부
    bool scroller_isShow;
    //유저가 컨트롤을 하지 않을때 스크롤바가 보이는 시간(카운터)
    float scroller_showTime;
    
    //Cell이 Add될 Model
    VBModel* container;
    
    //스크롤러 컨테이너의 방향(테이블과 테이블이 스크롤되는 방향)
    ScrollerContainerAlign align;
    
    CCTouch* touchScroller;
    
    //스크롤 관련 Unit Value
    float width; //스크롤러 컨테이너의 넓이
    float height; //스크롤러 컨테이너의 높이
    float size; //가로형 스크롤러 컨테이너 일대에는 width, 세로형일 때는 height(눈에 보이는 스크롤 되는 방향으로의 사이즈)
    float pageValue; //스크롤된 값이 갱신되는 부동소수점 값
    float prePageValue;
    float pageValueMin; //최소 pageValue값
    float forceValue; //스크롤 할때 유저가 미는 힘값
    float cellSize; //스크롤러 컨테이너의 내부에 있는 하나의 열 또는 행의 넓이 또는 높이
    float cellSizeTotal; //스크롤러 컨테이너의 내부에 있는 모든 행또는 열들의 넓이 또는 높이를 더한 값
    
    float elapseTime;
    Tweener slideTween;
    TweenerParam param;
    TweenerParam* runparam;
    
    float touchY;
    
    float margin;
    float marginDirBegin;
    float marginDirEnd;
    
    ScrollerContainer(VBObjectFile2D* _objScroller, VBTexture* _texScroller, 
                      VBArrayVector* _data, 
                      float _cellHeight = 50.0, 
                      float _width = 100.0, float _height = 100.0, 
                      float _margin = 5.0, float _marginDirBegin = 5.0, float _marginDirEnd = 5.0,
                      ScrollerContainerAlign _align = ScrollerContainerAlign_VO,
                      bool _is_center_cell = false);
    ~ScrollerContainer();
    
    bool enable;
    
    bool GetEnable();
    void SetEnable(bool _enable);
    
    void NextPage();
    void PrevPage();
    bool IsPossibleNextPage();
    bool IsPossiblePrevPage();
    
    bool IsVertical();
    bool IsInner();
    
    void ShowScrollBarMoment(float _time);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
    
    virtual void CellAlloc(CellData* _cell);
    virtual void CellFree(CellData* _cell);
    virtual void CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellUpdate(CellData* _cell, float _deltaTime);
};

#endif
