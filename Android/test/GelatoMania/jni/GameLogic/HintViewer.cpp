#include "HintViewer.h"
#include "ShareData.h"
#include "GameMain.h"
#include "cJSON.h"

HintViewer::HintViewer(GameMain *_parentModel, bool _showFlag, VBObjectFile2D *_obj, VBTexture *_tex)
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
        //TODO: set arrow position        
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
        
        showFlag = false;
        if(_showFlag) {
            show();
        }
        
        solution = NULL;
        
        cJSON *recipeJSON = cJSON_GetObjectItem(ShareDataGetRes(), "recipe");
        int recipeLen = cJSON_GetArraySize(recipeJSON);
        
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
}

HintViewer::~HintViewer()
{
    hide();
    
    for (int i=0; i<HINTSTATELEN; i++) {
        delete arrowModel[i];
    }
    
    VBObjectFile2DFree(&object);
    VBTextureFree(&texture);
    
    if (solutionFlag) {
        free(solution);
    }
    free(isMask);
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
    float screenHeight = 260.0;
    float screenWidth = 255.0;
    float recipeContainerInterval = -30.0;
    float toppingContainerInterval = 90.0;
    switch (state) {
        //Recipe Container Point
        case hintStateItem:
            if (position[state].y >= 0) {
                setState(hintStateTop);
            } else if (position[state].y <= screenHeight*(-1)) {
                setState(hintStateDown);
            } else {
                position[state].y = parent->getRecipePositionY(solution[currentSolutionIdx]) + recipeContainerInterval;
                arrowModel[state]->setPosition(position[state]);
                arrowModel[state]->setRotation(rotationR);
            }
            
            break;
        case hintStateTop:
            position[hintStateItem].y = parent->getRecipePositionY(solution[currentSolutionIdx]) + recipeContainerInterval;
            if (position[hintStateItem].y < 0) {
                setState(hintStateItem);
            }
            break;
        case hintStateDown:
            position[hintStateItem].y = parent->getRecipePositionY(solution[currentSolutionIdx]) + recipeContainerInterval;
            if (position[hintStateItem].y > screenHeight*(-1)) {
                setState(hintStateItem);
            }
            break;
            
        //Topping Container Point
        case hintStateToppingItem:
            if (position[state].x <= toppingContainerInterval - 5) {
                setState(hintStateLeft);
            } else if (position[state].x >= screenWidth + toppingContainerInterval) {
                setState(hintStateRight);
            } else {
                position[state].x = parent->getToppingPositionX(solution[currentSolutionIdx]) + toppingContainerInterval;
                arrowModel[state]->setPosition(position[state]);
            }
            break;
        case hintStateLeft:
            position[hintStateToppingItem].x = parent->getToppingPositionX(solution[currentSolutionIdx]) + toppingContainerInterval;
            if (position[hintStateToppingItem].x > toppingContainerInterval - 5) {
                setState(hintStateToppingItem);
            }
            break;
        case hintStateRight:
            position[hintStateToppingItem].x = parent->getToppingPositionX(solution[currentSolutionIdx]) + toppingContainerInterval;
            if (position[hintStateToppingItem].x < screenWidth + toppingContainerInterval) {
                setState(hintStateToppingItem);
            }
            break;
            
        case hintStateIceCream:case hintStateTopping:case hintStateReset:default:break;
    }
}

void HintViewer::initStep() {
    setState(hintStateItem);
    currentSolutionIdx = 1;
    maskStack[0] = -1;
    maskStack[1] = -1;
    maskOn = false;
}


bool HintViewer::step(int itemIdx)
{
    // -1: add icecream
    // -2: topping
    // -3: reset icecream
    // -4: remove mask
    bool returnValue = true;
    int tempI = 0;
    
    if (itemIdx == -3) {
        initStep();
        return false;
    }
    
    switch (state) {
        case hintStateItem:case hintStateTop:case hintStateDown:
            if (solution[currentSolutionIdx] == itemIdx) {
                //check mask
                if (isMask[itemIdx]) {
                    tempI = maskStack[0] == -1 ? 0 : 1;
                    maskStack[tempI] = itemIdx;
                    maskOn = true;
                    printf("mask[0]: %d, mask[1]: %d, maskOn: %s\n", maskStack[0], maskStack[1], maskOn ? "true" : "false");
                }
                currentSolutionIdx++;
                
                tempI = maskStack[1] == -1 ? 0 : 1;
                
                if (solution[currentSolutionIdx] == -1) {
                    //go to add
                    setState(hintStateAdd);
                } else if (solution[currentSolutionIdx] == -2) {
                    //go to topping
                    setState(hintStateTopping);
                } else if (isMask[solution[currentSolutionIdx]] && solution[currentSolutionIdx] == maskStack[tempI]) {
                    //go to mask off
                    setState(hintStateIceCream);
                }
            } else {
                returnValue = wrongStep();
            }
            break;
        case hintStateAdd:
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
                returnValue = wrongStep();
            }
            break;
        case hintStateIceCream:
            //mask off
            if (solution[currentSolutionIdx] == itemIdx) {
                currentSolutionIdx++;
                tempI = maskStack[1] == -1 ? 0 : 1;
                maskStack[tempI] = -1;
                if (tempI == 0) {
                    maskOn = false;
                }
                printf("mask[0]: %d, mask[1]: %d, maskOn: %s\n", maskStack[0], maskStack[1], maskOn ? "true" : "false");
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
                returnValue = wrongStep();
            }
            break;
        case hintStateTopping:
            if (itemIdx == -2) {
                currentSolutionIdx++;
                setState(hintStateToppingItem);
            } else {
                returnValue = wrongStep();
            }
            break;
        case hintStateToppingItem:case hintStateLeft:case hintStateRight:
            if (solution[currentSolutionIdx] == itemIdx) {
                currentSolutionIdx++;
            } else {
                returnValue = wrongStep();
            }
            break;
        default:
            break;
    }
    
    checkAndFinish();
    return returnValue;
    
    
}

void HintViewer::setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen)
{
    int preFlag = showFlag;
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
    
    if(solutionFlag) {
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
    initStep();
    solutionFlag = true;
//    printf("solution: ");
//    for (int i=0; i<solutionLen; i++) {
//        printf("%d ", solution[i]);
//    }
//    printf("\n");
    
    if(preFlag)
        show();
    
}

bool HintViewer::wrongStep()
{
    initStep();
    setState(hintStateReset);
    return false;
}

void HintViewer::checkAndFinish()
{
    if (currentSolutionIdx >= solutionLen) {
        hide();
        currentSolutionIdx = 0;
    }
}
