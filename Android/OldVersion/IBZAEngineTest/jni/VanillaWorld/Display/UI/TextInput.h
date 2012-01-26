#ifndef __TEXT_INPUT__H__
#define __TEXT_INPUT__H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "Text.h"
	
	typedef struct TextInput TextInput;
	
	typedef struct TextInputFocusEvent TextInputFocusEvent;
	
	struct TextInputFocusEvent {
		void* userReference;
		void (*event)(void* userReference, TextInput* input, bool focus);
	};
	
	struct TextInput {
		Text* originText;
		
		bool lineReturn;
		bool focus;
		unsigned long maxChar;
		unsigned long selectedIndex;
		
		Model* model;
		
		Model* underLine;
		Vector3D* underLineVertex;
		bool isUnderLineVisible;
		
		void* touchID;
		
		TextInputFocusEvent focusEvent;
	};
	
	bool TextInputInit(TextInput* input, Font* font, unsigned short width, unsigned short height, TextAlign align, bool lineReturn, unsigned long maxChar);
	bool TextInputFree(TextInput* input);
	
	bool TextInputSetFocus(TextInput* input, bool focus);
	bool TextInputGetFocus(TextInput* input);
	
	bool TextInputSetString(TextInput* input, char* string);
	char* TextInputGetString(TextInput* input);
	
	unsigned int TextInputGetStringLength(TextInput* input);
	
	bool TextInputInsertCharAtIndex(TextInput* input, char charCode, unsigned int index);
	bool TextInputDeleteCharAtIndex(TextInput* input, unsigned int index);
	
	bool TextInputSetAlign(TextInput* input, TextAlign align);
	TextAlign TextInputGetAlign(TextInput* input);
	
	bool TextInputAddFocusEvent(TextInput* input, TextInputFocusEvent focusEvent);
	bool TextInputRemoveFocusEvent(TextInput* input);
	
#ifdef __cplusplus
}
#endif

#endif