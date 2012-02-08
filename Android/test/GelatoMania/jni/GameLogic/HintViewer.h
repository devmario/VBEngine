#ifndef gelatomania_HintViewer_h
#define gelatomania_HintViewer_h

#include "VBEngine.h"
#include "VBModel.h"

#define HINTSTATELEN 10

class GameMain;

typedef enum hintStepWrongLevel
{
    hintWrongNone = 0,
    hintWrongReset = 1,
    hintWrongMaskOn = 2,
    hintWrongMaskOnDouble = 3,
    hintWrongMaskOff = 4,
    hintWrongMaskOffDouble = 5
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


class HintViewer {
    unsigned int retainCount;
    
    bool* isMask;
    bool maskOn;
    int maskStack[2];
    int solutionLen;
    int currentSolutionIdx;
    int* solution;
    bool solutionFlag;
    GameMain *parent;
    VBObjectFile2D *object;
    VBTexture *texture;
    CCPoint position[HINTSTATELEN];
    hintStateFlag state;
    bool showFlag;
    
    void setState(hintStateFlag newState);
    
    bool wrongStep(hintStepWrongLevel _wrongType, int _wrongIdx=-1);
    void checkAndFinish();
    
    hintStepWrongLevel wrongMode;
    int wrongIdx;
    int wrongIdxForMask;
    
public:
    VBModel *arrowModel[HINTSTATELEN];
    
    float rotationR;
    
    HintViewer(GameMain *_parentModel, bool _showFlag=false, VBObjectFile2D *_obj=NULL, VBTexture *_tex=NULL);
    ~HintViewer();
    
    void show();
    void hide();
    void initStep(bool isWrongStep);
    bool step(int itemIdx);
    void setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen);
    void setPosition(cocos2d::CCPoint _position);
    void update(float _deltaTime);
    
    void setGameMain(GameMain* _gameMain);
    void retain();
    void release();
    
};

#endif
