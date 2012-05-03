//
//  CCStreamTexture2D.h
//  MoronFriends
//
//  Created by wonhee jang on 12. 5. 3..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#ifndef MoronFriends_CCStreamTexture2D_h
#define MoronFriends_CCStreamTexture2D_h

#include <iostream>
#include <stdlib.h>
#include "cocos2d.h"

using namespace cocos2d;

namespace cocos2d {
	class CCStreamTexture2D : public CCTexture2D {
	public:
		CCStreamTexture2D();
		void reload(CCImage* img);
	};
};

#endif
