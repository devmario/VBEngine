#include "PackThumb.h"
#include "ShareData.h"
#include "PlatformFunctions.h"
#include "Language.h"

PackThumb::PackThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx) : VBModel() {
    packIdx = _packIdx;
    
    if(ShareDataGetPackLibraryName(packIdx)) {
        VBString* _str;
        VBObjectFile2DLibraryNameID* _library_name_id;
        LIBNAMEFIND(_library_name_id, _obj, ShareDataGetPackLibraryName(packIdx), _str);
        
        pack = new VBModel(_obj, _library_name_id, _tex, true);
        pack->stop();
        
        ((CCSprite*)this)->addChild((CCSprite*)pack);
        
        textTitle = new Text();
        textClear = new Text();
        textStar = new Text();
        textTime = new Text();
        
        Language* l = Language::shareLanguage();
        
        textTitle->SetText(l->GetString("si", 2, "packTitle", _packIdx), l->GetFontName("type0"), 25, 256, 32, "fffcf0ff", "000000FF", VBVector2DCreate(-1, -1), 0);
        
        if(ShareDataGetStageLength(packIdx)) {
            
            textClear->SetText("24 / 36", "ArialRoundedMTBold", 20, 80, 32, "413424FF", "FFFFFFFF", VBVector2DCreate(1, 1), -1);
            textStar->SetText("86 %", "ArialRoundedMTBold", 20, 80, 32, "413424FF", "FFFFFFFF", VBVector2DCreate(1, 1), -1);
            
            char buf[0xFF] = {'\0',};
            sprintf(buf, "%02d%s %02d%s %02d%s", 1, l->GetString("s", 1, "time"), 4, l->GetString("s", 1, "min"), 5, l->GetString("s", 1, "sec"));
            textTime->SetText(buf, l->GetFontName("type0"), 15, 128-20, 25, "413424FF", "FFFFFFFF", VBVector2DCreate(1, 1), 0);
        }
        
        textTitle->setPosition(CCPoint(50, -25-2));
        textClear->setPosition(CCPoint(220, -73-15));
        textStar->setPosition(CCPoint(220, -106-16));
        textTime->setPosition(CCPoint(190, -147-16 - 5));
        
        addChild(textTitle);
        addChild(textClear);
        addChild(textStar);
        addChild(textTime);
        
        Reset();
    }
}

PackThumb::~PackThumb() {
    removeChild(textTitle, false);
    delete textTitle;
    
    removeChild(textClear, false);
    delete textClear;
    
    removeChild(textStar, false);
    delete textStar;
    
    removeChild(textTime, false);
    delete textTime;
    
    removeChild(pack, false);
    delete pack;
}

void PackThumb::Reset() {
    if(1) {
        int packScore = 0;
        for(int i = 0; i < ShareDataGetStageLength(packIdx); i++) {
            packScore += ShareDataGetStageScoreAt(packIdx, i);
        }
    }
    
    if(1) {
        int starScore = 0;
        for(int i = 0; i < ShareDataGetStageLength(packIdx); i++) {
            starScore += ShareDataGetStageStarAt(packIdx, i);
        }
    }
}