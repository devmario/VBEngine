#include "VBDisplay2D.h"
#include "VBEngine.h"
#include "VBConfig.h"
#include <math.h>

#ifdef _VB_IPHONE_
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif


#ifdef _VB_ANDROID_
#include <GLES/gl.h>
#include <GLES/glext.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
#endif

VBArrayList* _ext_display2D = VBNull;

VBDisplay2D* VBDisplay2DAlloc(void) {
    VBDisplay2D* _display = VBSystemCalloc(1, sizeof(VBDisplay2D));
    
#ifdef _VB_DEBUG_
    if(_display == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, "VBEnging Log: VBDisplay2DAlloc() - 메모리를 할당할 수 없습니다.");
#endif
    
    if(_ext_display2D == VBNull) {
        _ext_display2D = VBArrayListInit(VBArrayListAlloc());
    }
    VBArrayListAddBack(_ext_display2D, _display);
    
    _display->picking_point = VBArrayListAlloc();
    _display->drawable_list = VBArrayListAlloc();
    _display->drawable = VBDrawable2DAlloc();
    _display->leaf_list = VBArrayListAlloc();
    _display->top = VBModel2DAlloc();
    
    return _display;
}

VBDisplay2D* VBDisplay2DInit(VBDisplay2D* _display) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DInit() - VBNull인 Display요소는 초기화 할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    _display->picking_point = VBArrayListInit(_display->picking_point);
    _display->drawable_list = VBArrayListInit(_display->drawable_list);
    _display->drawable = VBDrawable2DInit(_display->drawable);
    _display->leaf_list = VBArrayListInit(_display->leaf_list);
    _display->top = VBModel2DInit(_display->top);
    
    _display->width = 0;
    _display->height = 0;
    
    return _display;
}

VBDisplay2D* VBDisplay2DInitWithScreenSize(VBDisplay2D* _display, VBUShort _w, VBUShort _h) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DInitWithScreenSize() - VBNull인 Display요소는 초기화 할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    _display = VBDisplay2DInit(_display);
    _display->width = _w;
    _display->height = _h;
    
    return _display;
}

void VBDisplay2DFree(VBDisplay2D** _display) {
#ifdef _VB_DEBUG_
    if(*_display == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DFree() - VBNull인 Display요소는 해제 할수 없습니다. VBDisplay2DAlloc하지 않았거나 이미 VBDisplay2DFree했을 수 있습니다.");
#endif 
    
    VBArrayListRemove(_ext_display2D, _display);
    VBDisplay2DInit(*_display);
    VBSystemFree(_display);
}

void VBDisplay2DDraw(VBDisplay2D* _display) {
    VBDisplay2DCreateLeafListAndUpdateMatrixAndColor(_display, VBDisplay2DGetTopModel(_display), VBMatrix2DLoadIdentity(), VBColorAdvancedLoadIdentity());
    VBDisplay2DSetModelBB(_display);
    VBDisplay2DSetDrawFlag(_display);
    VBDisplay2DSetDrawableList(_display, VBDisplay2DGetTopModel(_display));
    
    VBArrayListNode* node = VBArrayListGetNodeAt(_display->drawable_list, 0);
    while(node) {
        VBDrawable2DDraw(VBArrayListNodeGetData(node));
        node = VBArrayListNodeGetNextNode(node);
    }
}

void VBDisplay2DUpdate(VBDisplay2D* _display, VBFloat _tick) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DDraw() - VBNull인 Display요소는 Draw할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBDisplay2DClearDrawableList(_display);
    
    if(VBEngineOpenGLGetIsSuportedShader() == VBFalse) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrthof(0.0f, (GLfloat)_display->width, (GLfloat)_display->height, 0.0f, 0.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();   
    } else {
        glUseProgram(VBEngineOpenGLGetProgram());
        float mvpmat[16] = {
            2.0 / _display->width, 0.000000, 0.000000, 0.000000, 
            0.000000, -2.0 / _display->height, 0.000000, 0.000000, 
            0.000000, 0.000000, -1.000000, 0.000000, 
            -1.000000, 1.000000, -1.000000, 1.000000
        };
        
        VBLong* uniforms = VBEngineOpenGLGetUniform();
        glUniformMatrix4fv(uniforms[UNIFORM_MVPMATRIX], 1, GL_FALSE, mvpmat);
        
        glValidateProgram(VBEngineOpenGLGetProgram());
    }
    
    VBModel2DAnimationUpdate(VBDisplay2DGetTopModel(_display) , _tick, VBTrue);
}

VBModel2D* VBDisplay2DGetTopModel(VBDisplay2D* _display) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DGetTopModel() - VBNull인 Display요소는 Top Model를 가져올 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    return _display->top;
}

VBArrayList* VBDisplay2DGetAllExistingVBDisplay2D(void) {
    return _ext_display2D;
}

void VBDisplay2DPushPickingPoint(VBDisplay2D* _display, VBPickingPoint _picking) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DPushPickingPoint() - ");
#endif
    
}

void VBDisplay2DSetModelBB(VBDisplay2D* _display) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DSetModelBB() - VBNull인 Display요소에 Bounding Box를 설정 할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBModel2DSetOBB(VBDisplay2DGetTopModel(_display));
	
    int i = 0;
    for(; i < VBArrayListGetLength(_display->leaf_list); i++) {
        VBModel2D* _model = VBArrayListDataAtIndex(_display->leaf_list, i);
        VBModel2DSetBB(_model, _model->own_bbox);
    }
    VBArrayListInit(_display->leaf_list);
}

void VBDisplay2DSetDrawFlag(VBDisplay2D* _display) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DSetDrawFlag() - VBNull인 Display요소는 DrawFlag를 설정할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBModel2DBB _bb;
    _bb.left = 0;
    _bb.right = _display->width;
    _bb.top = 0;
    _bb.bottom = _display->height;
    
    VBModel2DSetDrawFlag(_display->top, _bb);
}

void VBDisplay2DClearDrawableList(VBDisplay2D* _display) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DClearDrawableList() - VBNull인 Display요소는 Drawable List를 삭제할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBArrayListNode* node = VBArrayListGetNodeAt(_display->drawable_list, 0);
    while(node) {
        VBDrawable2D* drawable = VBArrayListNodeGetData(node);
        VBDrawable2DFree(&drawable);
        node = VBArrayListNodeGetNextNode(node);
    }
    VBArrayListInit(_display->drawable_list);
    _display->drawable = VBDrawable2DAlloc();
}

void VBDisplay2DSetDrawableList(VBDisplay2D* _display, VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DSetDrawableList() - VBNull인 Display요소는 Drawable List를 설정할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
    if(_model == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DSetDrawableList() - VBNull인 Model요소는 Drawable List를 설정할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    if(_model->bbox.is_draw) {
        if(_model->own_bbox.is_draw) {
            if(_model->drawable->tex) {
                if(_display->drawable->tex) {
                    if(_display->drawable->tex->tid != _model->drawable->tex->tid) {
                        _display->drawable = VBDrawable2DInitWithStepSize(VBDrawable2DAlloc());
                        VBArrayListAddBack(_display->drawable_list, _display->drawable);
                    }
                } else {
                    _display->drawable = VBDrawable2DInitWithStepSize(VBDrawable2DAlloc());
                    VBArrayListAddBack(_display->drawable_list, _display->drawable);
                }
                VBDrawable2DAppend(_display->drawable, _model->drawable);
            }
        }
			
		int i = 0;
        for(; i < VBModel2DGetChildNum(_model); i++) {
            VBModel2D* child = VBModel2DGetChildModelAt(_model, i);
            VBDisplay2DSetDrawableList(_display, child);
        }
    }
}

void VBDisplay2DCreateLeafListAndUpdateMatrixAndColor(VBDisplay2D* _display, VBModel2D* _model, VBMatrix2D _parent_mat, VBColorAdvanced _parent_color) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DCreateLeafListAndUpdateMatrix() - VBNull인 Display요소는 Lead List를 생성하고 Matrix를 업데이트 할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
    if(_model == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DCreateLeafListAndUpdateMatrix() - VBNull인 Model요소는 Lead List를 생성하고 Matrix를 업데이트 할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBColorAdvanced _merge_color = VBModel2DUpdateColor(_model, _parent_color);
    VBMatrix2D _merge_mat = VBModel2DUpdateMatrix(_model, _parent_mat);
    if(VBModel2DGetChildNum(_model) == 0) {
        VBArrayListAddBack(_display->leaf_list, _model);
    } else {
        VBArrayListNode* node = VBArrayListGetNodeAt(_model->child, 0);
        while(node) {
            VBModel2D* child = VBArrayListNodeGetData(node);
            VBDisplay2DCreateLeafListAndUpdateMatrixAndColor(_display, child, _merge_mat, _merge_color);
            node = VBArrayListNodeGetNextNode(node);
        }
    }
}

