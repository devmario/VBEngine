#ifndef __MODEL_H__
#define __MODEL_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
#include "../Core/Color.h"
	
#include "../Core/Vector.h"
#include "../Core/Matrix.h"
#include "../Core/Quaternion.h"
#include "../Core/Polygon.h"
	
#include "../../Util/Array.h"
	
#include "Camera.h"
#include "Light.h"
	
#ifdef ___MACSIMULATOR___
	unsigned char lineR;
	unsigned char lineG;
	unsigned char lineB;
	unsigned char lineA;
#endif
	
	
#pragma mark -
#pragma mark Model example
	
#pragma mark -
#pragma mark define
	
	enum {
		ModelManagerDisplayModeCustom =		0x00,
		ModelManagerDisplayMode2D =			0x01,
		ModelManagerDisplayMode3D =			0x02
	};
	typedef unsigned char ModelManagerDisplayMode;
	
	enum {
		TouchTypeBegan =	0x00,
		TouchTypeMove =		0x01,
		TouchTypeEnd =		0x02,
		TouchTypeCancel =	0x03
	};
	typedef unsigned char TouchType;
	
	enum {
		ModelColorModeNone =			0x00,
		ModelColorModeOneColor =		0x01,
		ModelColorModeVertexColor =		0x02
	};
	typedef unsigned char ModelColorMode;
	
	enum {
		ModelCullingModeOff =			0x00,
		ModelCullingModeOn =			0x01,
		ModelCullingModeScreen =		0x02,
		ModelCullingModeBack =			0x04,
		ModelCullingModeFront =			0x08
	};
	typedef unsigned char ModelCullingMode;
	
	//Model의 블렌드 모드
	enum {
		//일반 알파적용된 블렌드
		ModelBlendModeNormal =	0x00,
		//색상더하기(스크린효과) 블렌드
		ModelBlendModeAdd =		0x01,
		//기본블렌드에 알파적용되지않은 블렌드
		ModelBlendModeNoAlpha =	0x02,
		
		ModelBlendModeSubatract = 0x03,
		
		ModelBlendModeDot = 0x04,
		
		ModelBlendModePower = 0x05,
		
		ModelBlendModeInverse = 0x06
	};
	typedef unsigned char ModelBlendMode;
	
	typedef struct Model Model;
	typedef struct ModelManager ModelManager;
	
#pragma mark -
#pragma mark Model event argument struct
	
	typedef struct ModelEventTouchArgument ModelEventTouchArgument;
	struct ModelEventTouchArgument {
		Model* model;
		void* touchID;
		TouchType touchType;
		unsigned char touchTabCount;
		Vector2D touchVector;
		bool isHit;
		bool isChecked;
		bool isDouble;
		Vector3D* hitVector;
		Vector3D* hitVectorGlobal;
		
		Vector3D origin;
		Vector3D direction;
	};
	
	typedef struct ModelEventRenderArgument ModelEventRenderArgument;
	struct ModelEventRenderArgument {
		Model* model;
		bool isHitScreen;
	};
	
#pragma mark -
#pragma mark Model event
	
	typedef struct ModelEventTouch ModelEventTouch;
	struct ModelEventTouch {
		void* userReference;
		ModelEventTouchArgument argument;
		void (*event)(void* userReference, ModelEventTouchArgument argument);
	};
	
	typedef struct ModelEventRender ModelEventRender;
	struct ModelEventRender {
		void* userReference;
		ModelEventRenderArgument argument;
		void (*event)(void* userReference, ModelEventRenderArgument argument);
	};
	
#pragma mark -
#pragma mark ModelManager
	
	struct ModelManager {
		unsigned int width;
		unsigned int height;
		ColorRGBA clearColor;
		ModelManagerDisplayMode displayMode;
		Vector3D* lastBindVertex;
		Vector2D* lastBindTexcoord;
		unsigned int lastBindTexture;
		ColorRGBA* lastBindColor;
		Array* touchArguments;
		Vector3D cameraVector;
		Vector3D cameraDirection;
		Matrix3D projection3D;
		Matrix3D model3D;
		Matrix3D multy3D;
		int view[4];
		float g_frustumPlanes[6][4];
		int drawModelCount;
	};
	
#pragma mark -
#pragma mark Model Struct
	
	typedef struct {
		//ID - MovieClip
		unsigned int instanceID;
		unsigned int libraryID;
		
		//Animation - MovieClip
		bool aniAbleUserControlMatrix;
		bool aniAbleUserControlColor;
		bool aniIsPlay;
		bool aniIsLoop;
		int aniCurFrame;
		int aniTotalFrame;
		bool aniIsUpdateFrame;
		unsigned int* aniChildLength;
		Model*** aniChild;
		Matrix3D** aniMat;
		ColorRGBA** aniColor;
	} ModelAni;
	
	//Model구조체
	struct Model {
		ModelAni* ani;
		
		//렌더링 관련
		unsigned long vertexLength;					//폴리곤 정점 길이
		Vector3D* vertex;							//정점배열
		Vector2D* texcoord;							//텍스처 UV배열
		Vector3D* normal;							//법선배열
		unsigned short polygonLength;
		Polygon3D* polygon;
		unsigned int textureID;						//텍스쳐 아이디
		ModelColorMode colorMode;					//컬러 모드 온,오프
		ColorRGBA* color;							//칼라
		unsigned int mixColorLength;
		ColorRGBA* mixColor;						//트리구조 칼라믹스
		ModelBlendMode blendMode;					//블렌드 모드
		bool isLighting;							//라이트 모드 온,오프
		
		//컬링관련
		ModelCullingMode cullingMode;				//컬링모드
		bool isVisible;								//그리는지 안그리는지 여부
		
		//매트릭스(위치,스케일, 회전등)
		Vector3D position;
		Vector3D scale;
		Vector3D rotate;
		
		Vector3D globalPosition;
		Vector3D maxLengthVertex;
		float globalRadius;
		
		bool isNeedUpdateMatrix;
		bool isNeedUpdateScale;
		bool isNeedUpdateRotate;
		Matrix3D* matrix;							//단일매트릭스
		Matrix3D* matrixGlobal;						//글로벌 매트릭스
		
		//이벤트 관련
		ModelEventTouch touchEvent;					//터치콜백
		ModelEventRender renderEvent;				//렌더콜백
		
		//자식 Model 배열
		Array* child;
		
		//부모 Model
		Model* parent;
		
		//픽킹관련
		unsigned long hitTrianglePolygonLength;		//폴리곤 삼각형 개수
		Vector3D* hitVertex;						//정점배열(이것으로는 그리지않고 픽킹테스트만)
		bool isNeedTouchVector;						//터치포인트가 필요한가의 여부
		bool isAlsoHitTouchVector;					//터치가 히트됬을때만 터치포인트를 줄것인지의 여부
		Vector3D* touchVector;						//터치포인트
		bool isNeedTouchVectorGlobal;				//글로벌 터치포인트가 필요한가의 여부
		bool isAlsoHitTouchVectorGlobal;			//터치가 히트됬을때만 글로벌 터치포인트를 줄것인지의 여부
		Vector3D* touchVectorGlobal;				//글로벌 터치포인트
		
		//마스크
		Model* mask;								//현재 모델의 마지막 마스킹
		bool isMask;								//마스크일경우 true
		bool hasMask;								//마스크가 되어있는경우 true
		unsigned int maskDepth;						//마스크 depth
		bool isRender;
		
		bool isDepthTest;
		bool isTriangleFanMode;
	};
	
#pragma mark -
#pragma mark ModelManager 관리자 시작 종료함수
	
	bool ModelManagerStart(ModelManager* manager, unsigned int width, unsigned int height, ColorRGBA clearColor);
	
	bool ModelManagerShutdown(ModelManager* manager);
	
#pragma mark -
#pragma mark ModelManager 관리자 제어함수
	
	bool ModelManagerSetScreenSize(ModelManager* manager, unsigned int width, unsigned int height);
	
	bool ModelManagerSetClearColor(ModelManager* manager, ColorRGBA clearColor);
	
	bool ModelManagerSetClearColorHex(ModelManager* manager, ColorHexRGBA clearColor);
	
#pragma mark -
#pragma mark ModelManager 관리자 그리기 함수
	
	bool ModelManagerDisplayBegin(ModelManager* manager, ModelManagerDisplayMode displayMode, Camera* camera, Light* light);
	
#ifdef ___MACSIMULATOR___
	bool ModelManagerDisplay(ModelManager* manager, Model* model, bool line);
#else
	bool ModelManagerDisplay(ModelManager* manager, Model* model);
#endif
	
	bool ModelManagerDisplayEnd(ModelManager* manager);
	
#pragma mark -
#pragma mark ModelManager 관리자 드바이스 이벤트 받는 함수
	
	bool ModelManagerTouch(ModelManager* manager,
						   Vector2D touch, 
						   void* touchID, 
						   TouchType touchType, 
						   unsigned char tabCount);
	
#pragma mark -
#pragma mark Model 초기화 함수
	
	bool ModelInitDefault(Model* model);
	
	bool ModelInitWithVertex(Model* model, unsigned long vertexLength, Vector3D* vertex, Vector3D* normal, Vector2D* texcoord, unsigned short polygonLength, Polygon3D* polygon, unsigned int textureID);
	
	void ModelSetVertex(Model* model, Vector3D* vertex, int vertexLength);
	
	void ModelSetHitVertex(Model* model, Vector3D* vertex);
	
#pragma mark -
#pragma mark Model 해제 함수
	
	bool ModelFree(Model* model);
	
#pragma mark -
#pragma mark Model Animation
	
	void ModelAllLoopPlay(Model* model, bool loop);
	void ModelAllPlay(Model* model);
    void ModelAllBlandMode(Model* model, ModelBlendMode blendMode);
	void ModelAllVisible(Model* model, bool visible);
    void ModelAllGoToAndPlay(Model* model, int frame);
	void ModelPlay(Model* model);
	bool ModelIsPlaying(Model *model);
	void ModelGoToAndPlay(Model* model, int frame);
	
	void ModelStop(Model* model);
	void ModelGoToAndStop(Model* model, int frame);
	
	void ModelSetIsLoop(Model* model, bool isLoop);
	
	Model* ModelGetChildWithInstanceID(Model* model, unsigned int instanceID);
	
#pragma mark -
#pragma mark Model 색상
	
	bool ModelSetColor(Model* model, ColorRGBA color);
	
	bool ModelSetColorHex(Model* model, ColorHexRGBA color);
	
	bool ModelSetColorVertex(Model* model, ColorRGBA* color, unsigned int colorLength);
	
	ColorRGBA* ModelGetColor(Model* model);
	
#pragma mark -
#pragma mark Model visible 모드
	
	bool ModelSetIsVisible(Model* model, bool visible);
	
	bool ModelGetIsVisible(Model* model);
	
#pragma mark -
#pragma mark Model 블렌드 모드
	
	bool ModelSetBlendMode(Model* model, ModelBlendMode blendMode);
	
	ModelBlendMode ModelGetBlendMode(Model* model);
	
#pragma mark -
#pragma mark Model 컬링모드
	
	bool ModelSetCullingMode(Model* model, ModelCullingMode cullingMode);
	
	ModelCullingMode ModelGetCullingMode(Model* model);
	
#pragma mark -
#pragma mark Model 라이트모드
	
	bool ModelSetIsLighting(Model* model, bool lighting);
	
	bool ModelGetIsLighting(Model* model);
	
#pragma mark -
#pragma mark Model에 Model 붙히기
	
	bool ModelAdd(Model* model, Model* child);
	
	bool ModelAddAt(Model* model, Model* child, unsigned int index);
	
#pragma mark -
#pragma mark 붙어있는 Model 제거하기
	
	bool ModelRemove(Model* model, Model* child);
	
	Model* ModelRemoveAt(Model* model, unsigned int index);
	
#pragma mark -
#pragma mark Child Model, Parent Model
	
	bool ModelIsChild(Model* model, Model* child);
	
	Model* ModelGetChildAt(Model* model, unsigned int index);
	
	signed long ModelGetAtChild(Model* model, Model* child);
	
	unsigned int ModelGetChildLength(Model* model);
	
	Model* ModelGetParent(Model* model);
	
#pragma mark -
#pragma mark Model 매트릭스
	
	bool ModelSetMatrix(Model* model, Matrix3D matrix);
	
	Matrix3D* ModelGetMatrix(Model* model);
	
	Matrix3D* ModelMultyMatrix(Model* model, Matrix3D matrix);
	
	Matrix3D* ModelGetMatrixGlobal(Model* model);
	
	void ModelUpdateMatrix(Model* model);
	
#pragma mark -
#pragma mark Model 충돌
	
	bool ModelGetIsVertexHitLineDirection(Model* model, Vector3D origin, Vector3D direction, Vector3D* hitVector, Vector3D* hitVectorGlobal);
	
#pragma mark -
#pragma mark Model 위치
	
	bool ModelSetPosition(Model* model, Vector3D position);
	
	bool ModelAddPosition(Model* model, Vector3D position);
	
	Vector3D ModelGetPosition(Model* model);
	
#pragma mark -
#pragma mark Model 스케일
	
	bool ModelSetScale(Model* model, Vector3D scale);
	
	bool ModelAddScale(Model* model, Vector3D scale);
	
	Vector3D ModelGetScale(Model* model);
	
#pragma mark -
#pragma mark Model 회전
	
	bool ModelSetRotate(Model* model, Vector3D rotate);
	
	bool ModelAddRotate(Model* model, Vector3D rotate);
	
	Vector3D ModelGetRotate(Model* model);
	
#pragma mark cull
	
	void ModelCullParent(Model* model);
	
#pragma mark -
#pragma mark Model 마스킹
	
	bool ModelSetMask(Model* model, Model* mask);
	
	bool ModelSetMaskDetail(Model* model, Model* mask, unsigned int maskDepth);
	
	Model* ModelGetMask(Model* model);
	
	Model* ModelGetTopMaskingModel(Model* model);
	
	bool ModelRemoveMask(Model* model);
	
	bool ModelRemoveMaskDetail(Model* model, Model* mask);
	
#pragma mark -
#pragma mark Model 이벤트
	
	ModelEventRender ModelEventRenderInit(void* userReference, ModelEventRenderArgument argument, void (*event)(void* userReference, ModelEventRenderArgument argument));
	ModelEventTouch ModelEventTouchTinyInit(void* userReference, void (*event)(void* userReference, ModelEventTouchArgument argument));
	ModelEventTouch ModelEventTouchInit(void* userReference, ModelEventTouchArgument argument, void (*event)(void* userReference, ModelEventTouchArgument argument));
										
	bool ModelAddEventTouch(Model* model, ModelEventTouch event, 
							unsigned long hitTrianglePolygonLength, Vector3D* hitVertex,
							bool isNeedTouchVector, bool isAlsoHitTouchVector, 
							bool isNeedTouchVectorGlobal, bool isAlsoHitTouchVectorGlobal);
	
	bool ModelAddEventTouchAlsoIsHit(Model* model, ModelEventTouch event, unsigned long hitTrianglePolygonLength, Vector3D* hitVertex);
	
	bool ModelAddEventTouchNeedVector(Model* model, ModelEventTouch event, unsigned long hitTrianglePolygonLength, Vector3D* hitVertex);
	
	bool ModelAddEventTouchNeedGlobalVector(Model* model, ModelEventTouch event, unsigned long hitTrianglePolygonLength, Vector3D* hitVertex);
	
	bool ModelRemoveEventTouch(Model* model);
	
	bool ModelAddEventRender(Model* model, ModelEventRender event);
	
	bool ModelRemoveEventRender(Model* model);
	
#ifdef __cplusplus
}
#endif

#endif