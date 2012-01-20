#ifndef __VBEngineFileInfo_H__
#define __VBEngineFileInfo_H__


#include "../Util/VBArrayVector.h"
#include "../Util/VBString.h"
#include "VBType.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct VBEngineFileInfo {
	VBString* path;
	VBUShort fd;
	VBSize off;
	VBSize len;
} VBEngineFileInfo;

VBEngineFileInfo* VBEngineFileInfoAlloc(void);
VBEngineFileInfo* VBEngineFileInfoInit(VBEngineFileInfo* _info, VBChar* _path, VBUShort _fd, VBSize _off, VBSize _len);
void VBEngineFileInfoAdd(VBEngineFileInfo* _info);
VBArrayVector* VBEngineFileInfoGetVector(void);
void VBEngineFileInfoFree(VBEngineFileInfo** _info);

#ifdef __cplusplus
}
#endif

#endif