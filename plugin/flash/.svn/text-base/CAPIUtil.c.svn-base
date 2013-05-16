#include "CAPIUtil.h"

//메모리 생성된 ascii로 리턴
char* StringToAscii(unsigned short* string, unsigned int len) {
	int i;
	char* ascii = calloc(len + 1, sizeof(char));
	for(i = 0; i < len; i++) {
		if(string[i] > 127) {
			free(ascii);
			return NULL;
		} else {
			ascii[i] = string[i];
		}
	}
	return ascii;
}

//파일에 파일쓰기(파일이 둘다 열려있어야 함)
void WriteFileToFile(FILE* wf, FILE* rf) {
	fseek(rf, 0, SEEK_END);
	long size = ftell(rf);
	fseek(rf, 0, SEEK_SET);
	fwrite(&size, sizeof(long), 1, wf);
	
	int endOfFile = 1;
	int bufSize = 0xFFF;
	char* buf = calloc(1, bufSize);
	while(endOfFile) {
		long result = fread(buf, 1, bufSize, rf);
		if(result == 0) {
			endOfFile = 0;
		} else if(result < 0) {
			break;
		} else {
			fwrite(buf, 1, result, wf);
		}
	}
	free(buf);
}

//string으로 파일 열기
FILE* OpenFileString(unsigned short* string, unsigned int len, const char* mode) {
	char* path = StringToAscii(string, len);
	if(path) {
		FILE* fp = fopen(path, mode);
		free(path);
		return fp;
	} else {
		return NULL;
	}
}