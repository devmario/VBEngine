#include "Text.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

bool TextInit(Text* text, Font* font, unsigned short width, unsigned short height, TextAlign align) {
	text->font = font;
	
	text->align = align;
	
	text->width = width;
	text->height = height;
	
	text->vertex = malloc(sizeof(Vector3D) * 4);
	switch(align & TextAlignHorizontal) {
		case TextAlignLeft:
			text->vertex[0].x = text->vertex[2].x = 0.0;
			text->vertex[1].x = text->vertex[3].x = (float)width;
			break;
		case TextAlignCenter:
			text->vertex[0].x = text->vertex[2].x = -(float)width * 0.5;
			text->vertex[1].x = text->vertex[3].x = (float)width * 0.5;
			break;
		case TextAlignRight:
			text->vertex[0].x = text->vertex[2].x = -(float)width;
			text->vertex[1].x = text->vertex[3].x = 0.0;
			break;
	}
	switch(align & TextAlignVertical) {
		case TextAlignTop:
			text->vertex[0].y = text->vertex[1].y = 0.0;
			text->vertex[2].y = text->vertex[3].y = (float)height;
			break;
		case TextAlignMiddle:
			text->vertex[0].y = text->vertex[1].y = -(float)height * 0.5;
			text->vertex[2].y = text->vertex[3].y = (float)height * 0.5;
			break;
		case TextAlignBottom:
			text->vertex[0].y = text->vertex[1].y = -(float)height;
			text->vertex[2].y = text->vertex[3].y = 0.0;
			break;
	}
	
	text->model = malloc(sizeof(Model));
	ModelInitWithVertex(text->model, 4, text->vertex, NULL, NULL, 0, NULL, 0);
	
	text->maskModel = malloc(sizeof(Model));
	ModelInitWithVertex(text->maskModel, 4, text->vertex, NULL, NULL, 0, NULL, 0);
	ModelSetMask(text->model, text->maskModel);
	
	text->childModel = malloc(sizeof(Array));
	ArrayInit(text->childModel);
	
	text->string = NULL;
	
	return true;
}

bool TextFree(Text* text) {
	if(text->string)
		free(text->string);
	
	while(text->childModel->length) {
		Model* childModel = ArrayPopObjectAtIndex(text->childModel, 0);
		ModelFree(childModel);
		free(childModel);
	}
	ArrayFree(text->childModel);
	free(text->childModel);
	
	ModelFree(text->model);
	free(text->model);
	
	ModelFree(text->maskModel);
	free(text->maskModel);
	
	free(text->vertex);
	
	return true;
}

bool TextSetString(Text* text, char* string) {
	if(text->string) {
		while(text->childModel->length) {
			TextDeleteCharAtIndex(text, 0);
		}
	}
	
	int stringLength = strlen(string);
	int i = 0;
	for(; i < stringLength; i++) {
		TextInsertCharAtIndex(text, string[i], i);
	}
	
	TextSetAlign(text, text->align);
	
	return true;
}

char* TextGetString(Text* text) {
	return text->string;
}

unsigned int TextGetStringLength(Text* text) {
	return strlen(text->string);
}

bool TextInsertCharAtIndex(Text* text, char charCode, unsigned int index) {
	int stringLength = 0;
	if(text->string)
		stringLength = strlen(text->string);
	text->string = realloc(text->string, sizeof(char) * (stringLength + 2));
	int i;
	for(i = index; i < stringLength; i++) {
		text->string[i + 1] = text->string[i];
	}
	text->string[index] = charCode;
	text->string[stringLength + 1] = '\0';
	
	Model* model = malloc(sizeof(Model));
	ModelInitWithVertex(model, 4, 
						text->font->vertex[text->string[index]], 
						text->font->normal[text->string[index]], 
						text->font->texcoord[text->string[index]], 
						0, NULL,
						text->font->textureID);
	ArrayPushObjectAtIndex(text->childModel, model, index);
	if(model->vertex != text->font->vertex['\n'])
		ModelAdd(text->model, model);
	
	return true;
}

bool TextDeleteCharAtIndex(Text* text, unsigned int index) {
	int stringLength = 0;
	if(text->string)
		stringLength = strlen(text->string);
	int i = index;
	for(; i < stringLength; i++) {
		text->string[i] = text->string[i + 1];
	}
	text->string = realloc(text->string, sizeof(char) * stringLength);
	
	Model* model = (Model*)ArrayPopObjectAtIndex(text->childModel, index);
	ModelFree(model);
	free(model);
	
	return true;
}

bool TextSetAlign(Text* text, TextAlign align) {
	text->align = align;
	Model* model;
	int i;
	float maxWidth = 0.0;
	int lineNum = 1;
	for(i = 0; i < text->childModel->length; i++) {
		model = ArrayObjectAtIndex(text->childModel, i);
		if(model->vertex == text->font->vertex['\n']) {
			lineNum++;
		}
	}
	float width[lineNum];
	int lineIndex = 0;
	for(i = 0; i < text->childModel->length; i++) {
		model = ArrayObjectAtIndex(text->childModel, i);
		if(model->vertex != text->font->vertex['\n']) {
			width[lineIndex] += model->vertex[1].x - model->vertex[0].x;
		} else {
			maxWidth = fmaxf(maxWidth, width[lineIndex]);
			lineIndex++;
		}
	}
	float lineHeight = text->font->vertex[0][2].y - text->font->vertex[0][0].y;
	float y = 0.0;
	float x = 0.0;
	lineIndex = 0;
	switch(align & 0x0F) {
		case TextAlignLeft:
			x = 0.0;
			break;
		case TextAlignCenter:
			x = -width[lineIndex] / 2.0;
			break;
		case TextAlignRight:
			x = -width[lineIndex];
			break;
	}
	switch(align & 0xF0) {
		case TextAlignTop:
			y = 0.0;
			break;
		case TextAlignMiddle:
			y = -(lineHeight * lineNum) / 2.0;
			break;
		case TextAlignBottom:
			y = -(lineHeight * lineNum);
			break;
	}
	Model* preModel = NULL;
	for(i = 0; i < text->childModel->length; i++) {
		model = (Model*)ArrayObjectAtIndex(text->childModel, i);
		if(model->vertex != text->font->vertex['\n']) {
			if(preModel) {
				if(preModel->vertex != text->font->vertex['\n'])
					x += preModel->vertex[1].x;
			}
		} else {
			lineIndex++;
			switch(align & 0x0F) {
				case TextAlignLeft:
					x = 0.0;
					break;
				case TextAlignCenter:
					x = -width[lineIndex] / 2;
					break;
				case TextAlignRight:
					x = -width[lineIndex];
					break;
			}
			y += lineHeight;
		}
		ModelSetPosition(model, Vector3DInit(x, y, 0.0));
		preModel = model;
	}
	return true;
}

TextAlign TextGetAlign(Text* text) {
	return text->align;
}
