#ifndef VBEngineToCocos2d_x_VBModel_h
#define VBEngineToCocos2d_x_VBModel_h

#include "VBModel2D.h"
#include "cocos2d.h"


#ifdef __ANDROID__
void VBModelAllAllocatedReloadTexture();
#endif

using namespace cocos2d;

class VBModel : public cocos2d::CCSprite {
    void Link(int _currentIdx, VBModel* _child, VBObjectFile2DKeyFrame* _key_frame);
public:
    bool is_bitmap;
    
    VBColorRGBA color;
    VBColorRGBA mix_color;
    VBBool is_animation_update;
    VBBool is_use_animation;
    VBBool is_play_loop;
    VBBool is_play;
    VBBool is_real_time_animation;
    VBFloat frame_rate;
    VBFloat update_frame;
    VBObjectFile2DFrame* frame;
    VBArrayVector* frame_all_allocated_child_models;
    VBArrayVector* frame_willFree_child_models;
    VBArrayVector* frame_current_key_frame;
    VBFloat cur_frame;
    VBMatrix2DWrapper mat;
    VBObjectFile2DLibraryNameID* library_name_id;
    
    VBTexture* vb_tex;
    CCTexture2D* tex;
    
    
    VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, const char* _lib_name);
    
    void InitVBModelWithLibName(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, VBTexture* _texture, VBBool _is_realtime_animation);
    
    VBModel();
    VBModel(VBTexture* _tex);
    VBModel(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, VBTexture* _texture, VBBool _is_realtime_animation);
    ~VBModel();
    
    void reloadUName_Texture();
    
    virtual void SetTexture(VBTexture* _tex);
    
    VBModel* getVBModelByName(char* name);
    VBModel* getVBModelByInstanceName(const char* _name);
    
    void VBModelUpdateColor(VBColorRGBA _color);
    virtual void VBModelUpdate(float _tick);
    void setIsPlay(VBBool flag);
    void setIsPlayLoop(VBBool flag);
    void gotoAndPlay(float pos);
    void gotoAndStop(float pos);
    void play();
    void stop();
    
    virtual void setTextureRectInPixels(CCRect rect, bool rotated, CCSize size);
	virtual void updateTextureCoords(CCRect rect);
    virtual CCAffineTransform nodeToParentTransform(void);
    
    VBAABB getVBModelSize();
    bool checkCollisionWithButton(CCPoint pos);
    
    int getVertex(int _idx, CCPoint* _vert);
    bool hitTest(VBModel* _ot);
    
    CCPoint convertVBModelToWorldSpace(CCPoint _point);
};

#endif
