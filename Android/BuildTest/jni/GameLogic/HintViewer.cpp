//
//  HintViewer.cpp
//  gelatomania
//
//  Created by Kyung Gak Nam on 12. 1. 17..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#include "HintViewer.h"
#include "ShareData.h"
#include "GameMain.h"

HintViewer::HintViewer(GameMain *_parentModel, bool _showFlag, VBObjectFile2D *_obj, VBTexture *_tex, const char *iceModelName, const char *itemModelName, const char *topModelName, const char *downModelName)
{
    if (_parentModel) {
        VBObjectFile2DLibraryNameID *_library_name_id = NULL;
        VBString *_str = NULL;
        state = hintStateItem;
        rotationR = 0.0;
        showFlag = _showFlag;
        solutionFlag = false;
        
        if (_obj && _tex) {
            object = _obj;
            texture = _tex;
        } else {
            OBJLOAD(object, "hintPoint.obj", _str);
            TEXLOAD(texture, "hintPoint.png", _str);
        }
        parent = _parentModel;
        
        const char *iceName = iceModelName ? iceModelName : "pointIce";
        const char *itemName = itemModelName ? itemModelName : "pointItem";
        const char *topName = topModelName ? topModelName : "pointTop";
        const char *downName = downModelName ? downModelName : "pointDown";
        
        LIBNAMEFIND(_library_name_id, object, iceName, _str);
        arrowModel[hintStateIceCream] = new VBModel(object, _library_name_id, texture, true);
        LIBNAMEFIND(_library_name_id, object, itemName, _str);
        arrowModel[hintStateItem] = new VBModel(object, _library_name_id, texture, true);
        LIBNAMEFIND(_library_name_id, object, topName, _str);
        arrowModel[hintStateTop] = new VBModel(object, _library_name_id, texture, true);
        LIBNAMEFIND(_library_name_id, object, downName, _str);
        arrowModel[hintStateDown] = new VBModel(object, _library_name_id, texture, true);
        
        //TODO: set arrow position        
        position[hintStateItem] = CCPointMake(350.0, 0.0);
        position[hintStateTop] = CCPointMake(350.0, 0.0);
        position[hintStateDown] = CCPointMake(350.0, -260.0);
        position[hintStateIceCream] = CCPointMake(200, -200);
        for (int i=0; i<4; i++) {
            arrowModel[i]->setScale(0.5f);
            arrowModel[i]->setPosition(position[i]);
        }
        
        
        if (showFlag) {
            HintViewer::show();
        }
    }
}

HintViewer::~HintViewer()
{
    for (int i=0; i<4; i++) {
        parent->top->removeChild(arrowModel[i], false);
        delete arrowModel[i];
    }
    parent = NULL;
    
    VBObjectFile2DFree(&object);
    VBTextureFree(&texture);
    
    if (solutionFlag) {
        free(solution);
    }
}

void HintViewer::show()
{
    showFlag = true;
    parent->top->addChild(arrowModel[state]);
    
}

void HintViewer::hide()
{
    showFlag = false;
    parent->top->removeChild(arrowModel[state], false);
}

void HintViewer::setState(hintStateFlag newState)
{
    if (state != newState) {
        if (showFlag) {
            parent->top->removeChild(arrowModel[state], false);
            parent->top->addChild(arrowModel[newState]);
        }
        state = newState;
    }
}

void HintViewer::setPosition(cocos2d::CCPoint _position)
{
    if (state == hintStateItem) {
        position[state] = _position;
    }
}

void HintViewer::update(float _deltaTime)
{
    int screenHeight = 260;
    switch (state) {
        case hintStateItem:
            if (position[state].y > 0) {
                setState(hintStateTop);
            } else if (position[state].y < screenHeight*(-1)) {
                setState(hintStateDown);
            } else {
                position[state] = CCPointMake(350, parent->getRecipePositionY(solution[currentSolutionIdx])-30);
                arrowModel[state]->setPosition(position[state]);
                arrowModel[state]->setRotation(rotationR);
            }
            
            break;
        case hintStateIceCream:
            break;
        case hintStateTop:
            position[hintStateItem] = CCPointMake(350, parent->getRecipePositionY(solution[currentSolutionIdx])-30);
            if (position[hintStateItem].y < 0) {
                setState(hintStateItem);
            }
            break;
        case hintStateDown:
            position[hintStateItem] = CCPointMake(350, parent->getRecipePositionY(solution[currentSolutionIdx])-30);
            if (position[hintStateItem].y > screenHeight*(-1)) {
                setState(hintStateItem);
            }
            break;
        default:
            break;
    }
}

void HintViewer::step(int itemIdx)
{
    printf("hint step: %d, %d\n", currentSolutionIdx, solution[currentSolutionIdx]);
    if (itemIdx == solution[currentSolutionIdx]) {
        currentSolutionIdx++;
    } else {
        currentSolutionIdx = 0;
    }
}

void HintViewer::setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen)
{
    // -1: add icecream
    // -2: topping
    // -3: reset icecream
    solutionLen = recipeArrLen[0];
    if (recipeLen) {
        for (int i=1; i<recipeLen; i++) {
            solutionLen += recipeArrLen[i] + 1;
        }
    }
    if (toppingLen) {
        solutionLen = toppingLen+1;
        
    }
    
    solution = (int*)malloc(sizeof(int)*solutionLen);
    
    int idx=0;
    for (int i=0; i<recipeLen; i++) {
        if (i != 0) {
            solution[idx] = -1;
            idx++;
        }
        for (int j=0; j<recipeArrLen[i]; j++) {
            solution[idx] = recipe[i][j];
            idx++;
        }
    }
    if (toppingLen) {
        solution[idx] = -2;
        idx++;
        for (int i=0; i<toppingLen; i++) {
            solution[idx] = topping[i];
            idx++;
        }
    }
    solutionFlag = true;
    currentSolutionIdx = 1;
    
    printf("solution: ");
    for (int i=0; i<solutionLen; i++) {
        printf("%d ", solution[i]);
    }
    printf("\n");
}
