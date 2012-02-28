/**
 @file Core/Linear/VBTriangle2D.h
 
 @brief 삼각형의 구조체와 이를 다룰수 있는 함수들
 
 VBTriangle2D는 삼각형의 데이터사용과 충돌및 충돌검출등 삼각형과 관련된 여러가지 기능을 위해 만들어진 소스 입니다.\n
 VBTriangle2D를 이용하여 VBModel2D 의 충돌체크를 해주세요.\n
 
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

#ifndef __VBTriangle2D_H__
#define __VBTriangle2D_H__

#include "../../VBType.h"
#include "VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
	 @brief VBTriangle2D 구조체타입.
	 */
    typedef struct VBTriangle2D VBTriangle2D;
    
    /**
	 @brief VBTriangle2D 구조체.
	 */
    struct VBTriangle2D {
        /*!
         삼각형의 첫번째 꼭지점
         */
        VBVector2D a;
        
        /*!
         삼각형의 두번째 꼭지점
         */
        VBVector2D b;
        
        /*!
         삼각형의 세번째 꼭지점
         */
        VBVector2D c;
    };
    
    /**
     @brief 삼각형을 생성합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>삼각형 VBTriangle2D 만들기</i> \n\n
     VBTriangle2D tri = VBTriangle2DCreate( 0.0, 0.0, 10.0, -10.0, 20.0, 0.0 );
     </td>
     </tr>
	 </table>
     
     @param _ax 삼각형의 첫번째 꼭지점의 x축 좌표
     @param _ay 삼각형의 첫번째 꼭지점의 y축 좌표
     @param _bx 삼각형의 두번째 꼭지점의 x축 좌표
     @param _by 삼각형의 두번째 꼭지점의 y축 좌표
     @param _cx 삼각형의 세번째 꼭지점의 x축 좌표
     @param _cy 삼각형의 세번째 꼭지점의 y축 좌표
     @return 꼭지점 _ax, _ay, _bx, _by, _cx, _cy로 이루어진 VBTriangle2D 반환
     */
    VBTriangle2D VBTriangle2DCreate(VBFloat _ax, VBFloat _ay, VBFloat _bx, VBFloat _by, VBFloat _cx, VBFloat _cy);
    
    /**
     @brief 삼각형을 생성합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>삼각형 VBTriangle2D 만들기</i> \n\n
     VBVector2D a = VBVector2DCreate( 0.0, 0.0 );\n
     VBVector2D b = VBVector2DCreate( 10.0, -10.0 );\n
     VBVector2D c = VBVector2DCreate( 20.0, 0.0 );\n
     VBTriangle2D tri = VBTriangle2DCreateV( a, b, c );
     </td>
     </tr>
	 </table>
     
     @param _a 삼각형의 첫번째 꼭지점 VBVector2D
     @param _b 삼각형의 두번째 꼭지점 VBVector2D
     @param _c 삼각형의 세번째 꼭지점 VBVector2D
     @return 꼭지점 _a, _b, _c로 이루어진 VBTriangle2D 반환
     */
    VBTriangle2D VBTriangle2DCreateV(VBVector2D _a, VBVector2D _b, VBVector2D _c);
    
    
    /**
     @brief 삼각형 안에 점이 포함되어 있는지 검출합니다.
     
     삼각형각 꼭지점 ABC에 대한 선분 AB, BC, CA에 대해서 AB, BC, CA선분 위에 점이 위치할때도 충돌로 인지합니다. 
     
     <b>알고리즘</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     삼각형의 각꼭지점을 ABC라하고 테스트할 점을 V라고 했을때,\n
     삼각형 각선분의 벡터는 (B-A) = Ab, (C-B) = Bc, (A-C) = Ca이다.\n
     \n
     각꼭지점의 v에 대한 선분벡터를 AV, BV, CV라고 했을때,\n
     각꼭지점의 v에 대한 선분벡터는 (V-A) = Av, (V-B) = Bv, (V-C) = Cv이다.\n
     \n
     3차원 평면면 xyz에서의 두개의벡터 Ab,Av에 대한 외적 AbAv는 (AbyAvz - AvyAbz , AbzAvx - AvzAbx , AbxAvy - AvxAby) 이고,\n
     z축을 0으로 놓았을때의 외적 AbAv는 (0, 0 , AbxAvy - AvxAby)이므로\n
     <a href="http://ko.wikipedia.org/wiki/외적">외적 AbAv의 z인 AbxAvy - AvxAby가 0보다 작으면 오른손 좌표에서 벡터 Ab가 점 Av에 비해 반시계방향 쪽으로 위치하고 0보다 크면 시계방향 쪽으로 위치해 있다.
     (여기서 계산의 속도를 위해 2차원 좌표계의 외적 ||Ab|| ||Av|| sin AbAvθ 를 쓰지 않고 3차원 좌표계의 외적을 이용하였다.)</a>\n
     그러므로 2차원 평면에서의 벡터Av에 대한 벡터Ab의 방향은 AbxAvy - AvxAby가 0보다 크면 시계방향,작으면 반시계방향이다.\n
     \n
     삼각형과 점의 성질중 삼각형 각선분AB, BC, CA 에대해 점V가 같은방향에 위치하면 삼각형 내부에 위치하므로,\n
     이러한 성질을 이용하여 벡터 Ab, Bc, Ca에 대한 벡터 Av, Bv, Cv가 모두 같은 방향에 위치하면 점V는 삼각형ABC안에 위치한다.
     </td>
     </tr>
	 </table>
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>삼각형 VBTriangle2D 에서 점 VBVector2D 가 내부에 있는지 판단하기</i> \n\n
     VBTriangle2D tri = VBTriangle2DCreate( 0.0, 0.0, 10.0, -10.0, 20.0, 0.0 );\n
     VBVector2D vec = VBVector2DCreate( 10.0, -5.0 );\n
     VBBool is_hit = VBTriangle2DGetCollisionByVector( tri, vec );\n
     VBLog( "%s", is_hit ? "hit" : "no hit" );
     </td>
     </tr>
	 </table>
     
     @param _tri 삼각형 VBTriangle2D
     @param _vec 점 VBVector2D
     @return 점 VBVector2D _vec가 삼각형 VBTriangle2D _tri안에 있으면 VBTrue 반환, 아니면 VBFalse 반환
     */
    VBBool VBTriangle2DGetCollisionByVector(VBTriangle2D _tri, VBVector2D _vec);
    
#ifdef __cplusplus
}
#endif

#endif