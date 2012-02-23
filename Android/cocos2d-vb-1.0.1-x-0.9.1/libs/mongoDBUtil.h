//
//  mongoDBUtil.h
//  gelatomania
//
//  Created by wonhee jang on 12. 2. 19..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_mongoDBUtil_h
#define gelatomania_mongoDBUtil_h

#include <time.h>

time_t nodejsDateToTime(const char* nodeJSdateSTR);
char* timeToNodejsDate(time_t _time);
void printTime(time_t _time);

#endif
