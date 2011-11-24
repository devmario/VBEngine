#ifndef __CAPIUtil_H__
#define __CAPIUtil_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//메모리 생성된 ascii로 리턴
char* StringToAscii(unsigned short* string, unsigned int len);

//파일에 파일쓰기(파일이 둘다 열려있어야 함)
void WriteFileToFile(FILE* wf, FILE* rf);

//string으로 파일 열기
FILE* OpenFileString(unsigned short* string, unsigned int len, const char* mode);

#endif
