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
	if(argument.isHit)
		printf("hit!! touchID:%i hitVector(x:%f,y:%f,z:%f) touchType:%i\n", (int)argument.touchID, argument.hitVector->x, argument.hitVector->y, argument.hitVector->z, (int)argument.touchType);
	else
		printf("noHit!!\n");
}

//시작
void initTutorial(const char* _resourcePath, int w, int h) {
	//튜토리얼 스트럭쳐 메모리 allocate
	tutorial = calloc(1, sizeof(Tutorial));
	
	//리소스 경로 저장
	tutorial->resourcePath = calloc(strlen(_resourcePath), sizeof(char));
	sprintf(tutorial->resourcePath, "%s", _resourcePath);
	
	//카메라 생성
	tutorial->camera = malloc(sizeof(Camera));
	CameraInitWithVector3D(tutorial->camera, Vector3DInit(0.0, 0.0, -415.0), Vector3DInit(0.0, 0.0, 0.0), Vector3DInit(0.0, -1.0, 0.0));
	
	//모델메니져 시작
	tutorial->manager = malloc(sizeof(ModelManager));
	ModelManagerStart(tutorial->manager, w, h, ColorHexRGBAToRGBAColor(0x000000FF));
	
	//리소스 로드
	char* path = calloc(strlen(_resourcePath) + strlen("/ibiza.obj") + 1, sizeof(char));
	sprintf(path, "%s%s", _resourcePath, "/ibiza.obj");
	//내부적으로 메모리 생성
	tutorial->of = ObjectFileLoad(path); 
	free(path);
	
	//최상위 모델 생성
	tutorial->topModel = malloc(sizeof(Model));
	ModelInitDefault(tutorial->topModel);
	
	//기본 모델 라이브러리파일에서 오브젝트의 네이밍으로 모델 로드(이전버전과 틀린점은 플래쉬에서 센터 적용되어 있음)
	//내부적으로 메모리 생성
	//플래쉬의 라이브러리 center폴더
	tutorial->model = ObjectFileMakeModelWithSymbolName(tutorial->of, "window"); 
	//터치 이벤트 등록
	ModelAddEventTouch(tutorial->model, 
					   ModelEventTouchTinyInit(tutorial, _touchEvent), 2, tutorial->model->vertex, true, false, true, false);
	
	//mc_layout라이브러리 네임을 가진 무비클립로드
	//내부적으로 메모리 생성
	//플래쉬의 라이브러리 _dynamic폴더
	tutorial->layoutModel = ObjectFileMakeModelWithMovieClipName(tutorial->of, "mc_layout");
	
	//mc_animation라이브러리 네임을 가진 무비클립로드
	//내부적으로 메모리 생성
	//플래쉬의 라이브러리 _dynamic폴더
	tutorial->animationModel = ObjectFileMakeModelWithMovieClipName(tutorial->of, "mc_animation");
	
	//mc_dom라이브러리 네임을 가진 무비클립로드
	//내부적으로 메모리 생성
	//플래쉬의 라이브러리 _dynamic폴더
	tutorial->domModel = ObjectFileMakeModelWithMovieClipName(tutorial->of, "mc_dom");
	
	
	//최상위 모델에 생성된 모델 붙히기
	//밑에 라인에서 보고싶은 모델을 주석해제 하세요~
	{
		/*sampleModel 1 :센터 정렬한 기본 오브젝트(플래쉬 라이브러리 center폴더)*/
		//ModelAdd(tutorial->topModel, tutorial->model);
		
		/*sampleModel 2 :무비클립(레이아웃만 되어있음) 기본 오브젝트(플래쉬 라이브러리 _dynamic폴더)*/
		//ModelAdd(tutorial->topModel, tutorial->layoutModel);
		
		/*sampleModel 3 :무비클립(에니메이션만 되어있음) 기본 오브젝트(플래쉬 라이브러리 _dynamic폴더)*/
		//ModelAdd(tutorial->topModel, tutorial->animationModel);
		//ModelSetIsLoop(tutorial->animationModel, true);
		//ModelPlay(tutorial->animationModel);
		
		
		/*sampleModel 4 :무비클립(에니메이션및 레이아웃의 DOM구조로 되어있음) 기본 오브젝트(플래쉬 라이브러리 _dynamic폴더)*/
		ModelAdd(tutorial->topModel, tutorial->domModel);
		ModelSetIsLoop(tutorial->domModel, true);
		ModelPlay(tutorial->domModel);
		
		/*오브젝트 파일로 만들어진 모델의 하위모델을 가져오기 위한 인스턴스 네임*/
		unsigned int aniInstanceID = ObjectFileFindInstanceIDWithName(tutorial->of, "id_animation");
		
		tutorial->domChildAniModel = ModelGetChildWithInstanceID(tutorial->domModel, aniInstanceID);
		if(tutorial->domChildAniModel) {
			ModelSetIsLoop(tutorial->domChildAniModel, true);
			ModelPlay(tutorial->domChildAniModel);
		}
		
		aniInstanceID = ObjectFileFindInstanceIDWithName(tutorial->of, "id_sym_win");
		tutorial->domChildModel = ModelGetChildWithInstanceID(tutorial->domModel, aniInstanceID);
		tutorial->domChildModel->ani->aniAbleUserControlMatrix = true;
	}
}

//업데이트
void updateTutorial() {
	//기본 모델 회전시키기
	static float _x;
	static float _y;
	static float _r;
	_r += 0.1;
	_x = sinf(_r) * 100.0;
	_y = cosf(_r) * 100.0;
	ModelSetPosition(tutorial->model, Vector3DInit(_x, _y, 0.0));
	if(tutorial->domChildModel)
		ModelSetPosition(tutorial->domChildModel, Vector3DInit(_y, _x, 0.0));
}

//업데이트 및 드로윙
void renderTutorial() {
	updateTutorial();
	
	//최상위 모델만 드로우 콜해주면 그 하위 모델들도 자동으로 렌더링
	ModelManagerDisplayBegin(tutorial->manager, ModelManagerDisplayMode2D, tutorial->camera, NULL);
	ModelManagerDisplay(tutorial->manager, tutorial->topModel);
	ModelManagerDisplayEnd(tutorial->manager);
}

//끝
void freeTutorial() {
	tutorial->domChildModel = NULL;
	tutorial->domChildAniModel = NULL;
	//ObjectFileMakeModelWithMovieClipName로 생성한 무비클립은 반드시 ObjectFileMadeMovieClipFree로 메모리를 해제 해야 해용~
	//(일단은 이렇게 해놨어요~ModelFree에 넣어야 하는데 ㅜㅜ)
	ObjectFileMadeMovieClipFree(&tutorial->domModel);
	ObjectFileMadeMovieClipFree(&tutorial->animationModel);
	ObjectFileMadeMovieClipFree(&tutorial->layoutModel);
	ObjectFileMadeMovieClipFree(&tutorial->model);
	
	ModelFree(tutorial->topModel);
	free(tutorial->topModel);
	tutorial->model = NULL;
	
	ObjectFileFree(&tutorial->of);
	
	ModelManagerShutdown(tutorial->manager);
	free(tutorial->manager);
	tutorial->manager = NULL;
	
	CameraFree(tutorial->camera);
	free(tutorial->camera);
	tutorial->camera = NULL;
	
	free(tutorial);
	tutorial = NULL;
}
