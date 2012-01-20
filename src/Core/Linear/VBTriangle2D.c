#include "VBTriangle2D.h"

VBTriangle2D VBTriangle2DCreate(VBFloat _ax, VBFloat _ay, VBFloat _bx, VBFloat _by, VBFloat _cx, VBFloat _cy) {
    VBTriangle2D _tri;
    _tri.a = VBVector2DCreate(_ax, _ay);
    _tri.b = VBVector2DCreate(_bx, _by);
    _tri.c = VBVector2DCreate(_cx, _cy);
    return _tri;
}

VBTriangle2D VBTriangle2DCreateV(VBVector2D _a, VBVector2D _b, VBVector2D _c) {
    VBTriangle2D _tri;
    _tri.a = _a;
    _tri.b = _b;
    _tri.c = _c;
    return _tri;
}

VBBool VBTriangle2DGetCollisionByVector(VBTriangle2D _tri, VBVector2D _vec) {
    //삼각형의 각꼭지점을 ABC라하고 테스트할 점을 V라고 했을때,
    VBVector2D _A = _tri.a;
    VBVector2D _B = _tri.b;
    VBVector2D _C = _tri.c;
    VBVector2D _V = _vec;
    
    //삼각형의 꼭지점의 벡터는 (B-A) = Ab, (C-B) = Bc, (A-C) = Ca이다.
    VBVector2D _Ab = VBVector2DSubtract(_B, _A);
    VBVector2D _Bc = VBVector2DSubtract(_C, _B);
    VBVector2D _Ca = VBVector2DSubtract(_A, _C);
    
    //v에 대한 선분을 각꼭지점의 선분을 AV, BV, CV라고 했을때,
    //v에 대한 선분 삼각형의 꼭지점 벡터는 (V-A) = Av, (V-B) = Bv, (V-C) = Cv이다.
    VBVector2D _Av = VBVector2DSubtract(_V, _A);
    VBVector2D _Bv = VBVector2DSubtract(_V, _B);
    VBVector2D _Cv = VBVector2DSubtract(_V, _C);
    
    //3차원 평면면 xyz에서의 두개의벡터 Ab,Av에 대한 외적 AbAv (AbyAvz - AvyAbz , AbzAvx - AvzAbx , AbxAvy - AvxAby) 에 대해서
    //z축을 0으로 놓았을때 (0, 0 , AbxAvy - AvxAby)이므로
    //z인 AbxAvy - AvxAby가 0보다 작으면 오른손 좌표에서 벡터 Ab가 점 Av에 비해 반시계방향 쪽으로 위치하고 0보다 크면 시계방향 쪽으로 위치해 있다.
    //그러므로 2차원 평면에서의 벡터Av에 대한 벡터Ab의 방향은 AbxAvy - AvxAby가 0보다 크면 시계방향,작으면 반시계방향이다.
    VBFloat _AbAvZ = _Ab.x * _Av.y - _Av.x * _Ab.y;
    VBBool _orient = _AbAvZ < 0.0f;
    
    //삼각형과 점의 성질중 삼각형 각선분AB, BC, CA 에대해 점V가 같은방향에 위치하면 삼각형 내부에 위치하므로,
    //이러한 성질을 이용하여 벡터 Ab, Bc, Ca에 대한 벡터 Av, Bv, Cv가 모두 같은 방향에 위치하면 점V는 삼각형ABC안에 위치한다.
    VBFloat _BcBvZ = _Bc.x * _Bv.y - _Bv.x * _Bc.y;
    if(_orient != _BcBvZ < 0.0f)
        return VBFalse;
    
    VBFloat _CaCvZ = _Ca.x * _Cv.y - _Cv.x * _Ca.y;
    if(_orient != _CaCvZ < 0.0f)
        return VBFalse;
    
    return VBTrue;
}