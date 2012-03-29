#ifndef VBEngineToCocos2d_x_VBModel_h
#define VBEngineToCocos2d_x_VBModel_h

#include "VBModel2D.h"
#include "cocos2d.h"

using namespace cocos2d;

class VBModel : public CCSprite {
private:
    
#pragma mark -
#pragma mark member(private)
    
    bool is_bitmap;
    
    VBColorRGBA color;
    VBColorRGBA mix_color;
    
    bool is_real_time_animation;
    bool is_animation_update;
    bool is_use_animation;
    bool is_play_loop;
    bool is_play;
    float frame_rate;
    float update_frame;
    float cur_frame;
    
    VBMatrix2DWrapper mat;
    
    VBTexture* vb_tex;
    CCTexture2D* tex;
    
    VBModel* model_parent;
    
    VBObjectFile2DFrame* frame;
    
    VBArrayVector* frame_all_allocated_child_models;
    VBArrayVector* frame_willFree_child_models;
    VBArrayVector* frame_current_key_frame;
    
    bool is_exist_empty_frame;
    float empty_frame;
    
#pragma mark -
#pragma mark function(private)
    
    void Init();
    void InitWithLibName(VBObjectFile2D* _obj2D, VBTexture* _texture, 
                         VBObjectFile2DLibraryNameID* _library_name_id, 
                         bool _is_realtime_animation = true);
    bool LinkChildKeyFrames(int _current_idx, VBModel* _child, VBObjectFile2DKeyFrame* _key_frame);
    
public:
    
#pragma mark -
#pragma mark New, Delete
    
    VBModel();
    VBModel(VBTexture* _tex);
    VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, 
            const char* _lib_name, 
            bool _is_realtime_animation = true);
    VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, 
            VBObjectFile2DLibraryNameID* _library_name_id, 
            bool _is_realtime_animation = true);
    
    ~VBModel();
    
#pragma mark -
#pragma mark Animation
    
    float GetTotalFrame();
    float GetCurrentFrame();
    
    bool GetIsPlay();
    void SetIsPlay(bool _is_play, bool _recursion = true);
    void SetIsLoop(bool _is_loop, bool _recursion = true);
    void GoToAndPlay(float _frame);
    void GoToAndStop(float _frame);
    void Play(bool _recursion = true);
    void Stop(bool _recursion = true);
    
    void SetIsUseAnimation(bool _is_use, bool _recursion = false);
    
#pragma mark -
#pragma mark Tracer
    
    VBModel* GetChildByLibraryName(const char* _name, bool _recursion = true);
    VBModel* GetChildByInstanceName(const char* _name, bool _recursion = true);
    VBModel* GetChildAtIndex(unsigned int _idx);
    int GetIndexAtParent();
    
#pragma mark -
#pragma mark Vertex
    
    VBAABB GetAABB(bool _world = true, bool _recursion = true);
    int GetVertex(int _idx, CCPoint* _vertex, bool _recursion = true);
    float GetWidth(bool _recursion = true);
    float GetHeight(bool _recursion = true);
    
#pragma mark -
#pragma mark Collider
    
    bool IsHitByPoint(CCPoint _point, bool _recursion = true);
    bool IsHit(VBModel* _model_tester, bool _recursion = true);
    
#pragma mark -
#pragma mark Color
    
    VBColorRGBA GetColor();
    void SetColor(VBColorRGBA _color);
    
    unsigned char GetAlpha();
    void SetAlpha(unsigned char _alpha);
    
    void SetBrightness(unsigned char _brightness);
    unsigned char GetBrightness();
    
#pragma mark -
#pragma mark Update
    
    virtual void Update(float _tick, bool _is_top = false);
    
#pragma mark -
#pragma mark Texture
    
    void ReloadTexture();
    virtual void SetTexture(VBTexture* _tex);
    
#pragma mark -
#pragma mark Virtual(CCSprite)
    
    virtual void setTextureRectInPixels(CCRect rect, bool rotated, CCSize size);
	virtual void updateTextureCoords(CCRect rect);
    virtual CCAffineTransform nodeToParentTransform(void);
    
};

#pragma mark -
#pragma mark Android

#ifdef __ANDROID__
void VBModelAllAllocatedReloadTexture();
#endif

#pragma mark -
#pragma mark Depth Struct

typedef struct VBModelDepthSorter {
    VBModel* child;
    VBObjectFile2DKeyFrame* key;
} VBModelDepthSorter;

#endif
