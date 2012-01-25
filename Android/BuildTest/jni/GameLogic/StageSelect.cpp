#include "StageSelect.h"
#include "ShareData.h"
#include "StageThumb.h"

StageSelect::StageSelect(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex, 
                         int _totalIdx) : Pages(_obj, _tex, _totalIdx, 30, 600.0, -40, 480, 240, -280 + 8) {
    fontObj = _fontObj;
    fontTex = _fontTex;
    
    VBString* _str = VBStringInitWithCString(VBStringAlloc(), "_dynamic/dy_menu_stage0_bgStage");
    VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByName(obj, _str);
    VBStringFree(&_str);
    
    bg[0] = new VBModel(obj, _library_name_id, tex, true);
    ((CCSprite*)bg[0])->setPosition(CCPointMake(-30, 30));
    ((CCSprite*)slideM)->addChild((CCSprite*)bg[0]);
    bg[1] = new VBModel(obj, _library_name_id, tex, true);
    ((CCSprite*)bg[1])->setPosition(CCPointMake(-30 + pageTh, 30));
    ((CCSprite*)slideM)->addChild((CCSprite*)bg[1]);
    
    stages = VBArrayVectorInit(VBArrayVectorAlloc());
    
    packIdx = -1;
    touchM = NULL;
    touchMd = NULL;
}

StageSelect::~StageSelect() {
    slideM->removeChild(bg[0], false);
    slideM->removeChild(bg[1], false);
    delete bg[0];
    delete bg[1];
    while(VBArrayVectorGetLength(stages)) {
        StageThumb* _stage = (StageThumb*)VBArrayVectorRemoveAt(stages, 0);
        slideM->removeChild(_stage, false);
        delete _stage;
    }
    VBArrayVectorFree(&stages);
}

void StageSelect::SetPack(int _idx) {
    if(packIdx != _idx) {
        packIdx = _idx;
        
        while(VBArrayVectorGetLength(stages)) {
            StageThumb* _stage = (StageThumb*)VBArrayVectorRemoveAt(stages, 0);
            slideM->removeChild(_stage, false);
            delete _stage;
        }
        
        int xnum = 0;
        int ynum = 0;
        int pnum = 0;
        for(int i = 0; i < ShareDataGetStageLength(packIdx); i++) {
            StageThumb* _stage = new StageThumb(obj, tex, fontObj, fontTex, _idx, i);
            ((CCSprite*)_stage)->setPosition(CCPointMake(xnum * 70 + pnum * pageTh, -ynum * 70));
            VBArrayVectorAddBack(stages, _stage);
            
            ((CCSprite*)slideM)->addChild((CCSprite*)_stage);
            xnum++;
            if(xnum >= 6) {
                xnum = 0;
                ynum++;
                if(ynum >= 3) {
                    ynum = 0;
                    pnum++;
                }
            }
        }
        int thumbFrame = (packIdx - 1) * 2;
        if(thumbFrame > thumb->frame->total_frame - 2) {
            thumbFrame = thumb->frame->total_frame - 2;
        }
        thumb->gotoAndStop(thumbFrame + idx);
    }
}

void StageSelect::GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef) {
    Pages::GoPage(_idx, _pageFunc, _pageFuncRef);
    if(idx >= 0 && totalIdx > idx) {
        int thumbFrame = (packIdx - 1) * 2;
        if(thumbFrame > thumb->frame->total_frame - 2) {
            thumbFrame = thumb->frame->total_frame - 2;
        }
        thumb->gotoAndStop(thumbFrame + idx);
    }
}

void StageSelect::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    Pages::touchBegin(_touch, _location);
    if(touchM == NULL) {
        for(int i = 0; i < VBArrayVectorGetLength(stages); i++) {
            VBModel* _stage = (VBModel*)VBArrayVectorGetDataAt(stages, i);
            if(_stage->checkCollisionWithButton(_location)) {
                touchM = _touch;
                _stage->is_use_animation = false;
                _stage->color.r = 0x88+0x44;
                _stage->color.g = 0x88+0x44;
                _stage->color.b = 0x88+0x44;
                touchMd = _stage;
                break;
            }
        }
    }
}

void StageSelect::touchMove(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    Pages::touchMove(_touch, _location);
    if(touchM == _touch) {
        touchM = NULL;
        touchMd->color.r = 0xFF;
        touchMd->color.g = 0xFF;
        touchMd->color.b = 0xFF;
        touchMd = NULL;
    }
}

void StageSelect::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchM == _touch) {
        for(int i = 0; i < VBArrayVectorGetLength(stages); i++) {
            if(touchMd == VBArrayVectorGetDataAt(stages, i))
                _setsid(i);
        }
        touchM = NULL;
        touchSlide = NULL;
        touchMd->color.r = 0xFF;
        touchMd->color.g = 0xFF;
        touchMd->color.b = 0xFF;
        touchMd = NULL;
        ShareDataGetRoot()->ShowLoading(GameMainPage);
    } else {
        Pages::touchEndAndCancel(_touch, _location);
    }
}


