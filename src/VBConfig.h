/**
 @file VBConfig.h
 @brief VBEngine의 VBConfig 구조체타입과 여러 함수들.
 @author 
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section Lisence
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#include <limits.h>

#ifndef __VBConfig_H__
#define __VBConfig_H__

//운영체제 비트수: 아래위 옵션중 하나만 킬수 있습니다.(한개도 켜지 않을경우 빌드에러가 납니다.)
#define _VB_OS32_
//#define _VB_OS64_

//플랫폼: 아래위 옵션중 하나만 킬수 있습니다.(한개도 켜지 않을경우 빌드에러가 납니다.)
//#define _VB_IPHONE_
#define _VB_ANDROID_
//#define _VB_MAC_
//#define _VB_WINDOW_
//#define _VB_UNITY_3D_

//이옵션을 키면 디버그 모드로 작동합니다.(로그출력 및 로그파일에 로그 쓰기)
//#define _VB_DEBUG_
//디버그모드시 로그출력이나 로그파일출력때 쓰는 버퍼 사이즈
//#define _VB_DEBUG_PRINT_BUFFER_SIZE_ USHRT_MAX

//이옵션을 키면 모든 drawable을 텍스쳐없이 GL_LINE_LOOP로 그립니다.
//#define _VB_VISIBLE_VERTEX_LINE_

//바운딩 박스 컬링을 사용할 것인가
//#define _VB_USE_BBTREE_

#endif