#ifndef __POLYGON_H__
#define __POLYGON_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
	typedef struct Polygon3D Polygon3D;
	struct Polygon3D {
		unsigned short a;
		unsigned short b;
		unsigned short c; 
	};
	
	Polygon3D Polygon3DInit(unsigned short a, unsigned short b, unsigned short c);

#ifdef __cplusplus
}
#endif

#endif