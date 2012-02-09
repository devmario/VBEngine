#include "HintViewer.h"
#include "ShareData.h"
#include "GameMain.h"
#include "cJSON.h"

HintViewer::HintViewer(GameMain *_gameMain, bool _showFlag) {
    if (_gameMain) {
        retainCount = 1;
        
        hintState = hintStateItem;
        solution = NULL;
        isMask = NULL;
        
        setGameMain(_gameMain);
        loadArrowModel();
        loadMaskList();
        initStep(false);
        
        showFlag = _showFlag;
        
    }
}

HintViewer::~HintViewer() {
    hide();
    
    for (int i=0; i<HINTSTATELEN; i++) {
        delete arrowModel[i];
    }
    
    VBObjectFile2DFree(&object);
    VBTextureFree(&texture);
    
    if (solution) {
        free(solution);
    }
    if (isMask) {
        free(isMask);
    }
    
}

void HintViewer::loadArrowModel() {
    VBObjectFile2DLibraryNameID *_library_name_id = NULL;
    VBString *_str = NULL;
    
    OBJLOAD(object, "hintPoint.obj", _str);
    TEXLOAD(texture, "hintPoint.png", _str);
    
    LIBNAMEFIND(_library_name_id, object, "pointIce", _str);
    arrowModel[hintStateIceCream] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointItem", _str);
    arrowModel[hintStateItem] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointTop", _str);
    arrowModel[hintStateTop] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointDown", _str);
    arrowModel[hintStateDown] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointTopping", _str);
    arrowModel[hintStateTopping] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointLeft", _str);
    arrowModel[hintStateLeft] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointRight", _str);
    arrowModel[hintStateRight] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointReset", _str);
    arrowModel[hintStateReset] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointAdd", _str);
    arrowModel[hintStateAdd] = new VBModel(object, _library_name_id, texture, true);
    LIBNAMEFIND(_library_name_id, object, "pointTopping", _str);
    arrowModel[hintStateToppingItem] = new VBModel(object, _library_name_id, texture, true);
    
    position[hintStateItem] = CCPointMake(364.0, 0.0);
    position[hintStateIceCream] = CCPointMake(280, -178);
    position[hintStateTop] = CCPointMake(395.0, -36.0);
    position[hintStateDown] = CCPointMake(395.0, -258.0);
    position[hintStateTopping] = CCPointMake(320.0, -66.0);
    position[hintStateLeft] = CCPointMake(119.0, -24.0);
    position[hintStateRight] = CCPointMake(337.0, -24.0);
    position[hintStateReset] = CCPointMake(52.0, -203.0);
    position[hintStateAdd] = CCPointMake(186.0, -72.0);
    position[hintStateToppingItem] = CCPointMake(0.0, -77.0);
    
    for (int i=0; i<HINTSTATELEN; i++) {
        arrowModel[i]->setScale(0.5f);
        arrowModel[i]->setPosition(position[i]);
    }
}

void HintViewer::loadMaskList() {
    cJSON *recipeJSON = cJSON_GetObjectItem(ShareDataGetRes(), "recipe");
    int recipeLen = cJSON_GetArraySize(recipeJSON);
    
    if (isMask) {
        free(isMask);
        isMask = NULL;
    }
    isMask = (bool*)malloc(sizeof(bool)*recipeLen);
    for (int i=0; i<recipeLen; i++) {
        int temp = cJSON_GetArrayItem(cJSON_GetArrayItem(recipeJSON, i), 1)->valueint;
        if (temp == 1) {
            isMask[i] = true;
        } else {
            isMask[i] = false;
        }
    }
    maskStack[0] = -1;
    maskStack[1] = -1;
    maskOn = false;
}


void HintViewer::setState(hintStateFlag newState)
{
    if (hintState != newState) {
        if (showFlag) {
            gameMain->top->removeChild(arrowModel[hintState], false);
            gameMain->top->addChild(arrowModel[newState]);
        }
        if (newState == hintStateIceCream) {
            
        }
        hintState = newState;
    }
}

void HintViewer::update(float _deltaTime)
{
    const float screenHeight = 260.0, screenWidth = 255.0;
    const float recipeContainerInterval = -30.0, toppingContainerInterval = 90.0;
    
    switch (hintState) {
        //Recipe Container Point
        case hintStateItem:
            if (position[hintState].y >= 0) {
                setState(hintStateTop);
            } else if (position[hintState].y <= screenHeight*(-1)) {
                setState(hintStateDown);
            } else {
                position[hintState].y = gameMain->getRecipePositionY(solution[currentSolutionIdx]) + recipeContainerInterval;
                arrowModel[hintState]->setPosition(position[hintState]);
            }
            
            break;
        case hintStateTop:
            position[hintStateItem].y = gameMain->getRecipePositionY(solution[currentSolutionIdx]) + recipeContainerInterval;
            if (position[hintStateItem].y < 0) {
                setState(hintStateItem);
            }
            break;
        case hintStateDown:
            position[hintStateItem].y = gameMain->getRecipePositionY(solution[currentSolutionIdx]) + recipeContainerInterval;
            if (position[hintStateItem].y > screenHeight*(-1)) {
                setState(hintStateItem);
            }
            break;
            
        //Topping Container Point
        case hintStateToppingItem:
            if (position[hintState].x <= toppingContainerInterval - 5) {
                setState(hintStateLeft);
            } else if (position[hintState].x >= screenWidth + toppingContainerInterval) {
                setState(hintStateRight);
            } else {
                position[hintState].x = gameMain->getToppingPositionX(solution[currentSolutionIdx]) + toppingContainerInterval;
                arrowModel[hintState]->setPosition(position[hintState]);
            }
            break;
        case hintStateLeft:
            position[hintStateToppingItem].x = gameMain->getToppingPositionX(solution[currentSolutionIdx]) + toppingContainerInterval;
            if (position[hintStateToppingItem].x > toppingContainerInterval - 5) {
                setState(hintStateToppingItem);
            }
            break;
        case hintStateRight:
            position[hintStateToppingItem].x = gameMain->getToppingPositionX(solution[currentSolutionIdx]) + toppingContainerInterval;
            if (position[hintStateToppingItem].x < screenWidth + toppingContainerInterval) {
                setState(hintStateToppingItem);
            }
            break;
            
        case hintStateIceCream:case hintStateTopping:case hintStateReset:default:break;
    }
}

void HintViewer::initStep(bool isWrongStep) {
    if (!isWrongStep) {
        setState(hintStateItem);
    } else {
        setState(hintStateReset);
    }
    currentSolutionIdx = 1;
    maskStack[0] = -1;
    maskStack[1] = -1;
    maskOn = false;
    
    wrongMode = hintWrongNone;
    wrongIdx = -1;
    wrongIdxForMask = -1;
    lastAction = actionTypeNone;
}

void HintViewer::step(actionType currentAction, int itemIdx)
{
    // -1: add icecream
    // -2: topping
    switch (hintState) {
        case hintStateItem:case hintStateTop:case hintStateDown:
            if (solution[currentSolutionIdx] == itemIdx) {
                //check mask
                if (isMask[itemIdx])
                    pushMask(itemIdx);
                
                currentSolutionIdx++;
                
                if (solution[currentSolutionIdx] == -1) {
                    //go to add
                    setState(hintStateAdd);
                } else if (solution[currentSolutionIdx] == -2) {
                    //go to topping
                    setState(hintStateTopping);
                } else if (isMask[solution[currentSolutionIdx]] && solution[currentSolutionIdx] == maskStack[maskStack[1] == -1 ? 0 : 1]) {
                    //go to mask off
                    setState(hintStateIceCream);
                }
            } else {
                if (isMask[itemIdx]) {
                    if (currentAction == actionTypeIceCream) {
                        wrongStep(hintWrongMaskOff, itemIdx);
                    } else if (currentAction == actionTypeRecipe) {
                        wrongStep(hintWrongMaskOn, itemIdx);
                    }
                } else {
                    initStep(true);
                }
            }
            break;
        case hintStateIceCream:
            //mask off
            if (solution[currentSolutionIdx] == itemIdx) {
                currentSolutionIdx++;
                popMask();
                if (isMask[solution[currentSolutionIdx]] && solution[currentSolutionIdx] == maskStack[0]){
                    
                }
                else if (solution[currentSolutionIdx] == -1) {
                    setState(hintStateAdd);
                } else if (solution[currentSolutionIdx] == -2) {
                    setState(hintStateTopping);
                } else {
                    setState(hintStateItem);
                }
            } else {
                if (isMask[itemIdx]) {
                    if (currentAction == actionTypeIceCream) {
                        wrongStep(hintWrongMaskOff, itemIdx);
                    } else if (currentAction == actionTypeRecipe) {
                        wrongStep(hintWrongMaskOnDouble, itemIdx);
                    }
                } else {
                    initStep(true);
                }
            }
            break;
        case hintStateToppingItem:case hintStateLeft:case hintStateRight:
            if (solution[currentSolutionIdx] == itemIdx) {
                currentSolutionIdx++;
            } else {
                initStep(true);
            }
            break;
        default:
            break;
    }
    
    lastAction = currentAction;
    checkAndFinish();
    
}

void HintViewer::wrongStep(hintStepWrongLevel _wrongType, int _wrongIdx)
{
    if (wrongMode == hintWrongNone) {   //처음 틀렸을때
        wrongMode = _wrongType;
        wrongIdx = _wrongIdx;
        switch (_wrongType) {
            case hintWrongMaskOn: //마스크를 잘못 씌웠을때
                pushMask(_wrongIdx);
                setState(hintStateIceCream);
                break;
            case hintWrongMaskOff: //마스크를 잘못 벗겼을때
                popMask();
                currentSolutionIdx--;
                wrongMode = hintWrongNone;
                setState(hintStateItem);
                break;
            default:
                break;
        }
    } else {
        switch (wrongMode) {
            case hintWrongMaskOn: //이전에 마스크를 잘못 씌웠을때
                if (_wrongType == hintWrongMaskOnDouble) {    //마스크를 잘못 씌우고 또 잘못 씌웠을때
                    pushMask(_wrongIdx);
                    wrongIdxForMask = _wrongIdx;
                    wrongMode = hintWrongMaskOnDouble;
                } else if (_wrongType == hintWrongMaskOff) {    //잘못 씌우고 벗겼을때
                    popMask();
                    setState(hintStateItem);
                    wrongMode = hintWrongNone;
                } else {    //마스크를 잘못 씌우고 다른걸 칠했을때(reset)
                    initStep(true);
                }
                
                break;
            case hintWrongMaskOnDouble: //마스크를 두번 잘못 씌웠을때
                if (_wrongType == hintWrongMaskOff) {   //하나를 벗겼을때
                    wrongMode = hintWrongMaskOn;
                    wrongIdxForMask = -1; 
                } else {    //안벗기고 다른거 칠할때
                    initStep(true);
                }
                break;
            case hintWrongMaskOff:  //이전에 마스크를 잘못 벗겼을때
                if (wrongIdx == _wrongIdx) {    //다시 씌웠을때
                    pushMask(_wrongIdx);
                    wrongMode = hintWrongNone;
                } else {
                    initStep(true);
                }
                break;
            default:
                initStep(true);
                break;
        }
    }
    
}


actionType HintViewer::getLastActionType() {
    return lastAction;
}

void HintViewer::resetAction() {
    initStep(false);
}

void HintViewer::iceCreamAction(int itemIdx) {
    step(actionTypeIceCream, itemIdx);
}
void HintViewer::recipeContainerAction(int itemIdx) {
    if (itemIdx == -1) {    //add icecream
        if (solution[currentSolutionIdx] == itemIdx) {
            currentSolutionIdx++;
            switch (solution[currentSolutionIdx]) {
                    //go to add (not change state)
                case -1:
                    break;
                    //go to topping
                case -2:
                    setState(hintStateTopping);
                    break;
                    //go to item
                case 0:
                    currentSolutionIdx++;
                    setState(hintStateItem);
                default:
                    setState(hintStateItem);
                    break;
            }
        } else {
            initStep(true);
        }
    } else if (itemIdx == -2) { //go to topping
        if (solution[currentSolutionIdx] == itemIdx) {
            currentSolutionIdx++;
            setState(hintStateToppingItem);
        } else {
            initStep(true);
        }
    } else {
        step(actionTypeRecipe, itemIdx);
    }
}
void HintViewer::toppingAction(int itemIdx) {
    step(actionTypeTopping, itemIdx);
}

void HintViewer::setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen)
{
    bool preFlag = showFlag;
    if(preFlag)
        hide();
    solutionLen = 0;
    for(int i = 0; i < recipeLen; i++) {
        solutionLen += recipeArrLen[i];
        if (i < recipeLen-1) {
            solutionLen++;
        }
    }
    if(toppingLen > 0) {
        solutionLen++;
        solutionLen += toppingLen;
    }
    
    if(solution) {
        free(solution);
        solution = NULL;
    }
    solution = (int*)malloc(sizeof(int)*solutionLen);
    
    int idx=0;
    for (int i=0; i < recipeLen; i++) {
        for (int j=0; j<recipeArrLen[i]; j++) {
            solution[idx] = recipe[i][j];
            idx++;
        }
        if (i < recipeLen - 1) {
            solution[idx] = -1;
            idx++;
        }
    }
    if(toppingLen > 0) {
        solution[idx] = -2;
        idx++;
        for(int i=0; i<toppingLen; i++) {
            solution[idx] = topping[i];
            idx++;
        }
    }    
    if(preFlag)
        show();
    
}

// stack안의 갯수를 return. exception=-1
int HintViewer::pushMask(int maskIdx) {
    if (maskStack[1] == -1) {
        int temp = maskStack[0] == -1 ? 0 : 1;
        maskStack[temp] = maskIdx;
        maskOn = true;
        return temp+1;
    } else 
        return -1;
//    printf("mask[0]: %d, mask[1]: %d, maskOn: %s\n", maskStack[0], maskStack[1], maskOn ? "true" : "false");
}
int HintViewer::popMask(int *maskIdx) {
    if (maskStack[0] == -1)
        return -1;
    else {
        int temp = maskStack[1] == -1 ? 0 : 1;
        if (maskIdx) {
            *maskIdx = maskStack[temp];
        }
        maskStack[temp] = -1;
        maskOn = temp ? true : false;
        return temp;
    }
}

void HintViewer::setGameMain(GameMain* _gameMain) {
    gameMain = _gameMain;
}

void HintViewer::checkAndFinish() {
    if (currentSolutionIdx >= solutionLen) {
        hide();
        currentSolutionIdx = 0;
    }
}

void HintViewer::show() {
    if(!showFlag) {
        showFlag = true;
        gameMain->top->addChild(arrowModel[hintState]);
    }
    
}

void HintViewer::hide() {
    if(showFlag) {
        showFlag = false;
        gameMain->top->removeChild(arrowModel[hintState], false);
    }
}

void HintViewer::retain() {
    if (retainCount > 0) {
        retainCount++;
    }
}

void HintViewer::release() {
    if (retainCount > 1) {
        hide();
        retainCount--;
    } else if (retainCount == 1) {
        delete this;
    }
}

