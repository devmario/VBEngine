#ifndef __VBEngineFileInfo_H__
#define __VBEngineFileInfo_H__


#include "Core/VBArrayVector.h"
#include "VBType.h"
#include "Core/VBString.h"


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