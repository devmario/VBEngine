#ifndef __TWEEN_H__
#define __TWEEN_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
#include "Array.h"
	
	enum {
		TweenTrasitionTypeLinear = 0,
		TweenTrasitionTypeSine = 1,
		TweenTrasitionTypeQuint = 2,
		TweenTrasitionTypeQuart = 3,
		TweenTrasitionTypeQuad = 4,
		TweenTrasitionTypeExpo = 5,
		TweenTrasitionTypeElastic = 6,
		TweenTrasitionTypeCubic = 7,
		TweenTrasitionTypeCircle = 8,
		TweenTrasitionTypeBounce = 9,
		TweenTrasitionTypeBack = 10
	};
	typedef unsigned char TweenTrasitionType;
	
	enum {
		TweenEquationTypeEaseIn = 0,
		TweenEquationTypeEaseOut = 1,
		TweenEquationTypeEaseInOut = 2
	};
	typedef unsigned char TweenEquationType;
	
	typedef struct TweenProperty TweenProperty;
	typedef struct Tween Tween;
	typedef struct TweenManager TweenManager;
	
	typedef void (*TweenEvent)(Tween* tween, void* userReference);
	
	typedef struct TweenEventComplete TweenEventComplete;
	struct TweenEventComplete {
		void* userReference;
		TweenEvent event;
	};
	
	typedef struct TweenEventStep TweenEventStep;
	struct TweenEventStep {
		void* userReference;
		TweenEvent event;
	};
	
	typedef struct TweenEventPlay TweenEventPlay;
	struct TweenEventPlay {
		void* userReference;
		TweenEvent event;
	};
	
	typedef struct TweenEventStop TweenEventStop;
	struct TweenEventStop {
		void* userReference;
		TweenEvent event;
	};
	
	typedef float (*TweenCalculator)(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorLinear(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorSineEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorSineEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorSineEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorQuintEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorQuintEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorQuintEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorQuartEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorQuartEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorQuartEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorQuadEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorQuadEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorQuadEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorExpoEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorExpoEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorExpoEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorElasticEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorElasticEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorElasticEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorCubicEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorCubicEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorCubicEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorCircleEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorCircleEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorCircleEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorBounceEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorBounceEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorBounceEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	float TweenCalculatorBackEaseIn(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorBackEaseOut(float currentTime, float begin, float end, float totalTime);
	float TweenCalculatorBackEaseInOut(float currentTime, float begin, float end, float totalTime);
	
	struct TweenProperty {
		float* property;
		float propertyBegin;
		float propertyEnd;
	};
	
	struct Tween {
		unsigned short delayFrame;
		unsigned short transitionFrame;
		unsigned short totalFrame;
		unsigned short currentFrame;
		
		TweenCalculator tweenCalculator;
		
		TweenEventComplete completeEvent;
		TweenEventStep stepEvent;
		TweenEventPlay playEvent;
		TweenEventStop stopEvent;
		
		Array* property;
		
		bool isPlay;
	};
	
	struct TweenManager {
		Array* tween;
	};
	
	bool TweenManagerStart(TweenManager* manager);
	bool TweenManagerShutdown(TweenManager* manager);
	
	bool TweenManagerAddTween(TweenManager* manager, Tween* tween);
	bool TweenManagerRemoveTween(TweenManager* manager, Tween* tween);
	
	bool TweenManagerStep(TweenManager* manager, signed short frame);
	
	bool TweenInit(Tween* tween, unsigned short transitionFrame, unsigned short delayFrame, TweenTrasitionType transition, TweenEquationType equation);
	bool TweenInitCustomCalculator(Tween* tween, unsigned short transitionFrame, unsigned short delayFrame, TweenCalculator tweenCalculator);
	bool TweenFree(Tween* tween);
	
	TweenCalculator TweenGetCalculator(TweenTrasitionType transition, TweenEquationType equation);
	
	bool TweenStep(Tween* tween, signed short frame);
	
	TweenEventComplete TweenEventCompleteInit(void (*event)(Tween* tween, void* userReference), void* userReference);
	TweenEventStep TweenEventStepInit(void (*event)(Tween* tween, void* userReference), void* userReference);
	TweenEventPlay TweenEventPlayInit(void (*event)(Tween* tween, void* userReference), void* userReference);
	TweenEventStop TweenEventStopInit(void (*event)(Tween* tween, void* userReference), void* userReference);
	
	bool TweenAddEventComplete(Tween* tween, TweenEventComplete completeEvent);
	bool TweenAddEventStep(Tween* tween, TweenEventStep stepEvent);
	bool TweenAddEventPlay(Tween* tween, TweenEventPlay playEvent);
	bool TweenAddEventStop(Tween* tween, TweenEventStop stopEvent);
	
	bool TweenRemoveEventComplete(Tween* tween);
	bool TweenRemoveEventStep(Tween* tween);
	bool TweenRemoveEventPlay(Tween* tween);
	bool TweenRemoveEventStop(Tween* tween);
	
	TweenProperty TweenPropertyInit(float* property, float propertyBegin, float propertyEnd);
	
	TweenProperty* TweenAddProperty(Tween* tween, TweenProperty property);
	bool TweenRemoveProperty(Tween* tween, TweenProperty* property);
	
	bool TweenPlay(Tween* tween);
	bool TweenStop(Tween* tween);
	bool TweenGoToAndPlay(Tween* tween, unsigned long frame);
	bool TweenGoToAndStop(Tween* tween, unsigned long frame);
	
	unsigned short TweenGetTotalFrame(Tween* tween);
	unsigned short TweenGetCurrentFrame(Tween* tween);
	
#ifdef __cplusplus
}
#endif


#endif