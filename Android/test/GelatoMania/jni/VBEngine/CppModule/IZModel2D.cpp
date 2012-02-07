#include "IZModel2D.h"

IZModel2D::IZModel2D() {
    model = VBModel2DInit(VBModel2DAlloc());
}

IZModel2D::IZModel2D(VBObjectFile2D* _obj, VBTexture* _tex, const char* _libName) {
    VBString* _str = VBStringInitWithCString(VBStringAlloc(), _libName);
    model = VBModel2DInitWithLibraryNameAndTexture(VBModel2DAlloc(), _obj, _str, _tex, true);
    VBStringFree(&_str);
}

IZModel2D::IZModel2D(VBTexture* _tex) {
    
}

IZModel2D::~IZModel2D() {
    VBModel2DFree(&model);
}

void IZModel2D::SetTexture(VBTexture* _tex) {
    
}

VBTexture* IZModel2D::GetTexture() {
    return NULL;
}

IZModel2D* IZModel2D::GetChildByLibraryName(const char* _libName, int _idx) {
    
}

IZModel2D* IZModel2D::GetChildByInstanceName(const char* _instanceName, int _idx) {
    
}

void IZModel2D::AddChild(IZModel2D* _child) {
    
}

void IZModel2D::AddChildAt(IZModel2D* _child, int _at) {
    
}

bool IZModel2D::RemoveChild(IZModel2D* _child) {
    
}

void IZModel2D::SetPosition(VBVector2D _pos) {
    
}

VBVector2D IZModel2D::GetPosition() {
    
}

void IZModel2D::SetScale(VBVector2D _scale) {
    
}

void IZModel2D::Stop() {
    
}

void IZModel2D::Play() {
    
}

void IZModel2D::GotoAndStop() {
    
}

void IZModel2D::GotoAndPlay() {
    
}

bool IZModel2D::HitTestByVector(VBVector2D _vec) {
    
}

bool IZModel2D::HitTestByIZModel(IZModel2D* _other_model) {
    
}