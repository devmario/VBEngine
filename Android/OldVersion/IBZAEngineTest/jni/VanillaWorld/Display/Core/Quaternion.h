#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Vector example
	
#pragma mark -
#pragma mark define
	
#define QUATERNION_SLERP_TO_LERP_SWITCH_THRESHOLD 0.01f
	
	struct Vector2D;
	struct Vector3D;
	struct Vector4D;
	
	struct Matrix2D;
	struct Matrix3D;
	
	typedef struct Quaternion Quaternion;
	
#pragma mark -
#pragma mark Quaternion
	
	struct Quaternion {
		float x;
		float y;
		float z;
		float w;
	};
	
#pragma mark -
#pragma mark Quaternion
	
	Quaternion QuaternionInit(float x, float y, float z, float w);
	
	Quaternion QuaternionLoadIdentity(void);
	
	bool QuaternionIsEqual(Quaternion quat1, Quaternion quat2);
	
	Quaternion QuaternionInitAxisAngle(Vector3D axis, float angle);
	
	Quaternion QuaternionNormal(Quaternion quaternion);

	struct Matrix3D QuaternionGetMatrix3D(Quaternion quaternion);
	
	struct Vector3D QuaternionGetVector3D(Quaternion quaternion);
	
	struct Vector3D QuaternionGetAxis(Quaternion quaternion);
	
	float QuaternionGetAngle(Quaternion quaternion);
	
	Quaternion QuaternionMultiply(Quaternion quaternion1, Quaternion quaternion2);
	
	Quaternion QuaternionSlerp(Quaternion start, Quaternion end, float alpha);
	
	Quaternion QuaternionRotate(Quaternion quaternion, Vector3D axis, float angle);
	
	Quaternion QuaternionInvert(Quaternion quaternion);
	
	struct Vector3D QuaternionMultiplyVector(Quaternion quaternion, struct Vector3D vector);
	
#ifdef __cplusplus
}
#endif

#endif
