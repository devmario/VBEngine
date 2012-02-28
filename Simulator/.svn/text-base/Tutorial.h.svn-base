/*
 *  Tutorial.h
 *  IbizaXcode
 *
 *  Created by Mario on 10. 10. 29..
 *  Copyright 2010 Vanilla Breeze. All rights reserved.
 *
 */

#ifndef Tutorial_H
#define Tutorial_H

#include "Model.h"
#include "ObjFileForModel.h"

typedef struct Tutorial Tutorial;

struct Tutorial {
	char* resourcePath;
	
	ObjectFile* of;
	
	ModelManager* manager;
	Camera* camera;
	
	Model* topModel;
};

Tutorial* tutorial;

void initTutorial(const char* _resourcePath, int w, int h);

void renderTutorial(bool isLine);

void freeTutorial();

#endif