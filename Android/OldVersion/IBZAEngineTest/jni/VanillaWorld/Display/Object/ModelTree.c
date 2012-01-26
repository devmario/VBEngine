#include "Model.h"
#include <stdlib.h>

void ModelPlay(Model* model) {
	if(model->ani) {
		model->ani->aniIsPlay = true;
		model->ani->aniIsUpdateFrame = true;
	}
}

void ModelGoToAndPlay(Model* model, int frame) {
	if(model->ani) {
		if(frame >= 0 && frame < model->ani->aniTotalFrame)
			model->ani->aniCurFrame = frame;
		ModelPlay(model);
	}
}

void ModelStop(Model* model) {
	if(model->ani) {
		model->ani->aniIsPlay  = false;
		model->ani->aniIsUpdateFrame = true;
	}
}

void ModelGoToAndStop(Model* model, int frame) {
	if(model->ani) {
		if(frame >= 0 && frame < model->ani->aniTotalFrame)
			model->ani->aniCurFrame = frame;
		ModelStop(model);
	}
}

void ModelSetIsLoop(Model* model, bool isLoop) {
	if(model->ani) {
		model->ani->aniIsLoop = isLoop;
	}
}

Model* ModelGetChildWithInstanceID(Model* model, unsigned int instanceID) {
	int i, j;
	if(model->ani) {
		for(i = 0; i < model->ani->aniTotalFrame; i++) {
			for(j = 0; j < model->ani->aniChildLength[i]; j++) {
				Model* child = model->ani->aniChild[i][j];
				if(child->ani->instanceID == instanceID) {
					return child;
				} else {
					Model* inChild = ModelGetChildWithInstanceID(child, instanceID);
					if(inChild)
						return inChild;
				}
			}
		}
	}
	return NULL;
}

#pragma mark Model에 Model 붙히기

bool ModelAdd(Model* model, Model* child) {
	return ModelAddAt(model, child, model->child->length);
}

bool ModelAddAt(Model* model, Model* child, unsigned int index) {
	if(!child->parent) {
		child->parent = model;
		ArrayPushObjectAtIndex(model->child, child, index);
		if(model->hasMask) {
			ModelSetMaskDetail(child, NULL, model->maskDepth);
		}
	}
	return true;
}

#pragma mark -
#pragma mark 붙어있는 Model 제거하기

bool ModelRemove(Model* model, Model* child) {
	if(child->parent) {
		ArrayPopObject(model->child, child);
		if(child->hasMask) {
			ModelRemoveMaskDetail(child, NULL);
		}
		child->parent = NULL;
	}
	return true;
}

Model* ModelRemoveAt(Model* model, unsigned int index) {
	Model* child = ArrayObjectAtIndex(model->child, index);
	if(child) {
		ArrayPopObjectAtIndex(model->child, index);
		if(child->hasMask) {
			ModelRemoveMaskDetail(child, NULL);
		}
		child->parent = NULL;
		return child;
	}
	return NULL;
}

#pragma mark -
#pragma mark Child Model, Parent Model

bool ModelIsChild(Model* model, Model* child) {
	return ArrayIndexAtObject(model->child, child) != -1;
}

Model* ModelGetChildAt(Model* model, unsigned int index) {
	return ArrayObjectAtIndex(model->child, index);
}

signed long ModelGetAtChild(Model* model, Model* child) {
	return ArrayIndexAtObject(model->child, child);
}

unsigned int ModelGetChildLength(Model* model) {
	return model->child->length;
}

Model* ModelGetParent(Model* model) {
	return model->parent;
}

void ModelSwapDepth(Model* parent, Model* child, unsigned int index) {
	ArrayPopObject(parent->child, child);
	ArrayPushObjectAtIndex(parent->child, child, index);
}
