#include "VBTriangle2D.h"

VBTriangle2D VBTriangle2DCreate(VBVector2D _a, VBVector2D _b, VBVector2D _c)
{
    VBTriangle2D tri;
    tri.a = _a;
    tri.b = _b;
    tri.c = _c;
    
    return tri;
}

VBBool VBTriangle2DCheckCollisionWithPoint(VBTriangle2D _tri, VBVector2D _pos)
{
    //직선의 방정식 y = mx + n
    VBBool isVert[3] = {VBFalse, };
    VBVector2D vec[3] = {_tri.a, _tri.b, _tri.c};
    float m[3] = {0, };
    float n[3] = {0, };
    VBBool direction[3] = {VBFalse, };
    int insideCount = 0;
    
    VBVector2D center;
    center.x = (_tri.a.x + _tri.b.x + _tri.c.x) / 3;
    center.y = (_tri.a.y + _tri.b.y + _tri.c.y) / 3;
    
    //직선의 방석식 구하기
	int i = 0;
    for(i; i < 3; ++i) {
        if((vec[(i+1)%3].x - vec[i].x) != 0) {
            m[i] = (vec[(i+1)%3].y - vec[i].y) / (vec[(i+1)%3].x - vec[i].x);
            n[i] = vec[i].y - (m[i] * vec[i].x);
        } else {
            isVert[i] = VBTrue;
        }
    }
    
    //변 마다 내부에 속하는지 판정
	int j = 0;
    for(j; j < 3; ++j) {
        if(((m[j] * center.x) + n[j]) >= center.y)
            direction[j] = VBTrue;
        else
            direction[j] = VBFalse;
        
        if(isVert[j] == VBTrue) {
            if((vec[j].x < _pos.x) && (vec[j].x < center.x))
                insideCount++;
            else if((vec[j].x > _pos.x) && (vec[j].x > center.x))
                insideCount++;
        } else {
            if(direction[j] == VBTrue) {
                if(_pos.y <= ((m[j] * _pos.x) + n[j]))
                    insideCount++;
            } else if(direction[j] == VBFalse) {
                if(_pos.y >= ((m[j] * _pos.x) + n[j]))
                    insideCount++;
            }
        }
    }
    
    if(insideCount == 3)
        return VBTrue;
    else
        return VBFalse;
}