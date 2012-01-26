#ifndef gelatomania_RecipeContainer_h
#define gelatomania_RecipeContainer_h

#include "ScrollerContainer.h"
#include "IceCream.h"

class GameMain;
class RecipeContainer;

typedef struct RecipeContainerCellData {
    int recipeIdx;
    
    VBString* texPath;
    
    VBObjectFile2DLibraryNameID* name_id;
    VBObjectFile2D* obj;
    
    CCTouch* touch;
    
    VBTexture* tex;
    
    VBModel* shelf;
    
    VBModel* model;
    
    int status;
    
    VBModel* full;
    VBModel* disable;
    VBModel* empty;
    VBModel* pour;
    
    VBVector2D startVec;
    VBVector2D subVec;
    VBVector2D preVec;
    float swipe;
} RecipeContainerCellData;

RecipeContainerCellData* RecipeContainerCellDataInit(int _recipeIdx);
void RecipeContainerCellDataFree(RecipeContainerCellData** _ptr);

class RecipeContainer : public ScrollerContainer {
    //for hintviewer
    int recipeLen;
    int* recipeIndex;
    
public:
    VBModel* pourTarget;
    VBModel* pour;
    RecipeContainerCellData* selectedRecipe;
    GameMain* gameMain;
    IceCream* hitTarget;
    void (*hitFunc)(RecipeContainerCellData* _data);
    
    VBObjectFile2D* objShelf;
    VBTexture* texShelf;
    VBObjectFile2DLibraryNameID* nameIdShelf;
    
    RecipeContainer(VBObjectFile2D* _objShelf, VBTexture* _texShelf, VBObjectFile2D* _objScroller, VBTexture* _texScroller, VBArrayVector* _data, GameMain *_gameMain, VBModel* _pourTarget, IceCream* _hitTarget, void (*_hitFunc)(RecipeContainerCellData* _data));
    ~RecipeContainer();
    
    float getItemPositionY(int itemIdx);
    
    virtual void touchEndAndCancel(CCTouch* _touch, CCPoint _location);
    virtual void touchMove(CCTouch* _touch, CCPoint _location);
    
    virtual void CellAlloc(CellData* _cell);
    virtual void CellFree(CellData* _cell);
    virtual void CellTouchBegin(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchMove(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchEnd(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellTouchCancel(CellData* _cell, CCTouch* _touch, CCPoint _location);
    virtual void CellUpdate(CellData* _cell, float _deltaTime);
};


#endif
