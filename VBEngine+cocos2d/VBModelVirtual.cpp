#include "VBModel.h"

void VBModel::setTextureRectInPixels(CCRect rect, bool rotated, CCSize size) {
    m_obRectInPixels = rect;
	m_obRect = CC_RECT_PIXELS_TO_POINTS(rect);
	m_bRectRotated = rotated;
    
	setContentSizeInPixels(size);
	updateTextureCoords(m_obRectInPixels);
    
	CCPoint relativeOffsetInPixels = m_obUnflippedOffsetPositionFromCenter;
    
	if (m_bFlipX)
	{
		relativeOffsetInPixels.x = -relativeOffsetInPixels.x;
	}
	if (m_bFlipY)
	{
		relativeOffsetInPixels.y = -relativeOffsetInPixels.y;
	}
    
	m_obOffsetPositionInPixels.x = relativeOffsetInPixels.x + (m_tContentSizeInPixels.width - m_obRectInPixels.size.width) / 2;
	m_obOffsetPositionInPixels.y = relativeOffsetInPixels.y + (m_tContentSizeInPixels.height - m_obRectInPixels.size.height) / 2;
    
	if (m_bUsesBatchNode)
	{
		m_bDirty = true;
	}
	else
	{
		m_sQuad.bl.vertices = vertex3(0, 0, 0);
		m_sQuad.br.vertices = vertex3(m_obRectInPixels.size.width, 0, 0);
		m_sQuad.tl.vertices = vertex3(0, -m_obRectInPixels.size.height, 0);
		m_sQuad.tr.vertices = vertex3(m_obRectInPixels.size.width, -m_obRectInPixels.size.height, 0);
	}
}

void VBModel::updateTextureCoords(CCRect rect) {
	if(!tex) {
		return;
	}
    
	float atlasWidth = tex->width;
	float atlasHeight = tex->height;
    
	float left, right, top, bottom;
    
    left	= rect.origin.x/atlasWidth;
    right	= left + rect.size.width/atlasWidth;
    top		= rect.origin.y/atlasHeight;
    bottom	= top + rect.size.height/atlasHeight;
    
    m_sQuad.bl.texCoords.u = left;
    m_sQuad.bl.texCoords.v = top;
    m_sQuad.br.texCoords.u = right;
    m_sQuad.br.texCoords.v = top;
    m_sQuad.tl.texCoords.u = left;
    m_sQuad.tl.texCoords.v = bottom;
    m_sQuad.tr.texCoords.u = right;
    m_sQuad.tr.texCoords.v = bottom;
    
}

CCAffineTransform VBModel::nodeToParentTransform(void) {
	if(m_bIsTransformDirty) {
        mat = VBMatrix2DWrapperLoadIdentity();
		
        mat = VBMatrix2DWrapperSetPosition(mat, VBVector2DCreate(m_tPosition.x, m_tPosition.y));
        mat = VBMatrix2DWrapperSetScale(mat, VBVector2DCreate(m_fScaleX, m_fScaleY));
        if(isnan(m_fRotation)) {
            mat = VBMatrix2DWrapperSetShear(mat, VBVector2DCreate(m_fSkewX, m_fSkewY));
            mat = VBMatrix2DWrapperSetRotation(mat, NAN);
        } else {
            mat = VBMatrix2DWrapperSetRotation(mat, m_fRotation);
        }
        mat = VBMatrix2DWrapperSetAnchor(mat, VBVector2DCreate(m_tAnchorPoint.x, m_tAnchorPoint.y));
        mat = VBMatrix2DWrapperUpdate(mat);
        
		m_tTransform = CCAffineTransformMake(mat.mat.m11, mat.mat.m21, mat.mat.m12, mat.mat.m22, mat.mat.m13, mat.mat.m23);
        
		m_bIsTransformDirty = false;
	}
    
	return m_tTransform;
}

void VBModel::draw() {
	//CCSprint의 draw함수를 copy하여 수정한 코드
	CCAssert(! m_bUsesBatchNode, "");
	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: -
	bool newBlend = GL_SRC_ALPHA != CC_BLEND_SRC || GL_ONE_MINUS_SRC_ALPHA != CC_BLEND_DST;
	if (newBlend)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	
#define kQuadSize sizeof(m_sQuad.bl)
    if (tex)
    {
        glBindTexture(GL_TEXTURE_2D, VBTextureGetID(tex));
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
	
	long offset = (long)&m_sQuad;
	
	// vertex
	int diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexPointer(3, GL_FLOAT, kQuadSize, (void*)(offset + diff));
	
	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (void*)(offset + diff));
	
	// tex coords
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (void*)(offset + diff));
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	if( newBlend )
	{
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}
	
#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    CCSize s = m_tContentSize;
    CCPoint vertices[4] = {
        ccp(0,0), ccp(s.width,0),
        ccp(s.width,s.height), ccp(0,s.height)
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    const CCSize& s = m_obRect.size;
    const CCPoint& offsetPix = getOffsetPositionInPixels();
    CCPoint vertices[4] = {
        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
}
