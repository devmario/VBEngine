#include "FlashCS5extension.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

#include "CAPIUtil.h"

#pragma mark -
#pragma mark 유니크 아이디를 위한 네임 아이디
void writelog(char* format, ...);

//테스트

//라이브러리 네임과 ID를 매치시켜주는 스트럭쳐
typedef struct LibraryNameID LibraryNameID;
struct LibraryNameID {
	char* name;
	unsigned short id;
};


//unique ID를 위한 변수
unsigned int root_library_id = 0;
//라이브러리 아이디 갯수
unsigned int root_library_name_id_len = 0;
//라이브러리 아이디 스트럭처 포인터
LibraryNameID* root_library_name_id = NULL;

long root_w, root_h;
long root_flash_w, root_flash_h;

//문자열로 라이브러리 아이디를 리턴
unsigned int FindLybraryID(const char* name) {
	int i;
	for(i = 0; i < root_library_name_id_len; i++) {
		if(strcmp(root_library_name_id[i].name, name) == 0)
			return root_library_name_id[i].id;
	}
	return 0;
}

//라이브러리 아이디로 매치되는 해당 문자열 리턴
char* FindLibraryName(unsigned int id) {
	int i;
	for(i = 0; i < root_library_name_id_len; i++) {
		if(root_library_name_id[i].id == id) {
			return root_library_name_id[i].name;
		}
	}
	return NULL;
}

//라이브러리 아이디에 네임을 추가
unsigned int PushLibraryName(const char* name) {
	if(strlen(name) == 0)
		return 0;
	unsigned int id = FindLybraryID(name);
	if(id != 0)
		return id;
	root_library_name_id_len++;
	if(root_library_name_id == NULL) {
		root_library_name_id = (LibraryNameID*)malloc(sizeof(LibraryNameID));
	} else {
		root_library_name_id = (LibraryNameID*)realloc(root_library_name_id, sizeof(LibraryNameID) * root_library_name_id_len);
	}
	LibraryNameID* nameID = &root_library_name_id[root_library_name_id_len - 1];
	memset(nameID, 0, sizeof(LibraryNameID));
	
	nameID->name = calloc(strlen(name) + 1, sizeof(char));
	sprintf(nameID->name, "%s", name);
	writelog("++++++++++++++++ %s %i +++++++++++", nameID->name, strlen(nameID->name));
	
	nameID->id = ++root_library_id;
	return nameID->id;
}

//라이브러리 이름 변경
void ChangeLibraryName(const char* name, const char* anothername) {
    int anothername_len = strlen(anothername) + 1;
    if(anothername_len == 0)
        return;
    
    int i;
    for(i = 0; i < root_library_name_id_len; ++i) {
        if(strcmp(root_library_name_id[i].name, name) == 0) {
            root_library_name_id[i].name = realloc(root_library_name_id[i].name, anothername_len * sizeof(char));
			memset(root_library_name_id[i].name, 0x00, anothername_len * sizeof(char));
            sprintf(root_library_name_id[i].name, "%s", anothername);
			writelog("=========== %s %i ===========", root_library_name_id[i].name, strlen(root_library_name_id[i].name));
        }
    }
}

//라이브러리 아이디 삭제
void FreeLibraryName() {
	if(root_library_name_id) {
		int i;
		for(i = 0; i < root_library_name_id_len; i++) {
			free(root_library_name_id[i].name);
		}
		free(root_library_name_id);
		root_library_name_id = NULL;
		root_library_name_id_len = 0;
		root_library_id = 0;
	}
}

FILE* logfile = NULL;

void startlog();
void endlog();

void writelog(char* format, ...) {
    
    startlog();
    
    if(logfile == 0)
        return;
    
    char buffer[0xFFF];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    va_end (args);
    
    strcat(buffer, "\n");
    
    int len = strlen(buffer);
    fwrite(buffer, sizeof(char), len, logfile);
    
    endlog();
}

void startlog() {
    if(logfile) {
        fclose(logfile);
        logfile = NULL;
    }
    logfile = fopen("/VBEngine/tmp/log.txt", "a");
}

void endlog() {
    if(logfile) {
        fclose(logfile);
        logfile = NULL;
    }
}

void clearlog() {
    logfile = 0;
}


JSBool GetObject(JSContext* cx, JSObject* obj, int index, JSObject** value) {
    jsval element;
    if(JS_GetElement(cx, obj, index, &element) == JS_FALSE)
        return JS_FALSE;
    
    if(JS_ValueToObject(cx, element, value) == JS_FALSE)
        return JS_FALSE;
    
    return JS_TRUE;
}

char* GetString(JSContext* cx, JSObject* obj, int index) {
    jsval element;
    if(JS_GetElement(cx, obj, index, &element) == JS_FALSE)
        return 0;
    
    unsigned int strLen;
    unsigned short* str = JS_ValueToString(cx, element, &strLen);
    if(str == NULL)
        return 0;
    
    char* strAscii = StringToAscii(str, strLen);
    if(strAscii == NULL)
        return 0;
    
    return strAscii;
}

JSBool GetInteger(JSContext* cx, JSObject* obj, int index, long* value) {
    jsval element;
    if(JS_GetElement(cx, obj, index, &element) == JS_FALSE) 
        return JS_FALSE;
    
    if(JS_ValueToInteger(cx, element, value) == JS_FALSE)
        return JS_FALSE;
    
    return JS_TRUE;
}

JSBool GetDouble(JSContext* cx, JSObject* obj, int index, double* value) {
    jsval element;
    if(JS_GetElement(cx, obj, index, &element) == JS_FALSE) 
        return JS_FALSE;
    
    if(JS_ValueToDouble(cx, element, value) == JS_FALSE)
        return JS_FALSE;
    
    return JS_TRUE;
}




#pragma mark -
#pragma mark uv관련

//UV데이터 스트럭쳐
typedef struct UVdata UVdata;
struct UVdata {
	unsigned int libID;
    int pathCount;
	float *x, *y;
};

//UVdata array
unsigned int uv_data_len = 0;
UVdata* uv_data = NULL;

//한오브젝트의 UV데이터를 읽고 읽은 데이터 사이즈를 리턴
long ReadUVdata(FILE* uvFile, char* slicePath) {
    writelog("read uvdata");
	long result = 0;
	long len;
	result += fread(&len, sizeof(long), 1, uvFile) * sizeof(long);
	long tmp;
	result += fread(&tmp, sizeof(long), 1, uvFile) * sizeof(long);
	char* str = calloc(len + 1, sizeof(char));
	result += fread(str, sizeof(char), len, uvFile) * sizeof(char);
    
    char libName[0xFFF] = {'\0', };
    sprintf(libName, "%s%s.png", slicePath, str);
    
	uv_data_len++;
	if(uv_data == NULL) {
		uv_data = (UVdata*)malloc(sizeof(UVdata));
	} else {
		uv_data = (UVdata*)realloc(uv_data, sizeof(UVdata) * uv_data_len);
	}
	UVdata* data = &uv_data[uv_data_len - 1];
	memset(data, 0, sizeof(UVdata));
	
    //이름을 경로명으로 변경
    
	data->libID = PushLibraryName(libName);
    writelog("lib name = %s, id = %d", libName, data->libID);
	free(str);
    
    result += fread(&data->pathCount, sizeof(int), 1, uvFile) * sizeof(int);
    writelog("path count = %d", data->pathCount);
    
    if(data->pathCount == 0)
        return result;
    
    data->x = (float*)malloc(data->pathCount*sizeof(float));
    data->y = (float*)malloc(data->pathCount*sizeof(float));
    
    for(int i = 0; i < data->pathCount; ++i) {
        result += fread(&data->x[i], sizeof(float), 1, uvFile) * sizeof(float);
        result += fread(&data->y[i], sizeof(float), 1, uvFile) * sizeof(float);
        writelog("x = %.3f, y = %.3f", data->x[i], data->y[i]);
    }
    
	return result;
}

//uv데이터 배열을 삭제
void FreeUVdata() {
	if(uv_data) {
		free(uv_data);
		uv_data = NULL;
		uv_data_len = 0;
	}
}

#pragma mark -
#pragma mark 자바스크립트 유틸

//자바스크립트로 리턴할 문자를 만들고 성공여부를 리턴
JSBool ReturnString(JSContext *pCx, const char* pCStr, jsval *pVal)
{
	unsigned int strLen = strlen(pCStr) + 1;
	unsigned short* pStr = malloc(sizeof(unsigned short) * strLen);
	int i;
	for(i = 0; i < strLen-1; i++) {
		pStr[i] = (unsigned short)pCStr[i];
	}
    pStr[strLen] = 0;
	if(JS_StringToValue(pCx, pStr, strLen, pVal) == JS_FALSE) {
		free(pStr);
		return JS_FALSE;
	} else {
		free(pStr);
		return JS_TRUE;
	}
}



#pragma mark -
#pragma mark 자바스크립트가 호출할 함수

//생성할 오브젝트 파일
FILE* pObjectFile = NULL;

//FlashCS5extension.StartMakeObjectFile(생성할 오브젝트 파일패스, UV 파일패스들)
JSBool StartMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    
    clearlog();
    
    *rval = JS_BooleanToValue(JS_FALSE);
    
    if(argc != 3)
        return ReturnString(cx, "error: argument count", rval);
	
	unsigned int filePathLen;
	unsigned short* filePath = JS_ValueToString(cx, argv[0], &filePathLen);
	
	if(filePath == NULL)
        return ReturnString(cx, "error: obj file path", rval);
	
	JSObject* uvObj;
	if(JS_ValueToObject(cx, argv[1], &uvObj) == JS_FALSE)
        return ReturnString(cx, "error: uv file array", rval);
	
	long uvLen = JS_GetArrayLength(cx, uvObj);
	if(uvLen == -1)
        return ReturnString(cx, "error: image file array length", rval);
    
    JSObject* slicePathObj;
    if(JS_ValueToObject(cx, argv[2], &slicePathObj) == JS_FALSE)
        return ReturnString(cx, "error: slicePaht file array", rval);
	
	unsigned int uvPathLen[uvLen];
	unsigned short* uvPath[uvLen];
    
    char* slicePath = GetString(cx, slicePathObj, 0);
	
	int i;
	for(i = 0; i < uvLen; i++) {
		jsval posUV;
		if(JS_GetElement(cx, uvObj, i, &posUV) == JS_FALSE)
			return ReturnString(cx, "error: uv file array element", rval);
		
		uvPath[i] = JS_ValueToString(cx, posUV, &uvPathLen[i]);
		if(uvPath[i] == NULL)
			return ReturnString(cx, "error: uv file array element file path string", rval);
		
		FILE* uvDataFile = OpenFileString(uvPath[i], uvPathLen[i], "r");
        fread(&root_w, sizeof(long), 1, uvDataFile);
        fread(&root_h, sizeof(long), 1, uvDataFile);
		if(uvDataFile) {
			fseek(uvDataFile, 0, SEEK_END);
			long uvDataSize = ftell(uvDataFile);
			fseek(uvDataFile, sizeof(long) + sizeof(long), SEEK_SET);
			int result = sizeof(long) + sizeof(long);
			while(result < uvDataSize)
				result += ReadUVdata(uvDataFile, slicePath);
			fclose(uvDataFile);
		} else {
			return ReturnString(cx, "error: uv data fopen", rval);
		}
	}
    
    free(slicePath);
	
#define BreakStartMakeObjectFile(errorstr) \
fclose(pObjectFile); \
pObjectFile = NULL; \
return ReturnString(cx, errorstr, rval)
    
    if(pObjectFile) {
        fclose(pObjectFile);
        pObjectFile = NULL;
    }
	
	if(pObjectFile == NULL) {
		char* path = StringToAscii(filePath, filePathLen);
		pObjectFile = fopen(path, "w+");
		free(path);
		if(pObjectFile) {
			//fwrite(&imgLen, sizeof(long), 1, pObjectFile);FlashCS5extension.bundle
			for(i = 0; i < uvLen; i++) {
//				FILE* imgFile;
//				path = StringToAscii(imgPath[i], imgPathLen[i]);
//				if(path == NULL) {
//					BreakStartMakeObjectFile("error: image file path");
//				}
//				imgFile = fopen(path, "r");
//				free(path);
//				if(imgFile) {
//					WriteFileToFile(pObjectFile, imgFile);
//                    writelog("success write image");
//					fclose(imgFile);
//				} else {
//					BreakStartMakeObjectFile("error: image file fopen");
//				}
				
				int i;
				fwrite(&uv_data_len, sizeof(unsigned int), 1, pObjectFile);
                writelog("uv data length = %d", uv_data_len);
				for(i = 0; i < uv_data_len; i++) {
					fwrite(&uv_data[i].libID, sizeof(unsigned int), 1, pObjectFile);
                    writelog("libid = %d", uv_data[i].libID);
                    fwrite(&uv_data[i].pathCount, sizeof(int), 1, pObjectFile);
                    writelog("path count = %d", uv_data[i].pathCount);
                    for(int j = 0; j < uv_data[i].pathCount; ++j) {
                        float uv_x = (float)uv_data[i].x[j];
                        float uv_y = (float)uv_data[i].y[j];
                        fwrite(&uv_x, sizeof(float), 1, pObjectFile);
                        fwrite(&uv_y, sizeof(float), 1, pObjectFile);
                        writelog("x = %.3f, y = %.3f", uv_data[i].x[j], uv_data[i].y[j]);
                    }
				}
			}
		} else {
			//return JS_FALSE;
            return ReturnString(cx, "error : fail to make obj file", rval);
		}
	} else {
		//return JS_FALSE;
        return ReturnString(cx, "error : pObjectFile in use", rval);
	}
	
#undef BreakStartMakeObjectFile
	
	*rval = JS_BooleanToValue(JS_TRUE);
	for(int i = 0; i < root_library_name_id_len; i++) {
		writelog("??????????????????????????libname info length = %i data = %s??????????????????????????", strlen(root_library_name_id[i].name), root_library_name_id[i].name);
	}
	
	return JS_TRUE;
}

//FlashCS5extension.EndMakeObjectFile()
JSBool EndMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
	for(int i = 0; i < root_library_name_id_len; i++) {
		writelog("??????????????????????????libname info length = %i data = %s??????????????????????????", strlen(root_library_name_id[i].name), root_library_name_id[i].name);
	}
    if(argc != 2)
        return JS_FALSE;
	
	if(pObjectFile) {
		fseek(pObjectFile, 0, SEEK_END);
		long size = ftell(pObjectFile);
		fseek(pObjectFile, 0, SEEK_SET);
		void* allMem = malloc(size);
		fread(allMem, 1, size, pObjectFile);
		
		fseek(pObjectFile, 0, SEEK_SET);
        
		int i;
        //비트맵 이름을 업데이트 한다.
        JSObject* bitmapNameObj;
        if(JS_ValueToObject(cx, argv[0], &bitmapNameObj) == JS_FALSE)
            return ReturnString(cx, "fail to load bitmapNameArray", rval);
        
        int bitmapCount = JS_GetArrayLength(cx, bitmapNameObj);
        if(bitmapCount == -1)
            return ReturnString(cx, "fail to get bitmap Count", rval);
        
        for(i = 0; i < bitmapCount; ++i) {
            JSObject* bitmapObj;
            if(GetObject(cx, bitmapNameObj, i, &bitmapObj) == JS_FALSE)
                return ReturnString(cx, "fail to get bitmap obj", rval);
            
            char* bitmapName = GetString(cx, bitmapObj, 0);
            char* bitmapPath = GetString(cx, bitmapObj, 1);
			writelog("@@@@@@@@@@ %s %s @@@@@@@@@", bitmapPath, bitmapName);
            ChangeLibraryName(bitmapPath, bitmapName);
        }
        
        
        
        double frameRate;
        float frameRatef;
        
        if(JS_ValueToDouble(cx, argv[1], &frameRate) == JS_FALSE)
            return ReturnString(cx, "fail to load bitmapNameArray", rval);
        
        fwrite(&root_w, sizeof(long), 1, pObjectFile);
        fwrite(&root_h, sizeof(long), 1, pObjectFile);
        writelog("uv size = %f, %f", root_w, root_h);
        fwrite(&root_flash_w, sizeof(long), 1, pObjectFile);
        fwrite(&root_flash_h, sizeof(long), 1, pObjectFile);
        writelog("flash size = %f, %f", root_flash_w, root_flash_h);
        
        frameRatef = (float)frameRate;
        fwrite(&frameRatef, sizeof(float), 1, pObjectFile);
        writelog("frameRate = %f", frameRatef);
        
        writelog("=========== lib name layer ============");
        
		unsigned int name_len;
		fwrite(&root_library_name_id_len, sizeof(unsigned int), 1, pObjectFile);
		for(i = 0; i < root_library_name_id_len; i++) {
			name_len = strlen(root_library_name_id[i].name);
			writelog("libname info length = %i data = %s", name_len, root_library_name_id[i].name);
			fwrite(&name_len, sizeof(unsigned int), 1, pObjectFile);
			fwrite(root_library_name_id[i].name, sizeof(char), name_len, pObjectFile);
			fwrite(&root_library_name_id[i].id, sizeof(unsigned int), 1, pObjectFile);
            
            writelog("libname = %s, libid = %d", root_library_name_id[i].name, root_library_name_id[i].id);
		}
		fwrite(allMem, 1, size, pObjectFile);
		free(allMem);
		fclose(pObjectFile);
		pObjectFile = NULL;
		
		FreeLibraryName();
		FreeUVdata();
		
		*rval = JS_BooleanToValue(JS_TRUE);
		
		return JS_TRUE; 
	} else {
		
		FreeLibraryName();
	 	FreeUVdata();
		
		return JS_FALSE; 
	}
}

//FlashCS5extension.WriteDynamic(라이브러리 다이나믹들)
JSBool WriteDynamic(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    
    writelog("begin");
    
    if(argc != 1)
        return JS_FALSE;
    
    writelog("check arg count");
	
	if(pObjectFile) {
		JSObject* dynamicObjs;
		if(JS_ValueToObject(cx, argv[0], &dynamicObjs) == JS_FALSE)
			return ReturnString(cx, "q _ 1", rval);
        
        writelog("get dynamic objects from argv[0]");
		
		unsigned int dynamicLen = (unsigned int)JS_GetArrayLength(cx, dynamicObjs);
		if(dynamicLen == -1)
			return ReturnString(cx, "q _ 2", rval);
        
        writelog("get dynamic length = %u", dynamicLen);
		
		fwrite(&dynamicLen, sizeof(unsigned int), 1, pObjectFile);
		
		for(int i = 0; i < dynamicLen; i++) {
			jsval posDynamic;
			if(JS_GetElement(cx, dynamicObjs, i, &posDynamic) == JS_FALSE)
				return ReturnString(cx, "q _ 3", rval);
            
            writelog("==================================");
            writelog("get dynamic element %d", i);
			
			JSObject* dynamicObj;
			if(JS_ValueToObject(cx, posDynamic, &dynamicObj) == JS_FALSE)
				return ReturnString(cx, "q _ 4", rval);
            
            writelog("get dynamic object %d", i);
			
			//라이브러리 네임
            char *libName = GetString(cx, dynamicObj, 0);
            if(libName == 0)
                return ReturnString(cx, "q _ 5", rval);
            
            //library ID
			unsigned int libID = PushLibraryName(libName);
			fwrite(&libID, sizeof(unsigned int), 1, pObjectFile);
            writelog("libName = %s, libID = %u", libName, libID);
			free(libName);
            
            //library Type
            long libType;
            if(GetInteger(cx, dynamicObj, 4, &libType) == JS_FALSE)
                return ReturnString(cx, "q _ 51", rval);
            
            writelog("lib type = %d", libType);
            fwrite(&libType, sizeof(long), 1, pObjectFile);
            
            //frame Length
            long frameLength;
            if(GetInteger(cx, dynamicObj, 5, &frameLength) == JS_FALSE)
                return ReturnString(cx, "q _ 51", rval);
            
            writelog("frame length = %d", frameLength);
            fwrite(&frameLength, sizeof(long), 1, pObjectFile);
            
//            //인스턴스 
//            {
//                JSObject* instanceObj;
//                if(GetObject(cx, dynamicObj, 3, &instanceObj) == JS_FALSE)
//                    return ReturnString(cx, "instance  _ 1", rval);
//                
//                //인스턴스 개수
//                int insLen = (int)JS_GetArrayLength(cx, instanceObj);
//                if(insLen == -1)
//                    return ReturnString(cx, "instance  _ 2", rval);
//                
//                fwrite(&insLen, sizeof(int), 1, pObjectFile);
//                
//                writelog("instance length = %d", insLen);
//                
//                for(int m = 0; m < insLen; m++) {
//                    //instance obj
//                    JSObject* insObj;
//                    if(GetObject(cx, instanceObj, m, &insObj) == JS_FALSE)
//                        return ReturnString(cx, "instance  _ 3", rval);
//                    
//                    //instance id
//                    long insid;
//                    if(GetInteger(cx, insObj, 1, &insid) == JS_FALSE)
//                        return ReturnString(cx, "instance  _ 4", rval);
//                    
//                    //instance name
//                    char* insName = GetString(cx, insObj, 0);
//                    //instnace name length
//                    int insNameLen = strlen(insName);
//                    
//                    fwrite(&insNameLen, sizeof(int), 1, pObjectFile);
//                    
//                    writelog("instance name length = %d", insNameLen);
//                    
//                    fwrite(insName, sizeof(char), insNameLen, pObjectFile);
//                    
//                    writelog("instance name = %s", insName);
//                    
//                    fwrite(&insid, sizeof(int), 1, pObjectFile);
//                    
//                    writelog("instance id = %d", insid);
//                    
//                    free(insName);
//                }
//            }
            
            //레퍼런스
            {
                JSObject* referenceObj;
                if(GetObject(cx, dynamicObj, 1, &referenceObj) == JS_FALSE)
                    return ReturnString(cx, "q _ 6", rval);
                
                writelog("--------------------------------");
                writelog("get reference obj");
                
                
                
                //reference count
                int refLen = (int)JS_GetArrayLength(cx, referenceObj);
                if(refLen == -1)
                    return ReturnString(cx, "q _ 7", rval);
                
                writelog("reference length = %ld", refLen);
                
                fwrite(&refLen, sizeof(int), 1, pObjectFile);
                
                for(int j = 0; j < refLen; ++j) {
                    writelog("--------------------------------");
                    
                    //ref info obj
                    JSObject* refObj;
                    if(GetObject(cx, referenceObj, j, &refObj) == JS_FALSE)
                        return ReturnString(cx, "q _ 71", rval);
                    
                    int refMemberIndex = 0;
                    
                    int refinfoLen = (int)JS_GetArrayLength(cx, refObj);
                    if(refinfoLen == -1)
                        return ReturnString(cx, "q _ 72", rval);
                    
                    //reference ID
                    long refid;
                    if(GetInteger(cx, refObj, refMemberIndex++, &refid) == JS_FALSE)
                        return ReturnString(cx, "q _ 8", rval);
                    
                    //type
                    long type;
                    if(GetInteger(cx, refObj, refMemberIndex++, &type) == JS_FALSE)
                        return ReturnString(cx, "q _ 11", rval);
                    
                    writelog("type = %d", type);
                    
                    fwrite(&type, sizeof(long), 1, pObjectFile);
                    
                    //lib ID
                    char* libName = GetString(cx, refObj, refMemberIndex++);

                    //read Depth
                    
                    //read StartFrame
                    long startFrame;
                    if(GetInteger(cx, refObj, refMemberIndex++, &startFrame) == JS_FALSE)
                        return ReturnString(cx, "q _ 11", rval);
                    
                    //read End Frame
                    long endFrame;
                    if(GetInteger(cx, refObj, refMemberIndex++, &endFrame) == JS_FALSE)
                        return ReturnString(cx, "q _ 42", rval);
                    
                    //read next reference ID
                    long nextrefid;
                    if(GetInteger(cx, refObj, refMemberIndex++, &nextrefid) == JS_FALSE)
                        return ReturnString(cx, "q _ 8", rval);
                    
                    //read depth
                    long depth;
                    if(GetInteger(cx, refObj, refMemberIndex++, &depth) == JS_FALSE)
                        return ReturnString(cx, "q _ 8", rval);
                    
                                        
                    if(type == _TYPE_BITMAP_) {
                        //lib Path                    
                        char* libPath = GetString(cx, refObj, refMemberIndex++);
                        unsigned int libID = PushLibraryName(libPath);
                        fwrite(&libID, sizeof(unsigned int), 1, pObjectFile);
                        writelog("lib path = %s, lib = %u", libPath, libID);
                        free(libPath);
                    } else if(type == _TYPE_GRAPHIC_) {
                        //get lib name
                        unsigned int libID = PushLibraryName(libName);
                        fwrite(&libID, sizeof(unsigned int), 1, pObjectFile);
                        writelog("lib name = %s, lib = %u", libName, libID);
                        free(libName); 
                    } else {
                        //get lib name
                        unsigned int libID = PushLibraryName(libName);
                        fwrite(&libID, sizeof(unsigned int), 1, pObjectFile);
                        writelog("lib name = %s, lib = %u", libName, libID);
                        free(libName);    
                        
                        //instance ID
                        long insLen;
                        char* insName = GetString(cx, refObj, refMemberIndex++);
                        insLen = strlen(insName);
                        fwrite(&insLen, sizeof(long), 1, pObjectFile);
                        fwrite(insName, insLen, 1, pObjectFile);
                        writelog("instnace name = %s", insName);
                    }
                    
                    //write depth
                    writelog("depth = %d", depth);
                    fwrite(&depth, sizeof(long), 1, pObjectFile);
                    
                    //write Start Frame
                    writelog("startFrame = %d", startFrame);
                    
                    fwrite(&startFrame, sizeof(long), 1, pObjectFile);
                    
                    //write End Frame
                    writelog("end frame = %d", endFrame);
                    
                    fwrite(&endFrame, sizeof(long), 1, pObjectFile);

                    if(type == _TYPE_BITMAP_ || type == _TYPE_GRAPHIC_ || type == _TYPE_MOVIECLIP_) {
                        
                        
                        writelog("ref id = %d", refid);
                        
                        fwrite(&refid, sizeof(long), 1, pObjectFile);
                        
                        //write next reference ID
                        writelog("next ref id = %d", nextrefid);
                        
                        fwrite(&nextrefid, sizeof(long), 1, pObjectFile);
                        
                        //Start Position
                        double startX;
                        double startY;
                        if(GetDouble(cx, refObj, refMemberIndex++, &startX) == JS_FALSE)
                            return ReturnString(cx, "q _ 12", rval);
                        
                        if(GetDouble(cx, refObj, refMemberIndex++, &startY) == JS_FALSE)
                            return ReturnString(cx, "q _ 13", rval);
                        
                        float startXf, startYf;
                        startXf = (float)startX;
                        startYf = (float)startY;
                        fwrite(&startXf, sizeof(float), 1, pObjectFile);
                        fwrite(&startYf, sizeof(float), 1, pObjectFile);
                        
                        writelog("startX = %f, startY = %f", startX, startY);
                        
                        //Anchor
                        double anchorX;
                        double anchorY;
                        if(GetDouble(cx, refObj, refMemberIndex++, &anchorX) == JS_FALSE)
                            return ReturnString(cx, "q _ 14", rval);
                        
                        if(GetDouble(cx, refObj, refMemberIndex++, &anchorY) == JS_FALSE)
                            return ReturnString(cx, "q _ 15", rval);
                        
                        float anchorXf, anchorYf;
                        anchorXf = (float)anchorX;
                        anchorYf = (float)anchorY;
                        fwrite(&anchorXf, sizeof(float), 1, pObjectFile);
                        fwrite(&anchorYf, sizeof(float), 1, pObjectFile);
                        
                        writelog("anchorX = %f, anchorY = %f", anchorX, anchorY);
                        
                        //Start Rotation
                        double startRotation;
                        if(GetDouble(cx, refObj, refMemberIndex++, &startRotation) == JS_FALSE)
                            return ReturnString(cx, "q _ 16", rval);
                        
                        float rotf = (float)startRotation;
                        fwrite(&rotf, sizeof(float), 1, pObjectFile);
                        
                        writelog("rotation = %f", startRotation);
                        
                        //Start Scale
                        double scaleX;
                        double scaleY;
                        if(GetDouble(cx, refObj, refMemberIndex++, &scaleX) == JS_FALSE)
                            return ReturnString(cx, "q _ 17", rval);
                        if(GetDouble(cx, refObj, refMemberIndex++, &scaleY) == JS_FALSE)
                            return ReturnString(cx, "q _ 18", rval);
                        
                        float scaleXf, scaleYf;
                        scaleXf = (float)scaleX;
                        scaleYf = (float)scaleY;
                        fwrite(&scaleXf, sizeof(float), 1, pObjectFile);
                        fwrite(&scaleYf, sizeof(float), 1, pObjectFile);
                        
                        writelog("scale x = %f, y = %f", scaleX, scaleY);
                        
                        //Start Skew
                        double startSkewX;
                        double startSkewY;
                        if(GetDouble(cx, refObj, refMemberIndex++, &startSkewX) == JS_FALSE)
                            return ReturnString(cx, "q _ 19", rval);
                        if(GetDouble(cx, refObj, refMemberIndex++, &startSkewY) == JS_FALSE)
                            return ReturnString(cx, "q _ 20", rval);
                        
                        float skewXf, skewYf;
                        skewXf = (float)startSkewX;
                        skewYf = (float)startSkewY;
                        fwrite(&skewXf, sizeof(float), 1, pObjectFile);
                        fwrite(&skewYf, sizeof(float), 1, pObjectFile);
                        
                        writelog("skew x = %f, y = %f", startSkewX, startSkewY);
                        
                        if(type == _TYPE_GRAPHIC_ || type == _TYPE_MOVIECLIP_) {
                            //Start Color Style
                            long startColorAlphaPercent;
                            long startColorRedPercent;
                            long startColorGreenPercent;
                            long startColorBluePercent;
                            long startColorAlphaAmount;
                            long startColorRedAmount;
                            long startColorGreenAmount;
                            long startColorBlueAmount;
                            
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorAlphaPercent) == JS_FALSE)
                                return ReturnString(cx, "q _ 22", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorRedPercent) == JS_FALSE)
                                return ReturnString(cx, "q _ 23", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorGreenPercent) == JS_FALSE)
                                return ReturnString(cx, "q _ 24", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorBluePercent) == JS_FALSE)
                                return ReturnString(cx, "q _ 25", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorAlphaAmount) == JS_FALSE)
                                return ReturnString(cx, "q _ 26", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorRedAmount) == JS_FALSE)
                                return ReturnString(cx, "q _ 27", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorGreenAmount) == JS_FALSE)
                                return ReturnString(cx, "q _ 28", rval);
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorBlueAmount) == JS_FALSE)
                                return ReturnString(cx, "q _ 29", rval);
                            
                            char alphaPercent = (char)startColorAlphaPercent;
                            char redPercent = (char)startColorRedPercent;
                            char greenPercent = (char)startColorGreenPercent;
                            char bluePercent = (char)startColorBluePercent;
                            short alphaAmount = (short)startColorAlphaAmount;
                            short redAmount = (short)startColorRedAmount;
                            short greenAmount = (short)startColorGreenAmount;
                            short blueAmount = (short)startColorBlueAmount;                            
                            fwrite(&redPercent, sizeof(char), 1, pObjectFile);
                            fwrite(&greenPercent, sizeof(char), 1, pObjectFile);
                            fwrite(&bluePercent, sizeof(char), 1, pObjectFile);
                            fwrite(&alphaPercent, sizeof(char), 1, pObjectFile);                            
                            fwrite(&redAmount, sizeof(short), 1, pObjectFile);
                            fwrite(&greenAmount, sizeof(short), 1, pObjectFile);
                            fwrite(&blueAmount, sizeof(short), 1, pObjectFile);
                            fwrite(&alphaAmount, sizeof(short), 1, pObjectFile);
                            
                            writelog("alpha percent = %d", startColorAlphaPercent);
                            writelog("red percent = %d", startColorRedPercent);
                            writelog("green percent = %d", startColorGreenPercent);
                            writelog("blue percent = %d", startColorBluePercent);
                            writelog("alpha amount = %d", startColorAlphaAmount);
                            writelog("red amount = %d", startColorRedAmount);
                            writelog("green amount = %d", startColorGreenAmount);
                            writelog("blue amount = %d", startColorBlueAmount);
                        }
                        
                        if(type == _TYPE_GRAPHIC_ || type == _TYPE_MOVIECLIP_)  {
                            long startColorBlendMode;
                            if(GetInteger(cx, refObj, refMemberIndex++, &startColorBlendMode) == JS_FALSE)
                                return ReturnString(cx, "q _ 30", rval);
                            
                            unsigned char blendMode = (unsigned char)startColorBlendMode;
                            fwrite(&blendMode, sizeof(blendMode), 1, pObjectFile);
                            writelog("blend mode = %d", startColorBlendMode);
                            
                            //Ease
                            long easeType;
                            if(GetInteger(cx, refObj, refMemberIndex++, &easeType) == JS_FALSE)
                                return ReturnString(cx, "q _ 31", rval);
                            
                            writelog("ease type = %d", easeType);
                            
                            unsigned char easeTypeuc = (unsigned char)easeType;
                            fwrite(&easeTypeuc, sizeof(easeTypeuc), 1, pObjectFile);
                            
                            if(easeType == 2) {  //멀티 타입일 경우(Position, Rotation, Scale, Color, Filters)
                                for(int l = 0; l < 4; ++l)
                                {
                                    JSObject* easeObj;
                                    if(GetObject(cx, refObj, refMemberIndex++, &easeObj) == JS_FALSE)
                                        return ReturnString(cx, "q _ 32", rval);
                                    
                                    writelog("get multi ease obj");
                                    
                                    int easeCount = JS_GetArrayLength(cx, easeObj);
                                    if(easeCount == -1)
                                        return ReturnString(cx, "q _ 33", rval);
                                    
                                    writelog("get ease length = %d", easeCount);
                                    
                                    fwrite(&easeCount, sizeof(int), 1, pObjectFile);
                                    
                                    for(int k = 0; k < easeCount; ++k) {
                                        JSObject* posObj;
                                        if(GetObject(cx, easeObj, k, &posObj) == JS_FALSE)
                                            return ReturnString(cx, "q _ 34", rval);
                                        
                                        writelog("get pos obj");
                                        
                                        double x, y;
                                        if(GetDouble(cx, posObj, 0, &x) == JS_FALSE)
                                            return ReturnString(cx, "q _ 35", rval);
                                        if(GetDouble(cx, posObj, 1, &y) == JS_FALSE)
                                            return ReturnString(cx, "q _ 36", rval);
                                        
                                        float fx, fy;
                                        fx = (float)x;
                                        fy = (float)y;
                                        fwrite(&fx, sizeof(float), 1, pObjectFile);
                                        fwrite(&fy, sizeof(float), 1, pObjectFile);
                                        
                                        writelog("x = %f, y = %f", x, y);
                                    }
                                }
                            } else if(easeType == 1) {        //싱글이나 심플일 경우
                                JSObject* easeObj;
                                if(GetObject(cx, refObj, refMemberIndex++, &easeObj) == JS_FALSE)
                                    return ReturnString(cx, "q _ 37", rval);
                                
                                writelog("get ease obj");
                                
                                int easeCount = JS_GetArrayLength(cx, easeObj);
                                if(easeCount == -1)
                                    return ReturnString(cx, "q _ 38", rval);
                                
                                writelog("get ease length = %d", easeCount);
                                
                                fwrite(&easeCount, sizeof(int), 1, pObjectFile);
                                
                                for(int k = 0; k < easeCount; ++k) {
                                    JSObject* posObj;
                                    if(GetObject(cx, easeObj, k, &posObj) == JS_FALSE)
                                        return ReturnString(cx, "q _ 39", rval);
                                    
                                    writelog("get pos obj");
                                    
                                    double x, y;
                                    if(GetDouble(cx, posObj, 0, &x) == JS_FALSE)
                                        return ReturnString(cx, "q _ 40", rval);
                                    if(GetDouble(cx, posObj, 1, &y) == JS_FALSE)
                                        return ReturnString(cx, "q _ 41", rval);
                                    
                                    float fx, fy;
                                    fx = (float)x;
                                    fy = (float)y;
                                    fwrite(&fx, sizeof(float), 1, pObjectFile);
                                    fwrite(&fy, sizeof(float), 1, pObjectFile);
                                    
                                    writelog("x = %f, y = %f", x, y);
                                }
                            }
                        }    
                    }
                }                
            }
            
//			//프레임
//            {
//                JSObject* frameObj;
//                if(GetObject(cx, dynamicObj, 2, &frameObj) == JS_FALSE)
//                    return ReturnString(cx, "q _ 60", rval);
//                
//                writelog("get frame obj");
//                
//                //프레임 개수
//                int frameCount;
//                frameCount = JS_GetArrayLength(cx, frameObj);
//                if(frameCount == -1)
//                    return ReturnString(cx, "q _ 61", rval);
//                
//                writelog("get frame count = %d", frameCount);
//                
//                fwrite(&frameCount, sizeof(int), 1, pObjectFile);
//                
//                for(int j = 0; j < frameCount; ++j) {
//                    //레퍼런스 아이디 배열
//                    JSObject* refObj;
//                    if(GetObject(cx, frameObj, j, &refObj) == JS_FALSE)
//                        return ReturnString(cx, "q _ 62", rval);
//                    
//                    fwrite(&j, sizeof(int), 1, pObjectFile);
//                    
//                    writelog("frame = %d", j);
//                    
//                    //레퍼런스 개수
//                    int refCount = JS_GetArrayLength(cx, refObj);
//                    if(refCount == -1)
//                        return ReturnString(cx, "q _ 63", rval);
//                    
//                    fwrite(&refCount, sizeof(int), 1, pObjectFile);
//                    
//                    writelog("ref count = %d", refCount);
//                    
//                    for(int k = 0; k < refCount; ++k) {
//                        //레퍼런스 번호
//                        long refid;
//                        if(GetInteger(cx, refObj, k, &refid) == JS_FALSE)
//                            return ReturnString(cx, "q _ 64", rval);
//                        
//                        fwrite(&refid, sizeof(long), 1, pObjectFile);
//                        
//                        writelog("ref id = %d", refid);
//                    }
//                }
//            }
		}
        
		*rval = JS_BooleanToValue(JS_TRUE);
		
		return JS_TRUE; 
	} else {
		return ReturnString(cx, "a _ 17", rval);
	}
}

JSBool GetProjectPathAndFileName(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    if(argc != 0)
        return JS_FALSE;
    FILE* file = fopen("/VBEngine/tmp/photoshopPSDName", "r");
    if(file) {
        int tmplen;
        fread(&tmplen, 1, sizeof(int), file);
        char tmpstr[tmplen];
        fread(tmpstr, tmplen, sizeof(char), file);
        fclose(file);
        file = 0;
        remove("/VBEngine/tmp/photoshopPSDName");
        
        unsigned short* pStr = malloc(sizeof(unsigned short) * (tmplen + 1));
        int i;
        for(i = 0; i < tmplen; i++) {
            pStr[i] = (unsigned short)tmpstr[i];
        }
        pStr[i] = '\0';
        if(JS_StringToValue(cx, pStr, tmplen + 1, rval) == JS_FALSE) {
            free(pStr);
            return JS_FALSE;
        } else {
            free(pStr);
            return JS_TRUE;
        }
    } else {
		*rval = JS_BooleanToValue(JS_FALSE);
		
        return JS_TRUE;
    }
}

//fl.fileExists 로 대체해서 필요없는 코드임
JSBool CheckExistingProject(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    if(argc != 1)
        return JS_FALSE;
    
    unsigned int filePathLen;
	unsigned short* filePath = JS_ValueToString(cx, argv[0], &filePathLen);
    FILE* file = OpenFileString(filePath, filePathLen, "r");
    if(file) {
        *rval = JS_BooleanToValue(JS_TRUE);
        return JS_TRUE;
    } else {
        *rval = JS_BooleanToValue(JS_FALSE);
        return JS_TRUE;
    }
}


JSBool WriteOriginInfo(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    *rval = JS_BooleanToValue(JS_TRUE);
    
    if(argc != 2)
        return JS_FALSE;
    
    JS_ValueToInteger(cx, argv[0], &root_flash_w);
    JS_ValueToInteger(cx, argv[1], &root_flash_h);
    
    return JS_TRUE;
}






