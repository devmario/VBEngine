#ifndef __ObjFileForModel_H__
#define __ObjFileForModel_H__

#ifdef ___IPHONE___
#include <OpenGLES/ES1/gl.h>
#endif
#ifdef ___MAC___
#include <OpenGL/OpenGL.h>
#endif

#include "Model.h"
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct Symbol Symbol;
	typedef struct MovieClip MovieClip;
	typedef struct MCFrame MCFrame;
	typedef struct MCElement MCElement;
	typedef struct _NameID _NameID;
	typedef struct ObjectFile ObjectFile;
	
	typedef unsigned int LibraryID;
	typedef unsigned int InstanceID;
	
	struct Symbol {
		LibraryID lib_id;
		GLuint t_id;
		Vector3D vtx[4];
		Vector2D txr[4];
	};
	
	struct MovieClip {
		LibraryID lib_id;
		Array* frame;
	};
	
	struct MCFrame {
		Array* element;
	};
	
	struct MCElement {
		unsigned int lib_id;
		unsigned int instance_id;
		Matrix3D mat;
		ColorRGBA color;
	};
	
	struct _NameID {
		char* name;
		unsigned int id;
	};
	
	struct ObjectFile {
		unsigned int t_id_len;
		GLuint* t_id;
		
		Array* library_name_id;
		Array* instance_name_id;
		
		Array* symbol;
		Array* movie_clip;
	};
	
	ObjectFile* ObjectFileLoad(const char* path);
	void ObjectFileFree(ObjectFile** of);
	
	unsigned int ObjectFileFindLibraryIDWithName(ObjectFile* of, char* name);
	char* ObjectFileFindLibraryNameWithID(ObjectFile* of, unsigned int lib_id);
	
	unsigned int ObjectFileFindInstanceIDWithName(ObjectFile* of, char* name);
	char* ObjectFileFindInstanceNameWithID(ObjectFile* of, unsigned int lib_id);
	
	Symbol* ObjectFileFindSymbolWithID(ObjectFile* of, unsigned int lib_id); 
	Symbol* ObjectFileFindSymbolWithName(ObjectFile* of, char* name);
	
	MovieClip* ObjectFileFindMovieClipWithID(ObjectFile* of, unsigned int lib_id); 
	MovieClip* ObjectFileFindMovieClipWithName(ObjectFile* of, char* name);
	
	Model* MakeModelWithSymbol(Symbol* symbol);
	Model* ObjectFileMakeModelWithSymbolID(ObjectFile* of, unsigned int lib_id);
	Model* ObjectFileMakeModelWithSymbolName(ObjectFile* of, char* name);
	
	Model* ObjectFileMakeModelWithMovieClip(ObjectFile* of, MovieClip* mc);
	Model* ObjectFileMakeModelWithMovieClipID(ObjectFile* of, unsigned int lib_id);
	Model* ObjectFileMakeModelWithMovieClipName(ObjectFile* of, char* name);
	
	Model* ObjectFileMakeModelWithLibraryID(ObjectFile* of, unsigned int lib_id);
	Model* ObjectFileMakeModelWithLibraryName(ObjectFile* of, char* name);

	void ObjectFileMadeMovieClipFree(Model** model);
	Model* ModelGetChildWithInstanceName(Model* model, ObjectFile* of, const char* name);
	
#ifdef __cplusplus
}
#endif
#endif