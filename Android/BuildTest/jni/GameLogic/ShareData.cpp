//
//  ShareData.c
//  gelatomania
//
//  Created by wonhee jang on 11. 12. 22..
//  Copyright (c) 2011 VanillaBreeze. All rights reserved.
//

#include "ShareData.h"
#include <stdio.h>
#include <stdarg.h>

VBObjectFile2D* _shareTitleObj = NULL;
VBTexture* _shareTitleTexture = NULL;
VBModel* _shareLoadingModel = NULL;
Root* _shareRoot = NULL;
VBArrayVector* _sharePackRoot = NULL;
cJSON* _shareJSON = NULL;

cJSON* _shareResJSON = NULL;
VBArrayVector* _shareStageRoot = NULL;
cJSON* _shareInAppJSON = NULL;

cJSON* _shareTempJSON = NULL;

int pid = 0;
int sid = 0;
int _getpid(){return pid;}
int _getsid(){return sid;}
void _setpid(int _p){pid=_p;}
void _setsid(int _s){sid=_s;}

int hexToInt(char* szHex) {
    int hex = 0;
    int nibble;
    while (*szHex) {
        hex <<= 4;
        if (*szHex >= '0' && *szHex <= '9') {
            nibble = *szHex - '0';
        } else if (*szHex >= 'a' && *szHex <= 'f') {
            nibble = *szHex - 'a' + 10;
        } else if (*szHex >= 'A' && *szHex <= 'F') {
            nibble = *szHex - 'A' + 10;
        } else {
            nibble = 0;
        }
        hex |= nibble;
        szHex++;
    }
    return hex;
}

VBAABB JStoAABB(cJSON* _js) {
    cJSON* aabb = cJSON_GetObjectItem(_js, "aabb");
    return VBAABBCreate(cJSON_GetArrayItem(aabb, 0)->valuedouble, 
                        cJSON_GetArrayItem(aabb, 1)->valuedouble, 
                        cJSON_GetArrayItem(aabb, 2)->valuedouble, 
                        cJSON_GetArrayItem(aabb, 3)->valuedouble);
}

cJSON* ShareDataGetTemplate() {
    if(_shareTempJSON == NULL) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "template.json");
        FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
        VBStringFree(&_str);
        
        fseek(_jSONFile, 0, SEEK_END);
        size_t _len = ftell(_jSONFile);
        fseek(_jSONFile, 0, SEEK_SET);
        
        char* _jSONData = (char*)calloc(1, _len + 1);
        fread(_jSONData, 1, _len, _jSONFile);
        
        fclose(_jSONFile);
        
        _shareTempJSON = cJSON_Parse(_jSONData);
        if(_shareTempJSON == NULL) {
            printf("Error before: [%s]\n",cJSON_GetErrorPtr());
            return NULL;
        }
        
        free(_jSONData);
    }
    return _shareTempJSON;
}

cJSON* ShareDataGetTemplateData(cJSON* _idx) {
    cJSON* _tmp = ShareDataGetTemplate();
    int _len = cJSON_GetArraySize(_idx);
    for(int i = 0; i < _len; i++) {
        cJSON* _tk = cJSON_GetArrayItem(_idx, i);
        _tmp = cJSON_GetObjectItem(_tmp, _tk->valuestring);
        if(_tmp == NULL)
            return NULL;
    }
    return _tmp;
}

cJSON* ShareDataSearchJSON(cJSON* _js, int _len, ...) {
    va_list ap;
    int i;
    
    va_start (ap, _len); 
    
    for(i = 0; i < _len; i++) {
        char* _val = va_arg(ap, char*); 
        _js = cJSON_GetObjectItem(_js, _val);
        if(_js == NULL)
            return NULL;
    }
    
    va_end(ap);
    
    return _js;
}

cJSON* ShareDataGetRes() {
    if(_shareResJSON == NULL) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "res.json");
        FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
        VBStringFree(&_str);
        
        fseek(_jSONFile, 0, SEEK_END);
        size_t _len = ftell(_jSONFile);
        fseek(_jSONFile, 0, SEEK_SET);
        
        char* _jSONData = (char*)calloc(1, _len + 1);
        fread(_jSONData, 1, _len, _jSONFile);
        
        fclose(_jSONFile);
        
        _shareResJSON = cJSON_Parse(_jSONData);
        if(_shareResJSON == NULL) {
            printf("Error before: [%s]\n",cJSON_GetErrorPtr());
            return NULL;
        }
        
        free(_jSONData);
    }
    return _shareResJSON;
}

VBArrayVector* ShareDataGetStageJSON() {
    if(_shareStageRoot == NULL) {
        _shareStageRoot = VBArrayVectorInit(VBArrayVectorAlloc());
        for(int i = 0; i < ShareDataGetPackLength(); i++) {
            VBArrayVector* _packArr = VBArrayVectorInit(VBArrayVectorAlloc());
            for(int j = 0; j < ShareDataGetStageLength(i); j++) {
                VBArrayVectorAddBack(_packArr, NULL);
            }
            VBArrayVectorAddBack(_shareStageRoot, _packArr);
        }
    }
    return _shareStageRoot;
}

int ShareDataGetStageLength(int _idx) {
    cJSON* _json = ShareDataGetPackDataJSONAt(_idx);
    if(_json)
        return cJSON_GetArraySize(_json);
    else
        return 0;
}

cJSON* ShareDataGetStageDataJSONAt(int _packID, int _stageID) {
    cJSON* _json = ShareDataGetPackDataJSONAt(_packID);
    if(_json == NULL) {
        printf("PACK DATA NULL\n");
        return NULL;
    }
    _json = cJSON_GetArrayItem(_json, _stageID);
    return _json;
}

cJSON* ShareDataGetStageJSONAt(int _packID, int _stageID) {
    VBArrayVector* _packArr = (VBArrayVector*)VBArrayVectorGetDataAt(ShareDataGetStageJSON(), _packID);
    if(_packArr == NULL) {
        printf("NULL ARR'\n");
        return NULL;
    }
    cJSON* _stage = (cJSON*)VBArrayVectorGetDataAt(_packArr, _stageID);
    if(_stage == NULL) {
        if(ShareDataGetStageFilePathAt(_packID, _stageID) == NULL) {
            printf("NULL %i %i FilePat'\n", _packID, _stageID);
            return NULL;
        }
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), ShareDataGetStageFilePathAt(_packID, _stageID));
        FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
        VBStringFree(&_str);
        
        fseek(_jSONFile, 0, SEEK_END);
        size_t _len = ftell(_jSONFile);
        fseek(_jSONFile, 0, SEEK_SET);
        
        char* _jSONData = (char*)calloc(1, _len + 1);
        fread(_jSONData, 1, _len, _jSONFile);
        
        fclose(_jSONFile);
        
        _stage = cJSON_Parse(_jSONData);
        if(_stage == NULL) {
            printf("Error before: [%s]\n",cJSON_GetErrorPtr());
            return NULL;
        }
        
        free(_jSONData);
        
        _packArr->data[_stageID] = _stage;
    }
    return _stage;
}

int ShareDataGetStageScoreAt(int _packID, int _stageID) {
    cJSON* _json = ShareDataGetStageDataJSONAt(_packID, _stageID);
    if(_json == NULL)
        return false;
    _json = cJSON_GetObjectItem(_json, "score");
    return _json->valueint;
}

char* ShareDataGetStageFilePathAt(int _packID, int _stageID) {
    cJSON* _json = ShareDataGetStageDataJSONAt(_packID, _stageID);
    if(_json == NULL) {
        printf("STAGE DATA NULL\n");
        return NULL;
    }
    _json = cJSON_GetObjectItem(_json, "data");
    return _json->valuestring;
}

int ShareDataGetStageStarAt(int _packID, int _stageID) {
    cJSON* _json = ShareDataGetStageDataJSONAt(_packID, _stageID);
    if(_json == NULL)
        return false;
    _json = cJSON_GetObjectItem(_json, "star");
    return _json->valueint;
}

bool ShareDataGetStageLockAt(int _packID, int _stageID) {
    cJSON* _json = ShareDataGetStageDataJSONAt(_packID, _stageID);
    if(_json == NULL)
        return false;
    _json = cJSON_GetObjectItem(_json, "lock");
    return _json->valueint;
}

bool ShateDataGetHaveStage(int _idx) {
    cJSON* _packData = ShareDataGetPackDataJSONAt(_idx);
    if(_packData)
        return true;
    else
        return false;
}

int ShareDataGetStageLengthAt(int _idx) {
    cJSON* _packJSON = ShareDataGetPackDataJSONAt(_idx);
    if(_packJSON) {
        return cJSON_GetArraySize(_packJSON);
    }
    return 0;
}

char* ShareDataGetPackFileName(int _idx) {
    cJSON* _json = cJSON_GetObjectItem(ShareDataGetJSON(), "pack");
    _json = cJSON_GetArrayItem(_json, _idx);
    if(_json == NULL)
        return NULL;
    _json = cJSON_GetObjectItem(_json, "packData");
    if(_json == NULL)
        return NULL;
    return _json->valuestring;
}

cJSON* ShareDataGetPackDataJSONAt(int _idx) {
    return (cJSON*)VBArrayVectorGetDataAt(ShareDataGetPackDataJSON(), _idx);
}

void ShareDataPackDataSave() {
    for(int i = 0; i < ShareDataGetPackLength(); i++) {
        ShareDataPackDataSaveAt(i);
    }
}

void ShareDataPackDataSaveAt(int _idx) {
    if(ShareDataGetPackFileName(_idx) == NULL)
        return;
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), ShareDataGetPackFileName(_idx));
    FILE* _jSONFile = fopen(VBStringGetCString(_str), "w");
    VBStringFree(&_str);
    
    char* _json_str = cJSON_Print(ShareDataGetPackDataJSONAt(_idx));
    fwrite(_json_str, 1, strlen(_json_str), _jSONFile);
    free(_json_str);
    
    fclose(_jSONFile);
}

VBArrayVector* ShareDataGetPackDataJSON() {
    if(_sharePackRoot == NULL) {
        _sharePackRoot = VBArrayVectorInit(VBArrayVectorAlloc());
        for(int i = 0; i < ShareDataGetPackLength(); i++) {
            if(ShareDataGetPackFileName(i) == NULL) {
                VBArrayVectorAddBack(_sharePackRoot, NULL);
            } else {
                VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), ShareDataGetPackFileName(i));
                //printf("%s\n",_str->data);
                FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
                VBStringFree(&_str);
                
                fseek(_jSONFile, 0, SEEK_END);
                size_t _len = ftell(_jSONFile);
                fseek(_jSONFile, 0, SEEK_SET);
                
                char* _jSONData = (char*)calloc(1, _len + 1);
                fread(_jSONData, 1, _len, _jSONFile);
                
                fclose(_jSONFile);
                
                cJSON* _packJSON = cJSON_Parse(_jSONData);
                if(_packJSON == NULL)
                    printf("Error before: [%s]\n",cJSON_GetErrorPtr());
                
                free(_jSONData);
                VBArrayVectorAddBack(_sharePackRoot, _packJSON);
            }
        }
    }
    return _sharePackRoot;
}

VBObjectFile2D* ShareDataGetTitleObjFile() {
    if(_shareTitleObj == NULL) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "title_ui.obj");
        _shareTitleObj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
        VBStringFree(&_str);
    }
    return _shareTitleObj;
}

const char* ShareDataGetLoadingLibraryName() {
    return "_dynamic/dyMom_title_loading";
}

VBTexture* ShareDataGetTitleTexture() {
    if(_shareTitleTexture == NULL) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "title_ui.png");
        _shareTitleTexture = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
        VBStringFree(&_str);
    }
    return _shareTitleTexture;
}

VBModel* ShareDataGetLoadingModel() {
    if(_shareLoadingModel == NULL) {
        VBString* _str = VBStringInitWithCString(VBStringAlloc(), ShareDataGetLoadingLibraryName());
        _shareLoadingModel = new VBModel(ShareDataGetTitleObjFile(), VBObjectFile2DGetLibraryNameIDByName(ShareDataGetTitleObjFile(), _str), ShareDataGetTitleTexture(), true);
        VBStringFree(&_str);
    }
    return _shareLoadingModel;
}

Root* ShareDataGetRoot() {
    if(_shareRoot == NULL) {
        pid = 0;
        sid = 0;
        _shareRoot = new Root();
    }
    return _shareRoot;
}

void ShareDataFree() {
    if(_shareTitleObj)
        VBObjectFile2DFree(&_shareTitleObj);
    if(_shareTitleTexture)
        VBTextureFree(&_shareTitleTexture);
    if(_shareLoadingModel) {
        delete _shareLoadingModel;
        _shareLoadingModel = NULL;
    }
    if(_shareRoot) {
        delete _shareRoot;
        _shareRoot = NULL;
    }
    if(_shareJSON) {
        ShareDataSave();
        cJSON_Delete(_shareJSON);
        _shareJSON = NULL;
    }
    if(_sharePackRoot) {
        ShareDataPackDataSave();
        while(VBArrayVectorGetLength(_sharePackRoot)) {
            cJSON* _packJSON = (cJSON*)VBArrayVectorRemoveAt(_sharePackRoot, 0);
            if(_packJSON)
                cJSON_Delete(_packJSON);
        }
        VBArrayVectorFree(&_sharePackRoot);
    }
    if(_shareStageRoot) {
        while(VBArrayVectorGetLength(_shareStageRoot)) {
            VBArrayVector* _pack = (VBArrayVector*)VBArrayVectorRemoveBack(_shareStageRoot);
            if(_pack) {
                while(VBArrayVectorGetLength(_pack)) {
                    cJSON* _stage = (cJSON*)VBArrayVectorRemoveBack(_pack);
                    if(_stage)
                        cJSON_Delete(_stage);
                }
                VBArrayVectorFree(&_pack);
            }
        }
        VBArrayVectorFree(&_shareStageRoot);
    }
    if(_shareResJSON)
        cJSON_Delete(_shareResJSON);
    if(_shareTempJSON)
        cJSON_Delete(_shareTempJSON);
}

cJSON* ShareDataGetJSON() {
    if(_shareJSON == NULL) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "data.json");
        FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
        VBStringFree(&_str);
        
        fseek(_jSONFile, 0, SEEK_END);
        size_t _len = ftell(_jSONFile);
        fseek(_jSONFile, 0, SEEK_SET);
        
        char* _jSONData = (char*)calloc(1, _len + 1);
        fread(_jSONData, 1, _len, _jSONFile);
        
        fclose(_jSONFile);
        
        _shareJSON = cJSON_Parse(_jSONData);
        if(_shareJSON == NULL)
            printf("Error before: [%s]\n",cJSON_GetErrorPtr());
        
        free(_jSONData);
    }
    return _shareJSON;
}

int ShareDataGetPackLength() {
    cJSON* _json = cJSON_GetObjectItem(ShareDataGetJSON(), "pack");
    return cJSON_GetArraySize(_json);
}

char* ShareDataGetPackLibraryName(int _idx) {
    cJSON* _json = cJSON_GetObjectItem(ShareDataGetJSON(), "pack");
    _json = cJSON_GetArrayItem(_json, _idx);
    if(_json == NULL)
        return NULL;
    _json = cJSON_GetObjectItem(_json, "libName");
    if(_json == NULL)
        return NULL;
    return _json->valuestring;
}

void ShareDataSave() {
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "data.json");
    FILE* _jSONFile = fopen(VBStringGetCString(_str), "w");
    VBStringFree(&_str);
    
    char* _json_str = cJSON_Print(ShareDataGetJSON());
    fwrite(_json_str, 1, strlen(_json_str), _jSONFile);
    free(_json_str);
    
    fclose(_jSONFile);
}

/*
 * for shop
 */

cJSON* ShareDataGetInApp() {
    if(_shareInAppJSON == NULL) {
        VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "inapp.json");
        FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
        VBStringFree(&_str);
        
        fseek(_jSONFile, 0, SEEK_END);
        size_t _len = ftell(_jSONFile);
        fseek(_jSONFile, 0, SEEK_SET);
        
        char* _jSONData = (char*)calloc(1, _len + 1);
        fread(_jSONData, 1, _len, _jSONFile);
        
        fclose(_jSONFile);
        
        _shareInAppJSON = cJSON_Parse(_jSONData);
        if(_shareInAppJSON == NULL) {
            printf("Error before: [%s]\n",cJSON_GetErrorPtr());
            return NULL;
        }
        
        free(_jSONData);
    }
    return _shareInAppJSON;
}



