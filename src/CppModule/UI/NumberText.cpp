#include "NumberText.h"
#include "ShareData.h"

NumberText::NumberText(VBObjectFile2D* _obj, VBTexture* _tex, char* _lib_name, int _align, float _shiftX) : VBModel() {
    shiftX = _shiftX;
    obj = _obj;
    tex = _tex;
    num = -1;
    align = _align;
    libName = (char*)calloc(1, strlen(_lib_name) + 1);
    sprintf(libName, "%s", _lib_name);
    arr = VBArrayVectorInit(VBArrayVectorAlloc());
    
    SetNumber(0);
}

NumberText::~NumberText() {
    free(libName);
    while(VBArrayVectorGetLength(arr)) {
        VBModel* _numM = (VBModel*)VBArrayVectorRemoveAt(arr, 0);
        this->removeChild(_numM, false);
        delete _numM;
    }
    VBArrayVectorFree(&arr);
}

void NumberText::SetNumber(unsigned int _num) {
    char numBuf[0xFF];
    sprintf(numBuf, "%i", _num);
    
    int _preAlloc = VBArrayVectorGetLength(arr);
    while(VBArrayVectorGetLength(arr) > strlen(numBuf)) {
        VBModel* _numM = (VBModel*)VBArrayVectorRemoveBack(arr);
        this->removeChild(_numM, false);
        delete _numM;
    }
    
    VBString* _str;
    VBObjectFile2DLibraryNameID* name_id;
    float w = 0;
    
    for(int i = 0; i < strlen(numBuf); i++) {
        int numI = numBuf[i] - '0';
        VBModel* _m;
        if(i < _preAlloc) {
            _m = (VBModel*)VBArrayVectorGetDataAt(arr, i);
        } else {
            LIBNAMEFIND(name_id, obj, libName, _str);
            _m = new VBModel(obj, name_id, tex, true);
            VBArrayVectorAddBack(arr, _m);
            this->addChild(_m);
        }
        
        _m->setPosition(CCPointMake(w, 0));
        _m->gotoAndStop(numI);
        _m->VBModelUpdate(0.0);
        
        VBAABB _aabb = _m->getVBModelSize();
        float tw = _aabb.r - _aabb.l;
        w += tw + shiftX;
    }
    
    for(int i = 0; i < VBArrayVectorGetLength(arr); i++) {
        VBModel* _m = (VBModel*)VBArrayVectorGetDataAt(arr, i);
        if(align < 0) {
            ((CCSprite*)_m)->setPosition(CCPointMake(_m->getPosition().x - w, _m->getPosition().y));
        } else if(align == 0) {
            ((CCSprite*)_m)->setPosition(CCPointMake(_m->getPosition().x - w * 0.5, _m->getPosition().y));
        }
    }
}
