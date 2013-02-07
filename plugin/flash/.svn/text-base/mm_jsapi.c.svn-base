// Source code in C 
// Save the DLL or shared library with the name "FlashCS5extension". 
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>

#include "mm_jsapi.h"
#include "FlashCS5extension.h"


/* Definitions of global variables */
MM_Environment mmEnv;

void MM_RegistExtensionFunction(const char* funcName, JSNative callBack, unsigned int nargs) {
	int i;
	int funcNameLen = strlen(funcName);
	unsigned short* funcNameWord = calloc(funcNameLen + 1, sizeof(unsigned short));
	for(i = 0; i < funcNameLen; i++) {
		funcNameWord[i] = funcName[i];
	}
	JS_DefineFunction(funcNameWord, callBack, nargs);
	//JS_DefineFunction(funcNameWord, callBack, 2);
	free(funcNameWord);
}

void MM_Init() {
    MM_RegistExtensionFunction("GetProjectPathAndFileName", GetProjectPathAndFileName, 0);
    MM_RegistExtensionFunction("CheckExistingProject", CheckExistingProject, 1);
	MM_RegistExtensionFunction("StartMakeObjectFile", StartMakeObjectFile, 4);
	MM_RegistExtensionFunction("EndMakeObjectFile", EndMakeObjectFile, 2);
	MM_RegistExtensionFunction("WriteDynamic", WriteDynamic, 1);
	MM_RegistExtensionFunction("WriteOriginInfo", WriteOriginInfo, 2);
}

void MM_InitWrapper(MM_Environment *env, unsigned int envSize) {
	char **envPtr = (char **)env; 
	char **mmPtr =(char **)(&mmEnv);
	char **envEnd = (char **)((char *)envPtr + envSize);
	char **mmEnd =(char **)((char *)mmPtr+ sizeof(MM_Environment)); 
	
	/* Copy fields from env to mmEnv, one pointer at a time */
	while (mmPtr < mmEnd && envPtr < envEnd)
		*mmPtr++ = *envPtr++; 
	
	/* If env doesn't define all of mmEnv's fields, set extras to NULL */ 
	while (mmPtr < mmEnd) 
		*mmPtr++ = (char *)0; 
	
	/* Call user's MM_Init function */
	MM_Init();
} 