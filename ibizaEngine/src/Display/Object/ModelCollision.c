#include "Model.h"

#include <OpenGLES/ES1/gl.h>


#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
dest[0]=v1[0]-v2[0]; \
dest[1]=v1[1]-v2[1]; \
dest[2]=v1[2]-v2[2]; 

bool intersect_triangle(double orig[3], double dir[3],
						double vert0[3], double vert1[3], double vert2[3],
						double *t, double *u, double *v)
{
	bool hit = true;
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det,inv_det;
	
	/* find vectors for two edges sharing vert0 */
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);
	
	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);
	
	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);
	
#ifdef TEST_CULL           /* define TEST_CULL if culling is desired */
	if (det < EPSILON)
		hit = false;
	
	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, vert0);
	
	/* calculate U parameter and test bounds */
	*u = DOT(tvec, pvec);
	if (*u < 0.0 || *u > det)
		hit = false;
	
	/* prepare to test V parameter */
	CROSS(qvec, tvec, edge1);
	
    /* calculate V parameter and test bounds */
	*v = DOT(dir, qvec);
	if (*v < 0.0 || *u + *v > det)
		hit = false;
	
	/* calculate t, scale parameters, ray intersects triangle */
	*t = DOT(edge2, qvec);
	inv_det = 1.0 / det;
	*t *= inv_det;
	*u *= inv_det;
	*v *= inv_det;
#else                    /* the non-culling branch */
	if (det > -EPSILON && det < EPSILON)
		hit = false;
	inv_det = 1.0 / det;
	
	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, vert0);
	
	/* calculate U parameter and test bounds */
	*u = DOT(tvec, pvec) * inv_det;
	if (*u < 0.0 || *u > 1.0)
		hit = false;
	
	/* prepare to test V parameter */
	CROSS(qvec, tvec, edge1);
	
	/* calculate V parameter and test bounds */
	*v = DOT(dir, qvec) * inv_det;
	if (*v < 0.0 || *u + *v > 1.0)
		hit = false;
	
	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;
#endif
	return hit;
}

#pragma mark -
#pragma mark Model 충돌

bool ModelGetIsVertexHitLineDirection(Model* model, Vector3D origin, Vector3D direction, Vector3D* hitVector, Vector3D* hitVectorGlobal) {
	Matrix3D modelMatrix;
	//현재 매트릭스 가져오기
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&modelMatrix);
	
	Vector3D triangleVector[3];
	Vector3D collosion[3];
	Vector3D* vertex = model->hitVertex;
	for(int i = 0; i < model->hitTrianglePolygonLength; i++) {
		if(i == 0) {
			triangleVector[0] = vertex[0];
			triangleVector[1] = vertex[1];
			triangleVector[2] = vertex[2];
			vertex += 3;
		} else {
			if(model->isTriangleFanMode) {
				triangleVector[0] = model->hitVertex[0];
				triangleVector[1] = triangleVector[2];
				triangleVector[2] = vertex[0];
			} else {
				triangleVector[0] = triangleVector[1];
				triangleVector[1] = triangleVector[2];
				triangleVector[2] = vertex[0];
			}
			vertex += 1;
		}
		collosion[0] = Matrix3DMultiplyVector3D(modelMatrix, triangleVector[0]);
		collosion[1] = Matrix3DMultiplyVector3D(modelMatrix, triangleVector[1]);
		collosion[2] = Matrix3DMultiplyVector3D(modelMatrix, triangleVector[2]);
		double ta, tb, tc;
		double ori[3], dir[3], va[3], vb[3], vc[3];
		ori[0] = (double)origin.x;
		dir[0] = (double)direction.x;
		va[0] = (double)collosion[0].x;
		vb[0] = (double)collosion[1].x;
		vc[0] = (double)collosion[2].x;
		
		ori[1] = (double)origin.y;
		dir[1] = (double)direction.y;
		va[1] = (double)collosion[0].y;
		vb[1] = (double)collosion[1].y;
		vc[1] = (double)collosion[2].y;
		
		ori[2] = (double)origin.z;
		dir[2] = (double)direction.z;
		va[2] = (double)collosion[0].z;
		vb[2] = (double)collosion[1].z;
		vc[2] = (double)collosion[2].z;
		
		bool hit = intersect_triangle(ori, dir, va, vb, vc, &ta, &tb, &tc);
		if(hitVector || hitVectorGlobal) {
			Vector3D collisionVector = Vector3DInit(origin.x + (direction.x * ta), 
													origin.y + (direction.y * ta), 
													origin.z + (direction.z * ta));
			if(hitVectorGlobal) {
				*hitVectorGlobal = Vector3DInit(collisionVector.x, collisionVector.y, collisionVector.z);
			}
			if(hitVector) {
				Vector3D collisionVectorOfModel = Matrix3DMultiplyVector3D(Matrix3DInverte(modelMatrix), collisionVector);
				*hitVector = Vector3DInit(collisionVectorOfModel.x, collisionVectorOfModel.y, collisionVectorOfModel.z);
			}
		}
		if(hit)
			return hit;
	}
	return false;
}