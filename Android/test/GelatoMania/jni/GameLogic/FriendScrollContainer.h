//
//  FriendScrollContainer.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 13..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_FriendScrollContainer_h
#define gelatomania_FriendScrollContainer_h

#include "ScrollerContainer.h"

class FriendScrollContainer : public ScrollerContainer {
public:
    VBArrayVector* arr_rope;
    void ResetRope();
    
    VBObjectFile2D* objRope;
    VBTexture* texRope;
    
    VBObjectFile2DLibraryNameID* nameRope;
    
    FriendScrollContainer(VBObjectFile2D* _objRope, VBTexture* _texRope, VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data);
    ~FriendScrollContainer();
    
    virtual void ResetData();
    
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
