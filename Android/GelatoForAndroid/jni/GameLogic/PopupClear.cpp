#include "PopupClear.h"
#include "ShareData.h"

#define FB_TW_X_HIDE -150
#define FB_TW_X_SHOW -50

#define FB_Y -200
#define TW_Y -244

PopupClear::PopupClear(VBObjectFile2D* _obj, VBTexture* _tex, VBModel* _topView, int _starScore, int _score, VBObjectFile2D* _fontObj, VBTexture* _fontTex) : Popup(_obj, _tex, _topView) {
    initedPopupClear = false;
    starScore = _starScore;
    score = _score;
    fontObj = _fontObj;
    fontTex = _fontTex;
    clearTween = Tweener();
}

PopupClear::~PopupClear() {
    if(fontObj)
        VBObjectFile2DFree(&fontObj);
    if(fontTex)
        VBTextureFree(&fontTex);
    if(scoreText) {
        popup->removeChild(scoreText, false);
        delete scoreText;
        scoreText = NULL;
    }
    
    if(fbBT) {
        top->removeChild(fbBT, false);
        delete fbBT;
        fbBT = NULL;
        fbM = NULL;
    }
    
    if(twBT) {
        top->removeChild(twBT, false);
        delete twBT;
        twBT = NULL;
        twM = NULL;
    }
    
    for(int i = 0; i < 3; i++) {
        star[i] = NULL;
        starSmall[i] = NULL;
        starBig[i] = NULL;
    }
    
    if(runfbParam) {
        clearTween.removeTween(runfbParam);
        runfbParam = NULL;
    }
    
    if(runtwParam) {
        clearTween.removeTween(runtwParam);
        runtwParam = NULL;
    }
}

void PopupClear::init() {
    Popup::init();
    if(initedPopupClear == false) {
        VBString* _str;
        VBObjectFile2DLibraryNameID* _name_id;
        
        if(fontObj == NULL) {
            OBJLOAD(fontObj, "fontGame.obj", _str);
        } else {
            fontObj = NULL;
        }
        if(fontTex == NULL) {
            TEXLOAD(fontTex, "fontGame.png", _str);
        } else {
            fontTex = NULL;
        }
        
        scoreText = new NumberText(fontObj, fontTex, (char*)"dynamic/dy_fontGame_score", 0, -2);
        popup->addChild(scoreText);
        scoreText->setPosition(CCPointMake(240, -138));
        
        numTouch = fbTouch = twTouch = NULL;
        
        runfbParam = runtwParam = runstarParam = NULL;
        
        twX = fbX = FB_TW_X_HIDE;
        
        LIBNAMEFIND(_name_id, objRes, "facebook", _str);
        fbBT = new VBModel(objRes, _name_id, texRes, true);
        fbM = fbBT->getVBModelByName((char*)"fbBT");
        fbBT->stop();
        top->addChild(fbBT);
        fbBT->setPosition(CCPointMake(fbX, FB_Y));
        
        LIBNAMEFIND(_name_id, objRes, "twitter", _str);
        twBT = new VBModel(objRes, _name_id, texRes, true);
        twM = twBT->getVBModelByName((char*)"twBT");
        twBT->stop();
        top->addChild(twBT);
        twBT->setPosition(CCPointMake(twX, TW_Y));
        
#define STARMAKER(star, starSmall, starBig, idx, str) \
str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s%i", "star", idx);\
star[idx] = popup->getVBModelByInstanceName((const char*)str->data);\
star[idx]->setIsPlayLoop(false);\
starSmall[idx] = star[idx]->getVBModelByInstanceName("small");\
starSmall[idx]->setIsPlayLoop(false);\
starBig[idx] = star[idx]->getVBModelByInstanceName("big");\
starBig[idx]->setIsPlayLoop(false);\
VBStringFree(&str)
        
        for(int i = 0; i < 3; i++) {
            STARMAKER(star, starSmall, starBig, i, _str);
        }
        
#undef STARMAKER
        
        initedPopupClear = true;
    }
}

void PopupClear::Update(float _deltaTime) {
    clearTween.step(elapseTime);
    if(fbBT)
        fbBT->setPosition(CCPointMake(fbX, FB_Y));
    if(twBT)
        twBT->setPosition(CCPointMake(twX, TW_Y));
    for(int i = 0; i < starScore; i++) {
        if(isRunStar[i] == false) {
            if(i < scoreCount) {
                if(isBig[i])
                    starBig[i]->play();
                else
                    starSmall[i]->play();
                isRunStar[i] = true;
            }
        }
    }
    numCountTime += _deltaTime * 1000;
    if(scoreText) {
        if(numCountTime > 1000)
            scoreText->SetNumber(score);
        else
            scoreText->SetNumber(numCount);
    }
    
    Popup::Update(_deltaTime);
}

void PopupClear::NumEnd() {
    numCount = score;
}

void PopupClear::Open(void (*_closeFunc)(void *), void *_closeFuncRef) {
    Popup::Open(_closeFunc, _closeFuncRef);
    
    if(runfbParam) {
        clearTween.removeTween(runfbParam);
        runfbParam = NULL;
    }
    
    if(runtwParam) {
        clearTween.removeTween(runtwParam);
        runtwParam = NULL;
    }
    
    if(runstarParam) {
        clearTween.removeTween(runstarParam);
        runstarParam = NULL;
    }
    
    if(runnumParam) {
        clearTween.removeTween(runnumParam);
        runnumParam = NULL;
    }
    
    fbParam = TweenerParam(1000 * 0.5, EXPO, EASE_OUT);
    runfbParam = &fbParam;
    fbParam.addProperty(&fbX, FB_TW_X_SHOW);
    clearTween.addTween(fbParam);
    
    twParam = TweenerParam(1000 * 0.5, EXPO, EASE_OUT, 1000 * 0.125);
    runtwParam = &twParam;
    twParam.addProperty(&twX, FB_TW_X_SHOW);
    clearTween.addTween(twParam);
    
    starParam = TweenerParam(1000 * 0.3, LINEAR, EASE_OUT, 1000 * 0.125);
    runstarParam = &starParam;
    scoreCount = 0;
    for(int i = 0; i < 3; i++) {
        isRunStar[i] = false;
        isBig[i] = false;
    }
    starParam.addProperty(&scoreCount, 3);
    clearTween.addTween(starParam);
    
    star[0]->gotoAndStop(0.0);
    star[1]->gotoAndStop(0.0);
    star[2]->gotoAndStop(0.0);
    for(int i = 0; i < starScore; i++) {
        isBig[i] = starScore > 2;
        star[i]->gotoAndStop(isBig[i] ? 2.0 : 1.0);
        starSmall[i]->gotoAndStop(0.0);
        starBig[i]->gotoAndStop(0.0);
    }
    
    numParam = TweenerParam(1000 * 1.0, EXPO, EASE_IN);
    runnumParam = &numParam;
    numCountTime = numCount = 0;
    numParam.addProperty(&numCount, score);
    clearTween.addTween(numParam);
}

void PopupClear::Close() {
    if(runfbParam) {
        clearTween.removeTween(runfbParam);
        runfbParam = NULL;
    }
    
    if(runtwParam) {
        clearTween.removeTween(runtwParam);
        runtwParam = NULL;
    }
    
    if(runstarParam) {
        clearTween.removeTween(runstarParam);
        runstarParam = NULL;
    }
    
    if(runnumParam) {
        clearTween.removeTween(runnumParam);
        runnumParam = NULL;
    }
    
    fbParam = TweenerParam(1000 * 0.3, CUBIC, EASE_OUT);
    runfbParam = &fbParam;
    fbParam.addProperty(&fbX, FB_TW_X_HIDE);
    clearTween.addTween(fbParam);
    
    twParam = TweenerParam(1000 * 0.3, EXPO, EASE_OUT, 1000 * 0.05);
    runtwParam = &twParam;
    twParam.addProperty(&twX, FB_TW_X_HIDE);
    clearTween.addTween(twParam);
    
    Popup::Close();
}

void PopupClear::touchBegin(CCTouch* _touch, CCPoint _location) {
    Popup::touchBegin(_touch, _location);
    TOUCHBEGINBT(fbTouch, fbBT, _location, _touch, fbM->gotoAndStop(1));
    TOUCHBEGINBT(twTouch, twBT, _location, _touch, twM->gotoAndStop(1));
    if(reTouch == NULL && plTouch == NULL && meTouch == NULL && shTouch == NULL && frTouch == NULL && fbTouch == NULL && twTouch == NULL && numTouch == NULL) {
        numTouch = _touch;
    }
}

void PopupClear::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    Popup::touchEndAndCancel(_touch, _location);
    TOUCHENDBT(fbTouch, fbBT, _location, _touch, , fbM->gotoAndStop(0));
    TOUCHENDBT(twTouch, twBT, _location, _touch, , twM->gotoAndStop(0));
    if(numTouch == _touch) {
        numCount = score;
        
        if(runnumParam) {
            clearTween.removeTween(runnumParam);
            runnumParam = NULL;
        }
    }
}


