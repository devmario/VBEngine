#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
#include "../Object/Model.h"
	
	typedef struct Keyboard Keyboard;
	typedef struct Key Key;
	
	struct Key {
		char keyCode;
		Model* model;
	};
	
	struct Keyboard {
		Array* key;
		Model* model;
	};
	
	bool KeyboardStart(void);
	bool KeyboardShutdown(void);
	
#ifdef __cplusplus
}
#endif

#endif
