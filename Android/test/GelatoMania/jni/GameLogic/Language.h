//
//  Language.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 10..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_Language_h
#define gelatomania_Language_h

#include "cJSON.h"

class Language {
    cJSON* json;
    cJSON* font_json;
public:
    static Language* shareLanguage();
    
    Language();
    ~Language();
    
    const char* GetString(const char* tk, int count, ...);
    const char* GetFontName(const char* type);
};


#endif
