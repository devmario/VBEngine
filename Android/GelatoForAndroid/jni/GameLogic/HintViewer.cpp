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
        
        //TODO: set arrow position        
        position[hintStateItem] = CCPointMake(350.0, 0.0);
        position[hintStateIceCream] = CCPointMake(250, -170);
        position[hintStateTop] = CCPointMake(350.0, 0.0);
        position[hintStateDown] = CCPointMake(350.0, -260.0);
        position[hintStateTopping] = CCPointMake(350.0, 0.0);
        position[hintStateLeft] = CCPointMake(350.0, 0.0);
        position[hintStateRight] = CCPointMake(350.0, 0.0);
        position[hintStateReset] = CCPointMake(40.0, -205.0);
        
        for (int i=0; i<8; i++) {
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
    
    for (int i=0; i<8; i++) {
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
        case hintStateTopping:
            break;
        case hintStateLeft:
            break;
        case hintStateRight:
            break;
        case hintStateReset:
            break;
        default:
            break;
    }
}

void HintViewer::initStep() {
    currentSolutionIdx = 1;
}

void HintViewer::complete() {
    
}

bool HintViewer::step(int itemIdx)
{
    // -1: add icecream
    // -2: topping
    // -3: reset icecream
    // -4: remove mask
    
//    cout << "hintViewer::step(" << itemIdx << ") ==> " << solution[currentSolutionIdx];
//    cout << "\n  next ==> " << solution[currentSolutionIdx+1];
    bool returnValue = false;
    if (itemIdx == -3) {
        initStep();
        setState(hintStateItem);
        returnValue = true;
    } else if (itemIdx == -4) {
        int i = maskStack[1] == -1 ? 0 : 1;
        if (solution[currentSolutionIdx] == maskStack[i]) {
            currentSolutionIdx++;
            maskStack[i] = -1;
            if (i) {
                maskOn = true;
            } else {
                maskOn = false;
            }
        }
        returnValue = true;
    } else if(solution[currentSolutionIdx] == itemIdx) {
        if (isMask[itemIdx]) {
            int i = maskStack[0] == -1 ? 0 : 1;
            maskStack[i] = itemIdx;
            maskOn = true;
        }
        currentSolutionIdx++;
        if(currentSolutionIdx < solutionLen) {
            if(solution[currentSolutionIdx] == -1) {
                currentSolutionIdx++;
            }
            if(currentSolutionIdx >= solutionLen) {
                complete();
            } else {
                /*********************
                 토핑으로 전환하여야 함
                 *********************/
            }
            
            if (maskOn) {
                int i = maskStack[1] == -1 ? 0 : 1;
                if (solution[currentSolutionIdx] == maskStack[i]) {
                    setState(hintStateIceCream);
                }
            }
        }
        
        returnValue = true;
    } else {
        setState(hintStateReset);
        initStep();
        returnValue = false;
    }
    
    if (currentSolutionIdx >= solutionLen) {
        hide();
    }
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
