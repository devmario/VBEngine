#include "GameMain.h"
#include "ShareData.h"

//#define GAME_MAIN_EMPTY

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

int* loadRecipeTypeList() {
    cJSON *recipeJSON = cJSON_GetObjectItem(ShareDataGetRes(), "recipe");
    int recipeLen = cJSON_GetArraySize(recipeJSON);
    
    int* recipeTypeList = (int*)malloc(sizeof(int)*recipeLen);
    for (int i=0; i<recipeLen; i++) {
        recipeTypeList[i] = cJSON_GetArrayItem(cJSON_GetArrayItem(recipeJSON, i), 1)->valueint;
    }
    return recipeTypeList;
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
    free(objBg);
    free(texBg);
    objBg = NULL;
    texBg = NULL;
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
    free(modelBg);
    modelBg = NULL;
}

void GameMain::InitCook() {
    delIceCream = NULL;
    nextIceCreamMotion = NULL;
    dragIce = NULL;
    callBackStop = true;
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    if (!initWithIceCream) {
        for(int i = 0; i < rdTd->cook.rtcLen; i++) {
            if(i == 0) {
                baseIceCream = new IceCream(this, rdTd->rdVec, rdTd->tdVec, NULL, NULL, rdTd->cook.rtc[i], rdTd->cook.rtcArrLen[i]);
            }
            else
                baseIceCream->AddNextIceCream(rdTd->cook.rtc[i], rdTd->cook.rtcArrLen[i]);
        }
        callBackStop = false;
        if(rdTd->cook.tc && rdTd->cook.tcLen) {
            for(int i = 0; i < rdTd->cook.tcLen; i++) {
                baseIceCream->AddTopping(rdTd->cook.tc[i]);
            }
        }
        baseIceCream->setScale(0.5);
        baseIceCream->setPosition(CCPointMake(40, -90-63));
        

        

        iceCream = NULL;
        iceCream = new IceCream(this, rdTd->rdVec, rdTd->tdVec, this, baseIceCream);
        iceCream->setScale(0.5);
        iceCream->setPosition(CCPointMake(-2, 92-63));
        nextIceCream = NULL;
        modelRailIce[0]->addChild(iceCream);
        
    } else {
        initWithIceCream = false;
        iceCream->setGameMain(this);
        modelRailIce[0]->addChild(iceCream);
        
    }
    
    top->addChild(baseIceCream);
    
    if (nextIceCream) {
        nextIceCream->setGameMain(this);
        iceCream->AddNextIceCream(nextIceCream);
    }
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
    iceCream->release();
    iceCream = NULL;
    
    top->removeChild(baseIceCream, false);
    cout << baseIceCream->retainCount() << '\n';
    baseIceCream->release();
    baseIceCream = NULL;
    
}

void GameMain::InitRecipe() {
    recipeContainer = NULL;
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    recipeData = VBArrayVectorInit(VBArrayVectorAlloc());
    //printf("preSort ");
    for(int i = 0; i < VBArrayVectorGetLength(rdTd->rdVec); i++) {
        RT* _rt = (RT*)VBArrayVectorGetDataAt(rdTd->rdVec, i);
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
    toppingContainer = NULL;
#ifdef GAME_MAIN_EMPTY
    return;
#endif
    toppingData = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < VBArrayVectorGetLength(rdTd->tdVec); i++) {
        RT* _rt = (RT*)VBArrayVectorGetDataAt(rdTd->tdVec, i);
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

//other thread
void GameMain::GetIceCreamChecker(float per) {
    printf("아이스크림 일치율: %f\n", per);
    clearPer = per;
    if(clearPer > 99) {
        isClear = true;
    }
}

GameMain::GameMain(int _packIdx, int _stageIdx, IceCream* _baseIceCream, IceCream* _playedIceCream, IceCream* _nextIceCream, GameMainRdTd* _rdTd, HintViewer* _hintViewer, bool _isRecipeMode) {
    isClear = false;
    initWithIceCream = false;
    callBackStop = false;
    history = NULL;
    recipeTypeArr = loadRecipeTypeList();
    
    packIdx = _packIdx;
    stageIdx = _stageIdx;
    hintViewer = NULL;
    cJSON* _j = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetJSON(), "pack"), _packIdx);
    cJSON* _layer = cJSON_GetObjectItem(_j, "objLayer");
    cJSON* _ui = cJSON_GetObjectItem(_j, "objUI");
    
    resetAllStep();
    LoadResource(_layer, _ui);
    InitModel(_layer, _ui);
    
#ifndef GAME_MAIN_EMPTY
    if (_rdTd) {
        rdTd = _rdTd;
    } else {
        rdTd = new GameMainRdTd(_packIdx, _stageIdx);
    }
        
    if (_baseIceCream && _playedIceCream) {
        initWithIceCream = true;
        baseIceCream = _baseIceCream;
        iceCream = _playedIceCream;
        baseIceCream->rdVec = rdTd->rdVec;
        baseIceCream->tdVec = rdTd->tdVec;
        iceCream->rdVec = rdTd->rdVec;
        iceCream->tdVec = rdTd->tdVec;
        
        if (_nextIceCream) {
            nextIceCream = _nextIceCream;
            nextIceCream->rdVec = rdTd->rdVec;
            nextIceCream->tdVec = rdTd->tdVec;
        } else {
            nextIceCream = NULL;
        }
    }
    
    InitCook();
#endif
    
#ifdef GAME_MAIN_EMPTY
    InitCook();
#endif
    isRecipeMode = true;
    InitRecipe();
    InitTopping();
    
    if (_hintViewer) {
        hintViewer = _hintViewer;
        hintViewer->setGameMain(this);
        if (_isRecipeMode)
            hintViewer->show();
    } else {
        hintViewer = new HintViewer(this, IsRecipeMode());
        hintViewer->setSolution(rdTd->cook.rtc, rdTd->cook.rtcLen, rdTd->cook.rtcArrLen, rdTd->cook.tc, rdTd->cook.tcLen);
    }
    
    InitRope();
    initHistory();
    printf("new GameMain\n");
}

void GameMain::resetOtherStage(int _packIdx, int _stageIdx) {
    if (hintViewer) {
        hintViewer->release();
        hintViewer = NULL;
    }
    
    FreeCook();
    FreeRecipe();
    FreeRope();
    FreeTopping();
    
#ifndef GAME_MAIN_EMPTY
    delete rdTd;
    rdTd = NULL;
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
    
    
#ifndef GAME_MAIN_EMPTY
    rdTd = new GameMainRdTd(_packIdx, _stageIdx);
    
    InitCook();
#endif
    resetAllStep();
    isRecipeMode = true;
    InitRecipe();
    InitTopping();
    
    hintViewer = new HintViewer(this, true);
    hintViewer->setSolution(rdTd->cook.rtc, rdTd->cook.rtcLen, rdTd->cook.rtcArrLen, rdTd->cook.tc, rdTd->cook.tcLen);
    
    InitRope();
    initHistory();
    printf("reset GameMain\n");

}

void GameMain::ClearToppingTween() {
    if(toppingTweener) {
        delete toppingTweener;
        toppingTweener = NULL;
    }
}

void GameMain::UpdateToppingTween(float _deltaTime) {
    if(toppingTweener) {
        toppingTweener->update(_deltaTime);
    }
    if(toppingContainer)
        toppingContainer->setPosition(CCPointMake(0, toppingTweenerY));
}

void GameMain::BeginToppingTween(float _y, float _time, bool _is_ease_out) {
    ClearToppingTween();
    
    toppingTweener = new TweenerWrapper();
    
    TweenerParam *toppingTweenerParam = new TweenerParam(_time * 1000, EXPO, _is_ease_out ? EASE_OUT : EASE_IN);
    toppingTweenerParam->addProperty(&toppingTweenerY, _y);
    toppingTweener->setParamAndBegin(toppingTweenerParam, &toppingTweenerY, _y);
}

GameMain::~GameMain() {
    resetAllStep();
    FreeRope();
    FreeTopping();
    FreeRecipe();
    FreeCook();
    
    free(recipeTypeArr);
    
#ifndef GAME_MAIN_EMPTY
    rdTd->release();
#endif
    
    FreeModel();
    UnloadResource();
    
    hintViewer->release();
    
    printf("delete GameMain\n");
}

void GameMain::NextIceCream() {
    nextIceCream = new IceCream(this, rdTd->rdVec, rdTd->tdVec, NULL);
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
    iceCream = new IceCream(this, rdTd->rdVec, rdTd->tdVec, this, baseIceCream);
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

void GameMain::NewIceCreamWithBack() {
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
    
    if(isClear) {
        ShareDataGetRoot()->OpenPopup(PopupTypeClear, 2, 98765);
        isClear = false;
    }
    
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
    
    hintViewer->update(_deltaTime);
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
                         dragPre = _location;
                         if(dragIce->hitTest(recipeContainer)) {
                             dragIce->color.a = 0xFF;
                         } else {
                             dragIce->color.a = 0x88;
                         }
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
        float scale = 1.0;
        if(CCDirector::sharedDirector()->isRetinaDisplay() == false)
            scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
        dragIce->setPosition(CCPointMake(pp.x + (_location.x / scale - dragPre.x / scale), pp.y + (_location.y / scale - dragPre.y / scale)));
        if(dragIce->hitTest(recipeContainer)) {
            dragIce->color.a = 0xFF;
        } else {
            dragIce->color.a = 0x88;
        }
        //printf("%f %f\n",dragIce->getPosition().x,dragIce->getPosition().y);
        dragPre = _location;
    }
}

void GameMain::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(touchDown, modelDownButton, _location, _touch, 
               unDo();
               ,);
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
                       dragIce->color.a = 0xFF;
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
                   if(hintViewer) {
                       hintViewer->resetAction();
                   }
                   resetAllStep();
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

void GameMain::retainIceCream()
{
    baseIceCream->retain();
    iceCream->retain();
    if (nextIceCream) {
        nextIceCream->retain();
    }
}

// for HintViewer
float GameMain::getRecipePositionY(int recipeIdx)
{
    return recipeContainer->getItemPositionY(recipeIdx);
}

void GameMain::recipeContainerCallBack(int recipeIdx)
{
    if (hintViewer) {
        hintViewer->recipeContainerAction(recipeIdx);
    }

    if (!callBackStop && iceCream) {
        if (recipeIdx == -1) {
            saveStep(ActionNext, recipeIdx);
        } else if (recipeIdx == -2) {
            saveStep(ActionToppingRope, recipeIdx);
        } else {
            switch (recipeTypeArr[recipeIdx]) {
                case 1:
                    saveStep(ActionMaskOn, recipeIdx);
                    break;
                case 2:
                    saveStep(ActionSubToppingFlow, recipeIdx);
                    break;
                case 3:
                    saveStep(ActionSubTopping, recipeIdx);
                    break;
                case 4:
                    saveStep(ActionMix, recipeIdx);
                    break;
                case 5:
                    saveStep(ActionFreeze, recipeIdx);
                    break;
                default:
                    saveStep(ActionFill, recipeIdx);
                    break;
            }
        }
    }
}

float GameMain::getToppingPositionX(int toppingIdx)
{
    return toppingContainer->getToppingPositionX(toppingIdx);
}

void GameMain::iceCreamMaskCallBack(IceCream* caller, int recipeIdx)
{
    if (hintViewer) {
        hintViewer->iceCreamAction(recipeIdx);
    }

    if (!callBackStop && iceCream) {
        saveStep(ActionMaskOff, recipeIdx);

    }
}

void GameMain::toppingContainerCallBack(int recipeIdx)
{
    if (hintViewer) {
        hintViewer->toppingAction(recipeIdx);
    }

    if (!callBackStop && iceCream) {
        saveStep(ActionTopping, recipeIdx);

    }
}

void GameMain::CallbackSlideNextRope(void* _obj) {
    if(reinterpret_cast<GameMain*>(_obj)->IsActiveUI()) {
        reinterpret_cast<GameMain*>(_obj)->NextIceCream();
        reinterpret_cast<GameMain*>(_obj)->nextRopeSlider->SetEnable(false);
        reinterpret_cast<GameMain*>(_obj)->recipeContainerCallBack(-1);
//        reinterpret_cast<GameMain*>(_obj)->saveStep();
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

//for UnDo
//
void writeVBImageToFile(GameMain* gameMain, int step) {
    VBString* filePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/gameMain_step_%d.step", VBStringGetCString(VBEngineGetDocumentPath()), step);
    
    bool hasNext = gameMain->iceCream->next != NULL;
    
    VBImage* image1 = NULL; //imgBG
    VBImage* image2 = NULL; //imgBridge
    VBImage* image3 = NULL; //imgBitmask
    int w1, h1, b1, t1, w2, h2, b2, t2, w3, h3, b3, t3;
    VBULong s1, s2, s3;
    if (!hasNext) {
        image1 = gameMain->iceCream->imgBG;
        w1 = VBImageGetWidth(image1);
        h1 = VBImageGetHeight(image1);
        b1 = VBImageGetColorBit(image1);
        t1 = VBImageGetColorType(image1);
        s1 = VBImageGetImageDataSize(image1);
        image2 = gameMain->iceCream->imgBridge;
        w2 = VBImageGetWidth(image2);
        h2 = VBImageGetHeight(image2);
        b2 = VBImageGetColorBit(image2);
        t2 = VBImageGetColorType(image2);
        s2 = VBImageGetImageDataSize(image2);
        image3 = gameMain->iceCream->imgBitmask;
        w3 = VBImageGetWidth(image3);
        h3 = VBImageGetHeight(image3);
        b3 = VBImageGetColorBit(image3);
        t3 = VBImageGetColorType(image3);
        s3 = VBImageGetImageDataSize(image3);
        
    } else {
        image1 = gameMain->iceCream->next->imgBG;
        w1 = VBImageGetWidth(image1);
        h1 = VBImageGetHeight(image1);
        b1 = VBImageGetColorBit(image1);
        t1 = VBImageGetColorType(image1);
        s1 = VBImageGetImageDataSize(image1);
        image2 = gameMain->iceCream->next->imgBitmask;
        w2 = VBImageGetWidth(image2);
        h2 = VBImageGetHeight(image2);
        b2 = VBImageGetColorBit(image2);
        t2 = VBImageGetColorType(image2);
        s2 = VBImageGetImageDataSize(image2);
    }
    
    FILE* file = fopen(VBStringGetCString(filePath), "w");
    VBStringFree(&filePath);
    
    fwrite(&hasNext, 1, sizeof(bool), file);
    fwrite(&w1, 1, sizeof(int), file);
    fwrite(&h1, 1, sizeof(int), file);
    fwrite(&b1, 1, sizeof(int), file);
    fwrite(&t1, 1, sizeof(int), file);
    fwrite(&s1, 1, sizeof(VBULong), file);
    fwrite(VBImageGetImageData(image1), 1, s1, file);
    fwrite(&w2, 1, sizeof(int), file);
    fwrite(&h2, 1, sizeof(int), file);
    fwrite(&b2, 1, sizeof(int), file);
    fwrite(&t2, 1, sizeof(int), file);
    fwrite(&s2, 1, sizeof(VBULong), file);
    fwrite(VBImageGetImageData(image2), 1, s2, file);
    if (!hasNext) {
        fwrite(&w3, 1, sizeof(int), file);
        fwrite(&h3, 1, sizeof(int), file);
        fwrite(&b3, 1, sizeof(int), file);
        fwrite(&t3, 1, sizeof(int), file);
        fwrite(&s3, 1, sizeof(VBULong), file);
        fwrite(VBImageGetImageData(image3), 1, s3, file);
    }
    fclose(file);
}


void loadVBImageFromFile(int step, VBImage** _image1, VBImage** _image2, VBImage** _image3, bool _isCustomStep) {
    VBString* filePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/gameMain_step_%d.step", VBStringGetCString(VBEngineGetDocumentPath()), step);
    if (access(VBStringGetCString(filePath), F_OK) != 0) {
        VBStringFree(&filePath);
        printf("file not found: %d\n", step);
        return;
    }
    
    FILE* file = fopen(VBStringGetCString(filePath), "rb");
    VBStringFree(&filePath);
    
    bool hasNext = false;
    VBImage* image1 = NULL;
    VBImage* image2 = NULL;
    VBImage* image3 = NULL;
    int width, height, colorBit, colorType;
    VBULong dataSize;
    
    fread(&hasNext, 1, sizeof(bool), file);
    fread(&width, 1, sizeof(int), file);
    fread(&height, 1, sizeof(int), file);
    fread(&colorBit, 1, sizeof(int), file);
    fread(&colorType, 1, sizeof(int), file);
    fread(&dataSize, 1, sizeof(VBULong), file);
    void* imageData = malloc(dataSize);
    fread(imageData, 1, dataSize, file);
    image1 = VBImageInitWithData(VBImageAlloc(), colorType, colorBit, width, height, imageData);
    free(imageData);
    imageData = NULL;
    fread(&width, 1, sizeof(int), file);
    fread(&height, 1, sizeof(int), file);
    fread(&colorBit, 1, sizeof(int), file);
    fread(&colorType, 1, sizeof(int), file);
    fread(&dataSize, 1, sizeof(VBULong), file);
    imageData = malloc(dataSize);
    fread(imageData, 1, dataSize, file);
    image2 = VBImageInitWithData(VBImageAlloc(), colorType, colorBit, width, height, imageData);
    free(imageData);
    imageData = NULL;
    if (!hasNext) {
        fread(&width, 1, sizeof(int), file);
        fread(&height, 1, sizeof(int), file);
        fread(&colorBit, 1, sizeof(int), file);
        fread(&colorType, 1, sizeof(int), file);
        fread(&dataSize, 1, sizeof(VBULong), file);
        imageData = malloc(dataSize);
        fread(imageData, 1, dataSize, file);
        image3 = VBImageInitWithData(VBImageAlloc(), colorType, colorBit, width, height, imageData);
        free(imageData);
    }
    fclose(file);
    
    
    *_image1 = image1;
    *_image2 = image2;
    *_image3 = !hasNext ? image3 : NULL;
    
    printf("load end: %d\n", step);
    if (!_isCustomStep) {
        filePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/gameMain_step_%d.step", VBStringGetCString(VBEngineGetDocumentPath()), step+1);
        remove(VBStringGetCString(filePath));
        VBStringFree(&filePath);
    }
        
}

void moveToppingCellStateBack(VBArrayVector* toppingData, int toppingIdx) {
    
    ToppingContainerCellData* cell;
    for (int i=0; i<VBArrayVectorGetLength(toppingData); i++) {
        cell = (ToppingContainerCellData*)VBArrayVectorGetDataAt(toppingData, i);
        if (cell->type == toppingIdx) {
            cell->step = cell->step-1;
            if (cell->innerModel) {
                cell->innerModel->gotoAndStop(cell->innerModel->cur_frame - 1);
            } else {
                cell->model->gotoAndStop(0);
            }
        }
    }
    
}

bool GameMain::saveStep(ActionType actionType, int itemIdx) {
    IceCream* iceCreamOnTop = iceCream->next == NULL ? iceCream : iceCream->next;
    while (iceCreamOnTop->isRun_draw_pixel_thread) {
        usleep(16666);
    }
    printf("****saveStep()**** stepCount:%d\n", stepCount);
    stepCount++;
    
    IceCream* changeSelected = iceCream->next ? iceCream->next : iceCream;
    switch (actionType) {
        case ActionSubTopping:case ActionSubToppingFlow:
        {
            cJSON *res = cJSON_GetArrayItem(ShareDataGetRes(), 3);
            cJSON *item = cJSON_GetArrayItem(res, itemIdx);
            int position = cJSON_GetArrayItem(item, 3)->valueint;
            pushHistory(actionType, itemIdx, position);
        }
            break;
        case ActionTopping:
        {
            cJSON *res = cJSON_GetArrayItem(ShareDataGetRes(), 2);
            cJSON *item = cJSON_GetArrayItem(res, itemIdx);
            int type = cJSON_GetArrayItem(item, 1)->valueint;
            if (type == 0) {
                // count spuitL, spuitR
                pushHistory(ActionToppingSpuit, itemIdx);
            }
            else if (type == 1)
                pushHistory(ActionToppingFlow, itemIdx);
            else if (type == 2)
                pushHistory(ActionToppingCream, itemIdx);
            else if (type == 3)
                pushHistory(ActionToppingCherry, itemIdx);
        }   
            break;
        case ActionMix:
        {
            drawIceCremArg* mix = new drawIceCremArg(changeSelected->fillArg);
            pushHistory(actionType, itemIdx, 0, mix, changeSelected->bitmaskMerge);
        }
            break;
        default:
        {
            drawIceCremArg* mix = new drawIceCremArg(changeSelected->fillArg);
            pushHistory(actionType, itemIdx, 0, mix, changeSelected->bitmaskMerge);
        }
            break;
    }
    writeVBImageToFile(this, stepCount);
    
    
    return true;
}

void GameMain::unDo() {
    printf("****unDo()**** stepCount:%d\n", stepCount);
    if (stepCount < 1) {
        return;
    }
    
    //load icecream
    VBImage* image1;
    VBImage* image2;
    VBImage* image3;
    loadVBImageFromFile(stepCount-1, &image1, &image2, &image3, false);
    
    bool hasNext = image3 == NULL;
    
    //pop history
    HistoryList lastStep = popHistory();
    IceCream* changeSelected = hasNext ? iceCream->next : iceCream;
    
    //change icecream
    if (!hasNext) {
        if (lastStep.actionType == ActionNext) {
            VBImageFree(&image1);
            VBImageFree(&image2);
            VBImageFree(&image3);
            if (iceCream->modelLastRecipeBridge) {
                iceCream->removeChild(iceCream->modelLastRecipeBridge, false);
            }
            iceCream->removeChild(iceCream->modelBridge, false);
            iceCream->removeChild(iceCream->modelBridgeOutline, false);
            iceCream->removeChild(iceCream->next, false);
            
            delete iceCream->next;
            iceCream->next = NULL;
            
            nextRopeSlider->SetEnable(true);
            cout << "next icecream removed\n";
        } else {
            VBImage* temp = iceCream->imgBG;
            iceCream->imgBG = image1;
            image1 = NULL;
            VBImageFree(&temp);
            temp = iceCream->imgBridge;
            iceCream->imgBridge = image2;
            image2 = NULL;
            VBImageFree(&temp);
            temp = iceCream->imgBitmask;
            iceCream->imgBitmask = image3;
            image3 = NULL;
            VBImageFree(&temp);
        }
    } else {
        VBImage* temp = iceCream->next->imgBG;
        iceCream->next->imgBG = image1;
        image1 = NULL;
        VBImageFree(&temp);
        temp = iceCream->next->imgBitmask;
        iceCream->next->imgBitmask = image2;
        image2 = NULL;
        VBImageFree(&temp);
    }
    
    //remove next if previos step doesn't have next
    if (!hasNext && iceCream->next) {
        printf("\niceCream->next init\n");
        VBImageFree(&image1);
        VBImageFree(&image2);
        VBImageFree(&image3);
        loadVBImageFromFile(1, &image1, &image2, &image3, true);
        VBImage* temp = iceCream->next->imgBG;
        iceCream->next->imgBG = image1;
        image1 = NULL;
        VBImageFree(&temp);
        temp = iceCream->next->imgBridge;
        iceCream->next->imgBridge = image2;
        image2 = NULL;
        VBImageFree(&temp);
        temp = iceCream->next->imgBitmask;
        iceCream->next->imgBitmask = image3;
        VBImageFree(&temp);
        hasNext = true;
        iceCream->next->need_update_pixel = true;
        iceCream->next->Reshape();
    } else {
        IceCream* changeSelected = hasNext ? iceCream->next : iceCream;
        
        while (changeSelected->isRun_draw_pixel_thread) {
            usleep(16666);
        }
        changeSelected->need_update_pixel = true;
        changeSelected->Reshape();
    }
    
    //mask, subtopping, topping
    switch (lastStep.actionType) {
        /**
         * fill
         */
        case ActionFill:
            changeSelected->bitmaskMerge = lastStep.bitmaskMerge;
            changeSelected->fillArg = drawIceCremArg(*(lastStep.mix));
            free(lastStep.mix);
        /**
         * mix
         */
        case ActionMix:
            changeSelected->bitmaskMerge = lastStep.bitmaskMerge;
            changeSelected->fillArg = drawIceCremArg(*(lastStep.mix));
            free(lastStep.mix);
            break;
        /**
         * freeze
         */
        case ActionFreeze:
            changeSelected->removeChild(changeSelected->modelLastRecipe, false);
            changeSelected->removeChild(changeSelected->modelLastRecipeBridge, false);
            delete changeSelected->modelLastRecipe;
            delete changeSelected->modelLastRecipeBridge;
            changeSelected->modelLastRecipe = NULL;
            changeSelected->modelLastRecipeBridge = NULL;
            break;
        /**
         * mask
         */
        case ActionMaskOn:
            for (int i=0; i<VBArrayVectorGetLength(changeSelected->mask); i++) {
                RecipeMask *mask = (RecipeMask*)VBArrayVectorGetDataAt(changeSelected->mask, i);
                if (mask->idx == lastStep.recipeIdx) {
                    callBackStop = true;
                    changeSelected->ClearMask(mask, 1);
                    callBackStop = false;
                    break;
                }
            }
            break;
        case ActionMaskOff:
            for (int i=0; i<VBArrayVectorGetLength(rdTd->rdVec); i++) {
                RT* _rt = (RT*)VBArrayVectorGetDataAt(rdTd->rdVec, i);
                if (_rt->type == 1) {
                    RecipeMask *mask = (RecipeMask*)_rt->data;
                    if (mask->idx == lastStep.recipeIdx) {
                        
                        changeSelected->AddMask(mask);
                        changeSelected->need_update_model = true;
                        break;
                    }
                }
            }

            break;
        /**
         * subTopping
         */
        case ActionSubToppingFlow:
            VBArrayVectorRemoveBack((VBArrayVector*)VBArrayVectorGetDataAt(changeSelected->subToppingFlow, lastStep.position));
            VBArrayVectorRemoveBack(changeSelected->thumbs);
            changeSelected->need_update_model = true;
            
            break;
        case ActionSubTopping:
            VBArrayVectorRemoveAt(changeSelected->subTopping, lastStep.position);
            VBArrayVectorRemoveBack(changeSelected->thumbs);
            changeSelected->need_update_model = true;
            break;
        /**
         * topping
         */
        case ActionToppingRope:
            toppingRopeSlider->SetEnable(true);
            SwapRecipeAndToppingMode();
            if (!iceCream->next) {
                nextRopeSlider->SetEnable(true);
            }
            break;
        case ActionToppingSpuit:
        {
            ToppingContainerCellData* cell = (ToppingContainerCellData*)VBArrayVectorGetDataAt(toppingData, lastStep.recipeIdx);
            if (cell->step % 2 == 0) {
                VBArrayVectorRemoveBack(changeSelected->toppingSpuitR);
            } else {
                VBArrayVectorRemoveBack(changeSelected->toppingSpuitL);
            }
            VBArrayVectorRemoveBack(changeSelected->thumbs);
            changeSelected->need_update_model = true;
            moveToppingCellStateBack(toppingData, lastStep.recipeIdx);
        }
            break;
        case ActionToppingFlow:
        {
            VBArrayVectorRemoveBack(changeSelected->toppingFlow);
            VBArrayVectorRemoveBack(changeSelected->thumbs);
            changeSelected->need_update_model = true;
            moveToppingCellStateBack(toppingData, lastStep.recipeIdx);
        }
            break;
        case ActionToppingCherry:
        {
            for (int i=0; i<changeSelected->thumbs->len; i++) {
                Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(changeSelected->thumbs, i);
                if (_t->type == 2) {
                    changeSelected->addChild(_t->model);
                    break;
                }
            }
            
            changeSelected->toppingCherry = NULL;
            VBArrayVectorRemoveBack(changeSelected->thumbs);
            changeSelected->need_update_model = true;
            
            moveToppingCellStateBack(toppingData, lastStep.recipeIdx);
        }
            break;
        case ActionToppingCream:
            changeSelected->toppingCream = NULL;
            VBArrayVectorRemoveBack(changeSelected->thumbs);
            changeSelected->need_update_model = true;
            moveToppingCellStateBack(toppingData, lastStep.recipeIdx);
            break;
        default:
            break;
    }
    //TODO: 2단 쌓을때 history 관리
    
    hintViewer->backStep();
    stepCount--;
    printf("reduce stepCount\n");
}

void GameMain::resetAllStep() {
    stepCount = 0;
    clearHistory();
    //delete remain files
    for (int i=1; ; i++) {
        VBString* filePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/gameMain_step_%d.step", VBStringGetCString(VBEngineGetDocumentPath()), i);
        if (access(VBStringGetCString(filePath), F_OK) != 0) {
            VBStringFree(&filePath);
            break;
        }
        remove(VBStringGetCString(filePath));
        printf("remove %d\n", i);
        VBStringFree(&filePath);
    }
}

void GameMain::pushHistory(ActionType _actionType, int _recipeIdx, int _position, drawIceCremArg* _mix, unsigned long _bitmaskMerge) {
    HistoryList *newStep = new HistoryList();
    newStep->actionType = _actionType;
    newStep->recipeIdx = _recipeIdx;
    newStep->position = _position;
    if (_mix != NULL) {
        newStep->mix = _mix;
    }
    if (_bitmaskMerge != 0) {
        newStep->bitmaskMerge = _bitmaskMerge;
    }
    newStep->next = history;
    history = newStep;
}

HistoryList GameMain::popHistory() {
    if (!history) {
        return HistoryList();
    }
    HistoryList *lastStep = history;
    history = history->next;

    HistoryList returnVar = HistoryList();
    returnVar.actionType = lastStep->actionType;
    returnVar.recipeIdx = lastStep->recipeIdx;
    returnVar.position = lastStep->position;
    returnVar.mix = lastStep->mix;
    free(lastStep);
    
    return returnVar;
}

void GameMain::clearHistory() {
    HistoryList *temp = NULL;
    while (history) {
        temp = history;
        history = history->next;
        if (temp->mix) {
            free(temp->mix);
        }
        free(temp);
    }
}

void GameMain::initHistory() {
    clearHistory();
    writeVBImageToFile(this, 0);
    pushHistory(ActionNone, 0);
}

bool GameMain::getNextRopeEnable()
{
    return nextRopeSlider->GetEnable();
}

bool GameMain::getToppingRopeEnable()
{
    return toppingRopeSlider->GetEnable();
}

void GameMain::setNextRopeEnable(bool flag) {
    nextRopeSlider->SetEnable(flag);
}

void GameMain::setToppingRopeEnable(bool flag) {
    toppingRopeSlider->SetEnable(flag);
}
