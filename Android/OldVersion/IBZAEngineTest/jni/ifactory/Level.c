/*
 *  Level.c
 *  iFactory
 *
 *  Created by JungJin Lee on 10. 12. 22..
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Level.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "PNGDecoder.h"
//#include "xmlFarSard.h"
#include "Sample.h"

void *leveltouchID = NULL;
void *Pack0TouchID = NULL;
void *Pack1TouchID = NULL;
void *Pack2TouchID = NULL;
void *Pack3TouchID = NULL;
void *levelSwipeID = NULL;

LevelEvents LevelEventInit(void* userReference, void (*event)(void* userReference, LevelEventType type)){
	LevelEvents mainEvent;
	mainEvent.userReference = userReference;
	mainEvent.event = event;
	return mainEvent;
}

void LevelInit(Levels *levels , const char* _resourcePath ,LevelEvents _levelevent, ModelManager * _modelmanagers ,TweenManager* _tweenmanager , int pages,
               int _selectpage1 ,int _selectpage2, int _selectpage3,  bool _inouts  , Array * _stageinfor)
{
	//levels->resourcePath = calloc(strlen(_resourcePath), sizeof(char));
	//sprintf(levels->resourcePath, "%s", _resourcePath);
	levels->levelevent = _levelevent;
	levels->manager = _modelmanagers;
	levels->stageinforarray = _stageinfor;

	levels->LWmodels = calloc(1, sizeof(Model));
	ModelInitDefault(levels->LWmodels);
	levels->swichmodel = calloc(1, sizeof(Model));
	ModelInitDefault(levels->swichmodel);

    levels->selectswichmodel = calloc(1, sizeof(Model));
	ModelInitDefault(levels->selectswichmodel);

	levels->select_bg0_obj = ObjectFileLoad("level_stage0" );

	levels->select_menu = ObjectFileLoad("level_menu" );
	levels->fonts = ObjectFileLoad("level_font");
	levels->tutorial_obj  = ObjectFileLoad("level_tutorial" );

 //   levelselectSoundInit();
	LOGV("Levelinit State");
    levels->bg_0 = ObjectFileMakeModelWithMovieClipName(levels->select_bg0_obj , "dy_menu_stage0_bg");
	ModelAdd(levels->LWmodels  ,levels->bg_0 );
	ModelSetPosition(levels->bg_0 , Vector3DInit(-240.0f , -160.0f , 1.0f ));

	levels->backbutton = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_btnBack");
	ModelAdd(levels->LWmodels  ,levels->backbutton);
	ModelSetPosition(levels->backbutton , Vector3DInit(-235.0f , 100.0f , 1.0f ));
	Model * backtouch = ModelGetChildWithInstanceName(levels->backbutton , levels->select_menu , "id_menu_btnBack_on");

	ModelAddEventTouch(backtouch, ModelEventTouchTinyInit(levels , _LevelBackTouch )
					   , 2, backtouch->vertex, true, true, true, true);
   	ModelAdd(levels->LWmodels , levels->selectswichmodel );
	ModelAdd(levels->LWmodels , levels->swichmodel );

	Model * swipetouch = ModelGetChildWithInstanceName(levels->bg_0 , levels->select_bg0_obj , "id_menu_stage0_bg");

	ModelAddEventTouch(swipetouch ,  ModelEventTouchTinyInit(levels , _LevelSwipeTouch )
					   , 2, swipetouch->vertex , true, true, true, true);
	levels->pagevec = calloc(1 , sizeof(Vector2D));
	levels->pagevec->x = 0.0f;		levels->pagevec->y = 0.0f;
	levels->pagex = 0.0f;
	levels->gestureStart = calloc(1 , sizeof(Vector2D));
	levels->gestureMove = calloc(1 , sizeof(Vector2D));
	levels->gestureEnd = calloc(1 , sizeof(Vector2D));
	levels->gestureLast = 0.0f;
	levels->tweenmanger = _tweenmanager;
	levels->pageTween = calloc(1, sizeof(Tween));

	TweenInit(levels->pageTween , 15, 1, TweenTrasitionTypeLinear, TweenEquationTypeEaseOut);

	TweenManagerAddTween(levels->tweenmanger , levels->pageTween);
	TweenAddEventStep(levels->pageTween, TweenEventStepInit(_LevelTweenStep, levels));
	TweenAddEventComplete(levels->pageTween , TweenEventCompleteInit(_LevelTweenComplete, levels));

	levels->IcepageModel = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_icecream");
	ModelAdd(levels->LWmodels , levels->IcepageModel );
	ModelSetPosition(levels->IcepageModel , Vector3DInit(-72.75f , 110.0f, 1.0f));

	levels->page = pages;
    levels->selectpage1 = _selectpage1;
    levels->selectpage2 = _selectpage2;
    levels->selectpage3 = _selectpage3;


    levels->InStagePageModel = ObjectFileMakeModelWithMovieClipName(levels->select_bg0_obj , "dy_menu_page");
	ModelAdd(levels->LWmodels , levels->InStagePageModel );
	ModelSetPosition(levels->InStagePageModel , Vector3DInit(0.0f , 135.0f, 1.0f));

    levels->pageTitleModel = ObjectFileMakeModelWithMovieClipName(levels->select_bg0_obj , "dy_menu_title");
	ModelAdd(levels->LWmodels , levels->pageTitleModel );
	ModelSetPosition(levels->pageTitleModel , Vector3DInit(-101.65f , 85.0f, 1.0f));


	levels->levelarray = ArrayInit();

	int stagenums = 0;
    levels->state = LevelSelectStateMain;
    levels->pack0 = ObjectFileMakeModelWithMovieClipName(levels->tutorial_obj , "dy_tutorial_popup");
    levels->pack1 = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_popupBig");
    levels->pack2 = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_popupBig");
    levels->pack3 = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_popupBig");
    levels->pack4 = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_popupBig");
    ModelAdd(levels->swichmodel  ,levels->pack0);
    ModelAdd(levels->pack0  ,levels->pack1);
    ModelAdd(levels->pack1  ,levels->pack2);
    ModelAdd(levels->pack2  ,levels->pack3);
    ModelAdd(levels->pack3  ,levels->pack4);
   	ModelSetPosition(levels->pack0 , Vector3DInit(-167.0f , -160.0f, 1.0f));
   	ModelSetPosition(levels->pack1 , Vector3DInit(340.0f , 0.0f, 1.0f));
    ModelSetPosition(levels->pack2 , Vector3DInit(340.0f , 0.0f, 1.0f));
    ModelSetPosition(levels->pack3 , Vector3DInit(340.0f , 0.0f, 1.0f));
    ModelSetPosition(levels->pack4 , Vector3DInit(340.0f , 0.0f, 1.0f));

    Model * _pack0 = ModelGetChildWithInstanceName(levels->pack0 , levels->tutorial_obj, "id_tutorial_popup");
    Model * _pack1 = ModelGetChildWithInstanceName(levels->pack1 , levels->select_menu, "id_menu_popupBig");
    Model * _pack2 = ModelGetChildWithInstanceName(levels->pack2 , levels->select_menu, "id_menu_popupBig");
    Model * _pack3 = ModelGetChildWithInstanceName(levels->pack3 , levels->select_menu, "id_menu_popupBig");
    ModelAddEventTouch(_pack0 , ModelEventTouchTinyInit(levels , _Pack0Touch ), 2, _pack0->vertex, true, true, true, true);
    ModelAddEventTouch(_pack1 , ModelEventTouchTinyInit(levels , _Pack1Touch ), 2, _pack1->vertex, true, true, true, true);
    ModelAddEventTouch(_pack2 , ModelEventTouchTinyInit(levels , _Pack2Touch ), 2, _pack2->vertex, true, true, true, true);
    ModelAddEventTouch(_pack3 , ModelEventTouchTinyInit(levels , _Pack3Touch ), 2, _pack3->vertex, true, true, true, true);

    levels->pack1name =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_popupTitle");
    levels->pack2name =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_popupTitle");
    levels->pack3name =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_popupTitle");
    levels->pack4name =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_popupTitle");
    levels->pack1Mark =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_factory");
    levels->pack2Mark =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_factory");
    levels->pack3Mark =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_factory");
    levels->pack4Mark =  ObjectFileMakeModelWithMovieClipName(levels->select_menu ,"dy_menu_factory");

    ModelAdd(levels->pack1 , levels->pack1name);
    ModelAdd(levels->pack2 , levels->pack2name);
    ModelAdd(levels->pack3 , levels->pack3name);
    ModelAdd(levels->pack4 , levels->pack4name);

    ModelAdd(levels->pack1 , levels->pack1Mark);
    ModelAdd(levels->pack2 , levels->pack2Mark);
    ModelAdd(levels->pack3 , levels->pack3Mark);
    ModelAdd(levels->pack4 , levels->pack4Mark);

    ModelGoToAndStop(levels->pack1name , 0);
    ModelGoToAndStop(levels->pack2name , 1);
    ModelGoToAndStop(levels->pack3name , 2);
    ModelGoToAndStop(levels->pack4name , 3);

    ModelGoToAndStop(levels->pack1Mark , 0);
    ModelGoToAndStop(levels->pack2Mark , 1);
    ModelGoToAndStop(levels->pack3Mark , 2);
    ModelGoToAndStop(levels->pack4Mark , 2);

    ModelSetPosition(levels->pack1name, Vector3DInit( 56.0f , 47.0f , 1.0f));
    ModelSetPosition(levels->pack1Mark, Vector3DInit( 112.0f , 100.0f , 1.0f));
    ModelSetPosition(levels->pack2name, Vector3DInit( 66.0f , 47.0f , 1.0f));
    ModelSetPosition(levels->pack2Mark, Vector3DInit( 112.0f , 100.0f , 1.0f));
    ModelSetPosition(levels->pack3name, Vector3DInit( 62.0f , 47.0f , 1.0f));
    ModelSetPosition(levels->pack3Mark, Vector3DInit( 112.0f , 100.0f , 1.0f));
    ModelSetPosition(levels->pack4name, Vector3DInit( 48.0f , 47.0f , 1.0f));
    ModelSetPosition(levels->pack4Mark, Vector3DInit( 112.0f , 100.0f , 1.0f));
    int j , i = 0 ;
    for(  j = 0 ; j < 2;j++)
	{
        for (  i = 0  ; i < 18; i++) {
            stagenums++;
            Levelbutton * levelsbtn  = calloc(1 , sizeof(Levelbutton));
            levelsbtn->button = ObjectFileMakeModelWithMovieClipName(levels->select_bg0_obj , "dy_menu_stage0_stage");
            levelsbtn->star = ObjectFileMakeModelWithMovieClipName(levels->select_bg0_obj , "dy_menu_stage0_star");
            ModelAdd(levelsbtn->button , levelsbtn->star);
            ModelAdd(levels->selectswichmodel  ,levelsbtn->button);
            ModelGoToAndStop(levelsbtn->star , 2);
            ModelSetPosition(levelsbtn->star, Vector3DInit(35.0f, 51.0f, 1.0f));
            float posx =0.0f;
            float posy = 0.0f;
            if( i < 6)
            {
                posx = -212.0f + (j * 480.0f)+ (i * 71);
                posy = -122.0f;
            }
            else if( i < 12)
            {
                posx = -212.0f+ (j * 480.0f)+(( i -  6) * 71);
                posy = -52.0f;
            }
            else {
                posx = -212.0f + (j * 480.0f)+ (( i -  12) * 71);
                posy =  18.0f;
            }
            ModelSetPosition(levelsbtn->button , Vector3DInit( posx, posy , 1.0f ));

            int num10 = (int)((stagenums) / 10);

            if( num10 <= 0 )
            {
                levelsbtn->stageNum = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_stageOne");
                ModelAdd(levelsbtn->button  ,levelsbtn->stageNum);
                ModelSetPosition(levelsbtn->stageNum , Vector3DInit( 6.0f , 12.0f , 1.0f ));
            }
            else
            {
                levelsbtn->stageNum = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_stageTen");
                ModelAdd(levelsbtn->button  ,levelsbtn->stageNum);
                ModelSetPosition(levelsbtn->stageNum , Vector3DInit( 6.0f , 12.0f , 1.0f ));

            }
            levelsbtn->stage10Num = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_stageTen");
            ModelAdd(levelsbtn->stageNum  ,levelsbtn->stage10Num);
            ModelSetPosition(levelsbtn->stage10Num , Vector3DInit( 12.0f , 0.0f , 1.0f ));
            ModelSetIsVisible(levelsbtn->star , false);
            ModelSetIsVisible(levelsbtn->stageNum , false);
            ModelSetIsVisible(levelsbtn->stage10Num , false);


            levelsbtn->lock = true;

            ModelSetIsVisible(levelsbtn->button , false);


            levelsbtn->buttontouch = ModelGetChildWithInstanceName( levelsbtn->button , levels->select_bg0_obj, "id_touch");

            ModelAddEventTouch(levelsbtn->buttontouch , ModelEventTouchTinyInit(levels , _LevelTestTouch )
                               , 2, levelsbtn->buttontouch->vertex, true, true, true, true);
            ArrayPushObject(levels->levelarray  , levelsbtn );
            levels->selectonoff = false;
        }

    }

    if( levels->page == 1)
    {
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( (-levels->selectpage1 * 480.0f) ,0.0f  ,1.0f));
         ModelGoToAndStop(levels->InStagePageModel,  levels->selectpage1 );
        ModelGoToAndStop(levels->pageTitleModel,  0 );
    }
    else if( levels->page == 2)
    {
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( (-levels->selectpage2 * 480.0f) ,0.0f  ,1.0f));
        ModelGoToAndStop(levels->pageTitleModel,  1 );
         ModelGoToAndStop(levels->InStagePageModel,  levels->selectpage2 + 2 );
    }
    else if(levels->page == 3)
    {
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( (-levels->selectpage3 * 480.0f) ,0.0f  ,1.0f));
        ModelGoToAndStop(levels->pageTitleModel,  2 );
          ModelGoToAndStop(levels->InStagePageModel,  levels->selectpage3 + 4 );
    }

	ModelSetPosition(levels->swichmodel , Vector3DInit( (-levels->page * 340.0f) ,0.0f  ,1.0f));
	ModelGoToAndStop(levels->IcepageModel , levels->page);

	levels->commingsoon = ObjectFileMakeModelWithMovieClipName(levels->select_menu , "dy_menu_buynow");
	ModelAdd(levels->pack4 , levels->commingsoon );
	//ModelSetPosition(levels->commingsoon , Vector3DInit( -75.0f   , 0.0f, 1.0f));
    //ModelSetIsVisible(levels->commingsoon, false);

    LevelPackSetVisible(levels , _inouts);
    levels->pac1totalstar = 0;
    levels->pac2totalstar = 0;
    levels->pac3totalstar = 0;

    for( j = 0 ; j < 3 ; j++)
    {
        for( i =  0 ; i <  36  ; i++ )
        {
         //   StageInfo * info = ArrayObjectAtIndex(levels->stageinforarray , (j * 36)+i);
            if( ((j * 36)+i) < levels->stageinforarray->length)
            {
                if( j == 0)
                {
                    levels->pac1totalstar += 0;
                    levels->pac1totalpoint += 100;
                }
                else if(j == 1)
                {
                    levels->pac2totalstar +=2;
                    levels->pac2totalpoint += 0;
                }
                else if(j == 2)
                {
                    levels->pac3totalstar += 2;
                    levels->pac3totalpoint += 0;
                }
            }
        }
    }
    printf("level star %i %i %i \n" , levels->pac1totalstar , levels->pac2totalstar ,levels->pac3totalstar );

    levels->pac1starfont100 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
    levels->pac1starfont10 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
    levels->pac1starfont1 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");

    levels->pac2starfont100 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
    levels->pac2starfont10 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
    levels->pac2starfont1 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");

    levels->pac3starfont100 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
    levels->pac3starfont10 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
    levels->pac3starfont1 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");

//    levels->pac4starfont1 = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");

    ModelAdd(levels->pack1 , levels->pac1starfont100);
    ModelAdd(levels->pack1 , levels->pac1starfont10);
    ModelAdd(levels->pack1 , levels->pac1starfont1);

    ModelAdd(levels->pack2 , levels->pac2starfont100);
    ModelAdd(levels->pack2 , levels->pac2starfont10);
    ModelAdd(levels->pack2 , levels->pac2starfont1);

    ModelAdd(levels->pack3 , levels->pac3starfont100);
    ModelAdd(levels->pack3 , levels->pac3starfont10);
    ModelAdd(levels->pack3 , levels->pac3starfont1);

//    ModelAdd(levels->pack4 , levels->pac4starfont1);

    ModelSetPosition(levels->pac1starfont100,  Vector3DInit(207.0f , 223.0f , 1.0f));
    ModelSetPosition(levels->pac1starfont10,  Vector3DInit(220.0f , 223.0f , 1.0f));
    ModelSetPosition(levels->pac1starfont1,  Vector3DInit(233.0f , 223.0f , 1.0f));

    ModelSetPosition(levels->pac2starfont100,  Vector3DInit(207.0f , 223.0f , 1.0f));
    ModelSetPosition(levels->pac2starfont10,  Vector3DInit(220.0f , 223.0f , 1.0f));
    ModelSetPosition(levels->pac2starfont1,  Vector3DInit(233.0f , 223.0f , 1.0f));

    ModelSetPosition(levels->pac3starfont100,  Vector3DInit(207.0f , 223.0f , 1.0f));
    ModelSetPosition(levels->pac3starfont10,  Vector3DInit(220.0f , 223.0f , 1.0f));
    ModelSetPosition(levels->pac3starfont1,  Vector3DInit(233.0f , 223.0f , 1.0f));

 //   ModelSetPosition(levels->pac4starfont1,  Vector3DInit(233.0f , 223.0f , 1.0f));

    int pac1starfonts100 = levels->pac1totalstar / 100;
    int pac1starfonts10  = (levels->pac1totalstar % 100) / 10;
    int pac1starfonts1   = (levels->pac1totalstar % 100) % 10;

    ModelGoToAndStop(levels->pac1starfont100 , pac1starfonts100);
    ModelGoToAndStop(levels->pac1starfont10 , pac1starfonts10);
    ModelGoToAndStop(levels->pac1starfont1 , pac1starfonts1);

    if( pac1starfonts100 == 0 )
        ModelSetIsVisible(levels->pac1starfont100 ,  false);
    if( pac1starfonts10 == 0 && pac1starfonts100 == 0 )
        ModelSetIsVisible(levels->pac1starfont10 ,  false);

    int pac2starfonts100 = levels->pac2totalstar / 100;
    int pac2starfonts10  = (levels->pac2totalstar % 100) / 10;
    int pac2starfonts1   = (levels->pac2totalstar % 100) % 10;

    ModelGoToAndStop(levels->pac2starfont100 , pac2starfonts100);
    ModelGoToAndStop(levels->pac2starfont10 , pac2starfonts10);
    ModelGoToAndStop(levels->pac2starfont1 , pac2starfonts1);

    if( pac2starfonts100 == 0 )
        ModelSetIsVisible(levels->pac2starfont100 ,  false);
    if( pac2starfonts10 == 0 && pac2starfonts100 == 0 )
        ModelSetIsVisible(levels->pac2starfont10 ,  false);

    int pac3starfonts100 = levels->pac3totalstar / 100;
    int pac3starfonts10  = (levels->pac3totalstar % 100) / 10;
    int pac3starfonts1   = (levels->pac3totalstar % 100) % 10;

    ModelGoToAndStop(levels->pac3starfont100 , pac3starfonts100);
    ModelGoToAndStop(levels->pac3starfont10 , pac3starfonts10);
    ModelGoToAndStop(levels->pac3starfont1 , pac3starfonts1);

    if( pac3starfonts100 == 0 )
        ModelSetIsVisible(levels->pac3starfont100 ,  false);
    if( pac3starfonts10 == 0 && pac3starfonts100 == 0 )
        ModelSetIsVisible(levels->pac3starfont10 ,  false);

    for(  i = 0 ; i < 6 ; i++)
    {
        levels->pac1pointfont[i] = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
        levels->pac2pointfont[i] = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
        levels->pac3pointfont[i] = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");

         ModelAdd(levels->pack1 , levels->pac1pointfont[i]);
         ModelAdd(levels->pack2 , levels->pac2pointfont[i]);
         ModelAdd(levels->pack3 , levels->pac3pointfont[i]);

        ModelSetPosition(levels->pac1pointfont[i],  Vector3DInit((13.0f * i)+23.0f, 223.0f , 1.0f));
        ModelSetPosition(levels->pac2pointfont[i],  Vector3DInit((13.0f * i)+23.0f , 223.0f , 1.0f));
        ModelSetPosition(levels->pac3pointfont[i],  Vector3DInit((13.0f * i)+23.0f , 223.0f , 1.0f));
    }
 //   levels->pac4pointfont = ObjectFileMakeModelWithMovieClipName(levels->fonts , "dy_font_score");
  //  ModelAdd(levels->pack4 , levels->pac4pointfont);

    int number = levels->pac1totalpoint;
   	int oneNumber;
	 i = 0;
    int pac1points[6];
	while (number != 0) {
		oneNumber = number % 10;
		pac1points[i] = oneNumber;
		number /= 10;
		i++;
	}

    if( i == 0 )
    {
        ModelSetPosition( levels->pac1pointfont[0] ,  Vector3DInit( 65.0f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac1pointfont[0], 0);
        for( j = 1 ; j < 6 ; j++)
            ModelSetIsVisible(levels->pac1pointfont[j], false);
    }
    else if( i == 4)
    {
        ModelSetPosition( levels->pac1pointfont[0] ,  Vector3DInit( 86.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[1] ,  Vector3DInit( 72.75f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[2] ,  Vector3DInit( 58.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[3] ,  Vector3DInit( 44.60f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac1pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac1pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac1pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac1pointfont[3], pac1points[3]);
        for( j = 4 ; j < 6 ; j++)
            ModelSetIsVisible(levels->pac1pointfont[j], false);
    }
    else if( i == 5)
    {
        ModelSetPosition( levels->pac1pointfont[0] ,  Vector3DInit( 92.85f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[1] ,  Vector3DInit( 79.1f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[2] ,  Vector3DInit( 65.5f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[3] ,  Vector3DInit( 51.1f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[4] ,  Vector3DInit( 37.35f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac1pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac1pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac1pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac1pointfont[3], pac1points[3]);
        ModelGoToAndStop(levels->pac1pointfont[4], pac1points[4]);
        ModelSetIsVisible(levels->pac1pointfont[5], false);
    }
    else if( i == 6)
    {
        ModelSetPosition( levels->pac1pointfont[0] ,  Vector3DInit( 99.85f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[1] ,  Vector3DInit( 86.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[2] ,  Vector3DInit( 72.6f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[3] ,  Vector3DInit( 59.00f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[4] ,  Vector3DInit( 44.6f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac1pointfont[5] ,  Vector3DInit( 30.85f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac1pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac1pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac1pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac1pointfont[3], pac1points[3]);
        ModelGoToAndStop(levels->pac1pointfont[4], pac1points[4]);
        ModelGoToAndStop(levels->pac1pointfont[5], pac1points[5]);
    }



    number = levels->pac2totalpoint;
	i = 0;
	while (number != 0) {
		oneNumber = number % 10;
		pac1points[i] = oneNumber;
		number /= 10;
		i++;
	}
    if( i == 0 )
    {
        ModelSetPosition( levels->pac2pointfont[0] ,  Vector3DInit( 65.0f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac2pointfont[0], 0);
        for( j = 1 ; j < 6 ; j++)
            ModelSetIsVisible(levels->pac2pointfont[j], false);
    }
    else if( i == 4)
    {
        ModelSetPosition( levels->pac2pointfont[0] ,  Vector3DInit( 86.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[1] ,  Vector3DInit( 72.75f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[2] ,  Vector3DInit( 58.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[3] ,  Vector3DInit( 44.60f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac2pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac2pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac2pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac2pointfont[3], pac1points[3]);
        for( j = 4 ; j < 6 ; j++)
            ModelSetIsVisible(levels->pac2pointfont[j], false);
    }
    else if( i == 5)
    {
        ModelSetPosition( levels->pac2pointfont[0] ,  Vector3DInit( 92.85f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[1] ,  Vector3DInit( 79.1f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[2] ,  Vector3DInit( 65.5f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[3] ,  Vector3DInit( 51.1f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[4] ,  Vector3DInit( 37.35f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac2pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac2pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac2pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac2pointfont[3], pac1points[3]);
        ModelGoToAndStop(levels->pac2pointfont[4], pac1points[4]);
        ModelSetIsVisible(levels->pac2pointfont[5], false);
    }
    else if( i == 6)
    {
        ModelSetPosition( levels->pac2pointfont[0] ,  Vector3DInit( 99.85f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[1] ,  Vector3DInit( 86.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[2] ,  Vector3DInit( 72.6f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[3] ,  Vector3DInit( 59.00f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[4] ,  Vector3DInit( 44.6f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac2pointfont[5] ,  Vector3DInit( 30.85f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac2pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac2pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac2pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac2pointfont[3], pac1points[3]);
        ModelGoToAndStop(levels->pac2pointfont[4], pac1points[4]);
        ModelGoToAndStop(levels->pac2pointfont[5], pac1points[5]);
    }

    number = levels->pac3totalpoint;
	i = 0;
	while (number != 0) {
		oneNumber = number % 10;
		pac1points[i] = oneNumber;
		number /= 10;
		i++;
	}
    if( i == 0 )
    {
        ModelSetPosition( levels->pac3pointfont[0] ,  Vector3DInit( 65.0f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac3pointfont[0], 0);
        for( j = 1 ; j < 6 ; j++)
            ModelSetIsVisible(levels->pac3pointfont[j], false);
    }
    else if( i == 4)
    {
        ModelSetPosition( levels->pac3pointfont[0] ,  Vector3DInit( 86.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[1] ,  Vector3DInit( 72.75f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[2] ,  Vector3DInit( 58.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[3] ,  Vector3DInit( 44.60f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac3pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac3pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac3pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac3pointfont[3], pac1points[3]);
        for( j = 4 ; j < 6 ; j++)
            ModelSetIsVisible(levels->pac3pointfont[j], false);
    }
    else if( i == 5)
    {
        ModelSetPosition( levels->pac3pointfont[0] ,  Vector3DInit( 92.85f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[1] ,  Vector3DInit( 79.1f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[2] ,  Vector3DInit( 65.5f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[3] ,  Vector3DInit( 51.1f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[4] ,  Vector3DInit( 37.35f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac3pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac3pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac3pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac3pointfont[3], pac1points[3]);
        ModelGoToAndStop(levels->pac3pointfont[4], pac1points[4]);
        ModelSetIsVisible(levels->pac3pointfont[5], false);
    }
    else if( i == 6)
    {
        ModelSetPosition( levels->pac3pointfont[0] ,  Vector3DInit( 99.85f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[1] ,  Vector3DInit( 86.35f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[2] ,  Vector3DInit( 72.6f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[3] ,  Vector3DInit( 59.00f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[4] ,  Vector3DInit( 44.6f , 223.0f , 1.0f));
        ModelSetPosition( levels->pac3pointfont[5] ,  Vector3DInit( 30.85f , 223.0f , 1.0f));
        ModelGoToAndStop(levels->pac3pointfont[0], pac1points[0]);
        ModelGoToAndStop(levels->pac3pointfont[1], pac1points[1]);
        ModelGoToAndStop(levels->pac3pointfont[2], pac1points[2]);
        ModelGoToAndStop(levels->pac3pointfont[3], pac1points[3]);
        ModelGoToAndStop(levels->pac3pointfont[4], pac1points[4]);
        ModelGoToAndStop(levels->pac3pointfont[5], pac1points[5]);
    }

//    ModelSetPosition( levels->pac4pointfont,  Vector3DInit( 65.0f , 223.0f , 1.0f));

}
void LevelPackSetVisible(Levels* levels , bool toggle)
{
    if( toggle)
    {
        ModelSetIsVisible(levels->pack0 , false);
        ModelSetIsVisible(levels->pack1 , false);
        ModelSetIsVisible(levels->pack2 , false);
        ModelSetIsVisible(levels->pack3 , false);
        ModelSetIsVisible(levels->pack4 , false);
//        ModelSetIsVisible(levels->commingsoon, false);
        levels->state = LevelSelectStateSelect;
        ModelSetIsVisible(levels->IcepageModel , false);
        ModelSetIsVisible(levels->InStagePageModel , true);

        ModelSetIsVisible(levels->pageTitleModel , true);
        if( levels->page == 1)
            ModelGoToAndStop(levels->pageTitleModel,  0 );
        else if(levels->page == 2)
            ModelGoToAndStop(levels->pageTitleModel,  1 );
        else if(levels->page == 3)
        {
            ModelGoToAndStop(levels->pageTitleModel,  2 );
   //         ModelSetIsVisible(levels->commingsoon, true);
        }


        int i = 0 ;
        for( i =  0 ; i <  36  ; i++ )
        {

        //    StageInfo * info = ArrayObjectAtIndex(levels->stageinforarray , ((levels->page-1) * 36)+i);
            Levelbutton* levelsbtn = ArrayObjectAtIndex( levels->levelarray , i);
            ModelSetIsVisible(levelsbtn->button , true);
            if( (((levels->page-1) * 36)+i) < levels->stageinforarray->length)
            {
                if( false )
                {
                    if( i < 9 )
                    {
                        ModelSetPosition(levelsbtn->stageNum , Vector3DInit( 22.0f , 14.0f , 1.0f ));
                        ModelGoToAndStop(levelsbtn->stageNum,  i+1 );
                        ModelSetIsVisible(levelsbtn->stageNum , true);
                    }
                    else
                    {
                        ModelSetPosition(levelsbtn->stageNum , Vector3DInit( 17.5f , 14.0f , 1.0f ));
                        ModelSetPosition(levelsbtn->stage10Num , Vector3DInit( 18.5f , 0.0f , 1.0f ));
                        int num10 = (int)((i+1) / 10);
                        int num1 = (int)(i+1) - (num10 *  10);
                        ModelGoToAndStop(levelsbtn->stageNum, num10 );
                        ModelGoToAndStop(levelsbtn->stage10Num,  num1);

                        ModelSetIsVisible(levelsbtn->stageNum , true);
                        if( levelsbtn->stage10Num != NULL)
                            ModelSetIsVisible(levelsbtn->stage10Num , true);
                    }

                    if( levels->page == 1)
                        ModelGoToAndStop(levelsbtn->button,  1 );
                    else if(levels->page == 2)
                        ModelGoToAndStop(levelsbtn->button,  3 );
                    else if(levels->page == 3)
                        ModelGoToAndStop(levelsbtn->button,  5 );

                    levelsbtn->lock = false;
                }
                else
                {
                    if( levels->page == 1)
                        ModelGoToAndStop(levelsbtn->button,  0 );
                    else if(levels->page == 2)
                        ModelGoToAndStop(levelsbtn->button,  2 );
                    else if(levels->page == 3)
                        ModelGoToAndStop(levelsbtn->button,  4 );
                }


                    ModelSetIsVisible(levelsbtn->star , false);

            }
            else
            {
                if( levels->page == 1)
                    ModelGoToAndStop(levelsbtn->button,  0 );
                else if(levels->page == 2)
                    ModelGoToAndStop(levelsbtn->button,  2 );
                else if(levels->page == 3)
                    ModelGoToAndStop(levelsbtn->button,  4 );
            }
        }
    }
    else
    {
    //    ModelSetIsVisible(levels->commingsoon, false);
        ModelSetIsVisible(levels->pack0 , true);
        ModelSetIsVisible(levels->pack1 , true);
        ModelSetIsVisible(levels->pack2 , true);
        ModelSetIsVisible(levels->pack3 , true);
        ModelSetIsVisible(levels->pack4 , true);
        levels->state = LevelSelectStateMain;
        ModelSetIsVisible(levels->IcepageModel , true);
        ModelSetIsVisible(levels->InStagePageModel , false);
        ModelSetIsVisible(levels->pageTitleModel , false);
        int i = 0;
        for( i =  0 ; i <  36  ; i++ )
        {
            Levelbutton* levelsbtn = ArrayObjectAtIndex( levels->levelarray , i);
            if( levels->page == 1)
                ModelGoToAndStop(levelsbtn->button,  0 );
            else if(levels->page == 2)
                ModelGoToAndStop(levelsbtn->button,  2 );
            else if(levels->page == 3)
                ModelGoToAndStop(levelsbtn->button,  4 );

            levelsbtn->lock = true;
            ModelSetIsVisible(levelsbtn->button , false);
            ModelSetIsVisible(levelsbtn->stageNum , false);
            ModelSetIsVisible(levelsbtn->stage10Num , false);
            ModelSetIsVisible(levelsbtn->star , false);

        }
    }
}

void  _Pack0Touch(void *userReference, ModelEventTouchArgument argument)
{
    Levels* levels = (Levels*)userReference;
    if (argument.isHit) {

		if( argument.touchType == TouchTypeBegan && Pack1TouchID == NULL && !levels->moveon)
		{
			Pack0TouchID = argument.touchID;
		}
        else if( argument.touchType == TouchTypeMove && Pack0TouchID != NULL)
		{
            Pack0TouchID = NULL;
		}
		else if( argument.touchType == TouchTypeEnd && Pack0TouchID != NULL && !levels->moveon )
		{
            Pack0TouchID = NULL;
            if( levels->page == 0)
            {
           //     levelselectSoundPlay(0);
                levels->levelevent.event(levels->levelevent.userReference, LevelEventTypeTutorial);
            }
		}
	}
	else {
		if( argument.touchType == TouchTypeEnd  )
		{
			Pack0TouchID = NULL;
		}
	}
}

void  _Pack1Touch(void *userReference, ModelEventTouchArgument argument)
{
    Levels* levels = (Levels*)userReference;
    if (argument.isHit) {

		if( argument.touchType == TouchTypeBegan && Pack1TouchID == NULL && !levels->moveon)
		{
			Pack1TouchID = argument.touchID;
		}
        else if( argument.touchType == TouchTypeMove && Pack1TouchID != NULL)
		{
            Pack1TouchID = NULL;
		}
		else if( argument.touchType == TouchTypeEnd && Pack1TouchID != NULL && !levels->moveon )
		{
            Pack1TouchID = NULL;
            if( levels->page == 1)
            {
        //        levelselectSoundPlay(0);
                LevelPackSetVisible(levels , true);
            }
		}
	}
	else {
		if( argument.touchType == TouchTypeEnd  )
		{
			Pack1TouchID = NULL;
		}
	}
}
void  _Pack2Touch(void *userReference, ModelEventTouchArgument argument)
{
    Levels* levels = (Levels*)userReference;
    if (argument.isHit) {

		if( argument.touchType == TouchTypeBegan && Pack2TouchID == NULL && !levels->moveon)
		{
			Pack2TouchID = argument.touchID;
		}
        else if( argument.touchType == TouchTypeMove && Pack2TouchID != NULL)
		{
            Pack2TouchID = NULL;
		}
		else if( argument.touchType == TouchTypeEnd && Pack2TouchID != NULL && !levels->moveon )
		{
            Pack2TouchID = NULL;
            if( levels->page == 2)
            {
         //       levelselectSoundPlay(0);
                LevelPackSetVisible(levels , true);
            }
		}
	}
	else {
		if( argument.touchType == TouchTypeEnd  )
		{
			Pack2TouchID = NULL;
		}
	}
}
void  _Pack3Touch(void *userReference, ModelEventTouchArgument argument)
{
    Levels* levels = (Levels*)userReference;
    if (argument.isHit) {

		if( argument.touchType == TouchTypeBegan && Pack3TouchID == NULL && !levels->moveon)
		{
			Pack3TouchID = argument.touchID;
		}
        else if( argument.touchType == TouchTypeMove && Pack3TouchID != NULL)
		{
            Pack3TouchID = NULL;
		}
		else if( argument.touchType == TouchTypeEnd && Pack3TouchID != NULL && !levels->moveon )
		{
            Pack3TouchID = NULL;
            if( levels->page == 3)
            {
          //      levelselectSoundPlay(0);
                LevelPackSetVisible(levels , true);
            }
		}
	}
	else {
		if( argument.touchType == TouchTypeEnd  )
		{
			Pack3TouchID = NULL;
		}
	}
}
void _LevelTweenStep(Tween* tween, void* userReference)
{
	Levels* levels = (Levels*)userReference;
    if( levels->state == LevelSelectStateMain)
        ModelSetPosition(levels->swichmodel , Vector3DInit( levels->gestureLast ,0.0f  ,1.0f));
    else if( levels->state == LevelSelectStateSelect)
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( levels->gestureLast ,0.0f  ,1.0f));
}
void _LevelTweenComplete(Tween* tween, void* userReference)
{
	Levels* levels = (Levels*)userReference;

    levels->levelevent.event(levels->levelevent.userReference, LevelEventTypeSave);
    leveltouchID = NULL;

    while(levels->pageTween->property->length) {
        TweenProperty* prop = ArrayObjectAtIndex(levels->pageTween->property, 0);
        TweenRemoveProperty(levels->pageTween, prop);
    }
	ModelGoToAndStop(levels->IcepageModel , levels->page);

    if( levels->page == 1)
        ModelGoToAndStop(levels->InStagePageModel,  levels->selectpage1 );
    else if(levels->page == 2)
        ModelGoToAndStop(levels->InStagePageModel,  levels->selectpage2 + 2 );
    else if(levels->page == 3)
        ModelGoToAndStop(levels->InStagePageModel,  levels->selectpage3 + 4 );

	levels->moveon = false;
    if( levels->page == 1)
    {
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( (-levels->selectpage1 * 480.0f) ,0.0f  ,1.0f));
    }
    else if( levels->page == 2)
    {
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( (-levels->selectpage2 * 480.0f) ,0.0f  ,1.0f));
    }
    else if(levels->page == 3)
    {
        ModelSetPosition(levels->selectswichmodel , Vector3DInit( (-levels->selectpage3 * 480.0f) ,0.0f  ,1.0f));
    }
}


void  _LevelSwipeTouch(void *userReference, ModelEventTouchArgument eventType)
{
	Levels* levels = (Levels*)userReference;

    if( eventType.touchType == TouchTypeBegan)
    {
        if( levelSwipeID == NULL)
        {
            levelSwipeID = eventType.touchID;
        }
    }

    if( levelSwipeID == eventType.touchID)
    {

        printf("Begin %f %f\n", 160.0f + eventType.hitVectorGlobal->x ,eventType.hitVectorGlobal->y - 240.0f );
        eventType.touchVector = Vector2DInit( 160.0f + eventType.hitVectorGlobal->x ,eventType.hitVectorGlobal->y - 240.0f ) ;

        if (eventType.touchType == TouchTypeBegan && eventType.isHit ) {
            if( levels->state == LevelSelectStateMain)
                levels->pagegesturestartx = levels->swichmodel->position.x;
            else
                levels->pagegesturestartx = levels->selectswichmodel->position.x;
            levels->moveon = false;
            levels->gestureStart->x = eventType.touchVector.x;
            levels->gestureStart->y = eventType.touchVector.y;
        }
        else if (eventType.touchType == TouchTypeMove) {
            //	printf("Move %f %f\n", eventType.touchVector.x,eventType.touchVector.y);

            float deltay = fabsf(levels->gestureStart->y - eventType.touchVector.y);
            if( levels->state == LevelSelectStateMain)
            {
                if((levels->gestureStart->y - eventType.touchVector.y) > 0.0f)
                {
                    ModelSetPosition(levels->swichmodel , Vector3DInit( (levels->pagegesturestartx + deltay) , levels->swichmodel->position.y
                                                                       ,levels->swichmodel->position.z));


                }
                else if((levels->gestureStart->y - eventType.touchVector.y) < 0.0f)
                {

                    ModelSetPosition(levels->swichmodel , Vector3DInit( (levels->pagegesturestartx - deltay) , levels->swichmodel->position.y
                                                                       ,levels->swichmodel->position.z));
                }
            }
            else
            {
                if((levels->gestureStart->y - eventType.touchVector.y) > 0.0f)
                {
                    ModelSetPosition(levels->selectswichmodel , Vector3DInit( (levels->pagegesturestartx + deltay) , levels->selectswichmodel->position.y
                                                                             ,levels->selectswichmodel->position.z));


                }
                else if((levels->gestureStart->y - eventType.touchVector.y) < 0.0f)
                {

                    ModelSetPosition(levels->selectswichmodel , Vector3DInit( (levels->pagegesturestartx - deltay) , levels->selectswichmodel->position.y
                                                                             ,levels->selectswichmodel->position.z));
                }
            }
            levels->gestureMove->x = eventType.touchVector.x;
            levels->gestureMove->y = eventType.touchVector.y;
            levels->moveon = true;

        }
        else if (eventType.touchType == TouchTypeEnd) {

            if( levels->moveon )
            {
              //  levelselectSoundPlay(1);
                levels->gestureEnd->x = eventType.touchVector.x;
                levels->gestureEnd->y = eventType.touchVector.y;
                if( levels->state == LevelSelectStateMain)
                {
                    if((levels->gestureMove->y - eventType.touchVector.y )  < -2.0f)
                    {
                        if (levels->page < 4 ) {
                            levels->page++;
                        }
                    }
                    else if ((levels->gestureMove->y - eventType.touchVector.y )  > 2.0f)
                    {
                        if (levels->page > 0 ) {
                            levels->page--;
                        }
                    }

                    levels->gestureLast = levels->swichmodel->position.x;

                    TweenStop(levels->pageTween);
                    while(levels->pageTween->property->length) {
                        TweenProperty* prop = ArrayObjectAtIndex(levels->pageTween->property, 0);
                        TweenRemoveProperty(levels->pageTween, prop);
                    }

                    TweenAddProperty(levels->pageTween, TweenPropertyInit(&levels->gestureLast, levels->gestureLast, (-levels->page * 340.0f ) ));
                    TweenGoToAndPlay(levels->pageTween, 0);
                }
                else
                {
                    int selectpage = 0 ;
                    if( levels->page == 1)
                    {
                        selectpage = levels->selectpage1;
                    }
                    else if( levels->page == 2)
                    {
                        selectpage = levels->selectpage2;
                    }
                    else if(levels->page == 3)
                    {
                        selectpage = levels->selectpage3;
                    }
                    if((levels->gestureMove->y - eventType.touchVector.y )  < -2.0f)
                    {
                        if (selectpage < 1 ) {
                            selectpage++;
                        }
                    }
                    else if ((levels->gestureMove->y - eventType.touchVector.y )  > 2.0f)
                    {
                        if (selectpage > 0 ) {
                            selectpage--;
                        }
                    }

                    levels->gestureLast = levels->selectswichmodel->position.x;

                    TweenStop(levels->pageTween);
                    while(levels->pageTween->property->length) {
                        TweenProperty* prop = ArrayObjectAtIndex(levels->pageTween->property, 0);
                        TweenRemoveProperty(levels->pageTween, prop);
                    }

                    TweenAddProperty(levels->pageTween, TweenPropertyInit(&levels->gestureLast, levels->gestureLast, (-selectpage * 480.0f ) ));
                    TweenGoToAndPlay(levels->pageTween, 0);

                    if( levels->page == 1)
                    {
                        levels->selectpage1 = selectpage ;

                    }
                    else if( levels->page == 2)
                    {
                        levels->selectpage2 = selectpage ;
                    }
                    else if(levels->page == 3)
                    {
                        levels->selectpage3 = selectpage ;
                    }

                }

            }
            levelSwipeID = NULL;
        }
    }
}


void  _LevelTestTouch(void *userReference, ModelEventTouchArgument argument)
{
	Levels* levels = (Levels*)userReference;
	int i = 0;
	for ( i = 0; i < levels->levelarray->length ; i++) {
		Levelbutton* items = ArrayObjectAtIndex( levels->levelarray , i);
       	if (argument.isHit && !items->lock ) {

            if(items->buttontouch == argument.model )
            {
                if( argument.touchType == TouchTypeBegan && leveltouchID == NULL && !items->lock)
                {
                    printf("hit leveltouch begin\n");
                    leveltouchID = argument.touchID ;
                    levels->selectonoff = true;
                    levels->leveltouchindex = ((levels->page-1) * 36)+i ;

                    break;
                }
                else if( argument.touchType == TouchTypeMove && levels->leveltouchindex == ((levels->page-1) * 36)+i && levels->moveon )
                {
                    printf("hit leveltouch Move\n");
                    leveltouchID = NULL;
                    levels->leveltouchindex = -1 ;
                    levels->selectonoff = false;
                    break;
                }
                else if( argument.touchType == TouchTypeEnd && levels->leveltouchindex == ((levels->page-1) * 36)+i && !levels->moveon)
                {
                    printf("hit leveltouch end\n");
                    leveltouchID = NULL;
                    levels->levelevent.event(levels->levelevent.userReference, LevelEventTypeNone);
                    levels->selectonoff = false;
           //         levelselectSoundPlay(0);
                    break;
                }
            }
        }
        else {
            if(items->buttontouch == argument.model )
            {
                if( levels->leveltouchindex == ((levels->page-1) * 36)+i && levels->selectonoff)
                {

                    if( argument.touchType == TouchTypeEnd )
                    {
                        printf("leveltouch end\n");
                        leveltouchID = NULL;
                        levels->leveltouchindex = -1 ;
                        levels->selectonoff = false;
                        break;
                    }
                    else if( argument.touchType == TouchTypeMove  )
                    {
                        printf("leveltouch Move\n");
                        leveltouchID = NULL;
                        levels->leveltouchindex = -1 ;
                        levels->selectonoff = false;
                        break;
                    }
                }
            }
        }
    }
}
void LevelPacClearAnimation(Levels *levels)
{
    levels->page++;
    levels->gestureLast = levels->swichmodel->position.x;

    TweenStop(levels->pageTween);
    while(levels->pageTween->property->length) {
        TweenProperty* prop = ArrayObjectAtIndex(levels->pageTween->property, 0);
        TweenRemoveProperty(levels->pageTween, prop);
    }

    TweenAddProperty(levels->pageTween, TweenPropertyInit(&levels->gestureLast, levels->gestureLast, (-levels->page * 340.0f ) ));
    TweenGoToAndPlay(levels->pageTween, 0);

}
void  _LevelBackTouch(void *userReference, ModelEventTouchArgument argument)
{
	Levels* levels = (Levels*)userReference;

	if (argument.isHit && !levels->moveon) {

		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(levels->backbutton , 1);
		}
		if( argument.touchType == TouchTypeEnd )
		{
            if( levels->state == LevelSelectStateMain)
            {
                ModelGoToAndStop(levels->backbutton , 0);
                levels->levelevent.event(levels->levelevent.userReference, LevelEventTypeBack);
             //   levelselectSoundPlay(0);
            }
            else
            {
                ModelGoToAndStop(levels->backbutton , 0);
                LevelPackSetVisible(levels , false);
             //   levelselectSoundPlay(0);
            }
		}
	}
	else {
		if( argument.touchType == TouchTypeEnd  )
		{
			ModelGoToAndStop(levels->backbutton , 0);

		}

	}

}
void LevelFree(Levels *levels )
{
  //  levelselectSoundFree();
	levelSwipeID = NULL;
	leveltouchID = NULL;
    while(levels->pageTween->property->length) {
        TweenProperty* prop = ArrayObjectAtIndex(levels->pageTween->property, 0);
        TweenRemoveProperty(levels->pageTween, prop);
    }
    Model * _pack0 = ModelGetChildWithInstanceName(levels->pack0 , levels->tutorial_obj, "id_tutorial_popup");
    Model * _pack1 = ModelGetChildWithInstanceName(levels->pack1 , levels->select_menu, "id_menu_popupBig");
    Model * _pack2 = ModelGetChildWithInstanceName(levels->pack2 , levels->select_menu, "id_menu_popupBig");
    Model * _pack3 = ModelGetChildWithInstanceName(levels->pack3 , levels->select_menu, "id_menu_popupBig");
    ModelRemoveEventTouch(_pack0);
    ModelRemoveEventTouch(_pack1);
    ModelRemoveEventTouch(_pack2);
    ModelRemoveEventTouch(_pack3);

	Model * backtouch = ModelGetChildWithInstanceName(levels->backbutton , levels->select_menu , "id_menu_btnBack_on");
	ModelRemoveEventTouch(backtouch);
	Model * swipetouch = ModelGetChildWithInstanceName(levels->bg_0 , levels->select_bg0_obj , "id_menu_stage0_bg");
	ModelRemoveEventTouch(swipetouch);

    TweenManagerRemoveTween(levels->tweenmanger,levels->pageTween);
	TweenFree(levels->pageTween);
    free(levels->pageTween);

	free(levels->pagevec);
	free(levels->gestureStart);
	free(levels->gestureMove);
	free(levels->gestureEnd);
	int i = 0;
    for(  i = 0 ; i < 6 ; i++)
    {
       ObjectFileMadeMovieClipFree(&levels->pac1pointfont[i] );
       ObjectFileMadeMovieClipFree(&levels->pac2pointfont[i]);
       ObjectFileMadeMovieClipFree(&levels->pac3pointfont[i]);
    }
//    ObjectFileMadeMovieClipFree(&levels->pac4pointfont);

    ObjectFileMadeMovieClipFree(&levels->pac1starfont100);
    ObjectFileMadeMovieClipFree(&levels->pac1starfont10);
    ObjectFileMadeMovieClipFree(&levels->pac1starfont1);
    ObjectFileMadeMovieClipFree(&levels->pac2starfont100);
    ObjectFileMadeMovieClipFree(&levels->pac2starfont10);
    ObjectFileMadeMovieClipFree(&levels->pac2starfont1);
    ObjectFileMadeMovieClipFree(&levels->pac3starfont100);
    ObjectFileMadeMovieClipFree(&levels->pac3starfont10);
    ObjectFileMadeMovieClipFree(&levels->pac3starfont1);
//    ObjectFileMadeMovieClipFree(&levels->pac4starfont1);

    ObjectFileMadeMovieClipFree(&levels->pack1name);
    ObjectFileMadeMovieClipFree(&levels->pack2name);
    ObjectFileMadeMovieClipFree(&levels->pack3name);
    ObjectFileMadeMovieClipFree(&levels->pack4name);
    ObjectFileMadeMovieClipFree(&levels->pack1Mark);
    ObjectFileMadeMovieClipFree(&levels->pack2Mark);
    ObjectFileMadeMovieClipFree(&levels->pack3Mark);
    ObjectFileMadeMovieClipFree(&levels->pack4Mark);
    ObjectFileMadeMovieClipFree(&levels->pack0);
    ObjectFileMadeMovieClipFree(&levels->pack1);
    ObjectFileMadeMovieClipFree(&levels->pack2);
    ObjectFileMadeMovieClipFree(&levels->pack3);
    ObjectFileMadeMovieClipFree(&levels->pack4);
    ObjectFileMadeMovieClipFree(&levels->pageTitleModel);

    ObjectFileMadeMovieClipFree(&levels->commingsoon);
	ObjectFileMadeMovieClipFree(&levels->InStagePageModel);
	ObjectFileMadeMovieClipFree(&levels->bg_0);
	ObjectFileMadeMovieClipFree(&levels->backbutton);
	ObjectFileMadeMovieClipFree(&levels->IcepageModel);

	for ( i = levels->levelarray->length - 1 ;  i >= 0; i--) {
		Levelbutton* items = ArrayObjectAtIndex( levels->levelarray , i);
		ArrayPopObject(levels->levelarray , items);
		ModelRemoveEventTouch(items->buttontouch);
   		ObjectFileMadeMovieClipFree(&items->star);
		ObjectFileMadeMovieClipFree(&items->button);
		ObjectFileMadeMovieClipFree(&items->stageNum);
		if( items->stage10Num !=NULL)
			ObjectFileMadeMovieClipFree(&items->stage10Num);

		free(items);
	}
   // free(levels->resourcePath);
	ArrayFree(&levels->levelarray);
    ModelFree(levels->selectswichmodel);
    free(levels->selectswichmodel);
	ModelFree(levels->swichmodel);
    free(levels->swichmodel);
	ModelFree(levels->LWmodels);
    free(levels->LWmodels);
  	ObjectFileFree(&levels->tutorial_obj);
	ObjectFileFree(&levels->select_menu);
	ObjectFileFree(&levels->select_bg0_obj);
	ObjectFileFree(&levels->fonts);
}
void LevelRender(Levels *levels )
{

}
