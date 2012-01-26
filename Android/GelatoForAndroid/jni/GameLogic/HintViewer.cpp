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
        solutionFlag = false;
        initStep();
        
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
        
        showFlag = false;
        if(_showFlag) {
            show();
        }
        
        solution = NULL;
    }
}

HintViewer::~HintViewer()
{
    hide();
    
    for (int i=0; i<4; i++) {
        delete arrowModel[i];
    }
    
    VBObjectFile2DFree(&object);
    VBTextureFree(&texture);
    
    if (solutionFlag) {
        free(solution);
    }
}

void HintViewer::show()
{
    if(!showFlag) {
        showFlag = true;
        parent->top->addChild(arrowModel[state]);
    }
    
}

void HintViewer::hide()
{
    if(showFlag) {
        showFlag = false;
        parent->top->removeChild(arrowModel[state], false);
    }
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

void HintViewer::initStep() {
    currentSolutionIdx = 0;
}

bool HintViewer::step(int itemIdx)
{
    if(solution[currentSolutionIdx] == itemIdx) { 
        currentSolutionIdx++;
        if(currentSolutionIdx < solutionLen) {
            if(solution[currentSolutionIdx] == -1) {
                currentSolutionIdx++;
            }
            if(currentSolutionIdx >= solutionLen) {
                initStep();
            } else {
                /*********************
                 토핑으로 전환하여야 함
                 *********************/
            }
            printf("hint step: %d, %d\n", currentSolutionIdx, solution[currentSolutionIdx]);
        }
        return true;
    } else {
        /**********************************************
         새로운 아이스크림 나오는 버튼으로 힌트 전환 하여야 함
         **********************************************/
        initStep();
        return false;
    }
}

void HintViewer::setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen)
{
    int preFlag = showFlag;
    if(preFlag)
        hide();
    // -1: add icecream
    // -2: topping
    // -3: reset icecream
    solutionLen = 0;
    for(int i = 0; i < recipeLen; i++) {
        solutionLen += recipeArrLen[i];
    }
    if(toppingLen > 0) {
        solutionLen++;
        solutionLen += toppingLen;
    }
    
    if(solution)
        free(solution);
    solution = (int*)malloc(sizeof(int)*solutionLen);
    
    int idx=0;
    for (int i=0; i < recipeLen; i++) {
        for (int j=0; j<recipeArrLen[i]; j++) {
            solution[idx] = recipe[i][j];
            idx++;
        }
    }
    if(toppingLen > 0) {
        /**************************
         -1은 토핑이 시작된다는 의미
         **************************/
        solution[idx] = -1;
        idx++;
        for(int i=0; i<toppingLen; i++) {
            solution[idx] = topping[i];
            idx++;
        }
    }
    initStep();
    
    printf("solution: ");
    for (int i=0; i<solutionLen; i++) {
        printf("%d ", solution[i]);
    }
    printf("\n");
    
    if(preFlag)
        show();
}
