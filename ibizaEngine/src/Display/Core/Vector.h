#ifndef __VECTOR_H__
#define __VECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
	typedef struct Vector2D Vector2D;
	typedef struct Vector3D Vector3D;
	typedef struct Vector4D Vector4D;
	
	struct Matrix2D;
	struct Matrix3D;
	
	struct Quaternion;
	
	struct Vector2D {
		float x;
		float y;
	};
	
	struct Vector3D {
		float x;
		float y;
		float z;
	};
	
	struct Vector4D {
		float x;
		float y;
		float z;
		float w;
	};
	
	Vector2D Vector2DInit(float x, float y);
	Vector3D Vector3DInit(float x, float y, float z);
	Vector4D Vector4DInit(float x, float y, float z, float w);
	
	bool Vector2DIsEqual(Vector2D vector1, Vector2D vector2);
	bool Vector3DIsEqual(Vector3D vector1, Vector3D vector2);
	bool Vector4DIsEqual(Vector4D vector1, Vector4D vector2);
	
	Vector2D Vector2DNormal(Vector2D vector);
	Vector3D Vector3DNormal(Vector3D vector);
	
	Vector2D Vector2DAdd(Vector2D vector1, Vector2D vector2);
	Vector3D Vector3DAdd(Vector3D vector1, Vector3D vector2);
	
	Vector2D Vector2DSubtract(Vector2D vector1, Vector2D vector2);
	Vector3D Vector3DSubtract(Vector3D vector1, Vector3D vector2);
	
	float Vector2DDotProduct(Vector2D vector1, Vector2D vector2);
	float Vector3DDotProduct(Vector3D vector1, Vector3D vector2);
	
	Vector3D Vector3DCrossProduct(Vector3D vector1, Vector3D vector2);
	
	float Vector2DLength(Vector2D vector);
	float Vector3DLength(Vector3D vector);
	
	float Vector2DDistance(Vector2D vector1, Vector2D vector2);
	float Vector3DDistance(Vector3D vector1, Vector3D vector2);
	
	struct Quaternion Vector3DGetQuaternion(Vector3D vector);
	
#ifdef __cplusplus
}
#endif

#endif
