//
//  CCStreamImage.h
//  MoronFriends
//
//  Created by wonhee jang on 12. 5. 3..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#ifndef MoronFriends_CCStreamImage_h
#define MoronFriends_CCStreamImage_h

#include <iostream>
#include <stdlib.h>
#include "cocos2d.h"

using namespace cocos2d;

namespace cocos2d {
	class CCStreamImage : public CCImage {
	public:
		typedef enum PIXELTYPE {
			PIXELTYPE_RGB_24	=	0,
			PIXELTYPE_BGRA_32	=	1,
			PIXELTYPE_RGBA_32	=	2
		} PIXELTYPE;
		
		CCStreamImage();
		void resetStreamData(void * data, int nWidth, int nHeight, PIXELTYPE type);
		void flip();
	};
};

#endif
