#ifndef IZModel2D_h
#define IZModel2D_h

#include "VBModel2D.h"

class IZModel2D {
public:
    VBModel2D* model;
    
    IZModel2D();
    IZModel2D(VBObjectFile2D* _obj, VBTexture* _tex, const char* _libName);
    IZModel2D(VBTexture* _tex);
    ~IZModel2D();
    
    void SetTexture(VBTexture* _tex);
    VBTexture* GetTexture();
    
    IZModel2D* GetChildByLibraryName(const char* _libName, int _idx = 0);
    IZModel2D* GetChildByInstanceName(const char* _instanceName, int _idx = 0);
    
    void AddChild(IZModel2D* _child);
    void AddChildAt(IZModel2D* _child, int _at);
    bool RemoveChild(IZModel2D* _child);
    
    void SetPosition(VBVector2D _pos);
    VBVector2D GetPosition();
    void SetScale(VBVector2D _scale);
    
    void Stop();
    void Play();
    void GotoAndStop();
    void GotoAndPlay();
    
    bool HitTestByVector(VBVector2D _vec);
    bool HitTestByIZModel(IZModel2D* _other_model);
};

#endif
