#ifndef __PNG_Decoder_H__
#define __PNG_Decoder_H__

#include <stdio.h>

//열려진 PNG파일포인터와 읽어야 할사이즈를 주고, 이미지 사이즈, 칼라타입, 칼라비트, 비트맵데이터(메모리 생성됨)를 가져옴
//인자:열려진 파일포인터, 읽어야할 사이즈, 이미지넓이를 가져올 변수 포인터, 이미지높이를 가져올 변수 포인터, 이미지타입을 가져올 변수 포인터, 이미지 비트를 가져올 변수포인터
//리턴값:malloc된 비트맵 데이터
//참고사항1:8바이트RGBA로 된 PNG만 읽습니다.
//참고사항2:넘겨진 파일포인터는 읽은후에 PNG데이터가 끝나는위치까지 fseek합니다.
unsigned char* PNGReader(FILE* _fp, long _pngSize, unsigned long* _w, unsigned long* _h, unsigned char* _color, unsigned char* _bit);

#endif