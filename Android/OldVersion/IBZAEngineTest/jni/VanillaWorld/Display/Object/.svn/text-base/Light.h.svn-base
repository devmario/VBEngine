#ifndef __LIGHT_H__
#define __LIGHT_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
#include "../../Util/Array.h"
#include "../Core/Vector.h"
	
	typedef struct LightObject LightObject;
	typedef struct Light Light;
	
	struct LightObject {
		Vector4D* position;
		Vector4D* ambient;
		Vector4D* specural;
		Vector4D* diffuse;
		
		bool isOn;
		
		unsigned int target;
	};
	
	struct Light {
		Array* lights;
	};
	
	bool LightInit(Light* light, unsigned int lightNumber);
	bool LightFree(Light* light);
	
	bool LightSetDetailValue(Light* light, unsigned int index, bool isOn, Vector4D position, Vector4D ambient, Vector4D specural, Vector4D diffuse);
	
#ifdef __cplusplus
}
#endif

#endif
