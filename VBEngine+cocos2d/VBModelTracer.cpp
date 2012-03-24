#include "VBModel.h"

VBModel* VBModel::GetChildByLibraryName(const char* _name, bool _recursion) {
    if(frame) {
        VBArrayVector* _vec_key_frame = VBObjectFile2DFrameGetKeyFrames(frame);
        
        if(_vec_key_frame) {
            for(int i = 0; i < VBArrayVectorGetLength(_vec_key_frame); i++) {
                
                VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)VBArrayVectorGetDataAt(_vec_key_frame, i);
                
                VBObjectFile2DLibraryNameID* _name_id = VBObjectFile2DKeyFrameGetLibraryNameID(_key_frame);
                VBString* _library_name = VBObjectFile2DLibraryNameIDGetName(_name_id);
                
                VBModel* _child = (VBModel*)VBArrayVectorGetDataAt(frame_all_allocated_child_models, i);
                if(VBStringIsEqualToCString(_library_name, _name)) {
                    return _child;
                } else {
                    VBModel* _find = _child->GetChildByLibraryName(_name, _recursion);
                    if(_find)
                        return _find;
                }
            }
        }
    }
    return NULL;
}

VBModel* VBModel::GetChildByInstanceName(const char* _name, bool _recursion) {
    if(frame) {
        VBArrayVector* _vec_key_frame = VBObjectFile2DFrameGetKeyFrames(frame);
        
        if(_vec_key_frame) {
            for(int i = 0; i < VBArrayVectorGetLength(_vec_key_frame); i++) {
                
                VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)VBArrayVectorGetDataAt(_vec_key_frame, i);
                VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame);
                VBObjectFile2DKeyFrameElementType _type = VBObjectFile2DKeyFrameElementGetType(_element);
                
                if(_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                    
                    VBObjectFile2DKeyFrameElementMovieClip* _mc = (VBObjectFile2DKeyFrameElementMovieClip*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                    VBString* _instance_name = VBObjectFile2DKeyFrameElementMovieClipGetInstanceName(_mc);
                    
                    VBModel* _child = (VBModel*)VBArrayVectorGetDataAt(frame_all_allocated_child_models, i);
                    if(VBStringIsEqualToCString(_instance_name, _name)) {
                        return _child;
                    } else {
                        VBModel* _find = _child->GetChildByInstanceName(_name, _recursion);
                        if(_find)
                            return _find;
                    }
                }
            }
        }
    }
    return NULL;
}

VBModel* VBModel::GetChildAtIndex(unsigned int _idx) {
    if(getChildren()) {
        if(_idx < getChildren()->count()) {
            return (VBModel*)getChildren()->objectAtIndex(_idx);
        }
    }
    return NULL;
}

int VBModel::GetIndexAtParent() {
    CCNode* _parent = getParent();
    if(_parent) {
        if(_parent->getChildren()) {
            for(int i = 0; i < _parent->getChildren()->count(); i++) {
                CCNode* _node = (CCNode*)_parent->getChildren()->objectAtIndex(i);
                if(_node == this)
                    return i;
            }
        }
    }
    return -1;
}