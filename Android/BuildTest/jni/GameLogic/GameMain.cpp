#include "GameMain.h"
#include "ShareData.h"

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
    
    objBg = (VBObjectFile2D**)calloc(cJSON_GetArraySize(_layer), sizeof(VBObjectFile2D*));
    texBg = (VBTexture**)calloc(cJSON_GetArraySize(_layer), sizeof(VBTexture*));
    char _buf[0xFF] = {NULL,};
    for(int i = 0; i < cJSON_GetArraySize(_layer); i++) {
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

void GameMain::InitModel(cJSON* _layer, cJSON* _ui) {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _name_id;
    
    modelBg = (VBModel**)calloc(cJSON_GetArraySize(_layer) + 1, sizeof(VBModel*));
    for(int i = 0; i < cJSON_GetArraySize(_layer); i++) {
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

void GameMain::InitCook(int** _rtc, int _rtcLen, int* _rtcArrLen, int* _tc, int _tcLen) {
    for(int i = 0; i < _rtcLen; i++) {
        if(i == 0)
            baseIceCream = new IceCream(rdVec, tdVec, NULL, _rtc[i], _rtcArrLen[i]);
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
    
    iceCream = new IceCream(rdVec, tdVec, baseIceCream);
    iceCream->setScale(0.5);
    iceCream->setPosition(CCPointMake(-2, 92-63));
    modelRailIce[0]->addChild(iceCream);
    nextIceCream = NULL;
    
    delIceCream = NULL;
    nextIceCreamMotion = NULL;
    dragIce = NULL;
}

void GameMain::InitRecipe() {
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

void GameMain::InitTopping() {
    toppingTweener = NULL;
    toppingTweenerParam = NULL;
    toppingTweenerTime = 0.0;
    toppingTweenerTimeCount = 0.0;
    toppingData = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < VBArrayVectorGetLength(tdVec); i++) {
        RT* _rt = (RT*)VBArrayVectorGetDataAt(tdVec, i);
        VBArrayVectorAddBack(toppingData, ToppingContainerCellDataInit(_rt->idx));
    }
    VBArrayVectorQuickSort(toppingData, ToppingSort);
    //printf("removed %i\n", VBArrayVectorGetLength(toppingData));
    
    toppingTweenerY = 160;
    if(VBArrayVectorGetLength(toppingData)) {
        toppingContainer = new ToppingContainer(objScroll, texScroll, toppingData, iceCream);
        toppingContainer->setPosition(CCPointMake(0, toppingTweenerY));
        if(modelUI->getVBModelByInstanceName("topping") == NULL) {
            cout << "ui무비클립안에 topping instance name의 무비클립이 없음.\n";
        }
        modelUI->getVBModelByInstanceName("topping")->addChild(toppingContainer);
    } else {
        toppingContainer = NULL;
    }
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

GameMain::GameMain(int _packIdx, int _stageIdx) {
    cJSON* _j = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetJSON(), "pack"), _packIdx);
    cJSON* _layer = cJSON_GetObjectItem(_j, "objLayer");
    cJSON* _ui = cJSON_GetObjectItem(_j, "objUI");
    
    LoadResource(_layer, _ui);
    InitModel(_layer, _ui);
    
    cJSON* _stJ = ShareDataGetStageJSONAt(_packIdx, _stageIdx);
    cJSON* _rcJ = cJSON_GetObjectItem(_stJ, "recipe");
    
    rd = NULL;
    rdLen = 0;
    td = NULL;
    tdLen = 0;
    int* _tc = NULL;
    int _tcLen = 0;
    int _rtcLen = cJSON_GetArraySize(_rcJ) - 1;
    bool _hasTopping = false;
    int** _rtc = NULL;
    int* _rtcArrLen = 0;
    _hasTopping = cJSON_GetArrayItem(cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1), 0)->valueint != -1;
    if(_rtcLen > 0) {
        _rtc = (int**)calloc(_rtcLen, sizeof(int*));
        _rtcArrLen = (int*)calloc(_rtcLen, sizeof(int));
    }
    for(int i = 0; i < cJSON_GetArraySize(_rcJ); i++) {
        cJSON* _rtcIn = cJSON_GetArrayItem(_rcJ, i);
        if(i == cJSON_GetArraySize(_rcJ) - 1) {
            if(_hasTopping) {
                _tcLen = cJSON_GetArraySize(_rtcIn);
                _tc = (int*)calloc(_tcLen, sizeof(int));
                for(int j = 0; j < _tcLen; j++) {
                    int _curT = cJSON_GetArrayItem(_rtcIn, j)->valueint;
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
                    _tc[j] = _curT;
                }
            }
        } else {
            _rtcArrLen[i] = cJSON_GetArraySize(_rtcIn);
            _rtc[i] = (int*)calloc(_rtcArrLen[i], sizeof(int));
            for(int j = 0; j < _rtcArrLen[i]; j++) {
                int _curT = cJSON_GetArrayItem(_rtcIn, j)->valueint;
                if(i < cJSON_GetArraySize(_rcJ) - 1) {
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
                }
                _rtc[i][j] = _curT;
            }
        }
    }
    
    int _rdLen = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetRes(), "recipe"));
    int _rd[_rdLen];
    for(int i = 0; i < _rdLen; i++)
        _rd[i] = i;
    int _tdLen = cJSON_GetArraySize(cJSON_GetObjectItem(ShareDataGetRes(), "topping"));
    int _td[_tdLen];
    for(int i = 0; i < _tdLen; i++)
        _td[i] = i;
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
    tdVec = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < _tdLen; i++) {
        //printf("%s\n", cJSON_Print(cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "topping"), _td[i])));
        cJSON* _item = cJSON_GetArrayItem(cJSON_GetObjectItem(ShareDataGetRes(), "topping"), _td[i]);
        int _type = cJSON_GetArrayItem(_item, 1)->valueint;
        void* _t = NULL;
        if(_type == 0) {
            //printf("init topping spuit\n");
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
    
    //InitCook(rd, rdLen, td, tdLen, _rtc, _rtcLen, _rtcArrLen, _tc, _tcLen);
    
    //isRecipeMode = true;
    //InitRecipe(rd, rdLen);
    //InitTopping(td, tdLen);
    InitCook(_rtc, _rtcLen, _rtcArrLen, _tc, _tcLen);
    isRecipeMode = true;
    InitRecipe();
    InitTopping();
    
    hintViewer = new HintViewer(this, true);
    hintViewer->setSolution(_rtc, _rtcLen, _rtcArrLen, _tc, _tcLen);
    
    for(int i = 0; i < _rtcLen; i++)
        free(_rtc[i]);
    if(_rtc)
        free(_rtc);
    if(_rtcArrLen)
        free(_rtcArrLen);
    if(_tc)
        free(_tc);
    
    InitRope();
    
    printf("new GameMain\n");
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
    if(nextRopeSlider)
        delete nextRopeSlider;
    if(toppingRopeSlider)
        delete toppingRopeSlider;
    
    if(td)
        free(td);
    if(rd)
        free(rd);
    
    if(nextIceCream) {
        modelArm->getVBModelByInstanceName("id_dy_obj_armNode")->removeChild(nextIceCream, false);
        delete nextIceCream;
    }
    
    modelUI->getVBModelByInstanceName("arm")->removeChild(modelArm, false);
    delete modelArm;
    
    if(nextIceCreamMotion) {
        top->removeChild(nextIceCreamMotion, false);
        delete nextIceCreamMotion;
    }
    
    top->removeChild(baseIceCream, false);
    delete baseIceCream;
    
    if(delIceCream) {
        modelRailIce[0]->removeChild(delIceCream, false);
        delete delIceCream;
        modelRailIce[1]->removeChild(iceCream, false);
    } else {
        modelRailIce[0]->removeChild(iceCream, false);
    }
    delete iceCream;
    
    ClearToppingTween();
    if(toppingContainer) {
        modelUI->getVBModelByInstanceName("topping")->removeChild(toppingContainer, false);
        delete toppingContainer;
    }
    while (VBArrayVectorGetLength(toppingData)) {
        ToppingContainerCellData* _data = (ToppingContainerCellData*)VBArrayVectorRemoveBack(toppingData);
        ToppingContainerCellDataFree(&_data);
    }
    VBArrayVectorFree(&toppingData);
    
    modelUI->getVBModelByInstanceName("right")->getVBModelByInstanceName("shelf")->removeChild(recipeContainer, false);
    delete recipeContainer;
    while(VBArrayVectorGetLength(recipeData)) {
        RecipeContainerCellData* _cell = (RecipeContainerCellData*)VBArrayVectorRemoveBack(recipeData);
        RecipeContainerCellDataFree(&_cell);
    }
    VBArrayVectorFree(&recipeData);
    
    while(VBArrayVectorGetLength(rdVec)) {
        RT* _rt = (RT*)VBArrayVectorRemoveBack(rdVec);
        //printf("%lx ", (long)_rt->data);
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
        //printf("r %i %i %s\n", _rt->type, _rt->idx, _rt->data ? "nonNULL" : "NULL");
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
        //printf("t %i %i %s\n", _rt->type, _rt->idx, _rt->data ? "nonNULL" : "NULL");
        RTFree(&_rt);
    }
    VBArrayVectorFree(&tdVec);
    
    VBObjectFile2DFree(&objScroll);
    VBTextureFree(&texScroll);
    int i = 0;
    while(modelBg[i]) {
        top->removeChild(modelBg[i], false);
        delete modelBg[i];
        modelBg[i] = NULL;
        VBObjectFile2DFree(&objBg[i]);
        VBTextureFree(&texBg[i]);
        i++;
    }
    free(modelBg);
    free(objBg);
    free(texBg);
    
    top->removeChild(modelUI, false);
    delete modelUI;
    VBObjectFile2DFree(&objUI);
    VBObjectFile2DFree(&objArm);
    VBObjectFile2DFree(&objFont);
    VBTextureFree(&texUI);
    VBTextureFree(&texArm);
    VBTextureFree(&texFont);
    
    hintViewer->hide();
    delete hintViewer;
    
    printf("delete GameMain\n");
}

void GameMain::NextIceCream() {
    nextIceCream = new IceCream(rdVec, tdVec, NULL);
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
    iceCream = new IceCream(rdVec, tdVec, baseIceCream);
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
    
    recipeContainer->Update(_deltaTime);
    if(toppingContainer)
        toppingContainer->Update(_deltaTime);
    
    if(toppingRopeSlider)
        toppingRopeSlider->Update(_deltaTime);
    if(nextRopeSlider)
        nextRopeSlider->Update(_deltaTime);
    
    UpdateToppingTween(_deltaTime);
    
    modelDownButton->gotoAndStop(recipeContainer->IsPossibleNextPage() ? 1.0 : 0.0);
    modelUpButton->gotoAndStop(recipeContainer->IsPossiblePrevPage() ? 1.0 : 0.0);
    
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
    if(touchDown == NULL && touchUp == NULL)
        recipeContainer->touchBegin(_touch, _location);
    if(toppingContainer)
        toppingContainer->touchBegin(_touch, _location);
    
    TOUCHBEGINBT(touchCook, iceCream, _location, _touch, 
                 dragIce = iceCream->DragStartMount(top);
                 if(dragIce) {
                     dragIce->setPosition(CCPointMake(dragIce->getPosition().x + _location.x, dragIce->getPosition().y + (-320 + _location.y)));
                     dragPre = _location;
                 }
                 );
    TOUCHBEGINBT(touchPause, modelPauseButton, _location, _touch, modelPauseButton->gotoAndStop(1.0));
    TOUCHBEGINBT(touchNew, modelNewButton, _location, _touch, modelNewButton->gotoAndStop(1.0));
}

void GameMain::touchMove(CCTouch* _touch, CCPoint _location) {
    if(nextRopeSlider)
        nextRopeSlider->TouchMove(_touch, _location);
    if(toppingRopeSlider)
        toppingRopeSlider->TouchMove(_touch, _location);
    if(touchDown == NULL && touchUp == NULL)
        recipeContainer->touchMove(_touch, _location);
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
               recipeContainer->NextPage();
               ,);
    TOUCHENDBT(touchUp, modelUpButton, _location, _touch, 
               recipeContainer->PrevPage();
               ,);
    TOUCHENDBT(touchCook, iceCream, _location, _touch, ,
               if(dragIce) {
                   iceCream->DragEndMount(dragIce->hitTest(recipeContainer));
                   dragIce = NULL;
               }
               );
    TOUCHENDBT(touchPause, modelPauseButton, _location, _touch, ShareDataGetRoot()->OpenPopup(0, 0, 0), modelPauseButton->gotoAndStop(0.0));
    TOUCHENDBT(touchNew, modelNewButton, _location, _touch, 
               if(IsActiveUI()) {
                   if(nextRopeSlider) nextRopeSlider->SetEnable(true);
                   if(!IsRecipeMode()) SwapRecipeAndToppingMode();
                   if(toppingContainer) {
                       if(toppingRopeSlider) toppingRopeSlider->SetEnable(true);
                   }
                   NewIceCream();
                   //for hintviewer
                   recipeContainerCallBack(-3);
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
    if(touchDown == NULL && touchUp == NULL)
        recipeContainer->touchEnd(_touch, _location);
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
    hintViewer->step(recipeIdx);
}

