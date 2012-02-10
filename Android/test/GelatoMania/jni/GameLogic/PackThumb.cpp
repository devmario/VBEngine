#include "PackThumb.h"
#include "ShareData.h"
#include "PlatformFunctions.h"

PackThumb::PackThumb(VBObjectFile2D* _obj, VBTexture* _tex, int _packIdx) : VBModel() {
    packIdx = _packIdx;
    
    if(ShareDataGetPackLibraryName(packIdx)) {
        VBString* _str;
        VBObjectFile2DLibraryNameID* _library_name_id;
        LIBNAMEFIND(_library_name_id, _obj, ShareDataGetPackLibraryName(packIdx), _str);
        
        pack = new VBModel(_obj, _library_name_id, _tex, true);
        pack->stop();
        
        ((CCSprite*)this)->addChild((CCSprite*)pack);
        
        
        
        if(ShareDataGetStageLength(packIdx)) {
            VBImage* img;
            if(packIdx == 1)
                img = PlatformGetTextImageWithSizeDetail("1.波光粼粼的冰霜", "ArialRoundedMTBold", 55, 512, 64, "fffcf0ff", "000000FF", VBVector2DCreate(3, 3), 0);
            if(packIdx == 2)
                img = PlatformGetTextImageWithSizeDetail("2.Delightful Gelato", "ArialRoundedMTBold", 55, 512, 64, "fffcf0ff", "000000FF", VBVector2DCreate(3, 3), 0);
            if(packIdx == 3)
                img = PlatformGetTextImageWithSizeDetail("3.반짝거리는 아이스크림", "ArialRoundedMTBold", 55, 512, 64, "fffcf0ff", "000000FF", VBVector2DCreate(3, 3), 0);
            if(packIdx == 4)
                img = PlatformGetTextImageWithSizeDetail("4.キラキラアイスクリーム", "ArialRoundedMTBold", 55, 512, 64, "fffcf0ff", "000000FF", VBVector2DCreate(3, 3), 0);
            if(packIdx == 5)
                img = PlatformGetTextImageWithSizeDetail("5.Crème de glace pétillant", "ArialRoundedMTBold", 55, 512, 64, "fffcf0ff", "000000FF", VBVector2DCreate(3, 3), 0);
            texTitle = VBTextureInitAndLoadWithImage(VBTextureAlloc(), img);
            modelTitle = new VBModel(texTitle);
            modelTitle->setScale(0.5);
            modelTitle->setPosition(CCPoint(50, -25));
            pack->addChild(modelTitle);
            VBImageFree(&img);
            
            img = PlatformGetTextImageWithSizeDetail("24 / 36", "ArialRoundedMTBold", 50, 256, 64, "413424FF", "000000FF", VBVector2DCreate(1, 1), -1);
            texClear = VBTextureInitAndLoadWithImage(VBTextureAlloc(), img);
            modelClear = new VBModel(texClear);
            modelClear->setScale(0.5);
            modelClear->setPosition(CCPoint(220, -73-15));
            pack->addChild(modelClear);
            VBImageFree(&img);
            
            img = PlatformGetTextImageWithSizeDetail("86 %", "ArialRoundedMTBold", 50, 128, 64, "413424FF", "000000FF", VBVector2DCreate(1, 1), -1);
            texStar = VBTextureInitAndLoadWithImage(VBTextureAlloc(), img);
            modelStar = new VBModel(texStar);
            modelStar->setScale(0.5);
            modelStar->setPosition(CCPoint(220, -106-16));
            pack->addChild(modelStar);
            VBImageFree(&img);
            
            if(packIdx == 1)
                img = PlatformGetTextImageWithSizeDetail("01h 04m 56s", "ArialRoundedMTBold", 32, 207, 64, "413424FF", "000000FF", VBVector2DCreate(1, 1), 0);
            else
                img = PlatformGetTextImageWithSizeDetail("01시 04분 56초", "ArialRoundedMTBold", 32, 207, 64, "413424FF", "000000FF", VBVector2DCreate(1, 1), 0);
            texTime = VBTextureInitAndLoadWithImage(VBTextureAlloc(), img);
            modelTime = new VBModel(texTime);
            modelTime->setScale(0.5);
            modelTime->setPosition(CCPoint(180, -147-16));
            pack->addChild(modelTime);
            VBImageFree(&img);
        } else {
            VBImage* img = PlatformGetTextImageWithSizeDetail("연습하기", "ArialRoundedMTBold", 55, 512, 64, "fffcf0ff", "000000FF", VBVector2DCreate(3, 3), 0);
            texTitle = VBTextureInitAndLoadWithImage(VBTextureAlloc(), img);
            modelTitle = new VBModel(texTitle);
            modelTitle->setScale(0.5);
            modelTitle->setPosition(CCPoint(50, -25));
            pack->addChild(modelTitle);
            VBImageFree(&img);
            
            texClear = NULL;
            modelClear = NULL;
            
            texStar = NULL;
            modelStar = NULL;
            
            texTime = NULL;
            modelTime = NULL;
        }
            
        Reset();
    }
}

PackThumb::~PackThumb() {
    VBTextureFree(&texTitle);
    pack->removeChild(modelTitle, false);
    delete modelTitle;
    
    if(modelClear) {
        VBTextureFree(&texClear);
        pack->removeChild(modelClear, false);
        delete modelClear;
    }
    
    if(modelStar){
        VBTextureFree(&texStar);
        pack->removeChild(modelStar, false);
        delete modelStar;
    }
    
    if(modelTime){
        VBTextureFree(&texTime);
        pack->removeChild(modelTime, false);
        delete modelTime;
    }
    
    this->removeChild(pack, false);
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