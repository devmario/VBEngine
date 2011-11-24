#ifndef __MATRIX_H__
#define __MATRIX_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
	struct Vector2D;
	struct Vector3D;
	struct Vector4D;
	struct Quaternion;
	
	typedef struct Matrix2D Matrix2D;
	typedef struct Matrix3D Matrix3D;
	
	struct Matrix2D {
		float m11, m12, m13;
		float m21, m22, m23;
		float m31, m32, m33;
	};
	
	struct Matrix3D {
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;
	};
	
	Matrix2D Matrix2DInit(float m11, float m12, float m13,
						  float m21, float m22, float m23,
						  float m31, float m32, float m33);
	Matrix2D Matrix2DLoadIdentity(void);
	
	Matrix2D Matrix2DTranslate(Matrix2D mat, struct Vector2D pos);
	Matrix2D Matrix2DScale(Matrix2D mat, struct Vector2D scale);
	Matrix2D Matrix2DRotate(Matrix2D mat, float angle);
	Matrix2D Matrix2DShear(Matrix2D mat, struct Vector2D scale);
	
	
	Matrix3D Matrix3DInit(float m11, float m12, float m13, float m14,
						  float m21, float m22, float m23, float m24,
						  float m31, float m32, float m33, float m34,
						  float m41, float m42, float m43, float m44);
	Matrix3D Matrix3DLoadIdentity(void);
	Matrix3D Matrix3DPerspective(Matrix3D matrix, float fovY, float aspect, float zNear, float zFar);
	Matrix3D Matrix3DDirectionVectors(struct Vector3D right, struct Vector3D up, struct Vector3D front);
	
	Matrix3D Matrix3DMultiply(Matrix3D matrix1, Matrix3D matrix2);
	struct Vector3D Matrix3DMultiplyVector3D(struct Matrix3D matrix, struct Vector3D vector);
	struct Vector4D Matrix3DMultiplyVector4D(Matrix3D matrix, struct Vector4D vector);
	
	Vector3D Matrix3DGetScale(Matrix3D mat);
	
	Matrix3D Matrix3DTranslate(Matrix3D matrix, struct Vector3D vector);
	Matrix3D Matrix3DScale(Matrix3D matrix, struct Vector3D vector);
	Matrix3D Matrix3DRotate(Matrix3D matrix, struct Vector3D axis, float angle);
	Matrix3D Matrix3DShearX(Matrix3D matrix, float y, float z);
	Matrix3D Matrix3DShearY(Matrix3D matrix, float x, float z);
	Matrix3D Matrix3DShearZ(Matrix3D matrix, float x, float y);
	
	float Matrix3DSubDeterminant(Matrix3D matrix, int excludeIndex);
	float Matrix3DDeterminant(Matrix3D matrix);
	Matrix3D Matrix3DInverte(Matrix3D matrix);
	
#ifdef __cplusplus
}
#endif

#endif
