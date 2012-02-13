//
//  Text.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 10..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_Text_h
#define gelatomania_Text_h

#include "VBModel.h"

class Text : public VBModel {
    CCPoint tpos;
    VBTexture* ttex;
    VBVector2D shift;
public:
    Text();
    ~Text();
    
    virtual void setPosition(cocos2d::CCPoint pos);
    
    void SetText(const char* _txt, const char* _fontName, float _text_size, int _width, int _height, const char* _colorCode, const char* _shadowColorCode, VBVector2D _shadowOffset, int align = 0, int _is_line = 0);
};

#endif
