
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

typedef struct StageInfoEvents StageInfoEvents;             /// ť ��Ʈ���� �������ִ� �̺�Ʈ
struct StageInfoEvents {
    void* userReference;
    void (*event)(void* userReference, StageInfoEventType type);
};

char* resourcepaths;

typedef struct StageInfo StageInfo;                         /// �������� ���� ����ü
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
typedef unsigned char GameStaTeType;                        // ���� ���� Ÿ��


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
typedef unsigned char GameEvnetType;                        // ���� �ȿ��� �߻� �ϴ� �̺�Ʈ ���� Ÿ��



typedef struct Sample Sample;


struct Sample {
	char* resourcePath;
	
	ModelManager* manager;                                  // �� �Ŵ���
	
	TweenManager *tweenmanger;
	Tween *loadingTween;                                    // �ε� Ʈ��
	
	Camera* camera;
	
	Model* Wmodel;
//	Stage* stages;
	Levels* levels;
 //   Tutorial* tutorial;

	ObjectFile* titleobj;                                   // Ÿ��Ʋ ���� OBJ ����
    ObjectFile* titlelayout;                                // Ÿ��Ʋ ���̾ƿ� ����������
    ObjectFile* creditlayout;                               // ũ���� ����������
	
	Model* titleModel;                                      // Ÿ��Ʋ ��� ���� ��

    Model* aniicecream;                                     // ���ư��� ���̽�ũ�� ��

    Model* titlelayoutModel;                                // Ÿ��Ʋ ���̾ƿ� ���� ��
	Model* newgameModel;                                    // �÷��̹�ư ��
	Model* newgametouchModel;                               // �÷��̹�ư ��ġ ��

   	Model* leftbuttonModel;                                 // ���� �޴� ��ư
	Model* leftbuttontouchModel;                            // ���� �޴� ��ġ ��
    Model* leftaniModel;                                    // ���� ��ư ���� �ִϸ��̼� ��
    Model* leftMenuaniModel;                                // ���� �޴� ������ �ִϸ��̼� ��
    bool leftmenuOnOff;                                     // ���� �޴� ���������� üũ


    Model* rightbuttonModel;                                // ������ �޴� ��ư
	Model* rightbuttontouchModel;                           // ������ �޴� ��ġ ��
    Model* rightaniModel;                                   // ������ ��ư ���� �ִϸ��̼� ��
    Model* rightMenuaniModel;                               // ������ �޴� ������ �ִϸ��̼� ��
    bool rightmenuOnOff;                                    // ������ �޴� ���������� üũ

    Model* facebookModel;                                   // ���̽��� �����̺� ��ư
    Model* facebookTouchModel;                              // ���̽��� �������� ��ġ ��ư

    Model* gamecenterModel;                                 // ���Ӽ��� �������� ��ư
    Model* gamecenterTouchModel;                            // ���� ���� �������� ��ġ ��

    Model* AchivemnetModel;                                 // ���Ӽ��� ��ġ���Ʈ ��ư
    Model* AchivemnetTouchModel;                            // ���Ӽ��� ��ġ���Ʈ ��ġ ��

    Model* gameresetModel;                                  //���� ���� ��ư
    Model* gameresetTouchModel;                             // ���� ���� ��ġ ��

    Model* gameresetPopupModel;                             // ���� ���� �˾� ��� ��
    Model* gameresetPopupTxTModel;                          // ���� ���� �ؽ�Ʈ ��
    Model* gameresetPopupResetBtnModel;                     // ���� ���� �˾� ���� ��ư
    Model* gameresetPopupResetBtntouchModel;                // ���� ���� �˾� ���� ��ġ ��
    Model* gameresetPopup_cancel_BtnModel;                  // ���� ���� �˾� ��� ��ư
    Model* gameresetPopup_cancel_BtntouchModel;             // ���� ���� �˾� ��� ��ġ ��

	
    Model* gameinforModel;                                  // ���� ũ���� ��ư
    Model* gameinforTouchModel;                             // ���� ũ���� ��ġ ��

    Model* creditBackgroundModel;                           // ũ���� ��� ��
    Model* creditpaperModel;                                // ũ���� ���� ��
    Model* creditBtnModel;                                  // ũ���� �� ��ư
    Model* creditBtnTouchModel;                             // ũ���� �� ��ư ��ġ ��

	Model* loadingModel;                                    // �ε��� ���� ��� ��
	Model* loadingTxT;                                      // �ε��� �ؽ�Ʈ ��
	GameStaTeType gamestate;                                // ���� ����
	GameEvnetType Gameevent;                                // ���ӳ� �̺�Ʈ
	float rgba;                                             // �ε��� ������� ���� ���� ����
	int page;                                               // �� ���� ������ ����
    int selectpage1;                                        // �� ���� ������ ������
    int selectpage2;
    int selectpage3;
    Array * stageInfoarray;                                 // ���� �������� ���� ���
    StageInfoEvents stageinfoevent;                         // �� ��Ʈ�ѷ� ���� �̺�Ʈ

    float railsoundeff;                                     // Ÿ��Ʋ ���� �Ҹ� ������ ����

    float creditPosY;                                       // ũ���� Y ��ǥ ����
    bool  creditAutoMove;                                   // ũ���� ���� ���� ����
    Vector2D gestureStart;                                  // ũ���� ��ũ�� ù ��ġ
	float	gestureLast;                                    // ũ���� ��ũ�� ������ ��ġ

    bool language;                                          // ����
    unsigned int leftEndPoint;                              // ���� �ִ� ������ ������ üũ
    
    bool gamecenters;                                       // ���� ���� �οﰪ
};

StageInfoEvents StageInfoEventsInit(void* userReference, void (*event)(void* userReference, StageInfoEventType type)) ;         // �� ���� �̺�Ʈ �Լ�
void initSample(Sample *game , const char* _resourcePath , int w , int h , bool _gamecenter);   // ���� �ʱ�ȭ �Լ�
void renderSample(Sample *game , float tick );                                                                                  // ���� ���� �Լ�
void freeSample(Sample *game );                                                                                                 // ���� ���� �Լ�

void TitleLayoutInit(Sample *game , unsigned int _type);            // Ÿ��Ʋ ���̾ƿ� �ʱ�ȭ �Լ�
void PopupLayoutInit(Sample *game);                                 // Ÿ��Ʋ �˾� �ʱ�ȭ �Լ�

void TitleLayoutFree(Sample *game);                                 // Ÿ��Ʋ ���̾ƿ� ���� �Լ�

void GameMultiTaskBackground(Sample *game);                         // ���� ��׶���� ��ȯ�� �Լ�

void _LevelsEvent(void* userReference ,  LevelEventType eventType); // ���� �������� Ÿ��Ʋ �̺�Ʈ �Լ�
//void _StageEvent(void* userReference ,  GameStageType eventType);   // ���ӿ����� Ÿ��Ʋ �̺�Ʈ �Լ�
//void _TutorialEvent(void* userReference ,  GameStageType eventType);// Ʃ�丮�󿡼��� Ÿ��Ʋ �̺�Ʈ �Լ�
void _LoadingTweenStep(Tween* tween, void* userReference) ;         // �ε� Ʈ�� ����
void _LoadingTweenComplete(Tween* tween, void* userReference) ;     // �ε� Ʈ�� �Ϸ�


void  _newgameModelTouch(void *userReference, ModelEventTouchArgument argument);        // �÷��̹�ư ��ġ �̺�Ʈ
void  _leftbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);     // ���� ��ư ��ġ �̺�Ʈ
void  _rightbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);    // ������ ��ư ��ġ �̺�Ʈ

void  _gamecenterbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);   // ���Ӽ��� �������� ��ġ �̺�Ʈ
void  _AchievementbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);  //  ���Ӽ��� ��ġ���Ʈ ��ġ �̺�Ʈ

void  _facebookbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);     // ���̽��� �������� ��ġ �̺�Ʈ
void  _gameresetbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);    // ���� ���� ��ư ��ġ �̺�Ʈ
void  _gameinforbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);    // ũ���� ��ư ��ġ �̺�Ʈ
void  _gameCreditbackbuttonModelTouch(void *userReference, ModelEventTouchArgument argument);   //ũ���� ���ư ��ġ �̺�Ʈ
void  _gameCreditSwipebuttonModelTouch(void *userReference, ModelEventTouchArgument argument);  // ũ���� �������� ��ġ �̺�Ʈ

void  _gameResetPopup_ResetBtn_Touch(void *userReference, ModelEventTouchArgument argument);    // ���� ���� �˾� ���� ��ư ��ġ �̺�Ʈ
void  _gameResetPopup_CancelBtn_Touch(void *userReference, ModelEventTouchArgument argument);   // ���� ���� �˾� ��� ��ư ��ġ �̺�Ʈ


#endif
