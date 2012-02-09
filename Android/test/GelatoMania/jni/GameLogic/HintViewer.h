#ifndef gelatomania_HintViewer_h
#define gelatomania_HintViewer_h

#include "VBEngine.h"
#include "VBModel.h"

#define HINTSTATELEN 10

class GameMain;

typedef enum hintStepWrongLevel
{
    hintWrongNone = 0,
    hintWrongMaskOn = 1,
    hintWrongMaskOnDouble = 2,
    hintWrongMaskOff = 3,
    hintWrongMaskOffDouble = 4,
    //TODO: when fill other color
    hintWrongFillFull = 5   
} hintStepWrongLevel;

typedef enum hintStateFlag
{
    hintStateItem = 0,
    hintStateIceCream = 1,
	hintStateTop = 2,
    hintStateDown = 3,
    hintStateTopping = 4,
    hintStateLeft = 5,
    hintStateRight = 6,
    hintStateReset = 7,
    hintStateAdd = 8,
    hintStateToppingItem = 9
} hintStateFlag;

typedef enum actionType
{
    actionTypeNone = 0,
    actionTypeRecipe = 1,
    actionTypeIceCream = 2,
    actionTypeTopping = 3
} actionType;

class HintViewer {
    unsigned int retainCount;
    
    VBObjectFile2D *object;
    VBTexture *texture;
    VBModel *arrowModel[HINTSTATELEN];
    
    bool* isMask;
    bool maskOn;
    int maskStack[2];
    int solutionLen;
    int currentSolutionIdx;
    int* solution;
    GameMain *gameMain;
    
    CCPoint position[HINTSTATELEN];
    hintStateFlag hintState;
    bool showFlag;
    
    int pushMask(int maskIdx);
    int popMask(int* maskIdx=NULL);
    
    hintStepWrongLevel wrongMode;
    int wrongIdx;
    int wrongIdxForMask;
    
    actionType lastAction;
    
    void loadArrowModel();
    void loadMaskList();
    
    void setState(hintStateFlag newState);
    
    void step(actionType currentAction, int itemIdx);
    void initStep(bool isWrongStep);
    void wrongStep(hintStepWrongLevel _wrongType, int _wrongIdx=-1);
    void checkAndFinish();
    
public:
    
    HintViewer(GameMain *_gameMain, bool _showFlag=false);
    ~HintViewer();
    
    void update(float _deltaTime);
    
    void setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen);
    void setGameMain(GameMain* _gameMain);
    
    void show();
    void hide();
    
    void retain();
    void release();
    
    actionType getLastActionType();
    void resetAction();
    void iceCreamAction(int itemIdx);
    void recipeContainerAction(int itemIdx);
    void toppingAction(int itemIdx);
};

#endif
