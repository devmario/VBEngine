/*
 *  Tutorial.c
 *  IbizaXcode
 *
 *  Created by Mario on 10. 10. 29..
 *  Copyright 2010 Vanilla Breeze. All rights reserved.
 *
 */

#include "Tutorial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//터치 이벤트(주석 해제하면 작동함)
void _touchEvent(void *userReference, ModelEventTouchArgument argument) {
	/*
	if(argument.isHit)
		printf("hit!! touchID:%i hitVector(x:%f,y:%f,z:%f) touchType:%i\n", (int)argument.touchID, argument.hitVector->x, argument.hitVector->y, argument.hitVector->z, argument.touchType);
	else
		printf("noHit!!\n");
	*/
}

//시작
void initTutorial(const char* _resourcePath, int w, int h) {
	//튜토리얼 스트럭쳐 메모리 allocate
	tutorial = calloc(1, sizeof(Tutorial));
	
	//카메라 생성
	tutorial->camera = calloc(1, sizeof(Camera));
	CameraInitWithVector3D(tutorial->camera, Vector3DInit(0.0, 0.0, -415.0), Vector3DInit(0.0, 0.0, 0.0), Vector3DInit(0.0, -1.0, 0.0));
	
	//모델메니져 시작
	tutorial->manager = calloc(1, sizeof(ModelManager));
	ModelManagerStart(tutorial->manager, w, h, ColorHexRGBAToRGBAColor(0x000000FF));
	
	
	//최상위 모델 생성
	tutorial->topModel = calloc(1, sizeof(Model));
	ModelInitDefault(tutorial->topModel);
}

//업데이트
void updateTutorial() {
}

//업데이트 및 드로윙
void renderTutorial(bool line) {
	updateTutorial();
	
	//최상위 모델만 드로우 콜해주면 그 하위 모델들도 자동으로 렌더링
	ModelManagerDisplayBegin(tutorial->manager, ModelManagerDisplayMode3D, tutorial->camera, NULL);
	ModelManagerDisplay(tutorial->manager, tutorial->topModel,line);
	ModelManagerDisplayEnd(tutorial->manager);
}

//끝
void freeTutorial() {
	ModelFree(tutorial->topModel);
	free(tutorial->topModel);
	tutorial->topModel = NULL;
	
	ModelManagerShutdown(tutorial->manager);
	free(tutorial->manager);
	tutorial->manager = NULL;
	
	CameraFree(tutorial->camera);
	free(tutorial->camera);
	tutorial->camera = NULL;
	
	free(tutorial);
	tutorial = NULL;
}
