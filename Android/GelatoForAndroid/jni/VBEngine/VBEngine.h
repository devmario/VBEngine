/**
 @mainpage  VBEngine Project for 2D Games
 @section intro 소개
 - Vanilla Breeze의 강력한 모바일 에니메이션 엔진입니다.
 - <strong>What is Granular Synthesis</strong> 
 <p>Granular synthesis is a technique that involves dividing a sample into very short pieces, and then playing the pieces back superimposed and crossfaded with one another. These pieces, or "grains," are usually under 50 milliseconds long and sound like short clicks when heard individually. But when layered together, grains can produce lush textures with rich modulation possibilities.</p> 
 - <strong>Using the Granulator</strong> 
 <p>To use the Granulator, drag a sample onto its waveform display. You can then adjust the length of the grains and the density of their overlap with the Grain control. The playback position within the soundfile is set with the FilePos knob and can be modulated randomly or via the built-in LFO.</p> 
 <p>In addition to controls that influence the playback of the grains, there are also a number of "classical" synthesis parameters such as an ADSR envelope, two multimode filters and an FM oscillator that can dramatically alter the overall timbre.</p> 
 - <strong>Granulator Companion Device</strong> 
 <p>Granulator comes with a companion device called GranulatorInput that enables live input functionality for the Granulator. When the GranulatorInput device is on a track, any audio on that track can be captured in real-time by pressing Granulator's Grab button. The captured audio is then loaded into the Granulator automatically.</p> 
 @section  CREATEINFO      작성정보
 - 작성자      :   
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th><th>Mobile No.</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td><td>82-(0)10-xxxx-xxxx</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td><td>82-(0)10-xxxx-xxxx</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td><td>82-(0)10-xxxx-xxxx</td></tr>
 </table>
 - 작성일      :   2011/01/28
 - Version    : 1.0
 - 참조        :
 <ul>
 <li>@ref http://www.google.com</li>
 <li>@ref http://www.naver.com</li>
 <li>@ref http://www.daum.com</li>
 <li>@ref http://www.yahoo.com</li>
 <li>@ref http://www.joinc.com</li>
 <li>@ref http://www.nate.com</li>
 <li>@ref http://www.start.vanillabreeze.com</li>
 </ul>
 */

/**
 @file VBEngine.h
 @brief VBEngine의 VBEngine 구조체타입과 여러 함수들.
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

#ifndef __VBEngine_H__
#define __VBEngine_H__

#include "VBConfig.h"

#include "VBType.h"

#include "Core/Color/VBColor.h"
#include "Core/Color/VBColorG.h"
#include "Core/Color/VBColorGA.h"
#include "Core/Color/VBColorRGB.h"
#include "Core/Color/VBColorRGBA.h"

#include "Core/Linear/VBVector2D.h"
#include "Core/Linear/VBMatrix2D.h"
#include "Core/Linear/VBMatrix2DWrapper.h"
#include "Core/Linear/VBLine2D.h"
#include "Core/Linear/VBTriangle2D.h"
#include "Core/Linear/VBSpline2DBezierCubic.h"
#include "Core/Linear/VBAABB.h"

#include "Util/VBString.h"
#include "Util/VBDebug.h"
#include "Util/VBMath.h"
#include "Util/VBArrayList.h"
#include "Util/VBArrayVector.h"

#include "Display/VBDisplay2D.h"
#include "Display/VBDrawable2D.h"
#include "Display/VBImage.h"
#include "Display/VBTexture.h"
#include "Display/VBModel2D.h"
#include "Display/VBCamera2D.h"

#include "IO/VBSystem.h"
#include "IO/VBFile.h"
#include "IO/VBObjectFile2D.h"
#include "IO/VBObjectFile2DFrame.h"
#include "IO/VBObjectFile2DKeyFrame.h"
#include "IO/VBObjectFile2DKeyFrameElement.h"
#include "IO/VBObjectFile2DLibrary.h"
#include "IO/VBObjectFile2DLibraryNameID.h"
#include "IO/VBObjectFile2DTexcoord.h"
#include "IO/VBObjectFile2DTransition.h"
#include "IO/VBObjectFile2D.h"
#include "IO/VBPNGFile.h"
#include "IO/VBTouch.h"

#include "Other/zlib/zlib.h"
#include "Other/png/png.h"

// Use #include <unistd.h>  
#ifdef __ANDROID__
#include <unistd.h>  
/* access function */
// #define	F_OK		0	/* test for existence of file */
// #define	X_OK		0x01	/* test for execute or search permission */
// #define	W_OK		0x02	/* test for write permission */
// #define	R_OK		0x04	/* test for read permission */
// extern int access(const char *, int);
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    
    VBVector2D VBEngineGetScreenResoulution(void);
    /**
     @brief VB엔진의 초기화 작업을 진행합니다.
     @param _res_path 리소스 경로.
     @param _rw_doc_path 도큐먼트 경로.
     @param _screen_width의 x축해상도 사이즈
     @param _screen_height 디바이스의 y축해상도 사이즈
     @return VB엔진 초기화 작업의 성공 여부를 리턴합니다. VBTrue이면 성공, VBFalse이면 실패.
     
     <b>Example</b>
     <table bgcolor="#DDDDDD">
         <tr>
             <td>
                 NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
                 NSString* documentDirectory = [paths objectAtIndex:0];
                 VBEngineStart([[[NSBundle mainBundle] resourcePath] UTF8String], [documentDirectory UTF8String], [UIScreen mainScreen].currentMode.size.height, [UIScreen mainScreen].currentMode.size.width);
             </td>
         </tr>
	 </table>
     */
	VBBool VBEngineStart(const VBChar* _res_path, const VBChar* _rw_doc_path, VBUShort _screen_width, VBUShort _screen_height, VBUShort _default_resource_screen_width, VBUShort _default_resource_screen_height);
	
    /**
     @brief VB엔진을 종료합니다.
     @return VB엔진 종료의 성공 여부. VBTrue이면 성공, VBFalse이면 실패.
     */
	VBBool VBEngineShutdown(void);
	
    /**
     @brief VB엔진이 초기화 되었는지 여부를 반환합니다.
     @return VBTrue이면 초기화 됨, VBFalse이면 초기화 안됨.
     */
	VBBool VBEngineGetIsRunning(void);
	
    /**
     @brief 기본 디버거를 반환합니다.
     @return 기본 디버거.
     */
	VBDebug* VBEngineGetDefaultDebuger(void);
	
    /**
     @brief 설정된 리소스 경로를 반환합니다.
     @return 리소스 경로.
     */
	VBString* VBEngineGetResourcePath(void);
	
    /**
     @brief 도큐먼트 경로를 반환합니다.
     @return 도큐먼트 경로.
     */
	VBString* VBEngineGetDocumentPath(void);
    
	/**
     @brief 엔진의 기본 배경 색상을 설정합니다.
     */
    void VBEngineSetClearColor(VBColorRGBA _clear_color);
    
    /**
     @brief 엔진의 기본 배경 색상을 반환합니다.
     @return 배경색상.
     */
    VBColorRGBA VBEngineGetClearColor(void);
    
    /**
     @brief 엔진의 화면의 픽셀들을 배경색상으로 모두 채웁니다.
     */
    void VBEngineClearDisplay(void);
    
    /**
     @brief 엔진해상도의 사이즈를 반환합니다.
     @return 스크린 사이즈.
     */
    VBVector2D VBEngineGetScreenSize(void);
    
    /**
     @brief 기준이 되는 좌표계의 사이즈를 반환합니다.
     @return 좌표계.
     */
    VBVector2D VBEngineGetDefaultResourceScreenSize(void);
    
#ifdef __cplusplus
}
#endif

#endif
