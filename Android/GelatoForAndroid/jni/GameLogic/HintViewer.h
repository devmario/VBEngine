#ifndef gelatomania_HintViewer_h
#define gelatomania_HintViewer_h

#include "VBEngine.h"
#include "VBModel.h"

class GameMain;

typedef enum hintStateFlag
{
    hintStateItem = 0,
    hintStateIceCream = 1,
	hintStateTop = 2,
    hintStateDown = 3,
    hintStateTopping = 4,
    hintStateLeft = 5,
    hintStateRight = 6,
    hintStateReset = 7
} hintStateFlag;


class HintViewer {
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
    CCPoint position[8];
    hintStateFlag state;
    bool showFlag;
    
    void setState(hintStateFlag newState);
    void complete();
    
public:
    VBModel *arrowModel[8];
    VBModel *pointIceModel;
    VBModel *pointItemModel;
    VBModel *pointTopDownModel;
    
    float rotationR;
    
    HintViewer(GameMain *_parentModel, bool _showFlag=false, VBObjectFile2D *_obj=NULL, VBTexture *_tex=NULL);
    ~HintViewer();
    
    void show();
    void hide();
    void initStep();
    bool step(int itemIdx);
    void setSolution(int** recipe, int recipeLen, int* recipeArrLen, int* topping, int toppingLen);
    void setPosition(cocos2d::CCPoint _position);
    void update(float _deltaTime);
    
};

#endif
