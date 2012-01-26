#include "PackSelect.h"
#include "ShareData.h"
#include "PackThumb.h"
#include "SubMenu.h"

PackSelect::PackSelect(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex,
                       int _totalIdx, SubMenu* _subMenu) : Pages(_obj, _tex, _totalIdx, 60.0, 600.0, -25, 357, 240-85, -280) {
    packs = VBArrayVectorInit(VBArrayVectorAlloc());
    for(int i = 0; i < ShareDataGetPackLength(); i++) {
        PackThumb* _pack = new PackThumb(obj, tex, _fontObj, _fontTex, i);
        ((CCSprite*)_pack)->setPosition(CCPointMake(i * pageTh, 0));
        VBArrayVectorAddBack(packs, _pack);
        _pack->is_use_animation = false;
        
        slideM->addChild(_pack);
    }
    touchM = NULL;
    touchMd = NULL;
    subMenu = _subMenu;
}

PackSelect::~PackSelect() {
    while(VBArrayVectorGetLength(packs)) {
        PackThumb* _pack = (PackThumb*)VBArrayVectorRemoveAt(packs, 0);
        slideM->removeChild(_pack, false);
        delete _pack;
    }
    VBArrayVectorFree(&packs);
}

void PackSelect::Reset() {
    for(int i = 0; i < VBArrayVectorGetLength(packs); i++) {
        PackThumb* _pack = (PackThumb*)VBArrayVectorGetDataAt(packs, i);
        _pack->Reset();
    }
}

void PackSelect::GoPage(int _idx, void (*_pageFunc)(void* _pageFuncRef), void* _pageFuncRef) {
    Pages::GoPage(_idx, _pageFunc, _pageFuncRef);
    if(_idx != -1) {
        history* _preH = ShareDataGetRoot()->GetLastHistory();
        int _hi = 0;
        if(_preH->args[_hi] == PopupTypeClear)
            _hi += 3;
        else
            _hi++;
        _hi++;
        if(_preH->args[_hi] != SubMenuTypePackSelect)
            return;
        _hi++;
        if(_hi < _preH->count)
            _preH->args[_hi] = _idx;
    }
}

void PackSelect::touchBegin(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    Pages::touchBegin(_touch, _location);
    if(touchM == NULL) {
        for(int i = 0; i < VBArrayVectorGetLength(packs); i++) {
            VBModel* _pack = (VBModel*)VBArrayVectorGetDataAt(packs, i);
            if(_pack->checkCollisionWithButton(_location)) {
                selectedIdx = i;
                touchM = _touch;
                _pack->is_use_animation = false;
                _pack->color.r = 0x88+0x44;
                _pack->color.g = 0x88+0x44;
                _pack->color.b = 0x88+0x44;
                touchMd = _pack;
                break;
            }
        }
    }
}

void PackSelect::touchMove(CCTouch* _touch, CCPoint _location) {
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

void PackSelect::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    if(idx < 0)
        return;
    if(touchM == _touch) {
        touchM = NULL;
        touchSlide = NULL;
        touchMd->color.r = 0xFF;
        touchMd->color.g = 0xFF;
        touchMd->color.b = 0xFF;
        touchMd = NULL;
        _setpid(selectedIdx);
        if(ShareDataGetHaveStage(selectedIdx)) {
            int _lastLockedStage = 0;
            for(int i = 0; i < ShareDataGetStageLength(selectedIdx); i++) {
                if(ShareDataGetStageLockAt(selectedIdx, i)) {
                    _lastLockedStage = i;
                    break;
                }
            }
            ShareDataGetRoot()->ChangePage(6, LoadingTypeNone, PopupTypeNone, RootPageTypeSubMenu, SubMenuTypeStageSelect, selectedIdx, _lastLockedStage / 18);
        }
    } else {
        Pages::touchEndAndCancel(_touch, _location);
    }
}
