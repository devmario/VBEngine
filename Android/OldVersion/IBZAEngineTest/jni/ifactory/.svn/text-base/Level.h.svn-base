#ifndef LEVEL_H
#define LEVEL_H
#include "Display/Object/Model.h"
#include "Display/Object/ObjFileForModel.h"
#include "Util/Array.h"

enum {
	LevelEventTypeNone				=	0x00,
	LevelEventTypeComplete			=	0x01,
	LevelEventTypeBack			=	0x02,
    LevelEventTypeSave          =   0x03,
    LevelEventTypeTutorial      =   0x04,
};
typedef unsigned char LevelEventType;

typedef struct LevelEvents LevelEvents;
struct LevelEvents {
	void* userReference;
	void (*event)(void* userReference, LevelEventType type);
};

enum {
	LevelSelectStateMain = 0x00,
	LevelSelectStateSelect = 0x01
};
typedef unsigned char LevelSelectState;

typedef struct LevelButton Levelbutton;
struct LevelButton {
	bool lock;
	bool clear;
	int starnum;
	Model* button;
	Model* star;
	Model* stageNum;
	Model* stage10Num;	
	Model* buttontouch;		
};
typedef struct Levels Levels;
struct Levels {
	char* resourcePath;
	
	Model* LWmodels;
	
	Model* testModel;
	ModelManager* manager;
	
	LevelEvents levelevent;
	
	ObjectFile* select_bg0_obj;
	ObjectFile* select_menu;
	ObjectFile* fonts;	
	ObjectFile* tutorial_obj;
	Model* bg_0;
	Model* backbutton;
	
	Model* levelbutton;
	Model* swichmodel;
   	Model* selectswichmodel;
	Array* levelarray;
	int leveltouchindex;
	
	bool selectonoff;
	
	TweenManager *tweenmanger;
	Tween *pageTween;
	float pagex;
	float pagegesturestartx;
	Vector2D* pagevec;
	Vector2D* gestureStart;
	Vector2D* gestureMove;
	Vector2D* gestureEnd;
	float	gestureLast;
	bool moveon;
	int page;
    int selectpage1;
    int selectpage2;
    int selectpage3;
	Model * IcepageModel;
    Model * InStagePageModel;

	Model * commingsoon;
    
    Array* stageinforarray;
    
    Model* pack0;
    Model* pack1;
    Model* pack2; 
    Model* pack3;
    Model* pack4;
    
    Model* pack1name;
    Model* pack2name;
    Model* pack3name;
    Model* pack4name;

    Model* pack1Mark;
    Model* pack2Mark;
    Model* pack3Mark;
    Model* pack4Mark;

    Model* pageTitleModel;
    LevelSelectState state;

    unsigned int pac1totalstar;
    unsigned int pac2totalstar;
    unsigned int pac3totalstar;

    Model* pac1starfont100;
    Model* pac1starfont10;
    Model* pac1starfont1;

    Model* pac2starfont100;
    Model* pac2starfont10;
    Model* pac2starfont1;

    Model* pac3starfont100;
    Model* pac3starfont10;
    Model* pac3starfont1;

//    Model* pac4starfont1;


    unsigned int pac1totalpoint;
    unsigned int pac2totalpoint;
    unsigned int pac3totalpoint;

    Model* pac1pointfont[6];
    Model* pac2pointfont[6];
    Model* pac3pointfont[6];
 //   Model* pac4pointfont;

};
LevelEvents LevelEventInit(void* userReference, void (*event)(void* userReference, LevelEventType type));
void  _Pack0Touch(void *userReference, ModelEventTouchArgument argument) ;
void  _Pack1Touch(void *userReference, ModelEventTouchArgument argument) ;
void  _Pack2Touch(void *userReference, ModelEventTouchArgument argument) ;
void  _Pack3Touch(void *userReference, ModelEventTouchArgument argument) ;


void  _LevelTestTouch(void *userReference, ModelEventTouchArgument argument) ;
void  _LevelBackTouch(void *userReference, ModelEventTouchArgument argument) ;
void  _LevelSwipeTouch(void *userReference, ModelEventTouchArgument argument) ;

void LevelPacClearAnimation(Levels *levels);
void _LevelTweenStep(Tween* tween, void* userReference) ;
void _LevelTweenComplete(Tween* tween, void* userReference) ;

void LevelPackSetVisible(Levels* levels , bool toggle);
void LevelInit(Levels *levels , const char* _resourcePath ,LevelEvents _levelevent, ModelManager * _modelmanagers ,TweenManager* _tweenmanager , int pages,
              int _selectpage1 ,int _selectpage2, int _selectpage3,  bool _inouts  , Array * _stageinfor);
void LevelFree(Levels *levels );
void LevelRender(Levels *levels );


#endif
