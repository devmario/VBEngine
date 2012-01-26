/**
 @file Core/VBMatrixWrapper.h
 @brief VBEngine의 VBMatrixWrapper 구조체타입과 여러 함수들.
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

#ifndef __VBMatrix2DWrapper_H__
#define __VBMatrix2DWrapper_H__

#include "VBMatrix2D.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBMatrix2DWrapper의 구조체 타입.
	 */
	typedef struct VBMatrix2DWrapper VBMatrix2DWrapper;

	/**
	 @brief VBMatrix2DWrapper의 구조체.
	 */	
	struct VBMatrix2DWrapper {
		/*!
		 VBMatrix2D.
		 */
		VBMatrix2D mat;
		/*!
		 VBMatrix2D의 업데이트 확인값
		 */
		VBBool need_update;
		/*!
		 VBVector2D의 위치
		 */
		VBVector2D position;
        VBVector2D anchor;
		/*!
		 VBVector2D의 크기
		 */
		VBVector2D scale;
		/*!
		 VBVector2D의 기울기
		 */
		VBVector2D shear;
		/*!
		 회전값
		 */
		VBFloat rotation;
	};
	
	/**
	 @brief 초기화 된 VBMatrix2D와 초기화된 VBVector2D의 값(position, scale, shear, posotion)을 VBMatrixWrapper2D로 대입합니다. 
     @return 단위행렬과 초기화된 값들을 리턴합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperLoadIdentity(void);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 위치값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _pos 위치값.
	 @return _wrapper 위치값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetPosition(VBMatrix2DWrapper _wrapp, VBVector2D _pos);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 위치값을 반환합니다. 
	 @param _wrapp VBMartrix2DWrapper.
     @return 위치값을 반환합니다.
	 */
	VBVector2D VBMatrix2DWrapperGetPosition(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 가로축 값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMartrix2DWrapper.
	 @param _x 가로축값.
	 @return _wrapp 가로축 값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetX(VBMatrix2DWrapper _wrapp, VBFloat _x);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 가로축 값을 반환합니다.
	 @param _wrapp VBMartrix2DWrapper.
     @return x좌표의 값을 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetX(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 세로축 값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMartrix2DWrapper.
	 @param _x 세로축값.
	 @return _wrapp 세로축 값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetY(VBMatrix2DWrapper _wrapp, VBFloat _y);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 세로축 값을 반환합니다.
	 @param _wrapp VBMartrix2DWrapper.
     @return y좌표의 값을 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetY(VBMatrix2DWrapper _wrapp);
    
    /**
     @brief VBMatrix2DWrapper에 anchor를 설정합니다.
     @param _wrapp VBMatrix2DWrapper
     @param _anchor 회전축
     @return anchor가 설정된 VBMatrix2DWrapper
     */
	VBMatrix2DWrapper VBMatrix2DWrapperSetAnchor(VBMatrix2DWrapper _wrapp, VBVector2D _anchor);
    /**
     @brief VBMatrix2DWrapper에서 anchor를 반환합니다.
     @param _wrapp VBMatrix2DWrapper
     @return anchor를 반환합니다.
     */
	VBVector2D VBMatrix2DWrapperGetAnchor(VBMatrix2DWrapper _wrapp);
    
    /**
     @brief VBMatrix2DWrapper의 anchor에 x값을 설정합니다.
     @param _wrapp VBMatrix2DWrapper
     @param _ax 설정할 anchor의 x값
     @return 값이 설정된 VBMatrix2DWrapper
     */
    VBMatrix2DWrapper VBMatrix2DWrapperSetAnchorX(VBMatrix2DWrapper _wrapp, VBFloat _ax);
    /**
     @brief VBMatrix2DWrapper에서 anchor의 x값을 반환합니다.
     @param _wrapp VBMatrix2DWrapper
     @return VBMatrix2DWrapper에서 anchor의 x값
     */
    VBFloat VBMatrix2DWrapperGetAnchorX(VBMatrix2DWrapper _wrapp);
    /**
     @brief VBMatrix2DWrapper에서 anchor의 y값을 설정합니다.
     @param _wrapp VBMatrix2DWrapper
     @param _ay 설정할 anchor의 y값
     @return 값이 설정된 VBMatrix2DWrapper
     */
    VBMatrix2DWrapper VBMatrix2DWrapperSetAnchorY(VBMatrix2DWrapper _wrapp, VBFloat _ay);
    /**
     @brief VBMatrix2DWrapper에서 anchor의 y값을 반환합니다.
     @param _wrapp VBMatrix2DWrapper
     @return VBMatrix2DWrapper에서 anchor의 y값
     */
    VBFloat VBMatrix2DWrapperGetAnchorY(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 크기값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _scale 크기값.
	 @return _wrapper 크기값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetScale(VBMatrix2DWrapper _wrapp, VBVector2D _scale);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 크기값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return 크기 변형값을 벡터로 리턴합니다.
	 */
	VBVector2D VBMatrix2DWrapperGetScale(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 가로축의 크기값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _xs 가로축값.
	 @return _wrapper 가로축의 크기값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetXScale(VBMatrix2DWrapper _wrapp, VBFloat _xs);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 가로축의 크기값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return x축으로 크기변형값을 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetXScale(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 세로축의 크기값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _ys 가로축값.
	 @return _wrapper 세로축의 크기값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetYScale(VBMatrix2DWrapper _wrapp, VBFloat _ys);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 세로축의 크기값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return y축으로 크기변형값을 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetYScale(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 기울기값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _shear 기울기값.
	 @return _wrapper 기울기값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetShear(VBMatrix2DWrapper _wrapp, VBVector2D _shear);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 기울기값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return 기울이기 값을 벡터형태로 반환합니다.
	 */
	VBVector2D VBMatrix2DWrapperGetShear(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 가로축의 기울기값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _sx 가로축의 기울기값.
	 @return _wrapper 가로축의 기울기값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetXShear(VBMatrix2DWrapper _wrapp, VBFloat _sx);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 가로축의 기울기값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return x축의 기울이기값을 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetXShear(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 세로축의 기울기값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _sy 세로축의 기울기값.
	 @return _wrapper 세로축의 기울기값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetYShear(VBMatrix2DWrapper _wrapp, VBFloat _sy);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 세로축의 기울기값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return y축의 기울이기값을 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetYShear(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMartrix2DWrapper에 새로운 회전값을 대입한 후 업데이트 합니다.
	 @param _wrapp VBMatrix2DWrapper.
	 @param _position 회전값.
	 @return _wrapper 회전값이 업데이트된 VBMatrix2DWrapper를 반환합니다.
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperSetRotation(VBMatrix2DWrapper _wrapp, VBFloat _rotation);
	
	/**
	 @brief VBMartrix2DWrapper의 업데이트된 회전값을 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return 회전 각도를 반환합니다.
	 */
	VBFloat VBMatrix2DWrapperGetRotation(VBMatrix2DWrapper _wrapp);
	
	/**
	 @brief VBMatrix2DWrapper에서 업데이트 된 모든 값(위치, 크기, 기울기, 회전)을 대입한 VBMatrix2D를 반환합니다.
	 @param _wrapp VBMatrix2DWrapper.
     @return 업데이트된 VBMatrix2DWrapper
	 */
	VBMatrix2DWrapper VBMatrix2DWrapperUpdate(VBMatrix2DWrapper _wrapp);
    
    /**
     @brief VBMatrix2DWrapper에서 VBMatrix2D를 반환합니다.
     @param _wrapp VBMatrix2DWrapper
     @return VBMatrix2D
     */
    VBMatrix2D VBMatrix2DWrapperGetMatrix(VBMatrix2DWrapper _wrapp);
    
    /**
     @brief _wrapp1과 _wrapp2를 보간하여 새로운 VBMatrix2DWrapper를 반환합니다.
     @param _wrapp1 VBMatrix2DWrapper
     @param _wrapp2 VBMatrix2DWrapper
     @param _num 보간계수(0.0 ~ 1.0)
     @return 보간된 VBMatrix2DWrapper
     */
    VBMatrix2DWrapper VBMatrix2DWrapperInterpolate(VBMatrix2DWrapper _wrapp1, VBMatrix2DWrapper _wrapp2, VBFloat _num);
	
#ifdef __cplusplus
}
#endif

#endif