#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "Vector.h"
#include "Matrix.h"
#include "tween.h"
	
	typedef struct Camera Camera;
	
	struct Camera {
		Vector3D* eye;
		Vector3D* center;
		Vector3D* up;
		Matrix3D* matrix;
	};
	
	bool CameraInit(Camera* camera);
	
	bool CameraInitWithVector3D(Camera* camera, Vector3D eye, Vector3D center, Vector3D up);
	
	bool CameraFree(Camera* camera);
	
	bool CameraSetDetailValue(Camera* camera, Vector3D eye, Vector3D center, Vector3D up);

#ifdef __cplusplus
}
#endif

#endif