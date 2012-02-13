#include "StageSelect.h"
#include "ShareData.h"
#include "StageThumb.h"
#include "SubMenu.h"

StageSelect::StageSelect(VBObjectFile2D* _obj, VBTexture* _tex, 
                         int _totalIdx) : Pages(_obj, _tex, _totalIdx, 30 - 240, 240, -40, 480, 0, -280 + 8) {
    VBString* _str;
    VBObjectFile2DLibraryNameID* _library_name_id;
    OBJLOAD(objStage, "stage_select.obj", _str);
    TEXLOAD(texStage, "stage_select.png", _str);
    
    LIBNAMEFIND(_library_name_id, objStage, "stageRope", _str);
    
    bg[0] = new VBModel(objStage, _library_name_id, texStage, true);
    ((CCSprite*)bg[0])->setPosition(CCPointMake(40, -65));
    ((CCSprite*)slideM)->addChild((CCSprite*)bg[0]);
    
    bg[1] = new VBModel(objStage, _library_name_id, texStage, true);
    ((CCSprite*)bg[1])->setPosition(CCPointMake(40 + pageTh, -65));
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
        StageThumb* _stage = (StageThumb*)VBArrayVectorRemoveBack(stages);
        slideM->removeChild(_stage, false);
        delete _stage;
    }
    VBArrayVectorFree(&stages);
    
    VBObjectFile2DFree(&objStage);
    VBTextureFree(&texStage);
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
            StageThumb* _stage = new StageThumb(objStage, texStage, _idx, i);
            ((CCSprite*)_stage)->setPosition(CCPointMake(40 + xnum * 70 + pnum * pageTh, -20 -ynum * 70));
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
    }
}

void StageSelect::GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef) {
    Pages::GoPage(_idx, _pageFunc, _pageFuncRef);
    if(_idx != -1) {
        history* _preH = ShareDataGetRoot()->GetLastHistory();
        int _hi = 0;
        if(_preH->args[_hi] == PopupTypeClear)
            _hi += 3;
        else
            _hi++;
        _hi++;
        if(_preH->args[_hi] != SubMenuTypeStageSelect)
            return;
        _hi += 2;
        if(_hi < _preH->count)
            _preH->args[_hi] = _idx;
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
                startLocation = _location;
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
        if(VBVector2DLength(VBVector2DSubtract(VBVector2DCreate(_location.x, _location.y), VBVector2DCreate(startLocation.x, startLocation.y))) > 2.0) {
            touchM = NULL;
            touchMd->color.r = 0xFF;
            touchMd->color.g = 0xFF;
            touchMd->color.b = 0xFF;
            touchMd = NULL;
        }
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
        ShareDataGetRoot()->ChangePage(5, LoadingTypeFull, PopupTypeNone, RootPageTypeGameMain, _getpid(), _getsid());
    } else {
        Pages::touchEndAndCancel(_touch, _location);
    }
}


