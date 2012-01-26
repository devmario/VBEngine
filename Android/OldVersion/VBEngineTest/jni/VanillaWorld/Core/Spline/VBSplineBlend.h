/**
 @file Core/Spline/VBSplineBlend.h
 @brief VBSplineBlend 구조체 및 함수들
 @author
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section License
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBSplineBlend_H__
#define __VBSplineBlend_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "../../VBType.h"
	
    /**
     @brief 
     @param _ctr_num
     @param _ctr_idx
     @param _t
     */
	VBFloat VBSplineBlendBezier(VBULong _ctr_num, VBULong _ctr_idx, VBFloat _t);
	
#ifdef __cplusplus
}
#endif

#endif