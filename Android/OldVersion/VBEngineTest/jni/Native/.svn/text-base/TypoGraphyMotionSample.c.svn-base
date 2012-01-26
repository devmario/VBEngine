#include "TypoGraphyMotionSample.h"
#include <string.h>

//글자 최대 버퍼 사이즈
#define __TypoBufSize__ 0xFF
//타이포 에니메이션 끝난후 다음 타이포 에니메이션으로 가기전 기다릴 시간
#define __TypoTime__ 1.0f
//다음 에니메이션중 다음문자가 나올때의 경과시간
#define __TypoCharTime__ 0.04f
//공백 넓이
#define __TypoSpace__ 20.0f
//문자와 문자사이의 넓이
#define __TypoWordSpace__ 4.0f
//문자가 나오는 위치
#define __TypoApearX__ 500.0f
//문자가 스크롤되는 속도
#define __TypoScrollSpeed__ 0.08f

//문자열 에니메이션에 해당문자를 해당 위치에 붙히고 문자의 넓이 리턴
VBFloat _TypoGraphyMotionSampleAddChar(TypoGraphyMotionSample* _typo_graphy, VBChar _char, VBFloat _x);

//메모리 할당
TypoGraphyMotionSample* TypoGraphyMotionSampleAlloc() {
    TypoGraphyMotionSample* _typo_graphy = VBSystemCalloc(1, sizeof(TypoGraphyMotionSample));
    _typo_graphy->obj_2d = VBObjectFile2DAlloc();
    _typo_graphy->texure = VBTextureAlloc();
    _typo_graphy->top_model = VBModel2DAlloc();
    _typo_graphy->title = VBModel2DAlloc();
    _typo_graphy->text = VBModel2DAlloc();
    _typo_graphy->char_models = VBArrayVectorAlloc();
    _typo_graphy->shadow = VBModel2DAlloc();
    _typo_graphy->scripts = VBArrayVectorAlloc();
    return _typo_graphy;
}

//초기화
TypoGraphyMotionSample* TypoGraphyMotionSampleInit(TypoGraphyMotionSample* _typo_graphy, VBUShort _w, VBUShort _h) {
    //에니메이션 obj파일 로드
    VBString* _obj_2d_path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/TypoGraphyMotionSample.obj", VBStringGetCString(VBEngineGetResourcePath()));
    _typo_graphy->obj_2d = VBObjectFile2DInitAndLoad(_typo_graphy->obj_2d, _obj_2d_path);
    VBStringFree(&_obj_2d_path);
    
    //해상도에 맞게 텍스처 이미지파일 로드
    VBString* _png_path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/TypoGraphyMotionSample_%d_%d.png", VBStringGetCString(VBEngineGetResourcePath()), _w, _h);
    _typo_graphy->texure = VBTextureInitAndLoadWithImagePath(_typo_graphy->texure, _png_path);
    VBStringFree(&_png_path);
    
    //비어있는 최상위 모델 초기화
    _typo_graphy->top_model = VBModel2DInit(_typo_graphy->top_model);
    
    //텍스쳐와 obj파일의 img_res/TyphoGraphyMotionSample.png라는 이름으로 되어있는 라이브러리로 모델초기화
    VBString* _library_name = VBStringInitWithCString(VBStringAlloc(), "img_res/TyphoGraphyMotionSample.png");
    _typo_graphy->title = VBModel2DInitWithLibraryNameAndTexture(_typo_graphy->title, _typo_graphy->obj_2d, _library_name, _typo_graphy->texure, VBTrue);
    VBStringFree(&_library_name);
    
    //텍스쳐와 obj파일의 img_res/mask.png라는 이름으로 되어있는 라이브러리로 모델초기화
    _library_name = VBStringInitWithCString(VBStringAlloc(), "img_res/mask.png");
    _typo_graphy->shadow = VBModel2DInitWithLibraryNameAndTexture(_typo_graphy->shadow, _typo_graphy->obj_2d, _library_name, _typo_graphy->texure, VBTrue);
    VBStringFree(&_library_name);
    
    //문자열을 붙혀줄 모델초기화
    _typo_graphy->text = VBModel2DInit(_typo_graphy->text);
    
    //문자열 모델을 최상위 모델에 붙히고 y축을 flash스테이지의 가운데로 설정
    VBModel2DSetPosition(_typo_graphy->text, VBVector2DCreate(0.0f, VBObjectFile2DGetStageHeight(_typo_graphy->obj_2d) * 0.5f));
    VBModel2DAddChildModel(_typo_graphy->top_model, _typo_graphy->text);
    
    //그림자를 붙히고 위치와 넓이 조정(1픽셀짜리 를 스케일로 넓이를 설정해줌)
    VBModel2DSetPosition(_typo_graphy->shadow, VBVector2DCreate(0.0f, VBObjectFile2DGetStageHeight(_typo_graphy->obj_2d) * 0.5f));
    VBModel2DSetScaleX(_typo_graphy->shadow, VBObjectFile2DGetStageWidth(_typo_graphy->obj_2d));
    VBModel2DAddChildModel(_typo_graphy->top_model, _typo_graphy->shadow);
    
    //타이틀을 붙히고 위치(포토샵에서 패스를 따지 않았을 경우 가로 세로 여백 1픽셀이 있기때문에 -1로 설정)를 설정
    VBModel2DSetPosition(_typo_graphy->title, VBVector2DCreate(-1.0f, -1.0f));
    VBModel2DAddChildModel(_typo_graphy->top_model, _typo_graphy->title);
    
    //에니메이션중 보여줄 문자를 담을 배열 초기화
    _typo_graphy->char_models = VBArrayVectorInit(_typo_graphy->char_models);
    
    //속성 초기화
    _typo_graphy->container_x = __TypoApearX__;
    _typo_graphy->container_dest_x = __TypoApearX__;
    
    //문자 리소스 파일 열기
    VBString* _path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/TypoGraphyMotionSampleStringResource", VBStringGetCString(VBEngineGetResourcePath()));
    VBFile* _text_file = VBFileInitWithOpen(VBFileAlloc(), _path, VBFileMode_Read);
    VBStringFree(&_path);
    
    //문자들을 담을 배열 초기화
    _typo_graphy->scripts = VBArrayVectorInit(_typo_graphy->scripts);
    
    //읽은 문자를 담아놓을 메모리버퍼 생성하고 0x00으로 초기화하고 포인터 생성
    VBChar* _char = VBSystemMalloc(__TypoBufSize__);
    VBSystemMemorySet(_char, 0x00, __TypoBufSize__);
    VBChar* _char_ptr = _char;
    //파일사이즈 만큼 읽기(영문이랑 공백만 읽을수 있음)
    while(VBFileGetOffset(_text_file) < VBFileGetSize(_text_file)) {
        //한문자씩 읽기
        VBFileReadChar(_text_file, _char_ptr);
        //줄넘김이면 널문자 삽입후 문자열 생성한 후에 배열에 저장하고 메모리 버퍼와 포인터 초기화
        if(*_char_ptr == '\n') {
            *_char_ptr = '\0';
            VBString* _str = VBStringInitWithCString(VBStringAlloc(), _char);
            VBStringUpperCase(_str);
            VBArrayVectorAddBack(_typo_graphy->scripts, _str);
            
            VBSystemMemorySet(_char, 0x00, __TypoBufSize__);
            _char_ptr = _char;
        } else if((*_char_ptr <= 'Z' && *_char_ptr >= 'A') || 
                  (*_char_ptr <= 'z' && *_char_ptr >= 'a') ||
                  *_char_ptr == ' ') {
            //위의 평가식에 포함되는 문자만 포인터증가
            _char_ptr++;
        }
    }
    VBSystemFree(_char);
    
    //파일 해제(내부적으로는 열려있을 경우 닫아짐)
    VBFileFree(&_text_file);
    
    return _typo_graphy;
}

//메모리 해제
void TypoGraphyMotionSampleFree(TypoGraphyMotionSample** _typo_graphy) {
    //문자모델들 삭제
    TypoGraphyMotionSampleSetNextAnimation(*_typo_graphy);
    VBArrayVectorFree(&(*_typo_graphy)->char_models);
    
    //문자 해제
    while(VBArrayVectorGetLength((*_typo_graphy)->scripts)) {
        VBString* _str = VBArrayVectorRemoveBack((*_typo_graphy)->scripts);
        VBStringFree(&_str);
    }
    VBArrayVectorFree(&(*_typo_graphy)->scripts);
    
    //모델 삭제
    VBModel2DFree(&(*_typo_graphy)->shadow);
    VBModel2DFree(&(*_typo_graphy)->text);
    VBModel2DFree(&(*_typo_graphy)->title);
    VBModel2DFree(&(*_typo_graphy)->top_model);
    
    //obj파일 언로드
    VBObjectFile2DFree(&(*_typo_graphy)->obj_2d);
    
    //텍스쳐 언로드
    VBTextureFree(&(*_typo_graphy)->texure);
    
    //해제
    VBSystemFree(*_typo_graphy);
    *_typo_graphy = VBNull;
}

//최상위 모델 리턴
VBModel2D* TypoGraphyMotionSampleGetTopModel(TypoGraphyMotionSample* _typo_graphy) {
    return _typo_graphy->top_model;
}

//에니메이션 업데이트
void TypoGraphyMotionSampleUpdate(TypoGraphyMotionSample* _typo_graphy, VBFloat _time) {
    //역플레이시 리턴하여 업데이트 되는것 방지
    if(_time <= 0.0)
        return;
    
    //문자열 모델의 x위치가 원하는 목적x위치로 에니메이팅 되도록 함
    _typo_graphy->container_x += (_typo_graphy->container_dest_x - _typo_graphy->container_x) * __TypoScrollSpeed__;
    VBModel2DSetX(_typo_graphy->text, _typo_graphy->container_x);
    
    //현재 문자열 배열에서 가져오기
    VBString* _cur_str = VBArrayVectorGetDataAt(_typo_graphy->scripts, _typo_graphy->cur_idx);
    //문자인덱스가 문자열 길이보다 작을때(에니메이션 진행중)
    if(_typo_graphy->cur_char_idx < VBStringGetLength(_cur_str)) {
        //문자 시간 증가(이시간이 일정시간보다 커지면 화면에 문자가 붙는다)
        _typo_graphy->cur_char_time += _time;
        if(_typo_graphy->cur_char_time >= __TypoCharTime__) {
            //카운팅 후 카운팅변수 초기화
            _typo_graphy->cur_char_time = 0.0f;
            //문자가 공백이 아닐경우
            if(VBStringGetCharAt(_cur_str, _typo_graphy->cur_char_idx) != ' ') {
                //화면에 문자 붙힌후 문자의 넓이를 문자열의 넓이에 더함
                _typo_graphy->char_width += _TypoGraphyMotionSampleAddChar(_typo_graphy, VBStringGetCharAt(_cur_str, _typo_graphy->cur_char_idx), _typo_graphy->char_width);
                //문자와 문자사이의 넓이를 저장
                if(_typo_graphy->cur_char_idx != VBStringGetLength(_cur_str) - 1) {
                    _typo_graphy->char_width += __TypoWordSpace__;
                }
            } else {
                //공백의 넓이를 더함
                _typo_graphy->char_width += __TypoSpace__;
            }
            //문자열의 목적x위치 설정
            _typo_graphy->container_dest_x = __TypoApearX__ - _typo_graphy->char_width;
            //문자열의 문자 인덱스증가
            _typo_graphy->cur_char_idx++;
        }
    } else {
        //에니메이션이 끝난후 카운팅하여 일정한 시간이 지나면 모든 문자모델을 삭제하고 다음 문자열로 에니메이션 시작할수 있도록 속성 초기화
        _typo_graphy->cur_time += _time;
        if(_typo_graphy->cur_time >= __TypoTime__)
            TypoGraphyMotionSampleSetNextAnimation(_typo_graphy);
    }
}

//문자열 에니메이션 다음으로 넘기고 리셋
void TypoGraphyMotionSampleSetNextAnimation(TypoGraphyMotionSample* _typo_graphy) {
    //붙어있는 모든 문자 모델을 해제
    while(VBArrayVectorGetLength(_typo_graphy->char_models)) {
        VBModel2D* _model = VBArrayVectorRemoveBack(_typo_graphy->char_models);
        VBModel2DFree(&_model);
    }
    
    //다음 문자로 선택
    _typo_graphy->cur_idx++;
    if(_typo_graphy->cur_idx >= VBArrayVectorGetLength(_typo_graphy->scripts)) {
        _typo_graphy->cur_idx = 0;
    }
    
    //속성 초기화
    _typo_graphy->cur_time = 0.0f;
    _typo_graphy->cur_char_time = 0.0f;
    _typo_graphy->cur_char_idx = 0;
    _typo_graphy->char_width = 0.0f;
    _typo_graphy->container_x = __TypoApearX__;
    _typo_graphy->container_dest_x = __TypoApearX__;
}

//문자열 에니메이션에 해당문자를 해당 위치에 붙히고 문자의 넓이 리턴
VBFloat _TypoGraphyMotionSampleAddChar(TypoGraphyMotionSample* _typo_graphy, VBChar _char, VBFloat _x) {
    //해당 문자로 모델 생성
    VBString* _library_name = VBStringInitWithCStringFormat(VBStringAlloc(), "img_res/%c.png", _char);
    //문자 모델
    VBModel2D* _char_top = VBModel2DInitWithLibraryNameAndTexture(VBModel2DAlloc(), _typo_graphy->obj_2d, _library_name, _typo_graphy->texure, VBTrue);
    //반사된 문자 모델
    VBModel2D* _char_bottom = VBModel2DInitWithLibraryNameAndTexture(VBModel2DAlloc(), _typo_graphy->obj_2d, _library_name, _typo_graphy->texure, VBTrue);
    //모델 배열에 저장
    VBArrayVectorAddBack(_typo_graphy->char_models, _char_top);
    VBArrayVectorAddBack(_typo_graphy->char_models, _char_bottom);
    //모델의 y축을 각 문자에 맞게 조정
    VBModel2DSetPosition(_char_top, VBVector2DCreate(0.0f, -VBModel2DGetOriginHeight(_char_top)));
    VBModel2DSetPosition(_char_bottom, VBVector2DCreate(0.0f, -VBModel2DGetOriginHeight(_char_bottom)));
    //필요없는 문자 메모리 해제
    VBStringFree(&_library_name);
    
    //char_res라는 이름의 라이브러리로 모델 생성하고 배열에 저장
    _library_name = VBStringInitWithCString(VBStringAlloc(), "char_res");
    VBModel2D* _char_res = VBModel2DInitWithLibraryNameAndTexture(VBModel2DAlloc(), _typo_graphy->obj_2d, _library_name, _typo_graphy->texure, VBTrue);
    VBArrayVectorAddBack(_typo_graphy->char_models, _char_res);
    VBStringFree(&_library_name);
    
    //char_res에서 id_char_motion_top이라는 인스턴스 네임을 가진 모델에 접근(에니메이션이 있는 모델)
    VBString* _id_name = VBStringInitWithCString(VBStringAlloc(), "id_char_motion_top");
    VBModel2D* _top = VBModel2DGetChildModelByInstanceName(_char_res, _id_name);
    //루프를 끔(디폴트는 VBTrue)
    VBModel2DSetIsLoop(_top, VBFalse);
    VBStringFree(&_id_name);
    
    //id_char_motion_top에서 id_char이라는 인스턴스 네임을 가진 모델에 접근(비어있는 모델)
    _id_name = VBStringInitWithCString(VBStringAlloc(), "id_char");
    VBModel2D* _top_res = VBModel2DGetChildModelByInstanceName(_top, _id_name);
    //비어있는 모델에 생성한 문자 모델을 붙힘
    VBModel2DAddChildModel(_top_res, _char_top);
    VBStringFree(&_id_name);
    
    //char_res에서 id_char_motion_bottom라는 인스턴스 네임을 가진 모델에 접근(에니메이션이 있는 모델)
    _id_name = VBStringInitWithCString(VBStringAlloc(), "id_char_motion_bottom");
    VBModel2D* _bottom = VBModel2DGetChildModelByInstanceName(_char_res, _id_name);
    //루프를 끔(디폴트는 VBTrue)
    VBModel2DSetIsLoop(_bottom, VBFalse);
    VBStringFree(&_id_name);
    
    //id_char_motion_bottom에서 id_char이라는 인스턴스 네임을 가진 모델에 접근(비어있는 모델)
    _id_name = VBStringInitWithCString(VBStringAlloc(), "id_char");
    VBModel2D* _bottom_res = VBModel2DGetChildModelByInstanceName(_bottom, _id_name);
    //비어있는 모델에 생성한 문자 모델을 붙힘
    VBModel2DAddChildModel(_bottom_res, _char_bottom);
    VBStringFree(&_id_name);
    
    //문자의 x위치를 설정하고 문자열모델에 붙힘
    VBModel2DSetPosition(_char_res, VBVector2DCreate(_x, 0.0f));
    VBModel2DAddChildModel(_typo_graphy->text, _char_res);
    
    //문자의 넓이를 리턴
    return VBModel2DGetOriginWidth(_char_top);
}
