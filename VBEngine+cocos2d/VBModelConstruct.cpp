#include <iostream>
#include <string.h>
#include "VBModel.h"
#include "cocos2d.h"
#include "OverlapTester.h"

VBModel::VBModel(CCTexture2D* _tex) {
    init();
    setTexture(_tex);
	
	CCRect rect = CCRectZero;
	rect.size = _tex->getContentSize();
	setTextureRect(rect);
}

VBModel::VBModel() : CCSprite() {
    init();
}

VBModel::VBModel(VBObjectFile2D* _obj2D, CCTexture2D* _texture, const char* _lib_name, bool _is_realtime_animation) : CCSprite() {
    VBString* _name = VBStringInitWithCString(VBStringAlloc(), _lib_name);
    VBObjectFile2DLibraryNameID* _name_id = VBObjectFile2DGetLibraryNameIDByName(_obj2D, _name);
    VBStringFree(&_name);
    
    if(_name_id) {
        InitWithLibName(_obj2D, _texture, _name_id, _is_realtime_animation);
        Stop();
    }
}

VBModel::VBModel(VBObjectFile2D* _obj2D, CCTexture2D* _texture, VBObjectFile2DLibraryNameID* _library_name_id, bool _is_realtime_animation) : CCSprite() {
    InitWithLibName(_obj2D, _texture, _library_name_id, _is_realtime_animation);
}


VBModel::~VBModel() {
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
	
	if(getParent())
		getParent()->removeChild(this, true);
}
