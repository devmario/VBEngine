//
//  FriendScrollCell.cpp
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 13..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#include "FriendScrollCell.h"
#include "ShareData.h"
#include "Language.h"

FriendScrollCell::FriendScrollCell(VBObjectFile2D* _obj, VBTexture* _tex, cJSON* _info) {
    objCell = _obj;
    texCell = _tex;
    VBString* _str;
    data = _info;
    LIBNAMEFIND(nameCell, _obj, "cell", _str);
    
    modelCell = NULL;
    nameText = NULL;
    infoText = NULL;
    
}

FriendScrollCell::~FriendScrollCell() {
    
}

void FriendScrollCell::AllocCell(CellData* _data) {
    if(modelCell == NULL)
        modelCell = new VBModel(objCell, nameCell, texCell, true);
    modelCell->setPosition(CCPoint(20,0));
    _data->modelCell->addChild(modelCell);
    
    Language* l = Language::shareLanguage();
    if (nameText == NULL) {
        nameText = new Text();
        nameText->SetText(cJSON_GetArrayItem(data, 0)->valuestring, l->GetFontName("type0"), 14, 100, 14, "ffffffff", "ffffffff", VBVector2DCreate(0, 0), -1);
        modelCell->getVBModelByInstanceName("nameText")->addChild(nameText);
    }
    if (infoText == NULL) {
        infoText = new Text();
        infoText->SetText(cJSON_GetArrayItem(data, 1)->valuestring, l->GetFontName("type0"), 9, 100, 9, "ffffffff", "ffffffff", VBVector2DCreate(0, 0), -1);
        modelCell->getVBModelByInstanceName("infoText")->addChild(infoText);
    }
    
    
}

void FriendScrollCell::FreeCell(CellData* _data) {
    if (modelCell) {
//        modelCell->removeAllChildrenWithCleanup(false)
//        if (nameText) {
//            modelCell->getVBModelByInstanceName("nameText")->removeChild(nameText, false);
//            delete nameText;
//            nameText = NULL;
//        }
//        if (infoText) {
//            modelCell->getVBModelByInstanceName("infoText")->removeChild(infoText, false);
//            delete infoText;
//            infoText = NULL;
//        }
        _data->modelCell->removeChild(modelCell, false);
        delete modelCell;
        modelCell = NULL;
        if (nameText) {
            delete nameText;
            nameText = NULL;
        }
        if (infoText) {
            delete infoText;
            infoText = NULL;
        }
    }
    
}