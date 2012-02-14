#include "StageThumb.h"
#include "ShareData.h"
#include "Language.h"

StageThumb::StageThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx, int _stageIdx) : VBModel() {
    obj = _obj;
    tex = _tex;
    
    stage = NULL;
    
    textStage = textComplete = textTime = NULL;
    
    locked = true;
    
    Reset(_packIdx, _stageIdx);
}

void StageThumb::CleanThumb() {
    if(textStage) {
        removeChild(textStage, false);
        delete textStage;
        textStage = NULL;
    }
    
    if(textComplete) {
        removeChild(textComplete, false);
        delete textComplete;
        textComplete = NULL;
    }
    
    if(textTime) {
        removeChild(textTime, false);
        delete textTime;
        textTime = NULL;
    }
    
    if(stage) {
        removeChild(stage, false);
        delete stage;
        stage = NULL;
    }
}

StageThumb::~StageThumb() {
    CleanThumb();
}

void StageThumb::Reset(int _packIdx, int _stageIdx) {
    CleanThumb();
    
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    char buf[0xFF] = {'\0'};
    sprintf(buf, "stage%02d", _packIdx);
    LIBNAMEFIND(_library_name_id, obj, buf, _str);
    stage = new VBModel(obj, _library_name_id, tex, true);
    stage->stop();
    addChild(stage);
    
    packIdx = _packIdx;
    stageIdx = _stageIdx;
    cJSON* json = ShareDataGetStageDataJSONAt(packIdx, stageIdx);
    locked = cJSON_IsTrue(cJSON_GetObjectItem(json, "lock"));
    int complete = cJSON_GetObjectItem(json, "complete")->valueint;
    int time_val = cJSON_GetObjectItem(json, "time")->valueint;
    
    if(locked) {
        stage->gotoAndStop(0);
    } else {
        if(time_val == 0) {
            stage->gotoAndStop(1);
        } else {
            if(complete == 100) {
                stage->gotoAndStop(3);
            } else {
                stage->gotoAndStop(2);
            }
        }
    }
    if(locked == false) {
        textStage = new Text();
        addChild(textStage);
        char buf[0xF] = {'\0',};
        sprintf(buf, "%i", _stageIdx + 1);
        textStage->SetText(buf, Language::shareLanguage()->GetFontName("type0"), 32, 32, 32, "FFFFFFFF", "000000FF", VBVector2DCreate(-1, -1), 0, false);
        textStage->setPosition(CCPoint(-16, 16));
        
        if(complete != 100 && complete != 0) {
            textComplete = new Text();
            addChild(textComplete);
            memset(buf, 0, 0xF);
            sprintf(buf, "%i%%", complete);
            textComplete->SetText(buf, Language::shareLanguage()->GetFontName("type0"), 12, 40, 32, "ffde00FF", "000000FF", VBVector2DCreate(-1, -1), 1, false);
            textComplete->setPosition(CCPoint(-15, 32));
        }
        
        if(time_val != 0) {
            textTime = new Text();
            addChild(textTime);
            memset(buf, 0, 0xF);
            
            struct tm *tm_ptr;
            time_t _t = time_val;
            tm_ptr = localtime(&_t);
            
            sprintf(buf, "%02d:%02d:%02d", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
            textTime->SetText(buf, Language::shareLanguage()->GetFontName("type0"), 18, 85/2, 32, "FFFFFFFF", "000000FF", VBVector2DCreate(-1, -1), 1, false);
            textTime->setPosition(CCPoint(-21, -11));
        }
    }
}

