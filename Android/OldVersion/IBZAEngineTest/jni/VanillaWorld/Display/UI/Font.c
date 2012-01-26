#include "Font.h"
#include <stdlib.h>

bool FontInitFontObject2D(Font* font, Object2DSeries* fontObject2D) {
	//font->textureID = fontObject2D->textureID[0];
	font->vertex = malloc(sizeof(Vector3D*) * 127);
	font->normal = malloc(sizeof(Vector3D*) * 127);
	font->texcoord = malloc(sizeof(Vector2D*) * 127);
	signed char i = 0;
	for(; i < 127; i++) {
		char charCode[2];
		charCode[0] = i;
		charCode[1] = '\0';
		Object2D* charObject = Object2DSeriesGetObject2D(fontObject2D, charCode);
		if(charObject) {
			font->vertex[i] = charObject->vertex;
			font->normal[i] = charObject->normal;
			font->texcoord[i] = charObject->texcoord;
		}
	}
	return true;
}

bool FontFree(Font* font) {
	free(font->texcoord);
	free(font->normal);
	free(font->vertex);
	return true;
}

Vector3D* FontGetCharVertex(Font* font, char charCode) {
	return font->vertex[charCode];
}

Vector3D* FontGetCharNormal(Font* font, char charCode) {
	return font->normal[charCode];
}

Vector2D* FontGetCharTexcoord(Font* font, char charCode) {
	return font->texcoord[charCode];
}

