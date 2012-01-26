/**
 @file Core/VBMatrix2D.h
 @brief VBEngine의 VBMatrix2D 구조체타입과 여러 함수들.
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

#ifndef __VBMatrix2D_H__
#define __VBMatrix2D_H__

#include "VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief 2D관련 매트릭스 구조체타입
	 
	 VBMatrix2D 구조체는 특정 좌표 공간의 점을 다른 좌표 공간으로 매핑하는 방법을 결정하는 변형 행렬을 나타냅니다.\n
	 변형 기능으로는 평행 이동(x와 y 위치 변경), 회전, 크기 조절 및 기울이기 등이 있습니다.\n
	 이러한 종류의 변형을 총칭하여 어파인 변형(affine transformations)이라고 합니다.\n
	 어파인 변형에서는 변형 과정에서 선이 곧은 상태를 유지하므로 평행선이 그대로 평행을 이루게 됩니다.\n
	 36바이트 구조체이며, 4바이트 float 9개(3x3)를 포함하고 있습니다.
	 */
	typedef struct VBMatrix2D VBMatrix2D;
	
	/**
	 @brief 2D관련 매트릭스 구조체
	 
	 VBMatrix2D 구조체는 특정 좌표 공간의 점을 다른 좌표 공간으로 매핑하는 방법을 결정하는 변형 행렬을 나타냅니다.\n
	 변형 기능으로는 평행 이동(x와 y 위치 변경), 회전, 크기 조절 및 기울이기 등이 있습니다.\n
	 이러한 종류의 변형을 총칭하여 어파인 변형(affine transformations)이라고 합니다.\n
	 어파인 변형에서는 변형 과정에서 선이 곧은 상태를 유지하므로 평행선이 그대로 평행을 이루게 됩니다.\n
	 36바이트 구조체이며, 4바이트 float 9개(3x3)를 포함하고 있습니다.
	 */
	struct VBMatrix2D {
		/*!
		 2D 매트릭스의 (0, 0)\n
		 이미지의 크기를 조절하거나 회전할 때 x축의 픽셀 위치에 영향을 주는 값입니다.
		 */
		VBFloat m11;
		/*!
		 2D 매트릭스의 (0, 1)\n
		 이미지를 회전하거나 기울일 때 y축의 픽셀 위치에 영향을 주는 값입니다.
		 */
		VBFloat m12;
		/*!
		 2D 매트릭스의 (2, 0)\n
		 x축을 따라 각 점이 평행 이동할 거리입니다.
		 */
		VBFloat m13;
		/*!
		 2D 매트릭스의 (1, 0)\n
		 이미지를 회전하거나 기울일 때 x축의 픽셀 위치에 영향을 주는 값입니다.
		 */
		VBFloat m21;
		/*!
		 2D 매트릭스의 (1, 1)\n
		 이미지의 크기를 조절하거나 회전할 때 y축의 픽셀 위치에 영향을 주는 값입니다.
		 */
		VBFloat m22;
		/*!
		 2D 매트릭스의 (2, 1)\n
		 y축을 따라 각 점이 평행 이동할 거리입니다.
		 */
		VBFloat m23;
		/*!
		 2D 매트릭스의 (0, 2)
		 u,v,w 축의 u입니다.\n
		 VBMatrix2D는 2D영역에서만 작동하기 때문에 u값은 0.0입니다.
		 */
		VBFloat m31;
		/*!
		 2D 매트릭스의 (1, 2)\n
		 u,v,w 축의 v입니다.\n
		 VBMatrix2D는 2D영역에서만 작동하기 때문에 v값은 0.0입니다.
		 */
		VBFloat m32;
		/*!
		 2D 매트릭스의 (2, 2)\n
		 u,v,w 축의 w입니다.\n
		 VBMatrix2D는 2D영역에서만 작동하기 때문에 w값은 1.0입니다.
		 */
		VBFloat m33;
	};
	
	/**
	 @brief 3X3 크기의 2D 매트릭스를 생성합니다.
	 @param _m11 2D 매트릭스의 (0, 0).
	 @param _m12 2D 매트릭스의 (0, 1).
	 @param _m13 2D 매트릭스의 (0, 2).
	 @param _m21 2D 매트릭스의 (1, 0).
	 @param _m22 2D 매트릭스의 (1, 1).
	 @param _m23 2D 매트릭스의 (1, 2).
	 @param _m31 2D 매트릭스의 (2, 0).
	 @param _m32 2D 매트릭스의 (2, 1).
	 @param _m33 2D 매트릭스의 (2, 2).
	 @return _mat 생성된 2D 매트릭스를 반환합니다.
	 */
	VBMatrix2D VBMatrix2DCreate(VBFloat _m11, VBFloat _m12, VBFloat _m13, 
								VBFloat _m21, VBFloat _m22, VBFloat _m23,
								VBFloat _m31, VBFloat _m32, VBFloat _m33);
	
	/**
	 @brief 2개의 2D 매트릭스 각각의 요소를 비교합니다.  
	 @param _mat2D_1 첫번째 2D 매트릭스.
	 @param _mat2D_2 두번째 2D 매트릭스.
	 @return 2개의 2D 매트릭스가 동일할 경우 VBTrue, 동일하지 않을 경우 VBFalse 값을 반환합니다.
	 */
	VBBool VBMatrix2DIsEqual(VBMatrix2D _mat2D_1, VBMatrix2D _mat2D_2);
	
	/**
	 @brief 단위행렬을 반환합니다.
	 @return 단위행렬을 반환합니다.
	 */
	VBMatrix2D VBMatrix2DLoadIdentity(void);
	
	/**
	 @brief Determinant값이 0 일 경우에만 square 매트릭스가 성립합니다.
	 
	 VBMatrix2DInverse함수에서 내부적으로 Determinant값을 확인한 후 역 매트릭스 명령을 수행합니다
	 @param _mat2D 2D 매트릭스.
	 @return _mat2D.m11 * _mat2D.m22 * _mat2D.m33 - 
	 _mat2D.m11 * _mat2D.m23 * _mat2D.m32 + 
	 _mat2D.m12 * _mat2D.m23 * _mat2D.m31 - 
	 _mat2D.m12 * _mat2D.m21 * _mat2D.m33 + 
	 _mat2D.m13 * _mat2D.m21 * _mat2D.m32 - 
	 _mat2D.m13 * _mat2D.m22 * _mat2D.m31; Determinant값을 반환합니다. 
	 */
	VBFloat VBMatrix2DDeterminant(VBMatrix2D _mat2D);
	
	/**
	 @brief 2D 매트릭스의 반대 변형을 수행합니다. 
	 
	 함수 내부에 Determinant 값을 확인합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _invMat2D 2D 매트릭스.
     @return VBTrue면 성공, VBFalse면 실패
	 */
	VBBool VBMatrix2DInverse(VBMatrix2D _mat2D, VBMatrix2D _invMat2D);
	
	/**
	 @brief 2D 매트릭스를 현재 2D 매트릭와 연결하여 두 행렬의 기하학적 효과를 효율적으로 결합합니다. 
	 
	 수학적 용어에서 두 매트릭스을 연결한다는 것은 매트릭스 곱셈을 사용하여 두 매트릭스를 결합하는 것과 같습니다.
	 
	 @param _mat2D_1 기존의 2D 매트릭스.
	 @param _mat2D_2 기존의 2D 매트릭스에 연결할 새로운 2D 매트릭스.
	 @return _mat2D 두 2D 매트릭스의 연결값을 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DMultiply(VBMatrix2D _mat2D_1, VBMatrix2D _mat2D_2);
	
	/**
	 @brief _x 및 _y의 매개 변수에 지정된 대로 x 및 y 축을 따라 2D 매트릭스를 평행 이동합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _x x축을 따라 오른쪽으로 이동할 크기입니다.
	 @param _y y축을 따라 아래쪽으로 이동할 크기입니다.
	 @return x 및 y축을 따라 평행 이동한 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DTranslate(VBMatrix2D _mat2D, VBFloat _x, VBFloat _y);
	
	/**
	 @brief _x의 매개 변수에 지정된 대로 x축을 따라 2D 매트릭스를 평행 이동합니다. 
	 @param _mat2D 2D 매트릭스.
	 @param _x x축을 따라 평행 이동할 크기입니다.
	 @return _tMat2D x축을 따라 평행 이동한 2D 매트릭스를 반환합니다.
	 */
	VBMatrix2D VBMatrix2DTranslateX(VBMatrix2D _mat2D, VBFloat _x);
	
	/**
	 @brief _y의 매개 변수에 지정된 대로 y축을 따라 2D 매트릭스를 평행 이동합니다. 
	 @param _mat2D 2D 매트릭스.
	 @param _y y축을 따라 평행 이동할 크기입니다.
	 @return _tMat2D y축을 따라 평행 이동한 2D 매트릭스를 반환합니다.
	 */
	VBMatrix2D VBMatrix2DTranslateY(VBMatrix2D _mat2D, VBFloat _y);
	
	/**
	 @brief x 및 y 축의 값을 가지고 있는 2D 벡터로 해당 2D 매트릭스를 평행 이동합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _vec2D 2D 벡터.
	 @return _tMat2D 2D 벡터값에 따라 평행 이동한 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DTranslateV(VBMatrix2D _mat2D, VBVector2D _vec2D);
    VBMatrix2D VVBMatrix2DTranslateVA(VBMatrix2D _mat2D, VBVector2D _vec2D);
	
	/**
	 @brief 2D 매트릭스에 x, y축의 양쪽 크기 조절 변형을 적용합니다. 
	 
	 x 축에는 _sx가 곱해지고 y 축에는 _sy가 곱해집니다.\n
	 scale() 메서드는 Matrix 객체의 (0, 0)와 (1, 1) 속성을 변경합니다.
	 
	 @param _mat2D 2D 매트릭스.
	 @param _sx x 축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다.
	 @param _sy y 축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다.
	 @return _sMat2D 크기가 변형된 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DScale(VBMatrix2D _mat2D, VBFloat _sx, VBFloat _sy);
	
	/**
	 @brief 2D 매트릭스에 x축의 크기 조절 변형을 적용합니다. 
	 @param _mat2D 2D 매트릭스.
	 @param _sx x축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다. 
	 @return _sMat2D x축에 따라 크키가 변형된 2D 매트릭스를 반환합니다.
	 */
	VBMatrix2D VBMatrix2DScaleX(VBMatrix2D _mat2D, VBFloat _sx);
	
	/**
	 @brief 2D 매트릭스에 y축의 크기 조절 변형을 적용합니다. 
	 @param _mat2D 2D 매트릭스.
	 @param _sy y축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다. 
	 @return _sMat2D y축에 따라 크키가 변형된 2D 매트릭스를 반환합니다.
	 */
	VBMatrix2D VBMatrix2DScaleY(VBMatrix2D _mat2D, VBFloat _sy);
	
	/**
	 @brief x 및 y 축의 값을 가지고 있는 벡터로 해당 2D 매트릭스의 크기 조절 변형을 적용합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _vec2D 2D 벡터.
	 @return _sMat2D 2D 벡터로 크기가 변형된 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DScaleV(VBMatrix2D _mat2D, VBVector2D _vec2D);
	
	/**
	 @brief 2D Matrix에 회전 변형을 적용합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _angle 라디언 단위의 회전 각도.
	 @return _rMat2D 회전 변형된 2D Matrix를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DRotate(VBMatrix2D _mat2D, VBFloat _angle);
	
	/**
	 @brief 2D Matrix에 지정된 순서대로 지정된 x 및 y축의 기울이기를 적용합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _sx x축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @param _sy y축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @return _sMat2D 기울이기가 적용된 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DShear(VBMatrix2D _mat2D, VBFloat _sx, VBFloat _sy);
	
	/**
	 @brief 2D Matrix에 지정된 순서대로 지정된 x축의 기울이기를 적용합니다
	 @param _mat2D 2D 매트릭스.
	 @param _sx x축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @return _sMat2D x축의 기울이기가 적용된 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DShearX(VBMatrix2D _mat2D, VBFloat _sx);
	
	/**
	 @brief 2D Matrix에 지정된 순서대로 지정된 y축의 기울이기를 적용합니다
	 @param _mat2D 2D 매트릭스.
	 @param _sy y축의 기울이기를 조절하는데 사용하는 배수입니다.
	 @return _sMat2D y축의 기울이기가 적용된 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DShearY(VBMatrix2D _mat2D, VBFloat _sy);
	
	/**
	 @brief x 및 y 축의 값을 가지고 있는 벡터로 해당 2D 매트릭스의 기울이기 변형을 적용합니다.
	 @param _mat2D 2D 매트릭스.
	 @param _vec2D 2D x축과 y축의 기울기 값을 가진 벡터입니다.
	 @return _sMat2D 2D 벡터로 기울이기가 변형된 2D 매트릭스를 반환합니다. 
	 */
	VBMatrix2D VBMatrix2DShearV(VBMatrix2D _mat2D, VBVector2D _vec2D);
	
	/**
	 @brief 2D 매트릭스를 2D 벡터에 연결하여 2D 매트릭스와 2D 벡터의 기하학적 효과를 효율적으로 결합합니다. 
	 @param _mat2D 기존의 2D 매트릭스.
	 @param _vec2D 기존의 2D 매트릭스에 연결할 새로운 2D 벡터.
	 @return _mVec2D 기존의 2D 매트릭스에 연결된 2D 벡터를 반환합니다. 
	 */
	VBVector2D VBMatrix2DMultiplyVBVector2D(VBMatrix2D _mat2D, VBVector2D _vec2D);
	
	/**
	 @brief 2D 매트릭스를 2D 벡터에 연결하여 평행 이동을 제외한 2D 매트릭스와 2D 벡터의 기하학적 효과를 효과적으로 결합합니다. 
	 
	 @param _mat2D 기존의 2D 매트릭스.
	 @param _vec2D 기존의 2D 매트릭스에 연결할 새로운 2D 벡터.
	 @return _mVec2D 기본의 2D 매트릭스에 연결된 2D 벡터를 반환합니다. 
	 */
	VBVector2D VBMatrix2DMultiplyDeltaVBVector2D(VBMatrix2D _mat2D, VBVector2D _vec2D);
	
	/**
	 @brief 2개의 매트릭스를 보간하여 보간된 매트릭스를 리턴합니다.
	 @param _fromMat2D 시작 매트릭스
	 @param _toMat2D 끝 매트릭스
	 @param _num 보간 값(0.0 ~ 1.0)
	 @return _tMat2D 보간된 매트릭스
	 */
	VBMatrix2D VBMatrix2DInterpolate(VBMatrix2D _fromMat2D, VBMatrix2D _toMat2D, VBFloat _num);
	
#ifdef __cplusplus
}
#endif

#endif