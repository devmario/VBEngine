#include "PNGDecoder.h"
#include "png.h"
#include "Debug.h"
#include <stdlib.h>

unsigned char* PNGReader(FILE* _fp, long _pngSize, unsigned long* _w, unsigned long* _h, unsigned char* _color, unsigned char* _bit) {
	long pngArea;
	unsigned char header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;
	int y;
	
	pngArea = ftell(_fp) + _pngSize;
	
	fread(header, 1, 8, _fp);
	if(png_sig_cmp(header, 0, 8))
		DebugPrintAbort(true, "png파일이 아닙니다.");
	
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	if(!png_ptr)
		DebugPrintAbort(true, "png_create_read_struct 실패.");
	
	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
		DebugPrintAbort(true, "이미지의 정보를 불러올때 문제가 발생 했습니다.");
	
	if(setjmp(png_jmpbuf(png_ptr)))
		DebugPrintAbort(true, "이미지의 입출력에 문제가 발생 했습니다.");
	
	png_init_io(png_ptr, _fp);
	png_set_sig_bytes(png_ptr, 8);
	
	png_read_info(png_ptr, info_ptr);
	
	*_w = png_get_image_width(png_ptr, info_ptr);
	*_h = png_get_image_height(png_ptr, info_ptr);
	*_color = png_get_color_type(png_ptr, info_ptr);
	*_bit = png_get_bit_depth(png_ptr, info_ptr);
	
	number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);
	
	if(setjmp(png_jmpbuf(png_ptr)))
		DebugPrintAbort(true, "%s이미지를 읽는동안 문제가 발생 했습니다.");
    
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * *_h);
	for(y = 0; y < *_h; y++)
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
	
	png_read_image(png_ptr, row_pointers);
		
	unsigned char colorBit = (*_bit / 2);
	unsigned char* data = malloc(sizeof(unsigned char) * *_w * *_h * colorBit);
	unsigned char* dataPtr = data;
	for(y = 0; y < *_h; y++) {
		png_byte* row = row_pointers[y];
		long cpySize = sizeof(unsigned char) * *_w * colorBit;
		memcpy(dataPtr, row, cpySize);
		dataPtr += cpySize;
	}
	
	for(y = 0; y < *_h; y++)
		free(row_pointers[y]);
	free(row_pointers);
	
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	fseek(_fp, pngArea, SEEK_SET);
	
	return data;
}
