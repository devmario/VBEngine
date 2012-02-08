//
//  GamemainRdTd.cpp
//  gelatomania
//
//  Created by Kyung Gak Nam on 12. 2. 7..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#include "GameMainRdTd.h"

GameMainRdTd::GameMainRdTd(int _packIdx, int _stageIdx)
{
    retainCount = 1;
    cJSON* _stJ = ShareDataGetStageJSONAt(_packIdx, _stageIdx);
    cJSON* _rcJ = cJSON_GetObjectItem(_stJ, "recipe");
    
    rd = NULL;
    rdLen = 0;
    td = NULL;
    tdLen = 0;
    
    cook = cookRdTd();
    
    cook.rtc = NULL;
    cook.rtcArrLen = NULL;
    cook.rtcLen = cJSON_GetArraySize(_rcJ) - 1;
    cook.tc = NULL;
    cook.tcLen = 0;
    
    bool _hasTopping = cJSON_GetArrayItem(cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1), 0)->valueint != -1;
    
    if(cook.rtcLen > 0) {
        cook.rtc = (int**)calloc(cook.rtcLen, sizeof(int*));
        cook.rtcArrLen = (int*)calloc(cook.rtcLen, sizeof(int));
    }
    
    for(int i = 0; i < cook.rtcLen; i++) {
        cJSON* _rdData = cJSON_GetArrayItem(_rcJ, i);
        cook.rtcArrLen[i] = cJSON_GetArraySize(_rdData);
        cook.rtc[i] = (int*)calloc(cook.rtcArrLen[i], sizeof(int));
        for(int j = 0; j < cook.rtcArrLen[i]; j++) {
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
            cook.rtc[i][j] = _curT;
        }
    }
    
    if(_hasTopping) {
        cJSON* _tdData = cJSON_GetArrayItem(_rcJ, cJSON_GetArraySize(_rcJ) - 1);
        cook.tcLen = cJSON_GetArraySize(_tdData);
        cook.tc = (int*)calloc(cook.tcLen, sizeof(int));
        for(int i = 0; i < cook.tcLen; i++) {
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
            cook.tc[i] = _curT;
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
    
}

GameMainRdTd::~GameMainRdTd()
{
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
    
    for (int i=0; i<cook.rtcLen; i++) {
        if (cook.rtc[i]) {
            free(cook.rtc[i]);
        }
    }
    if (cook.rtc)
        free(cook.rtc);
    if (cook.rtcArrLen)
        free(cook.rtcArrLen);
    if (cook.tc)
        free(cook.tc);
}

void GameMainRdTd::retain()
{
    if (retainCount > 0) {
        retainCount++;
    }
}
void GameMainRdTd::release()
{
    if (retainCount > 1) {
        retainCount--;
    } else if (retainCount == 1) {
        delete this;
    }
}