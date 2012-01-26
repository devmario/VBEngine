#ifndef JNI_ASSET_FILE_LIST_H_INCLUDED
#define JNI_ASSET_FILE_LIST_H_INCLUDED

#define __Android__

/*
 *  list.h
 *  C List
 *
 *  Created by donny on 11. 1. 13..
 *  Copyright 2011 Vanilla Breeze. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  

typedef struct FileList FileList;
typedef struct FileInfo FileInfo;

FileList* fileList;

struct FileList {
	int size;
	FileInfo* first;
};

struct FileInfo {
	char* path;
	void* fptr;
	int indx;
	int fd;
	long off;
	long leng;
	FileInfo* next;
};

FileList* getFileListInstance();
FileInfo* getFileInfoInstance();
int addFileInfo(FileList* list, FileInfo* fileinfo);
FileInfo* getFileInfo(FileList* list, int indx);
int freeFileList(FileList* list);
FileInfo* searchFileInfo(FileList* list, const char* path);
FileInfo* searchFileInfoFPtr(FileList* list, void* fptr);

FILE* fopen_Android(const char* path, const char* mode, long* offset, long* length);
void fclose_Android(FILE* file);

#endif