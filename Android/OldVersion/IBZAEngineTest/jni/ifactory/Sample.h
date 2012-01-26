
#ifndef SAMPLE_H
#define SAMPLE_H

#include "importgl.h"
#include <sys/time.h>
#include <unistd.h>
#include "Display/Core/Math.h"
#include "Display/Object/Camera.h"
#include "Display/Object/ObjFileForModel.h"
#include "Display/Object/Model.h"
#include "Display/Object/Light.h"
#include "Display/Core/Vector.h"
#include "Display/UI/Button.h"
#include "Util/Tween.h"

//#include "stage.h"
#include "Level.h"
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "test", __VA_ARGS__);


#define LOADING_OPACITY 210
#define STAGE_NUMBER 108

enum {
    StageInfoSave		=	0x00,
    StagePageSave		=	0x01,
    FaceBokkSite        =   0x02,
    TwitterSite         =   0x03,
    TutorialClear       =   0x04,
    GameCenterLeaderboard   =   0x05,
    GameCenterAchivement    =   0x06,
    GameResets              =   0x07,
    GameTuTorialStart       =   0x08,
    GameCreditView         =   0x09 ,
    FACEBOOKFANPAGE         =   0x10 ,
};
typedef unsigned char StageInfoEventType;

typedef struct StageInfoEvents StageInfoEvents;             /// 큐 컨트럴과 연결해주는 이벤트
struct StageInfoEvents {
    void* userReference;
    void (*event)(void* userReference, StageInfoEventType type);
};

char* resourcepaths;

typedef struct StageInfo StageInfo;                         /// 스테이지 정보 구조체
struct StageInfo {
	unsigned int stagepoint;
    bool lock;
    unsigned int star;
};

enum {
	GameStaTeTypeTitle				=	0x00,
	GameStaTeTypeLevelSelect		=	0x01,
	GameStaTeTypeGame				=	0x02,
	GameStaTeTypeCredits            =   0x03,
   	GameStaTeTypeTutoial            =	0x04,
   	GameStaTeTypeResetPopup         =	0x05,
};
typedef unsigned char GameStaTeType;                        // 게임 상태 타입


enum {
    GameEvnetNone                   =	0x00,
	GameEvnetLevelStageIn			=	0x01,
	GameEvnetGameOut                =	0x02,
	GameEvnetGameIn                 =	0x03,
	GameEvnetTitleIn                =	0x04,
	GameEvnetGameNext               =	0x05,
	GameEvnetGamePacClear           =	0x06,
	GameEvnetGameTutorial           =	0x07,
	GameEvnetGameTutorialBack       =	0x08,
  	GameEvnetGameTutorialClear       =	0x09,
    GameEvnetGameAllClear           =	0x10,
};
typedef unsigned char GameEvnetType;                        // 게임 안에서 발생 하는 이벤트 정의 타입



typedef struct Sample Sample;


struct Sample {
	char* resourcePath;
	
	ModelManager* manager;                                  // 모델 매니저
	
	TweenManager *tweenmanger;
	Tween *loadingTween;                                    // 로딩 트윈
	
	Camera* camera;
	
	Model* Wmodel;
//	Stage* stages;
	Levels* levels;
 //   Tutorial* tutorial;

	ObjectFile* titleobj;                                   // 타이틀 배경들 OBJ 파일
    ObjectFile* titlelayout;                                // 타이틀 레이아웃 오브젝파일
    ObjectFile* creditlayout;                               // 크레딧 오브젝파일
	
	Model* titleModel;                                      // 타이틀 배경 메인 모델

    Model* aniicecream;                                     // 돌아가는 아이스크림 모델

    Model* titlelayoutModel;                                // 타이틀 레이아웃 메인 모델
	Model* newgameModel;                                    // 플레이버튼 모델
	Model* newgametouchModel;                               // 플레이버튼 터치 모델

   	Model* leftbuttonModel;                                 // 왼쪽 메뉴 버튼
	Model* leftbuttontouchModel;                            // 왼쪽 메뉴 터치 모델
    Model* leftaniModel;                                    // 왼쪽 버튼 위에 애니메이션 모델
    Model* leftMenuaniModel;                                // 왼쪽 메뉴 나오는 애니메이션 모델
    bool leftmenuOnOff;                                     // 왼쪽 메뉴 펼쳐짐여부 체크


    Model* rightbuttonModel;                                // 오른쪽 메뉴 버튼
	Model* rightbuttontouchModel;                           // 오른쪽 메뉴 터치 모델
    Model* rightaniModel;                                   // 오른쪽 버튼 위에 애니메이션 모델
    Model* rightMenuaniModel;                               // 오른쪽 메뉴 나오는 애니메이션 모델
    bool rightmenuOnOff;                                    // 오른쪽 메뉴 펼쳐짐여부 체크

    Model* facebookModel;                                   // 페이스북 팬페이비 버튼
    Model* facebookTouchModel;                              // 페이스북 펜페이지 터치 버튼

    Model* gamecenterModel;                                 // 게임센터 리더보드 버튼
    Model* gamecenterTouchModel;                            // 게임 센터 리더보드 터치 모델

    Model* AchivemnetModel;                                 // 게임센터 어치브먼트 버튼
    Model* AchivemnetTouchModel;                            // 게임센터 어치브먼트 터치 모델

    Model* gameresetModel;                                  //게임 리셋 버튼
    Model* gameresetTouchModel;                             // 게임 리셋 터치 모델

    Model* gameresetPopupModel;                             // 게임 리셋 팝업 배경 모델
    Model* gameresetPopupTxTModel;                          // 게임 리셋 텍스트 모델
    Model* gameresetPopupResetBtnModel;                     // 게임 리셋 팝업 리셋 버튼
    Model* gameresetPopupResetBtntouchModel;                // 게임 리셋 팝업 리셋 터치 모델
    Model* gameresetPopup_cancel_BtnModel;                  // 게임 리셋 팝업 취소 버튼
    Model* gameresetPopup_cancel_BtntouchModel;             // 게임 리셋 팝업 취소 터치 모델

	
    Model* gameinforModel;                                  // 게임 크레딧 버튼
    Model* gameinforTouchModel;                             // 게임 크레딧 터치 모델

    Model* creditBackgroundModel;                           // 크레딧 배경 모델
    Model* creditpaperModel;                                // 크레딧 종이 모델
    Model* creditBtnModel;                                  // 크레딧 백 버튼
    Model* creditBtnTouchModel;                             // 크레딧 백 버튼 터치 모델

	Model* loadingModel;                                    // 로딩시 검은 배경 모델
	Model* loadingTxT;                                      // 로딩시 텍스트 모델
	GameStaTeType gamestate;                                // 게임 상태
	GameEvnetType Gameevent;                                // 게임내 이벤트
	float rgba;                                             // 로딩시 검은배경 알파 조정 변수
	int page;                                               // 팩 선택 페이지 변수
    int selectpage1;                                        // 팩 안의 페이지 변수들
    int selectpage2;
    int selectpage3;
    Array * stageInfoarray;                                 // 게임 스테이지 정보 어레이
    StageInfoEvents stageinfoevent;                         // 뷰 컨트롤러 연결 이벤트

    float railsoundeff;                                     // 타이틀 레일 소리 딜레이 변수

    float creditPosY;                                       // 크레딧 Y 좌표 변수
    bool  creditAutoMove;                                   // 크레딧 오토 무브 변수
    Vector2D gestureStart;                                  // 크레딧 스크롤 첫 터치
	float	gestureLast;                                    // 크레딧 스크롤 마지막 터치

    bool language;                                          // 언어여부
    unsigned int leftEndPoint;                              // 왼쪽 애니 마지막 프레임 체크
    
    bool gamecenters;                                       // 게임 센터 부울값
};

StageInfoEvents StageInfoEventsInit(void* userReference, void (*event)(void* userReference, StageInfoEventType type)) ;         // 뷰 연결 이벤트 함수
void initSample(Sample *game , const char* _resourcePath , int w , int h , bool _gamecenter);   // 게임 초기화 함수
void renderSample(Sample *game , float tick );                                                                                  // 게임 렌더 함수
void freeSample(Sample *game );                                                                                                 // 게임 프리 함수

void TitleLayoutInit(Sample *game , unsigned int _type);            // 타이틀 레이아웃 초기화 함수
void PopupLayoutInit(Sample *game);                                 // 타이틀 팝업 초기화 함수

void TitleLayoutFree(Sample *game);                                 // 타이틀 레이아웃 프리 함수

void GameMultiTaskBackground(Sample *game);                         // 게임 백그라운드로 전환시 함수

void _LevelsEvent(void* userReference ,  LevelEventType eventType); // 레벨 씬에서의 타이틀 이벤트 함수
//void _StageEvent(void* userReference ,  GameStageType eventType);   // 게임에서의 타이틀 이벤트 함수
//void _TutorialEvent(void* userReference ,  GameStageType eventType);// 튜토리얼에서의 타이틀 이벤트 함수
void _LoadingTweenStep(Tween* tween, void* userReference) ;         // 로딩 트윈 스텝
void _LoadingTweenComplete(Tween* tween, void* userReference) ;     // 로딩 트윈 완료


void  _newgameModelTouch(void *userReference, ModelEventTouchArgument argument);        // 플레이버튼 터치 이벤트
void  _leftbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);     // 왼쪽 버튼 터치 이벤트
void  _rightbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);    // 오른쪽 버튼 터치 이벤트

void  _gamecenterbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);   // 게임센터 리더보드 터치 이벤트
void  _AchievementbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);  //  게임센터 어치브먼트 터치 이벤트

void  _facebookbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);     // 페이스북 팬페이지 터치 이벤트
void  _gameresetbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);    // 게임 리셋 버튼 터치 이벤트
void  _gameinforbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);    // 크레딧 버튼 터치 이벤트
void  _gameCreditbackbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);   //크레딧 백버튼 터치 이벤트
void  _gameCreditSwipebuttonModelTouch(void *userReference, ModelEventTouchArgument argument);  // 크레딧 스와이프 터치 이벤트

void  _gameResetPopup_ResetBtn_Touch(void *userReference, ModelEventTouchArgument argument);    // 게임 리셋 팝업 리셋 버튼 터치 이벤트
void  _gameResetPopup_CancelBtn_Touch(void *userReference, ModelEventTouchArgument argument);   // 게임 리셋 팝업 취소 버튼 터치 이벤트


#endif
