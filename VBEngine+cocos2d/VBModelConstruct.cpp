#include <iostream>
#include <string.h>
#include "VBModel.h"
#include "cocos2d.h"
#include "OverlapTester.h"

#ifdef __ANDROID__
VBArrayVector* _allocModel = NULL;

void VBModelAllAllocatedReloadTexture() {
    if(_allocModel) {
        for(int i = 0; i < _allocModel->len; i++) {
            VBModel* _m = (VBModel*)_allocModel->data[i];
            _m->ReloadTexture();
        }
    }
}

void AddAllocModel(VBModel* _m) {
    if(_allocModel == NULL)
        _allocModel = VBArrayVectorInit(VBArrayVectorAlloc());
    VBArrayVectorAddBack(_allocModel, _m);
}

void RemoveAllocModel(VBModel* _m) {
    if(_allocModel) {
        VBArrayVectorRemove(_allocModel, _m);
    }
}
#endif


VBModel::VBModel(VBTexture* _tex) {
#ifdef __ANDROID__
    AddAllocModel(this);
#endif
    Init();
    SetTexture(_tex);
}

VBModel::VBModel() : CCSprite() {
#ifdef __ANDROID__
    AddAllocModel(this);
#endif
    Init();
}

VBModel::VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, const char* _lib_name, bool _is_realtime_animation) : CCSprite() {
#ifdef __ANDROID__
    AddAllocModel(this);
#endif
    
    VBString* _name = VBStringInitWithCString(VBStringAlloc(), _lib_name);
    VBObjectFile2DLibraryNameID* _name_id = VBObjectFile2DGetLibraryNameIDByName(_obj2D, _name);
    VBStringFree(&_name);
    
    if(_name_id) {
        InitWithLibName(_obj2D, _texture, _name_id, _is_realtime_animation);
        Stop();
    }
}

VBModel::VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, VBObjectFile2DLibraryNameID* _library_name_id, bool _is_realtime_animation) : CCSprite() {
#ifdef __ANDROID__
    AddAllocModel(this);
#endif
    InitWithLibName(_obj2D, _texture, _library_name_id, _is_realtime_animation);
}


VBModel::~VBModel() {
#ifdef __ANDROID__
    RemoveAllocModel(this);
#endif
    if(getChildren()) {
        while(getChildren()->count())
            removeChild((VBModel*)getChildren()->objectAtIndex(0), false);
    }
    
    if(m_pobTexture) {
        m_pobTexture->m_uName = 0;
        if(m_pobTexture->retainCount() > 0) {
            m_pobTexture->release();
        }
        m_pobTexture = NULL;
    }
    
    if(tex) {
        tex->m_uName = 0;
        if(tex->retainCount() > 0) {
            tex->release();
        }
        tex = NULL;
    }
    
    if(frame_current_key_frame) {
        while(VBArrayVectorGetLength(frame_current_key_frame)) {
            VBModelDepthSorter* _sorter = (VBModelDepthSorter*)VBArrayVectorRemoveBack(frame_current_key_frame);
            free(_sorter);
        }
        VBArrayVectorFree(&frame_current_key_frame);
    }
    
    if(frame_willFree_child_models) {
        while(VBArrayVectorGetLength(frame_willFree_child_models)) {
            VBModel* _child = (VBModel*)VBArrayVectorRemoveBack(frame_willFree_child_models);
            delete _child;
        }
        VBArrayVectorFree(&frame_willFree_child_models);
    }
    if(frame_all_allocated_child_models)
        VBArrayVectorFree(&frame_all_allocated_child_models);
}