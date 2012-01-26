#include "VBGraphic2D.h"
#include "../VBEngine.h"
#include "../VBConfig.h"
#include "../Core/Spline/VBSpline2D.h"
#include <math.h>

VBGraphic2D* VBGraphic2DAlloc(void) {
	VBGraphic2D* _grap = VBSystemCalloc(1, sizeof(VBGraphic2D));
	
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DAlloc() - 메모리 할당에 실패하였습니다.");
#endif
	
	_grap->line_drawable = VBDrawable2DAlloc();
	_grap->fill_drawable = VBDrawable2DAlloc();
	
	return _grap;
}

VBGraphic2D* VBGraphic2DInit(VBGraphic2D* _grap) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DInit() - VBNull인 Graphic요소는 초기화 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->line_drawable = VBDrawable2DInitWithTexture(_grap->line_drawable, VBDrawable2DType_TriangleStrip, VBEngineGetGraphic2DLineTexture());
	
	_grap->fill_drawable = VBDrawable2DInitWithTexture(_grap->fill_drawable, VBDrawable2DType_TriangleFan, VBEngineGetGraphic2DLineTexture());
	
	_grap->line_width = 1.0;
	_grap->line_color = VBColorRGBACreate(0xFF, 0xFF, 0xFF, 0xFF);
	
	_grap->is_fill = VBFalse;
	_grap->fill_color = VBColorRGBACreate(0xFF, 0xFF, 0xFF, 0xFF);
	
	_grap->last_position = VBVector2DCreate(0.0, 0.0);
	
	return _grap;
}

void VBGraphic2DFree(VBGraphic2D** _grap) {
#ifdef _VB_DEBUG_
	if(*_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DFree() - VBNull인 Graphic요소는 해제 할수 없습니다. VBGraphic2DAlloc하지 않았거나 이미 VBGraphic2DFree했을 수 있습니다.");
#endif
	
	VBDrawable2DFree(&(*_grap)->fill_drawable);
	VBDrawable2DFree(&(*_grap)->line_drawable);
	VBSystemFree(*_grap);
	*_grap = VBNull;
}

void VBGraphic2DClear(VBGraphic2D* _grap) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DClear() - VBNull인 Graphic요소는 Clear 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap = VBGraphic2DInit(_grap);
}

void VBGraphic2DMoveTo(VBGraphic2D* _grap, VBFloat _x, VBFloat _y) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DMoveTo() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->last_position = VBVector2DCreate(_x, _y);
}

void VBGraphic2DLineTo(VBGraphic2D* _grap, VBFloat _x, VBFloat _y) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DLineTo() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	VBColorRGBA _color[8] = {
		_grap->line_color, _grap->line_color, _grap->line_color, _grap->line_color,
		_grap->line_color, _grap->line_color, _grap->line_color, _grap->line_color
	};
	
	VBFloat _angle = VBVector2DAngle(VBVector2DSubtract(VBVector2DCreate(_x, _y), _grap->last_position));
	
	VBFloat _half = _grap->line_width * 0.5;
	
	VBFloat _sinx = sinf(_angle) * _half;
	VBFloat _cosy = cosf(_angle) * _half;
	
	VBFloat _a = _sinx + _cosy;
	VBFloat _b = _sinx -_cosy;
	VBFloat _c = _cosy - _sinx;
	
	VBVector2D _vtx[8] = {
		{_grap->last_position.x - _a, _grap->last_position.y + _c},
		{_grap->last_position.x + _b, _grap->last_position.y - _a},
		{_grap->last_position.x - _sinx, _grap->last_position.y + _cosy},
		{_grap->last_position.x + _sinx, _grap->last_position.y - _cosy},
		{_x -_sinx, _y + _cosy},
		{_x + _sinx, _y - _cosy},
		{_x + _c, _y + _a},
		{_x + _a, _y + _b},
	};
	
	VBVector2D _txc[8] = {
		{0.0, 1.0}, {0.0, 0.0}, {0.25, 1.0}, {0.25, 0.0},
		{0.75, 1.0}, {0.75, 0.0}, {1.0, 1.0}, {1.0, 0.0}
	};
	
	VBUShort _idx[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	
	_grap->last_position = VBVector2DCreate(_x, _y);
	
	if(_grap->line_drawable->vtx) {
		VBDrawable2D* _line = VBDrawable2DInitWithData(VBDrawable2DAlloc(), 
													   VBDrawable2DType_TriangleStrip, 
													   VBEngineGetGraphic2DLineTexture(), 
													   8, _color, _vtx, _txc, 8, _idx);
		
		VBDrawable2DAppend(_grap->line_drawable, _line);
		
		VBDrawable2DFree(&_line);
	} else {
		_grap->line_drawable = VBDrawable2DInitWithData(_grap->line_drawable, 
													    VBDrawable2DType_TriangleStrip, 
													    VBEngineGetGraphic2DLineTexture(), 
													    8, _color, _vtx, _txc, 8, _idx);
	}
}

void VBGraphic2DQuadBezierCurveTo(VBGraphic2D* _grap, VBFloat _ctrX, VBFloat _ctrY, VBFloat _x, VBFloat _y, VBULong _detail) {
    VBSpline2DBezierQuadratic* _quad = VBSpline2DBezierQuadraticInitWithVector(VBSpline2DBezierQuadraticAlloc(), _grap->last_position, VBVector2DCreate(_ctrX, _ctrY), VBVector2DCreate(_x, _y));
    VBULong _i;
    for(_i = 1; _i <= _detail; _i++) {
        VBVector2D _p = VBSpline2DBezierQuadraticGetVector2D(_quad, (VBFloat)_i / _detail);
        VBGraphic2DLineTo(_grap, _p.x, _p.y);
    }
	_grap->last_position = VBVector2DCreate(_x, _y);
}

void VBGraphic2DCubicBezierCurveTo(VBGraphic2D* _grap, VBFloat _ctrX1, VBFloat _ctrY1, VBFloat _ctrX2, VBFloat _ctrY2, VBFloat _x, VBFloat _y, VBULong _detail) {
    VBSpline2DBezierCubic* _cubic = VBSpline2DBezierCubicInitWithVector(VBSpline2DBezierCubicAlloc(), _grap->last_position, VBVector2DCreate(_ctrX1, _ctrY1), VBVector2DCreate(_ctrX2, _ctrY2), VBVector2DCreate(_x, _y));
    VBULong _i;
    for(_i = 1; _i <= _detail; _i++) {
        VBVector2D _p = VBSpline2DBezierCubicGetVector2D(_cubic, (VBFloat)_i / _detail);
        VBGraphic2DLineTo(_grap, _p.x, _p.y);
    }
	_grap->last_position = VBVector2DCreate(_x, _y);
}

void VBGraphic2DSetLineColor(VBGraphic2D* _grap, VBColorRGBA _color) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DSetLineColor() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->line_color = _color;
}

void VBGraphic2DSetLineWidth(VBGraphic2D* _grap, VBFloat _width) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DSetLineWidth() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->line_width = _width;
}

void VBGraphic2DBeginFill(VBGraphic2D* _grap) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DBeginFill() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	if(!_grap->is_fill)
		_grap->is_fill = VBTrue;
}

void VBGraphic2DEndFill(VBGraphic2D* _grap) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DEndFill() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	if(_grap->is_fill)
		_grap->is_fill = VBFalse;
}

void VBGraphic2DSetFillColor(VBGraphic2D* _grap, VBColorRGBA _color) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DSetFillColor() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->fill_color = _color;
}

void VBGraphic2DDrawCircle(VBGraphic2D* _grap, VBFloat _x, VBFloat _y, VBFloat _radius) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DDrawCircle() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->last_position = VBVector2DCreate(_x, _y);
}

void VBGraphic2DDrawEllepse(VBGraphic2D* _grap, VBFloat _x, VBFloat _y, VBFloat _width, VBFloat _height) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DDrawEllepse() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->last_position = VBVector2DCreate(_x, _y);
}

void VBGraphic2DDrawRect(VBGraphic2D* _grap, VBFloat _x, VBFloat _y, VBFloat _width, VBFloat _height) {
#ifdef _VB_DEBUG_
	if(_grap == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBGraphic2DDrawRect() - VBNull인 Graphic요소는 사용 할수 없습니다. VBGraphic2DAlloc하지 않았을 수 있습니다.");
#endif
	
	_grap->last_position = VBVector2DCreate(_x, _y);
}
