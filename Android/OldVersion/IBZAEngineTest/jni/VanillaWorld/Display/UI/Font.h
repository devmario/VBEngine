#ifndef __FONT_H__
#define __FONT_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "../Core/Vector.h"
#include "../Object/Object2D.h"
#include <stdbool.h>
	
	typedef struct Font Font;
	
	struct Font {
		unsigned int textureID;
		
		Vector3D** vertex;
		Vector3D** normal;
		Vector2D** texcoord;
	};
	
	bool FontInitFontObject2D(Font* font, Object2DSeries* fontObject2D);
	bool FontFree(Font* font);
	
	Vector3D* FontGetCharVertex(Font* font, char charCode);
	Vector3D* FontGetCharNormal(Font* font, char charCode);
	Vector2D* FontGetCharTexcoord(Font* font, char charCode);
	
#ifdef __cplusplus
}
#endif

#endif