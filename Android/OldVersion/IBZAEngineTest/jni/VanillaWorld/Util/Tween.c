#include "Tween.h"
#include <math.h>
#include <stdlib.h>

float TweenCalculatorLinear(float currentTime, float begin, float end, float totalTime) {
	return end * currentTime / totalTime + begin;
}

float TweenCalculatorSineEaseIn(float currentTime, float begin, float end, float totalTime) {
	return -end * cosf(currentTime / totalTime * (M_PI * 0.5)) + end + begin;
}

float TweenCalculatorSineEaseOut(float currentTime, float begin, float end, float totalTime) {
	return end * sinf(currentTime / totalTime * (M_PI * 0.5)) + begin;
}

float TweenCalculatorSineEaseInOut(float currentTime, float begin, float end, float totalTime) {
	return -end * 0.5 * (cosf(M_PI * currentTime / totalTime) - 1.0) + begin;
}

float TweenCalculatorQuintEaseIn(float currentTime, float begin, float end, float totalTime) {
	return end * (currentTime /= totalTime) * currentTime * currentTime * currentTime * currentTime + begin;
}

float TweenCalculatorQuintEaseOut(float currentTime, float begin, float end, float totalTime) {
	return end * ((currentTime = currentTime / totalTime - 1.0) * currentTime * currentTime * currentTime * currentTime + 1.0) + begin;
}

float TweenCalculatorQuintEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if((currentTime /= totalTime * 0.5) < 1.0) {
		return end * 0.5 * currentTime * currentTime * currentTime * currentTime * currentTime + begin;
	}
	return end * 0.5 * ((currentTime -= 2.0) * currentTime * currentTime * currentTime * currentTime + 2.0) + begin;
}

float TweenCalculatorQuartEaseIn(float currentTime, float begin, float end, float totalTime) {
	return end * (currentTime /= totalTime) * currentTime * currentTime * currentTime + begin;
}

float TweenCalculatorQuartEaseOut(float currentTime, float begin, float end, float totalTime) {
	return -end * ((currentTime = currentTime / totalTime - 1.0) * currentTime * currentTime * currentTime - 1.0) + begin;
}

float TweenCalculatorQuartEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if((currentTime /= totalTime * 0.5) < 1.0) {
		return end * 0.5 * currentTime * currentTime * currentTime * currentTime + begin;
	}
	return -end * 0.5 * ((currentTime -= 2.0) * currentTime * currentTime * currentTime - 2.0) + begin;
}

float TweenCalculatorQuadEaseIn(float currentTime, float begin, float end, float totalTime) {
	return end * (currentTime /= totalTime) * currentTime + begin;
}

float TweenCalculatorQuadEaseOut(float currentTime, float begin, float end, float totalTime) {
	return -end * (currentTime /= totalTime) * (currentTime - 2.0) + begin;
}

float TweenCalculatorQuadEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if((currentTime /= totalTime * 0.5) < 1.0) {
		return ((end * 0.5) * (currentTime * currentTime)) + begin;
	}
	return -end * 0.5 * (((currentTime - 2.0) * (--currentTime)) - 1.0) + begin;
}

float TweenCalculatorExpoEaseIn(float currentTime, float begin, float end, float totalTime) {
	return (currentTime == 0.0) ? begin : end * powf(2.0, 10.0 * (currentTime / totalTime - 1.0)) + begin;
}

float TweenCalculatorExpoEaseOut(float currentTime, float begin, float end, float totalTime) {
	return (currentTime == totalTime) ? begin + end : end * (-powf(2.0, -10.0 * currentTime / totalTime) + 1.0) + begin;
}

float TweenCalculatorExpoEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if(currentTime == 0.0) {
		return begin;
	}
	if(currentTime == totalTime) {
		return begin + end;
	}
	if((currentTime /= totalTime / 2) < 1) {
		return end / 2 * powf(2, 10 * (currentTime - 1)) + begin;
	}
	return end / 2 * (-powf(2, -10 * --currentTime) + 2) + begin;
}

float TweenCalculatorElasticEaseIn(float currentTime, float begin, float end, float totalTime) {
	if(currentTime == 0.0) {
		return begin;
	}
	if((currentTime /= totalTime) == 1.0) {
		return begin + end;
	}
	float p = totalTime * 0.3;
	float a = end;
	float s = p * 0.25;
	float postFix = a * powf(2.0, 10.0 * (currentTime -= 1.0));
	return -(postFix * sinf((currentTime * totalTime - s) * (2.0 * M_PI) / p)) + begin;
}

float TweenCalculatorElasticEaseOut(float currentTime, float begin, float end, float totalTime) {
	if(currentTime == 0.0) {
		return begin;  
	}
	if((currentTime /= totalTime) == 1.0) {
		return begin + end;
	}
	float p = totalTime * 0.3;
	float a = end;
	float s = p * 0.25;
	return a * powf(2.0, -10.0 * currentTime) * sinf((currentTime * totalTime - s) * (2.0 * M_PI) / p) + end + begin;
}

float TweenCalculatorElasticEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if(currentTime == 0.0) {
		return begin;  
	}
	if((currentTime /= totalTime * 0.5) == 2.0) {
		return begin + end;
	}
	float p = totalTime * (0.3 * 1.5);
	float a = end;
	float s = p * 0.25;
	if(currentTime < 1.0) {
		float postFix = a * powf(2.0, 10.0 * (currentTime -= 1.0));
		return -0.5 * (postFix * sinf((currentTime * totalTime - s) * (2.0 * M_PI) /p)) + begin;
	}
	float postFix = a * powf(2.0, -10.0 * (currentTime -= 1.0));
	return postFix * sinf((currentTime * totalTime - s) * (2.0 * M_PI) / p) * 0.5 + end + begin;
}

float TweenCalculatorCubicEaseIn(float currentTime, float begin, float end, float totalTime) {
	return end * (currentTime /= totalTime) * currentTime * currentTime + begin;
}

float TweenCalculatorCubicEaseOut(float currentTime, float begin, float end, float totalTime) {
	return end * ((currentTime = currentTime / totalTime - 1.0) * currentTime * currentTime + 1.0) + begin;
}

float TweenCalculatorCubicEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if((currentTime /= totalTime * 0.5) < 1.0) {
		return end * 0.5 * currentTime * currentTime * currentTime + begin;
	}
	return end * 0.5 * ((currentTime -= 2.0) * currentTime * currentTime + 2.0) + begin;
}

float TweenCalculatorCircleEaseIn(float currentTime, float begin, float end, float totalTime) {
	return -end * (sqrtf(1.0 - (currentTime /= totalTime) * currentTime) - 1.0) + begin;
}

float TweenCalculatorCircleEaseOut(float currentTime, float begin, float end, float totalTime) {
	return end * sqrtf(1.0 - (currentTime = currentTime / totalTime - 1.0) * currentTime) + begin;
}

float TweenCalculatorCircleEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if((currentTime /= totalTime * 0.5) < 1.0) {
		return -end * 0.5 * (sqrtf(1.0 - currentTime * currentTime) - 1.0) + begin;
	}
	return end * 0.5 * (sqrtf(1.0 - currentTime * (currentTime -= 2.0)) + 1.0) + begin;
}

float TweenCalculatorBounceEaseIn(float currentTime, float begin, float end, float totalTime) {
	return end - TweenCalculatorBounceEaseOut(totalTime - currentTime, 0.0, end, totalTime) + begin;
}

float TweenCalculatorBounceEaseOut(float currentTime, float begin, float end, float totalTime) {
	if((currentTime /= totalTime) < (1 / 2.75)) {
		return end * (7.5625 * currentTime * currentTime) + begin;
	} else if(currentTime < (2 / 2.75)) {
		float postFix = currentTime -= (1.5 / 2.75);
		return end * (7.5625 * postFix * currentTime + 0.75) + begin;
	} else if(currentTime < (2.5 / 2.75)) {
		float postFix = currentTime -= (2.25 / 2.75);
		return end * (7.5625 * postFix * currentTime + 0.9375) + begin;
	} else {
		float postFix = currentTime -= (2.625 / 2.75);
		return end * (7.5625 * postFix * currentTime + 0.984375) + begin;
	}
}

float TweenCalculatorBounceEaseInOut(float currentTime, float begin, float end, float totalTime) {
	if(currentTime < totalTime * 0.5) {
		return TweenCalculatorBounceEaseIn(currentTime * 2.0, 0.0, end, totalTime) * 0.5 + begin;
	} else {
		return TweenCalculatorBounceEaseOut(currentTime * 2.0 - totalTime, 0.0, end, totalTime) * 0.5 + end * 0.5 + begin;
	}
}

float TweenCalculatorBackEaseIn(float currentTime, float begin, float end, float totalTime) {
	float s = 1.70158;
	float postFix = currentTime /= totalTime;
	return end * postFix * currentTime * ((s + 1.0) * currentTime - s) + begin;
}

float TweenCalculatorBackEaseOut(float currentTime, float begin, float end, float totalTime) {
	float s = 1.70158;
	return end * ((currentTime = currentTime / totalTime - 1.0) * currentTime * ((s + 1.0) * currentTime + s) + 1.0) + begin;
}

float TweenCalculatorBackEaseInOut(float currentTime, float begin, float end, float totalTime) {
	float s = 1.70158;
	if((currentTime /= totalTime * 0.5) < 1.0) {
		return end * 0.5 * (currentTime * currentTime * (((s *= 1.525) + 1.0) * currentTime - s)) + begin;
	}
	float postFix = currentTime -= 2.0;
	return end * 0.5 * (postFix * currentTime * (((s *= 1.525) + 1.0) * currentTime + s) + 2.0) + begin;
}

bool TweenManagerStart(TweenManager* manager) {
	manager->tween = ArrayInit();

	return true;
}

bool TweenManagerShutdown(TweenManager* manager) {
	while(manager->tween->length) {
		ArrayPopObjectAtIndex(manager->tween, 0);
	}
	
	ArrayFree(&manager->tween);
	
	return true;
}

bool TweenManagerAddTween(TweenManager* manager, Tween* tween) {
	ArrayPushObject(manager->tween, tween);
	return true;
}

bool TweenManagerRemoveTween(TweenManager* manager, Tween* tween) {
	ArrayPopObject(manager->tween, tween);
	return true;
}

bool TweenManagerStep(TweenManager* manager, signed short frame) {
	int i = 0;
	for(i = 0; i < manager->tween->length; i++) {
		Tween* tween = ArrayObjectAtIndex(manager->tween, i);
		if(tween->isPlay) {
			TweenStep(tween, frame);
		}
	}
	
	return true;
}

bool TweenInit(Tween* tween, unsigned short transitionFrame, unsigned short delayFrame, TweenTrasitionType transition, TweenEquationType equation) {
	return TweenInitCustomCalculator(tween, transitionFrame, delayFrame, TweenGetCalculator(transition, equation));
}

bool TweenInitCustomCalculator(Tween* tween, unsigned short transitionFrame, unsigned short delayFrame, TweenCalculator tweenCalculator) {
	tween->property = ArrayInit();

	tween->transitionFrame = transitionFrame;
	tween->delayFrame = delayFrame;
	tween->totalFrame = transitionFrame + delayFrame;
	tween->currentFrame = 0;
	
	tween->tweenCalculator = tweenCalculator;
	
	tween->completeEvent.event = NULL;
	tween->completeEvent.userReference = NULL;
	tween->stepEvent.event = NULL;
	tween->stepEvent.userReference = NULL;
	tween->playEvent.event = NULL;
	tween->playEvent.userReference = NULL;
	tween->stopEvent.event = NULL;
	tween->stopEvent.userReference = NULL;
	
	tween->isPlay = false;
	
	return true;
}

bool TweenFree(Tween* tween) {
	while(tween->property->length) {
		TweenProperty* property = ArrayPopObjectAtIndex(tween->property, 0);
		free(property);
	}
	
	ArrayFree(&tween->property);
	free(tween->property);
	
	return true;
}

TweenCalculator TweenGetCalculator(TweenTrasitionType transition, TweenEquationType equation) {
	switch(transition) {
		case TweenTrasitionTypeSine:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorSineEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorSineEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorSineEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeQuint:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorQuintEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorQuintEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorQuintEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeQuart:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorQuartEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorQuartEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorQuartEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeQuad:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorQuadEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorQuadEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorQuadEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeExpo:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorExpoEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorExpoEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorExpoEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeElastic:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorElasticEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorElasticEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorElasticEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeCubic:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorCubicEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorCubicEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorCubicEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeCircle:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorCircleEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorCircleEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorCircleEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeBounce:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorBounceEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorBounceEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorBounceEaseInOut;
					break;
			}
			break;
		case TweenTrasitionTypeBack:
			switch(equation) {
				case TweenEquationTypeEaseIn:
					return TweenCalculatorBackEaseIn;
					break;
				case TweenEquationTypeEaseOut:
					return TweenCalculatorBackEaseOut;
					break;
				case TweenEquationTypeEaseInOut:
					return TweenCalculatorBackEaseInOut;
					break;
			}
			break;
	}
	return TweenCalculatorLinear;
}

bool TweenStep(Tween* tween, signed short frame) {
	if(frame > 0) {
		if(tween->currentFrame + frame < tween->totalFrame) {
			tween->currentFrame += frame;
		} else {
			tween->currentFrame = tween->totalFrame;
		}
	} else if(frame < 0) {
		if(-frame > tween->currentFrame) {
			tween->currentFrame = 0;
		} else {
			tween->currentFrame += frame;
		}
	}
	
	float time = (float)(tween->currentFrame - tween->delayFrame) / (float)(tween->totalFrame - tween->delayFrame);
	if(tween->currentFrame > tween->delayFrame) {
		int i = 0;
		for(i = 0; i < tween->property->length; i++) {
			TweenProperty* property = ArrayObjectAtIndex(tween->property, i);
			*property->property = tween->tweenCalculator(time, property->propertyBegin, property->propertyEnd - property->propertyBegin, 1.0);
		}
	}
	
	if(tween->stepEvent.event) {
		tween->stepEvent.event(tween, tween->stepEvent.userReference);
	}
	
	if(tween->currentFrame == tween->totalFrame ) {
		TweenStop(tween);
		if(tween->completeEvent.event) {
			tween->completeEvent.event(tween, tween->completeEvent.userReference);
		}
	}
	return true;
}

TweenEventComplete TweenEventCompleteInit(void (*event)(Tween* tween, void* userReference), void* userReference) {
	TweenEventComplete result;
	result.event = event;
	result.userReference = userReference;
	return result;
}

TweenEventStep TweenEventStepInit(void (*event)(Tween* tween, void* userReference), void* userReference) {
	TweenEventStep result;
	result.event = event;
	result.userReference = userReference;
	return result;
}

TweenEventPlay TweenEventPlayInit(void (*event)(Tween* tween, void* userReference), void* userReference) {
	TweenEventPlay result;
	result.event = event;
	result.userReference = userReference;
	return result;
}

TweenEventStop TweenEventStopInit(void (*event)(Tween* tween, void* userReference), void* userReference) {
	TweenEventStop result;
	result.event = event;
	result.userReference = userReference;
	return result;
}

bool TweenAddEventComplete(Tween* tween, TweenEventComplete completeEvent) {
	tween->completeEvent = completeEvent;
	return true;
}

bool TweenAddEventStep(Tween* tween, TweenEventStep stepEvent) {
	tween->stepEvent = stepEvent;
	return true;
}

bool TweenAddEventPlay(Tween* tween, TweenEventPlay playEvent) {
	tween->playEvent = playEvent;
	return true;
}

bool TweenAddEventStop(Tween* tween, TweenEventStop stopEvent) {
	tween->stopEvent = stopEvent;
	return true;
}

bool TweenRemoveEventComplete(Tween* tween) {
	tween->completeEvent.event = NULL;
	tween->completeEvent.userReference = NULL;
	return true;
}

bool TweenRemoveEventStep(Tween* tween) {
	tween->stepEvent.event = NULL;
	tween->stepEvent.userReference = NULL;
	return true;
}

bool TweenRemoveEventPlay(Tween* tween) {
	tween->playEvent.event = NULL;
	tween->playEvent.userReference = NULL;
	return true;
}

bool TweenRemoveEventStop(Tween* tween) {
	tween->stopEvent.event = NULL;
	tween->stopEvent.userReference = NULL;
	return true;
}

TweenProperty TweenPropertyInit(float* property, float propertyBegin, float propertyEnd) {
	TweenProperty result;
	result.property = property;
	result.propertyBegin = propertyBegin;
	result.propertyEnd = propertyEnd;
	return result;
}

TweenProperty* TweenAddProperty(Tween* tween, TweenProperty property) {
	TweenProperty* tweenProperty = malloc(sizeof(TweenProperty));
	*tweenProperty = property;
	ArrayPushObject(tween->property, tweenProperty);
	return tweenProperty;
}

bool TweenRemoveProperty(Tween* tween, TweenProperty* property) {
	TweenProperty* tweenProperty = ArrayPopObject(tween->property, property);
	free(tweenProperty);
	return true;
}

bool TweenPlay(Tween* tween) {
	tween->isPlay = true;
	if(tween->playEvent.event) {
		tween->playEvent.event(tween, tween->playEvent.userReference);
	}
	return true;
}

bool TweenStop(Tween* tween) {
	tween->isPlay = false;
	if(tween->stopEvent.event) {
		tween->stopEvent.event(tween, tween->stopEvent.userReference);
	}
	return true;
}

bool TweenGoToAndPlay(Tween* tween, unsigned long frame) {
	tween->currentFrame = frame;
	TweenStep(tween, 0);
	tween->isPlay = true;
	if(tween->playEvent.event) {
		tween->playEvent.event(tween, tween->playEvent.userReference);
	}
	return true;
}

bool TweenGoToAndStop(Tween* tween, unsigned long frame) {
	tween->currentFrame = frame;
	TweenStep(tween, 0);
	tween->isPlay = false;
	if(tween->stopEvent.event) {
		tween->stopEvent.event(tween, tween->stopEvent.userReference);
	}
	return true;
}

unsigned short TweenGetTotalFrame(Tween* tween) {
	return tween->totalFrame;
}

unsigned short TweenGetCurrentFrame(Tween* tween) {
	return tween->currentFrame;
}
