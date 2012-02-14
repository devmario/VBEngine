//
//  FriendScrollCell.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 13..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_FriendScrollCell_h
#define gelatomania_FriendScrollCell_h

#include "VBModel.h"
#include "ScrollerContainer.h"
#include "cJSON.h"
#include "Text.h"

class FriendScrollCell {
    cJSON *data;
public:
    VBObjectFile2D* objCell;
    VBTexture* texCell;
    
    VBObjectFile2DLibraryNameID* nameCell;
    
    VBModel* modelCell;
    Text* nameText;
    Text* infoText;
    
    FriendScrollCell(VBObjectFile2D* _obj, VBTexture* _tex, cJSON* _info);
    ~FriendScrollCell();
    
    void AllocCell(CellData* _data);
    void FreeCell(CellData* _data);
};

#endif
