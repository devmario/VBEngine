#include "Text.h"
#include "PlatformFunctions.h"

Text::Text() : VBModel() {
    ttex = VBTextureInit(VBTextureAlloc());
    if(CCDirector::sharedDirector()->isRetinaDisplay()) {
        setScale(0.5);
    }
    shift = VBVector2DZero();
    tpos = CCPoint(0,0);
}

Text::~Text() {
    VBTextureFree(&ttex);
}

void Text::setPosition(cocos2d::CCPoint pos) {
    tpos = pos;
    VBModel::setPosition(CCPoint(tpos.x - shift.x / CCDirector::sharedDirector()->getContentScaleFactor(), tpos.y + shift.y / CCDirector::sharedDirector()->getContentScaleFactor()));
}

void Text::SetText(const char* _txt, const char* _fontName, float _text_size, int _width, int _height, const char* _colorCode, const char* _shadowColorCode, VBVector2D _shadowOffset, int align, int _is_line) {
    float scale = CCDirector::sharedDirector()->isRetinaDisplay() ? 2.0 : 1.0;
    VBImage* img = PlatformGetTextImageWithSizeDetail(_txt, _fontName, _text_size * scale, _width * scale, _height * scale, _colorCode, _shadowColorCode, VBVector2DMultiply(_shadowOffset, scale), align, _is_line);
    VBTextureUnload(ttex);
    VBTextureLoadImage(ttex, img);
    VBImageFree(&img);
    SetTexture(ttex);
    shift = VBVector2DCreate(ttex->shiftX, ttex->shiftY);
    setTextureRect( cocos2d::CCRectMake(((ttex->shiftX / ttex->width) * tex->getPixelsWide()) / CCDirector::sharedDirector()->getContentScaleFactor()
                                        ,((ttex->shiftY / ttex->height) * tex->getPixelsHigh()) / CCDirector::sharedDirector()->getContentScaleFactor()
                                        ,((1.0 - ((ttex->shiftX * 2) / ttex->width)) * tex->getPixelsWide()) / CCDirector::sharedDirector()->getContentScaleFactor()
                                        ,((1.0 - ((ttex->shiftY * 2) / ttex->height)) * tex->getPixelsHigh()) / CCDirector::sharedDirector()->getContentScaleFactor() ) );
    setPosition(tpos);
}
