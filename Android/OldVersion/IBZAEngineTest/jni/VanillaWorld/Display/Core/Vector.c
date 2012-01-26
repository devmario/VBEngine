#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

#include <math.h>

#pragma mark -
#pragma mark Vector의 스트럭처 함수

//초기화
Vector2D Vector2DInit(float x, float y) {
	Vector2D vector;
	vector.x = x;
	vector.y = y;
	return vector;
}

//초기화
Vector3D Vector3DInit(float x, float y, float z) {
	Vector3D vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

//초기화
Vector4D Vector4DInit(float x, float y, float z, float w) {
	Vector4D vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

//같은지 검사
bool Vector2DIsEqual(Vector2D vector1, Vector2D vector2) {
	if(vector1.x != vector2.x)
		return false;
	if(vector1.y != vector2.y)
		return false;
	return true;
}

//같은지 검사
bool Vector3DIsEqual(Vector3D vector1, Vector3D vector2) {
	if(vector1.x != vector2.x)
		return false;
	if(vector1.y != vector2.y)
		return false;
	if(vector1.z != vector2.z)
		return false;
	return true;
}

#pragma mark -
#pragma mark Vector의 기본 함수

//평준화
Vector2D Vector2DNormal(Vector2D vector) {
	float length = Vector2DLength(vector);
	vector.x /= length;
	vector.y /= length;
	return vector;
}

//평준화
Vector3D Vector3DNormal(Vector3D vector) {
	float length = Vector3DLength(vector);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return vector;
}

//두벡터 더하기
Vector2D Vector2DAdd(Vector2D vector1, Vector2D vector2) {
	return Vector2DInit(vector1.x + vector2.x, 
						vector1.y + vector2.y);
}

//두벡터 더하기
Vector3D Vector3DAdd(Vector3D vector1, Vector3D vector2) {
	return Vector3DInit(vector1.x + vector2.x, 
						vector1.y + vector2.y, 
						vector1.z + vector2.z);
}

//두벡터 빼기
Vector2D Vector2DSubtract(Vector2D vector1, Vector2D vector2) {
	return Vector2DInit(vector1.x - vector2.x, 
						vector1.y - vector2.y);
}

//두벡터 빼기
Vector3D Vector3DSubtract(Vector3D vector1, Vector3D vector2) {
	return Vector3DInit(vector1.x - vector2.x, 
						vector1.y - vector2.y, 
						vector1.z - vector2.z);
}

//두백터곱의 내적 스칼라를 리턴
float Vector2DDotProduct(Vector2D vector1, Vector2D vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

//두백터곱의 내적 스칼라를 리턴
float Vector3DDotProduct(Vector3D vector1, Vector3D vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

//두백터의 외적 벡터곱을 리턴
Vector3D Vector3DCrossProduct(Vector3D vector1, Vector3D vector2) {
	return Vector3DInit(vector1.y * vector2.z - vector1.z * vector2.y, 
					    vector1.z * vector2.x - vector1.x * vector2.z, 
					    vector1.x * vector2.y - vector1.y * vector2.x);
}

//벡터의 길이를 리턴
float Vector2DLength(Vector2D vector) {
	return sqrtf(Vector2DDotProduct(vector, vector));
}

//벡터의 길이를 리턴
float Vector3DLength(Vector3D vector) {
	return sqrtf(Vector3DDotProduct(vector, vector));
}

#pragma mark -
#pragma mark Vector의 유용한 함수

//두벡터의 거리를 리턴
float Vector2DDistance(Vector2D vector1, Vector2D vector2) {
	return Vector2DLength(Vector2DSubtract(vector1, vector2));
}

//두벡터의 거리를 리턴
float Vector3DDistance(Vector3D vector1, Vector3D vector2) {
	return Vector3DLength(Vector3DSubtract(vector1, vector2));
}

Quaternion Vector3DGetQuaternion(Vector3D vector) {
	return QuaternionInit(vector.x, vector.y, vector.z, 0.0);
}
