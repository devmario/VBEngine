#include "PackThumb.h"
#include "ShareData.h"

PackThumb::PackThumb(VBObjectFile2D* _obj, VBTexture* _tex, VBObjectFile2D* _fontObj, VBTexture* _fontTex, int _packIdx) : VBModel() {
    packIdx = _packIdx;
    
    if(ShareDataGetPackLibraryName(packIdx)) {
        VBString* _str;
        VBObjectFile2DLibraryNameID* _library_name_id;
        LIBNAMEFIND(_library_name_id, _obj, ShareDataGetPackLibraryName(packIdx), _str);
        
        pack = new VBModel(_obj, _library_name_id, _tex, true);
        
        ((CCSprite*)this)->addChild((CCSprite*)pack);
        
        if(ShareDataGetStageLength(packIdx)) {
            scoreText = new NumberText(_fontObj, _fontTex, (char*)"dynamic/dy_font_score", 0, -2);
            ((CCSprite*)scoreText)->setPosition(CCPointMake(243, -130));
            ((CCSprite*)this)->addChild((CCSprite*)scoreText);
            
            starText = new NumberText(_fontObj, _fontTex, (char*)"dynamic/dy_font_starscore", -1, -2);
            ((CCSprite*)starText)->setPosition(CCPointMake(253, -174));
            ((CCSprite*)this)->addChild((CCSprite*)starText);
        } else {
            scoreText = NULL;
            starText = NULL;
        }
            
        Reset();
    }
}

PackThumb::~PackThumb() {
    if(starText) {
        this->removeChild(starText, false);
        delete starText;
    }
    if(scoreText) {
        this->removeChild(scoreText, false);
        delete scoreText;
    }
    this->removeChild(pack, false);
    delete pack;
}

void PackThumb::Reset() {
    if(scoreText) {
        int packScore = 0;
        for(int i = 0; i < ShareDataGetStageLength(packIdx); i++) {
            packScore += ShareDataGetStageScoreAt(packIdx, i);
        }
        scoreText->SetNumber(packScore);
    }
    
    if(starText) {
        int starScore = 0;
        for(int i = 0; i < ShareDataGetStageLength(packIdx); i++) {
            starScore += ShareDataGetStageStarAt(packIdx, i);
        }
        starText->SetNumber(starScore);
    }
}