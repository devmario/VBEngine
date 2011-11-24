#include "Light.h"

#include <OpenGLES/ES1/gl.h>

#include <stdlib.h>

bool LightInit(Light* light, unsigned int lightNumber) {
	light->lights = ArrayInit();
	for(int i = 0; i < lightNumber; i++) {
		LightObject* object = malloc(sizeof(LightObject));
		
		object->position = malloc(sizeof(Vector4D));
		object->ambient = malloc(sizeof(Vector4D));
		object->specural = malloc(sizeof(Vector4D));
		object->diffuse = malloc(sizeof(Vector4D));
		
		object->target = GL_LIGHT0 + i;
		
		ArrayPushObject(light->lights, object);
		
		if(!LightSetDetailValue(light, i, false, 
								Vector4DInit(0.0f, 0.0f, 0.0f, 0.0f), 
								Vector4DInit(0.0f, 0.0f, 0.0f, 0.0f), 
								Vector4DInit(0.0f, 0.0f, 0.0f, 0.0f), 
								Vector4DInit(0.0f, 0.0f, 0.0f, 0.0f))) {
			LightFree(light);
			return false;
		}
		
		if(object->target > GL_LIGHT7) {
			LightFree(light);
			return false;
		}
	}
	return true;
}

bool LightFree(Light* light) {
	while(light->lights->length) {
		LightObject* object = ArrayObjectAtIndex(light->lights, 0);
		
		glDisable(object->target);
		
		free(object->position);
		free(object->ambient);
		free(object->specural);
		free(object->diffuse);
		
		free(object);
		
		ArrayPopObject(light->lights, object);
	}
	ArrayFree(&light->lights);
	return true;
}

bool LightSetDetailValue(Light* light, unsigned int index, bool isOn, Vector4D position, Vector4D ambient, Vector4D specural, Vector4D diffuse) {
	LightObject* object = ArrayObjectAtIndex(light->lights, index);
	if(object) {
		object->isOn = isOn;
		*object->position = position;
		*object->ambient = ambient;
		*object->specural = specural;
		*object->diffuse = diffuse;
		glLightfv(object->target, GL_POSITION, (float*)object->position);
		glLightfv(object->target, GL_AMBIENT, (float*)object->ambient);
		glLightfv(object->target, GL_DIFFUSE, (float*)object->diffuse);
		glLightfv(object->target, GL_SPECULAR, (float*)object->specural);
		if(object->isOn) {
			glEnable(object->target);
		} else {
			glDisable(object->target);
		}
		return true;
	} else {
		return false;
	}
}
