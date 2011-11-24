#include "VBCExternalForPhotoshop.h"
#include "SoSharedLibDefs.h"
#include <iostream>
#import <Foundation/Foundation.h>

FILE* pUVFile = NULL;

VBCExternalForPhotoshop_API long OpenUVFile(TaggedData* argv, long argc, TaggedData* retval)
{
	if(argc != 1)
	{
		return kESErrBadArgumentList;
	}
	
	if(argv[0].type != kTypeString)
	{
		return kESErrBadArgumentList;
	}
	
	if(pUVFile == NULL) {
		pUVFile = fopen(argv[0].data.string, "w");
	}
	
	return kESErrOK;
}

VBCExternalForPhotoshop_API long CloseUVFile(TaggedData* argv, long argc, TaggedData* retval)
{
	if(argc != 0)
	{
		return kESErrBadArgumentList;
	}
	
	if(pUVFile) {
		fclose(pUVFile);
		pUVFile = NULL;
	}
	
	return kESErrOK;
}

VBCExternalForPhotoshop_API long WriteUVName(TaggedData* argv, long argc, TaggedData* retval)
{
	if(argc != 1)
	{
		return kESErrBadArgumentList;
	}
	
	if(argv[0].type != kTypeString)
	{
		return kESErrBadArgumentList;
	}
	
	if(pUVFile) {
		char* UVName = argv[0].data.string;
		long len = strlen(UVName);
		fwrite(&len, sizeof(long), 1, pUVFile);
		fwrite(UVName, sizeof(char), len, pUVFile);
	}
	
	return kESErrOK;
} 

VBCExternalForPhotoshop_API long WriteUVInt(TaggedData* argv, long argc, TaggedData* retval)
{
	if(argc != 1)
	{
		return kESErrBadArgumentList;
	}
    
	if(pUVFile) {
		int UVInt = (int)argv[0].data.fltval;
		fwrite(&UVInt, sizeof(int), 1, pUVFile);
	}
	
	return kESErrOK;
}
VBCExternalForPhotoshop_API long WriteUVFloat(TaggedData* argv, long argc, TaggedData* retval)
{
	if(argc != 1)
	{
		return kESErrBadArgumentList;
	}
    
	if(pUVFile) {
		float UVFloat = (float)argv[0].data.fltval;
		fwrite(&UVFloat, sizeof(float), 1, pUVFile);
	}
	
	return kESErrOK;
}

VBCExternalForPhotoshop_API long OpenFlashAndSync(TaggedData* argv, long argc, TaggedData* retval)
{
	if(argc != 1)
	{
		return kESErrBadArgumentList;
	}
    
	NSDictionary* error;
    NSString* str = [NSString stringWithCString:argv[0].data.string encoding:NSUTF8StringEncoding];
    NSAppleScript* nsap = [[NSAppleScript alloc] initWithSource:str];
    [nsap executeAndReturnError:&error];
    [nsap release];
    
	return kESErrOK;
}

VBCExternalForPhotoshop_API long GetFileName(TaggedData* argv, long argc, TaggedData* retval) 
{
    if(argc != 1)
	{
		return kESErrBadArgumentList;
	}
    
    FILE* name = fopen("/VBEngine/tmp/photoshopPSDName", "w");
    int nameLength = strlen(argv[0].data.string);
    fwrite(&nameLength, 1, sizeof(int), name);
    fwrite(argv[0].data.string, nameLength, sizeof(char), name);
    fclose(name);
	
	return kESErrOK;
}

VBCExternalForPhotoshop_API long ESGetVersion()
{
	return 0x1;
}

VBCExternalForPhotoshop_API char* ESInitialize (const TaggedData ** argv, long argc) 
{ 
	return (char*)"OpenUVFile,CloseUVFile,WriteUVName,WriteUVInt,WriteUVFloat,OpenFlashAndSync";
}

VBCExternalForPhotoshop_API void ESTerminate()
{
	
}

VBCExternalForPhotoshop_API void* ESMallocMem (size_t nBytes)
{
	void* p = malloc(nBytes);
	return p ;
}

VBCExternalForPhotoshop_API void ESFreeMem (void* p)
{ 
	delete (char*)(p);
}