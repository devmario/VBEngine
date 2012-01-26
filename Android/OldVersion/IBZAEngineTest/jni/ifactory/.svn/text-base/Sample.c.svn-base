/*
 *  Sample.c
 *  iFactory
 *
 *  Created by Mario on 10. 11. 17..
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Sample.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
static long _getTime(void) {
	struct timeval now;
	gettimeofday(&now, NULL);
	return (long)(now.tv_sec*1000 + now.tv_usec/1000);
}


StageInfoEvents StageInfoEventsInit(void* userReference, void (*event)(void* userReference, StageInfoEventType type))
{
    StageInfoEvents mainEvent;
	mainEvent.userReference = userReference;
	mainEvent.event = event;
	return mainEvent;
}
void initSample(Sample *game , const char* _resourcePath , int w , int h , bool _gamecenter)
{
//	game->resourcePath = calloc(strlen(_resourcePath), sizeof(char));
//	sprintf(game->resourcePath, "%s", _resourcePath);
 //   resourcepaths  = calloc(strlen(_resourcePath), sizeof(char));
//	sprintf(resourcepaths, "%s", _resourcePath);
	
//	game->stageinfoevent = _stageinfoevent;
	//카메라 생성
	game->camera = calloc(1, sizeof(Camera));
	CameraInitWithVector3D(game->camera, Vector3DInit(0.0, 0.0, -415.0), Vector3DInit(0.0, 0.0, 0.0), Vector3DInit(-1.0, 0.0, 0.0));
	
	game->manager = calloc(1, sizeof(ModelManager));
	ModelManagerStart(game->manager, w, h, ColorHexRGBAToRGBAColor(0x000000FF));
	
	//최상위 모델 생성
	game->Wmodel = calloc(1, sizeof(Model));
	ModelInitDefault(game->Wmodel);
	game->gamecenters = _gamecenter;
  //  mainTitleSoundInit();

	game->titlelayout = ObjectFileLoad("titlelayout.obj" );
	game->gamestate = GameStaTeTypeTitle;
    TitleLayoutInit(game , 1);

	game->loadingModel = calloc(1, sizeof(Model));
	Vector3D* vec = calloc(4, sizeof(Vector3D));
	vec[0].x = -240.0;
	vec[1].x = 240.0;
	vec[0].y = -160.0;
	vec[1].y = -160.0;
	vec[2].x = -240.0;
	vec[3].x = 240.0;
	vec[2].y = 160.0;
	vec[3].y = 160.0;

	ModelInitWithVertex(game->loadingModel, 4, vec, NULL, NULL, 0, NULL, 0);
	ColorRGBA * color = calloc(4, sizeof(ColorRGBA));
	color[0] = ColorHexRGBAToRGBAColor(0x000000FF);
	color[1] = ColorHexRGBAToRGBAColor(0x000000FF);
	color[2] = ColorHexRGBAToRGBAColor(0x000000FF);
	color[3] = ColorHexRGBAToRGBAColor(0x000000FF);
	game->loadingModel->colorMode = ModelColorModeVertexColor;		
	ModelSetColorVertex(game->loadingModel, color , 4);
	free(color);

	ModelSetIsLighting(game->loadingModel, false);
	
//	ModelAdd(game->Wmodel , game->loadingModel );
	

	game->loadingModel->color->a = 0;
	
	game->rgba = 0;

	game->loadingTxT = ObjectFileMakeModelWithMovieClipName(game->titlelayout , "dyMom_title_loading");
	ModelAdd(game->Wmodel , game->loadingTxT);
	ModelSetPosition(game->loadingTxT , Vector3DInit(-89.15f, -50.0f, 1.0f));
	ModelSetIsVisible(game->loadingTxT , false);
	game->tweenmanger = calloc(1, sizeof(TweenManager));
	TweenManagerStart(game->tweenmanger);
	game->loadingTween = calloc(1, sizeof(Tween));
	TweenInit(game->loadingTween , 10, 1, TweenTrasitionTypeLinear, TweenEquationTypeEaseOut);

	TweenManagerAddTween(game->tweenmanger , game->loadingTween);
	TweenAddEventStep(game->loadingTween, TweenEventStepInit(_LoadingTweenStep, game));
	TweenAddEventComplete(game->loadingTween , TweenEventCompleteInit(_LoadingTweenComplete, game));
	game->Gameevent = GameEvnetNone;
	game->page = 0;
    game->selectpage1 = 0;
    game->selectpage2 = 0;
    game->selectpage3 = 0;
    game->stageInfoarray= ArrayInit();
    game->railsoundeff = 0.0f;
  //  mainTitleSoundPlay(1);
    PopupLayoutInit(game);

}
void GameMultiTaskBackground(Sample *game)
{
  //  if( game->stages != NULL)
  //      MultiTaskPause(game->stages);
}

void TitleLayoutInit(Sample *game, unsigned int _type)
{
	game->titleobj = ObjectFileLoad("titleintro.obj");
	game->creditlayout = ObjectFileLoad("creditlayer.obj" );

	game->titleModel = ObjectFileMakeModelWithMovieClipName(game->titleobj , "dyMom_title");
    game->titlelayoutModel = ObjectFileMakeModelWithMovieClipName(game->titlelayout , "dyMom_title");
    if( _type == 1)
    {
        ModelAdd(game->Wmodel  , game->titleModel );
        ModelAdd(game->Wmodel , game->titlelayoutModel);
    }
    else
    {
        ModelAddAt(game->Wmodel  , game->titlelayoutModel ,  game->Wmodel->child->length - 2);
		ModelAddAt(game->Wmodel  , game->titleModel ,  game->Wmodel->child->length - 3);
    }
	ModelSetPosition(game->titleModel , Vector3DInit(-240.0f , -160.0f , 1.0f ));

    game->aniicecream = ModelGetChildWithInstanceName( game->titleModel , game->titleobj , "id_dy_icecreamAni");
    ModelAllLoopPlay(game->aniicecream);


	ModelSetPosition(game->titlelayoutModel , Vector3DInit(-231.0f , -160.0f , 1.0f ));
 	game->newgameModel = ModelGetChildWithInstanceName( game->titlelayoutModel , game->titlelayout , "id_dy_title_btnPlay");
    game->newgametouchModel = ModelGetChildWithInstanceName( game->newgameModel , game->titlelayout , "id_title_btnPlay");
	ModelAddEventTouch(game->newgametouchModel , ModelEventTouchTinyInit(game ,_newgameModelTouch), 2, game->newgametouchModel->vertex , true , false , true , false);

    game->leftbuttonModel = ModelGetChildWithInstanceName(game->titlelayoutModel , game->titlelayout , "id_dy_title_btnLeft");
    game->leftbuttontouchModel = ModelGetChildWithInstanceName(game->leftbuttonModel , game->titlelayout , "id_title_btnBoxLeft");
    game->leftaniModel = ModelGetChildWithInstanceName(game->leftbuttonModel , game->titlelayout , "id_dy_title_iconSocial");
    ModelAddEventTouch(game->leftbuttontouchModel , ModelEventTouchTinyInit(game ,_leftbuttonModelTouch), 2, game->leftbuttontouchModel->vertex , true , false , true , false);
    if( game->gamecenters)
    {
        game->leftMenuaniModel = ModelGetChildWithInstanceName(game->titlelayoutModel , game->titlelayout , "id_dy_title_btnSocial");
        game->leftEndPoint = 69;
        game->facebookModel = ModelGetChildWithInstanceName(game->leftMenuaniModel, game->titlelayout , "id_dy_title_btnHome");
        game->facebookTouchModel = ModelGetChildWithInstanceName(game->facebookModel, game->titlelayout , "id_title_btnHome_on");
        ModelAddEventTouch(game->facebookTouchModel , ModelEventTouchTinyInit(game ,_facebookbuttonModelTouch), 2, game->facebookTouchModel->vertex , true , false , true , false);

      //  game->tweeterModel = ModelGetChildWithInstanceName(game->leftMenuaniModel, game->titlelayout , "id_dy_title_btnTwitter");
      //  game->tweeterTouchModel = ModelGetChildWithInstanceName(game->tweeterModel, game->titlelayout , "id_title_btnTwitter_on");
      //  ModelAddEventTouch(game->tweeterTouchModel , ModelEventTouchTinyInit(game ,_tweeterbuttonModelTouch), 2, game->tweeterTouchModel->vertex , true , false , true , false);

        game->gamecenterModel = ModelGetChildWithInstanceName(game->leftMenuaniModel, game->titlelayout ,"id_dy_title_btnLeaderboard");
        game->gamecenterTouchModel = ModelGetChildWithInstanceName(game->gamecenterModel, game->titlelayout ,"id_title_btnLeaderboard_on");
        ModelAddEventTouch(game->gamecenterTouchModel , ModelEventTouchTinyInit(game ,_gamecenterbuttonModelTouch), 2, game->gamecenterTouchModel->vertex , true , false , true , false);

        game->AchivemnetModel = ModelGetChildWithInstanceName(game->leftMenuaniModel, game->titlelayout ,"id_dy_title_btnAchivement");
        game->AchivemnetTouchModel = ModelGetChildWithInstanceName(game->AchivemnetModel, game->titlelayout ,"id_title_btnAchivement_on");
        ModelAddEventTouch(game->AchivemnetTouchModel , ModelEventTouchTinyInit(game ,_AchievementbuttonModelTouch), 2, game->AchivemnetTouchModel->vertex , true , false , true , false);
    }
    else
    {
        game->leftMenuaniModel = ModelGetChildWithInstanceName(game->titlelayoutModel , game->titlelayout , "id_dy_title_btnSocial2");
        game->leftEndPoint = 59;

        game->facebookModel = ModelGetChildWithInstanceName(game->leftMenuaniModel, game->titlelayout , "id_dy_title_btnHome02");
        game->facebookTouchModel = ModelGetChildWithInstanceName(game->facebookModel, game->titlelayout , "id_title_btnHome02_on");
        ModelAddEventTouch(game->facebookTouchModel , ModelEventTouchTinyInit(game ,_facebookbuttonModelTouch), 2, game->facebookTouchModel->vertex , true , false , true , false);

    //    game->tweeterModel = ModelGetChildWithInstanceName(game->leftMenuaniModel, game->titlelayout , "id_dy_title_btnTwitter2");
    //    game->tweeterTouchModel = ModelGetChildWithInstanceName(game->tweeterModel, game->titlelayout , "id_title_btnTwitter2_on");
    //    ModelAddEventTouch(game->tweeterTouchModel , ModelEventTouchTinyInit(game ,_tweeterbuttonModelTouch), 2, game->tweeterTouchModel->vertex , true , false , true , false);


    }

    game->leftmenuOnOff = false;



    game->rightbuttonModel = ModelGetChildWithInstanceName(game->titlelayoutModel , game->titlelayout , "id_dy_title_btnRight");
	game->rightbuttontouchModel = ModelGetChildWithInstanceName(game->rightbuttonModel , game->titlelayout , "title_btnBoxRight");
    game->rightaniModel = ModelGetChildWithInstanceName(game->rightbuttonModel , game->titlelayout , "id_dy_title_iconOption");
    ModelAddEventTouch(game->rightbuttontouchModel , ModelEventTouchTinyInit(game ,_rightbuttonModelTouch), 2, game->rightbuttontouchModel->vertex , true , false , true , false);
    game->rightMenuaniModel = ModelGetChildWithInstanceName(game->titlelayoutModel , game->titlelayout , "id_dy_title_btnInformation");
    game->rightmenuOnOff = false;

    game->gameresetModel = ModelGetChildWithInstanceName(game->rightMenuaniModel, game->titlelayout , "id_dy_title_btnReset");
    game->gameresetTouchModel = ModelGetChildWithInstanceName(game->gameresetModel, game->titlelayout , "id_title_btnReset_on");
    ModelAddEventTouch(game->gameresetTouchModel , ModelEventTouchTinyInit(game ,_gameresetbuttonModelTouch), 2, game->gameresetTouchModel->vertex , true , false , true , false);

    game->gameinforModel = ModelGetChildWithInstanceName(game->rightMenuaniModel, game->titlelayout , "id_dy_title_btnInfo");
    game->gameinforTouchModel = ModelGetChildWithInstanceName(game->gameinforModel, game->titlelayout , "id_title_btnInfo_on");
    ModelAddEventTouch(game->gameinforTouchModel , ModelEventTouchTinyInit(game ,_gameinforbuttonModelTouch), 2, game->gameinforTouchModel->vertex , true , false , true , false);

    game->creditBackgroundModel = ObjectFileMakeModelWithMovieClipName(game->creditlayout , "dy_credit_backWood");
    game->creditpaperModel = ObjectFileMakeModelWithMovieClipName(game->creditlayout , "dy_credit_paper");
    game->creditBtnModel = ObjectFileMakeModelWithMovieClipName(game->creditlayout , "dy_credit_btnBack");
    game->creditBtnTouchModel = ModelGetChildWithInstanceName(game->creditBtnModel, game->creditlayout, "id_credit_btnBack");
    ModelAddEventTouch(game->creditBtnTouchModel , ModelEventTouchTinyInit(game ,_gameCreditbackbuttonModelTouch), 2, game->creditBtnTouchModel->vertex , true , false , true , false);
    Model* papermodeltouch = ModelGetChildWithInstanceName(game->creditpaperModel , game->creditlayout, "id_credit_paper");
    ModelAddEventTouch(papermodeltouch , ModelEventTouchTinyInit(game ,_gameCreditSwipebuttonModelTouch), 2, papermodeltouch->vertex , true , false , true , false);

    ModelAdd(game->titlelayoutModel, game->creditBackgroundModel );
    ModelAdd(game->creditBackgroundModel, game->creditpaperModel );
    ModelAdd(game->creditBackgroundModel, game->creditBtnModel );
	ModelSetPosition(game->creditBackgroundModel , Vector3DInit(-9.0f, 0.0f, 1.0f));
	ModelSetPosition(game->creditpaperModel , Vector3DInit(55.0f, 100.0f, 1.0f));
    ModelSetPosition(game->creditBtnModel , Vector3DInit(425.25f, 263.25f, 1.0f));

    ModelSetIsVisible(game->creditBackgroundModel , false);
    ModelSetIsVisible(game->creditpaperModel , false);
    ModelSetIsVisible(game->creditBtnModel , false);
}
void PopupLayoutInit(Sample *game)
{
    game->gameresetPopupModel = ObjectFileMakeModelWithMovieClipName(game->titlelayout , "dyMom_reset");
    ModelAdd(game->Wmodel , game->gameresetPopupModel);
    ModelSetPosition(game->gameresetPopupModel, Vector3DInit(-182.5f, -87.5f, 1.0f));
    ModelSetIsVisible(game->gameresetPopupModel, false);
    game->gameresetPopupTxTModel = ModelGetChildWithInstanceName(game->gameresetPopupModel, game->titlelayout, "id_dy_title_ResetTxt");
    game->gameresetPopupResetBtnModel = ModelGetChildWithInstanceName(game->gameresetPopupModel, game->titlelayout, "id_dy_title_btnAlertReset");
    game->gameresetPopup_cancel_BtnModel= ModelGetChildWithInstanceName(game->gameresetPopupModel, game->titlelayout,"id_dy_title_btnCancel");
    game->gameresetPopupResetBtntouchModel= ModelGetChildWithInstanceName(game->gameresetPopupResetBtnModel, game->titlelayout, "id_title_btnAlertReset_on");
    
    game->gameresetPopup_cancel_BtntouchModel= ModelGetChildWithInstanceName(game->gameresetPopup_cancel_BtnModel, game->titlelayout, "id_title_btnCancel_on");
    ModelAddEventTouch(game->gameresetPopupResetBtntouchModel , ModelEventTouchTinyInit(game ,_gameResetPopup_ResetBtn_Touch), 2, game->gameresetPopupResetBtntouchModel->vertex , true , false , true , false);
    ModelAddEventTouch(game->gameresetPopup_cancel_BtntouchModel , ModelEventTouchTinyInit(game ,_gameResetPopup_CancelBtn_Touch), 2, game->gameresetPopup_cancel_BtntouchModel->vertex , true , false , true , false);

}

void TitleLayoutFree(Sample *game)
{
    ModelRemove(game->Wmodel , game->titleModel);
    ModelRemove(game->Wmodel , game->titlelayoutModel);
    ModelRemove(game->Wmodel , game->gameresetPopupModel);

    ModelRemoveEventTouch(game->newgametouchModel);
    ModelRemoveEventTouch(game->leftbuttontouchModel);
    ModelRemoveEventTouch(game->facebookTouchModel);
  //  ModelRemoveEventTouch(game->tweeterTouchModel);
    ModelRemoveEventTouch(game->rightbuttontouchModel);
    ModelRemoveEventTouch(game->gameresetTouchModel);
    ModelRemoveEventTouch(game->gameinforTouchModel);
    ModelRemoveEventTouch(game->creditBtnTouchModel);
    Model* papermodeltouch = ModelGetChildWithInstanceName(game->creditpaperModel , game->creditlayout, "id_credit_paper");
    ModelRemoveEventTouch(papermodeltouch);
    ModelRemoveEventTouch(game->gameresetPopupResetBtntouchModel);
    ModelRemoveEventTouch(game->gameresetPopup_cancel_BtntouchModel);

    if( game->gamecenters)
    {
        ModelRemoveEventTouch(game->gamecenterTouchModel);
        ModelRemoveEventTouch(game->AchivemnetTouchModel);
    }

    ModelRemove(game->titlelayoutModel, game->creditBackgroundModel);
    ModelRemove(game->creditBackgroundModel, game->creditpaperModel);
    ModelRemove(game->creditBackgroundModel, game->creditBtnModel);

    ObjectFileMadeMovieClipFree(&game->gameresetPopupModel);
    ObjectFileMadeMovieClipFree(&game->creditBackgroundModel);
    ObjectFileMadeMovieClipFree(&game->creditpaperModel);
	ObjectFileMadeMovieClipFree(&game->creditBtnModel);


    ObjectFileMadeMovieClipFree(&game->titleModel);
    ObjectFileMadeMovieClipFree(&game->titlelayoutModel);


    ObjectFileFree(&game->creditlayout);
    ObjectFileFree(&game->titleobj);
}
void _LoadingTweenStep(Tween* tween, void* userReference)
{
	Sample *game = (Sample*)userReference;

	game->loadingModel->color->a = game->rgba;
	
}
void _LoadingTweenComplete(Tween* tween, void* userReference)
{
	Sample *game = (Sample*)userReference;
    while(game->loadingTween->property->length) {
        TweenProperty* prop = ArrayObjectAtIndex(game->loadingTween->property, 0);
        TweenRemoveProperty(game->loadingTween, prop);
    }

	if( 	game->Gameevent == GameEvnetLevelStageIn)
	{
		LOGV("Levelinit");
		game->levels = calloc(1, sizeof(Levels));
		LOGV("Levelinit calloc");
        LevelInit(game->levels, game->resourcePath ,LevelEventInit(game, _LevelsEvent) , game->manager ,game->tweenmanger, game->page ,
                  game->selectpage1, game->selectpage2, game->selectpage3, false , game->stageInfoarray);
        LOGV("Levelinit complete");
		ModelAddAt(game->Wmodel, game->levels->LWmodels ,  game->Wmodel->child->length - 3);

        ModelGoToAndStop(game->aniicecream, game->aniicecream->ani->aniCurFrame);
        TitleLayoutFree(game);

     	game->gamestate =  GameStaTeTypeLevelSelect;
	}
/*	else if( 	game->Gameevent == GameEvnetGameOut)
	{
        ModelRemove(game->Wmodel,game->stages->SWmodel);
        if( game->stages != NULL)
		{
			freeStage(game->stages );
			free(game->stages);
			game->stages = NULL;

		}
		game->levels = calloc(1, sizeof(Levels));
        LevelInit(game->levels, game->resourcePath ,LevelEventInit(game, _LevelsEvent) , game->manager ,game->tweenmanger, game->page ,
                  game->selectpage1, game->selectpage2, game->selectpage3, true , game->stageInfoarray);
		ModelAddAt(game->Wmodel, game->levels->LWmodels,  game->Wmodel->child->length - 2);
		game->gamestate = GameStaTeTypeLevelSelect;
		mainTitleBackgroundPlay();
    }
	else if( 	game->Gameevent == GameEvnetGameIn)
	{
        ModelRemove(game->Wmodel, game->levels->LWmodels);
        game->page = game->levels->page;
        game->selectpage1 = game->levels->selectpage1;
        game->selectpage2 = game->levels->selectpage2;
        game->selectpage3 = game->levels->selectpage3;
        int touchindex = game->levels->leveltouchindex;
        if( game->levels != NULL)
		{
			LevelFree(game->levels);
			free(game->levels);
			game->levels = NULL;
		}

		game->stages = calloc(1, sizeof(Stage));


		initStage(game->stages, game->resourcePath,GameStageEventInit(game ,_StageEvent ), game->manager ,game->tweenmanger,  touchindex);
		ModelAddAt(game->Wmodel, game->stages->SWmodel,  game->Wmodel->child->length - 2);
		

		game->gamestate = GameStaTeTypeGame;
	}
	else if( 	game->Gameevent == GameEvnetTitleIn)
	{

        game->page = game->levels->page;
        ModelRemove(game->Wmodel, game->levels->LWmodels);
        if( game->levels != NULL)
		{
			LevelFree(game->levels);
			free(game->levels);
			game->levels = NULL;
		}
		game->gamestate = GameStaTeTypeTitle;

        TitleLayoutInit(game , 2);
        PopupLayoutInit(game);

  //      mainRailSoundInit();
  //      mainTitleSoundPlay(1);
        game->railsoundeff = 0.0f;
	}
	else if( game->Gameevent == GameEvnetGameNext)
	{
        NextResetGame(game->stages);
	}
    else if( game->Gameevent == GameEvnetGamePacClear)
    {
        ModelRemove(game->Wmodel,game->stages->SWmodel);
        if( game->stages != NULL)
		{
			freeStage(game->stages );
			free(game->stages);
			game->stages = NULL;

		}
        game->levels = calloc(1, sizeof(Levels));
        LevelInit(game->levels, game->resourcePath ,LevelEventInit(game, _LevelsEvent) , game->manager ,game->tweenmanger, game->page ,
                  game->selectpage1, game->selectpage2, game->selectpage3, false , game->stageInfoarray);
		ModelAddAt(game->Wmodel, game->levels->LWmodels,  game->Wmodel->child->length - 2);
		game->gamestate = GameStaTeTypeLevelSelect;
		mainTitleBackgroundPlay();
        LevelPacClearAnimation(game->levels);
    }
    else if(game->Gameevent == GameEvnetGameAllClear)
    {
        ModelRemove(game->Wmodel,game->stages->SWmodel);
        if( game->stages != NULL)
		{
			freeStage(game->stages );
			free(game->stages);
			game->stages = NULL;

		}
        mainTitleBackgroundPlay();
        game->levels = calloc(1, sizeof(Levels));
        LevelInit(game->levels, game->resourcePath ,LevelEventInit(game, _LevelsEvent) , game->manager ,game->tweenmanger, game->page ,
                  game->selectpage1, game->selectpage2, game->selectpage3, true , game->stageInfoarray);
        ModelAddAt(game->Wmodel, game->levels->LWmodels,  game->Wmodel->child->length - 2);
        game->gamestate = GameStaTeTypeLevelSelect;

    }
    else if( game->Gameevent == GameEvnetGameTutorial)
    {
        ModelRemove(game->Wmodel, game->levels->LWmodels);
        if( game->levels != NULL)
		{
			LevelFree(game->levels);
			free(game->levels);
			game->levels = NULL;
		}
        
        game->tutorial = calloc(1, sizeof(Tutorial));
		initTutorial(game->tutorial, game->resourcePath,TutorialEventsInit(game ,_TutorialEvent ), game->manager ,game->tweenmanger,  90 , game->language);
		ModelAddAt(game->Wmodel, game->tutorial->SWmodel,  game->Wmodel->child->length - 2);

		game->stageinfoevent.event(game->stageinfoevent.userReference, GameTuTorialStart);
		game->gamestate = GameStaTeTypeTutoial;
    }
    else if( game->Gameevent == GameEvnetGameTutorialBack)
    {
        ModelRemove(game->Wmodel,game->tutorial->SWmodel);
        if( game->tutorial != NULL)
		{
			freeTutorial(game->tutorial );
			free(game->tutorial);
			game->tutorial = NULL;

		}
         mainTitleBackgroundPlay();
        game->levels = calloc(1, sizeof(Levels));
        LevelInit(game->levels, game->resourcePath ,LevelEventInit(game, _LevelsEvent) , game->manager ,game->tweenmanger, game->page ,
                  game->selectpage1, game->selectpage2, game->selectpage3, false , game->stageInfoarray);
		ModelAddAt(game->Wmodel, game->levels->LWmodels,  game->Wmodel->child->length - 2);
		game->gamestate = GameStaTeTypeLevelSelect;

    }
    else if( game->Gameevent == GameEvnetGameTutorialClear)
    {
        ModelRemove(game->Wmodel,game->tutorial->SWmodel);
        if( game->tutorial != NULL)
		{
			freeTutorial(game->tutorial );
			free(game->tutorial);
			game->tutorial = NULL;
            mainTitleBackgroundPlay();
		}
        game->levels = calloc(1, sizeof(Levels));
        LevelInit(game->levels, game->resourcePath ,LevelEventInit(game, _LevelsEvent) , game->manager ,game->tweenmanger, game->page ,
                  game->selectpage1, game->selectpage2, game->selectpage3, false , game->stageInfoarray);
		ModelAddAt(game->Wmodel, game->levels->LWmodels,  game->Wmodel->child->length - 2);
		game->gamestate = GameStaTeTypeLevelSelect;

        LevelPacClearAnimation(game->levels);
    }
*/
	
	ModelSetIsVisible(game->loadingTxT , false);
	game->loadingModel->color->a = 0;
	game->rgba = 0;
	game->Gameevent = GameEvnetNone;
	
}


void *newGameTouchId = NULL;
void  _newgameModelTouch(void *userReference, ModelEventTouchArgument argument)
{
	Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->Gameevent ==GameEvnetNone)
	{
		if( argument.touchType == TouchTypeBegan && newGameTouchId == NULL)
		{
			ModelGoToAndStop( game->newgameModel , 5);
			newGameTouchId = argument.touchID;
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd && newGameTouchId != NULL)
		{
			ModelGoToAndStop( game->newgameModel , 0);
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);
			game->Gameevent = GameEvnetLevelStageIn;
			ModelSetIsVisible(game->loadingTxT , true);
			newGameTouchId = NULL;
    //        mainTitleSoundPlay(0);
     //       mainRailSoundUnload();
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle){
		if( argument.touchType == TouchTypeEnd)
		{
			ModelGoToAndStop( game->newgameModel , 0);
			newGameTouchId = NULL;
		}
	}
	
}

void *leftTouchId = NULL;
void  _leftbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
	Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->Gameevent ==GameEvnetNone)
	{
		if( argument.touchType == TouchTypeBegan && leftTouchId == NULL)
		{
			leftTouchId = argument.touchID;
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd && leftTouchId == argument.touchID)
		{
            leftTouchId = NULL;
             if( !game->leftmenuOnOff && !game->leftMenuaniModel->ani->aniIsPlay)
             {
                ModelGoToAndPlay(game->leftMenuaniModel , 0 );
                ModelPlay(game->leftaniModel);
     //           mainTitleSoundPlay(0);
             }
            else if( game->leftmenuOnOff && !game->leftMenuaniModel->ani->aniIsPlay)
            {
                ModelGoToAndPlay(game->leftMenuaniModel , 34 );
                ModelPlay(game->leftaniModel);
      //          mainTitleSoundPlay(0);
            }
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle){
		if( argument.touchType == TouchTypeEnd)
		{
			leftTouchId = NULL;
		}
	}
}
void *rightTouchId = NULL;
void  _rightbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->Gameevent ==GameEvnetNone)
	{
		if( argument.touchType == TouchTypeBegan && rightTouchId == NULL)
		{
			rightTouchId = argument.touchID;
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd && rightTouchId == argument.touchID)
		{
            rightTouchId = NULL;
            if( !game->rightmenuOnOff && !game->rightMenuaniModel->ani->aniIsPlay)
            {
                ModelGoToAndPlay(game->rightMenuaniModel , 0 );
                ModelPlay(game->rightaniModel);
    //            mainTitleSoundPlay(0);
            }
            else if( game->rightmenuOnOff && !game->rightMenuaniModel->ani->aniIsPlay)
            {
                ModelGoToAndPlay(game->rightMenuaniModel , 34 );
                ModelPlay(game->rightaniModel);
    //            mainTitleSoundPlay(0);
            }
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle){
		if( argument.touchType == TouchTypeEnd)
		{
			rightTouchId = NULL;
		}
	}
}
void  _gamecenterbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->leftMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->gamecenterModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->gamecenterModel, 0);
      //      mainTitleSoundPlay(0);
       //     game->stageinfoevent.event(game->stageinfoevent.userReference, GameCenterLeaderboard);
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle && game->leftMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
  			ModelGoToAndStop(game->gamecenterModel, 0);
		}
	}
}
void  _AchievementbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->leftMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->AchivemnetModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->AchivemnetModel, 0);
  //          mainTitleSoundPlay(0);
         //   game->stageinfoevent.event(game->stageinfoevent.userReference, GameCenterAchivement);
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle && game->leftMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
  			ModelGoToAndStop(game->AchivemnetModel, 0);
		}
	}

}
void  _facebookbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->leftMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->facebookModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->facebookModel, 0);
 //           mainTitleSoundPlay(0);
       //     game->stageinfoevent.event(game->stageinfoevent.userReference, FACEBOOKFANPAGE);
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle && game->leftMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
  			ModelGoToAndStop(game->facebookModel, 0);
		}
	}
}

void  _gameresetbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->rightMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->gameresetModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->gameresetModel, 0);
 //           mainTitleSoundPlay(0);
            ModelSetIsVisible(game->gameresetPopupModel, true);
            game->loadingModel->color->a = LOADING_OPACITY;
            game->gamestate = GameStaTeTypeResetPopup;
            if( game->language)
                ModelGoToAndStop(game->gameresetPopupTxTModel, 0);
            else
                ModelGoToAndStop(game->gameresetPopupTxTModel, 1);
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle && game->rightMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
            if( game->gameresetModel->ani->aniCurFrame == 1)
            {
                ModelGoToAndStop(game->gameresetModel, 0);
//                mainTitleSoundPlay(0);
            }
		}
	}
}
void  _gameResetPopup_ResetBtn_Touch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeResetPopup && game->rightMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->gameresetPopupResetBtnModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->gameresetPopupResetBtnModel, 0);
   //         mainTitleSoundPlay(0);
            ModelSetIsVisible(game->gameresetPopupModel, false);
            game->loadingModel->color->a = 0;
            game->gamestate = GameStaTeTypeTitle;

    //        game->stageinfoevent.event(game->stageinfoevent.userReference, GameResets);
		}
	}
	else if(game->gamestate == GameStaTeTypeResetPopup && game->rightMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
            if( game->gameresetModel->ani->aniCurFrame == 1)
            {
                ModelGoToAndStop(game->gameresetPopupResetBtnModel, 0);
    //            mainTitleSoundPlay(0);
            }
		}
	}
}
void  _gameResetPopup_CancelBtn_Touch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeResetPopup && game->rightMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->gameresetPopup_cancel_BtnModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->gameresetPopup_cancel_BtnModel, 0);
  //          mainTitleSoundPlay(0);
            ModelSetIsVisible(game->gameresetPopupModel, false);
            game->loadingModel->color->a = 0;
            game->gamestate = GameStaTeTypeTitle;
		}
	}
	else if(game->gamestate == GameStaTeTypeResetPopup && game->rightMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
            if( game->gameresetModel->ani->aniCurFrame == 1)
            {
                ModelGoToAndStop(game->gameresetPopup_cancel_BtnModel, 0);
    //            mainTitleSoundPlay(0);
            }
		}
	}
}

void  _gameinforbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
	if( argument.isHit && game->gamestate == GameStaTeTypeTitle && game->rightMenuaniModel->ani->aniCurFrame == 30 )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			ModelGoToAndStop(game->gameinforModel, 1);
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd )
		{
   			ModelGoToAndStop(game->gameinforModel, 0);
  //          mainTitleSoundPlay(0);
   //         mainRailSoundUnload();
            ModelSetIsVisible(game->creditBackgroundModel , true);
            ModelSetIsVisible(game->creditpaperModel , true);
            ModelSetIsVisible(game->creditBtnModel , true);
            game->creditAutoMove = false;
            game->gamestate = GameStaTeTypeCredits;
            game->creditPosY = 100.0f;
            ModelSetPosition(game->creditpaperModel , Vector3DInit(55.0f, game->creditPosY, 1.0f));
   //         game->stageinfoevent.event(game->stageinfoevent.userReference, GameCreditView);
		}
	}
	else if(game->gamestate == GameStaTeTypeTitle && game->rightMenuaniModel->ani->aniCurFrame == 30){
		if( argument.touchType == TouchTypeEnd)
		{
            if( game->gameinforModel->ani->aniCurFrame == 1)
            {
                ModelGoToAndStop(game->gameinforModel, 0);
  //              mainTitleSoundPlay(0);
  //              mainRailSoundUnload();
                ModelSetIsVisible(game->creditBackgroundModel , true);
                ModelSetIsVisible(game->creditpaperModel , true);
                ModelSetIsVisible(game->creditBtnModel , true);
                game->creditAutoMove = false;
                game->gamestate = GameStaTeTypeCredits;
                game->creditPosY = 100.0f;
                ModelSetPosition(game->creditpaperModel , Vector3DInit(55.0f, game->creditPosY, 1.0f));
            }
		}
	}
}
void *creditbtnID = NULL;
void  _gameCreditbackbuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
    if( argument.isHit && game->gamestate == GameStaTeTypeCredits )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			creditbtnID = argument.touchID;
		}
		else if( argument.touchType == TouchTypeMove)
		{
		}
		else if( argument.touchType == TouchTypeEnd && creditbtnID != NULL)
		{
            creditbtnID = NULL;
 //           mainTitleSoundPlay(0);
            ModelSetIsVisible(game->creditBackgroundModel , false);
            ModelSetIsVisible(game->creditpaperModel , false);
            ModelSetIsVisible(game->creditBtnModel , false);
            game->gamestate = GameStaTeTypeTitle;
     //       mainRailSoundInit();
  //          mainTitleSoundPlay(1);
            game->railsoundeff = 0.0f;
		}
	}
	else if(game->gamestate == GameStaTeTypeCredits){
		if( argument.touchType == TouchTypeEnd)
		{
            if( creditbtnID != NULL)
            {
                creditbtnID = NULL;
  //              mainTitleSoundPlay(0);
                ModelSetIsVisible(game->creditBackgroundModel , false);
                ModelSetIsVisible(game->creditpaperModel , false);
                ModelSetIsVisible(game->creditBtnModel , false);
                game->gamestate = GameStaTeTypeTitle;
   //             mainRailSoundInit();
  //              mainTitleSoundPlay(1);
                game->railsoundeff = 0.0f;
            }
		}
	}
}
void * creditswipeID = NULL;
void  _gameCreditSwipebuttonModelTouch(void *userReference, ModelEventTouchArgument argument)
{
    Sample *game = (Sample*)userReference;
    if( argument.isHit && game->gamestate == GameStaTeTypeCredits )
	{
		if( argument.touchType == TouchTypeBegan)
		{
			creditswipeID = argument.touchID;
            game->gestureStart.y = argument.hitVectorGlobal->x + 160.0f;
            game->gestureLast = game->creditpaperModel->position.y;

		}
		else if( argument.touchType == TouchTypeMove)
		{
            float deltay = fabsf(game->gestureStart.y -  (argument.hitVectorGlobal->x + 160.0f) );

            if( (game->gestureStart.y - (argument.hitVectorGlobal->x + 160.0f))  < 0.0f  )
            {
                ModelSetPosition(game->creditpaperModel , Vector3DInit(55.0f , (game->gestureLast - deltay ), 1.0f));
                if( game->creditpaperModel->position.y < -128.0f)
                     ModelSetPosition(game->creditpaperModel, Vector3DInit(55.0f, -128.0f, 1.0f));


            }
            else if( (game->gestureStart.y - (argument.hitVectorGlobal->x + 160.0f)) > 0.0f  )
            {
                if( (game->gestureLast  + deltay ) < 0.0f)
                {
                    ModelSetPosition(game->creditpaperModel , Vector3DInit(55.0f , (game->gestureLast  + deltay ), 1.0f));
                }
                else{
                    ModelSetPosition(game->creditpaperModel, Vector3DInit(55.0f, 0.0f, 1.0f));
                }
            }

		}
		else if( argument.touchType == TouchTypeEnd && creditswipeID != NULL)
		{
            creditswipeID = NULL;
        }
	}
	else if(game->gamestate == GameStaTeTypeCredits){
		if( argument.touchType == TouchTypeEnd)
		{
            if( creditswipeID != NULL)
            {
                creditswipeID = NULL;
            }
		}
	}
}/*
void _TutorialEvent(void* userReference ,  GameStageType eventType)
{
    Sample *game = (Sample*)userReference;
    if( game->tutorial != NULL)
	{
        if( eventType == TutorialTypeBack )
		{
            game->Gameevent = GameEvnetGameTutorialBack;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);
        }
        else if( eventType == TutorialTypeClear )
		{
            game->Gameevent = GameEvnetGameTutorialClear;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);
            StageInfo * nextinfo = ArrayObjectAtIndex(game->stageInfoarray , 0);
            nextinfo->lock   = true;
            game->stageinfoevent.event(game->stageinfoevent.userReference, TutorialClear);
        }
    }
}
void _StageEvent(void* userReference ,  GameStageType eventType)
{
	Sample *game = (Sample*)userReference;
	if( game->stages != NULL)
	{
		if( eventType == GameStageTypeNone )
		{
			game->Gameevent = GameEvnetGameOut;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);			
		}
		else if( eventType == GameStageTypeLevelReset && game->Gameevent == GameEvnetNone)
		{
			game->Gameevent = GameEvnetGameNext;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);			
		}
		else if( eventType == GameStageTypeBack )
		{
            game->Gameevent = GameEvnetGameAllClear;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);


		}
        else if( eventType == GameStageInforSave )
		{
            StageInfo * curentinfo = ArrayObjectAtIndex(game->stageInfoarray , game->stages->stagecount);

            if( curentinfo->stagepoint < game->stages->totalpoint)
            {
                printf("%i   %i \n" , curentinfo->stagepoint , game->stages->totalpoint) ;
                curentinfo->stagepoint = game->stages->totalpoint;
            }
            else
            {

            }
            if( curentinfo->star < game->stages->stagestars)
            {
                curentinfo->star = game->stages->stagestars;
            }
            if( game->stages->stagecount + 1 < STAGE_NUMBER)
            {
                StageInfo * nextinfo = ArrayObjectAtIndex(game->stageInfoarray , game->stages->stagecount + 1);
                nextinfo->lock   = true;
            }

            game->stageinfoevent.event(game->stageinfoevent.userReference, StageInfoSave);
        }
        else if( eventType == GameStagePacClear )
		{
            game->Gameevent = GameEvnetGamePacClear;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);
        }
        else if( eventType == GameStageTypeTwitterpost )
		{
            game->stageinfoevent.event(game->stageinfoevent.userReference, TwitterSite);
        }
        else if( eventType == GameStageTypeFacebookpost )
		{
            game->stageinfoevent.event(game->stageinfoevent.userReference, FaceBokkSite);
        }
	}
	
}*/

void _LevelsEvent(void* userReference ,  LevelEventType eventType)
{
	Sample *game = (Sample*)userReference;
	if(game->levels != NULL&& game->Gameevent == GameEvnetNone)
	{
		if( eventType == LevelEventTypeNone)
		{
			game->Gameevent = GameEvnetGameIn;

			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);			
		}
		else if( eventType == LevelEventTypeBack)
		{
			game->Gameevent = GameEvnetTitleIn;
			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);
		}
        else if( eventType == LevelEventTypeSave)
        {
            game->page = game->levels->page;
            game->selectpage1 = game->levels->selectpage1;
            game->selectpage2 = game->levels->selectpage2;
            game->selectpage3 = game->levels->selectpage3;
        //    game->stageinfoevent.event(game->stageinfoevent.userReference, StagePageSave);
        }
        else if( eventType == LevelEventTypeTutorial)
		{
			game->Gameevent = GameEvnetGameTutorial;

			TweenAddProperty(game->loadingTween, TweenPropertyInit(&game->rgba, game->rgba, LOADING_OPACITY));
			TweenGoToAndPlay(game->loadingTween, 0);

			ModelSetIsVisible(game->loadingTxT , true);			
		}

	}
}




void renderSample(Sample *game , float tick)
{

	
	float deltaTime = tick;


    //printf("cur fps %i \n" , game->aniicecream->ani->aniCurFrame);

	TweenManagerStep(game->tweenmanger, 1);

    if( game->gamestate == GameStaTeTypeCredits)
    {
        if(!game->creditAutoMove)
        {
            game->creditPosY -= 1.0;

        if(game->creditPosY < -128.0f)
        {
            game->creditPosY = -128.0f;
            game->creditAutoMove = true;
        }
            ModelSetPosition(game->creditpaperModel , Vector3DInit(55.0f, game->creditPosY, 1.0f));
        }
    }
    else if( game->gamestate == GameStaTeTypeResetPopup)
    {
        game->railsoundeff += deltaTime;
        if(game->railsoundeff > 6.0f)
        {
 //           mainTitleSoundPlay(1);
            game->railsoundeff = 0.0f;
        }
		/*if( game->levels != NULL)
		{
			LevelFree(game->levels);
			free(game->levels);
			game->levels = NULL;
		}*/
    }
	
	if( game->gamestate == GameStaTeTypeTitle)
	{
        game->railsoundeff += deltaTime;
        if(game->railsoundeff > 6.0f)
        {
   //         mainTitleSoundPlay(1);
            game->railsoundeff = 0.0f;
        }
		/*if( game->levels != NULL)
		{
			LevelFree(game->levels);
			free(game->levels);
			game->levels = NULL;
		}*/
        if( game->leftaniModel->ani->aniCurFrame == 20)
        {
            ModelGoToAndStop(game->leftaniModel , 0);
        }
        if( game->rightaniModel->ani->aniCurFrame == 20)
        {
            ModelGoToAndStop(game->rightaniModel , 0);
        }

        if( game->leftMenuaniModel->ani->aniCurFrame == 29)
        {
           ModelGoToAndStop(game->leftMenuaniModel, 30);
            game->leftmenuOnOff = true;
        }
        else if(game->leftMenuaniModel->ani->aniCurFrame == game->leftEndPoint)
        {
             ModelGoToAndStop(game->leftMenuaniModel, 0);
            game->leftmenuOnOff = false;
        }

        if( game->rightMenuaniModel->ani->aniCurFrame == 29)
        {
            ModelGoToAndStop(game->rightMenuaniModel, 30);
            game->rightmenuOnOff = true;
        }
        else if(game->rightMenuaniModel->ani->aniCurFrame == 69)
        {
            ModelGoToAndStop(game->rightMenuaniModel, 0);
            game->rightmenuOnOff = false;
        }
	}
	if( game->gamestate ==  GameStaTeTypeLevelSelect)
	{
		LevelRender(game->levels);
	}
/*
	if( game->gamestate ==  GameStaTeTypeGame)
	{
		renderStage(game->stages , deltaTime);
	}

    if( game->gamestate ==  GameStaTeTypeTutoial)
	{
		renderTutorial(game->tutorial , deltaTime);
	}*/
	
	ModelManagerDisplayBegin(game->manager, ModelManagerDisplayMode3D, game->camera, NULL);
	ModelManagerDisplay(game->manager, game->Wmodel);
	ModelManagerDisplayEnd(game->manager);
  //  oldTick = currTick;
}

void freeSample(Sample *game )
{	
  //  free(resourcepaths);
  //  mainTitleSoundFree();
/*	if(game->stages != NULL)
	{
		freeStage(game->stages);
	}
    
    if(game->tutorial != NULL)
	{
		freeTutorial(game->tutorial);
	}*/

    if(game->levels != NULL)
	{
		LevelFree(game->levels);
	}
    int i = 0 ;
    for ( i = game->stageInfoarray->length - 1 ;  i >= 0; i--) {
		StageInfo* items = ArrayObjectAtIndex( game->stageInfoarray , i);
		ArrayPopObject(game->stageInfoarray , items);
		free(items);
	}
    ArrayFree(&game->stageInfoarray);
    ModelRemoveEventTouch(game->newgametouchModel);
    ModelRemoveEventTouch(game->leftbuttontouchModel);
    ModelRemoveEventTouch(game->facebookTouchModel);
//  ModelRemoveEventTouch(game->tweeterTouchModel);
    ModelRemoveEventTouch(game->rightbuttontouchModel);
    ModelRemoveEventTouch(game->gameresetTouchModel);
    ModelRemoveEventTouch(game->gameinforTouchModel);
    ModelRemoveEventTouch(game->creditBtnTouchModel);

    ModelRemoveEventTouch(game->gameresetPopupResetBtntouchModel);
    ModelRemoveEventTouch(game->gameresetPopup_cancel_BtntouchModel);
    
    if( game->gamecenters)
    {
      ModelRemoveEventTouch(game->gamecenterTouchModel);
      ModelRemoveEventTouch(game->AchivemnetTouchModel);
    }

    Model* papermodeltouch = ModelGetChildWithInstanceName(game->creditpaperModel , game->creditlayout, "id_credit_paper");
    ModelRemoveEventTouch(papermodeltouch);
    ModelRemove(game->titlelayoutModel, game->creditBackgroundModel);
    ModelRemove(game->creditBackgroundModel, game->creditpaperModel);
    ModelRemove(game->creditBackgroundModel, game->creditBtnModel);
    ObjectFileMadeMovieClipFree(&game->gameresetPopupModel);
    ObjectFileMadeMovieClipFree(&game->creditBackgroundModel);
    ObjectFileMadeMovieClipFree(&game->creditpaperModel);
	ObjectFileMadeMovieClipFree(&game->creditBtnModel);


    ObjectFileMadeMovieClipFree(&game->titleModel);
    ObjectFileMadeMovieClipFree(&game->titlelayoutModel);
	ObjectFileMadeMovieClipFree(&game->loadingTxT);
	//VertexModelFree(game->loadingModel);
	TweenFree(game->loadingTween);
	TweenManagerShutdown(game->tweenmanger);
	
	ModelFree(game->Wmodel);
	free(game->Wmodel);
	game->Wmodel = NULL;
	
	ModelManagerShutdown(game->manager);
	free(game->manager);
	game->manager = NULL;
	
	CameraFree(game->camera);
	free(game->camera);
	game->camera = NULL;
    ObjectFileFree(&game->creditlayout);
    ObjectFileFree(&game->titlelayout);
    ObjectFileFree(&game->titleobj);
}
