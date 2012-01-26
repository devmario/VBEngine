#ifndef gelatomania_IceCream_h
#define gelatomania_IceCream_h

#define NEXT_ICECREAM_Y 92

#include "VBModel.h"
#include "ShareData.h"
#include "RecipeAndToppingData.h"

class IceCream : public VBModel {
private:
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
    
    VBArrayVector* topping;
    
    VBArrayVector* thumbs;
    
    VBModel* modelTop;
    
    IceCream* next;
    IceCream* prev;
    
    bool need_update_pixel;
    bool need_update_bitmask;
    bool need_update_model;
    
    bool Mix();
    void FillCream(int _bitmask, bool _isMix = false);
    void Reshape();
    
public:
    IceCream(VBArrayVector* _rdVec, VBArrayVector* _tdVec, IceCream* _baseIceCream = NULL, int* _recipe = NULL, int _recipe_len = 0);
    ~IceCream();
    
    float GetClear();
    
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
};

#endif
