//
//  CCStreamTexture2D.cpp
//  MoronFriends
//
//  Created by wonhee jang on 12. 5. 3..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCStreamTexture2D.h"

CCStreamTexture2D::CCStreamTexture2D() : CCTexture2D() {
	
}
void CCStreamTexture2D::reload(CCImage* img) {
	if(m_uName)
		glDeleteTextures(1, &m_uName);
	initWithImage(img);
}