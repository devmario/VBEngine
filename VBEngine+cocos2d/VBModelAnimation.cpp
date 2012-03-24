#include "VBModel.h"

float VBModel::GetTotalFrame() {
    if(frame)
    	return (float)VBObjectFile2DFrameGetTotalFrame(frame);
    
    return 0.0f;
}

float VBModel::GetCurrentFrame() {
    return cur_frame;
}

bool VBModel::GetIsPlay() {
    return is_play;
}

void VBModel::SetIsPlay(VBBool _is_play, bool _recursion) {
    is_play = _is_play;
    
    if(_recursion == false)
        return;
    
    if(getChildren()) {
        for(int i = 0; i < getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)getChildren()->objectAtIndex(i);
            _child->SetIsPlay(_is_play, _recursion);
        }
    }
}

void VBModel::SetIsLoop(VBBool _is_loop, bool _recursion) {
    is_play_loop = _is_loop;
    
    if(_recursion == false)
        return;
    
    if(getChildren()) {
        for(int i = 0; i < getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)getChildren()->objectAtIndex(i);
            _child->SetIsLoop(_is_loop, _recursion);
        }
    }
}

void VBModel::GoToAndPlay(float _frame) {
    SetIsPlay(true, false);
    update_frame = true;
    cur_frame = _frame;
}

void VBModel::GoToAndStop(float _frame) {
    SetIsPlay(false, false);
    update_frame = true;
    cur_frame = _frame;
}

void VBModel::Play(bool _recursion) {
    SetIsPlay(true, _recursion);
}

void VBModel::Stop(bool _recursion) {
    SetIsPlay(false, _recursion);
}

void VBModel::SetIsUseAnimation(bool _is_use, bool _recursion) {
    is_use_animation = _is_use;
    
    if(_recursion == false)
        return;
    
    if(getChildren()) {
        for(int i = 0; i < getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)getChildren()->objectAtIndex(i);
            _child->SetIsUseAnimation(_is_use, _recursion);
        }
    }
}