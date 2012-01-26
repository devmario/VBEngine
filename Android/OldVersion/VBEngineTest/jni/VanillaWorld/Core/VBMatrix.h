/**
 @file Core/VBMatrix.h
 @brief VBEngine의 VBMatrix 구조체타입과 여러 함수들.
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

#ifndef __VBMatrix_H__
#define __VBMatrix_H__

#include "VBMatrix2D.h"
#include "VBMatrix3D.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 @brief 2D Matrix로 3D 매트릭스를 구합니다. 
 @param _mat2D 2D 매트릭스.
 @return _mat3D 3D 매트릭스.
 */
VBMatrix3D VBMatrix2DGetVBMatrix3D(VBMatrix2D _mat2D);

#ifdef __cplusplus
}
#endif

#endif