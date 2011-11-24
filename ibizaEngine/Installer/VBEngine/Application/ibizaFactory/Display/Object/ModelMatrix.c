#include "Model.h"
#include <math.h>

#pragma mark -
#pragma mark Model 매트릭스

bool ModelSetMatrix(Model* model, Matrix3D matrix) {
	*model->matrix = matrix;
	return true;
}

Matrix3D* ModelGetMatrix(Model* model) {
	return model->matrix;
}

Matrix3D* ModelMultyMatrix(Model* model, Matrix3D matrix) {
	*model->matrix = Matrix3DMultiply(*model->matrix, matrix);
	return model->matrix;
}

Matrix3D* ModelGetMatrixGlobal(Model* model) {
	return model->matrixGlobal;
}


void ModelUpdateMatrix(Model* model) {
	if(model->isNeedUpdateMatrix) {
		*model->matrix = Matrix3DLoadIdentity();
		*model->matrix = Matrix3DTranslate(*model->matrix, model->position);
		*model->matrix = Matrix3DScale(*model->matrix, model->scale);
		*model->matrix = Matrix3DRotate(*model->matrix, Vector3DInit(1.0, 0.0, 0.0), M_PI * model->rotate.x);
		*model->matrix = Matrix3DRotate(*model->matrix, Vector3DInit(0.0, 1.0, 0.0), M_PI * model->rotate.y);
		*model->matrix = Matrix3DRotate(*model->matrix, Vector3DInit(0.0, 0.0, 1.0), M_PI * model->rotate.z);
		model->isNeedUpdateMatrix = false;
	}
}

#pragma mark -
#pragma mark Model 위치

bool ModelSetPosition(Model* model, Vector3D position) {
	Vector3D _position = position;
	if(!Vector3DIsEqual(_position, model->position)) {
		model->position = _position;
		model->isNeedUpdateMatrix = true;
	}
	return true;
}

bool ModelAddPosition(Model* model, Vector3D position) {
	Vector3D _position = Vector3DAdd(model->position, position);
	if(!Vector3DIsEqual(_position, model->position)) {
		model->position = _position;
		model->isNeedUpdateMatrix = true;
	}
	return true;
}

Vector3D ModelGetPosition(Model* model) {
	return model->position;
}

#pragma mark -
#pragma mark Model 스케일

bool ModelSetScale(Model* model, Vector3D scale) {
	Vector3D _scale = scale;
	if(!Vector3DIsEqual(_scale, model->scale)) {
		model->scale = _scale;
		/*
		Vector3D vec = Vector3DInit(model->maxLengthVertex.x * _scale.x,
									model->maxLengthVertex.y * _scale.y,
									model->maxLengthVertex.z * _scale.z);
		model->radius = Vector3DLength(vec);
		model->globalRadius = model->globalRadius > model->radius ? model->globalRadius : model->radius;
		*/
		model->isNeedUpdateMatrix = true;
	}
	return true;
}

bool ModelAddScale(Model* model, Vector3D scale) {
	Vector3D _scale = Vector3DInit(model->scale.x * scale.x, 
								   model->scale.y * scale.y, 
								   model->scale.z * scale.z);
	if(!Vector3DIsEqual(_scale, model->scale)) {
		model->scale = _scale;
		/*
		Vector3D vec = Vector3DInit(model->maxLengthVertex.x * _scale.x,
									model->maxLengthVertex.y * _scale.y,
									model->maxLengthVertex.z * _scale.z);
		model->radius = Vector3DLength(vec);
		model->globalRadius = model->globalRadius > model->radius ? model->globalRadius : model->radius;
		*/
		model->isNeedUpdateMatrix = true;
	}
	return true;
}

Vector3D ModelGetScale(Model* model) {
	return model->scale;
}

#pragma mark -
#pragma mark Model 회전

bool ModelSetRotate(Model* model, Vector3D rotate) {
	Vector3D _rotate = rotate;
	if(!Vector3DIsEqual(_rotate, model->rotate)) {
		model->rotate = _rotate;
		model->isNeedUpdateMatrix = true;
	}
	
	return true;
}

bool ModelAddRotate(Model* model, Vector3D rotate) {
	Vector3D _rotate = Vector3DAdd(model->rotate, rotate);
	if(!Vector3DIsEqual(_rotate, model->rotate)) {
		model->rotate = _rotate;
		model->isNeedUpdateMatrix = true;
	}
	
	return true;
}

Vector3D ModelGetRotate(Model* model) {
	return model->rotate;
}

void ModelCullParent(Model* model) {
}
