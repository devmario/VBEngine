#ifndef gelatomania_NumberText_h
#define gelatomania_NumberText_h

#include "VBModel.h"

class NumberText : public VBModel {
public:
    VBArrayVector* arr;
    VBObjectFile2D* obj;
    VBTexture* tex;
    unsigned int num;
    int align;
    char* libName;
    float shiftX;
    
    NumberText(VBObjectFile2D* _obj, VBTexture* _tex, char* _lib_name, int _align, float _shiftX);
    ~NumberText();
    
    void SetNumber(unsigned int _num);
};

#endif
