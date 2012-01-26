#ifndef __TEXT_H__
#define __TEXT_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "../Object/Model.h"
#include "../../Util/Array.h"
#include <stdbool.h>
	
#include "Font.h"
	
	typedef struct Text Text;
	
	enum {
		TextAlignHorizontal =	0x0F,
		TextAlignLeft =			0x02,
		TextAlignCenter =		0x04,
		TextAlignRight =		0x08,
		TextAlignVertical =		0xF0,
		TextAlignTop =			0x20,
		TextAlignMiddle =		0x40,
		TextAlignBottom =		0x80
	};
	typedef unsigned char TextAlign;
	
	struct Text {
		Font* font;
		
		Model* model;
		Model* maskModel;
		
		Array* childModel;
		
		Vector3D* vertex;
		
		unsigned short width;
		unsigned short height;
		
		TextAlign align;
		
		char* string;
	};
	
	bool TextInit(Text* text, Font* font, unsigned short width, unsigned short height, TextAlign align);
	bool TextFree(Text* text);
	
	bool TextSetString(Text* text, char* string);
	char* TextGetString(Text* text);
	
	unsigned int TextGetStringLength(Text* text);
	
	bool TextInsertCharAtIndex(Text* text, char charCode, unsigned int index);
	bool TextDeleteCharAtIndex(Text* text, unsigned int index);
	
	bool TextSetAlign(Text* text, TextAlign align);
	TextAlign TextGetAlign(Text* text);
	
#ifdef __cplusplus
}
#endif

#endif