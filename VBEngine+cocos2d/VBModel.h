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
    
    //비어있는 Sprite생성
    VBModel();
    //해당텍스쳐로 Sprite를 생성
    VBModel(VBTexture* _tex);
    //해당 에니메이션과 텍스쳐로 Sprite를 생성 
    //_obj2D:에니메이션 구조체 포인터
    //_texture:텍스쳐 구조체 포인터
    //_lib_name:가져올 플래쉬 라이브러리 name
    //_is_realtime_animation:실시간 에니메이션 지원(false일 경우 frame단위로 에니메이션 계산, 테스팅 안됨)
    VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, 
            const char* _lib_name, 
            bool _is_realtime_animation = true);
    //해당 에니메이션과 텍스쳐로 Sprite를 생성 
    //_obj2D:에니메이션 구조체 포인터
    //_texture:텍스쳐 구조체 포인터
    //_library_name_id:가져올 플래쉬 라이브러리 id
    //_is_realtime_animation:실시간 에니메이션 지원(false일 경우 frame단위로 에니메이션 계산, 테스팅 안됨)
    VBModel(VBObjectFile2D* _obj2D, VBTexture* _texture, 
            VBObjectFile2DLibraryNameID* _library_name_id, 
            bool _is_realtime_animation = true);
    
    ~VBModel();
    
#pragma mark -
#pragma mark Animation
    
    //전체 에니메이션 프레임
    float GetTotalFrame();
    //현재 위치한 에니메이션 프레임
    float GetCurrentFrame();
    
    //play여부
    bool GetIsPlay();
    //play하기
    //_is_play:play여부
    //_recursion:하위 트리 Animation까지도 모두 적용시킬 것인가의 여부
    void SetIsPlay(bool _is_play, bool _recursion = true);
    //loop하기
    //_is_loop:loop여부
    //_recursion:하위 트리 Animation까지도 모두 적용시킬 것인가의 여부
    void SetIsLoop(bool _is_loop, bool _recursion = true);
    //해당프레임으로 이동하고 플레이하기
    void GoToAndPlay(float _frame);
    //해당프레임으로 이동하고 정지하기
    void GoToAndStop(float _frame);
    //재생하기
    //_recursion:하위 트리 Animation까지도 모두 적용시킬 것인가의 여부
    void Play(bool _recursion = true);
    //정지하기
    //_recursion:하위 트리 Animation까지도 모두 적용시킬 것인가의 여부
    void Stop(bool _recursion = true);
    //에니메이팅 설정
    //_is_use:에니메이팅 시킬것인가
    //_recursion:하위 트리 Animation까지도 모두 적용시킬 것인가의 여부
    void SetIsUseAnimation(bool _is_use, bool _recursion = false);
    
#pragma mark -
#pragma mark Tracer
    
    //하위 트리 Sprite중에 _name의 이름과 동일한 library name(Flash)을 가진 sprite포인터를 리턴
    //_recursion:하위트리 모두 검색(false이면 바로 밑의 노드만 검색)
    VBModel* GetChildByLibraryName(const char* _name, bool _recursion = true);
    //하위 트리 Sprite중에 _name의 이름과 동일한 instance name(Flash)을 가진 sprite포인터를 리턴
    //_recursion:하위트리 모두 검색(false이면 바로 밑의 노드만 검색)
    VBModel* GetChildByInstanceName(const char* _name, bool _recursion = true);
    //해당뎁스의 위치한 sprite포인터를 리턴
    VBModel* GetChildAtIndex(unsigned int _idx);
    //부모 Sprite에서의 현재 Sprite의 뎁스를 리턴
    int GetIndexAtParent();
    
#pragma mark -
#pragma mark Vertex
    
    //AABB박스를 리턴
    //_world:실제 스크린에서의 사이즈 인가, 아니면 부모 Sprite에서의 사이즈 인가
    //_recursion:하위 Sprite까지 전부 AABB에 포함시킬것인가의 여부
    VBAABB GetAABB(bool _world = true, bool _recursion = true);
    //정점좌표 가져오기(성공시 -1리턴)
    //_idx:몇번째 Sprite의 정점좌표를 가져올 것인가
    //_vertex:가져온 정점좌표를 담을 CCPoint[4]배열 포인터
    //_recursion:하위 트리 모두를 검색할 것인가의 여부
    int GetVertex(int _idx, CCPoint* _vertex, bool _recursion = true);
    //넓이 가져오기
    //_recursion:하위 트리 모두를 계산할 것인가의 여부
    float GetWidth(bool _recursion = true);
    //높이 가져오기
    //_recursion:하위 트리 모두를 계산할 것인가의 여부
    float GetHeight(bool _recursion = true);
    
#pragma mark -
#pragma mark Collider
    
    //점과 Sprite의 충돌체크
    //_recursion:하위 트리 모두를 계산할 것인가의 여부
    bool IsHitByPoint(CCPoint _point, bool _recursion = true);
    //Sprite와 Sprite의 충돌체크
    //_recursion:하위 트리 모두를 계산할 것인가의 여부
    bool IsHit(VBModel* _model_tester, bool _recursion = true);
    
#pragma mark -
#pragma mark Color
    
    //색상 가져오기
    VBColorRGBA GetColor();
    //색상 설정
    void SetColor(VBColorRGBA _color);
    
    //Alpha가져오기
    unsigned char GetAlpha();
    //Alpha설정
    void SetAlpha(unsigned char _alpha);
    
    //밝기 설정하기
    void SetBrightness(unsigned char _brightness);
    //밝기 가져오기
    unsigned char GetBrightness();
    
#pragma mark -
#pragma mark Update
    
    //Update
    //_tick:경과시간(1.0 == 1sec)
    //_is_top:최상위 model의 경우에만 true
    virtual void Update(float _tick, bool _is_top = false);
    
#pragma mark -
#pragma mark Texture
    
    //텍스쳐 리로드(VBTexture의 내용이 바뀌면 다음을 호출하여야 함)
    void ReloadTexture();
    //텍스쳐 설정
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
