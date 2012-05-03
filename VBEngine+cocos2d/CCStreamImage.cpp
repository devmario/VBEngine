//
//  CCStreamImage.cpp
//  MoronFriends
//
//  Created by wonhee jang on 12. 5. 3..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include "CCStreamImage.h"

CCStreamImage::CCStreamImage() : CCImage() {
	m_pData = NULL;
}

void CCStreamImage::resetStreamData(void * data, int nWidth, int nHeight, PIXELTYPE p_type) {
	switch (p_type) {
		case PIXELTYPE_RGB_24:
			m_bHasAlpha = false;
			break;
		case PIXELTYPE_BGRA_32:
			m_bHasAlpha = true;
			break;
		case PIXELTYPE_RGBA_32:
			m_bHasAlpha = true;
			break;
	}
	m_nBitsPerComponent = 8;
	m_nHeight   = (short)nHeight;
	m_nWidth    = (short)nWidth;
	int word = (m_bHasAlpha ? 4 : 3);
	
	size_t len = m_nHeight * m_nWidth;
	size_t nSize = len * word;
	if(m_pData == NULL)
		m_pData = new unsigned char[nSize];
	else
		m_pData = (unsigned char*)realloc(m_pData, nSize);
	
	memcpy(m_pData, data, nSize);
	
	switch (p_type) {
		case PIXELTYPE_BGRA_32:
		{
			unsigned char* ptr = m_pData;
			for(int i = 0; i < len; i++) {
				unsigned char tmp = ptr[0];
				*(ptr) = ptr[2];
				*(ptr + 2) = tmp;
				ptr += word;
			}
		}
			break;
		default:
			break;
	}
}

void CCStreamImage::flip() {
	int word = (m_bHasAlpha ? 4 : 3);
	size_t rowSize = m_nWidth * word;
	unsigned char* row = new unsigned char[rowSize];
	unsigned char* ptrT = m_pData;
	unsigned char* ptrB = m_pData + m_nHeight * m_nWidth * word - rowSize;
	for(int i = 0; i < m_nHeight / 2; i++) {
		memcpy(row, ptrT, rowSize);
		memcpy(ptrT, ptrB, rowSize);
		memcpy(ptrB, row, rowSize);
		ptrT += rowSize;
		ptrB -= rowSize;
	}
}