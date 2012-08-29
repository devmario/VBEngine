//
//  CCStreamTexture2D.cpp
//  MoronFriends
//
//  Created by wonhee jang on 12. 5. 3..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCConfiguration.h"
#include "CCStreamTexture2D.h"
#include "ccUtils.h"

CCStreamTexture2D::CCStreamTexture2D() : CCTexture2D() {
	
}
CCStreamTexture2D::~CCStreamTexture2D() {
}
void CCStreamTexture2D::reload(CCImage* img) {
	if(m_uName)
		glDeleteTextures(1, &m_uName);
	m_uName = 0;
	initWithImage(img);
}

void CCStreamTexture2D::reload(const void *data, CCTexture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh) {
	if(m_uName)
		glDeleteTextures(1, &m_uName);
	m_uName = 0;
	
	unsigned int POTWide, POTHigh;
	
#if CC_TEXTURE_NPOT_SUPPORT
	if( conf->isSupportsNPOT() ) 
	{
		POTWide = pixelsWide;
		POTHigh = pixelsHigh;
	}
	else 
#endif
	{
		POTWide = ccNextPOT(pixelsWide);
		POTHigh = ccNextPOT(pixelsHigh);
	}
	
	initWithData(data, pixelFormat, POTWide, POTHigh, CCSize(pixelsWide, pixelsHigh));
}