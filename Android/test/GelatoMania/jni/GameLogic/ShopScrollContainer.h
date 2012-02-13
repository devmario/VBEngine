//
//  ShopScrollContainer.h
//  gelatomania
//
//  Created by Kyung Gak Nam on 12. 1. 11..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_ShopScrollContainer_h
#define gelatomania_ShopScrollContainer_h

#include "ScrollerContainer.h"
#include "Text.h"
#include "cJSON.h"
/*
 * scroller container class
 */
class ShopScrollerContainer;
typedef struct ShopCellData {
    int idx;
    
    VBString *thumbnailPath;
    
    CCTouch *touch;
    bool scrollFlag;
    
    VBTexture *thumbnailTex;
    
    VBModel *thumbnailModel;
    VBModel *bgModel;
    
    char* title;
    char* descript;
    char* money;
    
    double money_unit;
    
    Text* textTitle;
    Text* textDescript;
    Text* textMoney;
    
    ShopScrollerContainer *container;
} ShopCellData;
ShopCellData* ShopCellDataInit(cJSON* parent, int idx, VBObjectFile2D *_obj, VBTexture *_tex);
void ShopCellDataFree(ShopCellData **data);
class ShopScrollerContainer : public ScrollerContainer {
private:
    
public:
    virtual void ResetData();
    
    float tap_pageValue[3];
    
    VBArrayVector* arr_rope;
    void ResetRope();
    
    //for cell
    VBObjectFile2DLibraryNameID *cellLibNameId;
    VBObjectFile2DLibraryNameID *ropeLibNameId;
    VBObjectFile2D *cellBgObj;
    VBTexture *cellBgTex;
    //
    ShopScrollerContainer(int _tapIdx, VBObjectFile2D *_obj, VBTexture *_tex, VBObjectFile2D *_objScroller, VBTexture *_texScroller, VBArrayVector *_data);
    ~ShopScrollerContainer();
    
    VBArrayVector* topData;
    int tapIdx;
    void SetTapIdx(int _tapIdx);
    
    virtual void Update(float _deltaTime);
    
    virtual void CellAlloc(CellData* _cell);
    virtual void CellFree(CellData* _cell);
    virtual void CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellUpdate(CellData* _cell, float _deltaTime);
};

#endif
