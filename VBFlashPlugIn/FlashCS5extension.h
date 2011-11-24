#ifndef __FlashCS5extension_H__
#define __FlashCS5extension_H__

#include "mm_jsapi.h"

#define _TYPE_BITMAP_       0x01
#define _TYPE_GRAPHIC_      0x02
#define _TYPE_MOVIECLIP_    0x04

//FlashCS5extension.StartMakeObjectFile(생성할 오브젝트 파일패스, 이미지 파일패스들, UV 파일패스들)
JSBool StartMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

//FlashCS5extension.EndMakeObjectFile()
JSBool EndMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

//FlashCS5extension.WriteDynamic(라이브러리 다이나믹들)
JSBool WriteDynamic(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

JSBool GetProjectPathAndFileName(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

JSBool CheckExistingProject(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

JSBool WriteOriginInfo(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval);

#endif