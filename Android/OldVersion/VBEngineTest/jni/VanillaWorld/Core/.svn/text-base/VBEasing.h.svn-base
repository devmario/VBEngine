/**
 @file Core/VBEasing.h
 @brief VBEngine의 VBEasing 구조체타입과 여러 함수들.
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

#ifndef __VBEasing_H__
#define __VBEasing_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBEasing함수에서 쓰이는 함수 종류.
	 */
	enum {
		VBEasingType_Linear		=	0x00,
		VBEasingType_Sine		=	0x01,
		VBEasingType_Quint		=	0x02,
		VBEasingType_Quart		=	0x03,
		VBEasingType_Quad		=	0x04,
		VBEasingType_Expo		=	0x05,
		VBEasingType_Elastic	=	0x06,
		VBEasingType_Cubic		=	0x07,
		VBEasingType_Circle		=	0x08,
		VBEasingType_Bounce		=	0x09,
		VBEasingType_Back		=	0x0A
	};
	typedef VBUChar VBEasingType;
	
	/**
	 @brief VBEasing함수에서 쓰이는 애니메이션 타이밍 종류를 열거합니다. 
	 */
	enum {
		VBEasingEquationType_EaseNone	=	0x00,
		VBEasingEquationType_EaseIn		=	0x01,
		VBEasingEquationType_EaseOut	=	0x02,
		VBEasingEquationType_EaseInOut	=	0x03,
		VBEasingEquationType_EaseOutIn	=	0x04
	};
	typedef VBUChar VBEasingEquationType;
	
	/**
	 @brief VBEasingCalculator 함수 타입.
	 
	 트위닝를 사용하여 여러 프레임 또는 수 초에 걸쳐 애니매이션 효과가 나타나도록\n 
	 속성을 지정하여 이동 및 사라지는 효과를 나타낼 수 있도록 합니다.
	 
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)
	 */
	typedef VBFloat (*VBEasingCalculator)(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTiem);
	
	/**
	 @brief Linear 트위닝 함수. (Easing은 일어나지 않는다)
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	 
	 @return 
	 */
	VBFloat VBEasingCalculatorLinear(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Sine (sin(_currentTime)) Ease-In 함수입니다. 
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Sine (sin(_currentTime)) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorSineEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Sine (sin(_currentTime)) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Sine (sin(_currentTime)) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorSineEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Sine (sin(_currentTime)) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Sine (sin(_currentTime)) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorSineEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Sine (sin(_currentTime)) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Sine (sin(_currentTime)) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorSineEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);	
	
	/**
	 @brief Quintic (_currentTime^5) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quintic(_currentTime^5) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuintEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quintic (_currentTime^5) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quintic(_currentTime^5) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuintEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quintic (_currentTime^5) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quintic(_currentTime^5) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuintEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quintic (_currentTime^5) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quintic(_currentTime^5) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuintEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quartic (_currentTime^4) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quartic(_currentTime^4) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuartEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quartic (_currentTime^4) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quartic(_currentTime^4) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuartEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quartic (_currentTime^4) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quartic(_currentTime^4) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuartEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quartic (_currentTime^4) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quartic(_currentTime^4) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuartEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Quadatic (_currentTime^2) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quadratic(_currentTime^2) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuadEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);

	/**
	 @brief Quadatic (_currentTime^2) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quadratic(_currentTime^2) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuadEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/** 
	 @brief Quadatic (_currentTime^2) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quadratic(_currentTime^2) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuadEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);	
	
	/** 
	 @brief Quadatic (_currentTime^2) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Quadratic(_currentTime^2) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorQuadEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);	
	
	/**
	 @brief Exponent (2^_currentTime) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Exponent (2^_currentTime) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorExpoEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Exponent (2^_currentTime) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Exponent (2^_currentTime) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorExpoEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Exponent (2^_currentTime) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Exponent (2^_currentTime) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorExpoEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Exponent (2^_currentTime) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Exponent (2^_currentTime) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorExpoEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorElasticEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorElasticEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorElasticEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Elastic (Sine 곡선을 기하적급수적으로 쇠퇴) Ease-OutIn이 적용된 값을 반환합니다.
	 */	
	VBFloat VBEasingCalculatorElasticEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Cubic (_currentTime^3) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Cubic (_currentTime^3) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCubicEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Cubic (_currentTime^3) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Cubic (_currentTime^3) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCubicEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Cubic (_currentTime^3) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Cubic (_currentTime^3) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCubicEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Cubic (_currentTime^3) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Cubic (_currentTime^3) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCubicEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Circular (sqrt(1-_currentTime^2)) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Circular (sqrt(1-_currentTiem^2)) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCircleEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Circular (sqrt(1-_currentTime^2)) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Circular (sqrt(1-_currentTiem^2)) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCircleEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Circular (sqrt(1-_currentTime^2)) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Circular (sqrt(1-_currentTiem^2)) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCircleEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Circular (sqrt(1-_currentTime^2)) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Circular (sqrt(1-_currentTiem^2)) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorCircleEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);

	/**
	 @brief Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-In 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBounceEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-Out 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBounceEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-InOut 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBounceEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-OutIn 함수입니다.
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Bounce (포물선의 Bounce를 기하급수적으로 쇠퇴, 감퇴) Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBounceEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Back Ease-In 함수입니다. (속도 0에서부터 가속)
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Back Ease-In이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBackEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Back Ease-Out 함수입니다. (속도 0에서부터 감속)
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Back Ease-Out이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBackEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Back Ease-InOut 함수입니다. (중간까지 가속하고 그 이후로 감속)
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Back Ease-InOut이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBackEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief Back Ease-OutIn 함수입니다.(중간까지 감속하고, 그 이후로 가속)
	 @param _currentTime 트위닝되는 대상 객체 속성의 현재값.
	 @param _begin 트윈이 시작되기 전에 대상 객체에서 지정한 속성의 초기 값.
	 @param _end 트위닝되는 대상 객체 속성의 종료 값.
	 @param _totalTime 트위닝된 애니메이션의 지속 시간. (프레임 또는 초 단위)	
	 @return Back Ease-OutIn이 적용된 값을 반환합니다.
	 */
	VBFloat VBEasingCalculatorBackEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime);
	
	/**
	 @brief 트위닝 타입과 공식을 대입해 결과를 계산하는 함수입니다. 
	 
	 _type (Sine, Quint, Quart, Quad, Expo, Elastic, Cubic, Circle, Bounce, Back) \n
	 _equation (EaseIn, EaseOut, EaseInOut, EaseOutIn) \n
	 변수 _type과 _equation에 선택에 따라 애니매이션 효과를 달리할 수 있습니다.
	 
	 @param _type 적용할 트위닝 타입. 
	 @param _equation 적용할 애니매이션 효과. 
	 @return 적용되어진 트위닝 타입/애니매이션 효과가 계산된 결과를 반환합니다. 
	 */
	VBEasingCalculator VBEasingGetCalculator(VBEasingType _type, VBEasingEquationType _equation);
	
#ifdef __cplusplus
}
#endif

#endif