#ifndef gelatomania_SelectUserTable_h
#define gelatomania_SelectUserTable_h

#include "ScrollerContainer.h"
#include "cJSON.h"

class SelectUserTableProtocol {
public:
    virtual void SelectUserTableSelectCell(cJSON* user) {};
};

class SelectUserCell : public VBModel {
public:
    SelectUserTableProtocol* protocol;
    
    VBTexture* tex;
    VBModel* model;
    
    CCTouch* touch;
    
    cJSON* user;
    
    SelectUserCell(cJSON* _user, SelectUserTableProtocol* _protocol);
    ~SelectUserCell();
    
    void TouchBegin(CCTouch* _touch, CCPoint _location);
    void TouchMove(CCTouch* _touch, CCPoint _location);
    void TouchEndAndCancel(CCTouch* _touch, CCPoint _location);
};

class SelectUserTable : public ScrollerContainer {
    SelectUserTableProtocol* protocol;
    VBObjectFile2D* objCell;
    VBTexture* texCell;
public:
    virtual void CellAlloc(CellData* _cell);
    virtual void CellFree(CellData* _cell);
    virtual void CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location);
    
    SelectUserTable(VBObjectFile2D* _objCell, VBTexture* _texCell, VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data, SelectUserTableProtocol* _protocol);
    ~SelectUserTable();
};

#endif
