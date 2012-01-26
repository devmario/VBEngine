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
/*
 * scroller container class
 */
class ShopScrollerContainer;
typedef struct ShopCellData {
    int idx;
    int price;
    VBString *title;
    VBString *description;
    VBString *thumbnailPath;
    
    CCTouch *touch;
    bool scrollFlag;
    
    VBObjectFile2DLibraryNameID *thumbnailLibNameId;
    VBObjectFile2D *thumbnailObj;
    VBTexture *thumbnailTex;
    
    VBModel *thumbnailModel;
    VBModel *bgModel;
    
    ShopScrollerContainer *container;
} ShopCellData;
ShopCellData* ShopCellDataInit(int idx, VBObjectFile2D *_obj, VBTexture *_tex);
void ShopCellDataFree(ShopCellData **data);
class ShopScrollerContainer : public ScrollerContainer {
private:
    
public:
    //for cell
    VBObjectFile2DLibraryNameID *cellLibNameId;
    VBObjectFile2D *cellBgObj;
    VBTexture *cellBgTex;
    //
    ShopScrollerContainer(VBObjectFile2D *_obj, VBTexture *_tex, VBObjectFile2D *_objScroller, VBTexture *_texScroller, VBArrayVector *_data);
    ~ShopScrollerContainer();
    
    virtual void CellAlloc(CellData* _cell);
    virtual void CellFree(CellData* _cell);
    virtual void CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellUpdate(CellData* _cell, float _deltaTime);
};

#endif
