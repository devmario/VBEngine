/**
 @file Core/VBVector2D.h
 @brief VBEngine의 VBVector2D 구조체타입과 여러 함수들.
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

#ifndef __VBVector2D_H__
#define __VBVector2D_H__

#include "../VBType.h"
#include "VBString.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief 2D관련 벡터 구조체타입.
	 
	 VBVector2D 구조체는 2D환경에서 2차원 좌표계에서의 위치를 나타냅니다.\n
	 여기서 x는 가로 축, y는 세로 축을 나타냅니다.\n
	 8바이트 구조체이며, 4바이트 VBFloat 2개(x, y)를 포함하고 있습니다.
	 */
	typedef struct VBVector2D VBVector2D;
	
	/**
	 @brief 2D관련 벡터 구조체.
	 
	 VBVector2D 구조체는 2D환경에서 2차원 좌표계에서의 위치를 나타냅니다.\n
	 여기서 x는 가로 축, y는 세로 축을 나타냅니다.\n
	 8바이트 구조체이며, 4바이트 VBFloat 2개(x, y)를 포함하고 있습니다.
	 */
	struct VBVector2D {
		/*!
		 벡터의 x(가로축)
		 */
		VBFloat x;
		/*!
		 벡터의 y(세로축)
		 */
		VBFloat y;
	};
	
	/**
	 @brief 새로운 벡터를 생성합니다.
	 @param _x 가로 좌표입니다.
	 @param _y 세로 좌표입니다.
	 @return 생성된 벡터입니다.
	 */
	VBVector2D VBVector2DCreate(VBFloat _x, VBFloat _y);
	
	/**
	 @brief 벡터의 가로축을 가져옵니다.
	 @param _vec2D 벡터.
	 @return 인자로 넘겨진 벡터의 가로축(x).
	 */
	VBFloat VBVector2DGetX(VBVector2D _vec2D);
	
	/**
	 @brief 벡터의 세로축을 가져옵니다.
	 @param _vec2D 벡터.
	 @return 인자로 넘겨진 벡터의 세로축(y).
	 */
	VBFloat VBVector2DGetY(VBVector2D _vec2D);
	
	/**
	 @brief 두 벡터가 같은 벡터인지 결정합니다.\n
	 
	 두 벡터의 x 및 y 값이 같으면 두 벡터는 같은 벡터입니다.
	 @param _vec2D_1 비교할 첫번째 벡터입니다.
	 @param _vec2D_2 비교할 두번째 벡터입니다.
	 @return 첫번째 벡터와 두번째 벡터가 같으면 값이 VBTrue이고, 같지 않으면 VBFalse입니다.
	 */
	VBBool VBVector2DIsEqual(VBVector2D _vec2D_1, VBVector2D _vec2D_2);
	
	/**
	 @brief (0,0)과 현재 벡터 사이의 선분을 설정된 길이로 조절합니다.
	 @param _vec2D 현재 벡터입니다.
	 @param _thickness 크기 조절 값입니다.\n
	 예를 들어, 현재 점이 (0,5)이고 이 점을 1로 정규화하면 반환되는 점은 (0,1)입니다.
	 @return 설정된 선분의 길이의 벡터입니다.
	 */
	VBVector2D VBVector2DNormal(VBVector2D _vec2D, VBFloat _thickness);
	
	/**
	 @brief 벡터 2개를 더합니다.
	 @param _vec2D_1 첫번째 벡터.
	 @param _vec2D_2 두번째 벡터.
	 @return 첫번째 벡터와 두번째 벡터를 더한값 입니다.
	 */
	VBVector2D VBVector2DAdd(VBVector2D _vec2D_1, VBVector2D _vec2D_2);
	
	/**
	 @brief 벡터 2개를 뺍니다.
	 @param _vec2D_1 첫번째 벡터.
	 @param _vec2D_2 두번째 벡터.
	 @return 첫번째 벡터에서 두번째 벡터를 뺀값 입니다.
	 */
	VBVector2D VBVector2DSubtract(VBVector2D _vec2D_1, VBVector2D _vec2D_2);
	
	/**
	 @brief 벡터에 수를 곱합니다.
	 @param _vec2D 벡터.
	 @param _num 곱할 수.
	 @return 벡터에 수를 곱하여 반환합니다.
	 */
	VBVector2D VBVector2DMultiply(VBVector2D _vec2D, VBFloat _num);
	
	/**
	 @brief 벡터에 수를 나눕니다.
	 @param _vec2D 벡터.
	 @param _num 나눌 수.
	 @return 벡터에 수를 나누여 반환합니다.
	 */
	VBVector2D VBVector2DDivide(VBVector2D _vec2D, VBFloat _num);
	
	/**
	 @brief 2개의 백터에서 내적을 구합니다.
	 @param _vec2D_1 첫번째 벡터.
	 @param _vec2D_2 두번째 벡터.
	 @return 첫번째 벡터와 두번째 벡터의 내적을 반환합니다.
	 */
	VBFloat VBVector2DDotProduct(VBVector2D _vec2D_1, VBVector2D _vec2D_2);
	
	/**
	 @brief (0,0)에서 벡터까지 연결한 선분의 길이를 구합니다.
	 @param _vec2D 선분의 길이를 구할 벡터.
	 @return (0,0)에서 벡터까지 연결한 선분의 길이입니다.
	 */
	VBFloat VBVector2DLength(VBVector2D _vec2D);
	
	/**
	 @brief 2개의 백터의 거리를 구합니다.
	 @param _vec2D_1 첫번째 벡터.
	 @param _vec2D_2 두번째 벡터.
	 @return 첫번째 벡터와 두번째 벡터의 거리를 입니다.
	 */
	VBFloat VBVector2DDistance(VBVector2D _vec2D_1, VBVector2D _vec2D_2);
	
	/**
	 @brief 벡터의 각도를 구합니다.
	 @param _vec2D 벡터.
	 @return 원점벡터(0, 0)에서 인자로 넘겨진 벡터의 각도를 반환합니다.
	 */
	VBFloat VBVector2DAngle(VBVector2D _vec2D);
	
	/**
	 @brief 한벡터를 중심으로 다른벡터의 각도를 구합니다.
	 @param _vec2D_1 중심벡터.
	 @param _vec2D_2 각도를 구할벡터.
	 @return 원점벡터(_vec2D_1)에서 다른 한 벡터(_vec2D_2)의 각도를 반환합니다.
	 */
	VBFloat VBVector2DAngleTo(VBVector2D _vec2D_1, VBVector2D _vec2D_2);
	
	/**
	 @brief  지정한 두 벡터 사이에서 한 벡터를 정합니다.\n
	 
	 매개 변수 _num은 매개 변수 _vec2D_1 및 _vec2D_2에 의해 지정된 두 끝벡터를 기준으로 삽입된 새 벡터의 상대적인 위치를 결정합니다.
	 매개 변수 _num의 값이 1.0에 가까울수록 삽입된 벡터는 첫 번째 벡터(매개 변수 _vec2D_1)에 근접합니다.
	 매개 변수 _num의 값이 0에 가까울수록 삽입된 벡터는 두 번째 벡터(매개 변수 _vec2D_2)에 근접합니다.
	 @param _vec2D_1 첫번째 벡터.
	 @param _vec2D_2 두번째 벡터.
	 @param _num 두 벡터 사이의 삽입 레벨입니다.\n
	 _vec2D_1와 _vec2D_2 사이의 직선상에서 새 벡터의 위치를 나타냅니다.
	 _num =1이면 _vec2D_1이 반환되고, _num =0이면 _vec2D_2가 반환됩니다.
	 @return 새로 삽입된 벡터입니다.
	 */
	VBVector2D VBVector2DInterpolate(VBVector2D _vec2D_1, VBVector2D _vec2D_2, VBFloat _num);
	
	/**
	 @brief 극 좌표 쌍을 직교 좌표계의 한 벡터로 변환합니다.
	 @param _len 극 좌표 쌍의 길이입니다.
	 @param _angle 극 좌표 쌍의 각도(라디안 단위)입니다.
	 @return 직교 좌표 벡터입니다.
	 */
	VBVector2D VBVector2DPolar(VBFloat _len, VBFloat _angle);
	
	/**
	 @brief x 및 y 좌표의 값이 포함된 문자열을 가져옵니다.\n
	 
	 이 문자열의 형식은 "(x= x , y= y)"로, 23,17 위치의 벡터에 대해 VBVector2DToString 메서드를 호출하면 "(x=23, y=17)"을 가져올수 있습니다.\n
	 @param _vec 문자열을 가져올 벡터.
	 @param _str 문자열 포인터로 Alloc이 되어있어야 합니다.
	 */
	void VBVector2DToString(VBVector2D _vec, VBString* _str);
    
    /**
     @brief (0.0, 0.0)의 위치에 VBVector2D를 생성합니다.
     @return 생성된 VBVector2D를 반환합니다. 
     */
    VBVector2D VBVector2DZero(void);
	
#ifdef __cplusplus
}
#endif

#endif