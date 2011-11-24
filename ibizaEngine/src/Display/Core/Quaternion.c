#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

#include <math.h>
#include <stdlib.h>

Quaternion QuaternionInit(float x, float y, float z, float w) {
	Quaternion quaternion;
	quaternion.x = x;
	quaternion.y = y;
	quaternion.z = z;
	quaternion.w = w;
	return quaternion;
}

Quaternion QuaternionLoadIdentity(void) {
	return QuaternionInit(0.0f, 0.0f, 0.0f, 1.0f);
}

bool QuaternionIsEqual(Quaternion quat1, Quaternion quat2) {
	if(quat1.w != quat2.w)
		return false;
	if(quat1.x != quat2.x)
		return false;
	if(quat1.y != quat2.y)
		return false;
	if(quat1.z != quat2.z)
		return false;
	return true;
}

Quaternion QuaternionInitAxisAngle(Vector3D axis, float angle) {
	angle *= 0.5f;
	axis = Vector3DNormal(axis);
	float sinAngle = sinf(angle);
	return QuaternionInit(axis.x * sinAngle, axis.y * sinAngle, axis.z * sinAngle, cosf(angle));
}

Quaternion QuaternionNormal(Quaternion quaternion) {
	float magnitude = sqrt(quaternion.x * quaternion.x +
						   quaternion.y * quaternion.y +
						   quaternion.z * quaternion.z +
						   quaternion.w * quaternion.w);
	return QuaternionInit(quaternion.x / magnitude, quaternion.y / magnitude, quaternion.z / magnitude, quaternion.w / magnitude);
}

Matrix3D QuaternionGetMatrix3D(Quaternion quaternion) {
	Matrix3D matrix;
	matrix.m11 = 1.0f - (2.0f * ((quaternion.y * quaternion.y) + (quaternion.z * quaternion.z)));
	matrix.m12 =       (2.0f * ((quaternion.x * quaternion.y) + (quaternion.z * quaternion.w)));
	matrix.m13 =       (2.0f * ((quaternion.x * quaternion.z) - (quaternion.y * quaternion.w)));
	matrix.m14 = 0.0f;
	matrix.m21 =       (2.0f * ((quaternion.x * quaternion.y) - (quaternion.z * quaternion.w)));
	matrix.m22 = 1.0f - (2.0f * ((quaternion.x * quaternion.x) + (quaternion.z * quaternion.z)));
	matrix.m23 =       (2.0f * ((quaternion.y * quaternion.z) + (quaternion.x * quaternion.w)));
	matrix.m24 = 0.0f;
	matrix.m31 =       (2.0f * ((quaternion.x * quaternion.z) + (quaternion.y * quaternion.w)));
	matrix.m32 =       (2.0f * ((quaternion.y * quaternion.z) - (quaternion.x * quaternion.w)));
	matrix.m33 = 1.0f - (2.0f * ((quaternion.x * quaternion.x) + (quaternion.y * quaternion.y)));
	matrix.m34 = 0.0f;
	matrix.m41 = 0.0f;
	matrix.m42 = 0.0f;
	matrix.m43 = 0.0f;
	matrix.m44 = 1.0f;
	return matrix;
}

Vector3D QuaternionGetVector3D(Quaternion quaternion) {
	return Vector3DInit(quaternion.x, quaternion.y, quaternion.z);
}

Vector3D QuaternionGetAxis(Quaternion quaternion) {
	Quaternion normal = QuaternionNormal(quaternion);
	float sinAngle = sqrt(1.0f - (normal.w * normal.w));
	if(fabs(sinAngle) < 0.0005f)
		sinAngle = 1.0f;
	return Vector3DInit(normal.x / sinAngle, normal.y / sinAngle, normal.z / sinAngle);
}

float QuaternionGetAngle(Quaternion quaternion) {
	return acosf(quaternion.w) * 2.0f;
}

Quaternion QuaternionMultiply(Quaternion quaternion1, Quaternion quaternion2) {
	Vector3D vector1 = QuaternionGetVector3D(quaternion1);
	Vector3D vector2 = QuaternionGetVector3D(quaternion2);
	float angle = quaternion1.w * quaternion2.w - Vector3DDotProduct(vector1, vector2);
	Vector3D cross = Vector3DCrossProduct(vector1, vector2);
	
	vector1.x *= quaternion2.w;
	vector1.y *= quaternion2.w;
	vector1.z *= quaternion2.w;
	vector2.x *= quaternion1.w;
	vector2.y *= quaternion1.w;
	vector2.z *= quaternion1.w;
	
	return QuaternionInit(vector1.x + vector2.x + cross.x, 
						  vector1.y + vector2.y + cross.y, 
						  vector1.z + vector2.z + cross.z, 
						  angle);
}

Quaternion QuaternionSlerp(Quaternion start, Quaternion end, float alpha) {
	float startWeight, endWeight;
	float difference = start.x * end.x + start.y * end.y + start.z * end.z + start.w * end.w;
	if(1.0f - fabs(difference) > QUATERNION_SLERP_TO_LERP_SWITCH_THRESHOLD) {
		float theta = acosf(fabs(difference));
		float oneOverSinTheta = 1.0f / sin(theta);
		startWeight = sinf(theta * (1.0f - alpha)) * oneOverSinTheta;
		endWeight = sinf(theta * alpha) * oneOverSinTheta;
		if(difference < 0.0f) {
			startWeight = -startWeight;
		}
	} else {
		startWeight = 1.0f - alpha;
		endWeight = alpha;
	}
	Quaternion result = QuaternionInit(start.x * startWeight + end.x * endWeight, 
									   start.y * startWeight + end.y * endWeight, 
									   start.z * startWeight + end.z * endWeight, 
									   start.w * startWeight + end.w * endWeight);
	return QuaternionNormal(result);
}

Quaternion QuaternionRotate(Quaternion quaternion, Vector3D axis, float angle) {
	return QuaternionMultiply(quaternion, QuaternionInitAxisAngle(axis, angle));
}

Quaternion QuaternionInvert(Quaternion quaternion) {
	float length = 1.0f / (quaternion.x * quaternion.x +
						   quaternion.y * quaternion.y +
						   quaternion.z * quaternion.z +
						   quaternion.w * quaternion.w);
	
	return QuaternionInit(quaternion.x * -length, 
						  quaternion.y * -length, 
						  quaternion.z * -length, 
						  quaternion.w * length);
}

Vector3D QuaternionMultiplyVector(Quaternion quaternion, Vector3D vector) {
	Quaternion vectorQuaternion = Vector3DGetQuaternion(vector);
	Quaternion invertQuaternion = QuaternionInvert(quaternion);
	return QuaternionGetVector3D(QuaternionMultiply(vectorQuaternion, invertQuaternion));
}
