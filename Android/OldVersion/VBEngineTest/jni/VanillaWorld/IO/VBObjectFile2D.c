#include "VBObjectFile2D.h"
#include "../VBEngine.h"
#include <stdio.h>

VBObjectFile2D* VBObjectFile2DAlloc(void) {
    VBObjectFile2D* _obj2D = VBSystemCalloc(1, sizeof(VBObjectFile2D));
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DAlloc() - 메모리를 할당 할 수 없습니다.");
#endif
    if(_obj2D) {
        _obj2D->file = VBFileAlloc();
        
        _obj2D->library_name_id = VBArrayVectorAlloc();
        _obj2D->library = VBArrayVectorAlloc();
        
        _obj2D->library_graphic = VBArrayListAlloc();
        _obj2D->library_movie_clip = VBArrayListAlloc();
        
        _obj2D->library_bitmap = VBArrayVectorAlloc();
        
        _obj2D->frame = VBArrayListAlloc();
        _obj2D->key_frame = VBArrayListAlloc();
        _obj2D->element = VBArrayListAlloc();
        _obj2D->element_bitmap = VBArrayListAlloc();
        _obj2D->element_graphic = VBArrayListAlloc();
        _obj2D->element_movie_clip = VBArrayListAlloc();
        
        _obj2D->transition = VBArrayListAlloc();
    }
    return _obj2D;
}

VBObjectFile2D* VBObjectFile2DInit(VBObjectFile2D* _obj2D) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DInit() - 초기화에 실패하였습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용하고 있을 수 있습니다.");
#endif 
    if(_obj2D) {
        _obj2D->file = VBFileInit(_obj2D->file);
        
        _obj2D->library_name_id = VBArrayVectorInit(_obj2D->library_name_id);
        _obj2D->library = VBArrayVectorInit(_obj2D->library);
        
        _obj2D->library_graphic = VBArrayListInit(_obj2D->library_graphic);
        _obj2D->library_movie_clip = VBArrayListInit(_obj2D->library_movie_clip);
        
        _obj2D->library_bitmap = VBArrayVectorInit(_obj2D->library_bitmap);
        
        _obj2D->frame = VBArrayListInit(_obj2D->frame);
        _obj2D->key_frame = VBArrayListInit(_obj2D->key_frame);
        _obj2D->element = VBArrayListInit(_obj2D->element);
        _obj2D->element_bitmap = VBArrayListInit(_obj2D->element_bitmap);
        _obj2D->element_graphic = VBArrayListInit(_obj2D->element_graphic);
        _obj2D->element_movie_clip = VBArrayListInit(_obj2D->element_movie_clip);
        
        _obj2D->transition = VBArrayListInit(_obj2D->transition);
    }
    return _obj2D;
}
VBObjectFile2D* VBObjectFile2DInitAndLoad(VBObjectFile2D* _obj2D, VBString* _path) {
    _obj2D = VBObjectFile2DInit(_obj2D);
    VBObjectFile2DLoad(_obj2D, _path);
    return _obj2D;
}

void VBObjectFile2DFree(VBObjectFile2D** _obj2D) {
#ifdef _VB_DEBUG_
    if(*_obj2D == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DFree() - VBNull인 오브첵트 파일은 해제 할수 없습니다. VBObjectFile2DAlloc() 하지 않았거나 이미 VBObjectFile2DFree()했을 수 있습니다.");
#endif
    
    if(*_obj2D) {
        void* _data = VBArrayListRemoveBack((*_obj2D)->transition);
        while(_data) {
            VBObjectFile2DTransitionFree((VBObjectFile2DTransition**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->transition); 
        }
        VBArrayListFree(&(*_obj2D)->transition);
        
        _data = VBArrayListRemoveBack((*_obj2D)->element_movie_clip);
        while(_data) {
            VBObjectFile2DKeyFrameElementMovieClipFree((VBObjectFile2DKeyFrameElementMovieClip**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->element_movie_clip); 
        }
        VBArrayListFree(&(*_obj2D)->element_movie_clip);
        
        _data = VBArrayListRemoveBack((*_obj2D)->element_graphic);
        while(_data) {
            VBObjectFile2DKeyFrameElementGraphicFree((VBObjectFile2DKeyFrameElementGraphic**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->element_graphic); 
        }
        VBArrayListFree(&(*_obj2D)->element_graphic);
        
        _data = VBArrayListRemoveBack((*_obj2D)->element_bitmap);
        while(_data) {
            VBObjectFile2DKeyFrameElementBitmapFree((VBObjectFile2DKeyFrameElementBitmap**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->element_bitmap); 
        }
        VBArrayListFree(&(*_obj2D)->element_bitmap);
        
        _data = VBArrayListRemoveBack((*_obj2D)->element);
        while(_data) {
            VBObjectFile2DKeyFrameElementFree((VBObjectFile2DKeyFrameElement**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->element); 
        }
        VBArrayListFree(&(*_obj2D)->element);
        
        _data = VBArrayListRemoveBack((*_obj2D)->key_frame);
        while(_data) {
            VBObjectFile2DKeyFrameFree((VBObjectFile2DKeyFrame**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->key_frame); 
        }
        VBArrayListFree(&(*_obj2D)->key_frame);
        
        _data = VBArrayListRemoveBack((*_obj2D)->frame);
        while(_data) {
            VBObjectFile2DFrameFree((VBObjectFile2DFrame**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->frame); 
        }
        VBArrayListFree(&(*_obj2D)->frame);
        
        while(VBArrayVectorGetLength((*_obj2D)->library_bitmap)) {
            VBObjectFile2DLibraryBitmap* _bitmap = VBArrayVectorRemoveBack((*_obj2D)->library_bitmap);
            VBObjectFile2DLibraryBitmapFree(&_bitmap);
        }
        VBArrayVectorFree(&(*_obj2D)->library_bitmap);
        
        _data = VBArrayListRemoveBack((*_obj2D)->library_movie_clip);
        while(_data) {
            VBObjectFile2DLibraryMovieClipFree((VBObjectFile2DLibraryMovieClip**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->library_movie_clip); 
        }
        VBArrayListFree(&(*_obj2D)->library_movie_clip);
        
        _data = VBArrayListRemoveBack((*_obj2D)->library_graphic);
        while(_data) {
            VBObjectFile2DLibraryGraphicFree((VBObjectFile2DLibraryGraphic**)&_data);
            _data = VBArrayListRemoveBack((*_obj2D)->library_graphic); 
        }
        VBArrayListFree(&(*_obj2D)->library_graphic);
        
        while(VBArrayVectorGetLength((*_obj2D)->library)) {
            VBObjectFile2DLibrary* _library = VBArrayVectorRemoveBack((*_obj2D)->library);
            VBObjectFile2DLibraryFree(&_library);
        }
        VBArrayVectorFree(&(*_obj2D)->library);
        
        while(VBArrayVectorGetLength((*_obj2D)->library_name_id)) {
            VBObjectFile2DLibraryNameID* _library_name_id = VBArrayVectorRemoveBack((*_obj2D)->library_name_id);
            VBObjectFile2DLibraryNameIDFree(&_library_name_id);
        }
        VBArrayVectorFree(&(*_obj2D)->library_name_id);
        
        VBFileFree(&(*_obj2D)->file);
        
        VBSystemFree(*_obj2D);
        *_obj2D = VBNull;
    } 
}

void VBObjectFile2DLoad(VBObjectFile2D* _obj2D, VBString* _path) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLoad() - VBNull인 오브첵트 파일은 로드할 수 없습니다. VBObject2DAlloc()하지 않은 파일을 사용하고 있을 수 있습니다.");
    if(_path == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLoad() - VBNull인 파일패스로는 오브첵트 파일을 로드할 수 없습니다.                                         유효하지 않은 패스를 사용하고 있을 수 있습니다.");
#endif
    
    if(_obj2D) {
        //obj파일 열기
        VBFileOpen(_obj2D->file, _path, VBFileMode_Read);
        
        VBULong _i, _j, _k;
        VBULong _length;
        
        VBFileReadLong(_obj2D->file, &_obj2D->uv_w);
        VBFileReadLong(_obj2D->file, &_obj2D->uv_h);
        VBFileReadLong(_obj2D->file, &_obj2D->fl_w);
        VBFileReadLong(_obj2D->file, &_obj2D->fl_h);
        printf("stage : %i %i %i %i\n", _obj2D->uv_w, _obj2D->uv_h, _obj2D->fl_w, _obj2D->fl_h);
        
        VBFileReadFloat(_obj2D->file, &_obj2D->frame_rate);
        printf("frame rate : %f\n", _obj2D->frame_rate);
        
        //Library Name ID길이 읽기
        /******************************READ FILE******************************/
        VBFileReadULong(_obj2D->file, &_length);
        printf("library length: %ld\n", _length);
        for(_i = 0; _i < _length; _i++) {
            VBULong _library_name_data_length;
            //Library Name ID의 name문자열 길이 읽기
            /******************************READ FILE******************************/
            VBFileReadULong(_obj2D->file, &_library_name_data_length);
            VBByte* _library_name_data = VBSystemCalloc(_library_name_data_length + 1, sizeof(VBChar));
            printf("%ld ", _library_name_data_length);
            //Library Name ID의 name문자열 읽기
            /******************************READ FILE******************************/
            VBFileReadBytes(_obj2D->file, _library_name_data, _library_name_data_length * sizeof(VBChar));
            VBString* _library_name = VBStringInitWithCString(VBStringAlloc(), (VBChar*)_library_name_data);
            VBSystemFree(_library_name_data);
            printf("%s ", (char*)_library_name_data);
            
            VBULong _library_id;
            //Library Name ID의 id 읽기
            /******************************READ FILE******************************/
            VBFileReadULong(_obj2D->file, &_library_id);
            
            //Library Name ID생성하고 저장
            VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DLibraryNameIDInitWithIDAndName(VBObjectFile2DLibraryNameIDAlloc(), _library_id, _library_name);
            VBArrayVectorAddBack(_obj2D->library_name_id, _library_name_id);
            printf("%ld\n", _library_name_id->libraryID);
        }
        
        //UV(vertex, texcoord)가 있는 라이브러리의 길이 읽기(플래쉬의 비트맵)
        /******************************READ FILE******************************/
        VBFileReadULong(_obj2D->file, &_length);
        printf("bitmap length %ld\n", _length);
        for(_i = 0; _i < _length; _i++) {
            VBULong _library_id;
            //매치시킬 해당 Library Name ID를 찾기위해 id 읽기
            /******************************READ FILE******************************/
            VBFileReadULong(_obj2D->file, &_library_id);
            VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByID(_obj2D, _library_id);
            
            VBULong _texcoord_vector_length;
            //texcoord길이 읽기
            /******************************READ FILE******************************/
            VBFileReadULong(_obj2D->file, &_texcoord_vector_length);
            VBVector2D _texcoord_vector[_texcoord_vector_length];
            //texcoord읽기
            /******************************READ FILE******************************/
            
            VBFileReadBytes(_obj2D->file, (VBByte*)_texcoord_vector, _texcoord_vector_length * sizeof(VBVector2D));
            
            //비트맵 생성하고 저장
            VBObjectFile2DLibraryBitmap* _bitmap = VBObjectFile2DLibraryBitmapInitWithData(VBObjectFile2DLibraryBitmapAlloc(), _texcoord_vector_length, _texcoord_vector);
            VBArrayVectorAddBack(_obj2D->library_bitmap, _bitmap);
            
            //라이브러리 생성하고 저장
            VBObjectFile2DLibrary* _library = VBObjectFile2DLibraryInitWithType(VBObjectFile2DLibraryAlloc(), _library_name_id, VBObjectFile2DLibraryType_Bitmap, _bitmap);
            VBArrayVectorAddBack(_obj2D->library, _library);
            printf("bitmap uv %s %ld ", (char*)_library_name_id->libraryName->data, _library_name_id->libraryID);
            float* _tt = (float*)_texcoord_vector;
			int i = 0;
            for(; i < _texcoord_vector_length; i++) {
                printf("%f,%f,", *(_tt), *(_tt+1));
                _tt+=2;
            }
            printf("\n");
        }
        
        //비트맵을 제외한 모든 라이브러리의 길이 읽기(그래픽 또는 무비클립)
        /******************************READ FILE******************************/
        VBFileReadULong(_obj2D->file, &_length);
        printf("none bitmap length: %ld\n", _length);
        for(_i = 0; _i < _length; _i++) {
            VBObjectFile2DLibraryNameID* _library_name_id = VBNull;
            VBObjectFile2DLibraryType _library_type = VBObjectFile2DLibraryType_None;
            VBObjectFile2DLibrary* _library = VBNull;
            void* _library_base = VBNull;
            
            VBULong _library_id;
            //매치시킬 해당 Library Name ID를 찾기위해 id 읽기
            /******************************READ FILE******************************/
            VBFileReadULong(_obj2D->file, &_library_id);
            _library_name_id = VBObjectFile2DGetLibraryNameIDByID(_obj2D, _library_id);
            
            //라이브러리 타입 읽기
            /******************************READ FILE******************************/
            VBULong _tmp_lib_type;
            VBFileReadULong(_obj2D->file, &_tmp_lib_type);
            _library_type = _tmp_lib_type;
            printf("none bitmap %s %ld %ld, ", (char*)_library_name_id->libraryName->data, _tmp_lib_type, _library_name_id->libraryID);
            
            if(_library_type == VBObjectFile2DLibraryType_Graphic || _library_type == VBObjectFile2DLibraryType_MovieClip) {
                VBObjectFile2DFrame* _frame = VBNull;
                
                VBULong _frame_total;
                //프레임 갯수 읽기
                /******************************READ FILE******************************/
                VBFileReadULong(_obj2D->file, &_frame_total);
                printf("%ld,", _frame_total);
                
                //타입이 그래픽이나 무비클립일 경우 프레임이 존재하므로 프래임 생성후 배열에 저장함
                _frame = VBObjectFile2DFrameInit(VBObjectFile2DFrameAlloc());
                _frame->total_frame = _frame_total;
                VBArrayListAddBack(_obj2D->frame, _frame);
                
                VBULong _key_frame_length;
                //키프레임의 갯수 읽기
                /******************************READ FILE******************************/
                VBFileReadULong(_obj2D->file, &_key_frame_length);
                printf("%ld\n", _key_frame_length);
                
                //키프레임과 키프레임을 연결하기위한 배열
                VBULong _key_frame_id_arr[_key_frame_length];
                VBULong _next_key_frame_id_arr[_key_frame_length];
                VBObjectFile2DKeyFrame* _key_frame_arr[_key_frame_length];
                for(_j = 0; _j < _key_frame_length; _j++) {
                    _key_frame_id_arr[_j] = 0;
                    _next_key_frame_id_arr[_j] = 0;
                    _key_frame_arr[_j] = VBNull;
                    VBObjectFile2DKeyFrame* _key_frame = VBNull;
                    void* _element_base = VBNull;
                    VBObjectFile2DKeyFrameElement* _key_frame_element = VBNull;
                    VBObjectFile2DKeyFrameElementType _key_frame_element_type;
                    VBObjectFile2DLibraryNameID* _key_frame_element_library_name_id = VBNull;
                    VBString* _instance_name = VBNull;
                    VBULong _depth;
                    VBULong _begin_frame;
                    VBULong _end_frame;
                    VBMatrix2DWrapper _matrix_wrapper;
                    VBColorAdvanced _color_advanced;
                    VBBlendMode _blend_mode;
                    VBObjectFile2DTransitionType _transition_type;
                    VBULong _transition_single_bezier_vector_length;
                    VBVector2D* _transition_single_bezier_vector = VBNull;
                    VBULong _transition_position_bezier_vector_length;
                    VBVector2D* _transition_position_bezier_vector = VBNull;
                    VBULong _transition_rotation_bezier_vector_length;
                    VBVector2D* _transition_rotation_bezier_vector = VBNull;
                    VBULong _transition_scale_bezier_vector_length;
                    VBVector2D* _transition_scale_bezier_vector = VBNull;
                    VBULong _transition_color_bezier_vector_length;
                    VBVector2D* _transition_color_bezier_vector = VBNull;
                    VBObjectFile2DTransition* _transition = VBNull;
                    
                    //키프레임에 놓여진 오브젝트 타입 읽기
                    /******************************READ FILE******************************/
                    VBULong _tmp_element_type;
                    VBFileReadULong(_obj2D->file, &_tmp_element_type);
                    _key_frame_element_type = _tmp_element_type;
                    
                    VBULong _key_frame_element_library_id;
                    //키프레임에 놓여진 오브젝트 라이브러리 아이디 읽기
                    /******************************READ FILE******************************/
                    VBFileReadULong(_obj2D->file, &_key_frame_element_library_id);
                    _key_frame_element_library_name_id = VBObjectFile2DGetLibraryNameIDByID(_obj2D, _key_frame_element_library_id);
                    printf("    %s %ld %ld\n", (char*)_key_frame_element_library_name_id->libraryName->data, _key_frame_element_library_name_id->libraryID, _tmp_element_type);
                    
                    //키프레임의 오브젝트가 무비클립일 경우
                    if(_key_frame_element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                        VBULong _instance_name_byte_length;
                        VBChar* _instance_name_byte;
                        //오브젝트가 무비클립일 경우 인스턴스네임의 길이 읽기
                        /******************************READ FILE******************************/
                        VBFileReadULong(_obj2D->file, &_instance_name_byte_length);
                        _instance_name_byte = VBSystemCalloc(_instance_name_byte_length + 1, sizeof(VBChar));
                        printf("    instance name len:%ld\n", _instance_name_byte_length);
                        //인스턴스네임 읽기
                        /******************************READ FILE******************************/
                        if(_instance_name_byte_length) {
                            VBFileReadBytes(_obj2D->file, (VBByte*)_instance_name_byte, _instance_name_byte_length * sizeof(VBChar));
                            printf("    instance name:\"%s\"\n", _instance_name_byte);
                            _instance_name = VBStringInitWithCString(VBStringAlloc(), _instance_name_byte);
                            printf("    instance name:\"%s\"\n", _instance_name->data);
                            VBSystemFree(_instance_name_byte);
                        } else {
                            _instance_name = VBStringInitWithCString(VBStringAlloc(), "");
                        }
                    }
                    
                    //depth
                    /******************************READ FILE******************************/
                    VBFileReadULong(_obj2D->file, &_depth);
                    printf(" depth:%ld, ", _depth);
                    //키프레임의 시작프레임과 끝나는 프레임 읽기
                    /******************************READ FILE******************************/
                    VBFileReadULong(_obj2D->file, &_begin_frame);
                    /******************************READ FILE******************************/
                    VBFileReadULong(_obj2D->file, &_end_frame);
                    _end_frame++;
                    printf(" %ld~%ld ", _begin_frame, _end_frame);
                    
                    //키프레임의 오브젝트가 비트맵이나 그래픽 또는 무비클립일 경우
                    if(_key_frame_element_type == VBObjectFile2DKeyFrameElementType_Bitmap ||
                       _key_frame_element_type == VBObjectFile2DKeyFrameElementType_Graphic ||
                       _key_frame_element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                        //키프레임의 아이디와 다음 키프레임 아이디 읽기
                        /******************************READ FILE******************************/
                        VBFileReadULong(_obj2D->file, &_key_frame_id_arr[_j]);
                        /******************************READ FILE******************************/
                        VBFileReadULong(_obj2D->file, &_next_key_frame_id_arr[_j]);
                        printf("%ld %ld\n", _key_frame_id_arr[_j], _next_key_frame_id_arr[_j]);
                        
                        _matrix_wrapper = VBMatrix2DWrapperLoadIdentity();
                        
                        VBSize _vector_size = sizeof(VBVector2D);
                        VBVector2D _vector;
                        
                        //위치 읽기
                        /******************************READ FILE******************************/
                        VBFileReadBytes(_obj2D->file, (VBByte*)&_vector, _vector_size);
                        _matrix_wrapper = VBMatrix2DWrapperSetPosition(_matrix_wrapper, _vector);
                        printf("    position %f, %f\n", _vector.x, _vector.y);
                        
                        //앵커 읽기
                        /******************************READ FILE******************************/
                        VBFileReadBytes(_obj2D->file, (VBByte*)&_vector, _vector_size);
                        _matrix_wrapper = VBMatrix2DWrapperSetAnchor(_matrix_wrapper, _vector);
                        printf("    anchor %f, %f\n", _vector.x, _vector.y);
                        
                        VBFloat _rotation;
                        //각도 읽기
                        /******************************READ FILE******************************/
                        
                        VBFileReadBytes(_obj2D->file, (VBByte*)&_rotation, sizeof(VBFloat));
                        _matrix_wrapper = VBMatrix2DWrapperSetRotation(_matrix_wrapper, _rotation);
                        printf("    rotation %f\n", _rotation);
                        
                        //스케일 읽기
                        /******************************READ FILE******************************/
                        VBFileReadBytes(_obj2D->file, (VBByte*)&_vector, _vector_size);
                        _matrix_wrapper = VBMatrix2DWrapperSetScale(_matrix_wrapper, _vector);
                        printf("    scale %f, %f\n", _vector.x, _vector.y);
                        
                        //찌그러짐 읽기
                        /******************************READ FILE******************************/
                        VBFileReadBytes(_obj2D->file, (VBByte*)&_vector, _vector_size);
                        _matrix_wrapper = VBMatrix2DWrapperSetShear(_matrix_wrapper, _vector);
                        printf("    skew %f, %f\n", _vector.x, _vector.y);
                        
                        _matrix_wrapper = VBMatrix2DWrapperUpdate(_matrix_wrapper);
                        
                        //키프레임의 오브젝트가 그래픽 또는 무비클립일 경우
                        if(_key_frame_element_type == VBObjectFile2DKeyFrameElementType_Graphic ||
                           _key_frame_element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                            //색상 읽기
                            /******************************READ FILE******************************/
                            VBFileReadBytes(_obj2D->file, (VBByte*)&_color_advanced, sizeof(VBColorAdvanced));;
                            
                            printf("color advanced detail %i %i %i %i, %i %i %i %i\n",
                                   _color_advanced.red_percent,_color_advanced.green_percent, _color_advanced.blue_percent, _color_advanced.alpha_percent,
                                   _color_advanced.red_amount, _color_advanced.green_amount, _color_advanced.blue_amount,
                                   _color_advanced.alpha_amount);
                            
                            
                            //블렌드모드 읽기
                            /******************************READ FILE******************************/
                            VBFileReadBytes(_obj2D->file, (VBByte*)&_blend_mode, sizeof(VBBlendMode));
                            
                            //트렌지션 타입 읽기
                            /******************************READ FILE******************************/
                            VBFileReadBytes(_obj2D->file, (VBByte*)&_transition_type, sizeof(VBObjectFile2DTransitionType));
                            printf("    transition type %i\n", _transition_type);
                            if(_transition_type == VBObjectFile2DTransitionType_SingleBezier) {
                                //베지어 곡선의 길이 읽기
                                /******************************READ FILE******************************/
                                VBFileReadULong(_obj2D->file, &_transition_single_bezier_vector_length);
                                printf("    transition length %ld\n", _transition_single_bezier_vector_length);
                                VBSize _bezier_data_size;
                                if(_transition_single_bezier_vector_length) { 
                                    _bezier_data_size = _transition_single_bezier_vector_length * sizeof(VBVector2D);
                                    _transition_single_bezier_vector = VBSystemMalloc(_bezier_data_size);
                                    //베지어 곡선 벡터 읽기
                                    /******************************READ FILE******************************/
                                    VBFileReadBytes(_obj2D->file, (VBByte*)_transition_single_bezier_vector, _bezier_data_size);
                                }
                                
                                //읽은 정보로 싱글 트렌지션 생성
                                _transition = VBObjectFile2DTransitionInitWithSingleData(VBObjectFile2DTransitionAlloc(), _transition_single_bezier_vector_length, _transition_single_bezier_vector);
                            } else if(_transition_type == VBObjectFile2DTransitionType_MultiBezier) {
                                //위치 트렌지션 베지어 곡선의 길이 읽기
                                /******************************READ FILE******************************/
                                VBFileReadULong(_obj2D->file, &_transition_position_bezier_vector_length);
                                VBSize _bezier_data_size;
                                if(_transition_position_bezier_vector_length) {
                                    _bezier_data_size = _transition_position_bezier_vector_length * sizeof(VBVector2D);
                                    _transition_position_bezier_vector = VBSystemMalloc(_bezier_data_size);
                                    //위치 트렌지션 베지어 곡선 읽기
                                    /******************************READ FILE******************************/
                                    VBFileReadBytes(_obj2D->file, (VBByte*)_transition_position_bezier_vector, _bezier_data_size);
                                }
                                
                                //회전 트렌지션 베지어 곡선의 길이 읽기
                                /******************************READ FILE******************************/
                                VBFileReadULong(_obj2D->file, &_transition_rotation_bezier_vector_length);
                                if(_transition_rotation_bezier_vector_length) {
                                    _bezier_data_size = _transition_rotation_bezier_vector_length * sizeof(VBVector2D);
                                    _transition_rotation_bezier_vector = VBSystemMalloc(_bezier_data_size);
                                    //회전 트렌지션 베지어 곡선 읽기
                                    /******************************READ FILE******************************/
                                    VBFileReadBytes(_obj2D->file, (VBByte*)_transition_rotation_bezier_vector, _bezier_data_size);
                                }
                                
                                //스케일 트렌지션 베지어 곡선의 길이 읽기
                                /******************************READ FILE******************************/
                                VBFileReadULong(_obj2D->file, &_transition_scale_bezier_vector_length);
                                if(_transition_scale_bezier_vector_length) {
                                    _bezier_data_size = _transition_scale_bezier_vector_length * sizeof(VBVector2D);
                                    _transition_scale_bezier_vector = VBSystemMalloc(_bezier_data_size);
                                    //스케일 트렌지션 베지어 곡선 읽기
                                    /******************************READ FILE******************************/
                                    VBFileReadBytes(_obj2D->file, (VBByte*)_transition_scale_bezier_vector, _bezier_data_size);
                                }
                                
                                //색상 트렌지션 베지어 곡선의 길이 읽기
                                /******************************READ FILE******************************/
                                VBFileReadULong(_obj2D->file, &_transition_color_bezier_vector_length);
                                if(_transition_color_bezier_vector_length) {
                                    _bezier_data_size = _transition_color_bezier_vector_length * sizeof(VBVector2D);
                                    _transition_color_bezier_vector = VBSystemMalloc(_bezier_data_size);
                                    //색상 트렌지션 베지어 곡선 읽기
                                    /******************************READ FILE******************************/
                                    VBFileReadBytes(_obj2D->file, (VBByte*)_transition_color_bezier_vector, _bezier_data_size);
                                }
                                
                                //읽은 정보로 멀티 트렌지션 생성하고 배열에 저장
                                _transition = VBObjectFile2DTransitionInitWithMultiData(VBObjectFile2DTransitionAlloc(), _transition_position_bezier_vector_length, _transition_position_bezier_vector, _transition_rotation_bezier_vector_length, _transition_rotation_bezier_vector, _transition_scale_bezier_vector_length, _transition_scale_bezier_vector, _transition_color_bezier_vector_length, _transition_color_bezier_vector);
                                VBArrayListAddBack(_obj2D->transition, _transition);
                            }
                        }
                    }
                    
                    //타입에 맞춰서 키프레임 요소의 데이터 생성하고 저장
                    if(_key_frame_element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
                        _element_base = VBObjectFile2DKeyFrameElementGraphicInitWithData(VBObjectFile2DKeyFrameElementGraphicAlloc(), _blend_mode, _transition, _matrix_wrapper, _color_advanced);
                        VBArrayListAddBack(_obj2D->element_graphic, _element_base);
                    } else if(_key_frame_element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                        _element_base = VBObjectFile2DKeyFrameElementMovieClipInitWithData(VBObjectFile2DKeyFrameElementMovieClipAlloc(), _instance_name, _blend_mode, _transition, _matrix_wrapper, _color_advanced);
                        VBArrayListAddBack(_obj2D->element_movie_clip, _element_base);
                    } else if(_key_frame_element_type == VBObjectFile2DKeyFrameElementType_Bitmap) {
                        _element_base = VBObjectFile2DKeyFrameElementBitmapInitWithData(VBObjectFile2DKeyFrameElementBitmapAlloc(), _matrix_wrapper);
                        VBArrayListAddBack(_obj2D->element_bitmap, _element_base);
                        
                    }
                    //키프레임요소 생성하고 저장
                    _key_frame_element = VBObjectFile2DKeyFrameElementInitWithType(VBObjectFile2DKeyFrameElementAlloc(), _key_frame_element_type, _element_base);
                    VBArrayListAddBack(_obj2D->element, _key_frame_element);
                    //타입에 맞춰 키프레임 생성하고 저장
                    _key_frame = VBObjectFile2DKeyFrameInitWithData(VBObjectFile2DKeyFrameAlloc(), _key_frame_element_library_name_id, _begin_frame, _end_frame, _key_frame_element);
                    _key_frame->depth = _depth;
                    VBArrayListAddBack(_obj2D->key_frame, _key_frame);
                    
                    _key_frame_arr[_j] = _key_frame;
                    
                    VBArrayVectorAddBack(_frame->key_frame, _key_frame);
                    
                    //메모리 점유하고 있는 필요없는 포인터들 메모리 해제
                    if(_instance_name)
                        VBStringFree(&_instance_name);
                    if(_transition_single_bezier_vector)
                        VBSystemFree(_transition_single_bezier_vector);
                    if(_transition_position_bezier_vector)
                        VBSystemFree(_transition_position_bezier_vector);
                    if(_transition_rotation_bezier_vector)
                        VBSystemFree(_transition_rotation_bezier_vector);
                    if(_transition_scale_bezier_vector)
                        VBSystemFree(_transition_scale_bezier_vector);
                    if(_transition_color_bezier_vector)
                        VBSystemFree(_transition_color_bezier_vector);
                }
                
                //프레임있는 라이브러리 생성
                if(_library_type == VBObjectFile2DLibraryType_Graphic) {
                    _library_base = VBObjectFile2DLibraryGraphicInitWithData(VBObjectFile2DLibraryGraphicAlloc(), _frame);
                } else if(_library_type == VBObjectFile2DLibraryType_MovieClip) {
                    _library_base = VBObjectFile2DLibraryMovieClipInitWithData(VBObjectFile2DLibraryMovieClipAlloc(), _frame);
                }
                
                //라이브러리 생성후 내부 키프레임 요소가 그래픽이나 무비클립일 경우 
                //에니메이션을 위한 링크드 리스트 연결
                for(_j = 0; _j < _key_frame_length; _j++) {
                    VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame_arr[_j]);
                    VBObjectFile2DKeyFrameElementType _element_type = VBObjectFile2DKeyFrameElementGetType(_element);
                    //요소가 그래픽이나 무비클립일 경우만
                    if(_element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
                        VBObjectFile2DKeyFrameElementGraphic* _graphic = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                        //트렌지션이 있고 링크드리스트가 연결이 안되어 있을경우만 검색
                        if(VBObjectFile2DKeyFrameElementGraphicGetTransition(_graphic) && VBObjectFile2DKeyFrameElementGraphicGetNext(_graphic) == VBNull && _next_key_frame_id_arr[_j] != 0) {
                            //검색하여서 다음프레임의 아이디랑 같은 키프레임의 포인터를 링크드 리스트로 연결
                            for(_k = 0; _k < _key_frame_length; _k++) {
                                if(_key_frame_id_arr[_k] == _next_key_frame_id_arr[_j]) {
                                    VBObjectFile2DKeyFrameElementGraphicSetNext(_graphic, VBObjectFile2DKeyFrameElementGetBaseElement(VBObjectFile2DKeyFrameGetElement(_key_frame_arr[_k])));
                                    break;
                                }
                            }
                        }
                    } else if(_element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                        VBObjectFile2DKeyFrameElementMovieClip* _movie_clip = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                        //트렌지션이 있고 링크드리스트가 연결이 안되어 있을경우만 검색
                        if(VBObjectFile2DKeyFrameElementMovieClipGetTransition(_movie_clip) && VBObjectFile2DKeyFrameElementMovieClipGetNext(_movie_clip) == VBNull && _next_key_frame_id_arr[_j] != 0) {
                            //검색하여서 다음프레임의 아이디랑 같은 키프레임의 포인터를 링크드 리스트로 연결
                            for(_k = 0; _k < _key_frame_length; _k++) {
                                if(_key_frame_id_arr[_k] == _next_key_frame_id_arr[_j]) {
                                    VBObjectFile2DKeyFrameElementMovieClipSetNext(_movie_clip, VBObjectFile2DKeyFrameElementGetBaseElement(VBObjectFile2DKeyFrameGetElement(_key_frame_arr[_k])));
                                    break;
                                }
                            }
                        }
                    }
                    int _key_frame_length = _key_frame_arr[_j]->end_frame - _key_frame_arr[_j]->begin_frame + 1;
                    int _key_i;
                    if(_element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
                        VBObjectFile2DKeyFrameElementGraphic* _graphic = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                        if(VBObjectFile2DKeyFrameElementGraphicGetNext(_graphic)) {
                            _key_frame_arr[_j]->none_real_time_matrix = VBSystemCalloc(sizeof(VBMatrix2DWrapper), _key_frame_length);
                            _key_frame_arr[_j]->none_real_time_color = VBSystemCalloc(sizeof(VBColorAdvanced), _key_frame_length);
                            for(_key_i = 0; _key_i < _key_frame_length; _key_i++) {
                                VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(_graphic, (float)_key_i / (float)_key_frame_length, _key_frame_arr[_j]->none_real_time_matrix + _key_i, _key_frame_arr[_j]->none_real_time_color + _key_i);
                            }
                        } else {
                            _key_frame_arr[_j]->none_real_time_matrix = VBSystemCalloc(sizeof(VBMatrix2DWrapper), 1);
                            _key_frame_arr[_j]->none_real_time_color = VBSystemCalloc(sizeof(VBColorAdvanced), 1);
                            *_key_frame_arr[_j]->none_real_time_matrix = _graphic->matrix;
                            *_key_frame_arr[_j]->none_real_time_color = _graphic->color;
                        }
                    } else if(_element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                        VBObjectFile2DKeyFrameElementMovieClip* _mc = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                        if(VBObjectFile2DKeyFrameElementMovieClipGetNext(_mc)) {
                            _key_frame_arr[_j]->none_real_time_matrix = VBSystemCalloc(sizeof(VBMatrix2DWrapper), _key_frame_length);
                            _key_frame_arr[_j]->none_real_time_color = VBSystemCalloc(sizeof(VBColorAdvanced), _key_frame_length);
                            for(_key_i = 0; _key_i < _key_frame_length; _key_i++) {
                                VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(_mc, (float)_key_i / (float)_key_frame_length, _key_frame_arr[_j]->none_real_time_matrix + _key_i, _key_frame_arr[_j]->none_real_time_color + _key_i);
                            }
                        } else {
                            _key_frame_arr[_j]->none_real_time_matrix = VBSystemCalloc(sizeof(VBMatrix2DWrapper), 1);
                            _key_frame_arr[_j]->none_real_time_color = VBSystemCalloc(sizeof(VBColorAdvanced), 1);
                            *_key_frame_arr[_j]->none_real_time_matrix = _mc->matrix;
                            *_key_frame_arr[_j]->none_real_time_color = _mc->color;
                        }
                    } else if(_element_type == VBObjectFile2DKeyFrameElementType_Bitmap) {
                        _key_frame_arr[_j]->none_real_time_matrix = VBSystemCalloc(sizeof(VBMatrix2DWrapper), 1);
                        _key_frame_arr[_j]->none_real_time_color = VBSystemCalloc(sizeof(VBColorAdvanced), 1);
                        VBObjectFile2DKeyFrameElementBitmap* _bmp = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                        *_key_frame_arr[_j]->none_real_time_matrix = _bmp->matrix;
                        *_key_frame_arr[_j]->none_real_time_color = VBColorAdvancedLoadIdentity();
                    }
                }
            }
            
            //라이브러리 배열에 저장
            _library = VBObjectFile2DLibraryInitWithType(VBObjectFile2DLibraryAlloc(), _library_name_id, _library_type, _library_base);
            VBArrayVectorAddBack(_obj2D->library, _library);
        }
        
        VBFileClose(_obj2D->file);
    }
}

VBObjectFile2DLibraryNameID* VBObjectFile2DGetLibraryNameIDByName(VBObjectFile2D* _obj2D, VBString* _name) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryNameIDByName() - VBNull인 오브첵트 파일로는 라이브러리 네임 아아이디를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다.");
    if(_name == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryNameIDByName() - VBNull인 이름으로는 라이브러리 네임 아이디를 구할 수 없습니다.");
#endif
    
    VBULong _i;
    for(_i = 0; _i < VBObjectFile2DGetLibraryNameIDLength(_obj2D); _i++) {
        VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameAt(_obj2D, _i);
        if(VBStringIsEqual(VBObjectFile2DLibraryNameIDGetName(_library_name_id), _name)) {
            return _library_name_id;
        }
    }
    return VBNull;
}

VBObjectFile2DLibraryNameID* VBObjectFile2DGetLibraryNameIDByID(VBObjectFile2D* _obj2D, VBULong _id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryNameIDByID() - VBNull인 오브첵트 파일로는 라이브러리 네임 아아이디를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    VBULong _i;
    for(_i = 0; _i < VBObjectFile2DGetLibraryNameIDLength(_obj2D); _i++) {
        VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameAt(_obj2D, _i);
        if(VBObjectFile2DLibraryNameIDGetID(_library_name_id) == _id) {
            return _library_name_id;
        }
    }
    return VBNull;
}


VBULong VBObjectFile2DGetLibraryNameIDLength(VBObjectFile2D* _obj2D) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryNameIDLength() - VBNull인 오브첵트 파일로는 라이브러리 네임 아아이디의 길이를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif  
    
    return VBArrayVectorGetLength(_obj2D->library_name_id);
}

VBObjectFile2DLibraryNameID* VBObjectFile2DGetLibraryNameAt(VBObjectFile2D* _obj2D, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryNameAt() - VBNull인 오브첵트 파일로는 라이브러리 네임의 위치를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayVectorGetDataAt(_obj2D->library_name_id, _at);
}

VBULong VBObjectFile2DGetLibraryLength(VBObjectFile2D* _obj2D) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryLength() - VBNull인 오브첵트 파일로는 라이브러리의 길이를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayVectorGetLength(_obj2D->library);
}

VBULong VBObjectFile2DGetLibraryBitmapLength(VBObjectFile2D* _obj2D) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryBitmapLength() - VBNull인 오브첵트 파일로는 라이브러리 비트맵의 길이를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayVectorGetLength(_obj2D->library_bitmap);
}

VBULong VBObjectFile2DGetLibraryGraphicLength(VBObjectFile2D* _obj2D) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicLength() - VBNull인 오브첵트 파일로는 라이브러리 그래픽의 길이를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayListGetLength(_obj2D->library_graphic);
}

VBULong VBObjectFile2DGetLibraryMovieClipLength(VBObjectFile2D* _obj2D) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryMovieClipLength() - VBNull인 오브첵트 파일로는 라이브러리 무비클립의 길이를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayListGetLength(_obj2D->library_movie_clip);
}

VBObjectFile2DLibrary* VBObjectFile2DGetLibraryAt(VBObjectFile2D* _obj2D, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryAt() - VBNull인 오브첵트 파일로는 라이브러리의 위치를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayVectorGetDataAt(_obj2D->library, _at);
}

VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapAt(VBObjectFile2D* _obj2D, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryBitmapAt() - VBNull인 오브첵트 파일로는 라이브러리 비트맴의 위치를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayVectorGetDataAt(_obj2D->library_bitmap, _at);
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicAt(VBObjectFile2D* _obj2D, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicAt() - VBNull인 오브첵트 파일로는 라이브러리 그래픽의 위치를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayListNodeGetData(VBArrayListGetNodeAt(_obj2D->library_graphic, _at));
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipAt(VBObjectFile2D* _obj2D, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryMovieClipAt() - VBNull인 오브첵트 파일로는 라이브러리 무비클립의 위치를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    return VBArrayListNodeGetData(VBArrayListGetNodeAt(_obj2D->library_movie_clip, _at));
}

VBObjectFile2DLibrary* VBObjectFile2DGetLibraryByName(VBObjectFile2D* _obj2D, VBString* _name) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryByName() - VBNull인 오브첵트 파일로는 라이브러리를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    
    if(_name == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryByName() - VBNull인 이름으로 라이브러리를 구할 수 없습니다");
#endif  
    
    VBObjectFile2DLibraryNameID* _name_id = VBObjectFile2DGetLibraryNameIDByName(_obj2D, _name);
    return VBObjectFile2DGetLibraryByNameID(_obj2D, _name_id);
}

VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapByName(VBObjectFile2D* _obj2D, VBString* _name) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryBitmapByName() - VBNull인 오브첵트 파일로는 라이브러리 비트맵을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    if(_name == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: - VBNull인 이름으로 라이브러리 비트맵을 구할 수 없습니다");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByName(_obj2D, _name);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_Bitmap)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicByName(VBObjectFile2D* _obj2D, VBString* _name) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicByName() - VBNull인 오브첵트 파일로는 라이브러리 그래픽을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    
    if(_name == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicByName() - VBNull인 이름으로 라이브러리 그래픽을 구할 수 없습니다");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByName(_obj2D, _name);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_Graphic)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipByName(VBObjectFile2D* _obj2D, VBString* _name) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryMovieClipByName() - VBNull인 오브첵트 파일로는 라이브러리 무비클립을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    
    if(_name == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryMovieClipByName() - VBNull인 이름으로 라이브러리 그래픽을 구할 수 없습니다");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByName(_obj2D, _name);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_MovieClip)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibrary* VBObjectFile2DGetLibraryByID(VBObjectFile2D* _obj2D, VBULong _id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryByID() - VBNull인 오브첵트 파일로는 라이브러리를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    VBObjectFile2DLibraryNameID* _name_id = VBObjectFile2DGetLibraryNameIDByID(_obj2D, _id);
    return VBObjectFile2DGetLibraryByNameID(_obj2D, _name_id);
}

VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapByID(VBObjectFile2D* _obj2D, VBULong _id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryBitmapByID() - VBNull인 오브첵트 파일로는 라이브러리 비트맵을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByID(_obj2D, _id);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_Bitmap)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicByID(VBObjectFile2D* _obj2D, VBULong _id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicByID() - VBNull인 오브첵트 파일로는 라이브러리 그래픽을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByID(_obj2D, _id);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_Graphic)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipByID(VBObjectFile2D* _obj2D, VBULong _id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryMovieClipByID() - VBNull인 오브첵트 파일로는 라이브러리 무비클립을  구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByID(_obj2D, _id);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_MovieClip)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibrary* VBObjectFile2DGetLibraryByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryByNameID() - VBNull인 오브첵트 파일로는 라이브러리를 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    if(_name_id == 0) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryByNameID() - VBNull인 이름 아이디로 라이브러리를 구할 수 없습니다.");
#endif  
    
    VBULong _i;
    for(_i = 0; _i < VBObjectFile2DGetLibraryLength(_obj2D); _i++) {
        VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryAt(_obj2D, _i);
        if(VBObjectFile2DLibraryGetNameID(_library) == _name_id) {
            return _library;
        }
    }
    return VBNull;
}
VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryBitmapByNameID() - VBNull인 오브첵트 파일로는 라이브러리 비트맵을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    if(_name_id == 0) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryBitmapByNameID() - VBNull인 이름 아이디로 라이브러리 비트맵을  구할 수 없습니다.");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _name_id);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_Bitmap)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicByNameID() - VBNull인 오브첵트 파일로는 라이브러리 그래픽을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    if(_name_id == 0) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryGraphicByNameID() - VBNull인 이름 아이디로 라이브러리 그래픽을 구할 수 없습니다.");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _name_id);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_Graphic)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_obj2D == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryMovieClipByNameID() - VBNull인 오브첵트 파일로는 라이브러리 무비클립을 구할 수 없습니다. VBObjectFile2DAlloc()하지 않은 파일을 사용했을 수 있습니다");
    if(_name_id == 0) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DGetLibraryByID() - VBNull인 이름 아이디로 라이브러리 무비클립을 구할 수 없습니다.");
#endif  
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _name_id);
    if(VBObjectFile2DLibraryGetType(_library) == VBObjectFile2DLibraryType_MovieClip)
        return VBObjectFile2DLibraryGetBase(_library);
    return VBNull;
}

VBFloat VBObjectFile2DGetFrameRate(VBObjectFile2D* _obj2D) {
    return _obj2D->frame_rate;
}


VBLong VBObjectFile2DGetStageWidth(VBObjectFile2D* _obj2D) {
    return _obj2D->fl_w;
}

VBLong VBObjectFile2DGetStageHeight(VBObjectFile2D* _obj2D) {
    return _obj2D->fl_h;
}

VBLong VBObjectFile2DGetDefaultTextureWidth(VBObjectFile2D* _obj2D) {
    return _obj2D->uv_w;
}

VBLong VBObjectFile2DGetDefaultTextureHeight(VBObjectFile2D* _obj2D) {
    return _obj2D->uv_h;
}
