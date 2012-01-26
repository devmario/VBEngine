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

#include "Core/VBString.h"
#include "Core/VBArray.h"
#include "Core/VBColor.h"
#include "Core/VBVector.h"
#include "Core/VBMatrix.h"
#include "Core/Spline/VBSpline.h"
#include "Core/VBQuadtree.h"
#include "Core/VBTriangle.h"
#include "Core/VBAABB.h"

#include "Display/VBImage.h"
#include "Display/VBTexture.h"
#include "Display/VBGraphic.h"
#include "Display/VBModel.h"
#include "Display/VBDrawable.h"
#include "Display/VBBlendMode.h"

#include "IO/VBSystem.h"
#include "IO/VBFile.h"
#include "IO/VBPNGFile.h"
#include "IO/VBJPEGFile.h"
#include "IO/VBObjectFile.h"
#include "IO/VBTouch.h"
#include "IO/VBThread.h"

#include "Util/VBDebug.h"
#include "Util/VBTween.h"

#include "VBDisplay2D.h"
#include "VBDisplay3D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    enum {
        UNIFORM_MVPMATRIX,
        UNIFORM_TEXTURE,
        NUM_UNIFORMS
    };
    
    enum {
        ATTRIB_VERTEX,
        ATTRIB_TEXCOORD,
        ATTRIB_COLOR_PERCENT,
        ATTRIB_COLOR_ADD,
        NUM_ATTRIBUTES
    };
    
    VBVector2D VBEngineGetScreenResoulution(void);
    /**
     @brief VB엔진의 초기화 작업을 진행합니다.
     @param _res_path 리소스 경로.
     @param _rw_doc_path 도큐먼트 경로.
     @return VB엔진 초기화 작업의 성공 여부를 리턴합니다. VBTrue이면 성공, VBFalse이면 실패.
     
     <b>Example</b>
     <table bgcolor="#DDDDDD">
         <tr>
             <td>
                 NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
                 NSString* documentDirectory = [paths objectAtIndex:0];
                 VBEngineStart([[[NSBundle mainBundle] resourcePath] UTF8String], [documentDirectory UTF8String]);
             </td>
         </tr>
	 </table>
     */
	VBBool VBEngineStart(const VBChar* _res_path, const VBChar* _rw_doc_path);
	
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
     @brief 2D Line을 그리는데 쓰이는 텍스쳐를 반환합니다.
     @return 2D Line의 텍스쳐.
     */
	VBTexture* VBEngineGetGraphic2DLineTexture(void);
    
    VBFloat VBEngineOpenGLGetIsSuportedShader(void);
    
    VBULong VBEngineOpenGLGetProgram(void);
    
    VBLong* VBEngineOpenGLGetUniform();
	
    void VBEngineSetClearColor(VBColorRGBAf _clear_color);
    VBColorRGBAf VBEngineGetClearColor(void);
    void VBEngineClearDisplay(void);
    
#ifdef __cplusplus
}
#endif

#endif
