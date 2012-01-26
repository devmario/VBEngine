#include "jni_asset_file_list.h"
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "test", __VA_ARGS__);



FileList* getFileListInstance() {
	FileList* list = (FileList*)malloc(sizeof(FileList));
	list->size = 0;
	list->first = NULL;
	return list;
}

FileInfo* getFileInfoInstance() {
	FileInfo* fileinfo = (FileInfo*)malloc(sizeof(FileInfo));
	fileinfo->indx = -1;
	fileinfo->fd = -1;
	fileinfo->off = -1;
	fileinfo->leng = -1;
	fileinfo->next = NULL;
	return fileinfo;
}

int addFileInfo(FileList* list, FileInfo* fileinfo) {
	if (list == NULL || fileinfo == NULL) {
		return 0;
	}
	int size = list->size;
	if (size > 0) {
		FileInfo* prevNode = getFileInfo(list, size-1);
		if (prevNode == NULL) {
			return 0;
			}
		
		prevNode->next = fileinfo;
	} else {
		list->first = fileinfo;
	}

	fileinfo->indx = size;
	fileinfo->next = NULL;
	list->size = size + 1;
	
	return 1;
}

FileInfo* getFileInfo(FileList* list, int indx) {
	if (list == NULL || list->size == 0) return NULL;
	if (list->size <= indx) return NULL;
	
	FileInfo* currNode = list->first;
	
	int currIndx;
	for (currIndx = 1; currIndx <= indx; currIndx++) {
		if (currNode == NULL) return NULL;
		
		FileInfo* nextNode = currNode->next;
		currNode = nextNode;
	}
	return currNode;
}

int freeFileList(FileList* list) {
	if (list == NULL) return 0;
	
	int indx;
	for (indx = list->size - 1; indx >= 0; indx--) {
		FileInfo* fileinfo = getFileInfo(list, indx);
		if (fileinfo != NULL){
			free(fileinfo->path);
			free(fileinfo);
		}
	}
	
	free(list);
}

FileInfo* searchFileInfo(FileList* list, const char* path) {
	int i;
	for(i = 0; i < list->size; i++) {
		FileInfo* info = getFileInfo(list, i);
//		LOGV("--- %s --- %s ---",info->path, path);
		if(strcmp(info->path, path) == 0) {
			return info;
		}
	}
	return 0;
}

FileInfo* searchFileInfoFPtr(FileList* list, void* fptr) {
	int i;
	for(i = 0; i < list->size; i++) {
		FileInfo* info = getFileInfo(list, i);
		if(info->fptr == fptr) {
			return info;
		}
	}
	return 0;
}

FILE* fopen_Android(const char* path, const char* mode, long* offset, long* length) {
	FILE* _fptr = NULL;
	int _fd = 0;
	FileInfo* _info = searchFileInfo(fileList, path);

//		LOGV("info %i", _info);
//		LOGV("path %s", _info->path);
	if(strcmp(_info->path, path) == 0) {
		_fd = dup(_info->fd);
//		LOGV("fd %i %i %i", _fd, _info->off, _info->leng);
		*offset = _info->off;
		*length = _info->leng;
	}
	_fptr = fdopen(_fd, mode);
	if (_fptr){
		_info->fptr = _fptr;
		fseek(_fptr, *offset, SEEK_SET);
	}
	return _fptr;
}

void fclose_Android(FILE* file) {
	FileInfo* _info = searchFileInfoFPtr(fileList,file);
	_info->fptr = NULL;
	fclose(file);
	close(_info->fd);
}
