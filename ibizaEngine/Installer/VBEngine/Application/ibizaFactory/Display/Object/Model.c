#include "Model.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifdef ___IPHONE___
#include <OpenGLES/ES1/gl.h>
#endif
#ifdef ___MAC___
#include <OpenGL/OpenGL.h>
#endif

#include "PNGDecoder.h"

#pragma mark -
#pragma mark Model 초기화 함수

bool ModelInitDefault(Model* model) {
	return ModelInitWithVertex(model, 0, NULL, NULL, NULL, 0, NULL, 0);
}

bool ModelInitWithVertex(Model* model, unsigned long vertexLength, Vector3D* vertex, Vector3D* normal, Vector2D* texcoord, unsigned short polygonLength, Polygon3D* polygon, unsigned int textureID) {
	model->position = Vector3DInit(0.0, 0.0, 0.0);
	model->scale = Vector3DInit(1.0, 1.0, 1.0);
	model->rotate = Vector3DInit(0.0, 0.0, 0.0);
	
	model->globalPosition = Vector3DInit(0.0, 0.0, 0.0);
	
	model->globalRadius = 0.0;
	
	model->mixColorLength = 1;
	model->mixColor = malloc(sizeof(ColorRGBA));
	*model->mixColor = ColorRGBAInit(0xFF, 0xFF, 0xFF, 0xFF);
	
	ModelSetVertex(model, vertex, vertexLength);
	model->texcoord = texcoord;
	model->normal = normal;
	model->polygonLength = polygonLength * 3;
	model->polygon = polygon;
	model->textureID = textureID;
	model->colorMode = ModelColorModeOneColor;
	model->color = malloc(sizeof(ColorRGBA));
	*model->color = ColorRGBAInit(0xFF, 0xFF, 0xFF, 0xFF);
	model->blendMode = ModelBlendModeNormal;
	model->isLighting = false;
	
	model->cullingMode = ModelCullingModeOn | ModelCullingModeScreen | ModelCullingModeBack;
	model->isVisible = true;
	
	model->touchEvent.event = NULL;
	model->renderEvent.event = NULL;
	model->touchEvent.userReference = NULL;
	model->renderEvent.userReference = NULL;
	
	model->matrix = malloc(sizeof(Matrix3D));
	*model->matrix = Matrix3DLoadIdentity();
	model->matrixGlobal = malloc(sizeof(Matrix3D));
	*model->matrix = Matrix3DLoadIdentity();
	
	model->child = ArrayInit();
	model->parent = NULL;
	
	model->hitTrianglePolygonLength = 0;
	model->hitVertex = NULL;
	model->isNeedTouchVector = false;
	model->isAlsoHitTouchVector = false;
	model->touchVector = NULL;
	model->isNeedTouchVectorGlobal = false;
	model->isAlsoHitTouchVectorGlobal = false;
	model->touchVectorGlobal = NULL;
	
	model->mask = NULL;
	model->isMask = false;
	model->hasMask = false;
	model->maskDepth = 0;
	
	model->isDepthTest = false;
	model->isTriangleFanMode = false;
	
	return true;
}

void ModelSetVertex(Model* model, Vector3D* vertex, int vertexLength) {
	model->vertexLength = vertexLength;
	model->vertex = vertex;
	float radius = 0.0;
	for(int i = 0; i < model->vertexLength; i++) {
		float len = Vector3DLength(model->vertex[i]);
		if(len > radius) {
			model->maxLengthVertex = model->vertex[i];
			radius = len;
		}
	}
}

#pragma mark -
#pragma mark Model 해제 함수

bool ModelFree(Model* model) {
	if(model->parent) {
		ModelRemove(model->parent, model);
		model->parent = NULL;
	}
	
	while(ArrayLength(model->child)) {
		Model* child = (Model*)ArrayObjectAtIndex(model->child, 0);
		ModelRemove(model, child);
		child->parent = NULL;
	}
	ArrayFree(&model->child);
	
	free(model->color);
	model->color = NULL;
	
	free(model->matrix);
	model->matrix = NULL;
	
	return true;
}

#pragma mark -
#pragma mark Model 색상

bool ModelSetColor(Model* model, ColorRGBA color) {
	if(model->colorMode == ModelColorModeOneColor) {
		if(model->color)
			free(model->color);
		if(model->mixColor)
			free(model->mixColor);
		model->mixColorLength = 1;
		model->mixColor = calloc(1, sizeof(ColorRGBA));
		//*model->mixColor = ColorRGBAInit(0xFF, 0xFF, 0xFF, 0xFF);
		model->color = calloc(1, sizeof(ColorRGBA));
		*model->color = color;
		return true;
	}
	return false;
}

bool ModelSetColorHex(Model* model, ColorHexRGBA color) {
	if(model->colorMode == ModelColorModeOneColor) {
		if(model->color)
			free(model->color);
		if(model->mixColor)
			free(model->mixColor);
		model->mixColorLength = 1;
		model->mixColor = calloc(1, sizeof(ColorRGBA));
		//*model->mixColor = ColorRGBAInit(0xFF, 0xFF, 0xFF, 0xFF);
		model->color = calloc(1, sizeof(ColorRGBA));
		*model->color = ColorHexRGBAToRGBAColor(color);
		return true;
	}
	return false;
}

bool ModelSetColorVertex(Model* model, ColorRGBA* color, unsigned int colorLength) {
	if(model->colorMode == ModelColorModeVertexColor) {
		if(model->color)
			free(model->color);
		if(model->mixColor)
			free(model->mixColor);
		model->mixColorLength = colorLength;
		model->mixColor = calloc(colorLength, sizeof(ColorRGBA));
		model->color = calloc(colorLength, sizeof(ColorRGBA));
		int i;
		for(i = 0; i < colorLength; i++) {
			model->color[i] = color[i];
			//model->mixColor[i] = ColorRGBAInit(0xFF, 0xFF, 0xFF, 0xFF);
		}
		return true;
	}
	return false;
}

ColorRGBA* ModelGetColor(Model* model) {
	return model->color;
}

#pragma mark -
#pragma mark Model visible 모드

bool ModelSetIsVisible(Model* model, bool visible) {
	if(model->isVisible != visible) {
		model->isVisible = visible;
		return true;
	}
	return false;
}

bool ModelGetIsVisible(Model* model) {
	return model->isVisible;
}

#pragma mark -
#pragma mark Model 블렌드 모드

bool ModelSetBlendMode(Model* model, ModelBlendMode blendMode) {
	if(model->blendMode != blendMode) {
		model->blendMode = blendMode;
		return true;
	}
	return false;
}

ModelBlendMode ModelGetBlendMode(Model* model) {
	return model->blendMode;
}

#pragma mark -
#pragma mark Model 컬링모드

bool ModelSetCullingMode(Model* model, ModelCullingMode cullingMode) {
	if(model->cullingMode != cullingMode) {
		model->cullingMode = cullingMode;
		return true;
	}
	return false;
}

ModelCullingMode ModelGetCullingMode(Model* model) {
	return model->cullingMode;
}

#pragma mark -
#pragma mark Model 라이트모드

bool ModelSetIsLighting(Model* model, bool lighting) {
	model->isLighting = lighting;
	return true;
}

bool ModelGetIsLighting(Model* model) {
	return model->isLighting;
}

#pragma mark -
#pragma mark Model 마스킹

bool ModelSetMask(Model* model, Model* mask) {
	return ModelSetMaskDetail(model, mask, 0);
}

bool ModelSetMaskDetail(Model* model, Model* mask, unsigned int maskDepth) {
	if(mask) {
		model->mask = mask;		//인자가 들어올경우 마스크 셋팅
		mask = NULL;			//마스크 인자를 NULL로하여 자식 스프라이트 에게 인자를 전달 안하도록함
	} else {
		model->mask = NULL;
	}
	if(model->mask) {			//마스크가 셋팅되어있는경우(톱마스크+서브마스크) 마스크의maskPass 설정후 스프라이트에 전달할 maskPass +1
		model->mask->isMask = true;
		model->mask->maskDepth = maskDepth;
		
		maskDepth++;
	}
	model->maskDepth = maskDepth;
	model->hasMask = true;
	for(int i = 0; i < model->child->length; i++)
		ModelSetMaskDetail(ArrayObjectAtIndex(model->child, i), mask, maskDepth);
	return true;
}

Model* ModelGetMask(Model* model) {
	if(model) {
		if(!model->mask) {
			return ModelGetMask(model->parent);
		} else {
			return model->mask;
		}
	} else {
		return NULL;
	}
}

Model* ModelGetTopMaskingModel(Model* model) {
	if(!model->mask) {
		return ModelGetTopMaskingModel(model->parent);
	} else {
		return model;
	}
}

bool ModelRemoveMask(Model* model) {
	return ModelRemoveMaskDetail(model, model->mask);
}

bool ModelRemoveMaskDetail(Model* model, Model* mask) {
	int i;
	model->hasMask = false;
	model->maskDepth = 0;
	model->mask = NULL;
	for(i = 0; i < model->child->length; i++)
		ModelRemoveMaskDetail(ArrayObjectAtIndex(model->child, i), mask);
	return true;
}

void ModelAllLoopPlay(Model* m) {
	if(m->ani) {
		if(m->ani->aniTotalFrame > 1) {
			ModelSetIsLoop(m, true);
			ModelPlay(m);
		}
		if(m->ani->aniTotalFrame) {
			for(int i = 0; i < m->ani->aniTotalFrame; i++) {
				if(m->ani->aniChildLength) {
					for(int j = 0; j < m->ani->aniChildLength[i]; j++) {
						ModelAllLoopPlay(m->ani->aniChild[i][j]);
					}
				}
			}
		}
	}
}

Model* ModelInitPNG(const char* path) {
	Model* model = calloc(1, sizeof(Model));
	glEnable(GL_TEXTURE_2D);
	GLuint t_id;
	glGenTextures(1, &t_id);
	FILE* file = fopen(path, "rb");
	int size = fseek(file, 0, SEEK_END);
	fseek(file, 0, SEEK_SET);
	glBindTexture(GL_TEXTURE_2D, t_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	unsigned long w, h;
	unsigned char c, b;
	unsigned char* data = PNGReader(file, size, &w, &h, &c, &b);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	Vector3D* vec = calloc(4, sizeof(Vector3D));
	vec[1].x = (float)w;
	vec[2].y = (float)h;
	vec[3].x = (float)w;
	vec[3].y = (float)h;
	Vector2D* tex = calloc(4, sizeof(Vector2D));
	tex[1].x = 1.0;
	tex[2].y = 1.0;
	tex[3].x = 1.0;
	tex[3].y = 1.0;
	ModelInitWithVertex(model, 4, vec, NULL, tex, 0, NULL, t_id);
	return model;
}

void ModelPNGSetAABB(Model* model, float x1, float y1, float x2, float y2) {
	model->vertex[0].x = x1;
	model->vertex[0].y = y1;
	
	model->vertex[1].x = x2;
	model->vertex[1].y = y1;
	
	model->vertex[2].x = x1;
	model->vertex[2].y = y2;
	
	model->vertex[3].x = x2;
	model->vertex[3].y = y2;
}

void ModelFreePNG(Model** model) {
	glDeleteTextures(1, &(*model)->textureID);
	free((*model)->vertex);
	free((*model)->texcoord);
	ModelFree(*model);
	free(*model);
}

