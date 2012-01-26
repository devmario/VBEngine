#include "Plane.h"

Plane PlaneInit(float a, float b, float c, float d) {
	Plane plane;
	plane.a = a;
	plane.b = b;
	plane.c = c;
	plane.d = d;
	return plane;
}