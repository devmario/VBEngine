#include "ObjFileForModel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PNGDecoder.h"

unsigned int ObjectFileFindLibraryIDWithName(ObjectFile* of, char* name) {
	int i;
	for(i = 0; i < ArrayLength(of->library_name_id); i++) {
		_NameID* name_id = ArrayObjectAtIndex(of->library_name_id, i);
		if(strcmp(name_id->name, name) == 0) {
			return name_id->id;
		}
	}
	return 0;
}

char* ObjectFileFindLibraryNameWithID(ObjectFile* of, unsigned int lib_id) {
	int i;
	for(i = 0; i < ArrayLength(of->library_name_id); i++) {
		_NameID* name_id = ArrayObjectAtIndex(of->library_name_id, i);
		if(name_id->id == lib_id) {
			return name_id->name;
		}
	}
	return NULL;
}

unsigned int ObjectFileFindInstanceIDWithName(ObjectFile* of, char* name) {
	int i;
	for(i = 0; i < ArrayLength(of->instance_name_id); i++) {
		_NameID* name_id = ArrayObjectAtIndex(of->instance_name_id, i);
		if(strcmp(name_id->name, name) == 0) {
			return name_id->id;
		}
	}
	return 0;
}

char* ObjectFileFindInstanceNameWithID(ObjectFile* of, unsigned int lib_id) {
	int i;
	for(i = 0; i < ArrayLength(of->instance_name_id); i++) {
		_NameID* name_id = ArrayObjectAtIndex(of->instance_name_id, i);
		if(name_id->id == lib_id) {
			return name_id->name;
		}
	}
	return NULL;
}

Symbol* ObjectFileFindSymbolWithID(ObjectFile* of, unsigned int lib_id) {
	int i;
	for(i = 0; i < ArrayLength(of->symbol); i++) {
		Symbol* sym = ArrayObjectAtIndex(of->symbol, i);
		if(sym->lib_id == lib_id) {
			return sym;
		}
	}
	return NULL;
}

Symbol* ObjectFileFindSymbolWithName(ObjectFile* of, char* name) {
	unsigned int lib_id = ObjectFileFindLibraryIDWithName(of, name);
	return ObjectFileFindSymbolWithID(of, lib_id);
}

MovieClip* ObjectFileFindMovieClipWithID(ObjectFile* of, unsigned int lib_id) {
	int i;
	for(i = 0; i < ArrayLength(of->movie_clip); i++) {
		MovieClip* mc = ArrayObjectAtIndex(of->movie_clip, i);
		if(mc->lib_id == lib_id) {
			return mc;
		}
	}
	return NULL;
}

MovieClip* ObjectFileFindMovieClipWithName(ObjectFile* of, char* name) {
	unsigned int lib_id = ObjectFileFindLibraryIDWithName(of, name);
	return ObjectFileFindMovieClipWithID(of, lib_id);
}

void ReadNameID(FILE* fp, Array* nameIDArr) {
	int i;
	unsigned int id_len;
	fread(&id_len, sizeof(unsigned int), 1, fp);
	for(i = 0; i < id_len; i++) {
		unsigned int name_len;
		fread(&name_len, sizeof(unsigned int), 1, fp);
		char* name = calloc(name_len + 1, sizeof(char));
		fread(name, sizeof(char), name_len, fp);
		_NameID* name_id = malloc(sizeof(_NameID));
		name_id->name = name;
		unsigned int id;
		fread(&id, sizeof(unsigned int), 1, fp);
		name_id->id = id;
		ArrayPushObject(nameIDArr, name_id);
	}
}

void ReadFileImageAndUV(FILE* fp, ObjectFile* of) {
	ReadNameID(fp, of->library_name_id);
	ReadNameID(fp, of->instance_name_id);
	
	unsigned int len;
	fread(&len, sizeof(unsigned int), 1, fp);
	
	of->t_id_len = len;
	of->t_id = calloc(len, sizeof(GLuint));
	
	glEnable(GL_TEXTURE_2D);
	glGenTextures(len, of->t_id);
	int i;
	for(i = 0; i < len; i++) {
		int pngSize;
		fread(&pngSize, sizeof(int), 1, fp);
		glBindTexture(GL_TEXTURE_2D, of->t_id[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		unsigned long width, height;
		unsigned char c, b;
		GLubyte* data = PNGReader(fp, pngSize, &width, &height, &c, &b);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		free(data);
		
		unsigned int uvCount;
		fread(&uvCount, sizeof(unsigned int), 1, fp);
		
		int j;
		for(j = 0; j < uvCount; j++) {
			Symbol* sym = calloc(1, sizeof(Symbol));
			unsigned int lib_id;
			fread(&lib_id, sizeof(unsigned int), 1, fp);
			sym->lib_id = lib_id;
			int x, y, w, h;
			fread(&x, sizeof(int), 1, fp);
			fread(&y, sizeof(int), 1, fp);
			fread(&w, sizeof(int), 1, fp);
			fread(&h, sizeof(int), 1, fp);
			
			x -= 1;
			y -= 1;
			w += 2;
			h += 2;
			
			sym->t_id = of->t_id[i];
			
			sym->vtx[0] = Vector3DInit(0.0, 0.0, 0.0);
			sym->vtx[1] = Vector3DInit((float)w, 0.0, 0.0);
			sym->vtx[2] = Vector3DInit(0.0, (float)h, 0.0);
			sym->vtx[3] = Vector3DInit((float)w, (float)h, 0.0);
			
			sym->txr[0] = Vector2DInit((float)x / (float)width, (float)y / (float)height);
			sym->txr[1] = Vector2DInit(((float)x + (float)w) / (float)width, (float)y / (float)height);
			sym->txr[2] = Vector2DInit((float)x / (float)width, ((float)y + (float)h) / (float)height);
			sym->txr[3] = Vector2DInit(((float)x + (float)w) / (float)width, ((float)y + (float)h) / (float)height);
			
			ArrayPushObject(of->symbol, sym);
		}
	}
}

void ReadFileSymbol(FILE* fp, ObjectFile* of) {
	int symLen;
	fread(&symLen, sizeof(int), 1, fp);

	int i;
	for(i = 0; i < symLen; i++) {
		unsigned int lib_id;
		fread(&lib_id, sizeof(unsigned int), 1, fp);
		
		Symbol* sym = ObjectFileFindSymbolWithID(of, lib_id);
		
		Vector2D center;
		fread(&center, sizeof(float), 2, fp);
		
		sym->vtx[0].x += center.x;
		sym->vtx[1].x += center.x;
		sym->vtx[2].x += center.x;
		sym->vtx[3].x += center.x;
		
		sym->vtx[0].y += center.y;
		sym->vtx[1].y += center.y;
		sym->vtx[2].y += center.y;
		sym->vtx[3].y += center.y;
	}
}

void ReadFileMovieClip(FILE* fp, ObjectFile* of) {
	unsigned int mcLen;
	fread(&mcLen, sizeof(unsigned int), 1, fp);
	
	int i, j, m;
	for(i = 0; i < mcLen; i++) {
		MovieClip* mc = calloc(1, sizeof(MovieClip));
		
		unsigned int lib_id;
		fread(&lib_id, sizeof(unsigned int), 1, fp);
		mc->lib_id = lib_id;
		mc->frame = ArrayInit();
		
		unsigned int frameCount;
		fread(&frameCount, sizeof(unsigned int), 1, fp);
		
		
		for(j = 0; j < frameCount; j++) {
			MCFrame* frame = calloc(1, sizeof(MCFrame));
			frame->element = ArrayInit();
			
			unsigned int depthCount;
			fread(&depthCount, sizeof(unsigned int), 1, fp);
			
			for(m = 0; m < depthCount; m++) {
				MCElement* element = calloc(1, sizeof(MCElement));
				
				unsigned int _lib_id;
				fread(&_lib_id, sizeof(unsigned int), 1, fp);
				element->lib_id = _lib_id;
				
				unsigned int _instance_id;
				fread(&_instance_id, sizeof(unsigned int), 1, fp);
				element->instance_id = _instance_id;
				
				float mat[9];
				fread(mat, sizeof(float), 9, fp);
				element->mat = Matrix3DLoadIdentity();
				element->mat.m11 = mat[0];
				element->mat.m21 = mat[1];
				element->mat.m41 = mat[2];
				element->mat.m12 = mat[3];
				element->mat.m22 = mat[4];
				element->mat.m42 = mat[5];
				element->mat.m14 = mat[6];
				element->mat.m24 = mat[7];
				element->mat.m44 = mat[8];
				
				unsigned char color[4];
				fread(color, sizeof(unsigned char), 4, fp);
				element->color.r = color[0];
				element->color.g = color[1];
				element->color.b = color[2];
				element->color.a = color[3];
				
				ArrayPushObject(frame->element, element);
			}
			ArrayPushObject(mc->frame, frame);
		}
		ArrayPushObject(of->movie_clip, mc);
	}
	
}

ObjectFile* ObjectFileLoad(const char* path) {
	ObjectFile* of = calloc(1, sizeof(ObjectFile));
	
	of->library_name_id = ArrayInit();
	of->instance_name_id = ArrayInit();
	of->symbol = ArrayInit();
	of->movie_clip = ArrayInit();
	
	FILE* fp = fopen(path, "r");
	ReadFileImageAndUV(fp, of);
	ReadFileSymbol(fp, of);
	ReadFileMovieClip(fp, of);
	fclose(fp);
	
	return of;
}

void ObjectFileFree(ObjectFile** of) {
	while(ArrayLength(of[0]->movie_clip)) {
		MovieClip* mc = ArrayPopObjectAtIndex(of[0]->movie_clip, 0);
		while(ArrayLength(mc->frame)) {
			MCFrame* frame = ArrayPopObjectAtIndex(mc->frame, 0);
			while(ArrayLength(frame->element)) {
				MCElement* element = ArrayPopObjectAtIndex(frame->element, 0);
				free(element);
			}
			ArrayFree(&frame->element);
			free(frame);
		}
		ArrayFree(&mc->frame);
		free(mc);
	}
	ArrayFree(&of[0]->movie_clip);
	
	while(ArrayLength(of[0]->symbol)) {
		Symbol* sym = ArrayPopObjectAtIndex(of[0]->symbol, 0);
		free(sym);
	}
	ArrayFree(&of[0]->symbol);
	
	while(ArrayLength(of[0]->instance_name_id)) {
		_NameID* name_id = ArrayPopObjectAtIndex(of[0]->instance_name_id, 0);
		free(name_id->name);
		free(name_id);
	}
	ArrayFree(&of[0]->instance_name_id);
	
	while(ArrayLength(of[0]->library_name_id)) {
		_NameID* name_id = ArrayPopObjectAtIndex(of[0]->library_name_id, 0);
		free(name_id->name);
		free(name_id);
	}
	ArrayFree(&of[0]->library_name_id);
	
	free(of[0]);
	of[0] = NULL;
}

Model* MakeModelWithSymbol(Symbol* symbol) {
	Model* model = calloc(1, sizeof(Model));
	model->ani = calloc(1, sizeof(ModelAni));
	ModelInitWithVertex(model, 4, symbol->vtx, NULL, symbol->txr, 0, NULL, symbol->t_id);
	model->ani->libraryID = symbol->lib_id;
	return model;
}

Model* ObjectFileMakeModelWithSymbolID(ObjectFile* of, unsigned int lib_id) {
	Symbol* symbol = ObjectFileFindSymbolWithID(of, lib_id);
	return MakeModelWithSymbol(symbol);
}

Model* ObjectFileMakeModelWithSymbolName(ObjectFile* of, char* name) {
	Symbol* symbol = ObjectFileFindSymbolWithName(of, name);
	return MakeModelWithSymbol(symbol);
}

typedef struct {
	unsigned int instance_id;
	Model* model;
} InstanceModel;

Model* ObjectFileMakeModelWithMovieClip(ObjectFile* of, MovieClip* mc) {
	Model* model = calloc(1, sizeof(Model));
	ModelInitDefault(model);
	model->ani = calloc(1, sizeof(ModelAni));
	model->ani->libraryID = mc->lib_id;
	int i, j;
	
	model->ani->aniCurFrame = 0;
	model->ani->aniTotalFrame = ArrayLength(mc->frame);
	
	model->ani->aniChildLength = calloc(ArrayLength(mc->frame), sizeof(unsigned int));
	model->ani->aniChild = calloc(ArrayLength(mc->frame), sizeof(Model**));
	model->ani->aniMat = calloc(ArrayLength(mc->frame), sizeof(Matrix3D*));
	model->ani->aniColor = calloc(ArrayLength(mc->frame), sizeof(ColorRGBA*));
	
	Array* instance = ArrayInit();
	for(i = 0; i < ArrayLength(mc->frame); i++) {
		MCFrame* frame = ArrayObjectAtIndex(mc->frame, i);
		
		model->ani->aniChildLength[i] = ArrayLength(frame->element);
		model->ani->aniChild[i] = calloc(ArrayLength(frame->element), sizeof(Model*));
		model->ani->aniMat[i] = calloc(ArrayLength(frame->element), sizeof(Matrix3D));
		model->ani->aniColor[i] = calloc(ArrayLength(frame->element), sizeof(ColorRGBA));
		
		for(j = 0; j < ArrayLength(frame->element); j++) {
			MCElement* element = ArrayObjectAtIndex(frame->element, j);
			signed long index = -1;
			int q;
			for(q = 0; q < ArrayLength(instance); q++) {
				InstanceModel* im = ArrayObjectAtIndex(instance, q);
				if(im->instance_id == element->instance_id) {
					index = q;
				}
			}
			if(index < 0) {
				Model* child = ObjectFileMakeModelWithLibraryID(of, element->lib_id);
				child->ani->instanceID = element->instance_id;
				model->ani->aniChild[i][j] = child;
				InstanceModel* im = calloc(1, sizeof(InstanceModel));
				im->instance_id = element->instance_id;
				im->model = child;
				ArrayPushObject(instance, im);
			} else {
				InstanceModel* im = ArrayObjectAtIndex(instance, index);
				model->ani->aniChild[i][j] = im->model;
			}
			
			model->ani->aniMat[i][j] = element->mat;
			model->ani->aniColor[i][j] = element->color;
		}
	}
	while(ArrayLength(instance)) {
		InstanceModel* im = ArrayPopObjectAtIndex(instance, 0);
		free(im);
	}
	ArrayFree(&instance);
	
	model->ani->aniIsUpdateFrame = true;
	return model;
}

Model* ObjectFileMakeModelWithMovieClipID(ObjectFile* of, unsigned int lib_id) {
	MovieClip* mc = ObjectFileFindMovieClipWithID(of, lib_id);
	return ObjectFileMakeModelWithMovieClip(of, mc);
}

Model* ObjectFileMakeModelWithMovieClipName(ObjectFile* of, char* name) {
	MovieClip* mc = ObjectFileFindMovieClipWithName(of, name);
	return ObjectFileMakeModelWithMovieClip(of, mc);
}

Model* ObjectFileMakeModelWithLibraryID(ObjectFile* of, unsigned int lib_id) {
	Symbol* sym = ObjectFileFindSymbolWithID(of, lib_id);
	if(sym) {
		return MakeModelWithSymbol(sym);
	} else {
		MovieClip* mc = ObjectFileFindMovieClipWithID(of, lib_id);
		if(mc) {
			return ObjectFileMakeModelWithMovieClip(of, mc);
		} else {
			return NULL;
		}
	}
}

Model* ObjectFileMakeModelWithLibraryName(ObjectFile* of, char* name) {
	Symbol* sym = ObjectFileFindSymbolWithName(of, name);
	if(sym) {
		return MakeModelWithSymbol(sym);
	} else {
		MovieClip* mc = ObjectFileFindMovieClipWithName(of, name);
		if(mc) {
			return ObjectFileMakeModelWithMovieClip(of, mc);
		} else {
			return NULL;
		}
	}
}

void ObjectFileMadeMovieClipFree(Model** model) {
	Array* childStack= ArrayInit();
	
	int i, j;
	if(model[0]->ani) {
		for(i = 0; i < model[0]->ani->aniTotalFrame; i++) {
			for(j = 0; j < model[0]->ani->aniChildLength[i]; j++) {
				signed long index = ArrayIndexAtObject(childStack, model[0]->ani->aniChild[i][j]);
				if(index < 0) {
					ArrayPushObject(childStack, model[0]->ani->aniChild[i][j]);
				}
			}
			if(model[0]->ani->aniChild[i])
				free(model[0]->ani->aniChild[i]);
			if(model[0]->ani->aniMat[i])
				free(model[0]->ani->aniMat[i]);
			if(model[0]->ani->aniColor[i])
				free(model[0]->ani->aniColor[i]);
		}
		if(model[0]->ani->aniChildLength)
			free(model[0]->ani->aniChildLength);
		if(model[0]->ani->aniChild)
			free(model[0]->ani->aniChild);
		if(model[0]->ani->aniMat)
			free(model[0]->ani->aniMat);
		if(model[0]->ani->aniColor)
			free(model[0]->ani->aniColor);
		free(model[0]->ani);
	}
	
	while (ArrayLength(childStack)) {
		Model* _child = ArrayPopObjectAtIndex(childStack, 0);
		ObjectFileMadeMovieClipFree(&_child);
	}
	
	ModelFree(model[0]);
	free(model[0]);
	model[0] = NULL;
	
	ArrayFree(&childStack);
}

Model* ModelGetChildWithInstanceName(Model* model, ObjectFile* of, const char* name) {
	unsigned int name_id = ObjectFileFindInstanceIDWithName(of, name);
	return ModelGetChildWithInstanceID(model, name_id);
}



