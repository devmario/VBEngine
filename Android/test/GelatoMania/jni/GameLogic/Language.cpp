#include "Language.h" 
#include "VBEngine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PlatformFunctions.h"
#include <stdarg.h>

Language* _rootLang = NULL;

Language* Language::shareLanguage() {
    if(_rootLang == NULL)
        _rootLang = new Language();
    return _rootLang;
}

Language::Language() {
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "language.json");
    FILE* _jSONFile = fopen(VBStringGetCString(_str), "r");
    VBStringFree(&_str);
    
    fseek(_jSONFile, 0, SEEK_END);
    size_t _len = ftell(_jSONFile);
    fseek(_jSONFile, 0, SEEK_SET);
    
    char* _jSONData = (char*)calloc(1, _len + 1);
    fread(_jSONData, 1, _len, _jSONFile);
    
    fclose(_jSONFile);
    
    json = cJSON_Parse(_jSONData);
    if(json == NULL) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    
    free(_jSONData);
    
    _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), "font.json");
    _jSONFile = fopen(VBStringGetCString(_str), "r");
    VBStringFree(&_str);
    
    fseek(_jSONFile, 0, SEEK_END);
    _len = ftell(_jSONFile);
    fseek(_jSONFile, 0, SEEK_SET);
    
    _jSONData = (char*)calloc(1, _len + 1);
    fread(_jSONData, 1, _len, _jSONFile);
    
    fclose(_jSONFile);
    
    font_json = cJSON_Parse(_jSONData);
    if(font_json == NULL) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    
    free(_jSONData);
}

Language::~Language() {
    cJSON_Delete(json);
    cJSON_Delete(font_json);
}

const char* Language::GetString(const char* tk, int count, ...) {
    va_list ap; 
    int i;
    va_start(ap, count); 
    cJSON* js = cJSON_GetObjectItem(json, PlatformGetLanguage());
    if(js == NULL)
        js = cJSON_GetObjectItem(json, "default");
    for(i = 0; i < count; i++) {
        if(tk[i] == 'i') {
            int idx = va_arg(ap, int);
            js = cJSON_GetArrayItem(js, idx);
            if(js == NULL)
                return NULL;
        } else if(tk[i] == 's') {
            char* str = va_arg(ap, char*);
            js = cJSON_GetObjectItem(js, str);
            if(js == NULL)
                return NULL;
        }
    }
    
    va_end (ap); 
    
    return js->valuestring;
}

const char* Language::GetFontName(const char* type) {
    cJSON* js = cJSON_GetObjectItem(font_json, PlatformGetLanguage());
    if(js == NULL)
        js = cJSON_GetObjectItem(font_json, "default");
#ifdef __ANDROID__
    js = cJSON_GetObjectItem(js, "android");
#endif
#ifndef __ANDROID__
    js = cJSON_GetObjectItem(js, "ios");
#endif
    js = cJSON_GetObjectItem(js, type);
    if(js) {
        int f_len = cJSON_GetArraySize(js);
        for(int i = 0; i < f_len; i++) {
            cJSON* fjs = cJSON_GetArrayItem(js, i);
            if(fjs) {
                if(fjs->valuestring) {
                if(PlatformIsHaveFont(fjs->valuestring))
                    return fjs->valuestring;
                }
            }
        }
    }
    return NULL;
}
