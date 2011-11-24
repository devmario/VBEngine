#include "Camera.h"

#include <stdlib.h>


#include <OpenGLES/ES1/gl.h>


bool CameraInit(Camera* camera) {
	return CameraInitWithVector3D(camera, 
								  Vector3DInit(0.0, 0.0, 0.0), 
								  Vector3DInit(0.0, 0.0, 0.0), 
								  Vector3DInit(0.0, 0.0, 0.0));
}

bool CameraInitWithVector3D(Camera* camera, Vector3D eye, Vector3D center, Vector3D up) {
	camera->eye = malloc(sizeof(Vector3D));
	camera->center = malloc(sizeof(Vector3D));
	camera->up = malloc(sizeof(Vector3D));
	
	camera->matrix = malloc(sizeof(Matrix3D));
	*camera->matrix = Matrix3DLoadIdentity();
	
	CameraSetDetailValue(camera, eye, center, up);
	
	return true;
}

bool CameraFree(Camera* camera) {
	free(camera->eye);
	free(camera->center);
	free(camera->up);
	return true;
}

bool CameraSetDetailValue(Camera* camera, Vector3D eye, Vector3D center, Vector3D up) {
	*camera->eye = eye;
	*camera->center = center;
	*camera->up = up;
	
	Vector3D forwardVector = Vector3DSubtract(*camera->center, *camera->eye);
	forwardVector = Vector3DNormal(forwardVector);
	
	Vector3D sideVector = Vector3DCrossProduct(forwardVector, *camera->up);
	sideVector = Vector3DNormal(sideVector);
	
	Vector3D upVector = Vector3DCrossProduct(sideVector, forwardVector);
	
	camera->matrix->m11 = sideVector.x;
	camera->matrix->m21 = sideVector.y;
	camera->matrix->m31 = sideVector.z;
	
	camera->matrix->m12 = upVector.x;
	camera->matrix->m22 = upVector.y;
	camera->matrix->m32 = upVector.z;
	
	camera->matrix->m13 = -forwardVector.x;
	camera->matrix->m23 = -forwardVector.y;
	camera->matrix->m33 = -forwardVector.z;
	
	camera->matrix->m41 = eye.x;
	camera->matrix->m42 = eye.y;
	camera->matrix->m43 = eye.z;
	
	return true;
}