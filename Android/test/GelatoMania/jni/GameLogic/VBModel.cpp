#include <iostream>
#include <string.h>
#include "VBModel.h"
#include "cocos2d.h"
/*
 *		  		
 *  Triangle-Triangle Overlap Test Routines				
 *  July, 2002                                                          
 *  Updated December 2003                                                
 *                                                                       
 *  This file contains C implementation of algorithms for                
 *  performing two and three-dimensional triangle-triangle intersection test 
 *  The algorithms and underlying theory are described in                    
 *                                                                           
 * "Fast and Robust Triangle-Triangle Overlap Test 
 *  Using Orientation Predicates"  P. Guigue - O. Devillers
 *                                                 
 *  Journal of Graphics Tools, 8(1), 2003                                    
 *                                                                           
 *  Several geometric predicates are defined.  Their parameters are all      
 *  points.  Each point is an array of two or three double precision         
 *  floating point numbers. The geometric predicates implemented in          
 *  this file are:                                                            
 *                                                                           
 *    int tri_tri_overlap_test_3d(p1,q1,r1,p2,q2,r2)                         
 *    int tri_tri_overlap_test_2d(p1,q1,r1,p2,q2,r2)                         
 *                                                                           
 *    int tri_tri_intersection_test_3d(p1,q1,r1,p2,q2,r2,
 *                                     coplanar,source,target)               
 *                                                                           
 *       is a version that computes the segment of intersection when            
 *       the triangles overlap (and are not coplanar)                        
 *                                                                           
 *    each function returns 1 if the triangles (including their              
 *    boundary) intersect, otherwise 0                                       
 *                                                                           
 *                                                                           
 *  Other information are available from the Web page                        
 *  http://www.acm.org/jgt/papers/GuigueDevillers03/                         
 *                                                                           
 */



/* function prototype */

int tri_tri_overlap_test_3d(double p1[3], double q1[3], double r1[3], 
                            double p2[3], double q2[3], double r2[3]);


int coplanar_tri_tri3d(double  p1[3], double  q1[3], double  r1[3],
                       double  p2[3], double  q2[3], double  r2[3],
                       double  N1[3], double  N2[3]);


int tri_tri_overlap_test_2d(double p1[2], double q1[2], double r1[2], 
                            double p2[2], double q2[2], double r2[2]);


int tri_tri_intersection_test_3d(double p1[3], double q1[3], double r1[3], 
                                 double p2[3], double q2[3], double r2[3],
                                 int * coplanar, 
                                 double source[3],double target[3]);

/* coplanar returns whether the triangles are coplanar  
 *  source and target are the endpoints of the segment of 
 *  intersection if it exists) 
 */


/* some 3D macros */

#define CROSS(dest,v1,v2)                       \
dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
dest[2]=v1[0]*v2[1]-v1[1]*v2[0];

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])



#define SUB(dest,v1,v2) dest[0]=v1[0]-v2[0]; \
dest[1]=v1[1]-v2[1]; \
dest[2]=v1[2]-v2[2]; 


#define SCALAR(dest,alpha,v) dest[0] = alpha * v[0]; \
dest[1] = alpha * v[1]; \
dest[2] = alpha * v[2];



#define CHECK_MIN_MAX(p1,q1,r1,p2,q2,r2) {\
SUB(v1,p2,q1)\
SUB(v2,p1,q1)\
CROSS(N1,v1,v2)\
SUB(v1,q2,q1)\
if (DOT(v1,N1) > 0.0f) return 0;\
SUB(v1,p2,p1)\
SUB(v2,r1,p1)\
CROSS(N1,v1,v2)\
SUB(v1,r2,p1) \
if (DOT(v1,N1) > 0.0f) return 0;\
else return 1; }



/* Permutation in a canonical form of T2's vertices */

#define TRI_TRI_3D(p1,q1,r1,p2,q2,r2,dp2,dq2,dr2) { \
if (dp2 > 0.0f) { \
if (dq2 > 0.0f) CHECK_MIN_MAX(p1,r1,q1,r2,p2,q2) \
else if (dr2 > 0.0f) CHECK_MIN_MAX(p1,r1,q1,q2,r2,p2)\
else CHECK_MIN_MAX(p1,q1,r1,p2,q2,r2) }\
else if (dp2 < 0.0f) { \
if (dq2 < 0.0f) CHECK_MIN_MAX(p1,q1,r1,r2,p2,q2)\
else if (dr2 < 0.0f) CHECK_MIN_MAX(p1,q1,r1,q2,r2,p2)\
else CHECK_MIN_MAX(p1,r1,q1,p2,q2,r2)\
} else { \
if (dq2 < 0.0f) { \
if (dr2 >= 0.0f)  CHECK_MIN_MAX(p1,r1,q1,q2,r2,p2)\
else CHECK_MIN_MAX(p1,q1,r1,p2,q2,r2)\
} \
else if (dq2 > 0.0f) { \
if (dr2 > 0.0f) CHECK_MIN_MAX(p1,r1,q1,p2,q2,r2)\
else  CHECK_MIN_MAX(p1,q1,r1,q2,r2,p2)\
} \
else  { \
if (dr2 > 0.0f) CHECK_MIN_MAX(p1,q1,r1,r2,p2,q2)\
else if (dr2 < 0.0f) CHECK_MIN_MAX(p1,r1,q1,r2,p2,q2)\
else return coplanar_tri_tri3d(p1,q1,r1,p2,q2,r2,N1,N2);\
}}}



/*
 *
 *  Three-dimensional Triangle-Triangle Overlap Test
 *
 */


int tri_tri_overlap_test_3d(double p1[3], double q1[3], double r1[3], 
                            
                            double p2[3], double q2[3], double r2[3])
{
    double dp1, dq1, dr1, dp2, dq2, dr2;
    double v1[3], v2[3];
    double N1[3], N2[3]; 
    
    /* Compute distance signs  of p1, q1 and r1 to the plane of
     triangle(p2,q2,r2) */
    
    
    SUB(v1,p2,r2)
    SUB(v2,q2,r2)
    CROSS(N2,v1,v2)
    
    SUB(v1,p1,r2)
    dp1 = DOT(v1,N2);
    SUB(v1,q1,r2)
    dq1 = DOT(v1,N2);
    SUB(v1,r1,r2)
    dr1 = DOT(v1,N2);
    
    if (((dp1 * dq1) > 0.0f) && ((dp1 * dr1) > 0.0f))  return 0; 
    
    /* Compute distance signs  of p2, q2 and r2 to the plane of
     triangle(p1,q1,r1) */
    
    
    SUB(v1,q1,p1)
    SUB(v2,r1,p1)
    CROSS(N1,v1,v2)
    
    SUB(v1,p2,r1)
    dp2 = DOT(v1,N1);
    SUB(v1,q2,r1)
    dq2 = DOT(v1,N1);
    SUB(v1,r2,r1)
    dr2 = DOT(v1,N1);
    
    if (((dp2 * dq2) > 0.0f) && ((dp2 * dr2) > 0.0f)) return 0;
    
    /* Permutation in a canonical form of T1's vertices */
    
    
    if (dp1 > 0.0f) {
        if (dq1 > 0.0f) TRI_TRI_3D(r1,p1,q1,p2,r2,q2,dp2,dr2,dq2)
            else if (dr1 > 0.0f) TRI_TRI_3D(q1,r1,p1,p2,r2,q2,dp2,dr2,dq2)	
                else TRI_TRI_3D(p1,q1,r1,p2,q2,r2,dp2,dq2,dr2)
                    } else if (dp1 < 0.0f) {
                        if (dq1 < 0.0f) TRI_TRI_3D(r1,p1,q1,p2,q2,r2,dp2,dq2,dr2)
                            else if (dr1 < 0.0f) TRI_TRI_3D(q1,r1,p1,p2,q2,r2,dp2,dq2,dr2)
                                else TRI_TRI_3D(p1,q1,r1,p2,r2,q2,dp2,dr2,dq2)
                                    } else {
                                        if (dq1 < 0.0f) {
                                            if (dr1 >= 0.0f) TRI_TRI_3D(q1,r1,p1,p2,r2,q2,dp2,dr2,dq2)
                                                else TRI_TRI_3D(p1,q1,r1,p2,q2,r2,dp2,dq2,dr2)
                                                    }
                                        else if (dq1 > 0.0f) {
                                            if (dr1 > 0.0f) TRI_TRI_3D(p1,q1,r1,p2,r2,q2,dp2,dr2,dq2)
                                                else TRI_TRI_3D(q1,r1,p1,p2,q2,r2,dp2,dq2,dr2)
                                                    }
                                        else  {
                                            if (dr1 > 0.0f) TRI_TRI_3D(r1,p1,q1,p2,q2,r2,dp2,dq2,dr2)
                                                else if (dr1 < 0.0f) TRI_TRI_3D(r1,p1,q1,p2,r2,q2,dp2,dr2,dq2)
                                                    else return coplanar_tri_tri3d(p1,q1,r1,p2,q2,r2,N1,N2);
                                        }
                                    }
};



int coplanar_tri_tri3d(double p1[3], double q1[3], double r1[3],
                       double p2[3], double q2[3], double r2[3],
                       double normal_1[3], double normal_2[3]){
    
    double P1[2],Q1[2],R1[2];
    double P2[2],Q2[2],R2[2];
    
    double n_x, n_y, n_z;
    
    n_x = ((normal_1[0]<0)?-normal_1[0]:normal_1[0]);
    n_y = ((normal_1[1]<0)?-normal_1[1]:normal_1[1]);
    n_z = ((normal_1[2]<0)?-normal_1[2]:normal_1[2]);
    
    
    /* Projection of the triangles in 3D onto 2D such that the area of
     the projection is maximized. */
    
    
    if (( n_x > n_z ) && ( n_x >= n_y )) {
        // Project onto plane YZ
        
        P1[0] = q1[2]; P1[1] = q1[1];
        Q1[0] = p1[2]; Q1[1] = p1[1];
        R1[0] = r1[2]; R1[1] = r1[1]; 
        
        P2[0] = q2[2]; P2[1] = q2[1];
        Q2[0] = p2[2]; Q2[1] = p2[1];
        R2[0] = r2[2]; R2[1] = r2[1]; 
        
    } else if (( n_y > n_z ) && ( n_y >= n_x )) {
        // Project onto plane XZ
        
        P1[0] = q1[0]; P1[1] = q1[2];
        Q1[0] = p1[0]; Q1[1] = p1[2];
        R1[0] = r1[0]; R1[1] = r1[2]; 
        
        P2[0] = q2[0]; P2[1] = q2[2];
        Q2[0] = p2[0]; Q2[1] = p2[2];
        R2[0] = r2[0]; R2[1] = r2[2]; 
        
    } else {
        // Project onto plane XY
        
        P1[0] = p1[0]; P1[1] = p1[1]; 
        Q1[0] = q1[0]; Q1[1] = q1[1]; 
        R1[0] = r1[0]; R1[1] = r1[1]; 
        
        P2[0] = p2[0]; P2[1] = p2[1]; 
        Q2[0] = q2[0]; Q2[1] = q2[1]; 
        R2[0] = r2[0]; R2[1] = r2[1]; 
    }
    
    return tri_tri_overlap_test_2d(P1,Q1,R1,P2,Q2,R2);
    
};



/*
 *                                                                
 *  Three-dimensional Triangle-Triangle Intersection              
 *
 */

/*
 This macro is called when the triangles surely intersect
 It constructs the segment of intersection of the two triangles
 if they are not coplanar.
 */

#define CONSTRUCT_INTERSECTION(p1,q1,r1,p2,q2,r2) { \
SUB(v1,q1,p1) \
SUB(v2,r2,p1) \
CROSS(N,v1,v2) \
SUB(v,p2,p1) \
if (DOT(v,N) > 0.0f) {\
SUB(v1,r1,p1) \
CROSS(N,v1,v2) \
if (DOT(v,N) <= 0.0f) { \
SUB(v2,q2,p1) \
CROSS(N,v1,v2) \
if (DOT(v,N) > 0.0f) { \
SUB(v1,p1,p2) \
SUB(v2,p1,r1) \
alpha = DOT(v1,N2) / DOT(v2,N2); \
SCALAR(v1,alpha,v2) \
SUB(source,p1,v1) \
SUB(v1,p2,p1) \
SUB(v2,p2,r2) \
alpha = DOT(v1,N1) / DOT(v2,N1); \
SCALAR(v1,alpha,v2) \
SUB(target,p2,v1) \
return 1; \
} else { \
SUB(v1,p2,p1) \
SUB(v2,p2,q2) \
alpha = DOT(v1,N1) / DOT(v2,N1); \
SCALAR(v1,alpha,v2) \
SUB(source,p2,v1) \
SUB(v1,p2,p1) \
SUB(v2,p2,r2) \
alpha = DOT(v1,N1) / DOT(v2,N1); \
SCALAR(v1,alpha,v2) \
SUB(target,p2,v1) \
return 1; \
} \
} else { \
return 0; \
} \
} else { \
SUB(v2,q2,p1) \
CROSS(N,v1,v2) \
if (DOT(v,N) < 0.0f) { \
return 0; \
} else { \
SUB(v1,r1,p1) \
CROSS(N,v1,v2) \
if (DOT(v,N) >= 0.0f) { \
SUB(v1,p1,p2) \
SUB(v2,p1,r1) \
alpha = DOT(v1,N2) / DOT(v2,N2); \
SCALAR(v1,alpha,v2) \
SUB(source,p1,v1) \
SUB(v1,p1,p2) \
SUB(v2,p1,q1) \
alpha = DOT(v1,N2) / DOT(v2,N2); \
SCALAR(v1,alpha,v2) \
SUB(target,p1,v1) \
return 1; \
} else { \
SUB(v1,p2,p1) \
SUB(v2,p2,q2) \
alpha = DOT(v1,N1) / DOT(v2,N1); \
SCALAR(v1,alpha,v2) \
SUB(source,p2,v1) \
SUB(v1,p1,p2) \
SUB(v2,p1,q1) \
alpha = DOT(v1,N2) / DOT(v2,N2); \
SCALAR(v1,alpha,v2) \
SUB(target,p1,v1) \
return 1; \
}}}} 



#define TRI_TRI_INTER_3D(p1,q1,r1,p2,q2,r2,dp2,dq2,dr2) { \
if (dp2 > 0.0f) { \
if (dq2 > 0.0f) CONSTRUCT_INTERSECTION(p1,r1,q1,r2,p2,q2) \
else if (dr2 > 0.0f) CONSTRUCT_INTERSECTION(p1,r1,q1,q2,r2,p2)\
else CONSTRUCT_INTERSECTION(p1,q1,r1,p2,q2,r2) }\
else if (dp2 < 0.0f) { \
if (dq2 < 0.0f) CONSTRUCT_INTERSECTION(p1,q1,r1,r2,p2,q2)\
else if (dr2 < 0.0f) CONSTRUCT_INTERSECTION(p1,q1,r1,q2,r2,p2)\
else CONSTRUCT_INTERSECTION(p1,r1,q1,p2,q2,r2)\
} else { \
if (dq2 < 0.0f) { \
if (dr2 >= 0.0f)  CONSTRUCT_INTERSECTION(p1,r1,q1,q2,r2,p2)\
else CONSTRUCT_INTERSECTION(p1,q1,r1,p2,q2,r2)\
} \
else if (dq2 > 0.0f) { \
if (dr2 > 0.0f) CONSTRUCT_INTERSECTION(p1,r1,q1,p2,q2,r2)\
else  CONSTRUCT_INTERSECTION(p1,q1,r1,q2,r2,p2)\
} \
else  { \
if (dr2 > 0.0f) CONSTRUCT_INTERSECTION(p1,q1,r1,r2,p2,q2)\
else if (dr2 < 0.0f) CONSTRUCT_INTERSECTION(p1,r1,q1,r2,p2,q2)\
else { \
*coplanar = 1; \
return coplanar_tri_tri3d(p1,q1,r1,p2,q2,r2,N1,N2);\
} \
}} }


/*
 The following version computes the segment of intersection of the
 two triangles if it exists. 
 coplanar returns whether the triangles are coplanar
 source and target are the endpoints of the line segment of intersection 
 */

int tri_tri_intersection_test_3d(double p1[3], double q1[3], double r1[3], 
                                 double p2[3], double q2[3], double r2[3],
                                 int * coplanar, 
                                 double source[3], double target[3] )

{
    double dp1, dq1, dr1, dp2, dq2, dr2;
    double v1[3], v2[3], v[3];
    double N1[3], N2[3], N[3];
    double alpha;
    
    // Compute distance signs  of p1, q1 and r1 
    // to the plane of triangle(p2,q2,r2)
    
    
    SUB(v1,p2,r2)
    SUB(v2,q2,r2)
    CROSS(N2,v1,v2)
    
    SUB(v1,p1,r2)
    dp1 = DOT(v1,N2);
    SUB(v1,q1,r2)
    dq1 = DOT(v1,N2);
    SUB(v1,r1,r2)
    dr1 = DOT(v1,N2);
    
    if (((dp1 * dq1) > 0.0f) && ((dp1 * dr1) > 0.0f))  return 0; 
    
    // Compute distance signs  of p2, q2 and r2 
    // to the plane of triangle(p1,q1,r1)
    
    
    SUB(v1,q1,p1)
    SUB(v2,r1,p1)
    CROSS(N1,v1,v2)
    
    SUB(v1,p2,r1)
    dp2 = DOT(v1,N1);
    SUB(v1,q2,r1)
    dq2 = DOT(v1,N1);
    SUB(v1,r2,r1)
    dr2 = DOT(v1,N1);
    
    if (((dp2 * dq2) > 0.0f) && ((dp2 * dr2) > 0.0f)) return 0;
    
    // Permutation in a canonical form of T1's vertices
    
    
    if (dp1 > 0.0f) {
        if (dq1 > 0.0f) TRI_TRI_INTER_3D(r1,p1,q1,p2,r2,q2,dp2,dr2,dq2)
            else if (dr1 > 0.0f) TRI_TRI_INTER_3D(q1,r1,p1,p2,r2,q2,dp2,dr2,dq2)
                
                else TRI_TRI_INTER_3D(p1,q1,r1,p2,q2,r2,dp2,dq2,dr2)
                    } else if (dp1 < 0.0f) {
                        if (dq1 < 0.0f) TRI_TRI_INTER_3D(r1,p1,q1,p2,q2,r2,dp2,dq2,dr2)
                            else if (dr1 < 0.0f) TRI_TRI_INTER_3D(q1,r1,p1,p2,q2,r2,dp2,dq2,dr2)
                                else TRI_TRI_INTER_3D(p1,q1,r1,p2,r2,q2,dp2,dr2,dq2)
                                    } else {
                                        if (dq1 < 0.0f) {
                                            if (dr1 >= 0.0f) TRI_TRI_INTER_3D(q1,r1,p1,p2,r2,q2,dp2,dr2,dq2)
                                                else TRI_TRI_INTER_3D(p1,q1,r1,p2,q2,r2,dp2,dq2,dr2)
                                                    }
                                        else if (dq1 > 0.0f) {
                                            if (dr1 > 0.0f) TRI_TRI_INTER_3D(p1,q1,r1,p2,r2,q2,dp2,dr2,dq2)
                                                else TRI_TRI_INTER_3D(q1,r1,p1,p2,q2,r2,dp2,dq2,dr2)
                                                    }
                                        else  {
                                            if (dr1 > 0.0f) TRI_TRI_INTER_3D(r1,p1,q1,p2,q2,r2,dp2,dq2,dr2)
                                                else if (dr1 < 0.0f) TRI_TRI_INTER_3D(r1,p1,q1,p2,r2,q2,dp2,dr2,dq2)
                                                    else {
                                                        // triangles are co-planar
                                                        
                                                        *coplanar = 1;
                                                        return coplanar_tri_tri3d(p1,q1,r1,p2,q2,r2,N1,N2);
                                                    }
                                        }
                                    }
};





/*
 *
 *  Two dimensional Triangle-Triangle Overlap Test    
 *
 */


/* some 2D macros */

#define ORIENT_2D(a, b, c)  ((a[0]-c[0])*(b[1]-c[1])-(a[1]-c[1])*(b[0]-c[0]))


#define INTERSECTION_TEST_VERTEX(P1, Q1, R1, P2, Q2, R2) {\
    if (ORIENT_2D(R2,P2,Q1) >= 0.0f)\
        if (ORIENT_2D(R2,Q2,Q1) <= 0.0f)\
            if (ORIENT_2D(P1,P2,Q1) > 0.0f) {\
                if (ORIENT_2D(P1,Q2,Q1) <= 0.0f) return 1; \
                else return 0;} else {\
                if (ORIENT_2D(P1,P2,R1) >= 0.0f)\
                    if (ORIENT_2D(Q1,R1,P2) >= 0.0f) return 1; \
                    else return 0;\
                else return 0;}\
            else \
                if (ORIENT_2D(P1,Q2,Q1) <= 0.0f)\
                    if (ORIENT_2D(R2,Q2,R1) <= 0.0f)\
                        if (ORIENT_2D(Q1,R1,Q2) >= 0.0f) return 1; \
                        else return 0;\
                    else return 0;\
                else return 0;\
            else\
                if (ORIENT_2D(R2,P2,R1) >= 0.0f) \
                    if (ORIENT_2D(Q1,R1,R2) >= 0.0f)\
                        if (ORIENT_2D(P1,P2,R1) >= 0.0f) return 1;\
                        else return 0;\
                    else \
                        if (ORIENT_2D(Q1,R1,Q2) >= 0.0f) {\
                            if (ORIENT_2D(R2,R1,Q2) >= 0.0f) return 1; \
                            else return 0; }\
                        else return 0; \
                else  return 0; \
};



#define INTERSECTION_TEST_EDGE(P1, Q1, R1, P2, Q2, R2) { \
if (ORIENT_2D(R2,P2,Q1) >= 0.0f) {\
if (ORIENT_2D(P1,P2,Q1) >= 0.0f) { \
if (ORIENT_2D(P1,Q1,R2) >= 0.0f) return 1; \
else return 0;} else { \
if (ORIENT_2D(Q1,R1,P2) >= 0.0f){ \
if (ORIENT_2D(R1,P1,P2) >= 0.0f) return 1; else return 0;} \
else return 0; } \
} else {\
if (ORIENT_2D(R2,P2,R1) >= 0.0f) {\
if (ORIENT_2D(P1,P2,R1) >= 0.0f) {\
if (ORIENT_2D(P1,R1,R2) >= 0.0f) return 1;  \
else {\
if (ORIENT_2D(Q1,R1,R2) >= 0.0f) return 1; else return 0;}}\
else  return 0; }\
else return 0; }}



int ccw_tri_tri_intersection_2d(double p1[2], double q1[2], double r1[2], 
                                double p2[2], double q2[2], double r2[2]) {
    if ( ORIENT_2D(p2,q2,p1) >= 0.0f ) {
        if ( ORIENT_2D(q2,r2,p1) >= 0.0f ) {
            if ( ORIENT_2D(r2,p2,p1) >= 0.0f ) return 1;
            else INTERSECTION_TEST_EDGE(p1,q1,r1,p2,q2,r2)
                } else {  
                    if ( ORIENT_2D(r2,p2,p1) >= 0.0f ) 
                        INTERSECTION_TEST_EDGE(p1,q1,r1,r2,p2,q2)
                        else INTERSECTION_TEST_VERTEX(p1,q1,r1,p2,q2,r2)}}
    else {
        if ( ORIENT_2D(q2,r2,p1) >= 0.0f ) {
            if ( ORIENT_2D(r2,p2,p1) >= 0.0f ) 
                INTERSECTION_TEST_EDGE(p1,q1,r1,q2,r2,p2)
                else  INTERSECTION_TEST_VERTEX(p1,q1,r1,q2,r2,p2)}
        else INTERSECTION_TEST_VERTEX(p1,q1,r1,r2,p2,q2)}
};


int tri_tri_overlap_test_2d(double p1[2], double q1[2], double r1[2], 
                            double p2[2], double q2[2], double r2[2]) {
    if ( ORIENT_2D(p1,q1,r1) < 0.0f )
        if ( ORIENT_2D(p2,q2,r2) < 0.0f )
            return ccw_tri_tri_intersection_2d(p1,r1,q1,p2,r2,q2);
        else
            return ccw_tri_tri_intersection_2d(p1,r1,q1,p2,q2,r2);
        else
            if ( ORIENT_2D(p2,q2,r2) < 0.0f )
                return ccw_tri_tri_intersection_2d(p1,q1,r1,p2,r2,q2);
            else
                return ccw_tri_tri_intersection_2d(p1,q1,r1,p2,q2,r2);
    
};

typedef struct _key_sort {
    VBModel* _child;
    VBObjectFile2DKeyFrame* _key;
} _key_sort;

int _key_sort_func(const void* _a, const void* _b) {
    _key_sort** _key_a = (_key_sort**)_a;
    _key_sort** _key_b = (_key_sort**)_b;
    int sortNum = (*_key_a)->_key->depth - (*_key_b)->_key->depth;
    return sortNum;
}

using namespace cocos2d;

void VBModel::SetTexture(VBTexture* _tex) {
    if(tex == NULL)
        tex = new cocos2d::CCTexture2D();
    
    tex->m_bPVRHaveAlphaPremultiplied = false;
    tex->m_bHasPremultipliedAlpha = false;
    if(_tex) {
        if(_tex->color_type == VBColorType_RGBA)
            tex->m_ePixelFormat = kCCTexture2DPixelFormat_RGBA8888;
        tex->m_uName = _tex->tid;
        tex->m_uPixelsWide = _tex->width;
        tex->m_uPixelsHigh = _tex->height;
        tex->m_tContentSize.width = _tex->width * CCDirector::sharedDirector()->getContentScaleFactor();
        tex->m_tContentSize.height = _tex->height * CCDirector::sharedDirector()->getContentScaleFactor();
    } else {
        tex->m_ePixelFormat = kCCTexture2DPixelFormat_RGBA8888;
        tex->m_uName = 0;
        tex->m_uPixelsWide = 0;
        tex->m_uPixelsHigh = 0;
        tex->m_tContentSize.width = 0;
        tex->m_tContentSize.height = 0;
    }
    tex->m_fMaxS = 1.0;
    tex->m_fMaxT = 1.0;
    this->setTexture(tex);
    VBVector2D _txc[4] = {{0,0},{0,1},{1,0},{1,1}};
    this->setTextureRect( cocos2d::CCRectMake(_txc[0].x * tex->getPixelsWide()
                                              ,_txc[0].y * tex->getPixelsHigh()
                                              ,_txc[3].x * tex->getPixelsWide() - _txc[0].x * tex->getPixelsWide()
                                              ,_txc[3].y  * tex->getPixelsHigh() - _txc[0].y * tex->getPixelsHigh() ) );
}

VBModel::VBModel(VBTexture* _tex) {
    is_bitmap = true;
    color = mix_color = VBColorRGBALoadIdentity();
    this->setAnchorPoint(ccp(0,0));
    is_animation_update = 0;
    is_use_animation = 0;
    is_play_loop = 0;
    is_play = 0;
    is_real_time_animation = 0;
    update_frame = 0;
    frame_rate = 0;
    frame = NULL;
    cur_frame = 0;
    frame_all_allocated_child_models = NULL;
    frame_willFree_child_models = NULL;
    frame_current_key_frame = NULL;
    library_name_id = NULL;
    tex = NULL;
    SetTexture(_tex);
}

VBModel::VBModel() {
    tex = NULL;
    is_bitmap = false;
    color = mix_color = VBColorRGBALoadIdentity();
    this->setAnchorPoint(ccp(0,0));
    is_animation_update = 0;
    is_use_animation = 0;
    is_play_loop = 0;
    is_play = 0;
    is_real_time_animation = 0;
    update_frame = 0;
    frame_rate = 0;
    frame = NULL;
    frame_current_key_frame = NULL;
    cur_frame = 0;
    frame_all_allocated_child_models = NULL;
    frame_willFree_child_models = NULL;
    frame_current_key_frame = NULL;
    library_name_id = NULL;
}

VBModel::VBModel(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, VBTexture* _texture, VBBool _is_realtime_animation) {
    tex = NULL;
    is_bitmap = false;
    color = mix_color = VBColorRGBALoadIdentity();
    this->setAnchorPoint(ccp(0,0));
    is_animation_update = 0;
    is_use_animation = true;
    is_play_loop = true;
    is_play = true;
    is_real_time_animation = _is_realtime_animation;
    update_frame = false;
    frame = NULL;
    frame_current_key_frame = NULL;
    cur_frame = 0.0;
    library_name_id = _library_name_id;
    this->is_real_time_animation = _is_realtime_animation;
    this->frame_rate = VBObjectFile2DGetFrameRate(_obj2D);
    this->is_use_animation = VBTrue;
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _library_name_id);
    void* _library_base = VBObjectFile2DLibraryGetBase(_library);
    if(VBObjectFile2DLibraryType_Bitmap == VBObjectFile2DLibraryGetType(_library)) {
        
        this->frame_all_allocated_child_models = NULL;
        this->frame_willFree_child_models = NULL;
        this->frame_current_key_frame = NULL;
        
        is_bitmap = true;
        VBObjectFile2DLibraryBitmap* _bitmap = (VBObjectFile2DLibraryBitmap*)_library_base;
        
        VBULong _poly_len = VBObjectFile2DLibraryBitmapGetUVInfoLength(_bitmap);
        
        VBVector2D _txc[_poly_len];
        VBVector2D* _uv = VBObjectFile2DLibraryBitmapGetUVInfo(_bitmap);
        
        VBVector2D* _txc_ptr = _txc;
        
        VBULong _i;
        
        for(_i = 0; _i < _poly_len; _i++) {
            _txc_ptr->x = _uv[_i].x;
            _txc_ptr->y = _uv[_i].y;
            _txc_ptr++;
        }
        tex = new cocos2d::CCTexture2D();
        
        tex->m_bPVRHaveAlphaPremultiplied = false;
        tex->m_bHasPremultipliedAlpha = false;
        if(_texture->color_type == VBColorType_RGBA)
            tex->m_ePixelFormat = kCCTexture2DPixelFormat_RGBA8888;
        tex->m_uName = _texture->tid;
        tex->m_fMaxS = 1.0;
        tex->m_fMaxT = 1.0;
        tex->m_uPixelsWide = _texture->width;
        tex->m_uPixelsHigh = _texture->height;
        tex->m_tContentSize.width = _texture->width * CCDirector::sharedDirector()->getContentScaleFactor();
        tex->m_tContentSize.height = _texture->height * CCDirector::sharedDirector()->getContentScaleFactor();
        this->setTexture(tex);
        
        this->setTextureRect( cocos2d::CCRectMake(_txc[0].x * tex->getPixelsWide() / CCDirector::sharedDirector()->getContentScaleFactor()
                                                  ,_txc[0].y * tex->getPixelsHigh() / CCDirector::sharedDirector()->getContentScaleFactor()
                                                  ,(_txc[2].x * tex->getPixelsWide() - _txc[0].x * tex->getPixelsWide()) / CCDirector::sharedDirector()->getContentScaleFactor()
                                                  ,(_txc[2].y  * tex->getPixelsHigh() - _txc[0].y * tex->getPixelsHigh()) / CCDirector::sharedDirector()->getContentScaleFactor() ) );
        
    } else if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library) || VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
        
        this->frame_all_allocated_child_models = VBArrayVectorInit(VBArrayVectorAlloc());
        this->frame_willFree_child_models = VBArrayVectorInit(VBArrayVectorAlloc());
        this->frame_current_key_frame = VBArrayVectorInit(VBArrayVectorAlloc());
        
        if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryGraphic* _graphic = (VBObjectFile2DLibraryGraphic*)_library_base;
            this->frame = VBObjectFile2DLibraryGraphicGetFrame(_graphic);
        } else if(VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryMovieClip* _movie_clip = (VBObjectFile2DLibraryMovieClip*)_library_base;
            this->frame = VBObjectFile2DLibraryMovieClipGetFrame(_movie_clip);
        }
        
        this->is_play = VBTrue;
        this->is_play_loop = VBTrue;
        this->is_animation_update = VBTrue;
        
        while (frame_all_allocated_child_models->len < frame->key_frame->len) {
            VBArrayVectorAddBack(frame_all_allocated_child_models, NULL);
        }
        for(int i = 0; i < frame->key_frame->len; i++) {
            VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)frame->key_frame->data[i];
            if(frame_all_allocated_child_models->data[i] == NULL) {
                VBModel* _child = new VBModel(_obj2D, _key_frame->library_id, _texture, _is_realtime_animation);
                frame_all_allocated_child_models->data[i] = _child;
                VBArrayVectorAddBack(frame_willFree_child_models, _child);
                Link(i, _child, _key_frame);
            }
        }
    }
    VBModelUpdate(0.0f);
}

void VBModel::Link(int _currentIdx, VBModel* _child, VBObjectFile2DKeyFrame* _key_frame) {
    int j;
    if(_key_frame->element->element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
        VBObjectFile2DKeyFrameElementGraphic* _grap = (VBObjectFile2DKeyFrameElementGraphic*)_key_frame->element->element;
        if(VBObjectFile2DKeyFrameElementGraphicGetNext(_grap)) {
            for(j = _currentIdx; j < frame->key_frame->len; j++) {
                VBObjectFile2DKeyFrame* _key_frame_ot = (VBObjectFile2DKeyFrame*)frame->key_frame->data[j];
                if(_key_frame_ot->element->element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
                    VBObjectFile2DKeyFrameElementGraphic* _grap_ot = (VBObjectFile2DKeyFrameElementGraphic*)_key_frame_ot->element->element;
                    if(VBObjectFile2DKeyFrameElementGraphicGetNext(_grap) == _grap_ot) {
                        frame_all_allocated_child_models->data[j] = _child;
                        if(j + 1 < frame->key_frame->len)
                            Link(j + 1, _child, _key_frame_ot);
                        break;
                    }
                }
            }
        }
    }
    if(_key_frame->element->element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
        VBObjectFile2DKeyFrameElementMovieClip* _mc = (VBObjectFile2DKeyFrameElementMovieClip*)_key_frame->element->element;
        if(VBObjectFile2DKeyFrameElementMovieClipGetNext(_mc)) {
            for(j = _currentIdx; j < frame->key_frame->len; j++) {
                VBObjectFile2DKeyFrame* _key_frame_ot = (VBObjectFile2DKeyFrame*)frame->key_frame->data[j];
                if(_key_frame_ot->element->element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                    VBObjectFile2DKeyFrameElementMovieClip* _mc_ot = (VBObjectFile2DKeyFrameElementMovieClip*)_key_frame_ot->element->element;
                    if(VBObjectFile2DKeyFrameElementMovieClipGetNext(_mc) == _mc_ot) {
                        frame_all_allocated_child_models->data[j] = _child;
                        if(j + 1 < frame->key_frame->len)
                            Link(j + 1, _child, _key_frame_ot);
                        break;
                    }
                }
            }
        }
    }
}


VBModel::~VBModel() {
    if(getChildren()) {
        while(getChildren()->count())
            removeChild((VBModel*)getChildren()->objectAtIndex(0), false);
    }
    if(tex) {
        m_pobTexture->release();
        m_pobTexture = NULL;
        tex->m_uName = 0;
        delete tex;
        tex = NULL;
    }
    
    if(frame_current_key_frame) {
        while(VBArrayVectorGetLength(frame_current_key_frame)) {
            _key_sort* _key = (_key_sort*)VBArrayVectorRemoveBack(this->frame_current_key_frame);
            VBSystemFree(_key);
        }
        VBArrayVectorFree(&frame_current_key_frame);
    }
    
    if(frame_willFree_child_models) {
        while(VBArrayVectorGetLength(frame_willFree_child_models)) {
            VBModel* _child = (VBModel*)VBArrayVectorRemoveBack(frame_willFree_child_models);
            delete _child;
        }
        VBArrayVectorFree(&frame_willFree_child_models);
    }
    if(frame_all_allocated_child_models)
        VBArrayVectorFree(&frame_all_allocated_child_models);
}

VBModel* VBModel::getVBModelByName(char* name) {
    if(frame) {
        if(frame->key_frame) {
            if(this->getChildren()) {
                for(int i = 0; i < this->getChildren()->count(); i++) {
                    VBModel* _child = (VBModel*)this->getChildren()->objectAtIndex(i);
                    if(strcmp((char*)_child->library_name_id->libraryName->data, name) == 0){
                        return _child;
                    } else {
                        VBModel* _child2 = _child->getVBModelByName(name);
                        if( _child2 ){
                            return _child2;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

VBModel* VBModel::getVBModelByInstanceName(const char* _name) {
    int i;
    if(frame) {
        if(frame->key_frame) {
            for(i = 0; i < frame->key_frame->len; i++) {
                VBObjectFile2DKeyFrame* _k_frame = (VBObjectFile2DKeyFrame*)frame->key_frame->data[i];
                if(_k_frame->element->element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                    VBObjectFile2DKeyFrameElementMovieClip* _mc = (VBObjectFile2DKeyFrameElementMovieClip*)_k_frame->element->element;
                    if(_mc->instance_name) {
                        if(strcmp((const char*)_mc->instance_name->data, _name) == 0) {
                            return (VBModel*)frame_all_allocated_child_models->data[i];
                        }
                    }
                }
            }
        }
    }
    return VBNull;
}

void VBModel::VBModelUpdateColor(VBColorRGBA _color) {
    mix_color = VBColorRGBAMultiply(color, _color);
    if(is_bitmap) {
        ccColor3B _color3B;
        _color3B.r = mix_color.r;
        _color3B.g = mix_color.g;
        _color3B.b = mix_color.b;
        setColor(_color3B);
        setOpacity(mix_color.a);
    }
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)this->getChildren()->objectAtIndex(i);
            _child->VBModelUpdateColor(mix_color);
        }
    }
}

void VBModel::VBModelUpdate(float _tick) {
    if(this->frame) { //모델에 애니메이션 정보가 존재하는지 검사한다.
        if(this->is_play) { //모델의 애니메이션이 플레이 중인지 검사한다.
            //현재 프레임을 증가시킨다.
            if ( !this->update_frame ){
                this->cur_frame += _tick * this->frame_rate;
            }else{
                this->update_frame = VBFalse;
            }
            if(this->cur_frame > this->frame->total_frame - 1) { //모델의 현재 프레임이 전체 프레임 수 보다 큰지 검사한다.
                if(this->is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 초기 프레임으로 변경한다.
                    this->cur_frame = 0;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    this->is_play = VBFalse;
                    this->cur_frame = this->frame->total_frame - 1;
                }
            } else if(this->cur_frame < 0.0) {
                if(this->is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 마지막 프레임으로 변경한다.
                    this->cur_frame = this->frame->total_frame - 1;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    this->is_play = VBFalse;
                }
            }
            //모델의 애니메이션이 업데이트 되었음을 설정한다.
            this->is_animation_update = VBTrue;
        }else{
            if ( this->update_frame ){
                this->is_animation_update = VBTrue;
            }
        }
        this->update_frame = VBFalse;
        
        //애니메이션이 업데이트 되었을 경우 차일드 리스트에서 삭제하고 애니메이트 된다.
        if(this->frame_current_key_frame) {
            if(this->is_animation_update) {
                while(this->frame_current_key_frame->len) {
                    _key_sort* _key = (_key_sort*)VBArrayVectorRemoveBack(this->frame_current_key_frame);
                    this->removeChild(_key->_child, false);
                    VBSystemFree(_key);
                }
                for(int i = 0; i < this->frame->key_frame->len; i++) {
                    VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)this->frame->key_frame->data[i];
                    if((float)_key_frame->end_frame <=  this->cur_frame) {
                        continue;
                    }
                    if((float)_key_frame->begin_frame > this->cur_frame) {
                        break;
                    }
                    _key_sort* _key = (_key_sort*)VBSystemCalloc(1, sizeof(_key_sort));
                    _key->_key = _key_frame;
                    _key->_child = (VBModel*)frame_all_allocated_child_models->data[i];
                    VBArrayVectorAddBack(this->frame_current_key_frame, _key);
                }
                VBArrayVectorQuickSort(this->frame_current_key_frame, _key_sort_func);
                
                if(this->is_real_time_animation) {
                    for(int i = 0; i < this->frame_current_key_frame->len; i++) {
                        _key_sort* _key = (_key_sort*)this->frame_current_key_frame->data[i];
                        VBModel* child = (VBModel*)_key->_child;
                        if(child->is_use_animation) {
                            VBObjectFile2DKeyFrame* _key_frame = _key->_key;
                            VBULong _b = VBObjectFile2DKeyFrameGetBeginFrame(_key_frame);
                            VBULong _e = VBObjectFile2DKeyFrameGetEndFrame(_key_frame);
                            VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame);
                            if(VBObjectFile2DKeyFrameElementType_Bitmap == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBObjectFile2DKeyFrameElementBitmap* _bitmap = (VBObjectFile2DKeyFrameElementBitmap*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBMatrix2DWrapper mat = _bitmap->matrix;
                                child->setPosition(CCPoint(mat.position.x , -mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, -mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                child->setSkewX(mat.shear.x);
                                child->setSkewY(-mat.shear.y);
                                child->setRotation(-mat.rotation);
                            } else if(VBObjectFile2DKeyFrameElementType_Graphic == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBObjectFile2DKeyFrameElementGraphic* _graphic = (VBObjectFile2DKeyFrameElementGraphic*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (this->cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(_graphic, t, &mat, &child->color);
                                child->setPosition(CCPoint(mat.position.x, -mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, -mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                child->setSkewX(mat.shear.x);
                                child->setSkewY(-mat.shear.y);
                                child->setRotation(-mat.rotation);
                            } else if(VBObjectFile2DKeyFrameElementType_MovieClip == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBObjectFile2DKeyFrameElementMovieClip* _movie_clip = (VBObjectFile2DKeyFrameElementMovieClip*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (this->cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(_movie_clip, t, &mat, &child->color); 
                                child->setPosition(CCPoint(mat.position.x, -mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, -mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                child->setSkewX(mat.shear.x);
                                child->setSkewY(-mat.shear.y);
                                child->setRotation(-mat.rotation);
                            }
                        }
                        this->addChild(child);
                    }
                }
            }
            this->is_animation_update = VBFalse;
        }
    }
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)this->getChildren()->objectAtIndex(i);
            _child->VBModelUpdate(_tick);
        }
    }
}

void VBModel::setIsPlay(VBBool flag) {
    this->is_play = flag;
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)this->getChildren()->objectAtIndex(i);
            _child->setIsPlay(flag);
        }
    }
}

void VBModel::setIsPlayLoop(VBBool flag) {
    this->is_play_loop = flag;
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)this->getChildren()->objectAtIndex(i);
            _child->setIsPlayLoop(flag);
        }
    }
}

void VBModel::gotoAndPlay(float pos) {
    this->setIsPlay(VBTrue);
    this->update_frame = VBTrue;
    this->cur_frame = pos;
}

void VBModel::gotoAndStop(float pos) {
    this->setIsPlay(VBFalse);
    this->update_frame = VBTrue;
    this->cur_frame = pos;
}

void VBModel::play() {
    this->setIsPlay(VBTrue);
}

void VBModel::stop() {
    this->setIsPlay(VBFalse);
}

void VBModel::setTextureRectInPixels(CCRect rect, bool rotated, CCSize size) {
    m_obRectInPixels = rect;
	m_obRect = CC_RECT_PIXELS_TO_POINTS(rect);
	m_bRectRotated = rotated;
    
	setContentSizeInPixels(size);
	updateTextureCoords(m_obRectInPixels);
    
	CCPoint relativeOffsetInPixels = m_obUnflippedOffsetPositionFromCenter;
    
	if (m_bFlipX)
	{
		relativeOffsetInPixels.x = -relativeOffsetInPixels.x;
	}
	if (m_bFlipY)
	{
		relativeOffsetInPixels.y = -relativeOffsetInPixels.y;
	}
    
	m_obOffsetPositionInPixels.x = relativeOffsetInPixels.x + (m_tContentSizeInPixels.width - m_obRectInPixels.size.width) / 2;
	m_obOffsetPositionInPixels.y = relativeOffsetInPixels.y + (m_tContentSizeInPixels.height - m_obRectInPixels.size.height) / 2;
    
	if (m_bUsesBatchNode)
	{
		m_bDirty = true;
	}
	else
	{
		m_sQuad.bl.vertices = vertex3(0, 0, 0);
		m_sQuad.br.vertices = vertex3(m_obRectInPixels.size.width, 0, 0);
		m_sQuad.tl.vertices = vertex3(0, -m_obRectInPixels.size.height, 0);
		m_sQuad.tr.vertices = vertex3(m_obRectInPixels.size.width, -m_obRectInPixels.size.height, 0);
	}
}

void VBModel::updateTextureCoords(CCRect rect) {
    CCTexture2D *tex = m_bUsesBatchNode ? m_pobTextureAtlas->getTexture() : m_pobTexture;
	if (! tex)
	{
		return;
	}
    
	float atlasWidth = (float)tex->getPixelsWide();
	float atlasHeight = (float)tex->getPixelsHigh();
    
	float left, right, top, bottom;
    
    left	= rect.origin.x/atlasWidth;
    right	= left + rect.size.width/atlasWidth;
    top		= rect.origin.y/atlasHeight;
    bottom	= top + rect.size.height/atlasHeight;
    
    m_sQuad.bl.texCoords.u = left;
    m_sQuad.bl.texCoords.v = top;
    m_sQuad.br.texCoords.u = right;
    m_sQuad.br.texCoords.v = top;
    m_sQuad.tl.texCoords.u = left;
    m_sQuad.tl.texCoords.v = bottom;
    m_sQuad.tr.texCoords.u = right;
    m_sQuad.tr.texCoords.v = bottom;
    
}

CCAffineTransform VBModel::nodeToParentTransform(void) {
	if (m_bIsTransformDirty) {
        mat = VBMatrix2DWrapperLoadIdentity();
		
        mat = VBMatrix2DWrapperSetPosition(mat, VBVector2DCreate(m_tPosition.x, m_tPosition.y));
        mat = VBMatrix2DWrapperSetScale(mat, VBVector2DCreate(m_fScaleX, m_fScaleY));
        mat = VBMatrix2DWrapperSetShear(mat, VBVector2DCreate(m_fSkewX, m_fSkewY));
        mat = VBMatrix2DWrapperSetRotation(mat, m_fRotation);
        mat = VBMatrix2DWrapperSetAnchor(mat, VBVector2DCreate(m_tAnchorPoint.x, m_tAnchorPoint.y));
        mat = VBMatrix2DWrapperUpdate(mat);
        
		m_tTransform = CCAffineTransformMake(mat.mat.m11, mat.mat.m21, mat.mat.m12, mat.mat.m22, mat.mat.m13, mat.mat.m23);
        
		m_bIsTransformDirty = false;
	}
    
	return m_tTransform;
}

// p1, p2, p3는 삼각형의 세 점 cp는 현재 마우스 좌표
// cp가 삼각형내에 있으면 TRUE 삼각형 밖이면 FALSE
bool CheckTriangle(CCPoint p1, CCPoint p2, CCPoint p3, CCPoint cp)
{
    //p1, p2, p3의 세 점의 y값을 기준으로 순서 정렬 작은값 -> 큰값
    CCPoint temp;
    if(p1.y > p2.y)
    {
        temp = p1;
        p1 = p2;
        p2 = temp;
    }
    
    if(p1.y > p3.y)
    {
        temp = p1;
        p1 = p3;
        p3 = temp;
    }
    if(p2.y > p3.y)
    {
        temp = p2;
        p2 = p3;
        p3 = temp;
    }
    //---------------------------------------------------------
    
    // 현재 마우스좌표의 y값이 p1.y와 p3.y의 밖에 있으면 FALSE 리턴
    if(cp.y < p1.y || cp.y > p3.y) return false;
    
    // 기울기로 사용할 변수 m1, m2
    int m1, m2;
    
    // 마우스좌표의 y값에 대응되는 삼각형의 x좌표 2개
    int x1, x2, tmp;
    
    // 삼각형의 3점의 중간 y값이 마우스y값보다 작으면 
    // 마우스좌표는 p1.y와 p2.y값 사이에 있으므로
    // 마우스좌표x의 값은 점p1과 p2을 연결하는 선의 기울기를 구하여 
    // 마우스좌표y에 대응되는 x값을구한다(점p1과 점p3도 마찬가지)
    // 구해진 x값2개사이에 마우스좌표x가 있으면 삼각형안 이고 아니면 삼각형 밖이다.
    // 마우스좌표y가 p2.y와 p3.y사이에 있으면 점p3과 p2, 점p3과 p1의 기울기를 구하여 위의 방법으로 계산한다.
    if(cp.y <= p2.y)
    {
        // 점p1과 점p2에 대한 기울기(고정소수점)
        m1 = (((int)p2.x - (int)p1.x)<<16) / (p2.y - p1.y);
        
        // 점p1과 점p3에 대한 기울기
        m2 = (((int)p3.x - (int)p1.x)<<16) / (p3.y - p1.y);
        
        // 기울기를 가지고 마우스y에대응되는 x값 구함
        x1 = p1.x + ((int)((cp.y - p1.y) * m1) >> 16);
        x2 = p1.x + ((int)((cp.y - p1.y) * m2) >> 16);
        
        // x1, x2스왑                
        if(x1 > x2)
        {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        
        // x1과 x2사이에 있는지 비교
        if(cp.x < x1 || cp.x > x2) return false;
        return true;
    }
    else
    {
        m1 = ((int)(p2.x - p3.x)<<16) / (p2.y - p3.y);
        
        m2 = ((int)(p1.x - p3.x)<<16) / (p1.y - p3.y);
        
        x1 = p3.x + ((int)((cp.y - p3.y) * m1) >> 16);
        x2 = p3.x + ((int)((cp.y - p3.y) * m2) >> 16);
        
        if(x1 > x2)
        {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        if(cp.x < x1 || cp.x > x2) return false;
        return true;
    }
}

VBAABB VBModel::getVBModelSize() {
    if(is_bitmap) {
        CCPoint tl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y), nodeToWorldTransform());
        CCPoint tr = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y), nodeToWorldTransform());
        CCPoint bl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y), nodeToWorldTransform());
        CCPoint br = CCPointApplyAffineTransform(CCPointMake(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y), nodeToWorldTransform());
        VBVector2D vtx[4] = {{tl.x,tl.y}, {tr.x,tr.y}, {bl.x,bl.y}, {br.x,br.y}};
        return VBAABBCreateWithVertex(vtx, 4);
    }
    VBAABB _aabb = VBAABBLoadIndentity();
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            _aabb = VBAABBMerge(_aabb, ((VBModel*)this->getChildren()->objectAtIndex(i))->getVBModelSize());
        }
    }
    return _aabb;
}

bool VBModel::checkCollisionWithButton(CCPoint pos) {
    if(is_bitmap) {
        CCPoint _pos = pos;
        if(CCDirector::sharedDirector()->isRetinaDisplay()) {
            float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
            _pos.x *=  scale;
            _pos.y *=  scale;
        }
        CCPoint tl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y), nodeToWorldTransform());
        CCPoint tr = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y), nodeToWorldTransform());
        CCPoint bl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y), nodeToWorldTransform());
        CCPoint br = CCPointApplyAffineTransform(CCPointMake(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y), nodeToWorldTransform());
        
        if(CheckTriangle(tl, tr, bl, _pos))
            return true;
        if(CheckTriangle(bl, tr, br, _pos))
            return true;
    }
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            if(((VBModel*)this->getChildren()->objectAtIndex(i))->checkCollisionWithButton(pos))
                return true;
        }
    }
    return false;
}

int VBModel::getVertex(int _idx, CCPoint* _vert) {
    if(is_bitmap) {
        if(_idx == 0) {
            CCPoint tl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y), nodeToWorldTransform());
            CCPoint tr = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y), nodeToWorldTransform());
            CCPoint bl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y), nodeToWorldTransform());
            CCPoint br = CCPointApplyAffineTransform(CCPointMake(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y), nodeToWorldTransform());
            _vert[0] = tl;
            _vert[1] = tr;
            _vert[2] = bl;
            _vert[3] = br;
        }
        _idx--;
    }
    if(_idx < 0) {
        //성공시 -1 리턴
        return _idx;
    }
    
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            int _subIdx = ((VBModel*)getChildren()->objectAtIndex(i))->getVertex(_idx, _vert);
            if(_subIdx < 0)
                return _subIdx;
            else
                _idx -= (_idx - _subIdx);
        }
    }
    
    //실패시 그냥 리턴
    return _idx;
}

bool VBModel::hitTest(VBModel* _ot) {
    CCPoint vert[4];
    int vertIdx = 0;
    int remain = 1;
    while(remain > 0) {
        remain = getVertex(vertIdx, vert);
        vertIdx++;
        //printf("remain %i\n", remain);
        CCPoint vert2[4];
        int vertIdx2 = 0;
        int remain2 = 1;
        while(remain2 > 0) {
            remain2 = _ot->getVertex(vertIdx2, vert2);
            vertIdx2++;
            //printf("    remain %i\n", remain2);
            double p[4][2];
            double d[4][2];
            for(int i = 0; i < 4; i++) {
                p[i][0] = vert[i].x;
                p[i][1] = vert[i].y;
                d[i][0] = vert2[i].x;
                d[i][1] = vert2[i].y;
            }
            if(tri_tri_overlap_test_2d(p[0], p[1], p[2], d[0], d[1], d[2]))
                return true;
            if(tri_tri_overlap_test_2d(p[0], p[1], p[2], d[2], d[1], d[3]))
                return true;
            if(tri_tri_overlap_test_2d(p[2], p[1], p[3], d[0], d[1], d[2]))
                return true;
            if(tri_tri_overlap_test_2d(p[2], p[1], p[3], d[2], d[1], d[3]))
                return true;
        }
    }
    return false;
}
