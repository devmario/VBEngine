#ifndef __VBFlashPlugIn_H__
#define __VBFlashPlugIn_H__

#include "mm_jsapi.h"

//VBFlashPlugIn.StartMakeObjectFile(생성할 오브젝트 파일패스, 이미지 파일패스들, UV 파일패스들)
JSBool StartMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

//VBFlashPlugIn.EndMakeObjectFile()
JSBool EndMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

//VBFlashPlugIn.WriteObject(라이브러리 Object들)
JSBool WriteObject(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

//VBFlashPlugIn.WriteDynamic(라이브러리 다이나믹들)
JSBool WriteDynamic(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

#endif