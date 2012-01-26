#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "VBEasing.h"

VBFloat VBEasingCalculatorLinear(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * _currentTime / _totalTime + _begin;
}

VBFloat VBEasingCalculatorSineEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return -_end * cosf(_currentTime / _totalTime * (M_PI * 0.5)) + _end + _begin;
}

VBFloat VBEasingCalculatorSineEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * sinf(_currentTime / _totalTime * (M_PI * 0.5)) + _begin;
}

VBFloat VBEasingCalculatorSineEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return -_end * 0.5 * (cosf(M_PI * _currentTime / _totalTime) - 1.0) + _begin;
}

VBFloat VBEasingCalculatorSineEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime  < _totalTime * 0.5) {
		return VBEasingCalculatorSineEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorSineEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorQuintEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * (_currentTime /= _totalTime) * _currentTime * _currentTime * _currentTime * _currentTime + _begin;
}

VBFloat VBEasingCalculatorQuintEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * ((_currentTime = _currentTime / _totalTime - 1.0) * _currentTime * _currentTime * _currentTime * _currentTime + 1.0) + _begin;
}

VBFloat VBEasingCalculatorQuintEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return _end / 2.0 * _currentTime * _currentTime * _currentTime * _currentTime * _currentTime + _begin; 
	}
	return _end / 2.0 * ((_currentTime -= 2.0) * _currentTime * _currentTime * _currentTime * _currentTime + 2.0) + _begin;
}

VBFloat VBEasingCalculatorQuintEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorQuintEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorQuintEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorQuartEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * (_currentTime /= _totalTime) * _currentTime * _currentTime * _currentTime + _begin;
}

VBFloat VBEasingCalculatorQuartEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return -_end * ((_currentTime = _currentTime / _totalTime - 1.0) * _currentTime * _currentTime * _currentTime - 1.0) + _begin;
}

VBFloat VBEasingCalculatorQuartEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return _end * 0.5 * _currentTime * _currentTime * _currentTime * _currentTime + _begin;
	}
	return -_end * 0.5 * ((_currentTime -= 2.0) * _currentTime * _currentTime * _currentTime - 2) + _begin;
}

VBFloat VBEasingCalculatorQuartEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorQuartEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorQuartEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorQuadEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * (_currentTime /= _totalTime) * _currentTime + _begin;
}

VBFloat VBEasingCalculatorQuadEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return -_end * (_currentTime /= _totalTime) * (_currentTime - 2.0) + _begin;
}

VBFloat VBEasingCalculatorQuadEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {	
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return _end * 0.5 * _currentTime * _currentTime + _begin;
	}
	return -_end * 0.5 * ((--_currentTime) * (_currentTime - 2.0) - 1.0) + _begin;
}

VBFloat VBEasingCalculatorQuadEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorQuadEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorQuadEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorExpoEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return (_currentTime == 0.0) ? _begin : _end * powf(2.0, 10.0 * (_currentTime / _totalTime -1.0)) + _begin - _end * 0.001;
}

VBFloat VBEasingCalculatorExpoEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return (_currentTime == _totalTime) ? _begin + _end : _end * 1.001 * (-powf(2.0, -10.0 * _currentTime / _totalTime) + 1.0) + _begin;
}
 
VBFloat VBEasingCalculatorExpoEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime == 0) {
		return _begin;
	}
	if (_currentTime == _totalTime) {
		return _begin + _end;
	}
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return _end * 0.5 * powf(2.0, 10.0 * (_currentTime - 1.0)) + _begin - _end * 0.0005;
	}
	return _end * 0.5 * 1.0005 * (-powf(2.0, -10.0 * --_currentTime) + 2.0) + _begin;
}

VBFloat VBEasingCalculatorExpoEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorExpoEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorExpoEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorElasticEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime == 0.0) {
		return _begin;
	}
	if ((_currentTime /= _totalTime) == 1.0) {
		return _begin + _end;
	}
	VBFloat _p = _totalTime * 0.3;
	VBFloat _s = _p * 0.25;
	VBFloat _a = _end;
	VBFloat _postFix = _a * powf(2.0, 10.0 * (_currentTime -= 1.0));
	return -(_postFix * sinf((_currentTime * _totalTime - _s) * (2.0 * M_PI) / _p)) + _begin;
}

VBFloat VBEasingCalculatorElasticEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime == 0) {
		return _begin;
	}
	if ((_currentTime /= _totalTime) == 1.0) {
		return _begin + _end;
	}
	VBFloat _p = _totalTime * 0.3;
	VBFloat _s = _p * 0.25;
	VBFloat _a = _end;
	VBFloat _postFix = _a * powf(2.0, -10.0 * _currentTime);
	return  _postFix * sinf((_currentTime * _totalTime - _s) * (2.0 * M_PI) / _p) + _end + _begin;
}
VBFloat VBEasingCalculatorElasticEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime == 0.0) {
		return _begin;
	}
	if ((_currentTime /= _totalTime * 0.5) == 2.0) {
		return _begin + _end;
	}
	
	VBFloat _p = _totalTime * (0.3 * 1.5);
	VBFloat _s = _p * 0.25;
	VBFloat _a = _end;
	
	if (_currentTime < 1.0) {
		VBFloat _postFix = _a * powf(2.0, 10.0 * (_currentTime -= 1.0));
		return -0.5 * (_postFix * sinf((_currentTime * _totalTime - _s) * (2.0 * M_PI) / _p)) + _begin;
	}
	VBFloat _postFix = _a * powf(2.0, -10.0 * (_currentTime -= 1.0));
	return _postFix * sinf((_currentTime * _totalTime - _s) * (2.0 * M_PI) / _p) * 0.5 * _end + _begin;
}
VBFloat VBEasingCalculatorElasticEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorElasticEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorElasticEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorCubicEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * (_currentTime /= _totalTime) * _currentTime * _currentTime + _begin;
}

VBFloat VBEasingCalculatorCubicEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * ((_currentTime = _currentTime / _totalTime - 1.0) * _currentTime * _currentTime + 1.0) + _begin;
}

VBFloat VBEasingCalculatorCubicEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return _end * 0.5 * _currentTime * _currentTime * _currentTime + _begin;
	}
		return _end * 0.5 * ((_currentTime -= 2.0) * _currentTime * _currentTime + 2.0) + _begin;
}

VBFloat VBEasingCalculatorCubicEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorCubicEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorCubicEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorCircleEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return -_end * (sqrt(1.0 - (_currentTime /= _totalTime) * _currentTime) - 1) + _begin;
}

VBFloat VBEasingCalculatorCircleEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end * sqrt(1.0 - (_currentTime = _currentTime / _totalTime - 1.0) * _currentTime) + _begin;
}

VBFloat VBEasingCalculatorCircleEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return -_end * 0.5 * (sqrt(1.0 - _currentTime * _currentTime) - 1.0) + _begin;
	}
	return _end * 0.5 * (sqrt(1.0 - (_currentTime -= 2.0) * _currentTime) + 1.0) + _begin;
}

VBFloat VBEasingCalculatorCircleEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorCircleEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorCircleEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorBounceEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	return _end - VBEasingCalculatorBounceEaseOut(_totalTime - _currentTime, 0.0, _end, _totalTime);
}

VBFloat VBEasingCalculatorBounceEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if ((_currentTime /= _totalTime) < (1.0 / 2.75)) {
		return _end * (7.5625 * _currentTime * _currentTime) + _begin;
	} else if (_currentTime < (2.0 / 2.75)) {
		return _end * (7.5625 * (_currentTime -= (1.5 / 2.75)) * _currentTime + 0.75) + _begin;
	} else if (_currentTime < (2.5 / 2.75)) {
		return _end * (7.5625 * (_currentTime -= (2.25 / 2.75)) * _currentTime + 0.9375) + _begin;
	} else {
		return _end * (7.5625 * (_currentTime -= (2.625 / 2.75)) * _currentTime + 0.984375) + _begin;
	}
}

VBFloat VBEasingCalculatorBounceEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorBounceEaseIn(_currentTime * 2.0, 0.0, _end, _totalTime);
	} else {
		return VBEasingCalculatorBounceEaseOut(_currentTime * 2.0 - _totalTime, 0.0, _end, _totalTime) * 0.5 + _end * 0.5 + _begin;
	}
}

VBFloat VBEasingCalculatorBounceEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorBounceEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorBounceEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBFloat VBEasingCalculatorBackEaseIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	VBFloat _s = 1.70158;
	return _end * (_currentTime /= _totalTime) * _currentTime * ((_s + 1.0) * _currentTime - _s) + _begin;
}

VBFloat VBEasingCalculatorBackEaseOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	VBFloat _s = 1.70158;
	return _end * ((_currentTime = _currentTime / _totalTime - 1.0) * _currentTime * ((_s + 1.0) * _currentTime + _s) + 1.0) + _begin;
}

VBFloat VBEasingCalculatorBackEaseInOut(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	VBFloat _s = 1.70158;
	if ((_currentTime /= _totalTime * 0.5) < 1.0) {
		return _end / 2.0 * (_currentTime * _currentTime *(((_s *= (1.525)) + 1.0) * _currentTime - _s)) + _begin;
	}
	return _end / 2.0 * ((_currentTime -= 2.0) * _currentTime * (((_s *=(1.525)) + 1.0) * _currentTime + _s) + 2.0) + _begin;
}

VBFloat VBEasingCalculatorBackEaseOutIn(VBFloat _currentTime, VBFloat _begin, VBFloat _end, VBFloat _totalTime) {
	if (_currentTime < _totalTime * 0.5) {
		return VBEasingCalculatorBackEaseOut(_currentTime * 2.0, _begin, _end * 0.5, _totalTime);
	}
	return VBEasingCalculatorBackEaseIn((_currentTime * 2.0) - _totalTime, _begin + _end * 0.5, _end * 0.5, _totalTime);
}

VBEasingCalculator VBEasingGetCalculator(VBEasingType _type, VBEasingEquationType _equation) {
	switch (_type) {
		case VBEasingType_Sine:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorSineEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorSineEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorSineEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorSineEaseOutIn;
			}
			break;
		case VBEasingType_Quint:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorQuintEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorQuintEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorQuintEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorQuintEaseOutIn;
			}
			break;
		case VBEasingType_Quart:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorQuartEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorQuartEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorQuartEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorQuartEaseOutIn;
			}
			break;
		case VBEasingType_Quad:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorQuadEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorQuadEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorQuadEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorQuadEaseOutIn;
			}
			break;
		case VBEasingType_Expo:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorExpoEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorExpoEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorExpoEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorExpoEaseOutIn;
			}
			break;
		case VBEasingType_Elastic:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorElasticEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorElasticEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorElasticEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorElasticEaseOutIn;
			}
			break;
		case VBEasingType_Cubic:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorCubicEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorCubicEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorCubicEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorCubicEaseOutIn;
			}
			break;
		case VBEasingType_Circle:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorCircleEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorCircleEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorCircleEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorCircleEaseOutIn;
			}
			break;
		case VBEasingType_Bounce:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorBounceEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorBounceEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorBounceEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorBounceEaseOutIn;
			}
			break;
		case VBEasingType_Back:
			switch (_equation) {
				case VBEasingEquationType_EaseIn:
					return VBEasingCalculatorBackEaseIn;
				case VBEasingEquationType_EaseOut:
					return VBEasingCalculatorBackEaseOut;
				case VBEasingEquationType_EaseInOut:
					return VBEasingCalculatorBackEaseInOut;
				case VBEasingEquationType_EaseOutIn:
					return VBEasingCalculatorBackEaseOutIn;
			}
			break;
	}
	return VBEasingCalculatorLinear;
}