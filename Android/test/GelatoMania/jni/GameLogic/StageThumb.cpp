#include "StageThumb.h"
#include "ShareData.h"

StageThumb::StageThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx, int _stageIdx) : VBModel() {
    obj = _obj;
    tex = _tex;
    
    stage = NULL;
    
    Reset(_packIdx, _stageIdx);
}

void StageThumb::CleanThumb() {
    if(stage) {
        removeChild(stage, false);
        delete stage;
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
    addChild(stage);
    
    packIdx = _packIdx;
    stageIdx = _stageIdx;
    bool locked = ShareDataGetStageLockAt(packIdx, stageIdx);
    stage->gotoAndStop(locked ? 0 : 1);
    
    if(locked == false) {
//        int starScore = ShareDataGetStageStarAt(packIdx, stageIdx);
//        bool haveStar = starScore > 0 && starScore <= 3;
//        
//        bool isOne = stageIdx + 1 < 10;
//        label = new NumberText(fontObj, fontTex, (char*)(isOne ? "dynamic/dy_font_stageOne" : "dynamic/dy_font_stageTen"), 0, -4);
//        this->addChild(label);
//        label->setPosition(CCPointMake(isOne ? 35 : 31, haveStar? -13 : -18));
//        label->SetNumber(stageIdx + 1);
//        
//        if(haveStar) {
//            VBString* _str;
//            VBObjectFile2DLibraryNameID* _library_name_id;
//            LIBNAMEFIND(_library_name_id, obj, "_dynamic/dy_menu_stage0_star", _str);
//            star = new VBModel(obj, _library_name_id, tex, true);
//            star->gotoAndStop(starScore - 1);
//            star->setPosition(CCPointMake(35, -45));
//            this->addChild(star);
//        }
    }
}

