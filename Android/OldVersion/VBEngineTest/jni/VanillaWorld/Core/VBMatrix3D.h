/**
 @file Core/VBMatrix3D.h
 @brief VBEngine의 VBMatrix3D 구조체타입과 여러 함수들.
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

#ifndef __VBMatrix3D_H__
#define __VBMatrix3D_H__

#include "VBVector3D.h"
#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBMatrix3D 관련 구조체타입.
	 */
	typedef struct VBMatrix3D VBMatrix3D;
	
	/**
	 @brief VBMatrix3D 관련 구조체.
	 */
	struct VBMatrix3D {
        /*!
		 3D 매트릭스의 (0, 0)\n
		 */
		VBFloat m11;
        /*!
		 3D 매트릭스의 (0, 1)\n
		 */
		VBFloat m12;
        /*!
		 3D 매트릭스의 (0, 2)\n
		 */
		VBFloat m13;
        /*!
		 3D 매트릭스의 (0, 3)\n
		 */
		VBFloat m14;
        /*!
		 3D 매트릭스의 (1, 0)\n
		 */
		VBFloat m21;
        /*!
		 3D 매트릭스의 (1, 1)\n
		 */
		VBFloat m22;
        /*!
		 3D 매트릭스의 (1, 2)\n
		 */
		VBFloat m23;
        /*!
		 3D 매트릭스의 (1, 3)\n
		 */
		VBFloat m24;
        /*!
		 3D 매트릭스의 (2, 0)\n
		 */
		VBFloat m31;
        /*!
		 3D 매트릭스의 (2, 1)\n
		 */
		VBFloat m32;
        /*!
		 3D 매트릭스의 (2, 2)\n
		 */
		VBFloat m33;
        /*!
		 3D 매트릭스의 (2, 3)\n
		 */
		VBFloat m34;
        /*!
		 3D 매트릭스의 (3, 0)\n
		 */
		VBFloat m41;
        /*!
		 3D 매트릭스의 (3, 1)\n
		 */
		VBFloat m42;
        /*!
		 3D 매트릭스의 (3, 2)\n
		 */
		VBFloat m43;
        /*!
		 3D 매트릭스의 (3, 3)\n
		 */
		VBFloat m44;
	};
	
    /**
	 @brief 4X4 크기의 3D 매트릭스를 생성합니다.
	 @param _m11 3D 매트릭스의 (0, 0).
	 @param _m12 3D 매트릭스의 (0, 1).
	 @param _m13 3D 매트릭스의 (0, 2).
     @param _m14 3D 매트릭스의 (0, 3).
	 @param _m21 3D 매트릭스의 (1, 0).
	 @param _m22 3D 매트릭스의 (1, 1).
	 @param _m23 3D 매트릭스의 (1, 2).
     @param _m24 3D 매트릭스의 (1, 3).
	 @param _m31 3D 매트릭스의 (2, 0).
	 @param _m32 3D 매트릭스의 (2, 1).
	 @param _m33 3D 매트릭스의 (2, 2).
     @param _m34 3D 매트릭스의 (2, 3).
     @param _m41 3D 매트릭스의 (3, 0).
	 @param _m42 3D 매트릭스의 (3, 1).
	 @param _m43 3D 매트릭스의 (3, 2).
     @param _m44 3D 매트릭스의 (3, 3).
	 @return _mat 생성된 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DCreate(VBFloat _m11, VBFloat _m12, VBFloat _m13, VBFloat _m14,
								VBFloat _m21, VBFloat _m22, VBFloat _m23, VBFloat _m24,
								VBFloat _m31, VBFloat _m32, VBFloat _m33, VBFloat _m34,
								VBFloat _m41, VBFloat _m42, VBFloat _m43, VBFloat _m44);
        
    /**
	 @brief 2개의 3D 매트릭스 각각의 요소를 비교합니다.  
	 @param _mat2D_1 첫번째 3D 매트릭스.
	 @param _mat2D_2 두번째 3D 매트릭스.
	 @return 2개의 3D 매트릭스가 동일할 경우 VBTrue, 동일하지 않을 경우 VBFalse 값을 반환합니다.
	 */
    VBBool VBMatrix3DIsEqual(VBMatrix3D _mat3D_1, VBMatrix3D _mat3D_2);
	
    /**
	 @brief 단위행렬을 반환합니다.
	 @return 단위행렬을 반환합니다.
	 */
	VBMatrix3D VBMatrix3DLoadIdentity(void);
		
    /**
	 @brief Determinant값이 0 일 경우에만 square 매트릭스가 성립합니다.
	 
	 VBMatrix3DInverse함수에서 내부적으로 Determinant값을 확인한 후 역 매트릭스 명령을 수행합니다
	 @param _mat3D 3D 매트릭스.
	 @return _mat3D.m11 * _mat3D.m22 * _mat3D.m33 * _mat3D.m44 - 
	 _mat3D.m11 * _mat3D.m24 * _mat3D.m33 * _mat3D.m42 + 
	 _mat3D.m12 * _mat3D.m23 * _mat3D.m34 * _mat3D.m41 - 
	 _mat3D.m12 * _mat3D.m21 * _mat3D.m34 * _mat3D.m43 + 
	 _mat3D.m13 * _mat3D.m24 * _mat3D.m31 * _mat3D.m42 - 
	 _mat3D.m13 * _mat3D.m22 * _mat3D.m31 * _mat3D.m44 +
     _mat3D.m14 * _mat3D.m21 * _mat3D.m32 * _mat3D.m43 -
     _mat3D.m14 * _mat3D.m23 * _mat3D.m31 * _mat3D.m44; Determinant값을 반환합니다. 
	 */
	VBFloat VBMatrix3DDeterminant(VBMatrix3D _mat3D);
	
    /**
	 @brief 3D 매트릭스의 반대 변형을 수행합니다. 
	 
	 함수 내부에 Determinant 값을 확인합니다.
	 @param _mat2D 3D 매트릭스.
	 @param _invMat3D 3D 매트릭스.
     @return VBTrue면 성공, VBFalse면 실패
	 */
	VBMatrix3D VBMatrix3DInverse(VBMatrix3D _mat3D);
	
    /**
	 @brief 3D 매트릭스를 현재 3D 매트릭스와 연결하여 두 행렬의 기하학적 효과를 효율적으로 결합합니다. 
	 
	 수학적 용어에서 두 매트릭스을 연결한다는 것은 매트릭스 곱셈을 사용하여 두 매트릭스를 결합하는 것과 같습니다.
	 
	 @param _mat3D_1 기존의 3D 매트릭스.
	 @param _mat3D_2 기존의 3D 매트릭스에 연결할 새로운 3D 매트릭스.
	 @return _mat3D 두 3D 매트릭스의 연결값을 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DMultiply(VBMatrix3D _mat3D_1, VBMatrix3D _mat3D_2);
	
    /**
	 @brief _x, _y, _z의 매개 변수에 지정된 대로 x, y, z 축을 따라 3D 매트릭스를 평행 이동합니다.
	 @param _mat3D 3D 매트릭스.
	 @param _x x축을 따라 이동할 크기입니다.
	 @param _y y축을 따라 이동할 크기입니다.
     @param _z z축을 따라 이동할 크기입니다.
	 @return x, y, z축을 따라 평행 이동한 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DTranslate(VBMatrix3D _mat3D, VBFloat _x, VBFloat _y, VBFloat _z);
	
    /**
	 @brief _x의 매개 변수에 지정된 대로 x축을 따라 3D 매트릭스를 평행 이동합니다. 
	 @param _mat3D 3D 매트릭스.
	 @param _x x축을 따라 평행 이동할 크기입니다.
	 @return _tMat3D x축을 따라 평행 이동한 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DTranslateX(VBMatrix3D _mat3D, VBFloat _x);
	
    /**
	 @brief _y의 매개 변수에 지정된 대로 y축을 따라 3D 매트릭스를 평행 이동합니다. 
	 @param _mat3D 3D 매트릭스.
	 @param _y y축을 따라 평행 이동할 크기입니다.
	 @return _tMat3D y축을 따라 평행 이동한 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DTranslateY(VBMatrix3D _mat3D, VBFloat _y);
	
    /**
	 @brief _z의 매개 변수에 지정된 대로 z축을 따라 3D 매트릭스를 평행 이동합니다. 
	 @param _mat3D 3D 매트릭스.
	 @param _z z축을 따라 평행 이동할 크기입니다.
	 @return _tMat3D z축을 따라 평행 이동한 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DTranslateZ(VBMatrix3D _mat3D, VBFloat _z);
	
    /**
	 @brief x, y, z 축의 값을 가지고 있는 3D 벡터로 해당 3D 매트릭스를 평행 이동합니다.
	 @param _mat2D 3D 매트릭스.
	 @param _vec2D 3D 벡터.
	 @return _tMat2D 3D 벡터값에 따라 평행 이동한 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DTranslateV(VBMatrix3D _mat3D, VBVector3D _vec3D);
	
    /**
	 @brief 3D 매트릭스에 x, y, z축의 양쪽 크기 조절 변형을 적용합니다. 
	 
	 x 축에는 _sx가 y 축에는 _sy, z축에는 _sz가 곱해집니다.\n
	 
	 @param _mat3D 3D 매트릭스.
	 @param _sx x 축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다.
	 @param _sy y 축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다.
     @param _sz z 축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다.
	 @return _sMat3D 크기가 변형된 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DScale(VBMatrix3D _mat3D, VBFloat _sx, VBFloat _sy, VBFloat _sz);
	
    /**
	 @brief 3D 매트릭스에 x축의 크기 조절 변형을 적용합니다. 
	 @param _mat3D 3D 매트릭스.
	 @param _sx x축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다. 
	 @return _sMat3D x축에 따라 크키가 변형된 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DScaleX(VBMatrix3D _mat3D, VBFloat _sx);
	
    /**
	 @brief 3D 매트릭스에 y축의 크기 조절 변형을 적용합니다. 
	 @param _mat3D 3D 매트릭스.
	 @param _sy y축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다. 
	 @return _sMat3D y축에 따라 크키가 변형된 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DScaleY(VBMatrix3D _mat3D, VBFloat _sy);
	
    /**
	 @brief 3D 매트릭스에 z축의 크기 조절 변형을 적용합니다. 
	 @param _mat3D 3D 매트릭스.
	 @param _sz z축을 따라 객체의 크기를 조절하는 데 사용되는 배수입니다. 
	 @return _sMat3D z축에 따라 크키가 변형된 3D 매트릭스를 반환합니다.
	 */
	VBMatrix3D VBMatrix3DScaleZ(VBMatrix3D _mat3D, VBFloat _sz);
	
    /**
	 @brief x, y, z 축의 값을 가지고 있는 벡터로 해당 3D 매트릭스의 크기 조절 변형을 적용합니다.
	 @param _mat3D 3D 매트릭스.
	 @param _vec3D 3D 벡터.
	 @return _sMat3D 3D 벡터로 크기가 변형된 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DScaleV(VBMatrix3D _mat3D, VBVector3D _vec3D);
	
    /**
	 @brief 3D Matrix에 회전 변형을 적용합니다.
	 @param _mat3D 3D 매트릭스.
	 @param _angle 라디언 단위의 회전 각도.
	 @return _rMat3D 회전 변형된 3D Matrix를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DRotate(VBMatrix3D _mat3D, VBFloat _angle);
	
    /**
	 @brief 3D Matrix에 지정된 순서대로 지정된 x, y, z축의 기울이기를 적용합니다.
	 @param _mat3D 3D 매트릭스.
	 @param _sx x축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @param _sy y축의 기울이기를 조절하는데 사용하는 배수입니다. 
     @param _sz z축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @return _sMat3D 기울이기가 적용된 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DShear(VBMatrix3D _mat3D, VBFloat _sx, VBFloat _sy, VBFloat _sz);
	
    /**
	 @brief 3D Matrix에 지정된 순서대로 지정된 x축의 기울이기를 적용합니다
	 @param _mat3D 3D 매트릭스.
	 @param _sx x축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @return _sMat3D x축의 기울이기가 적용된 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DShearX(VBMatrix3D _mat3D, VBFloat _sx);
	
    /**
	 @brief 3D Matrix에 지정된 순서대로 지정된 y축의 기울이기를 적용합니다
	 @param _mat3D 3D 매트릭스.
	 @param _sy y축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @return _sMat3D y축의 기울이기가 적용된 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DShearY(VBMatrix3D _mat3D, VBFloat _sy);
	
    /**
	 @brief 3D Matrix에 지정된 순서대로 지정된 z축의 기울이기를 적용합니다
	 @param _mat3D 3D 매트릭스.
	 @param _sx z축의 기울이기를 조절하는데 사용하는 배수입니다. 
	 @return _sMat3D z축의 기울이기가 적용된 3D 매트릭스를 반환합니다. 
	 */
	VBMatrix3D VBMatrix3DShearZ(VBMatrix3D _mat3D, VBFloat _sz);
    
    /**
	 @brief x, y, z 축의 값을 가지고 있는 벡터로 해당 3D 매트릭스의 기울이기 변형을 적용합니다.
	 @param _mat3D 3D 매트릭스.
	 @param _vec3D 3D x, y, z축의 기울기 값을 가진 벡터입니다.
	 @return _sMat3D 3D 벡터로 기울이기가 변형된 3D 매트릭스를 반환합니다. 
	 */
    VBMatrix3D VBMatrix3DShearV(VBMatrix3D _mat3D, VBVector3D _vec3D);
	
    /**
	 @brief 3D 매트릭스를 3D 벡터에 연결하여 3D 매트릭스와 3D 벡터의 기하학적 효과를 효율적으로 결합합니다. 
	 @param _mat3D 기존의 3D 매트릭스.
	 @param _vec3D 기존의 3D 매트릭스에 연결할 새로운 3D 벡터.
	 @return _mVec3D 기존의 3D 매트릭스에 연결된 3D 벡터를 반환합니다. 
	 */
	VBVector3D VBMatrix3DMultiplyVBVector3D(VBMatrix3D _mat3D, VBVector3D _vec3D);
	
#ifdef __cplusplus
}
#endif

#endif