#include "TextInput.h"
#include <stdlib.h>
#include <string.h>

void TextInputEventTouch(void* userReference, ModelEventTouchArgument argument) {
}

void TextInputEventRender(void* userReference, ModelEventRenderArgument argument) {
}

bool TextInputInit(TextInput* input, Font* font, unsigned short width, unsigned short height, TextAlign align, bool lineReturn, unsigned long maxChar) {
	input->originText = malloc(sizeof(Text));
	TextInit(input->originText, font, width, height, align);
	input->model = input->originText->model;
	
	input->lineReturn = lineReturn;
	input->maxChar = maxChar;
	
	ModelEventTouch event;
	event.userReference = NULL;
	event.event = TextInputEventTouch;
	ModelAddEventTouch(input->model, event, 2, input->originText->vertex, false, false, false, false);
	
	input->underLineVertex = malloc(sizeof(Vector3D) * 4);
	input->underLineVertex[0].x = input->underLineVertex[2].x = -3.0;
	input->underLineVertex[0].y = input->underLineVertex[1].y = 0.0;
	input->underLineVertex[1].x = input->underLineVertex[3].x = 3.0;
	input->underLineVertex[2].y = input->underLineVertex[3].y = font->vertex[0][2].y - font->vertex[0][0].y;
	input->underLineVertex[0].z = input->underLineVertex[1].z = input->underLineVertex[2].z = input->underLineVertex[3].z = 0.0;
	
	input->underLine = malloc(sizeof(Model));
	ModelInitWithVertex(input->underLine, 4, input->underLineVertex, NULL, NULL, 0, NULL, 0);
	
	input->focusEvent.userReference = NULL;
	input->focusEvent.event = NULL;
	
	return true;
}

bool TextInputFree(TextInput* input) {
	ModelFree(input->underLine);
	free(input->underLine);
	free(input->underLineVertex);
	
	TextFree(input->originText);
	free(input->originText);
	return true;
}

bool TextInputAlignUnderLine(TextInput* input) {
	float addX = 0.0;
	float addY = 0.0;
	Model* child;
	if(input->selectedIndex > 0) {
		child = ArrayObjectAtIndex(input->originText->childModel, input->selectedIndex - 1);
		if(child->vertex == input->originText->font->vertex['\n']) {
			addX = child->matrix->m41 - input->underLine->matrix->m41;
			addY = child->matrix->m42 - input->underLine->matrix->m42;
		} else {
			addX = (child->matrix->m41 + child->vertex[1].x) - input->underLine->matrix->m41;
			addY = child->matrix->m42 - input->underLine->matrix->m42;
		}
	} else {
		if(input->originText->childModel->length) {
			child = ArrayObjectAtIndex(input->originText->childModel, 0);
			addX = child->matrix->m41 - input->underLine->matrix->m41;
			addY = child->matrix->m42 - input->underLine->matrix->m42;
		} else {
			addX = -input->underLine->matrix->m41;
			switch(input->originText->align & 0xF0) {
				case TextAlignTop:
					addY = -input->underLine->matrix->m42;
					break;
				case TextAlignMiddle:
					addY = -(input->underLine->vertex[2].y * 0.5) - input->underLine->matrix->m42;
					break;
				case TextAlignBottom:
					addY = -input->underLine->vertex[2].y - input->underLine->matrix->m42;
					break;
			}
		}
	}
	*input->underLine->matrix = Matrix3DTranslate(*input->underLine->matrix, Vector3DInit(addX, addY, 0.0));
	return true;
}

bool TextInputSetFocus(TextInput* input, bool focus) {
	if(focus != input->focus) {
		input->focus = focus;
		if(input->focusEvent.event)
			input->focusEvent.event(input->focusEvent.userReference, input, input->focus);
		if(focus) {
			ModelAdd(input->model, input->underLine);
			
			TextInputAlignUnderLine(input);
			
			ModelEventRender event;
			event.userReference = input;
			event.event = TextInputEventRender;
			ModelAddEventRender(input->underLine, event);
			
			//openGLkeyboard* keyboard = (openGLkeyboard*)input->keyboard;
			//setKeyboardTarget(keyboard, input);
		} else {
			ModelRemove(input->model, input->underLine);
			ModelRemoveEventRender(input->underLine);
			
			//openGLkeyboard* keyboard = (openGLkeyboard*)input->keyboard;
			//setKeyboardTarget(keyboard, NULL);
		}
	}
	return true;
}

bool TextInputGetFocus(TextInput* input) {
	return input->focus;
}

bool TextInputSetString(TextInput* input, char* string) {
	TextSetString(input->originText, string);
	input->selectedIndex = strlen(string);
	TextInputAlignUnderLine(input);
	return true;
}

char* TextInputGetString(TextInput* input) {
	return input->originText->string;
}

unsigned int TextInputGetStringLength(TextInput* input) {
	return strlen(input->originText->string);
}

bool TextInputInsertCharAtIndex(TextInput* input, char charCode, unsigned int index) {
	return true;
}

bool TextInputDeleteCharAtIndex(TextInput* input, unsigned int index) {
	return true;
}

bool TextInputSetAlign(TextInput* input, TextAlign align) {
	return true;
}

TextAlign TextInputGetAlign(TextInput* input) {
	return TextAlignBottom;
}

bool TextInputAddFocusEvent(TextInput* input, TextInputFocusEvent focusEvent) {
	return true;
}

bool TextInputRemoveFocusEvent(TextInput* input) {
	return true;
}