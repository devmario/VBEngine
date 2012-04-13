//
//  OverlapTester.h
//  gelatomania
//
//  Created by wonhee jang on 12. 3. 25..
//  Copyright (c) 2012년 VanillaBreeze. All rights reserved.
//

#ifndef gelatomania_OverlapTester_h
#define gelatomania_OverlapTester_h

#include "cocos2d.h"

using namespace cocos2d;

// p1, p2, p3는 삼각형의 세 점 cp는 현재 마우스 좌표
// cp가 삼각형내에 있으면 TRUE 삼각형 밖이면 FALSE
bool CheckTriangle(CCPoint p1, CCPoint p2, CCPoint p3, CCPoint cp);

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


#endif
