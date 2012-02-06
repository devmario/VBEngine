#include "Popup.h"
#include "ShareData.h"
#include "SubMenu.h"

#define ENDY_POPUP 320
#define ENDALPHA_POPUP 0x88

void popUpTweenCallBack(void*);

Popup::Popup(VBObjectFile2D* _obj, VBTexture* _tex, VBModel* _topView) : View() {
    //cout << "new Popup\n";
    isClearPopup = false;
    obj = _obj;
    tex = _tex;
    topView = _topView;
    inited = false;
    closeCount = 0;
    isClosed = false;
    showTween = NULL;
}

void Popup::init() {
    if(inited == false) {
        ClearTween();
        
        VBObjectFile2DLibraryNameID* _name_id;
        VBString* _str;
        
        popupY = ENDY_POPUP;
        bgAlpha = 0.0;
        
        reBT = plBT = meBT = shBT = frBT = NULL;
        reTouch = plTouch = meTouch = shTouch = frTouch = NULL;
        
        if(obj == NULL) {
            OBJLOAD(obj, ObjName(), _str);
            objRes = obj;
        } else {
            objRes = obj;
            obj = NULL;
        }
        if(tex == NULL) {
            TEXLOAD(tex, TexName(), _str);
            texRes = tex;
        } else {
            texRes = tex;
            tex = NULL;
        }
        
        LIBNAMEFIND(_name_id, obj, "bg", _str);
        bg = new VBModel(obj, _name_id, tex, true);
        top->addChild(bg);
        bg->color.a = bgAlpha;
        
        LIBNAMEFIND(_name_id, obj, "popup", _str);
        popup = new VBModel(obj, _name_id, tex, true);
        popup->stop();
        top->addChild(popup);
        popup->setPosition(CCPointMake(0, popupY));
        
        reBT = popup->getVBModelByName((char*)"re");
        plBT = popup->getVBModelByName((char*)"play");
        meBT = popup->getVBModelByName((char*)"menu");
        shBT = popup->getVBModelByName((char*)"shop");
        frBT = popup->getVBModelByName((char*)"free");
        inited = true;
        isClosed = false;
    }
}

Popup::~Popup() {

    //cout << "delete Popup\n";
    ClearTween();
    
    top->removeChild(popup, false);
    delete popup;
    popup = NULL;
    top->removeChild(bg, false);
    delete bg;
    bg = NULL;
    if(obj)
        VBObjectFile2DFree(&obj);
    if(tex)
        VBTextureFree(&tex);
}

void Popup::ClearTween() {
    if(showTween) {
        delete showTween;
        showTween = NULL;
    }
    
}

void Popup::Update(float _deltaTime) {
    if (showTween) {
        showTween->update(_deltaTime);
    }
    if(popup)
        popup->setPosition(CCPointMake(0, popupY));
    if(bg)
        bg->color.a = (unsigned char)bgAlpha;
    if(top) {
        unsigned char colorCode = (unsigned char)(bgAlpha * 2.0 > 0xFF ? 0xFF : bgAlpha * 2.0);
        top->color.r = colorCode;
        top->color.g = colorCode;
        top->color.b = colorCode;
    }
    if(isClosed) {
        closeCount += 1000 * _deltaTime;
        if(closeCount > 1000 * 0.5) {
            if(closeFunc)
                closeFunc(closeFuncRef);
        }
    }
}

void Popup::Open(void (*_closeFunc)(void* _closeFuncRef), void* _closeFuncRef) {
    init();
    
    closeFunc = _closeFunc;
    closeFuncRef = _closeFuncRef;
    
    topView->addChild(top);
    
    ClearTween();
    
    TweenerParam *slideParam = new TweenerParam(1000 * 0.5, EXPO, EASE_OUT);
    slideParam->addProperty(&bgAlpha, ENDALPHA_POPUP);
    
    showTween = new TweenerWrapper();
    showTween->setParamAndBegin(slideParam, &popupY, 0, popUpTweenCallBack, this);
}

void Popup::Close() {
    ClearTween();
    
    TweenerParam *slideParam = new TweenerParam(1000 * 0.5, EXPO, EASE_OUT);
    slideParam->addProperty(&bgAlpha, 0x00);
    showTween = new TweenerWrapper();
    showTween->setParamAndBegin(slideParam, &popupY, ENDY_POPUP, popUpTweenCallBack, this);
    
    closeCount = 0;
    isClosed = true;
}


void Popup::touchBegin(CCTouch* _touch, CCPoint _location) {
    TOUCHBEGINBT(reTouch, reBT, _location, _touch, reBT->gotoAndStop(1));
    TOUCHBEGINBT(plTouch, plBT, _location, _touch, plBT->gotoAndStop(1));
    TOUCHBEGINBT(meTouch, meBT, _location, _touch, meBT->gotoAndStop(1));
    TOUCHBEGINBT(shTouch, shBT, _location, _touch, shBT->gotoAndStop(1));
    TOUCHBEGINBT(frTouch, frBT, _location, _touch, frBT->gotoAndStop(1));
}

void Popup::touchMove(CCTouch* _touch, CCPoint _location) {
    
}

void Popup::touchEndAndCancel(CCTouch* _touch, CCPoint _location) {
    TOUCHENDBT(reTouch, reBT, _location, _touch, ShareDataGetRoot()->ClosePopup(),reBT->gotoAndStop(0));
    TOUCHENDBT(plTouch, plBT, _location, _touch, playButtonClick(),plBT->gotoAndStop(0));
    TOUCHENDBT(meTouch, meBT, _location, _touch, ShareDataGetRoot()->OutGoingAtGameMain(),meBT->gotoAndStop(0));
    TOUCHENDBT(shTouch, shBT, _location, _touch, 
               ShareDataGetRoot()->ChangePage(4, LoadingTypeFull, PopupTypeNone, RootPageTypeSubMenu, SubMenuTypeShop);
               ,shBT->gotoAndStop(0));
    TOUCHENDBT(frTouch, frBT, _location, _touch, ShareDataGetRoot()->ClosePopup(),frBT->gotoAndStop(0));
}

void Popup::touchEnd(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}

void Popup::touchCancel(CCTouch* _touch, CCPoint _location) {
    touchEndAndCancel(_touch, _location);
}

void Popup::playButtonClick() {
    if (isClearPopup) {
        ShareDataGetRoot()->goFowardStage();
    } else {
        ShareDataGetRoot()->ClosePopup();
    }
}

void popUpTweenCallBack(void* callBackObj)
{
    Popup *popup = (Popup*)callBackObj;
    if (popup->isClosed) {
        if(popup->closeFunc)
            popup->closeFunc(popup->closeFuncRef);
    } else {
        popup->bgAlpha = ENDALPHA_POPUP;
        
    }
    
}
