#ifndef gelatomania_GameMain_h
#define gelatomania_GameMain_h

#include "View.h"
#include "RecipeContainer.h"
#include "IceCream.h"
#include "ToppingContainer.h"
#include "Slider.h"
#include "ShareData.h"
#include "HintViewer.h"

using namespace tween;

class GameMain : public View {
private:
    int packIdx;
    int stageIdx;
    int* rd;
    int rdLen;
    int* td;
    int tdLen;
    
    int bgLen;
    
    VBArrayVector* rdVec;
    VBArrayVector* tdVec;
    
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
    
    IceCream* baseIceCream;
    IceCream* iceCream;
    IceCream* delIceCream;
    IceCream* nextIceCream;
    IceCream* nextIceCreamMotion;
    
    void InitCook(int** _rtc, int _rtcLen, int* _rtcArrLen, int* _tc, int _tcLen);
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
    
    Tweener* toppingTweener;
    TweenerParam* toppingTweenerParam;
    float toppingTweenerTime;
    float toppingTweenerTimeCount;
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
    void NewIceCreamUpdate(float _deltaTime);
    
    void SwapRecipeAndToppingMode();
    void SwapRecipeAndToppingModeUpdate(float _deltaTime);
    bool IsRecipeMode();
    
    bool IsActiveUI();
    
    HintViewer *hintViewer;
public:
    
    GameMain(int _packIdx, int _stageIdx);
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
};


#endif
