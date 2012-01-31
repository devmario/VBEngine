#include "GameMain.h"
#include "ShareData.h"

//#define GAME_MAIN_EMPTY
#define HINT_COMPLETE

int RecipeSort(const void* _a, const void* _b) {
    RecipeContainerCellData** _cd1 = (RecipeContainerCellData**)_a;
    RecipeContainerCellData** _cd2 = (RecipeContainerCellData**)_b;
    return (*_cd1)->recipeIdx - (*_cd2)->recipeIdx; 
}

int ToppingSort(const void* _a, const void* _b) {
    ToppingContainerCellData** _td1 = (ToppingContainerCellData**)_a;
    ToppingContainerCellData** _td2 = (ToppingContainerCellData**)_b;
    return (*_td1)->type - (*_td2)->type; 
}

void GameMain::LoadResource(cJSON* _layer, cJSON* _ui) {
    VBString* _str;
    
    bgLen = cJSON_GetArraySize(_layer);
    objBg = (VBObjectFile2D**)calloc(bgLen, sizeof(VBObjectFile2D*));
    texBg = (VBTexture**)calloc(bgLen, sizeof(VBTexture*));
    char _buf[0xFF] = {NULL,};
    for(int i = 0; i < bgLen; i++) {
        memset(_buf, 0, 0xFF);
        sprintf(_buf, "%s.obj", cJSON_GetArrayItem(_layer, i)->valuestring);
        OBJLOAD(objBg[i], _buf, _str);
        if(objBg[i] == NULL) {
            cout << _buf << "가 없음.\n";
        }
        memset(_buf, 0, 0xFF);
        sprintf(_buf, "%s.png", cJSON_GetArrayItem(_layer, i)->valuestring);
        TEXLOAD(texBg[i], _buf, _str);
        if(texBg[i] == NULL) {
            cout << _buf << "가 없음.\n";
        }
    }
    
    memset(_buf, 0, 0xFF);
    sprintf(_buf, "%s.obj", _ui->valuestring);
    OBJLOAD(objUI, _buf, _str);
    if(objUI == NULL) {
        cout << _buf << "가 없음.\n";
    }
    
    memset(_buf, 0, 0xFF);
    sprintf(_buf, "%s.png", _ui->valuestring);
    TEXLOAD(texUI, _buf, _str);
    if(texUI == NULL) {
        cout << _buf << "가 없음.\n";
    }
    
    OBJLOAD(objArm, "obj_arm.obj", _str);
    if(objArm == NULL) {
        cout << "obj_arm.obj" << "가 없음.\n";
    }
    TEXLOAD(texArm, "obj_arm.png", _str);
    if(texArm == NULL) {
        cout << "obj_arm.png" << "가 없음.\n";
    }
    
    OBJLOAD(objFont, "fontGame.obj", _str);
    if(objFont == NULL) {
        cout << "fontGame.obj" << "가 없음.\n";
    }
    TEXLOAD(texFont, "fontGame.png", _str);
    if(texFont == NULL) {
        cout << "fontGame.png" << "가 없음.\n";
    }
    
    OBJLOAD(objScroll, "scroller.obj", _str);
    if(objScroll == NULL) {
        cout << "scroller.obj" << "가 없음.\n";
    }
    TEXLOAD(texScroll, "scroller.png", _str);
    if(texScroll == NULL) {
        cout << "scroller.png" << "가 없음.\n";
    }
}

void GameMain::UnloadResource() {
    VBObjectFile2DFree(&objScroll);
    VBObjectFile2DFree(&objUI);
    VBObjectFile2DFree(&objArm);
    VBObjectFile2DFree(&objFont);
    VBTextureFree(&texUI);
    VBTextureFree(&texArm);
    VBTextureFree(&texFont);
    VBTextureFree(&texScroll);
    for(int i = 0; i < bgLen; i++) {
        VBObjectFile2DFree(&objBg[i]);
        VBTextureFree(&texBg[i]);
    }
}

void GameMain::InitModel(cJSON* _layer, cJSON* _ui) {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _name_id;
    
    modelBg = (VBModel**)calloc(bgLen + 1, sizeof(VBModel*));
    for(int i = 0; i < bgLen; i++) {
        LIBNAMEFIND(_name_id, objBg[i], "obj", _str);
        if(_name_id == NULL) {
            cout << "백그라운드 obj파일에 obj무비클립이 없음.\n";
        }
        modelBg[i] = new VBModel(objBg[i], _name_id, texBg[i], true);
        top->addChild(modelBg[i]);
        modelBg[i]->setPosition(CCPointMake(-1, 2));
    }
    
    LIBNAMEFIND(_name_id, objUI, "ui", _str);
    if(_name_id == NULL) {
        cout << "UI obj파일에 ui무비클립이 없음.\n";
    }
    modelUI = new VBModel(objUI, _name_id, texUI, true);
    modelUI->stop();
    top->addChild(modelUI);
    modelUI->setPosition(CCPointMake(-1, 2));
    
    LIBNAMEFIND(_name_id, objArm, "_dynamic/dyMom_obj_arm", _str);
    if(_name_id == NULL) {
        cout << "Arm obj파일에 _dynamic/dyMom_obj_arm무비클립이 없음.\n";
    }
    modelArm = new VBModel(objArm, _name_id, texArm, true);
    modelUI->getVBModelByInstanceName("arm")->addChild(modelArm);
    modelArm->setIsPlayLoop(false);
    modelArm->stop();
    
    modelPauseButton = modelUI->getVBModelByInstanceName("pause");
    if(modelPauseButton == NULL) {
        cout << "ui무비클립에 pause instance name의 무비클립이 없음.\n";
    }
    modelPauseButton->stop();
    
    modelNewButton = modelUI->getVBModelByInstanceName("restart");
    if(modelPauseButton == NULL) {
        cout << "ui무비클립에 restart instance name의 무비클립이 없음.\n";
    }
    modelNewButton->stop();
    
    if(modelUI->getVBModelByInstanceName("right") == NULL) {
        cout << "ui무비클립에 right instance name의 무비클립이 없음.\n";
    }
    modelUpButton = modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("up");
    if(modelUpButton == NULL) {
        cout << "ui무비클립안의 right instance name안에 up instance name의 무비클립이 없음.\n";
    }
    modelUpButton->gotoAndStop(1.0);
    
    modelDownButton = modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("down");
    if(modelDownButton == NULL) {
        cout << "ui무비클립안의 right instance name안에 down instance name의 무비클립이 없음.\n";
    }
    modelDownButton->gotoAndStop(1.0);
    
    modelDoor = modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("door");
    if(modelDoor == NULL) {
        cout << "ui무비클립안의 right instance name안에 door instance name의 무비클립이 없음.\n";
    }
    modelDoor->setIsPlayLoop(false);
    modelDoor->gotoAndPlay(60);
    
    modelRail = modelUI->getVBModelByInstanceName("rail");
    if(modelRail == NULL) {
        cout << "ui무비클립안에 rail instance name의 무비클립이 없음.\n";
    }
    modelRail->setIsPlayLoop(false);
    modelRail->stop();
    
    if(modelRail->getVBModelByInstanceName("inRail") == NULL) {
        cout << "ui무비클립안의 rail instance name안에 inRail instance name의 무비클립이 없음.\n";
    }
    modelRailIce[0] = modelRail->getVBModelByInstanceName("inRail")->getVBModelByInstanceName("ice0");
    if(modelRailIce[0] == NULL) {
        cout << "ui무비클립안의 rail instance name안에 inRail instance name안에 ice0 instance name의 무비클립이 없음.\n";
    }
    modelRailIce[1] = modelRail->getVBModelByInstanceName("inRail")->getVBModelByInstanceName("ice1");
    if(modelRailIce[1] == NULL) {
        cout << "ui무비클립안의 rail instance name안에 inRail instance name안에 ice1 instance name의 무비클립이 없음.\n";
    }
    
    touchCook = touchDown = touchUp = touchPause = touchNew = NULL;
}

void GameMain::FreeModel() {
    modelUI->getVBModelByInstanceName("arm")->removeChild(modelArm, false);
    delete modelArm;
    
    top->removeChild(modelUI, false);
    delete modelUI;
    
    for(int i = 0; i < bgLen; i++) {
        top->removeChild(modelBg[i], false);
        delete modelBg[i];
        modelBg[i] = NULL;
    }
    modelBg = NULL;
}

void GameMain::InitCook(int** _rtc, int _rtcLen, int* _rtcArrLen, int* _tc, int _tcLen) {
    iceCream = NULL;
    nextIceCream = NULL;
    delIceCream = NULL;
    nextIceCreamMotion = NULL;
    dragIce = NULL;
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    for(int i = 0; i < _rtcLen; i++) {
        if(i == 0)
            baseIceCream = new IceCream(this, rdVec, tdVec, NULL, _rtc[i], _rtcArrLen[i]);
        else
            baseIceCream->AddNextIceCream(_rtc[i], _rtcArrLen[i]);
    }
    if(_tc && _tcLen) {
        for(int i = 0; i < _tcLen; i++) {
            baseIceCream->AddTopping(_tc[i]);
        }
    }
    baseIceCream->setScale(0.5);
    baseIceCream->setPosition(CCPointMake(40, -90-63));
    top->addChild(baseIceCream);
    
    iceCream = new IceCream(this, rdVec, tdVec, baseIceCream);
    iceCream->setScale(0.5);
    iceCream->setPosition(CCPointMake(-2, 92-63));
    modelRailIce[0]->addChild(iceCream);
}

void GameMain::FreeCook() {
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    if(nextIceCreamMotion) {
        top->removeChild(nextIceCreamMotion, false);
        delete nextIceCreamMotion;
        nextIceCreamMotion = NULL;
    }
    
    modelRailIce[0]->removeAllChildrenWithCleanup(false);
    modelRailIce[1]->removeAllChildrenWithCleanup(false);
    if(delIceCream) {
        delete delIceCream;
        delIceCream = NULL;
    }
    delete iceCream;
    iceCream = NULL;
    
    top->removeChild(baseIceCream, false);
    delete baseIceCream;
    baseIceCream = NULL;
}

void GameMain::InitRecipe() {
    recipeContainer = NULL;
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    recipeData = VBArrayVectorInit(VBArrayVectorAlloc());
    //printf("preSort ");
    for(int i = 0; i < VBArrayVectorGetLength(rdVec); i++) {
        RT* _rt = (RT*)VBArrayVectorGetDataAt(rdVec, i);
        VBArrayVectorAddBack(recipeData, RecipeContainerCellDataInit(_rt->idx));
        //printf("%i ", _rd[i]);
    }
    //printf("\n");
    VBArrayVectorQuickSort(recipeData, RecipeSort);
    /*
     printf("sort ");
     for(int i = 0; i < recipeData->len; i++) {
     printf("%i ", ((RecipeContainerCellData*)VBArrayVectorGetDataAt(recipeData, i))->recipeIdx);
     }
     printf("\n");
     */
    recipeContainer = new RecipeContainer(objUI, texUI, objScroll, texScroll, recipeData, this, top, iceCream, NULL);
    if(modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("shelf") == NULL) {
        cout << "ui무비클립안의 right instance name안에 shelf instance name의 무비클립이 없음.\n";
    }
    modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("shelf")->addChild(recipeContainer);
}

void GameMain::FreeRecipe() {
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("shelf")->removeChild(recipeContainer, false);
    delete recipeContainer;
    recipeContainer = NULL;
    
    while (VBArrayVectorGetLength(recipeData)) {
        RecipeContainerCellData* _data = (RecipeContainerCellData*)VBArrayVectorRemoveBack(recipeData);
        RecipeContainerCellDataFree(&_data);
    }
    VBArrayVectorFree(&recipeData);
}

void GameMain::InitTopping() {
    toppingTweener = NULL;
    toppingTweenerParam = NULL;
    toppingTweenerTime = 0.0;
    toppingTweenerTimeCount = 0.0;
    toppingContainer = NULL;
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    toppingData = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < VBArrayVectorGetLength(tdVec); i++) {
        RT* _rt = (RT*)VBArrayVectorGetDataAt(tdVec, i);
        int _stepTotal = 1;
        switch(_rt->type) {
            case 0://눈깔
            {
                ToppingSpuit* _ts = (ToppingSpuit*)_rt->data;
                _stepTotal = _ts->len;
            }
                break;
            case 1://flow
            {
                ToppingFlow* _tf = (ToppingFlow*)_rt->data;
                _stepTotal = _tf->len;
            }
                break;
            case 2://크림
                _stepTotal = 1;
                break;
            case 3://체리
                _stepTotal = 1;
                break;
        }
        VBArrayVectorAddBack(toppingData, ToppingContainerCellDataInit(_rt->idx, _stepTotal));
    }
    VBArrayVectorQuickSort(toppingData, ToppingSort);
    //printf("removed %i\n", VBArrayVectorGetLength(toppingData));
    
    toppingTweenerY = 160;
    if(VBArrayVectorGetLength(toppingData)) {
        toppingContainer = new ToppingContainer(this, objScroll, texScroll, toppingData, iceCream);
        toppingContainer->setPosition(CCPointMake(0, toppingTweenerY));
        if(modelUI->getVBModelByInstanceName("topping") == NULL) {
            cout << "ui무비클립안에 topping instance name의 무비클립이 없음.\n";
        }
        modelUI->getVBModelByInstanceName("topping")->addChild(toppingContainer);
    } else {
        toppingContainer = NULL;
    }
}

void GameMain::FreeTopping() {
    ClearToppingTween();
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    if(toppingContainer) {
        modelUI->getVBModelByInstanceName("topping")->removeChild(toppingContainer, false);
        delete toppingContainer;
        toppingContainer = NULL;
    }
    
    while (VBArrayVectorGetLength(toppingData)) {
        ToppingContainerCellData* _data = (ToppingContainerCellData*)VBArrayVectorRemoveBack(toppingData);
        ToppingContainerCellDataFree(&_data);
    }
    VBArrayVectorFree(&toppingData);
}

void GameMain::CallbackSlideNextRope(void* _obj) {
    if(reinterpret_cast<GameMain*>(_obj)->IsActiveUI()) {
        reinterpret_cast<GameMain*>(_obj)->NextIceCream();
        reinterpret_cast<GameMain*>(_obj)->nextRopeSlider->SetEnable(false);
        reinterpret_cast<GameMain*>(_obj)->recipeContainerCallBack(-1);
    }
}

void GameMain::CallbackSlideToppingRope(void* _obj) {
    if(reinterpret_cast<GameMain*>(_obj)->IsActiveUI() && 
       reinterpret_cast<GameMain*>(_obj)->IsRecipeMode()) {
        reinterpret_cast<GameMain*>(_obj)->SwapRecipeAndToppingMode();
        reinterpret_cast<GameMain*>(_obj)->toppingRopeSlider->SetEnable(false);
        if(reinterpret_cast<GameMain*>(_obj)->nextRopeSlider)
            reinterpret_cast<GameMain*>(_obj)->nextRopeSlider->SetEnable(false);
        reinterpret_cast<GameMain*>(_obj)->recipeContainerCallBack(-2);
    }
}

void GameMain::InitRope() {
    nextRopeSlider = NULL;
    toppingRopeSlider = NULL;
#ifdef GAME_MAIN_EMPTY
    return;
#endif 
    //printf("0 ");
    if(modelUI->getVBModelByInstanceName("nextRope")) {
        nextRopeSlider = new Slider(modelUI->getVBModelByInstanceName("nextRope"), false, -4, 95, -18, -113, SliderDir_Vertical_T, this,
                                    CallbackSlideNextRope);
        nextRopeSlider->SetEnable(true, 0.3);
        //printf("1 ");
    } else {
        nextRopeSlider = NULL;
    }
    
    if(modelUI->getVBModelByInstanceName("toppingRope")) {
        toppingRopeSlider = new Slider(modelUI->getVBModelByInstanceName("toppingRope"), false, 4, 74, -10, -129, SliderDir_Vertical_T, this,
                                       CallbackSlideToppingRope);
        if(toppingContainer)
            toppingRopeSlider->SetEnable(true, 0.4);
        //printf("2 ");
    } else {
        toppingRopeSlider = NULL;
    }
    //printf("3 ");
}

void GameMain::FreeRope() {
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    if(nextRopeSlider) {
        delete nextRopeSlider;
        nextRopeSlider = NULL;
    }
    if(toppingRopeSlider) {
        delete toppingRopeSlider;
        toppingRopeSlider = NULL;
    }
}

GameMain::GameMain(int _packIdx, int _stageIdx) {
    packIdx = _packIdx;
    stageIdx = _stageIdx;
    hintViewer = NULL;
    cJSON* _j = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetJSON(), "pack"), _packIdx);
    cJSON* _layer = cJSON_GetObjectItem(_j, "objLayer");
    cJSON* _ui = cJSON_GetObjectItem(_j, "objUI");
    
    LoadResource(_layer, _ui);
    InitModel(_layer, _ui);
    
    cJSON* _stJ = ShareDataGetStageJSONAt(_packIdx, _stageIdx);
    cJSON* _rcJ = cJSON_GetObjectItem(_stJ, "recipe");
    
    
#ifndef GAME_MAIN_EMPTY
    rd = NULL;
    rdLen = 0;
    td = NULL;
    tdLen = 0;
    
    int* _cook_td = NULL;
    int _cook_tdLen = 0;
    int _cook_rdLen = cJSON_GetArraySize(_rcJ) - 1;
    int** _cook_rd = NULL;
    int* _cook_rdArrLen = NULL;
    
    bool _hasTopping = cJSON_GetArrayItem(cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1), 0)->valueint != -1;
    
    if(_cook_rdLen > 0) {
        _cook_rd = (int**)calloc(_cook_rdLen, sizeof(int*));
        _cook_rdArrLen = (int*)calloc(_cook_rdLen, sizeof(int));
    }
    
    for(int i = 0; i < _cook_rdLen; i++) {
        cJSON* _rdData = cJSON_GetArrayItem(_rcJ, i);
        _cook_rdArrLen[i] = cJSON_GetArraySize(_rdData);
        _cook_rd[i] = (int*)calloc(_cook_rdArrLen[i], sizeof(int));
        for(int j = 0; j < _cook_rdArrLen[i]; j++) {
            int _curT = cJSON_GetArrayItem(_rdData, j)->valueint;
            bool _hasT = false;
            for(int k = 0; k < rdLen; k++) {
                if(rd[k] == _curT) {
                    _hasT = true;
                    break;
                }
            }
            if(!_hasT) {
                if(rd == NULL)
                    rd = (int*)calloc(rdLen + 1, sizeof(int));
                else
                    rd = (int*)realloc(rd, (rdLen + 1) * sizeof(int));
                rd[rdLen] = _curT;
                rdLen++;
            }
            _cook_rd[i][j] = _curT;
        }
    }
    
    if(_hasTopping) {
        cJSON* _tdData = cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1);
        _cook_tdLen = cJSON_GetArraySize(_tdData);
        _cook_td = (int*)calloc(_cook_tdLen, sizeof(int));
        for(int i = 0; i < _cook_tdLen; i++) {
            int _curT = cJSON_GetArrayItem(_tdData, i)->valueint;
            bool _hasT = false;
            for(int k = 0; k < tdLen; k++) {
                if(td[k] == _curT) {
                    _hasT = true;
                    break;
                }
            }
            if(!_hasT) {
                if(td == NULL)
                    td = (int*)calloc(tdLen + 1, sizeof(int));
                else
                    td = (int*)realloc(td, (tdLen + 1) * sizeof(int));
                td[tdLen] = _curT;
                tdLen++;
            }
            _cook_td[i] = _curT;
        }
    }
    
    int _rdLen = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetRes(), "recipe"));
    int _rd[_rdLen];
    for(int i = 0; i < _rdLen; i++)
        _rd[i] = i;
    rdVec = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < _rdLen; i++) {
        cJSON* _item = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "recipe"), _rd[i]);
        int _type = cJSON_GetArrayItem(_item, 1)->valueint;
        void* _r = NULL;
        if(_type == 0) {
            cJSON* _maskJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            _r = RecipeFillInit(_maskJS, hexToInt(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "fill"), cJSON_GetArrayItem(_item, 3)->valueint)->valuestring), cJSON_GetArrayItem(_item, 3)->valueint);
        } else if(_type == 1) {
            cJSON* _maskJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            cJSON* _thumbJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 3));
            _r = RecipeMaskInit(_maskJS, _thumbJS, _rd[i]);
        } else if(_type == 2) {
            cJSON* _flowJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            _r = RecipeSubToppingFlowInit(_flowJS, cJSON_GetArrayItem(_item, 3)->valueint);
        } else if(_type == 3) {
            cJSON* _thumbJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            _r = RecipeSubToppingInit(_thumbJS, cJSON_GetArrayItem(_item, 3)->valueint);
        } else if(_type == 4) {
            _r = RecipeMixInit(cJSON_GetArrayItem(_item, 2),cJSON_GetArrayItem(_item, 3));
        } else if(_type == 5) {
            cJSON* _lastJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            cJSON* _lastBridgeJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 3));
            _r = RecipeLastInit(_lastJS, _lastBridgeJS);
        }
        if(_r)
            VBArrayVectorAddBack(rdVec, RTInit(true, _rd[i], _type, _r));
    }
    
    int _tdLen = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetRes(), "topping"));
    int _td[_tdLen];
    for(int i = 0; i < _tdLen; i++)
        _td[i] = i;
    tdVec = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < _tdLen; i++) {
        cJSON* _item = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "topping"), _td[i]);
        int _type = cJSON_GetArrayItem(_item, 1)->valueint;
        void* _t = NULL;
        if(_type == 0) {
            _t = ToppingSpuitInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)));
        } else if(_type == 1) {
            _t = ToppingFlowInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)));
        } else if(_type == 2) {
            _t = ToppingCreamInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)));
        } else if(_type == 3) {
            _t = ToppingCherryInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)), ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 3)));
        }
        if(_t)
            VBArrayVectorAddBack(tdVec, RTInit(false, _td[i], _type, _t));
    }
    
    InitCook(_cook_rd, _cook_rdLen, _cook_rdArrLen, _cook_td, _cook_tdLen);
#endif
    
#ifdef GAME_MAIN_EMPTY
    InitCook(NULL, 0, NULL, NULL, 0);
#endif
    isRecipeMode = true;
    InitRecipe();
    InitTopping();
    
#ifdef HINT_COMPLETE
    hintViewer = new HintViewer(this, true);
    hintViewer->setSolution(_cook_rd, _cook_rdLen, _cook_rdArrLen, _cook_td, _cook_tdLen);
#endif
    
    InitRope();
    
#ifndef GAME_MAIN_EMPTY
    for(int i = 0; i < _cook_rdLen; i++) {
        if(_cook_rd[i])
            free(_cook_rd[i]);
    }
    if(_cook_rd)
        free(_cook_rd);
    if(_cook_rdArrLen)
        free(_cook_rdArrLen);
    if(_cook_td)
        free(_cook_td);
#endif
    
    printf("new GameMain\n");
}

void GameMain::resetOtherStage(int _packIdx, int _stageIdx) {
#ifdef HINT_COMPLETE
    if (hintViewer) {
        delete hintViewer;
        hintViewer = NULL;
    }
#endif
    
    FreeCook();
    FreeRecipe();
    FreeRope();
    FreeTopping();
    
#ifndef GAME_MAIN_EMPTY
    if(td)
        free(td);
    if(rd)
        free(rd);
    
    while(VBArrayVectorGetLength(rdVec)) {
        RT* _rt = (RT*)VBArrayVectorRemoveBack(rdVec);
        switch(_rt->type) {
            case 0:
                RecipeFillFree((RecipeFill**)&_rt->data);
                break;
            case 1:
                RecipeMaskFree((RecipeMask**)&_rt->data);
                break;
            case 2:
                RecipeSubToppingFlowFree((RecipeSubToppingFlow**)&_rt->data);
                break;
            case 3:
                RecipeSubToppingFree((RecipeSubTopping**)&_rt->data);
                break;
            case 4:
                RecipeMixFree((RecipeMix**)&_rt->data);
                break;
            case 5:
                RecipeLastFree((RecipeLast**)&_rt->data);
                break;
        }
        RTFree(&_rt);
    }
    VBArrayVectorFree(&rdVec);
    
    while(VBArrayVectorGetLength(tdVec)) {
        RT* _rt = (RT*)VBArrayVectorRemoveBack(tdVec);
        switch(_rt->type) {
            case 0:
                ToppingSpuitFree((ToppingSpuit**)&_rt->data);
                break;
            case 1:
                ToppingFlowFree((ToppingFlow**)&_rt->data);
                break;
            case 2:
                ToppingCreamFree((ToppingCream**)&_rt->data);
                break;
            case 3:
                ToppingCherryFree((ToppingCherry**)&_rt->data);
                break;
        }
        RTFree(&_rt);
    }
    VBArrayVectorFree(&tdVec);
#endif

    
    if (packIdx != _packIdx) {
        FreeModel();
        UnloadResource();
        
        cJSON* _j = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetJSON(), "pack"), _packIdx);
        cJSON* _layer = cJSON_GetObjectItem(_j, "objLayer");
        cJSON* _ui = cJSON_GetObjectItem(_j, "objUI");
        
        LoadResource(_layer, _ui);
        InitModel(_layer, _ui);
    }
    
    
    cJSON* _stJ = ShareDataGetStageJSONAt(_packIdx, _stageIdx);
    cJSON* _rcJ = cJSON_GetObjectItem(_stJ, "recipe");
    
    
#ifndef GAME_MAIN_EMPTY
    rd = NULL;
    rdLen = 0;
    td = NULL;
    tdLen = 0;
    
    int* _cook_td = NULL;
    int _cook_tdLen = 0;
    int _cook_rdLen = cJSON_GetArraySize(_rcJ) - 1;
    int** _cook_rd = NULL;
    int* _cook_rdArrLen = NULL;
    
    bool _hasTopping = cJSON_GetArrayItem(cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1), 0)->valueint != -1;
    
    if(_cook_rdLen > 0) {
        _cook_rd = (int**)calloc(_cook_rdLen, sizeof(int*));
        _cook_rdArrLen = (int*)calloc(_cook_rdLen, sizeof(int));
    }
    
    for(int i = 0; i < _cook_rdLen; i++) {
        cJSON* _rdData = cJSON_GetArrayItem(_rcJ, i);
        _cook_rdArrLen[i] = cJSON_GetArraySize(_rdData);
        _cook_rd[i] = (int*)calloc(_cook_rdArrLen[i], sizeof(int));
        for(int j = 0; j < _cook_rdArrLen[i]; j++) {
            int _curT = cJSON_GetArrayItem(_rdData, j)->valueint;
            bool _hasT = false;
            for(int k = 0; k < rdLen; k++) {
                if(rd[k] == _curT) {
                    _hasT = true;
                    break;
                }
            }
            if(!_hasT) {
                if(rd == NULL)
                    rd = (int*)calloc(rdLen + 1, sizeof(int));
                else
                    rd = (int*)realloc(rd, (rdLen + 1) * sizeof(int));
                rd[rdLen] = _curT;
                rdLen++;
            }
            _cook_rd[i][j] = _curT;
        }
    }
    
    if(_hasTopping) {
        cJSON* _tdData = cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1);
        _cook_tdLen = cJSON_GetArraySize(_tdData);
        _cook_td = (int*)calloc(_cook_tdLen, sizeof(int));
        for(int i = 0; i < _cook_tdLen; i++) {
            int _curT = cJSON_GetArrayItem(_tdData, i)->valueint;
            bool _hasT = false;
            for(int k = 0; k < tdLen; k++) {
                if(td[k] == _curT) {
                    _hasT = true;
                    break;
                }
            }
            if(!_hasT) {
                if(td == NULL)
                    td = (int*)calloc(tdLen + 1, sizeof(int));
                else
                    td = (int*)realloc(td, (tdLen + 1) * sizeof(int));
                td[tdLen] = _curT;
                tdLen++;
            }
            _cook_td[i] = _curT;
        }
    }
    
    int _rdLen = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetRes(), "recipe"));
    int _rd[_rdLen];
    for(int i = 0; i < _rdLen; i++)
        _rd[i] = i;
    rdVec = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < _rdLen; i++) {
        cJSON* _item = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "recipe"), _rd[i]);
        int _type = cJSON_GetArrayItem(_item, 1)->valueint;
        void* _r = NULL;
        if(_type == 0) {
            cJSON* _maskJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            _r = RecipeFillInit(_maskJS, hexToInt(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "fill"), cJSON_GetArrayItem(_item, 3)->valueint)->valuestring), cJSON_GetArrayItem(_item, 3)->valueint);
        } else if(_type == 1) {
            cJSON* _maskJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            cJSON* _thumbJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 3));
            _r = RecipeMaskInit(_maskJS, _thumbJS, _rd[i]);
        } else if(_type == 2) {
            cJSON* _flowJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            _r = RecipeSubToppingFlowInit(_flowJS, cJSON_GetArrayItem(_item, 3)->valueint);
        } else if(_type == 3) {
            cJSON* _thumbJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            _r = RecipeSubToppingInit(_thumbJS, cJSON_GetArrayItem(_item, 3)->valueint);
        } else if(_type == 4) {
            _r = RecipeMixInit(cJSON_GetArrayItem(_item, 2),cJSON_GetArrayItem(_item, 3));
        } else if(_type == 5) {
            cJSON* _lastJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2));
            cJSON* _lastBridgeJS = ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 3));
            _r = RecipeLastInit(_lastJS, _lastBridgeJS);
        }
        if(_r)
            VBArrayVectorAddBack(rdVec, RTInit(true, _rd[i], _type, _r));
    }
    
    int _tdLen = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetRes(), "topping"));
    int _td[_tdLen];
    for(int i = 0; i < _tdLen; i++)
        _td[i] = i;
    tdVec = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < _tdLen; i++) {
        cJSON* _item = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "topping"), _td[i]);
        int _type = cJSON_GetArrayItem(_item, 1)->valueint;
        void* _t = NULL;
        if(_type == 0) {
            _t = ToppingSpuitInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)));
        } else if(_type == 1) {
            _t = ToppingFlowInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)));
        } else if(_type == 2) {
            _t = ToppingCreamInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)));
        } else if(_type == 3) {
            _t = ToppingCherryInit(ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 2)), ShareDataGetTemplateData(cJSON_GetArrayItem(_item, 3)));
        }
        if(_t)
            VBArrayVectorAddBack(tdVec, RTInit(false, _td[i], _type, _t));
    }
    
    InitCook(_cook_rd, _cook_rdLen, _cook_rdArrLen, _cook_td, _cook_tdLen);
#endif
    
#ifdef GAME_MAIN_EMPTY
    InitCook(NULL, 0, NULL, NULL, 0);
#endif
    isRecipeMode = true;
    InitRecipe();
    InitTopping();
    
#ifdef HINT_COMPLETE
    hintViewer = new HintViewer(this, true);
    hintViewer->setSolution(_cook_rd, _cook_rdLen, _cook_rdArrLen, _cook_td, _cook_tdLen);
#endif
    
    InitRope();
    
#ifndef GAME_MAIN_EMPTY
    for(int i = 0; i < _cook_rdLen; i++) {
        if(_cook_rd[i])
            free(_cook_rd[i]);
    }
    if(_cook_rd)
        free(_cook_rd);
    if(_cook_rdArrLen)
        free(_cook_rdArrLen);
    if(_cook_td)
        free(_cook_td);
#endif
    
    printf("reset GameMain\n");

}

void GameMain::ClearToppingTween() {
    if(toppingTweenerParam) {
        if(toppingTweener)
            toppingTweener->removeTween(toppingTweenerParam);
        delete toppingTweenerParam;
    }
    toppingTweenerParam = NULL;
    if(toppingTweener) {
        delete toppingTweener;
    }
    toppingTweener = NULL;
    toppingTweenerTimeCount = 0.0;
}

void GameMain::UpdateToppingTween(float _deltaTime) {
    if(toppingTweener) {
        toppingTweenerTimeCount += _deltaTime;
        toppingTweener->step(toppingTweenerTimeCount * 1000);
        if(toppingContainer)
            toppingContainer->setPosition(CCPointMake(0, toppingTweenerY));
        if(toppingTweenerTimeCount > toppingTweenerTime)
            ClearToppingTween();
    }
}

void GameMain::BeginToppingTween(float _y, float _time, bool _is_ease_out) {
    ClearToppingTween();
    toppingTweener = new Tweener();
    toppingTweenerTime = _time;
    toppingTweenerParam = new TweenerParam(toppingTweenerTime * 1000, EXPO, _is_ease_out ? EASE_OUT : EASE_IN);
    toppingTweenerParam->addProperty(&toppingTweenerY, _y);
    toppingTweener->addTween(*toppingTweenerParam);
}

GameMain::~GameMain() {
    FreeRope();
    FreeTopping();
    FreeRecipe();
    FreeCook();
    
#ifndef GAME_MAIN_EMPTY
    if(td)
        free(td);
    if(rd)
        free(rd);
    
    while(VBArrayVectorGetLength(rdVec)) {
        RT* _rt = (RT*)VBArrayVectorRemoveBack(rdVec);
        switch(_rt->type) {
            case 0:
                RecipeFillFree((RecipeFill**)&_rt->data);
                break;
            case 1:
                RecipeMaskFree((RecipeMask**)&_rt->data);
                break;
            case 2:
                RecipeSubToppingFlowFree((RecipeSubToppingFlow**)&_rt->data);
                break;
            case 3:
                RecipeSubToppingFree((RecipeSubTopping**)&_rt->data);
                break;
            case 4:
                RecipeMixFree((RecipeMix**)&_rt->data);
                break;
            case 5:
                RecipeLastFree((RecipeLast**)&_rt->data);
                break;
        }
        RTFree(&_rt);
    }
    VBArrayVectorFree(&rdVec);
    
    while(VBArrayVectorGetLength(tdVec)) {
        RT* _rt = (RT*)VBArrayVectorRemoveBack(tdVec);
        switch(_rt->type) {
            case 0:
                ToppingSpuitFree((ToppingSpuit**)&_rt->data);
                break;
            case 1:
                ToppingFlowFree((ToppingFlow**)&_rt->data);
                break;
            case 2:
                ToppingCreamFree((ToppingCream**)&_rt->data);
                break;
            case 3:
                ToppingCherryFree((ToppingCherry**)&_rt->data);
                break;
        }
        RTFree(&_rt);
    }
    VBArrayVectorFree(&tdVec);
#endif
    
    FreeModel();
    UnloadResource();
    
#ifdef HINT_COMPLETE
    delete hintViewer;
#endif
    
    printf("delete GameMain\n");
}

void GameMain::NextIceCream() {
    nextIceCream = new IceCream(this, rdVec, tdVec, NULL);
    nextIceCream->setScale(0.5);
    nextIceCream->setPosition(CCPointMake(0, -63));
    if(modelArm) {
        modelArm->play();
        if(modelArm->getVBModelByInstanceName("id_dy_obj_armNode") == NULL)
            cout << "Arm무비클립안에 id_dy_obj_armNode instance name의 무비클립이 없음.\n";
        modelArm->getVBModelByInstanceName("id_dy_obj_armNode")->addChild(nextIceCream);
    }
    if(nextRopeSlider)
        nextRopeSlider->SetEnable(false);
}

void GameMain::NextIceCreamUpdate(float _deltaTime) {
    if(modelArm) {
        if(!modelArm->is_play)
            modelArm->gotoAndStop(0);
        if(nextIceCream) {
            if(modelArm->cur_frame + _deltaTime >= 121) {
                if(modelArm->getVBModelByInstanceName("id_dy_obj_armNode") == NULL) {
                    cout << "Arm무비클립안에 id_dy_obj_armNode instance name의 무비클립이 없음.\n";
                }
                modelArm->getVBModelByInstanceName("id_dy_obj_armNode")->removeChild(nextIceCream, false);
                CCPoint p1 = nextIceCream->getPosition();
                CCPoint p2 = modelArm->getVBModelByInstanceName("id_dy_obj_armNode")->getPosition();
                CCPoint p3 = modelUI->getVBModelByInstanceName("arm")->getPosition();
                nextIceCream->setPosition(CCPointMake(p1.x + p2.x + p3.x, p1.y + p2.y + p3.y));
                top->addChild(nextIceCream);
                nextIceCreamMotion = nextIceCream;
                nextIceCream = NULL;
            }
        }
        if(nextIceCreamMotion) {
            CCPoint p1 = nextIceCreamMotion->getPosition();
            if(p1.y > -120-50)
                nextIceCreamMotion->setPosition(CCPointMake(p1.x, p1.y - _deltaTime * 600.0));
            else {
                nextIceCreamMotion->setScale(1.0);
                top->removeChild(nextIceCreamMotion, false);
                iceCream->AddNextIceCream(nextIceCreamMotion);
                nextIceCreamMotion = NULL;
            }
        }
    }
}

void GameMain::NewIceCream() {
    delIceCream = iceCream;
    iceCream = new IceCream(this, rdVec, tdVec, baseIceCream);
    if(recipeContainer)
        recipeContainer->hitTarget = iceCream;
    if(toppingContainer)
        toppingContainer->SetCook(iceCream);
    iceCream->setScale(0.5);
    iceCream->setPosition(CCPointMake(-2, 92-63));
    modelRailIce[1]->addChild(iceCream);
    recipeContainer->hitTarget = iceCream;
    
    modelRail->play();
}

void GameMain::NewIceCreamUpdate(float _deltaTime) {
    if(modelRail) {
        if(!modelRail->is_play) {
            if(delIceCream) {
                modelRailIce[0]->removeChild(delIceCream, false);
                delete delIceCream;
                delIceCream = NULL;
                modelRailIce[1]->removeChild(iceCream, false);
                modelRailIce[0]->addChild(iceCream);
            }
            modelRail->gotoAndStop(0);
        }
    }
}

void GameMain::SwapRecipeAndToppingMode() {
    isRecipeMode = !isRecipeMode;
    
    if(!IsRecipeMode()) {
        BeginToppingTween(0, 0.5, true);
        if(toppingContainer) {
            toppingContainer->ResetData();
        }
        if(toppingContainer)
            toppingContainer->ShowScrollBarMoment(1.0);
    } else {
        BeginToppingTween(160, 0.5, false);
        recipeContainer->ShowScrollBarMoment(1.0);
    }
    if(modelDoor)
        modelDoor->play();
}

void GameMain::SwapRecipeAndToppingModeUpdate(float _deltaTime) {
    if(!IsRecipeMode()) {
        if(modelDoor->cur_frame + _deltaTime >= 60)
            modelDoor->gotoAndStop(60);
    } else {
        if(modelDoor->cur_frame + _deltaTime >= 113)
            modelDoor->gotoAndStop(0);
    }
}

bool GameMain::IsRecipeMode() {
    return isRecipeMode;
}

bool GameMain::IsActiveUI() {
    bool _avail;
    
    _avail = (modelArm ? (modelArm->cur_frame == 0 && !modelArm->is_play) : true);
    _avail = _avail && (nextIceCream == NULL && nextIceCreamMotion == NULL);
    _avail = _avail && (modelDoor ? (modelDoor->cur_frame == 0 || modelDoor->cur_frame == 60) && !modelDoor->is_play : true);
    _avail = _avail && (modelRail ? (modelRail->cur_frame == 0 && !modelRail->is_play) : true);
    
    return _avail;
}

void GameMain::Update(float _deltaTime) {
    View::Update(_deltaTime);
    
    if(recipeContainer)
        recipeContainer->Update(_deltaTime);
    if(toppingContainer)
        toppingContainer->Update(_deltaTime);
    
    if(toppingRopeSlider)
        toppingRopeSlider->Update(_deltaTime);
    if(nextRopeSlider)
        nextRopeSlider->Update(_deltaTime);
    
    UpdateToppingTween(_deltaTime);
    
    if(recipeContainer) {
        modelDownButton->gotoAndStop(recipeContainer->IsPossibleNextPage() ? 1.0 : 0.0);
        modelUpButton->gotoAndStop(recipeContainer->IsPossiblePrevPage() ? 1.0 : 0.0);
    }
    
    NextIceCreamUpdate(_deltaTime);
    NewIceCreamUpdate(_deltaTime);
    SwapRecipeAndToppingModeUpdate(_deltaTime);
    
#ifdef HINT_COMPLETE
    hintViewer->update(_deltaTime);
#endif
}

void GameMain::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(nextRopeSlider)
        nextRopeSlider->TouchBegin(_touch, _location);
    if(toppingRopeSlider)
        toppingRopeSlider->TouchBegin(_touch, _location);
    
    TOUCHBEGINBT(touchDown, modelDownButton, _location, _touch, );
    TOUCHBEGINBT(touchUp, modelUpButton, _location, _touch, );
    if(IsRecipeMode()) {
        if(touchDown == NULL && touchUp == NULL) {
            if(recipeContainer)
                recipeContainer->touchBegin(_touch, _location);
        }
    } else {
        if(toppingContainer)
            toppingContainer->touchBegin(_touch, _location);
    }
    
    if(iceCream) {
        TOUCHBEGINBT(touchCook, iceCream, _location, _touch, 
                     dragIce = iceCream->DragStartMount(top);
                     if(dragIce) {
                         dragIce->setPosition(CCPointMake(dragIce->getPosition().x + _location.x, dragIce->getPosition().y + (-320 + _location.y)));
                         dragPre = _location;
                     }
                     );
    }
    
    TOUCHBEGINBT(touchPause, modelPauseButton, _location, _touch, modelPauseButton->gotoAndStop(1.0));
    TOUCHBEGINBT(touchNew, modelNewButton, _location, _touch, modelNewButton->gotoAndStop(1.0));
}

void GameMain::touchMove(CCTouch* _touch, CCPoint _location) {
    if(nextRopeSlider)
        nextRopeSlider->TouchMove(_touch, _location);
    if(toppingRopeSlider)
        toppingRopeSlider->TouchMove(_touch, _location);
    if(touchDown == NULL && touchUp == NULL) {
        if(recipeContainer)
            recipeContainer->touchMove(_touch, _location);
    }
    if(toppingContainer)
        toppingContainer->touchMove(_touch, _location);
    if(dragIce) {
        CCPoint pp = dragIce->getPosition();
        dragIce->setPosition(CCPointMake(pp.x + (_location.x - dragPre.x), pp.y + (_location.y - dragPre.y)));
        //printf("%f %f\n",dragIce->getPosition().x,dragIce->getPosition().y);
        dragPre = _location;
    }
}

void GameMain::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(touchDown, modelDownButton, _location, _touch, 
               if(recipeContainer) {
                   recipeContainer->NextPage();
               }
               ,);
    TOUCHENDBT(touchUp, modelUpButton, _location, _touch, 
               if(recipeContainer) {
                   recipeContainer->PrevPage();
               }
               ,);
    if(iceCream) {
        TOUCHENDBT(touchCook, iceCream, _location, _touch, ,
                   if(dragIce) {
                       iceCream->DragEndMount(dragIce->hitTest(recipeContainer));
                       dragIce = NULL;
                   }
                   );
    }
    TOUCHENDBT(touchPause, modelPauseButton, _location, _touch, 
               ShareDataGetRoot()->OpenPopup(PopupTypePause, 0, 0), 
               modelPauseButton->gotoAndStop(0.0));
    TOUCHENDBT(touchNew, modelNewButton, _location, _touch, 
               if(IsActiveUI()) {
                   if(nextRopeSlider) nextRopeSlider->SetEnable(true);
                   if(!IsRecipeMode()) SwapRecipeAndToppingMode();
                   if(toppingContainer) {
                       if(toppingRopeSlider) toppingRopeSlider->SetEnable(true);
                   }
                   NewIceCream();
//for hintviewer
#ifdef HINT_COMPLETE
                   if(hintViewer) {
                       hintViewer->step(-3);
                   }
#endif
               }
               , modelNewButton->gotoAndStop(0.0));
}

void GameMain::touchEnd(CCTouch* _touch, CCPoint _location) {
    if(nextRopeSlider) {
        nextRopeSlider->TouchEnd(_touch, _location);
    }
    if(toppingRopeSlider) {
        toppingRopeSlider->TouchEnd(_touch, _location);
    }
    if(touchDown == NULL && touchUp == NULL) {
        if(recipeContainer)
            recipeContainer->touchEnd(_touch, _location);
    }
    if(toppingContainer)
        toppingContainer->touchEnd(_touch, _location);
    touchEndAndCancel(_touch, _location);
}

void GameMain::touchCancel(CCTouch* _touch, CCPoint _location) {
    if(nextRopeSlider)
        nextRopeSlider->TouchCancel(_touch, _location);
    if(toppingRopeSlider)
        toppingRopeSlider->TouchCancel(_touch, _location);
    if(touchDown == NULL && touchUp == NULL)
        recipeContainer->touchCancel(_touch, _location);
    if(toppingContainer)
        toppingContainer->touchCancel(_touch, _location);
    touchEndAndCancel(_touch, _location);
}


// for HintViewer
float GameMain::getRecipePositionY(int recipeIdx)
{
    return recipeContainer->getItemPositionY(recipeIdx);
}

void GameMain::recipeContainerCallBack(int recipeIdx)
{
    iceCream->GetClear();
#ifdef HINT_COMPLETE
    printf("step %s\n", hintViewer->step(recipeIdx) ? "ok" : "no");
#endif
}

float GameMain::getToppingPositionX(int toppingIdx)
{
    return toppingContainer->getToppingPositionX(toppingIdx);
}

void GameMain::iceCreamMaskCallBack(int recipeIdx)
{
#ifdef HINT_COMPLETE
    if (hintViewer) {
        hintViewer->step(recipeIdx);
    }
#endif
}

void GameMain::toppingContainerCallBack(int recipeIdx)
{
#ifdef HINT_COMPLETE
    if (hintViewer) {
        hintViewer->step(recipeIdx);
    }
#endif
}
