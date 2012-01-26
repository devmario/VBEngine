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
    hintStateDown = 3
} hintStateFlag;


class HintViewer {
    int solutionLen;
    int currentSolutionIdx;
    int* solution;
    bool solutionFlag;
    GameMain *parent;
    VBObjectFile2D *object;
    VBTexture *texture;
    CCPoint position[4];
    hintStateFlag state;
    bool showFlag;
    
    void setState(hintStateFlag newState);
public:
    VBModel *arrowModel[4];
    VBModel *pointIceModel;
    VBModel *pointItemModel;
    VBModel *pointTopDownModel;
    
    float rotationR;
    
    HintViewer(GameMain *_parentModel, bool _showFlag=false, VBObjectFile2D *_obj=NULL, VBTexture *_tex=NULL, const char *iceModelName=NULL, const char *itemModelName=NULL, const char *topDownModelName=NULL, const char *downModelName=NULL);
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
