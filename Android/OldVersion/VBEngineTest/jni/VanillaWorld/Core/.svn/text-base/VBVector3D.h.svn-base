/**
 @file Core/VBVector3D.h
 @brief VBEngine의 VBVector3D 구조체타입과 여러 함수들.
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

#ifndef __VBVector3D_H__
#define __VBVector3D_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief 3D관련 벡터 구조체타입.
	 
	 VBVector3D 구조체는 3D환경에서 3차원 좌표계에서의 위치를 나타냅니다.\n
	 여기서 x는 가로 축(길이), y는 세로 축(너비), z는 직각(깊이)을 나타냅니다.\n
	 12바이트 구조체이며, 4바이트 VBFloat 3개(x, y, z)를 포함하고 있습니다.
	 */
	typedef struct VBVector3D VBVector3D;
	
	/**
	 @brief 3D관련 벡터 구조체.
	 
	 VBVector3D 구조체는 3D환경에서 3차원 좌표계에서의 위치를 나타냅니다.\n
	 여기서 x는 가로 축, y는 세로 축, z는 직각을 나타냅니다.\n
	 12바이트 구조체이며, 4바이트 VBFloat 3개(x, y, z)를 포함하고 있습니다.
	 */
	struct VBVector3D {
		/*!
		 벡터의 x(가로축)
		 */
		VBFloat x;
		/*!
		 벡터의 y(가로축)
		 */
		VBFloat y;
		/*!
		 벡터의 z(직각)
		 */
		VBFloat z;
	};
	
    /**
     @brief 새로운 VBVector3D벡터를 생성합니다.
     @param _x 가로 좌표입니다.
     @param _y 세로 좌표입니다.
     @param _z 직각 좌표입니다.
     @return 생성된 3D벡터입니다. 
     
     */
	VBVector3D VBVector3DCreate(VBFloat _x, VBFloat _y, VBFloat _z);
	
    /**
     @brief VBVector3D의 가로축을 가져옵니다.
     @param _vec3D 3D벡터.
     @return 인자로 넘겨진 벡터의 가로축(x).
     */

	VBFloat VBVector3DGetX(VBVector3D _vec3D);

	/**
     @brief VBVector3D의 세로축을 가져옵니다.
     @param _vec3D 3D벡터.
     @return 인자로 넘겨진 벡터의 세로축(y).
     */
	VBFloat VBVector3DGetY(VBVector3D _vec3D);
    
    /**
     @brief VBVector3D의 높이축을 가져옵니다.
     @param _vec3D 3D벡터.
     @return 인자로 넘겨진 벡터의 직각축(z).
     */
	VBFloat VBVector3DGetZ(VBVector3D _vec3D);
    
    /**
     @brief 두 벡터가 같은 벡터인지 결정합니다. \n
     
     두 벡터의 x, y 및 z값이 같으면 두 벡터는 같은 벡터입니다.
     @param _vec3D_1 비교할 첫번째 벡터입니다.
     @param _vec3D_2 비교할 두번째 벡터입니다.
     @param 첫번쨰 벡터와 두번째 벡터가 같으면 값이 VBTrue이고, 같지 않으면 VBFalse입니다. 
     */
	VBBool VBVector3DIsEqual(VBVector3D _vec3D_1, VBVector3D _vec3D_2);	
	
    /**
     @brief 입력된 벡터를 정규화하여 반환합니다.
     @param _vec3D 3D벡터.
     @return 정규화된 벡터
     */
	VBVector3D VBVector3DNormal(VBVector3D _vec3D);
	
    /**
     @brief 두 개의 VBVector3D를 더합니다.
     @param _vec3D_1 첫번째 벡터.
     @param _vec3D_2 두번쨰 벡터.
     @return 첫번째 벡터와 두번째 벡터를 더한값 입니다.
     */
	VBVector3D VBVector3DAdd(VBVector3D _vec3D_1, VBVector3D _vec3D_2);
	
    /**
     @brief 두 개의 VBVector3D를 뺍니다.
     @param _vec3D_1 첫번째 벡터.
     @param _vec3D_2 두번쨰 벡터.
     @return 첫번째 벡터와 두번째 벡터를 뺀 값입니다.
     */
	VBVector3D VBVector3DSubtract(VBVector3D _vec3D_1, VBVector3D _vec3D_2);
	
    /**
     @brief VBVector3D에 수를 곱합니다.
     @param _vec3D_1 첫번째 벡터.
     @param _num 곱할 수.
	 @return 벡터에 수를 곱하여 반환합니다.     
     */
	VBVector3D VBVector3DMultiply(VBVector3D _vec3D, VBFloat _num);
	
    /**
     @brief VBVector3D에 수를 나눕니다.
     @param _vec3D_1 첫번째 벡터.
     @param _num 나눌 수.
     @return 벡터에 수를 나눠 반환합니다.
     */
	VBVector3D VBVector3DDivide(VBVector3D _vec3D, VBFloat _num);
	
    /**
     @brief 두 개의 VBVector3D에서 내적을 구합니다.
     @param _vec3D_1 첫번째 벡터.
     @param _vec3D_2 두번쨰 벡터.
	 @return 첫번째 벡터와 두번째 벡터의 내적을 반환합니다.
     */
	VBFloat VBVector3DDotProduct(VBVector3D _vec3D_1, VBVector3D _vec3D_2);
	
    /**
     @brief 두 개의 VBVector3D에서 외적을 구합니다.
     @param _vec3D_1 첫번째 벡터.
     @param _vec3D_2 두번쨰 벡터.
     @return 첫번째 벡터와 두번째 벡터의 외적을 반환합니다.
     */
	VBVector3D VBVector3DCrossProduct(VBVector3D _vec3D_1, VBVector3D _vec3D_2);
	
    /**
     @brief 벡터의 길이를 구합니다.
     @param _vec3D 벡터
     @return 벡터의 길이
     */
	VBFloat VBVector3DLength(VBVector3D _vec3D);
	
    /**
     @brief 두 벡터간의 거리를 구합니다.
     @param _vec3D_1 첫번째 벡터
     @param _vec3D_2 두번째 벡터
     @return 두 벡터간의 거리
     */
	VBFloat VBVector3DDistance(VBVector3D _vec3D_1, VBVector3D _vec3D_2);
	
    /**
     @brief 벡터의 각도를 구합니다.
     @param _vec3D 벡터
     @return 벡터의 각도
     */
    VBFloat VBVector3DAngle(VBVector3D _vec3D);
    
    /**
     @brief 두 벡터 사이의 각도를 구합니다.
     @param _vec3D_1 첫번째 벡터
     @param _vec3D_2 두번째 벡터
     @return 벡터 사이의 각도
     */
    VBFloat VBVector3DAngleTo(VBVector3D _vec3D_1, VBVector3D _vec3D_2);
    
    /**
     @brief 두 벡터를 보간합니다.
     @param _vec3D_1 첫번째 벡터
     @param _vec3D_2 두번째 벡터
     @param _num 보간계수(0.0 ~ 1.0)
     @return 보간된 벡터
     */
    VBVector3D VBVector3DInterpolate(VBVector3D _vec3D_1, VBVector3D _vec3D_2, VBFloat _num);
    
    /**
     @brief 길이와 각도를 이용해 벡터를 생성합니다.
     @param _len 원점으로부터의 길이
     @param _theta z축 양의 방향과 이루는 각도
     @param _phi xy평면으로의 사영이 x축 양의 방향과 이루는 각도
     @return 생성된 벡터
     */
    VBVector3D VBVector3DPolar(VBFloat _len, VBFloat _theta, VBFloat _phi);
    
#ifdef __cplusplus
}
#endif

#endif