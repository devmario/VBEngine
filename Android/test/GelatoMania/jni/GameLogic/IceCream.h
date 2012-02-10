#ifndef gelatomania_IceCream_h
#define gelatomania_IceCream_h

#define NEXT_ICECREAM_Y 92

#include "VBModel.h"
#include "ShareData.h"
#include "RecipeAndToppingData.h"
#include <pthread.h>

class IceCream;

typedef struct drawIceCremArg {
    IceCream* iceCream;
    VBImage* _imgArea;
    VBAABB _aabbArea;
    VBImage* _imgMask;
    VBAABB _aabbMask;
    int _shiftBit;
    int _hex;
} drawIceCremArg;

class GameMain;

class IceCreamProtocol {
public:
    virtual void GetIceCreamChecker(float per) {};
};

class IceCream : public VBModel {
public:
    
    drawIceCremArg fillArg;
    IceCreamProtocol* protocol;
    
    pthread_t draw_pixel_thread;
    pthread_t mix_thread;
    pthread_t checker_thread;
    bool isRun_draw_pixel_thread;
    bool isRun_draw_pixel_threadReal;
    bool isRun_mix_thread;
    bool isRunClearCheck;
    
    VBArrayVector* rdVec;
    VBArrayVector* tdVec;
    
    //NULL이면 왼쪽에 나오는 답안 아이스크림
    IceCream* baseIceCream;
    
    unsigned long isClear;
    unsigned long totalClear;
    
    VBTexture* texBgOutline;
    VBModel* modelBgOutline;
    
    VBTexture* texBridgeOutline;
    VBModel* modelBridgeOutline;
    
    VBAABB aabbBG;
    
    VBImage* imgBGOrigin;
    VBImage* imgBG;
    VBTexture* texBG;
    VBModel* modelBG;
    
    VBAABB aabbBridge;
    
    VBImage* imgBridgeOrigin;
    VBImage* imgBridge;
    VBTexture* texBridge;
    VBModel* modelBridge;
    
    VBAABB aabbBitmask;
    VBImage* imgBitmask;
    unsigned long bitmaskMerge;
    
    VBArrayVector* mask;
    
    VBModel* modelLastRecipe;
    VBModel* modelLastRecipeBridge;
    
    VBArrayVector* subTopping;
    VBArrayVector* subToppingFlow;
    
    VBArrayVector* toppingSpuitL;
    VBArrayVector* toppingSpuitR;
    VBArrayVector* toppingFlow;
    void* toppingCream;
    void* toppingCherry;
    
    VBArrayVector* thumbs;
    
    VBModel* modelTop;
    
    bool need_update_pixel;
    bool need_update_model;
    
    bool Mix();
    void FillCream(int _bitmask, bool _isMix = false);
    void Reshape();
    
    GameMain *gameMain;
public:
    IceCream* next;
    IceCream* prev;
    
    IceCream(GameMain *_gameMain, VBArrayVector* _rdVec, VBArrayVector* _tdVec, IceCreamProtocol* _protocol, IceCream* _baseIceCream = NULL, int* _recipe = NULL, int _recipe_len = 0);
    ~IceCream();
    
    void GetClear();
    
    unsigned int GetHeight();
    
    VBModel* DragStartMount(VBModel* _topView);
    void DragEndMount(bool _success);
    
    bool IsEqual(IceCream* _other);
    void SaveImage(char* _fileName);
    
    void Mix(RecipeMix* _rm);
    void AddMask(RecipeMask* _rm);
    int ClearMask(RecipeMask* _rm, int _num);
    void FillCream(VBImage* _imgArea, VBAABB _aabbArea, VBImage* _imgMask, VBAABB _aabbMask, int _shiftBit, int _hex);
    void FillCream(RecipeFill* _rf, int _isMix);
    bool AddSubTopping(RecipeSubTopping* _rst);
    bool AddSubToppingFlow(RecipeSubToppingFlow* _rstf);
    void SetLast(RecipeLast* _rl);
    bool AddRecipe(int _recipe);
    
    bool IsHaveSubTopping();
    bool IsPossibleRecipe(int _recipe);
    bool IsPossibleTopping(int _topping);
    bool IsPossibleNext();
    
    void AddToppingSpuit(ToppingSpuit* _ts);
    void AddToppingFlow(ToppingFlow* _tf);
    void AddToppingCream(ToppingCream* _tc);
    void AddToppingCherry(ToppingCherry* _tc);
    bool AddTopping(int _topping);
    
    bool AddNextIceCream(int* _recipe = NULL, int _recipe_len = 0);
    bool AddNextIceCream(IceCream* _other);
    
    virtual void VBModelUpdate(float _tick);
    void setGameMain(GameMain* _gameMain);
};

#endif
