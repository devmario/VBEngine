#include "FlashCS5extension.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CAPIUtil.h"

#pragma mark -
#pragma mark 유니크 아이디를 위한 네임 아이디

//라이브러리 네임과 ID를 매치시켜주는 스트럭쳐
typedef struct LibraryNameID LibraryNameID;
struct LibraryNameID {
	char* name;
	unsigned short id;
};

//인스턴스 네임과 ID를 매치시켜주는 스트럭쳐
typedef struct InstanceNameID InstanceNameID;
struct InstanceNameID {
	char* name;
	unsigned int id;
};

//unique ID를 위한 변수
unsigned int root_library_id = 0;
//라이브러리 아이디 갯수
unsigned int root_library_name_id_len = 0;
//라이브러리 아이디 스트럭처 포인터
LibraryNameID* root_library_name_id = NULL;

//unique ID를 위한 변수
unsigned int root_instance_id = 0;
//인스턴스 아이디 갯수
unsigned int root_instance_name_id_len = 0;
//인스턴스 아이디 스트럭쳐 포인터
InstanceNameID* root_instance_name_id = NULL;

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
	if(name[0] < 32 || name[0] > 126)
		return 0;
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
	
	nameID->id = ++root_library_id;
	return nameID->id;
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

//문자열로 인스턴스 아이디를 리턴
unsigned int FindInstanceID(const char* name) {
	int i;
	for(i = 0; i < root_instance_name_id_len; i++) {
		if(strcmp(root_instance_name_id[i].name, name) == 0)
			return root_instance_name_id[i].id;
	}
	return 0;
}

//인스턴스 아이디로 매치되는 해당 문자열 리턴
char* FindInstanceName(unsigned int id) {
	int i;
	for(i = 0; i < root_instance_name_id_len; i++) {
		if(root_instance_name_id[i].id == id) {
			return root_instance_name_id[i].name;
		}
	}
	return NULL;
}

//인스턴스 아이디에 네임을 추가
unsigned int PushInstanceName(const char* name) {
	if(name[0] < 32 || name[0] > 126)
		return 0;
	if(strlen(name) == 0)
		return 0;
	unsigned int id = FindInstanceID(name);
	if(id != 0)
		return id;
	root_instance_name_id_len++;
	if(root_instance_name_id == NULL) {
		root_instance_name_id = (InstanceNameID*)malloc(sizeof(InstanceNameID));
	} else {
		root_instance_name_id = (InstanceNameID*)realloc(root_instance_name_id, sizeof(InstanceNameID) * root_instance_name_id_len);
	}
	InstanceNameID* nameID = &root_instance_name_id[root_instance_name_id_len - 1];
	memset(nameID, 0, sizeof(InstanceNameID));
	
	nameID->name = calloc(strlen(name) + 1, sizeof(char));
	sprintf(nameID->name, "%s", name);
	
	nameID->id = ++root_instance_id;
	return nameID->id;
}

//인스턴스 아이디 삭제
void FreeInstanceName() {
	if(root_instance_name_id) {
		int i;
		for(i = 0; i < root_instance_name_id_len; i++) {
			free(root_instance_name_id[i].name);
		}
		free(root_instance_name_id);
		root_instance_name_id = NULL;
		root_instance_name_id_len = 0;
		root_instance_id = 0;
	}
}

#pragma mark -
#pragma mark uv관련

//UV데이터 스트럭쳐
typedef struct UVdata UVdata;
struct UVdata {
	unsigned int libID;
	int x, y, width, height;
};

//UVdata array
unsigned int uv_data_len = 0;
UVdata* uv_data = NULL;

//한오브젝트의 UV데이터를 읽고 읽은 데이터 사이즈를 리턴
long ReadUVdata(FILE* uvFile) {
	long result = 0;
	long len;
	result += fread(&len, sizeof(long), 1, uvFile) * sizeof(long);
	long tmp;
	result += fread(&tmp, sizeof(long), 1, uvFile) * sizeof(long);
	char* str = calloc(len + 1, sizeof(char));
	result += fread(str, sizeof(char), len, uvFile) * sizeof(char);
	
	uv_data_len++;
	if(uv_data == NULL) {
		uv_data = (UVdata*)malloc(sizeof(UVdata));
	} else {
		uv_data = (UVdata*)realloc(uv_data, sizeof(UVdata) * uv_data_len);
	}
	UVdata* data = &uv_data[uv_data_len - 1];
	memset(data, 0, sizeof(UVdata));
	
	data->libID = PushLibraryName(str);
	free(str);
	
	result += fread(&data->x, sizeof(float), 1, uvFile) * sizeof(float);
	result += fread(&data->y, sizeof(float), 1, uvFile) * sizeof(float);

	result += fread(&data->height, sizeof(float), 1, uvFile) * sizeof(float);
	
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

//FlashCS5extension.StartMakeObjectFile(생성할 오브젝트 파일패스, 이미지 파일패스들, UV 파일패스들)
JSBool StartMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    if(argc != 3)
        return ReturnString(cx, "error: argument count", rval);
	
	unsigned int filePathLen;
	unsigned short* filePath = JS_ValueToString(cx, argv[0], &filePathLen);
	
	if(filePath == NULL)
        return ReturnString(cx, "error: obj file path", rval);
	
	JSObject* imgObj;
	if(JS_ValueToObject(cx, argv[1], &imgObj) == JS_FALSE)
        return ReturnString(cx, "error: image file array", rval);
	
	long imgLen = JS_GetArrayLength(cx, imgObj);
	if(imgLen == -1)
        return ReturnString(cx, "error: image file array length", rval);
	
	JSObject* uvObj;
	if(JS_ValueToObject(cx, argv[2], &uvObj) == JS_FALSE)
        return ReturnString(cx, "error: uv file array", rval);
	
	long uvLen = JS_GetArrayLength(cx, uvObj);
	if(uvLen == -1)
        return ReturnString(cx, "error: uv file array length", rval);
	if(uvLen != imgLen)
        return ReturnString(cx, "error: image file array length != uv file array length", rval);
	
	unsigned int imgPathLen[imgLen];
	unsigned short* imgPath[imgLen];
	
	unsigned int uvPathLen[uvLen];
	unsigned short* uvPath[uvLen];
	
	int i;
	for(i = 0; i < imgLen; i++) {
		jsval posImg;
		if(JS_GetElement(cx, imgObj, i, &posImg) == JS_FALSE)
			return ReturnString(cx, "error: image file array element", rval);
		
		imgPath[i] = JS_ValueToString(cx, posImg, &imgPathLen[i]);
		if(imgPath[i] == NULL)
			return ReturnString(cx, "error: image file array element file path string", rval);
		
		jsval posUV;
		if(JS_GetElement(cx, uvObj, i, &posUV) == JS_FALSE)
			return ReturnString(cx, "error: uv file array element", rval);
		
		uvPath[i] = JS_ValueToString(cx, posUV, &uvPathLen[i]);
		if(uvPath[i] == NULL)
			return ReturnString(cx, "error: uv file array element file path string", rval);
		
		FILE* uvDataFile = OpenFileString(uvPath[i], uvPathLen[i], "r");
		if(uvDataFile) {
			fseek(uvDataFile, 0, SEEK_END);
			long uvDataSize = ftell(uvDataFile);
			fseek(uvDataFile, 0, SEEK_SET);
			int result = 0;
			while(result < uvDataSize)
				result += ReadUVdata(uvDataFile);
			fclose(uvDataFile);
		} else {
			return ReturnString(cx, "error: uv data fopen", rval);
		}
	}
	
#define BreakStartMakeObjectFile(errorstr) \
	fclose(pObjectFile); \
	pObjectFile = NULL; \
	return ReturnString(cx, errorstr, rval)
	
	if(pObjectFile == NULL) {
		char* path = StringToAscii(filePath, filePathLen);
		pObjectFile = fopen(path, "w+");
		free(path);
		if(pObjectFile) {
			fwrite(&imgLen, sizeof(long), 1, pObjectFile);
			for(i = 0; i < imgLen; i++) {
				FILE* imgFile;
				path = StringToAscii(imgPath[i], imgPathLen[i]);
				if(path == NULL) {
					BreakStartMakeObjectFile("error: image file path");
				}
				imgFile = fopen(path, "r");
				free(path);
				if(imgFile) {
					WriteFileToFile(pObjectFile, imgFile);
					fclose(imgFile);
				} else {
					BreakStartMakeObjectFile("error: image file fopen");
				}
				
				int i;
				fwrite(&uv_data_len, sizeof(unsigned int), 1, pObjectFile);
				for(i = 0; i < uv_data_len; i++) {
					fwrite(&uv_data[i].libID, sizeof(unsigned int), 1, pObjectFile);
					fwrite(&uv_data[i].x, sizeof(int), 1, pObjectFile);
					fwrite(&uv_data[i].y, sizeof(int), 1, pObjectFile);
					fwrite(&uv_data[i].width, sizeof(int), 1, pObjectFile);
					fwrite(&uv_data[i].height, sizeof(int), 1, pObjectFile);
				}
			}
		} else {
			return JS_FALSE;
		}
	} else {
		return JS_FALSE;
	}
	
#undef BreakStartMakeObjectFile
	
	*rval = JS_BooleanToValue(JS_TRUE);
	
	return JS_TRUE;
}

//FlashCS5extension.EndMakeObjectFile()
JSBool EndMakeObjectFile(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    if(argc != 0)
        return JS_FALSE;
	
	if(pObjectFile) {
		fseek(pObjectFile, 0, SEEK_END);
		long size = ftell(pObjectFile);
		fseek(pObjectFile, 0, SEEK_SET);
		void* allMem = malloc(size);
		fread(allMem, 1, size, pObjectFile);
		
		fseek(pObjectFile, 0, SEEK_SET);
		int i;
		unsigned int name_len;
		fwrite(&root_library_name_id_len, sizeof(unsigned int), 1, pObjectFile);
		for(i = 0; i < root_library_name_id_len; i++) {
			name_len = strlen(root_library_name_id[i].name);
			fwrite(&name_len, sizeof(unsigned int), 1, pObjectFile);
			fwrite(root_library_name_id[i].name, sizeof(char), name_len, pObjectFile);
			fwrite(&root_library_name_id[i].id, sizeof(unsigned int), 1, pObjectFile);
		}
		fwrite(&root_instance_name_id_len, sizeof(unsigned int), 1, pObjectFile);
		for(i = 0; i < root_instance_name_id_len; i++) {
			name_len = strlen(root_instance_name_id[i].name);
			fwrite(&name_len, sizeof(unsigned int), 1, pObjectFile);
			fwrite(root_instance_name_id[i].name, sizeof(char), name_len, pObjectFile);
			fwrite(&root_instance_name_id[i].id, sizeof(unsigned int), 1, pObjectFile);
		}
		fwrite(allMem, 1, size, pObjectFile);
		free(allMem);
		fclose(pObjectFile);
		pObjectFile = NULL;
		
		FreeLibraryName();
		FreeInstanceName();
		FreeUVdata();
		
		*rval = JS_BooleanToValue(JS_TRUE);
		
		return JS_TRUE; 
	} else {
		
		FreeLibraryName();
		FreeInstanceName();
		FreeUVdata();
		
		return JS_FALSE; 
	}
}

//FlashCS5extension.WriteObject(라이브러리 Object들)
JSBool WriteObject(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    if(argc != 1)
        return JS_FALSE;
	
	if(pObjectFile) {
		JSObject* objs;
		if(JS_ValueToObject(cx, argv[0], &objs) == JS_FALSE)
			return ReturnString(cx, "z _ 1", rval);
		
		unsigned int objsLen = (unsigned int)JS_GetArrayLength(cx, objs);
		if(objsLen == -1)
			return ReturnString(cx, "z _ 2", rval);
		
		fwrite(&objsLen, sizeof(unsigned int), 1, pObjectFile);
		
		int i;
		for(i = 0; i < objsLen; i++) {
			jsval posObj;
			if(JS_GetElement(cx, objs, i, &posObj) == JS_FALSE)
				return ReturnString(cx, "z _ 3", rval);
			
			JSObject* obj;
			if(JS_ValueToObject(cx, posObj, &obj) == JS_FALSE)
				return ReturnString(cx, "z _ 4", rval);
			
			jsval element;
			
			//라이브러리 네임
			if(JS_GetElement(cx, obj, 0, &element) == JS_FALSE)
				return ReturnString(cx, "z _ 5", rval);
			
			unsigned int libNameLen;
			unsigned short* libName = JS_ValueToString(cx, element, &libNameLen);
			if(libName == NULL)
				return ReturnString(cx, "z _ 6", rval);
			
			char* libNameAscii = StringToAscii(libName, libNameLen);
			if(libNameAscii == NULL)
				return JS_FALSE;
			unsigned int libID = PushLibraryName(libNameAscii);
			fwrite(&libID, sizeof(unsigned int), 1, pObjectFile);
			free(libNameAscii);
			
			//센터
			double center;
			
			if(JS_GetElement(cx, obj, 1, &element) == JS_FALSE)
				return ReturnString(cx, "z _ a", rval);
			if(JS_ValueToDouble(cx, element, &center) == JS_FALSE)
				return ReturnString(cx, "z _ b", rval);
			float x = (float)center;
			fwrite(&x, sizeof(float), 1, pObjectFile);
			
			if(JS_GetElement(cx, obj, 2, &element) == JS_FALSE)
				return ReturnString(cx, "z _ z", rval);
			if(JS_ValueToDouble(cx, element, &center) == JS_FALSE)
				return ReturnString(cx, "z _ q1", rval);
			float y = (float)center;
			fwrite(&y, sizeof(float), 1, pObjectFile);
		}
		
		*rval = JS_BooleanToValue(JS_TRUE);
		
		return JS_TRUE; 
	} else {
		return JS_FALSE; 
	}
}

//FlashCS5extension.WriteDynamic(라이브러리 다이나믹들)
JSBool WriteDynamic(JSContext *cx, JSObject *obj, unsigned int argc, jsval *argv, jsval *rval) {
    if(argc != 1)
        return JS_FALSE;
	
	if(pObjectFile) {
		JSObject* dynamicObjs;
		if(JS_ValueToObject(cx, argv[0], &dynamicObjs) == JS_FALSE)
			return ReturnString(cx, "q _ 1", rval);
		
		unsigned int dynamicLen = (unsigned int)JS_GetArrayLength(cx, dynamicObjs);
		if(dynamicLen == -1)
			return ReturnString(cx, "q _ 2", rval);
		
		fwrite(&dynamicLen, sizeof(unsigned int), 1, pObjectFile);
		
		int i, j, m, n;
		for(i = 0; i < dynamicLen; i++) {
			jsval posDynamic;
			if(JS_GetElement(cx, dynamicObjs, i, &posDynamic) == JS_FALSE)
				return ReturnString(cx, "q _ 3", rval);
			
			JSObject* dynamicObj;
			if(JS_ValueToObject(cx, posDynamic, &dynamicObj) == JS_FALSE)
				return ReturnString(cx, "q _ 4", rval);
			
			jsval element;
			
			//라이브러리 네임
			if(JS_GetElement(cx, dynamicObj, 0, &element) == JS_FALSE)
				return ReturnString(cx, "z _ 4", rval);
			
			unsigned int libNameLen;
			unsigned short* libName = JS_ValueToString(cx, element, &libNameLen);
			if(libName == NULL)
				return ReturnString(cx, "q _ 5", rval);
			
			char* libNameAscii = StringToAscii(libName, libNameLen);
			if(libNameAscii == NULL)
				return ReturnString(cx, "q _ 6", rval);
			unsigned int libID = PushLibraryName(libNameAscii);
			fwrite(&libID, sizeof(unsigned int), 1, pObjectFile);
			free(libNameAscii);
			
			
			//프레임
			JSObject* frame;
			if(JS_GetElement(cx, dynamicObj, 1, &element) == JS_FALSE)
				return ReturnString(cx, "q _ 7", rval);
			if(JS_ValueToObject(cx, element, &frame) == JS_FALSE)
				return ReturnString(cx, "q _ 8", rval);
			
			//프레임 길이
			unsigned int frameLen = (unsigned int)JS_GetArrayLength(cx, frame);
			if(frameLen == -1)
				return ReturnString(cx, "q _ 9", rval);
			fwrite(&frameLen, sizeof(unsigned int), 1, pObjectFile);
			
			for(j = 0; j < frameLen; j++) {
				jsval posFrame;
				if(JS_GetElement(cx, frame, j, &posFrame) == JS_FALSE)
					return ReturnString(cx, "q _ 10", rval);
				
				JSObject* frameObj;
				if(JS_ValueToObject(cx, posFrame, &frameObj) == JS_FALSE)
					return ReturnString(cx, "q _ 11", rval);
				
				//한프레임당 오브젝트 갯수
				unsigned int depthLen = (unsigned int)JS_GetArrayLength(cx, frameObj);
				if(depthLen == -1)
					return ReturnString(cx, "q _ 12", rval);
				fwrite(&depthLen, sizeof(unsigned int), 1, pObjectFile);
				
				for(m = 0; m < depthLen; m++) {
					jsval posDepth;
					if(JS_GetElement(cx, frameObj, m, &posDepth) == JS_FALSE)
						return ReturnString(cx, "q _ 13", rval);
					
					JSObject* depthObj;
					if(JS_ValueToObject(cx, posDepth, &depthObj) == JS_FALSE)
						return ReturnString(cx, "q _ 14", rval);
					
					jsval depthElement;
					
					//라이브러리 네임
					if(JS_GetElement(cx, depthObj, 0, &depthElement) == JS_FALSE)
						return ReturnString(cx, "a _ 1", rval);
					
					unsigned int depthLibNameLen;
					unsigned short* depthLibName = JS_ValueToString(cx, depthElement, &depthLibNameLen);
					if(depthLibName == NULL)
						return ReturnString(cx, "a _ 2", rval);
					
					char* depthLibNameAscii = StringToAscii(depthLibName, depthLibNameLen);
					if(depthLibNameAscii == NULL)
						return ReturnString(cx, "a _ 3", rval);
					unsigned int depthlibID = PushLibraryName(depthLibNameAscii);
					fwrite(&depthlibID, sizeof(unsigned int), 1, pObjectFile);
					free(depthLibNameAscii);
					
					//인스턴스 네임
					if(JS_GetElement(cx, depthObj, 1, &depthElement) == JS_FALSE)
						return ReturnString(cx, "a _ 4", rval);
					
					unsigned int depthNameLen;
					unsigned short* depthName = JS_ValueToString(cx, depthElement, &depthNameLen);
					if(depthName == NULL)
						return ReturnString(cx, "a _ 5", rval);
					
					char* depthNameAscii = StringToAscii(depthName, depthNameLen);
					if(depthNameAscii == NULL)
						return ReturnString(cx, "a _ 6", rval);
					unsigned int depthID = PushInstanceName(depthNameAscii);
					fwrite(&depthID, sizeof(unsigned int), 1, pObjectFile);
					free(depthNameAscii);
					
					//매트릭스
					if(JS_GetElement(cx, depthObj, 2, &depthElement) == JS_FALSE)
						return ReturnString(cx, "a _ 7", rval);
					
					JSObject* matObj;
					if(JS_ValueToObject(cx, depthElement, &matObj) == JS_FALSE)
						return ReturnString(cx, "a _ 8", rval);
					
					long matLen = JS_GetArrayLength(cx, matObj);
					if(matLen != 9)
						return ReturnString(cx, "a _ 9", rval);
					
					for(n = 0; n < matLen; n++) {
						jsval posMat;
						if(JS_GetElement(cx, matObj, n, &posMat) == JS_FALSE)
							return ReturnString(cx, "a _ 10", rval);
						
						double mat;
						if(JS_ValueToDouble(cx, posMat, &mat) == JS_FALSE)
							return ReturnString(cx, "a _ 11", rval);
						float fmat = (float)mat;
						fwrite(&fmat, sizeof(float), 1, pObjectFile);
					}
					
					//칼라
					if(JS_GetElement(cx, depthObj, 3, &depthElement) == JS_FALSE)
						return ReturnString(cx, "a _ 12", rval);
					
					JSObject* colorObj;
					if(JS_ValueToObject(cx, depthElement, &colorObj) == JS_FALSE)
						return ReturnString(cx, "a _ 13", rval);
					
					long colorLen = JS_GetArrayLength(cx, colorObj);
					if(colorLen != 4)
						return ReturnString(cx, "a _ 14", rval);
					
					for(n = 0; n < colorLen; n++) {
						jsval posColor;
						if(JS_GetElement(cx, colorObj, n, &posColor) == JS_FALSE)
							return ReturnString(cx, "a _ 15", rval);
						
						long color;
						if(JS_ValueToInteger(cx, posColor, &color) == JS_FALSE)
							return ReturnString(cx, "a _ 16", rval);
						unsigned char ucolor = (unsigned char)color;
						fwrite(&ucolor, sizeof(unsigned char), 1, pObjectFile);
					}
				}
			}
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
    FILE* file = fopen("/test111", "r");
    if(file) {
        char tmpstr[100] = "";
        fread(tmpstr, 100, 1, file);
        fclose(file);
        file = 0;
        remove("/test111");
        return ReturnString(cx, tmpstr, rval);
    } else {
		*rval = JS_BooleanToValue(JS_FALSE);
		
        return JS_FALSE;
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







