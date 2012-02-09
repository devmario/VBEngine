#ifndef gelatomania_GameMain_h
#define gelatomania_GameMain_h

#include "View.h"
#include "RecipeContainer.h"
#include "IceCream.h"
#include "ToppingContainer.h"
#include "Slider.h"
#include "ShareData.h"
#include "HintViewer.h"
#include "GameMainRdTd.h"

using namespace tween;

//typedef enum 

class GameMain : public View, IceCreamProtocol {
private:
    
    bool initWithIceCream;
    
    int packIdx;
    int stageIdx;
    
    int bgLen;
    
    unsigned int stepCount;
    
    VBObjectFile2D** objBg;
    VBTexture** texBg;
    
    VBObjectFile2D* objUI;
    VBTexture* texUI;
    
    VBObjectFile2D* objArm;
    VBTexture* texArm;
    
    VBObjectFile2D* objScroll;
    VBTexture* texScroll;
    
    VBObjectFile2D* objFont;
    VBTexture* texFont;
    
    bool isClear;
    float clearPer;
    
    void LoadResource(cJSON* _layer, cJSON* _ui);
    void UnloadResource();
    
    VBModel** modelBg;
    VBModel* modelUI;
    
    VBModel* modelArm;
    
    VBModel* modelPauseButton;
    VBModel* modelNewButton;
    VBModel* modelUpButton;
    VBModel* modelDownButton;
    VBModel* modelDoor;
    VBModel* modelRail;
    VBModel* modelRailIce[2];
    
    void InitModel(cJSON* _layer, cJSON* _ui);
    void FreeModel();
    
    VBModel* dragIce;
    CCPoint dragPre;
    
    CCTouch* touchDown;
    CCTouch* touchUp;
    CCTouch* touchPause;
    CCTouch* touchNew;
    CCTouch* touchCook;
    
    void InitCook();
    void FreeCook();
    
    bool isRecipeMode;
    
    VBArrayVector* recipeData;
    RecipeContainer* recipeContainer;
    
    void InitRecipe();
    void FreeRecipe();
    
    VBArrayVector* toppingData;
    ToppingContainer* toppingContainer;
    
    void InitTopping();
    void FreeTopping();
    
    TweenerWrapper* toppingTweener;

    float toppingTweenerY;
    
    void ClearToppingTween();
    void BeginToppingTween(float _y, float _time, bool _is_ease_out);
    void UpdateToppingTween(float _deltaTime);
    
    Slider* nextRopeSlider;
    Slider* toppingRopeSlider;
    
    void InitRope();
    void FreeRope();
    
    static void CallbackSlideNextRope(void* _obj);
    static void CallbackSlideToppingRope(void* _obj);
    
    void NextIceCream();
    void NextIceCreamUpdate(float _deltaTime);
    
    void NewIceCream();
    void NewIceCreamWithBack();
    void NewIceCreamUpdate(float _deltaTime);
    
    void SwapRecipeAndToppingMode();
    void SwapRecipeAndToppingModeUpdate(float _deltaTime);
    
    bool IsActiveUI();
    
    bool saveStep();
    void resetAllStep();
    
public:
    HintViewer *hintViewer;
    GameMainRdTd *rdTd;
    IceCream* baseIceCream;
    IceCream* iceCream;
    IceCream* delIceCream;
    IceCream* nextIceCream;
    IceCream* nextIceCreamMotion;
    
    virtual void GetIceCreamChecker(float per);
    
    GameMain(int _packIdx, int _stageIdx, IceCream* _baseIceCream=NULL, IceCream* _playedIceCream=NULL, IceCream* _nextIceCream=NULL, GameMainRdTd* _rdTd=NULL, HintViewer* _hintViewer=NULL, bool _isRecipeMode=false);
    ~GameMain();
    
    void resetOtherStage(int _packIdx, int _stageIdx);
    
    float getRecipePositionY(int recipeIdx);
    void recipeContainerCallBack(int recipeIdx);
    float getToppingPositionX(int toppingIdx);
    void toppingContainerCallBack(int recipeIdx);
    void iceCreamMaskCallBack(int recipeIdx);
    
    virtual void Update(float _deltaTime);
    
    virtual void touchBegin(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    virtual void touchEnd(CCTouch* _touch, CCPoint _location);
    virtual void touchCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    
    void retainIceCream();
    bool IsRecipeMode();
    
    void unDo();
};


#endif
