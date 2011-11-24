#include "Model.h"

#include <math.h>
#include <stdlib.h>
#ifdef ___IPHONE___
#include <OpenGLES/ES1/gl.h>
#endif
#ifdef ___MAC___
#include <OpenGL/OpenGL.h>
#endif

#pragma mark -
#pragma mark ModelManager 관리자 시작 종료함수

bool ModelManagerStart(ModelManager* manager, unsigned int width, unsigned int height, ColorRGBA clearColor) {
	if(!ModelManagerSetScreenSize(manager, width, height))
		return false;
	if(!ModelManagerSetClearColor(manager, clearColor))
		return false;
	glEnableClientState(GL_VERTEX_ARRAY);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LESS);
	glDisable(GL_DEPTH_TEST);
	manager->touchArguments = ArrayInit();
	
	int maxSize;
	int maxUnit;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxUnit);
	
	return true;
}

bool ModelManagerShutdown(ModelManager* manager) {
	ArrayFree(&manager->touchArguments);
	return true;
}

#pragma mark -
#pragma mark ModelManager 관리자 제어함수

bool ModelManagerSetScreenSize(ModelManager* manager, unsigned int width, unsigned int height) {
	manager->width = width;
	manager->height = height;
	
	glViewport(0, 0, width, height);
	glGetIntegerv(GL_VIEWPORT, manager->view);
	
	float near = 1.0;
	float far = 30000.0;
	float fovy = 60.0;
	float aspect = (float)width / (float)height;
	float sine, cotangent, deltaZ;
	float radians = fovy / 2 * M_PI / 180;
	
	deltaZ = far - near;
	sine = sin(radians);
	if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
		return false;
	}
	cotangent = cosf(radians) / sine;
	manager->projection3D = Matrix3DLoadIdentity();
	
	manager->projection3D.m11 = cotangent / aspect;
	manager->projection3D.m22 = cotangent;
	manager->projection3D.m33 = -(far + near) / deltaZ;
	manager->projection3D.m34 = -1;
	manager->projection3D.m43 = -2 * near * far / deltaZ;
	manager->projection3D.m44 = 0;
	
	manager->model3D = Matrix3DLoadIdentity();
	
	manager->multy3D = Matrix3DMultiply(manager->projection3D, manager->model3D);
	manager->multy3D = Matrix3DInverte(manager->multy3D);
	
	return true;
}

bool ModelManagerSetClearColor(ModelManager* manager, ColorRGBA clearColor) {
	manager->clearColor = clearColor;
	glClearColor(clearColor.r / 255.0, clearColor.g / 255.0, clearColor.b / 255.0, clearColor.a / 255.0);
	return true;
}

bool ModelManagerSetClearColorHex(ModelManager* manager, ColorHexRGBA clearColor) {
	ColorRGBA color = ColorHexRGBAToRGBAColor(clearColor);
	ModelManagerSetClearColor(manager, color);
	return true;
}

#pragma mark -
#pragma mark ModelManager 관리자 그리기 함수
bool ModelManagerDisplayBegin(ModelManager* manager, ModelManagerDisplayMode displayMode, Camera* camera, Light* light) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	manager->drawModelCount = 0;
	if(manager->displayMode != displayMode) {
		manager->displayMode = displayMode;
		if(displayMode == ModelManagerDisplayMode3D) {
			glMatrixMode(GL_PROJECTION);
			glMultMatrixf((float*)&manager->projection3D);
		} else if(displayMode == ModelManagerDisplayMode2D) {
			// switch to projection mode
			glMatrixMode(GL_PROJECTION);
			// save previous matrix which contains the 
			//settings for the perspective projection
			glPushMatrix();
			// reset matrix
			glLoadIdentity();
			// set a 2D orthographic projection
			
#ifdef ___IPHONE___
			glOrthof(0, (float)manager->width, (float)manager->height, 0, 1.0, 30000.0);
#endif
#ifdef ___MAC___
			glOrtho(0, (float)manager->width, (float)manager->height, 0, 1.0, 30000.0);
#endif
			// invert the y axis, down is positive
			glScalef(1, -1, 1);
			// mover the origin from the bottom left corner
			// to the upper left corner
			glTranslatef((float)manager->width * 0.5, -(float)manager->height * 0.5, 0);
		}
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	float p[16];   // projection matrix
	float mv[16];  // model-view matrix
	float mvp[16]; // model-view-projection matrix
	float t;
	
	glGetFloatv( GL_PROJECTION_MATRIX, p );
	glGetFloatv( GL_MODELVIEW_MATRIX, mv );
	
	//
	// Concatenate the projection matrix and the model-view matrix to produce 
	// a combined model-view-projection matrix.
	//
	
	mvp[ 0] = mv[ 0] * p[ 0] + mv[ 1] * p[ 4] + mv[ 2] * p[ 8] + mv[ 3] * p[12];
	mvp[ 1] = mv[ 0] * p[ 1] + mv[ 1] * p[ 5] + mv[ 2] * p[ 9] + mv[ 3] * p[13];
	mvp[ 2] = mv[ 0] * p[ 2] + mv[ 1] * p[ 6] + mv[ 2] * p[10] + mv[ 3] * p[14];
	mvp[ 3] = mv[ 0] * p[ 3] + mv[ 1] * p[ 7] + mv[ 2] * p[11] + mv[ 3] * p[15];
	
	mvp[ 4] = mv[ 4] * p[ 0] + mv[ 5] * p[ 4] + mv[ 6] * p[ 8] + mv[ 7] * p[12];
	mvp[ 5] = mv[ 4] * p[ 1] + mv[ 5] * p[ 5] + mv[ 6] * p[ 9] + mv[ 7] * p[13];
	mvp[ 6] = mv[ 4] * p[ 2] + mv[ 5] * p[ 6] + mv[ 6] * p[10] + mv[ 7] * p[14];
	mvp[ 7] = mv[ 4] * p[ 3] + mv[ 5] * p[ 7] + mv[ 6] * p[11] + mv[ 7] * p[15];
	
	mvp[ 8] = mv[ 8] * p[ 0] + mv[ 9] * p[ 4] + mv[10] * p[ 8] + mv[11] * p[12];
	mvp[ 9] = mv[ 8] * p[ 1] + mv[ 9] * p[ 5] + mv[10] * p[ 9] + mv[11] * p[13];
	mvp[10] = mv[ 8] * p[ 2] + mv[ 9] * p[ 6] + mv[10] * p[10] + mv[11] * p[14];
	mvp[11] = mv[ 8] * p[ 3] + mv[ 9] * p[ 7] + mv[10] * p[11] + mv[11] * p[15];
	
	mvp[12] = mv[12] * p[ 0] + mv[13] * p[ 4] + mv[14] * p[ 8] + mv[15] * p[12];
	mvp[13] = mv[12] * p[ 1] + mv[13] * p[ 5] + mv[14] * p[ 9] + mv[15] * p[13];
	mvp[14] = mv[12] * p[ 2] + mv[13] * p[ 6] + mv[14] * p[10] + mv[15] * p[14];
	mvp[15] = mv[12] * p[ 3] + mv[13] * p[ 7] + mv[14] * p[11] + mv[15] * p[15];
	
	//
	// Extract the frustum's right clipping plane and normalize it.
	//
	
	
	manager->g_frustumPlanes[0][0] = mvp[ 3] - mvp[ 0];
	manager->g_frustumPlanes[0][1] = mvp[ 7] - mvp[ 4];
	manager->g_frustumPlanes[0][2] = mvp[11] - mvp[ 8];
	manager->g_frustumPlanes[0][3] = mvp[15] - mvp[12];
	
	t = (float) sqrt(manager->g_frustumPlanes[0][0] * manager->g_frustumPlanes[0][0] + 
					 manager->g_frustumPlanes[0][1] * manager->g_frustumPlanes[0][1] + 
					 manager->g_frustumPlanes[0][2] * manager->g_frustumPlanes[0][2] );
	
	manager->g_frustumPlanes[0][0] /= t;
	manager->g_frustumPlanes[0][1] /= t;
	manager->g_frustumPlanes[0][2] /= t;
	manager->g_frustumPlanes[0][3] /= t;
	
	//
	// Extract the frustum's left clipping plane and normalize it.
	//
	
	manager->g_frustumPlanes[1][0] = mvp[ 3] + mvp[ 0];
	manager->g_frustumPlanes[1][1] = mvp[ 7] + mvp[ 4];
	manager->g_frustumPlanes[1][2] = mvp[11] + mvp[ 8];
	manager->g_frustumPlanes[1][3] = mvp[15] + mvp[12];
	
	t = (float) sqrt(manager->g_frustumPlanes[1][0] * manager->g_frustumPlanes[1][0] + 
					 manager->g_frustumPlanes[1][1] * manager->g_frustumPlanes[1][1] + 
					 manager->g_frustumPlanes[1][2] * manager->g_frustumPlanes[1][2] );
	
	manager->g_frustumPlanes[1][0] /= t;
	manager->g_frustumPlanes[1][1] /= t;
	manager->g_frustumPlanes[1][2] /= t;
	manager->g_frustumPlanes[1][3] /= t;
	
	//
	// Extract the frustum's bottom clipping plane and normalize it.
	//
	
	manager->g_frustumPlanes[2][0] = mvp[ 3] + mvp[ 1];
	manager->g_frustumPlanes[2][1] = mvp[ 7] + mvp[ 5];
	manager->g_frustumPlanes[2][2] = mvp[11] + mvp[ 9];
	manager->g_frustumPlanes[2][3] = mvp[15] + mvp[13];
	
	t = (float) sqrt(manager->g_frustumPlanes[2][0] * manager->g_frustumPlanes[2][0] + 
					 manager->g_frustumPlanes[2][1] * manager->g_frustumPlanes[2][1] + 
					 manager->g_frustumPlanes[2][2] * manager->g_frustumPlanes[2][2] );
	
	manager->g_frustumPlanes[2][0] /= t;
	manager->g_frustumPlanes[2][1] /= t;
	manager->g_frustumPlanes[2][2] /= t;
	manager->g_frustumPlanes[2][3] /= t;
	
	//
	// Extract the frustum's top clipping plane and normalize it.
	//
	
	manager->g_frustumPlanes[3][0] = mvp[ 3] - mvp[ 1];
	manager->g_frustumPlanes[3][1] = mvp[ 7] - mvp[ 5];
	manager->g_frustumPlanes[3][2] = mvp[11] - mvp[ 9];
	manager->g_frustumPlanes[3][3] = mvp[15] - mvp[13];
	
	t = (float) sqrt(manager->g_frustumPlanes[3][0] * manager->g_frustumPlanes[3][0] + 
					 manager->g_frustumPlanes[3][1] * manager->g_frustumPlanes[3][1] + 
					 manager->g_frustumPlanes[3][2] * manager->g_frustumPlanes[3][2] );
	
	manager->g_frustumPlanes[3][0] /= t;
	manager->g_frustumPlanes[3][1] /= t;
	manager->g_frustumPlanes[3][2] /= t;
	manager->g_frustumPlanes[3][3] /= t;
	
	//
	// Extract the frustum's far clipping plane and normalize it.
	//
	
	manager->g_frustumPlanes[4][0] = mvp[ 3] - mvp[ 2];
	manager->g_frustumPlanes[4][1] = mvp[ 7] - mvp[ 6];
	manager->g_frustumPlanes[4][2] = mvp[11] - mvp[10];
	manager->g_frustumPlanes[4][3] = mvp[15] - mvp[14];
	
	t = (float) sqrt(manager->g_frustumPlanes[4][0] * manager->g_frustumPlanes[4][0] +  
					 manager->g_frustumPlanes[4][1] * manager->g_frustumPlanes[4][1] + 
					 manager->g_frustumPlanes[4][2] * manager->g_frustumPlanes[4][2] );
	
	manager->g_frustumPlanes[4][0] /= t;
	manager->g_frustumPlanes[4][1] /= t;
	manager->g_frustumPlanes[4][2] /= t;
	manager->g_frustumPlanes[4][3] /= t;
	manager->drawModelCount = 0;
	//
	// Extract the frustum's near clipping plane and normalize it.
	//
	
	manager->g_frustumPlanes[5][0] = mvp[ 3] + mvp[ 2];
	manager->g_frustumPlanes[5][1] = mvp[ 7] + mvp[ 6];
	manager->g_frustumPlanes[5][2] = mvp[11] + mvp[10];
	manager->g_frustumPlanes[5][3] = mvp[15] + mvp[14];
	
	t = (float) sqrt(manager->g_frustumPlanes[5][0] * manager->g_frustumPlanes[5][0] + 
					 manager->g_frustumPlanes[5][1] * manager->g_frustumPlanes[5][1] + 
					 manager->g_frustumPlanes[5][2] * manager->g_frustumPlanes[5][2] );
	
	manager->g_frustumPlanes[5][0] /= t;
	manager->g_frustumPlanes[5][1] /= t;
	manager->g_frustumPlanes[5][2] /= t;
	manager->g_frustumPlanes[5][3] /= t;
	
	for(int i = 0; i < manager->touchArguments->length; i++) {
		ModelEventTouchArgument* touchArgument = ArrayObjectAtIndex(manager->touchArguments, i);
		
		float div = manager->multy3D.m33 == 0 ? 1.0 : manager->multy3D.m33;
		
		Vector4D screenVector = Vector4DInit((((touchArgument->touchVector.x - manager->view[0]) / manager->view[2]) * 2) - 1, 
											 
											 (((manager->view[3] - touchArgument->touchVector.y - manager->view[1]) / manager->view[3]) * 2) - 1, 
											 
											 -(manager->multy3D.m13 * touchArgument->touchVector.x + 
											   manager->multy3D.m23 * touchArgument->touchVector.y + 
											   manager->multy3D.m43) / div,
											 
											 1.0);
		
		Vector4D object4D = Matrix3DMultiplyVector4D(manager->multy3D, screenVector);
		Vector3D object3D;
		if(object4D.w != 0.0) {
			object3D = Vector3DInit(object4D.x / object4D.w, 
									object4D.y / object4D.w, 
									object4D.z / object4D.w);
		} else {
			object3D = Vector3DInit(0.0, 0.0, 0.0);
		}
		
		touchArgument->origin = Vector3DInit(0.0, 0.0, 0.0);
		touchArgument->direction = Vector3DSubtract(object3D, touchArgument->origin);
		touchArgument->direction = Vector3DNormal(touchArgument->direction);
	}
	glMultMatrixf((float*)camera->matrix);
	
	
	return true;
}

#ifdef ___MACSIMULATOR___
bool ModelManagerDisplay(ModelManager* manager, Model* model, bool line) {
#else
bool ModelManagerDisplay(ModelManager* manager, Model* model) {
#endif
	if(model->ani) {
		if(model->ani->aniIsPlay) {
			if(model->ani->aniCurFrame < model->ani->aniTotalFrame - 1) {
				model->ani->aniCurFrame++;
				model->ani->aniIsUpdateFrame = true;
			} else {
				if(model->ani->aniIsLoop) {
					model->ani->aniCurFrame = 0;
					model->ani->aniIsUpdateFrame = true;
				} else {
					model->ani->aniIsUpdateFrame = true;
					model->ani->aniIsPlay = false;
				}
				
			}
		}
		
		if(model->ani->aniIsUpdateFrame) {
			//모든 에니메이션 모델 삭제
			int i;
			for(i = 0; i < model->child->length; i++) {
				Model* child = ArrayObjectAtIndex(model->child, i);
				if(child->ani) {
					if(child->ani->instanceID) {
						ModelRemoveAt(model, i);
						i--;
					}
				}
			}
			
			//현제 프레임의 하위모델 셋팅후 매트릭스,칼라 셋팅
			if(model->ani->aniChildLength) {
				for(i = 0; i < model->ani->aniChildLength[model->ani->aniCurFrame]; i++) {
					ModelAddAt(model, model->ani->aniChild[model->ani->aniCurFrame][i], 0);
					if(!model->ani->aniChild[model->ani->aniCurFrame][i]->ani->aniAbleUserControlMatrix)
						ModelSetMatrix(model->ani->aniChild[model->ani->aniCurFrame][i], model->ani->aniMat[model->ani->aniCurFrame][i]);
					if(!model->ani->aniChild[model->ani->aniCurFrame][i]->ani->aniAbleUserControlColor)
						ModelSetColor(model->ani->aniChild[model->ani->aniCurFrame][i], model->ani->aniColor[model->ani->aniCurFrame][i]);
				}
			}
			
			model->ani->aniIsUpdateFrame = false;
		}
	}
	
	glPushMatrix();
	
	ModelUpdateMatrix(model);
	
	glMultMatrixf((float*)model->matrix);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*)model->matrixGlobal);
	
	model->globalPosition = Matrix3DMultiplyVector3D(*model->matrixGlobal, Vector3DInit(0.0, 0.0, 0.0));
	
	model->isRender = true;
	
	if(model->vertex) {
		Vector3D scale = Matrix3DGetScale(*model->matrixGlobal);
		Vector3D vec = Vector3DInit(model->maxLengthVertex.x * scale.x,
									model->maxLengthVertex.y * scale.y,
									model->maxLengthVertex.z * scale.z);
		model->globalRadius = Vector3DLength(vec);
		for(int i = 0; i < 6; i++ ) {
			if( manager->g_frustumPlanes[i][0] * model->globalPosition.x +
				manager->g_frustumPlanes[i][1] * model->globalPosition.y +
				manager->g_frustumPlanes[i][2] * model->globalPosition.z +
			    manager->g_frustumPlanes[i][3] <= -model->globalRadius ) {
				model->isRender = false;
			}
		}
	}
	
	if(model->isRender) {
		
#ifdef ___MACSIMULATOR___
		if(model->mask) {
			ModelManagerDisplay(manager, model->mask, line);
		}
#else
		if(model->mask) {
			ModelManagerDisplay(manager, model->mask);
		}
#endif
		
		//if(model->renderEvent.event) {
		//	model->renderEvent.event(model->renderEvent.userReference, model->renderEvent.argument);
		//}
		
		if(model->touchEvent.event) {
			for(int i = 0; i < manager->touchArguments->length; i++) {
				ModelEventTouchArgument* touchArgumentCurrent = manager->touchArguments->data[i];
				bool hit = ModelGetIsVertexHitLineDirection(model, 
															touchArgumentCurrent->origin, touchArgumentCurrent->direction, 
															model->touchVector, model->touchVectorGlobal);
				
				model->touchEvent.argument.hitVector = model->touchVector;
				model->touchEvent.argument.hitVectorGlobal = model->touchVectorGlobal;
				model->touchEvent.argument.isHit = hit;
				model->touchEvent.argument.model = model;
				model->touchEvent.argument.touchID = touchArgumentCurrent->touchID;
				model->touchEvent.argument.touchTabCount = touchArgumentCurrent->touchTabCount;
				model->touchEvent.argument.touchType = touchArgumentCurrent->touchType;
				model->touchEvent.event(model->touchEvent.userReference, model->touchEvent.argument);
				touchArgumentCurrent->isChecked = true;
			}
		}
		
		Model* _parent = ModelGetParent(model);
		for(int i = 0; i < model->mixColorLength; i++) {
			if(_parent) {
				model->mixColor[i].r = (unsigned char)(((float)_parent->mixColor[0].r / (float)0xFF) * (float)model->color[i].r);
				model->mixColor[i].g = (unsigned char)(((float)_parent->mixColor[0].g / (float)0xFF) * (float)model->color[i].g);
				model->mixColor[i].b = (unsigned char)(((float)_parent->mixColor[0].b / (float)0xFF) * (float)model->color[i].b);
				model->mixColor[i].a = (unsigned char)(((float)_parent->mixColor[0].a / (float)0xFF) * (float)model->color[i].a);
			} else {
				model->mixColor[i] = model->color[0];
			}
		}
		
		if(model->vertex) {
			
			//if(manager->lastBindVertex != model->vertex) {
				glVertexPointer(3, GL_FLOAT, 0, model->vertex);
			//	manager->lastBindVertex = model->vertex;
			//}
			
			if(model->texcoord) {
				glEnable(GL_TEXTURE_2D);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				if(manager->lastBindTexcoord != model->texcoord) {
					glTexCoordPointer(2, GL_FLOAT, 0, model->texcoord);
					manager->lastBindTexcoord = model->texcoord;
				}
				if(manager->lastBindTexture != model->textureID) {
					glBindTexture(GL_TEXTURE_2D, model->textureID);
					manager->lastBindTexture = model->textureID;
				}
				
			} else {
				glDisable(GL_TEXTURE_2D);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			
			if(model->blendMode == ModelBlendModeNormal) {
				//	glDepthFunc(GL_LESS);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
				
			} else if(model->blendMode == ModelBlendModeAdd) {
				glDepthFunc(GL_ALWAYS);
				glBlendFunc(GL_ONE, GL_ONE);
			} else if(model->blendMode == ModelBlendModeNoAlpha) {
				//	glDepthFunc(GL_LESS);
				glBlendFunc(GL_ONE, GL_ZERO);
			} else if(model->blendMode == ModelBlendModeSubatract) {
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			} else if(model->blendMode == ModelBlendModeDot) {
				glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			} else if(model->blendMode == ModelBlendModePower) {
				glBlendFunc(GL_ZERO, GL_DST_COLOR);
			} else if(model->blendMode == ModelBlendModeInverse) {
				glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
			}
			
			if(model->isMask) {
				glColorMask(0, 0, 0, 0);
				//if(model->maskDepth == 0) {
					//glDisable(GL_DEPTH_TEST);
					glEnable(GL_STENCIL_TEST);
					glClear(GL_STENCIL_BUFFER_BIT);
				//}
				glStencilFunc(GL_ALWAYS, model->maskDepth, model->maskDepth);
				glStencilOp(GL_INCR, GL_INCR, GL_INCR);
			} else if(model->hasMask) {
				glColorMask(1, 1, 1, 1);
				glStencilFunc(GL_LEQUAL, model->maskDepth, model->maskDepth);
				glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
			} else {
				glColorMask(1, 1, 1, 1);
				glDisable(GL_STENCIL_TEST);
				//if(model->isDepthTest) {
					//glEnable(GL_DEPTH_TEST);
				//} else {
				//	glDisable(GL_DEPTH_TEST);
				//}
			}
			
			/*
			if(model->isLighting) {
				glEnable(GL_LIGHTING);
			} else {
				glDisable(GL_LIGHTING);
			}
			 */
			
			//if(model->colorMode == ModelColorModeNone) {
			//	glDisable(GL_COLOR_MATERIAL);
			//	glDisableClientState(GL_COLOR_ARRAY);
			//} else if(model->colorMode == ModelColorModeOneColor) {
				//glEnable(GL_COLOR_MATERIAL);
				//glDisableClientState(GL_COLOR_ARRAY);
				glColor4ub(model->mixColor->r, model->mixColor->g, model->mixColor->b, model->mixColor->a);
			//} else if(model->colorMode == ModelColorModeVertexColor) {
			//	glEnable(GL_COLOR_MATERIAL);
			//	glEnableClientState(GL_COLOR_ARRAY);
			//	glColorPointer(4, GL_UNSIGNED_BYTE, 0, model->mixColor);
			//}
			
			if(model->isVisible) {
				
				manager->drawModelCount++;
				//if(model->polygon) {
				//	glDrawElements(GL_TRIANGLES, model->polygonLength, GL_UNSIGNED_SHORT, model->polygon);
				//} else {
				if(model->isTriangleFanMode) {
#ifdef ___MACSIMULATOR___
					if(line){
						glDisable(GL_TEXTURE_2D);
						glLineWidth(1.0);
						glColor4ub(lineR, lineG, lineB, 0xFF);
						glDrawArrays(GL_LINE_STRIP, 1, model->vertexLength - 2);
					}else
#endif
						glDrawArrays(GL_TRIANGLE_FAN, 0, model->vertexLength);
				}else{
#ifdef ___MACSIMULATOR___
					if(line){
						glDisable(GL_TEXTURE_2D);
						glLineWidth(1.0);
						glColor4ub(lineR, lineG, lineB, 0xFF);
						glDrawArrays(GL_LINE_STRIP, 0, model->vertexLength);
						Vector3D vec[4];
						vec[0] = model->vertex[1];
						vec[1] = model->vertex[3];
						vec[2] = model->vertex[0];
						vec[3] = model->vertex[2];
						glVertexPointer(3, GL_FLOAT, 0, vec);
						glDrawArrays(GL_LINES, 0, 4);
					}else
#endif
						glDrawArrays(GL_TRIANGLE_STRIP, 0, model->vertexLength);
				}
				//}
			}
		}
	}
#ifdef ___MACSIMULATOR___
		for(int i = 0; i < model->child->length; i++)
			ModelManagerDisplay(manager, model->child->data[i], line);
#else
		for(int i = 0; i < model->child->length; i++)
			ModelManagerDisplay(manager, model->child->data[i]);
#endif
	
	glPopMatrix();
	
	return true;
}

bool ModelManagerDisplayEnd(ModelManager* manager) {
	while(manager->touchArguments->length) {
		ModelEventTouchArgument* touchArgument = ArrayObjectAtIndex(manager->touchArguments, 0);
		ArrayPopObjectAtIndex(manager->touchArguments, 0);
		free(touchArgument);
	}
	return true;
}

#pragma mark -
#pragma mark ModelManager 관리자 드바이스 이벤트 받는 함수

bool ModelManagerTouch(ModelManager* manager,
					   Vector2D touch, 
					   void* touchID, 
					   TouchType touchType, 
					   unsigned char tabCount) {
	ModelEventTouchArgument* touchArgument = (ModelEventTouchArgument*)calloc(1, sizeof(ModelEventTouchArgument));
	touchArgument->touchVector = touch;
	touchArgument->touchID = touchID;
	touchArgument->touchType = touchType;
	touchArgument->touchTabCount = tabCount;
	ArrayPushObject(manager->touchArguments, touchArgument);
	return true;
}