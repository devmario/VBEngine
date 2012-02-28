#include "VBDisplay2D.h"
#include "VBEngine.h"
#include "VBConfig.h"
#include <math.h>

#ifdef _VB_IPHONE_
#include <OpenGLES/ES1/gl.h>
#endif
#ifdef _MAC_
#include <OpenGL/OpenGL.h>
#endif

#ifdef __ANDROID__
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#pragma mark - private 접근

//모델의 Vertex의 AABB를 설정합니다.(이메소드 호출시 하위의 모든 자식의 Vertex들도 AABB가 설정됨)
//child로 내려가며 재귀
void _VBModel2DSetVertexAABBTowardChildsRecursive(VBModel2D* _model);

//모델의 AABB(모든 자식들의 AABB를 포함)를 설정합니다.(이메소드 호출시 모든 부모들의 AABB도 설정됨)
//parent로 타고 올라가며 재귀
void _VBModel2DSetAABBTowardParentsRecursive(VBModel2D* _model, VBAABB _child_aabb);

//모델의 AABB와 화면의 AABB를 충돌검사해서 출력 플래그를 설정합니다.
//child로 내려가며 재귀
void _VBModel2DSetDrawFlagAsAABBTowardChildsRecursive(VBModel2D* _model, VBAABB _screen_aabb);

//VBModel2D의 에니메이션 업데이트(private한 재귀 method)
//자식으로 내려가면서 모든 에니메이션을 업데이트
void _VBModel2DAnimationUpdateTowardChildsRecursive(VBModel2D* _model, VBFloat _tick, VBBool _is_update_child);

//모델의 칼라와 매트릭스를 두번째,세번째 인자로 넘긴 속성들과 혼합하고 Drawable을 만드는 private한 method
//자식들을 타고 내려가며 재귀 method
//5번째 인자로 넘긴 콜백은 재귀도는중 현재 모델이 모델트리의 가장 하위일때 호출된다.(자식이 없는 모델)
//이는 VBDisplay2D에서 모델을 Draw할때 AABB박스를 모델트리구조를 따르면서 병합하기 위해서이다.(빠른 렌더링 위해)
//4번째 인자로 넘긴 포인터는 5번째인자의 콜백 호출시 넘겨진다.
void _VBModel2DUpdateColorAndMatrixAndDrawableTowardChildsRecursive(VBModel2D* _model, VBColorRGBA _parent_color, VBMatrix2D _parent_mat, void* _user_reference, void _leaf_tree_child_func(void*,VBModel2D*));

#pragma mark - private 모델의 모델트리가 최하위 일때 콜백

void _VBDisplay2DEventLeafModel(void* _user_reference, VBModel2D* _leaf_model);
void _VBDisplay2DSetDrawableListTowardChildsRecursive(VBDisplay2D* _display, VBModel2D* _model);

//VBDisplay2DDraw실행중 모델의 모든 Drawable을 만들다가 최하위 모델을 만났을경우 호출
//AABB를 만들기 위해 최하위 모델 리스트를 만든다.
void _VBDisplay2DEventLeafModel(void* _user_reference, VBModel2D* _leaf_model) {
    VBDisplay2D* _display = _user_reference;
    VBArrayListAddBack(_display->leaf_list, _leaf_model);
}

#pragma mark - private 디스플레이의 모든 Drawable 리스트를 만들기 위한 재귀 method 

//디스플레이의 모든 Drawable 리스트를 만드는 함수
void _VBDisplay2DSetDrawableListTowardChildsRecursive(VBDisplay2D* _display, VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, "VBEngine Log: VBDisplay2DSetDrawableList() - VBNull인 Display요소는 Drawable List를 설정할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
    if(_model == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, "VBEngine Log: VBDisplay2DSetDrawableList() - VBNull인 Model요소는 Drawable List를 설정할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    if(_model->is_aabb_draw) {
        if(_model->is_vertex_aabb_draw) {
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
        VBArrayListNode* _node = VBArrayListGetFirstNode(_model->child);
        while(_node) {
            VBModel2D* _child = VBArrayListNodeGetData(_node);
            _VBDisplay2DSetDrawableListTowardChildsRecursive(_display, _child);
            _node = VBArrayListNodeGetNextNode(_node);
        }
    }
}

#pragma mark - 메모리 생성및 해제, 초기화

VBDisplay2D* VBDisplay2DAlloc(void) {
    VBDisplay2D* _display = VBSystemCalloc(1, sizeof(VBDisplay2D));
    
#ifdef _VB_DEBUG_
    if(_display == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, "VBEnging Log: VBDisplay2DAlloc() - 메모리를 할당할 수 없습니다.");
#endif
    
    _display->drawable_list = VBArrayListAlloc();
    _display->drawable = VBNull;
    _display->leaf_list = VBArrayListAlloc();
    _display->top = VBModel2DAlloc();
    _display->camera = VBCamera2DAlloc();
    
    return _display;
}

VBDisplay2D* VBDisplay2DInit(VBDisplay2D* _display) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DInit() - VBNull인 Display요소는 초기화 할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    if(_display->drawable_list)
        _display->drawable_list = VBArrayListInit(_display->drawable_list);
    if(_display->leaf_list)
        _display->leaf_list = VBArrayListInit(_display->leaf_list);
    if(_display->top)
        _display->top = VBModel2DInit(_display->top);
    if(_display->camera)
        _display->camera = VBCamera2DInitWithMode(_display->camera, VBCamera2DMode_Default);
    
    return _display;
}

void VBDisplay2DFree(VBDisplay2D** _display) {
#ifdef _VB_DEBUG_
    if(*_display == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DFree() - VBNull인 Display요소는 해제 할수 없습니다. VBDisplay2DAlloc하지 않았거나 이미 VBDisplay2DFree했을 수 있습니다.");
#endif 
    
    VBArrayListFree(&(*_display)->drawable_list);
    VBArrayListFree(&(*_display)->leaf_list);
    VBModel2DFree(&(*_display)->top);
    VBCamera2DFree(&(*_display)->camera);
    VBDisplay2DInit(*_display);
    VBSystemFree(*_display);
    *_display = VBNull;
}

#pragma mark - Update And Draw

void VBDisplay2DUpdate(VBDisplay2D* _display, VBFloat _tick) {
#ifdef _VB_DEBUG_
    if(_display == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDisplay2DDraw() - VBNull인 Display요소는 Draw할 수 없습니다. VBDisplayAlloc()하지 않았을 수 있습니다.");
#endif
    
    //모든 Drawable 리스트 초기화
    VBArrayListNode* node = VBArrayListGetFirstNode(_display->drawable_list);
    while(node) {
        VBDrawable2D* drawable = VBArrayListNodeGetData(node);
        VBDrawable2DFree(&drawable);
        node = VBArrayListNodeGetNextNode(node);
    }
    VBArrayListInit(_display->drawable_list);
    VBDrawable2D* _tmpDrawable = _display->drawable = VBDrawable2DAlloc();
    
#ifdef _VB_USE_BBTREE_
    //AABB생성을 위한 최하위 모델리스트 초기화
    VBArrayListInit(_display->leaf_list);
#endif
    
    //에니메이션 업데이트
    _VBModel2DAnimationUpdateTowardChildsRecursive(VBDisplay2DGetTopModel(_display) , _tick, VBTrue);
    
    //모델의 색상과 변환행렬을 모델트리구조에서 혼합하고 모든 모델의 Drawable을 만든다.
    //추가로 AABB생성을 위한 최하위 모델들도 수집한다.
    _VBModel2DUpdateColorAndMatrixAndDrawableTowardChildsRecursive(VBDisplay2DGetTopModel(_display), VBColorRGBALoadIdentity(), VBCamera2DGetMatrix(_display->camera), _display, _VBDisplay2DEventLeafModel);
    
#ifdef _VB_USE_BBTREE_
    //버텍스 AABB 설정
    _VBModel2DSetVertexAABBTowardChildsRecursive(VBDisplay2DGetTopModel(_display));
    
    //AABB 설정
    VBArrayListNode* _node = VBArrayListGetFirstNode(_display->leaf_list);
    while(_node) {
        VBModel2D* _model = VBArrayListNodeGetData(_node);
        _VBModel2DSetAABBTowardParentsRecursive(_model, _model->vertex_aabb);
        _node = VBArrayListNodeGetNextNode(_node);
    }
    
    //모델을 그릴것인가 말것인가를 스크린의 AABB와 모델트리의 AABB들과 판단하여 플래그 값을 설정한다.
    VBVector2D _screen_size = VBEngineGetScreenSize();
    _VBModel2DSetDrawFlagAsAABBTowardChildsRecursive(_display->top, VBAABBCreate(0.0f, 0.0f, _screen_size.x, _screen_size.y));
#endif
    
    //디스플레이의 모델들을 최소 갯수의 Drawable로 병합한다.
    _VBDisplay2DSetDrawableListTowardChildsRecursive(_display, VBDisplay2DGetTopModel(_display));
    
    VBDrawable2DFree(&_tmpDrawable);
}

void VBDisplay2DDraw(VBDisplay2D* _display) {
    //OpenGL 좌표계 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    VBVector2D _screen_size = VBEngineGetScreenSize();
#ifdef _MAC_
    glOrtho(0, _screen_size.x, _screen_size.y, 0, -1, 1);
#elif
    glOrthof(0, _screen_size.x, _screen_size.y, 0, -1, 1);
#endif
    
    //ModelView전환
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  
    
    //병합된 모든 Drawable을 그린다.
    VBArrayListNode* node = VBArrayListGetNodeAt(_display->drawable_list, 0);
    while(node) {
        VBDrawable2DDraw(VBArrayListNodeGetData(node));
        node = VBArrayListNodeGetNextNode(node);
    }
}

#pragma mark - Getter

VBCamera2D* VBDisplay2DGetCamera(VBDisplay2D* _display) {
    return _display->camera;
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

