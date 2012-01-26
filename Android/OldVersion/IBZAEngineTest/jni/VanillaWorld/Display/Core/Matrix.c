#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

#include <math.h>
#include "Math.h"

Matrix3D Matrix3DInit(float m11, float m12, float m13, float m14,
					  float m21, float m22, float m23, float m24,
					  float m31, float m32, float m33, float m34,
					  float m41, float m42, float m43, float m44) {
	Matrix3D matrix;
	matrix.m11 = m11;	matrix.m12 = m12;	matrix.m13 = m13;	matrix.m14 = m14;
	matrix.m21 = m21;	matrix.m22 = m22;	matrix.m23 = m23;	matrix.m24 = m24;
	matrix.m31 = m31;	matrix.m32 = m32;	matrix.m33 = m33;	matrix.m34 = m34;
	matrix.m41 = m41;	matrix.m42 = m42;	matrix.m43 = m43;	matrix.m44 = m44;
	return matrix;
}

Vector3D Matrix3DGetScale(Matrix3D mat) {
	Vector3D vec;
	vec.x = Vector3DLength(Vector3DInit(mat.m11, mat.m12, mat.m13));
	vec.y = Vector3DLength(Vector3DInit(mat.m21, mat.m22, mat.m23));
	vec.z = Vector3DLength(Vector3DInit(mat.m31, mat.m32, mat.m33));
	return vec;
}

Matrix3D Matrix3DLoadIdentity(void) {
	return Matrix3DInit(1.0, 0.0, 0.0, 0.0, 
						0.0, 1.0, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
}

Matrix3D Matrix3DDirectionVectors(Vector3D right, Vector3D up, Vector3D front) {
	Matrix3D matrix = Matrix3DLoadIdentity();
	matrix.m11 = right.x;	matrix.m12 = right.y;	matrix.m13 = right.z;
	matrix.m21 = up.x;		matrix.m22 = up.y;		matrix.m23 = up.z;
	matrix.m31 = front.x;	matrix.m32 = front.y;	matrix.m33 = front.z;
	return matrix;
}

Matrix3D Matrix3DMultiply(Matrix3D matrix1, Matrix3D matrix2) {
	Matrix3D result;
	result.m11 = matrix1.m11 * matrix2.m11 + matrix1.m21 * matrix2.m12 + matrix1.m31 * matrix2.m13 + matrix1.m41 * matrix2.m14;
	result.m12 = matrix1.m12 * matrix2.m11 + matrix1.m22 * matrix2.m12 + matrix1.m32 * matrix2.m13 + matrix1.m42 * matrix2.m14;
	result.m13 = matrix1.m13 * matrix2.m11 + matrix1.m23 * matrix2.m12 + matrix1.m33 * matrix2.m13 + matrix1.m43 * matrix2.m14;
	result.m14 = matrix1.m14 * matrix2.m11 + matrix1.m24 * matrix2.m12 + matrix1.m34 * matrix2.m13 + matrix1.m44 * matrix2.m14;
	
	result.m21 = matrix1.m11 * matrix2.m21 + matrix1.m21 * matrix2.m22 + matrix1.m31 * matrix2.m23 + matrix1.m41 * matrix2.m24;
	result.m22 = matrix1.m12 * matrix2.m21 + matrix1.m22 * matrix2.m22 + matrix1.m32 * matrix2.m23 + matrix1.m42 * matrix2.m24;
	result.m23 = matrix1.m13 * matrix2.m21 + matrix1.m23 * matrix2.m22 + matrix1.m33 * matrix2.m23 + matrix1.m43 * matrix2.m24;
	result.m24 = matrix1.m14 * matrix2.m21 + matrix1.m24 * matrix2.m22 + matrix1.m34 * matrix2.m23 + matrix1.m44 * matrix2.m24;
	
	result.m31 = matrix1.m11 * matrix2.m31 + matrix1.m21 * matrix2.m32 + matrix1.m31 * matrix2.m33 + matrix1.m41 * matrix2.m34;
	result.m32 = matrix1.m12 * matrix2.m31 + matrix1.m22 * matrix2.m32 + matrix1.m32 * matrix2.m33 + matrix1.m42 * matrix2.m34;
	result.m33 = matrix1.m13 * matrix2.m31 + matrix1.m23 * matrix2.m32 + matrix1.m33 * matrix2.m33 + matrix1.m43 * matrix2.m34;
	result.m34 = matrix1.m14 * matrix2.m31 + matrix1.m24 * matrix2.m32 + matrix1.m34 * matrix2.m33 + matrix1.m44 * matrix2.m34;
	
	result.m41 = matrix1.m11 * matrix2.m41 + matrix1.m21 * matrix2.m42 + matrix1.m31 * matrix2.m43 + matrix1.m41 * matrix2.m44;
	result.m42 = matrix1.m12 * matrix2.m41 + matrix1.m22 * matrix2.m42 + matrix1.m32 * matrix2.m43 + matrix1.m42 * matrix2.m44;
	result.m43 = matrix1.m13 * matrix2.m41 + matrix1.m23 * matrix2.m42 + matrix1.m33 * matrix2.m43 + matrix1.m43 * matrix2.m44;
	result.m44 = matrix1.m14 * matrix2.m41 + matrix1.m24 * matrix2.m42 + matrix1.m34 * matrix2.m43 + matrix1.m44 * matrix2.m44;
	return result;
}

Vector3D Matrix3DMultiplyVector3D(Matrix3D matrix, Vector3D vector) {
	Vector3D result;
	result.x = matrix.m11 * vector.x + matrix.m21 * vector.y + matrix.m31 * vector.z + matrix.m41;
	result.y = matrix.m12 * vector.x + matrix.m22 * vector.y + matrix.m32 * vector.z + matrix.m42;
	result.z = matrix.m13 * vector.x + matrix.m23 * vector.y + matrix.m33 * vector.z + matrix.m43;
	return result;
}

Vector4D Matrix3DMultiplyVector4D(Matrix3D matrix, Vector4D vector) {
	Vector4D result;
	result.x = vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31 + vector.w * matrix.m41;
	result.y = vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32 + vector.w * matrix.m42;
	result.z = vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33 + vector.w * matrix.m43;
	result.w = vector.x * matrix.m14 + vector.y * matrix.m24 + vector.z * matrix.m34 + vector.w * matrix.m44;
	return result;
}

Matrix3D Matrix3DTranslate(Matrix3D matrix, Vector3D vector) {
	Matrix3D translate = Matrix3DLoadIdentity();
	translate.m41 = vector.x;
	translate.m42 = vector.y;
	translate.m43 = vector.z;
	return Matrix3DMultiply(matrix, translate);
}

Matrix3D Matrix3DScale(Matrix3D matrix, Vector3D vector) {
	Matrix3D scale = Matrix3DLoadIdentity();
	scale.m11 = vector.x;
	scale.m22 = vector.y;
	scale.m33 = vector.z;
	return Matrix3DMultiply(matrix, scale);
}

Matrix3D Matrix3DRotate(Matrix3D matrix, Vector3D axis, float angle) {
	Quaternion quaternion = QuaternionInitAxisAngle(axis, angle);
	Matrix3D rotate = QuaternionGetMatrix3D(quaternion);
	return Matrix3DMultiply(matrix, rotate);
}

Matrix3D Matrix3DShearX(Matrix3D matrix, float y, float z) {
	Matrix3D shearX = Matrix3DLoadIdentity();
	shearX.m12 = y;
	shearX.m13 = z;
	return Matrix3DMultiply(matrix, shearX);
}

Matrix3D Matrix3DShearY(Matrix3D matrix, float x, float z) {
	Matrix3D shearY = Matrix3DLoadIdentity();
	shearY.m21 = x;
	shearY.m23 = z;
	return Matrix3DMultiply(matrix, shearY);
}

Matrix3D Matrix3DShearZ(Matrix3D matrix, float x, float y) {
	Matrix3D shearZ = Matrix3DLoadIdentity();
	shearZ.m31 = x;
	shearZ.m32 = y;
	return Matrix3DMultiply(matrix, shearZ);
}

Matrix3D Matrix3DPerspective(Matrix3D matrix, float fovY, float aspect, float zNear, float zFar) {
	fovY = (MathUtilDegreesToRadians(fovY) / 2.0f);
	float deltaZ = zFar - zNear;
	float sine = sinf(fovY);
	if(deltaZ == 0.0f || sine == 0.0f || aspect == 0.0f) {
		return matrix;
	}
	float cotangent = (cos(fovY) / sine);
	
	Matrix3D perspective = Matrix3DLoadIdentity();
	perspective.m11 = cotangent / aspect;
	perspective.m22 = cotangent;
	perspective.m33 = -(zFar + zNear) / deltaZ;
	perspective.m34 = -1.0f;
	perspective.m43 = (-2.0f * zNear * zFar) / deltaZ;
	perspective.m44 = 0.0f;
	return Matrix3DMultiply(matrix, perspective);
}

float Matrix3DSubDeterminant(Matrix3D matrix, int excludeIndex) {
	float matrix3x3[9];
	int index3x3 = 0;
	float* matrixPtr = (float*)&matrix;
	int index4x4 = 0;
	for(; index4x4 < 16; index4x4++) {
		if(index4x4 / 4 == excludeIndex / 4 || index4x4 % 4 == excludeIndex % 4) {
			continue;
		}
		matrix3x3[index3x3++] = matrixPtr[index4x4];
	}
	return matrix3x3[0] * (matrix3x3[4] * matrix3x3[8] - matrix3x3[5] * matrix3x3[7]) -
		   matrix3x3[3] * (matrix3x3[1] * matrix3x3[8] - matrix3x3[2] * matrix3x3[7]) +
	       matrix3x3[6] * (matrix3x3[1] * matrix3x3[5] - matrix3x3[2] * matrix3x3[4]);
}

float Matrix3DDeterminant(Matrix3D matrix) {
	float subdeterminant0 = Matrix3DSubDeterminant(matrix, 0);
	float subdeterminant1 = Matrix3DSubDeterminant(matrix, 4);
	float subdeterminant2 = Matrix3DSubDeterminant(matrix, 8);
	float subdeterminant3 = Matrix3DSubDeterminant(matrix, 12);
	return matrix.m11 * subdeterminant0 + matrix.m21 * -subdeterminant1 + matrix.m31 * subdeterminant2 + matrix.m41 * -subdeterminant3;
}

Matrix3D Matrix3DInverte(Matrix3D matrix) {
	float determinant = Matrix3DDeterminant(matrix);
	Matrix3D result;
	float* resultPtr = (float*)&result;
	int index = 0;
	for (; index < 16; index++) {
		int sign = 1 - (((index % 4) + (index / 4)) % 2) * 2;
		int indexTransposed = (index % 4) * 4 + index / 4;
		resultPtr[indexTransposed] = Matrix3DSubDeterminant(matrix, index) * sign / determinant;
	}
	return result;
}
