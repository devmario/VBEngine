#include "StageThumb.h"
#include "ShareData.h"

StageThumb::StageThumb(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex, int _packIdx, int _stageIdx) : VBModel() {
    label = NULL;
    star = NULL;
    
    obj = _obj;
    tex = _tex;
    fontObj = _fontObj;
    fontTex = _fontTex;
    
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    LIBNAMEFIND(_library_name_id, _obj, "_dynamic/dy_menu_stage0_stage", _str);
    
    stage = new VBModel(obj, _library_name_id, tex, true);
    
    ((CCSprite*)this)->addChild((CCSprite*)stage);
    
    Reset(_packIdx, _stageIdx);
}

void StageThumb::CleanThumb() {
    if(label) {
        this->removeChild(label, false);
        delete label;
        label = NULL;
    }
    
    if(star) {
        this->removeChild(star, false);
        delete star;
        star = NULL;
    }
}

StageThumb::~StageThumb() {
    CleanThumb();
    this->removeChild(stage, false);
    delete stage;
}

void StageThumb::Reset(int _packIdx, int _stageIdx) {
    packIdx = _packIdx;
    stageIdx = _stageIdx;
    bool locked = ShareDataGetStageLockAt(packIdx, stageIdx);
    stage->gotoAndStop((packIdx-1) * 2 + (locked ? 0 : 1));
    CleanThumb();
    if(locked == false) {
        int starScore = ShareDataGetStageStarAt(packIdx, stageIdx);
        bool haveStar = starScore > 0 && starScore <= 3;
        
        bool isOne = stageIdx + 1 < 10;
        label = new NumberText(fontObj, fontTex, (char*)(isOne ? "dynamic/dy_font_stageOne" : "dynamic/dy_font_stageTen"), 0, -4);
        this->addChild(label);
        label->setPosition(CCPointMake(isOne ? 35 : 31, haveStar? -13 : -18));
        label->SetNumber(stageIdx + 1);
        
        if(haveStar) {
            VBString* _str;
            VBObjectFile2DLibraryNameID* _library_name_id;
            LIBNAMEFIND(_library_name_id, obj, "_dynamic/dy_menu_stage0_star", _str);
            star = new VBModel(obj, _library_name_id, tex, true);
            star->gotoAndStop(starScore - 1);
            star->setPosition(CCPointMake(35, -45));
            this->addChild(star);
        }
    }
}

