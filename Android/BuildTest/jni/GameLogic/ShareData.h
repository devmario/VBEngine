#ifndef gelatomania_ShareData_h
#define gelatomania_ShareData_h

#include "VBEngine.h"
#include "VBModel.h"
#include "Root.h"
#include "cJSON.h"

#define GAME_FRAME 60.0

#ifdef __ANDROID__
/* access function */
#define	F_OK		0	/* test for existence of file */
#define	X_OK		0x01	/* test for execute or search permission */
#define	W_OK		0x02	/* test for write permission */
#define	R_OK		0x04	/* test for read permission */

extern int access(const char *, int);
#endif

VBObjectFile2D* ShareDataGetTitleObjFile();
const char* ShareDataGetLoadingLibraryName();
VBTexture* ShareDataGetTitleTexture();
VBModel* ShareDataGetLoadingModel();
Root* ShareDataGetRoot();
void ShareDataFree();
cJSON* ShareDataGetJSON();
int ShareDataGetPackLength();
char* ShareDataGetPackLibraryName(int _idx);
void ShareDataSave();
bool ShateDataGetHaveStage(int _idx);
int ShareDataGetStageLengthAt(int _idx);
int ShareDataGetStageLength(int _idx);
cJSON* ShareDataGetStageDataJSONAt(int _packID, int _stageID);
bool ShareDataGetStageLockAt(int _packID, int _stageID);
int ShareDataGetStageStarAt(int _packID, int _stageID);
int ShareDataGetStageScoreAt(int _packID, int _stageID);
cJSON* ShareDataGetStageJSONAt(int _packID, int _stageID);
char* ShareDataGetPackFileName(int _idx);
void ShareDataPackDataSave();
void ShareDataPackDataSaveAt(int _idx);
VBArrayVector* ShareDataGetPackDataJSON();
cJSON* ShareDataGetPackDataJSONAt(int _idx);
VBArrayVector* ShareDataGetStageJSON();
char* ShareDataGetStageFilePathAt(int _packID, int _stageID);
cJSON* ShareDataGetRes();
int _getpid();
int _getsid();
void _setpid(int);
void _setsid(int);
cJSON* ShareDataGetInApp();
cJSON* ShareDataGetTemplate();
cJSON* ShareDataSearchJSON(cJSON* _js, int _len, ...);
cJSON* ShareDataGetTemplateData(cJSON* _idx);
int hexToInt(char* szHex);
VBAABB JStoAABB(cJSON* _js);

#define TOUCHBEGINBT(touchPtr, modelPtr, location, touch, code) \
if(touchPtr == NULL) {\
if(modelPtr->checkCollisionWithButton(location)) {\
code;\
touchPtr = touch;\
}\
}

#define TOUCHENDBT(touchPtr, modelPtr, location, touch, code, mustCode)\
if(touchPtr == touch) {\
if(modelPtr->checkCollisionWithButton(location)) {\
code;\
}\
mustCode;\
touchPtr = NULL;\
}

#ifdef _VB_ANDROID_
#define OBJLOAD(_obj, _resChar, _str)\
_str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _resChar);\
if(VBStringGetCString(_str) != NULL) {\
_obj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);\
} else {\
_obj = NULL;\
}\
VBStringFree(&_str)
#else
#define OBJLOAD(_obj, _resChar, _str)\
_str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _resChar);\
if(access(VBStringGetCString(_str), F_OK) == 0) {\
_obj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);\
} else {\
_obj = NULL;\
}\
VBStringFree(&_str)
#endif

#ifdef _VB_ANDROID_
#define TEXLOAD(_tex, _resChar, _str)\
_str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _resChar);\
if(VBStringGetCString(_str) != NULL) {\
_tex = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);\
} else {\
_tex = NULL;\
}\
VBStringFree(&_str)
#else
#define TEXLOAD(_tex, _resChar, _str)\
_str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _resChar);\
if(access(VBStringGetCString(_str), F_OK) == 0) {\
_tex = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);\
} else {\
_tex = NULL;\
}\
VBStringFree(&_str)
#endif

#define IMGLOAD(_img, _resChar, _str)\
_str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _resChar);\
_img = VBImageInitWithPath(VBImageAlloc(), _str);\
VBStringFree(&_str)

#define TEXLOADANDWRITE(_resChar, _str, _outResChar, _outStr)\
_str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _resChar);\
VBImage* _img = VBImageInitWithPath(VBImageAlloc(), _str);\
assert(_img == NULL);\
VBStringFree(&_str);\
_outStr = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _outResChar);\
FILE* _file = fopen(VBStringGetCString(_outStr), "w+");\
assert(_file == NULL);\
fwrite(VBImageGetImageData(_img), 1, VBImageGetImageDataSize(_img), _file);\
fclose(_file)

#define LIBNAMEFIND(_library_name_id, _obj, _resChar, _str)\
if(_obj) {\
_str = VBStringInitWithCString(VBStringAlloc(), _resChar);\
_library_name_id = VBObjectFile2DGetLibraryNameIDByName(_obj, _str);\
VBStringFree(&_str);\
} else {\
_library_name_id = NULL;\
}

#endif
