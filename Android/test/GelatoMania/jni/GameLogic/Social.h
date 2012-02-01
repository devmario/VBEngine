//
//  Social.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 1..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#include "cJSON.h"

#ifndef gelatomania_Social_h
#define gelatomania_Social_h

class Social {
public:
    cJSON* gameCenterInfo;
    
    Social();
    ~Social();
    
    void LoginFacebook();
    void LoginGameCenter();
};

#endif
