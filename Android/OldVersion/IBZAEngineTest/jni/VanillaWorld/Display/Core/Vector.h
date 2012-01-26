#ifndef __VECTOR_H__
#define __VECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
#pragma mark -
#pragma mark Vector example
	
	/*
	 #include "Vector.h"
	 
	 //카메라위치
	 Vector3D camera = Vector3DInit(0.0, 0.0, 0.0);
	 //물체위치
	 Vector3D object = Vector3DInit(0.0, 0.0, 10.0);
	 //물체와 카메라의 거리
	 float distance = Vector3DDistance(camera, object);
	 */
	
#pragma mark -
#pragma mark define
	
	typedef struct Vector2D Vector2D;
	typedef struct Vector3D Vector3D;
	typedef struct Vector4D Vector4D;
	
	struct Matrix2D;
	struct Matrix3D;
	
	struct Quaternion;
	
#pragma mark -
#pragma mark Vector2D
	
	//2D Vector 구조체
	struct Vector2D {
		float x;
		float y;
	};
	
#pragma mark -
#pragma mark Vector3D
	
	//3D Vector 구조체
	struct Vector3D {
		float x;
		float y;
		float z;
	};
	
#pragma mark -
#pragma mark Vector4D
	
	struct Vector4D {
		float x;
		float y;
		float z;
		float w;
	};
	
#pragma mark -
#pragma mark Vector의 스트럭처 함수
	
	//초기화
	Vector2D Vector2DInit(float x, float y);
	Vector3D Vector3DInit(float x, float y, float z);
	Vector4D Vector4DInit(float x, float y, float z, float w);
	
	//두벡터가 같은지 검사
	bool Vector2DIsEqual(Vector2D vector1, Vector2D vector2);
	bool Vector3DIsEqual(Vector3D vector1, Vector3D vector2);
	
#pragma mark -
#pragma mark Vector의 기본 함수
	
	//평준화
	Vector2D Vector2DNormal(Vector2D vector);
	Vector3D Vector3DNormal(Vector3D vector);
	
	//두벡터 더하기
	Vector2D Vector2DAdd(Vector2D vector1, Vector2D vector2);
	Vector3D Vector3DAdd(Vector3D vector1, Vector3D vector2);
	
	//두벡터 빼기
	Vector2D Vector2DSubtract(Vector2D vector1, Vector2D vector2);
	Vector3D Vector3DSubtract(Vector3D vector1, Vector3D vector2);
	
	//두백터곱의 내적 스칼라를 리턴
	float Vector2DDotProduct(Vector2D vector1, Vector2D vector2);
	float Vector3DDotProduct(Vector3D vector1, Vector3D vector2);
	
	//두백터의 외적 벡터곱을 리턴
	Vector3D Vector3DCrossProduct(Vector3D vector1, Vector3D vector2);
	
	//벡터의 길이를 리턴
	float Vector2DLength(Vector2D vector);
	float Vector3DLength(Vector3D vector);
	
#pragma mark -
#pragma mark Vector의 유용한 함수
	
	//두벡터의 거리를 리턴
	float Vector2DDistance(Vector2D vector1, Vector2D vector2);
	float Vector3DDistance(Vector3D vector1, Vector3D vector2);
	
	struct Quaternion Vector3DGetQuaternion(Vector3D vector);
	
#ifdef __cplusplus
}
#endif

#endif
