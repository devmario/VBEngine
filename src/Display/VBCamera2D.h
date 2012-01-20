/**
 @file Display/VBCamera2D.h
 @brief VBDisplay2D 의 시점을 컨트롤 할수있는 VBCamera2D 구조체와 함수들
 
 VBCamera2D 는 카메라같은 간단한 조작으로 VBMatrix2D 를 만들어 낼 수 있는 소스 입니다.\n
 VBCamera2D 를 이용하여 VBDisplay2D 의 카메라를 조작해 주세요.\n
 
 @author 문서에 잘못된 부분이 있거나 각종 문의사항은 mario@vanillabreeze.com로 연락 바랍니다.
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th><th>Mobile Phone</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td><td>82-(0)10-4443-0711</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td><td>82-(0)10-2624-6873</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td><td>82-(0)10-6825-3221</td></tr>
 </table>
 @version 1.0
 @section License
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBCamera2D_H__
#define __VBCamera2D_H__

#include "VBType.h"
#include "../Core/Linear/VBMatrix2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
	 @brief VBCamera2D 에서 사용되는 모드들.
	 */
    enum {
        /**
         기본 모드.
         */
        VBCamera2DMode_Default  =   0x00,
        
        /**
         왼쪽으로 눞혔을때 모드.
         */
        VBCamera2DMode_Left     =   0x01,
        
        /**
         오른쪽으로 눞혔을때 모드.
         */
        VBCamera2DMode_Right    =   0x02,
        
        /**
         뒤집었을때 모드.
         */
        VBCamera2DMode_Reverse  =   0x03,
    };
    /**
	 @brief VBCamera2D 에서 사용되는 모드의 타입정의.
	 */
    typedef VBUChar VBCamera2DMode;
    
    /**
     @brief VBCamera2D 구조체 타입 정의
     */
    typedef struct VBCamera2D VBCamera2D;
    
    /**
     @brief VBCamera2D 정보 구조체
     */
    struct VBCamera2D {
        /**
         카메라의 위치
         */
        VBVector2D position;
        
        /**
         카메라의 회전각도
         */
        VBFloat rotation;
        
        /**
         카메라의 줌인
         */
        VBFloat zoom;
        
        /**
         카메라의 매트릭스가 업데이트필요한지 여부
         */
        VBBool is_need_update;
        
        /**
         카메라의 매트릭스
         */
        VBMatrix2D mat;
        
        /**
         카메라의 모드
         */
        VBCamera2DMode mode;
    };
    
    /**
     @brief VBCamera2D 를 메모리 할당합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 메모리 할당</i> \n\n
     VBCamera2D *camera = VBCamera2DAlloc();
     </td>
     </tr>
	 </table>
     
     @return 메모리 할당된 VBCamera2D 의 포인터.
     */
    VBCamera2D* VBCamera2DAlloc(void);
    
    /**
     @brief VBCamera2D 를 초기화합니다.
     
     모드는 VBCamera2DMode_Default 로 설정됩니다.\n
     초기 위치값은 (0.0, 0.0 : 스크린의 중심)이며, 줌값은 1.0이고, 회전값은 0.0입니다.\n
     줌과 회전은 스크린의 중심을 중심점으로 하여 작동합니다.\n
     VBEngineStart() 시 설정된 리소스크기와 스크린크기를 비교하여 잘리는곳 없이 화면에 올바르게 채움니다.\n
     초기화 시 매트릭스는 업데이트가 되지 않습니다. VBCamera2DGetMatrix() 호출 시에 매트릭스가 업데이트 됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 메모리 할당후 초기화</i> \n\n
     VBCamera2D *camera = VBCamera2DInit( VBCamera2DAlloc() );
     </td>
     </tr>
	 </table>
     
     @param _camera VBCamera2D 포인터.
     @return 초기화된 VBCamera2D 의 포인터.
     */
    VBCamera2D* VBCamera2DInit(VBCamera2D* _camera);
    
    /**
     @brief VBCamera2D 를 VBCamera2DMode 의 해당모드로 초기화합니다.
     
     초기 위치값은 (0.0, 0.0 : 스크린의 중심)이며, 줌값은 1.0이고, 회전값은 0.0입니다.\n
     줌과 회전은 스크린의 중심을 중심점으로 하여 작동합니다.\n
     VBEngineStart() 시 설정된 리소스크기와 스크린크기를 비교하여 잘리는곳 없이 화면에 올바르게 채움니다.\n
     초기화 시 매트릭스는 업데이트가 되지 않습니다. VBCamera2DGetMatrix() 호출 시에 매트릭스가 업데이트 됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 메모리 할당후 VBCamera2DMode_Default 모드로 초기화</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );
     </td>
     </tr>
	 </table>
     
     @param _camera VBCamera2D 포인터.
     @param _mode 초기화 시킬 VBCamera2D 의 모드.
     @return 초기화된 VBCamera2D 의 포인터.
     */
    VBCamera2D* VBCamera2DInitWithMode(VBCamera2D* _camera, VBCamera2DMode _mode);
    
    /**
     @brief VBCamera2D 의 메모리를 해제하고 포인터를 VBNull 로 설정합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 초기화후 메모리 해제.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DFree(&camera);
     </td>
     </tr>
	 </table>
     
     @param _camera VBCamera2D 포인터변수를 선언한 곳의 주소(이중 포인터).
     */
    void VBCamera2DFree(VBCamera2D** _camera);
    
    /**
     @brief VBCamera2D 를 VBCamera2DMode 의 해당모드로 변경합니다.
     
     모드 변경시 값들이 초기화 됩니다. 위치값은 (0.0, 0.0 : 스크린의 중심)이며, 줌값은 1.0이고, 회전값은 0.0입니다.\n
     줌과 회전은 스크린의 중심을 중심점으로 하여 작동합니다.\n
     VBEngineStart() 시 설정된 리소스크기와 스크린크기를 비교하여 잘리는곳 없이 화면에 올바르게 채움니다.\n
     모드 변경시 매트릭스는 업데이트가 되지 않습니다. VBCamera2DGetMatrix() 호출 시에 매트릭스가 업데이트 됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 초기화후 VBCamera2DMode_Left 모드로 설정.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DSetMode( camera , VBCamera2DMode_Left );
     </td>
     </tr>
	 </table>
     
     @param _camera 변경시킬 VBCamera2D 포인터.
     @param _mode 변경시킬 VBCamera2D 의 모드.
     */
    void VBCamera2DSetMode(VBCamera2D* _camera, VBCamera2DMode _mode);
    
    /**
     @brief VBCamera2D 의 VBCamera2DMode 를 반환합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 초기화후 VBCamera2DMode 가져와서 출력.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DSetMode( camera , VBCamera2DMode_Left );\n
     VBCamera2DMode mode = VBCamera2DGetMode( camera );\n
     switch(mode) {\n
     &nbsp; &nbsp; &nbsp; &nbsp; case VBCamera2DMode_Default:\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; VBLog( "VBCamera2DMode_Default" );\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; break;\n
     &nbsp; &nbsp; &nbsp; &nbsp; case VBCamera2DMode_Left:\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; VBLog( "VBCamera2DMode_Left" );\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; break;\n
     &nbsp; &nbsp; &nbsp; &nbsp; case VBCamera2DMode_Right:\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; VBLog( "VBCamera2DMode_Right" );\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; break;\n
     &nbsp; &nbsp; &nbsp; &nbsp; case VBCamera2DMode_Reverse:\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; VBLog( "VBCamera2DMode_Reverse" );\n
     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; break;\n
     }
     </td>
     </tr>
	 </table>
     
     @param _camera 알아볼 VBCamera2D 포인터.
     @return 해당 VBCamera2D 의 모드 VBCamera2DMode.
     */
    VBCamera2DMode VBCamera2DGetMode(VBCamera2D* _camera);
    
    /**
     @brief VBCamera2D 의 카메라 위치를 변경합니다.
     
     원점(0, 0)은 스크린의 중심입니다.\n
     카메라 위치 변경시 매트릭스는 업데이트가 되지 않습니다. VBCamera2DGetMatrix() 호출 시에 매트릭스가 업데이트 됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 초기화후 카메라의 가로위치를 스크넓이의 절반의 위치로 설정.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBVector2D screen = VBEngineGetScreenSize();\n
     VBCamera2DSetPosition( camera , VBVector2DCreate( screen.x * 0.5f , 0.0f ) );
     </td>
     </tr>
	 </table>
     
     @param _camera 변경시킬 VBCamera2D 포인터.
     @param _position 변경시킬 카메라의 위치.
     */
    void VBCamera2DSetPosition(VBCamera2D* _camera, VBVector2D _position);
    
    /**
     @brief VBCamera2D 의 카메라 위치를 반환합니다.
     
     원점(0, 0)은 스크린의 중심입니다.\n
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 의 카메라가로위치를 스크넓이의 절반의 위치로 설정하고 카메라 위치 출력.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBVector2D screen = VBEngineGetScreenSize();\n
     VBCamera2DSetPosition( camera , VBVector2DCreate( screen.x * 0.5f , 0.0f ) );\n
     VBVector2D position = VBCamera2DGetPosition( camera );\n
     VBLog( "camera position (%f, %f)" , position.x , position.y );
     </td>
     </tr>
	 </table>
     
     @param _camera 알아볼 VBCamera2D 포인터.
     @return 해당 VBCamera2D 의 카메라 위치.
     */
    VBVector2D VBCamera2DGetPosition(VBCamera2D* _camera);
    
    /**
     @brief VBCamera2D 의 카메라 회전각을 변경합니다.
     
     회전각은 -VB_PI(3.14...) ~ VB_PI까지입니다(-180도 ~ 180도).\n
     회전각의 기본각인 0도는 모드에 따라서 다릅니다.(즉 VBCamera2DMode_Default 모드의 "-VB_PI / 2.0f" 는 VBCamera2DMode_Left 모드의 "0.0f"와 같습니다.\n
     회적각의 중심점은 스크린의 중심입니다.\n
     카메라 위치 변경시 매트릭스는 업데이트가 되지 않습니다. VBCamera2DGetMatrix() 호출 시에 매트릭스가 업데이트 됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 초기화후 카메라의 회전각을 90도로 설정.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DSetRotation( camera , VB_PI / 2.0f );
     </td>
     </tr>
	 </table>
     
     @param _camera 변경시킬 VBCamera2D 포인터.
     @param _position 변경시킬 카메라의 위치.
     */
    void VBCamera2DSetRotation(VBCamera2D* _camera, VBFloat _rotation);
    
    /**
     @brief VBCamera2D 의 카메라 회전각을 반환합니다.
     
     회전각은 -VB_PI(3.14...) ~ VB_PI까지입니다(-180도 ~ 180도).\n
     회전각의 기본각인 0도는 모드에 따라서 다릅니다.(즉 VBCamera2DMode_Default 모드의 "-VB_PI / 2.0f" 는 VBCamera2DMode_Left 모드의 "0.0f"와 같습니다.\n
     회적각의 중심점은 스크린의 중심입니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 의 카메라 회전각을 90도로 설정하고 회전각 출력.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DSetRotation( camera , VB_PI / 2.0f );\n
     VBFloat rotation = VBCamera2DGetRotation( camera );\n
     VBLog( "camera rotation %f" , rotation );
     </td>
     </tr>
	 </table>
     
     @param _camera 알아볼 VBCamera2D 포인터.
     @return 해당 VBCamera2D 의 카메라 회전각.
     */
    VBFloat VBCamera2DGetRotation(VBCamera2D* _camera);
    
    /**
     @brief VBCamera2D 의 카메라 줌(확대)을 변경합니다.
     
     기본확대비율은 1.0입니다.(기본확대비율이 커질수록 화면출력내용도 커집니다.)\n
     확대의 중심점은 스크린의 중심입니다.\n
     카메라 위치 변경시 매트릭스는 업데이트가 되지 않습니다. VBCamera2DGetMatrix() 호출 시에 매트릭스가 업데이트 됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 초기화후 카메라의 줌을 절반으로 설정.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DSetZoom( camera , 0.5f );
     </td>
     </tr>
	 </table>
     
     @param _camera 변경시킬 VBCamera2D 포인터.
     @param _position 변경시킬 카메라의 줌(확대비율).
     */
    void VBCamera2DSetZoom(VBCamera2D* _camera, VBFloat _zoom);
    
    /**
     @brief VBCamera2D 의 카메라 줌(확대)을 반환합니다.
     
     기본확대비율은 1.0입니다.(기본확대비율이 커질수록 화면출력내용도 커집니다.)\n
     확대의 중심점은 스크린의 중심입니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 의 줌을 절반으로 설정하고 카메라 줌 출력.</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBCamera2DSetZoom( camera , 0.5f );\n
     VBFloat zoom = VBCamera2DGetZoom( camera );\n
     VBLog( "camera zoom %f" , zoom );
     </td>
     </tr>
	 </table>
     
     @param _camera 알아볼 VBCamera2D 포인터.
     @return 해당 VBCamera2D 의 줌(확대비율).
     */
    VBFloat VBCamera2DGetZoom(VBCamera2D* _camera);
    
    /**
     @brief VBCamera2D 의 변환행렬을 반환 합니다.
     
     변환행렬은 기본적으로 이함수를 실행할때 업데이트 됩니다.\n
     이함수를 호출하기 전에 변경된 사항이 없으면 기존에 변환해 놓은 변환행렬을 반환 합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBCamera2D 의 기본모드 변환행렬을 출력</i> \n\n
     VBCamera2D *camera = VBCamera2DInitWithMode( VBCamera2DAlloc() , VBCamera2DMode_Default );\n
     VBMatrix2D matrix = VBCamera2DGetMatrix( camera );\n
     VBLog( "camera matrix \n %f,%f,%f,\n  %f,%f,%f,\n  %f,%f,%f" , matrix.m11, matrix.m12, matrix.m13, matrix.m21, matrix.m22, matrix.m23, matrix.m31, matrix.m32, matrix.m33 );
     </td>
     </tr>
	 </table>
     
     @param _camera 알아볼 VBCamera2D 포인터.
     @return 해당 VBCamera2D 의 줌(확대비율).
     */
    VBMatrix2D VBCamera2DGetMatrix(VBCamera2D* _camera);
	
#ifdef __cplusplus
}
#endif

#endif