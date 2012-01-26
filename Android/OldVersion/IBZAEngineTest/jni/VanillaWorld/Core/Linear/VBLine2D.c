#include "VBLine2D.h"
#include "../../VBEngine.h"

VBLine2D VBLine2DCreate(VBFloat _beginX, VBFloat _beginY, VBFloat _endX, VBFloat _endY) {
    VBLine2D _line;
    _line.begin = VBVector2DCreate(_beginX, _beginY);
    _line.end = VBVector2DCreate(_endX, _endY);
    return _line;
}

VBLine2D VBLine2DCreateV(VBVector2D _begin, VBVector2D _end) {
    VBLine2D _line;
    _line.begin = _begin;
    _line.end = _end;
    return _line;
}

VBVector2D VBLine2DGetVector2D(VBLine2D _line, VBFloat _t) {
    //A+(B-A)t
    return VBVector2DAdd(_line.begin, VBVector2DMultiply(VBVector2DSubtract(_line.end, _line.begin), _t));
}

VBBool VBLine2DGetCollisionVectorByLine(VBLine2D _line1, VBLine2D _line2, VBVector2D* _col_vec) {
    //A+(B-A)t = C+(D-C)s 의 s에 대한 정리
    VBVector2D _A = _line1.begin;
    VBVector2D _B = _line1.end;
    VBVector2D _C = _line2.begin;
    VBVector2D _D = _line2.end;
    //(A+(B-A)t-C)/(D-C) = s 이므로
    //(Ax+(Bx-Ax)t-Cx)/(Dx-Cx) = (Ay+(By-Ay)t-Cy)/(Dy-Cy) 이다.
    //D-C가 a라고 하였을때, 우변을 좌변으로 이항하면
    VBVector2D _a = VBVector2DSubtract(_D, _C);
    //ayAx+ayBxt-ayAxt-ayCx-axAy-axByt+axAyt+axCy=0 이고 이를 t에 대한 일차방정식으로 정리하면,
    //(ayBx-ayAx-axBy+axAy)t+(ayAx-ayCx-axAy+axCy)=0 이다,
    VBFloat _ayAx = _a.y * _A.x;
    VBFloat _axAy = _a.x * _A.y;
    VBFloat _ayBx = _a.y * _B.x;
    VBFloat _axBy = _a.x * _B.y;
    VBFloat _ayCx = _a.y * _C.x;
    VBFloat _axCy = _a.x * _C.y;
    
    //(ayBx-ayAx-axBy+axAy)t+(ayAx-ayCx-axAy+axCy)=0을 et + f = 0으로 변환하고
    //et + f = 0에 대해서 -f / e = t 로 t를 구할수 있다(접점t)
    //이때 e가 0이면 t을 구할수 없으므로 충돌하지 않는다.
    VBFloat _e = _ayBx - _ayAx - _axBy + _axAy;
    if(_e == 0.0f)
        return VBFalse;
    VBFloat _f = _ayAx - _ayCx - _axAy + _axCy;
    
    VBFloat _t = -_f / _e;
    
    //t는 0.0~1.0이므로 t가 0.0보다 작고 1.0보다 크면 A+(B-A)t에서 벗어나므로 충돌하지 않는다.
    if(_t > 1.0f)
        return VBFalse;
    if(_t < 0.0f)
        return VBFalse;
    
    //(Ax+(Bx-Ax)t-Cx)/(Dx-Cx) = s이므로, s도 구할수 있다.
    //0으로 나눌수 없으므로 Dx-Cx가 0이면 (Ay+(By-Ay)t-Cy)/(Dy-Cy)로 s를 구한다.
    //Dx-Cx와 Dy-Cy가 모두 0일때는 s를 구할수 없으므로 충돌하지 않는다.
    VBFloat _s;
    if(_a.x != 0.0f)
        _s = (_A.x + (_B.x - _A.x) * _t - _C.x) / _a.x;
    else if(_a.y != 0.0f)
        _s = (_A.y + (_B.y - _A.y) * _t - _C.y) / _a.y;
    else
        return VBFalse;
    
    //s는 0.0~1.0이므로 s가 0.0보다 작고 1.0보다 크면 C+(D-C)s에서 벗어나므로 충돌하지 않는다.
    if(_s > 1.0f)
        return VBFalse;
    if(_s < 0.0f)
        return VBFalse;
    
    *_col_vec = VBLine2DGetVector2D(_line1, _t);
    
    return VBTrue;
}