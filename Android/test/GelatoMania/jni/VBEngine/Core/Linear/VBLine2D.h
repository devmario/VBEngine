/**
 @file Core/Linear/VBLine2D.h
 
 @brief 선의 구조체와 이를 다룰수 있는 함수들
 
 VBLine2D는 라인의 데이터사용과 충돌및 점검출등 라인과 관련된 여러가지 기능을 위해 만들어진 소스 입니다.\n
 VBLine2D를 이용하여 움직이고 있는 두물체의 물리적인 충돌체크를 해주세요.\n
 
 @author
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

#ifndef __VBLine2D_H__
#define __VBLine2D_H__

#include "../../VBType.h"
#include "VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
	 @brief VBLine2D 구조체타입.
	 */
    typedef struct VBLine2D VBLine2D;
    
    /**
	 @brief VBLine2D 구조체.
	 */
    struct VBLine2D {
        /*!
         라인의 시작점
         */
        VBVector2D begin;
        
        /*!
         라인의 끝점
         */
        VBVector2D end;
    };
    
    /**
     @brief 시작점과 끝점으로 라인을 생성합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>시작점(0,0)과 끝점(10,0)으로 라인을 생성하기</i> \n\n
     VBLine2D line = VBLine2DCreate( 0.0f, 0.0f, 10.0f, 0.0f );
     </td>
     </tr>
	 </table>
     
     @param _beginX 시작점의 x좌표
     @param _beginY 시작점의 y좌표
     @param _endX 끝점의 x좌표
     @param _endY 끝점의 y좌표
     @return 생성된 라인을 반환
     */
    VBLine2D VBLine2DCreate(VBFloat _beginX, VBFloat _beginY, VBFloat _endX, VBFloat _endY);
    
    /**
     @brief 시작점과 끝점으로 라인을 생성합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>시작점(0,0)과 끝점(10,0)으로 라인을 생성하기</i> \n\n
     VBVector2D begin = VBLine2DGetVector2D( 0.0f, 0.0f );\n
     VBVector2D end = VBLine2DGetVector2D( 10.0f, 0.0f );\n
     VBLine2D line = VBLine2DCreateV( begin, end );
     </td>
     </tr>
	 </table>
     
     @param _begin 시작점의 벡터
     @param _end 끝점의 벡터
     @return 생성된 라인을 반환
     */
    VBLine2D VBLine2DCreateV(VBVector2D _begin, VBVector2D _end);
    
    /**
     @brief 한선에서 점을 추출합니다.
     
     0.0은 시작점이며 1.0은 끝점입니다.\n
     시작점과 끝점사이의 점을 구하려면 0.0과 1.0사의의 값을 인자로 쓰세요\n
     
     <b>알고리즘</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     A가 시작점이고 B가 끝점이면 선분은 A+(B-A)이므로,\n
     우리가 구하려는 값인 t에 대한 선분의값은 A+(B-A)*t 이다.\n
     </td>
     </tr>
	 </table>
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>라인 VBLine2D 시작점(0,0)과 끝점(10,0) 에서 중간에 위치한 점 추출하기</i> \n\n
     VBLine2D line = VBLine2DCreate( 0.0f, 0.0f, 10.0f, 0.0f );\n
     VBVector2D vec = VBLine2DGetVector2D( line, 0.5f );\n
     VBLog("line vector %f = (%f, %f)", 0.5f, vec.x, vec.y);
     </td>
     </tr>
	 </table>
     
     @param _line 선 VBLine2D
     @param _t 0.0~1.0의 값
     @return 해당 T값에 위치한 VBVector2D
     */
    VBVector2D VBLine2DGetVector2D(VBLine2D _line, VBFloat _t);
    
    /**
     @brief 두 VBLine2D 가 충돌했는지 반환하고 충돌지점을 검출합니다.
     
     이때 두선분중 한개 이상이 점일경우(시작점과 끝점이 동일)와 두 선분이 평행할때는 충돌하지 않습니다.
     
     <b>알고리즘</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     A+(B-A)t = C+(D-C)s 의 s에 대한 정리는\n
     (A+(B-A)t-C)/(D-C) = s 이므로\n
     (Ax+(Bx-Ax)t-Cx)/(Dx-Cx) = (Ay+(By-Ay)t-Cy)/(Dy-Cy) 이다.\n
     \n
     D-C가 a라고 하였을때, 우변을 좌변으로 이항하면\n
     ayAx+ayBxt-ayAxt-ayCx-axAy-axByt+axAyt+axCy=0 이고 이를 t에 대한 일차방정식으로 정리하면,\n
     (ayBx-ayAx-axBy+axAy)t+(ayAx-ayCx-axAy+axCy)=0 이다.\n
     \n
     이때 (ayBx-ayAx-axBy+axAy)t+(ayAx-ayCx-axAy+axCy)=0을 et + f = 0으로 변환하고\n
     et + f = 0에 대해서 -f / e = t 로 t를 구할수 있다(접점t)\n
     이때 e가 0이면 t을 구할수 없으므로 충돌하지 않는다.(인자로 넘긴 두선이 선아닌 점이거나 또는 평행)\n
     t는 0.0~1.0이므로 t가 0.0보다 작고 1.0보다 크면 A+(B-A)t에서 벗어나므로 충돌하지 않는다.\n
     \n
     (Ax+(Bx-Ax)t-Cx)/(Dx-Cx) = s이므로, s도 구할수 있다.\n
     0으로 나눌수 없으므로 Dx-Cx가 0이면 (Ay+(By-Ay)t-Cy)/(Dy-Cy)로 s를 구한다.\n
     Dx-Cx와 Dy-Cy가 모두 0일때는 s를 구할수 없으므로 충돌하지 않는다.(인자로 넘긴 두선이 선아닌 점이거나 또는 평행)\n
     s는 0.0~1.0이므로 s가 0.0보다 작고 1.0보다 크면 C+(D-C)s에서 벗어나므로 충돌하지 않는다.\n
     \n
     위의 모든 테스트를 통과하였을경우 충돌이며 t와A,B를 이용 A+(B-A)t충돌지점을 검출한다.\n
     </td>
     </tr>
	 </table>
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>두 라인 VBLine2D (0,0 ~ 10,0 와 5,-5 ~ 10,5)의 충돌 검출</i> \n\n
     VBLine2D a = VBLine2DCreate( 0.0f, 0.0f, 10.0f, 0.0f );\n
     VBLine2D b = VBLine2DCreate( 5.0f, -5.0f, 10.0f, 5.0f );\n
     VBVector2D vec;\n
     VBBool is_hit = VBLine2DGetCollisionVectorByLine( a, b, &vec );\n
     VBLog("%s-> collision vector (%f, %f)", is_hit ? "hit" : "no hit" , vec.x, vec.y);
     </td>
     </tr>
	 </table>
     
     @param _line1 첫번째 선 VBLine2D
     @param _line2 두번째 선 VBLine2D
     @param _col_vec 두 VBLine2D 의 충돌지점을 가져올 VBVector2D 타입의 변수 포인터(주소값)이며 만약에 충돌되지 않았을 경우 설정되지 않습니다.
     @return 두 VBLine2D 의 충돌 여부
     */
    VBBool VBLine2DGetCollisionVectorByLine(VBLine2D _line1, VBLine2D _line2, VBVector2D* _col_vec);

#ifdef __cplusplus
}
#endif

#endif