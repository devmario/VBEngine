#include "IceCream.h"

float IceCream::GetClear() {
#ifdef TEST_AABB_AMOUNT
    VBAABB test1 = {0, 0, 10, 10};
    VBAABB test2 = {5, 5, 15, 15};
    VBAABB test3 = {5, 5, 15, 15};
    VBAABB test[3] = {test1, test2, test3};
    cout << VBAABBGetAmount(test1) << "\n";
    cout << VBAABBGetAmount(test2) << "\n";
    cout << VBAABBGetAmount(test3) << "\n";
    cout << "\n";
    
    VBAABB hit;
    bool isHit = VBAABBGetHitAABB(test1, test2, &hit);
    cout << isHit << "," << hit.l << "," << hit.t << "," << hit.r << "," << hit.b << "\n";
    cout << VBAABBGetAmount(hit) << "\n";
    cout << "\n";
    
    isHit = VBAABBGetHitAABB(test2, test3, &hit);
    cout << isHit << "," << hit.l << "," << hit.t << "," << hit.r << "," << hit.b << "\n";
    cout << VBAABBGetAmount(hit) << "\n";
    cout << "\n";
    
    isHit = VBAABBGetHitAABB(test1, test3, &hit);
    cout << isHit << "," << hit.l << "," << hit.t << "," << hit.r << "," << hit.b << "\n";
    cout << VBAABBGetAmount(hit) << "\n";
    cout << "\n";
    
    cout << VBAABBGetAmountAtManyBox(3, test) << "\n";
#endif
    
    cout << "\n";
    
    /*******************bg***********************/
    cout << "\n";
    cout << "< GetClear bg >\n";
    
    VBAABB* bg_aabb = NULL;
    int bg_aabbIdx = 0;
    
    unsigned long _clear = 0;
    unsigned long _totalClear = 0;
    
    IceCream* _link = this;
    IceCream* _linkBase = baseIceCream;
    
    VBVector2D _vec = VBVector2DCreate(0, 0);
    
    while(_link || _linkBase) {
        if(_link)
            bg_aabb = VBAABBMemResizeAndSet(bg_aabb, VBAABBShift(_link->aabbBG, _vec), bg_aabbIdx, ++bg_aabbIdx);
        if(_linkBase)
            bg_aabb = VBAABBMemResizeAndSet(bg_aabb, VBAABBShift(_linkBase->aabbBG, _vec), bg_aabbIdx, ++bg_aabbIdx);
        
        if(_link)
            _clear += _link->isClear;
        _totalClear += _link ? _link->totalClear : _linkBase->totalClear;
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float bg_amount = VBAABBGetAmountAtManyBox(bg_aabbIdx, bg_aabb);
    
    float _bgPer = (float)_clear / _totalClear;
    _bgPer = isnan(_bgPer) ? 0 : _bgPer;
    cout << "_bgPer:" << _bgPer << "\n";
    
    if(bg_aabb)
        free(bg_aabb);
    
    
    
    /*******************maskThumb***********************/
    cout << "\n";
    cout << "< GetClear maskThumb >\n";
    
    VBAABB* mask_aabb = NULL;
    int mask_aabbIdx = 0;
    
    unsigned long _maskThumb = 0;
    unsigned long _maskThumbTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        for(int i = 0; i < MAX((_link ? _link->mask->len : 0), (_linkBase ? _linkBase->mask->len : 0)); i++) {
            void* _data = NULL;
            if(i < (_link ? _link->mask->len : 0)) {
                _data = _link->mask->data[i];
                RecipeMask* _r = (RecipeMask*)_data;
                mask_aabb = VBAABBMemResizeAndSet(mask_aabb, VBAABBShift(_r->aabbThumb, _vec), mask_aabbIdx, ++mask_aabbIdx);
            }
            void* _dataBase = NULL;
            if(i < (_linkBase ? _linkBase->mask->len : 0)) {
                _dataBase = _linkBase->mask->data[i];
                RecipeMask* _r = (RecipeMask*)_dataBase;
                mask_aabb = VBAABBMemResizeAndSet(mask_aabb, VBAABBShift(_r->aabbThumb, _vec), mask_aabbIdx, ++mask_aabbIdx);
            }
            if(_data && _dataBase) {
                if(_data == _dataBase)
                    _maskThumb++;
            }
            _maskThumbTotal++;
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float mask_amount = VBAABBGetAmountAtManyBox(mask_aabbIdx, mask_aabb);
    
    float _maskThumbPer = (float)_maskThumb / (float)_maskThumbTotal;
    _maskThumbPer = isnan(_maskThumbPer) ? 0 : _maskThumbPer;
    cout << "_maskThumbPer:" << _maskThumbPer << ", _maskThumb:" << _maskThumb << ", _maskThumbTotal:" << _maskThumbTotal << "\n";
    
    if(mask_aabb)
        free(mask_aabb);
    
    
    /*******************subTopping***********************/
    cout << "\n";
    cout << "< GetClear subTopping >\n";
    
    VBAABB* subTopping_aabb = NULL;
    int subTopping_aabbIdx = 0;
    
    unsigned long _subTopping = 0;
    unsigned long _subToppingTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        for(int i = MAX((_link ? _link->subTopping->len : 0), (_linkBase ? _linkBase->subTopping->len : 0)) - 1; i > -1 ; i--) {
            void* _data = NULL;
            if(i < (_link ? _link->subTopping->len : 0)) {
                _data = _link->subTopping->data[i];
            }
            void* _dataBase = NULL;
            if(i < (_linkBase ? _linkBase->subTopping->len : 0)) {
                _dataBase = _linkBase->subTopping->data[i];
            }
            if(_data) {
                RecipeSubTopping* _r = (RecipeSubTopping*)_data;
                subTopping_aabb = VBAABBMemResizeAndSet(subTopping_aabb, VBAABBShift(_r->aabbThumb, _vec), subTopping_aabbIdx, ++subTopping_aabbIdx);
            }
            if(_dataBase) {
                RecipeSubTopping* _r = (RecipeSubTopping*)_dataBase;
                subTopping_aabb = VBAABBMemResizeAndSet(subTopping_aabb, VBAABBShift(_r->aabbThumb, _vec), subTopping_aabbIdx, ++subTopping_aabbIdx);
            }
            if(_data && _dataBase) {
                if(_data == _dataBase)
                    _subTopping++;
            }
            _subToppingTotal++;
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float subTopping_amount = VBAABBGetAmountAtManyBox(subTopping_aabbIdx, subTopping_aabb);
    
    float _subToppingPer = (float)_subTopping / (float)_subToppingTotal;
    _subToppingPer = isnan(_subToppingPer) ? 0 : _subToppingPer;
    cout << "_subToppingPer:" << _subToppingPer << ", _subTopping:" << _subTopping << ", _subToppingTotal:" << _subToppingTotal << "\n";
    
    if(subTopping_aabb)
        free(subTopping_aabb);
    
    
    /*******************subToppingFlow***********************/
    cout << "\n";
    cout << "< GetClear subToppingFlow >\n";
    
    VBAABB* subToppingFlow_aabb = NULL;
    int subToppingFlow_aabbIdx = 0;
    
    unsigned long _subToppingFlow = 0;
    unsigned long _subToppingFlowTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        for(int i = 0; i < MAX((_link ? _link->subToppingFlow->len : _linkBase->subToppingFlow->len), (_linkBase ? _linkBase->subToppingFlow->len : _link->subToppingFlow->len)); i++) {
            VBArrayVector* _arr = NULL;
            if(_link)
                _arr = (VBArrayVector*)VBArrayVectorGetDataAt(_link->subToppingFlow, i);
            VBArrayVector* _arrBase = NULL;
            if(_linkBase)
                _arrBase = (VBArrayVector*)VBArrayVectorGetDataAt(_linkBase->subToppingFlow, i);
            for(int j = 0; j < MAX((_arr ? _arr->len : 0), (_arrBase ? _arrBase->len : 0)); j++) {
                void* _data = NULL;
                if(j < (_arr ? _arr->len : 0)) {
                    _data = _arr->data[j];
                    RecipeSubToppingFlow* _r = (RecipeSubToppingFlow*)_data;
                    subToppingFlow_aabb = VBAABBMemResizeAndSet(subToppingFlow_aabb, VBAABBShift(_r->aabbThumb[j], _vec), subToppingFlow_aabbIdx, ++subToppingFlow_aabbIdx);
                }
                void* _dataBase = NULL;
                if(j < (_arrBase ? _arrBase->len : 0)) {
                    _dataBase = _arrBase->data[j];
                    RecipeSubToppingFlow* _r = (RecipeSubToppingFlow*)_dataBase;
                    subToppingFlow_aabb = VBAABBMemResizeAndSet(subToppingFlow_aabb, VBAABBShift(_r->aabbThumb[j], _vec), subToppingFlow_aabbIdx, ++subToppingFlow_aabbIdx);
                }
                //cout << j << ":" << _data << ", " << _dataBase;
                if(_data && _dataBase) {
                    if(_data == _dataBase) {
                        _subToppingFlow++;
                        //cout << " is Equal";
                    }
                }
                //cout << "\n";
                _subToppingFlowTotal++;
            }
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float subToppingFlow_amount = VBAABBGetAmountAtManyBox(subToppingFlow_aabbIdx, subToppingFlow_aabb);
    
    float _subToppingFlowPer = (float)_subToppingFlow / (float)_subToppingFlowTotal;
    _subToppingFlowPer = isnan(_subToppingFlowPer) ? 0 : _subToppingFlowPer;
    cout << "_subToppingFlowPer:" << _subToppingFlowPer << ", _subToppingFlow:" << _subToppingFlow << ", _subToppingFlowTotal:" << _subToppingFlowTotal << "\n";
    
    if(subToppingFlow_aabb)
        free(subToppingFlow_aabb);
    
    /*******************toppingSpuit***********************/
    cout << "\n";
    cout << "< GetClear toppingSpuit >\n";
    
    VBAABB* toppingSpuit_aabb = NULL;
    int toppingSpuit_aabbIdx = 0;
    
    unsigned long _toppingSpuit = 0;
    unsigned long _toppingSpuitTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        TS_idx* _tiL[0xFF] = {NULL,};
        int _tiL_idx = 0;
        TS_idx* _tiLBase[0xFF] = {NULL,};
        int _tiLBase_idx = 0;
        
        TS_idx* _tiR[0xFF] = {NULL,};
        int _tiR_idx = 0;
        TS_idx* _tiRBase[0xFF] = {NULL,};
        int _tiRBase_idx = 0;
        
        int _lid = 0;
        int _rid = 0;
        
        if(_link) {
            _lid = -1;
            for(int i = _link->toppingSpuitL->len - 1; i > -1; i--) {
                TS_idx* _ti = (TS_idx*)_link->toppingSpuitL->data[i];
                if(_lid < _ti->_idx) {
                    _lid = _ti->_idx;
                    _tiL[_tiL_idx] = _ti;
                    _tiL_idx++;
                }
            }
            _rid = -1;
            for(int i = _link->toppingSpuitR->len - 1; i > -1; i--) {
                TS_idx* _ti = (TS_idx*)_link->toppingSpuitR->data[i];
                if(_rid < _ti->_idx) {
                    _rid = _ti->_idx;
                    _tiR[_tiR_idx] = _ti;
                    _tiR_idx++;
                }
            }
        }
        
        if(_linkBase) {
            _lid = -1;
            for(int i = _linkBase->toppingSpuitL->len - 1; i > -1; i--) {
                TS_idx* _ti = (TS_idx*)_linkBase->toppingSpuitL->data[i];
                if(_lid < _ti->_idx) {
                    _lid = _ti->_idx;
                    _tiLBase[_tiLBase_idx] = _ti;
                    _tiLBase_idx++;
                }
            }
            _rid = -1;
            for(int i = _linkBase->toppingSpuitR->len - 1; i > -1; i--) {
                TS_idx* _ti = (TS_idx*)_linkBase->toppingSpuitR->data[i];
                if(_rid < _ti->_idx) {
                    _rid = _ti->_idx;
                    _tiRBase[_tiRBase_idx] = _ti;
                    _tiRBase_idx++;
                }
            }
        }
        
        for(int i = 0; i < _tiLBase_idx; i++) {
            toppingSpuit_aabb = VBAABBMemResizeAndSet(toppingSpuit_aabb, VBAABBShift(_tiLBase[i]->_aabb, _vec), toppingSpuit_aabbIdx, ++toppingSpuit_aabbIdx);
        }
        
        for(int i = 0; i < _tiRBase_idx; i++) {
            toppingSpuit_aabb = VBAABBMemResizeAndSet(toppingSpuit_aabb, VBAABBShift(_tiRBase[i]->_aabb, _vec), toppingSpuit_aabbIdx, ++toppingSpuit_aabbIdx);
        }
        for(int i = 0; i < _tiL_idx; i++) {
            toppingSpuit_aabb = VBAABBMemResizeAndSet(toppingSpuit_aabb, VBAABBShift(_tiL[i]->_aabb, _vec), toppingSpuit_aabbIdx, ++toppingSpuit_aabbIdx);
        }
        
        for(int i = 0; i < _tiR_idx; i++) {
            toppingSpuit_aabb = VBAABBMemResizeAndSet(toppingSpuit_aabb, VBAABBShift(_tiR[i]->_aabb, _vec), toppingSpuit_aabbIdx, ++toppingSpuit_aabbIdx);
        }
        
        for(int i = 0; i < _tiL_idx; i++) {
            for(int j = 0; j < _tiLBase_idx; j++) {
                if(_tiL[i]->_t == _tiLBase[j]->_t) {
                    _toppingSpuit += 3 - abs(_tiLBase[j]->_idx - _tiL[i]->_idx);
                }
            }
        }
        
        for(int i = 0; i < _tiR_idx; i++) {
            for(int j = 0; j < _tiRBase_idx; j++) {
                if(_tiR[i]->_t == _tiRBase[j]->_t) {
                    _toppingSpuit += 3 - abs(_tiRBase[j]->_idx - _tiR[i]->_idx);
                }
            }
        }
        
        _toppingSpuitTotal += MAX(_tiLBase_idx, _tiL_idx) * 3;
        _toppingSpuitTotal += MAX(_tiRBase_idx, _tiR_idx) * 3;
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float toppingSpuit_amount = VBAABBGetAmountAtManyBox(toppingSpuit_aabbIdx, toppingSpuit_aabb);
    
    
    float _toppingSpuitPer = (float)_toppingSpuit / (float)_toppingSpuitTotal;
    _toppingSpuitPer = isnan(_toppingSpuitPer) ? 0 : _toppingSpuitPer;
    cout << "_toppingSpuitPer:" << _toppingSpuitPer << ", _toppingSpuit:" << _toppingSpuit << ", _toppingSpuitTotal:" << _toppingSpuitTotal << "\n";
    
    if(toppingSpuit_aabb)
        free(toppingSpuit_aabb);
    
    
    /*******************toppingFlow***********************/
    cout << "\n";
    cout << "< GetClear toppingFlow >\n";
    
    VBAABB* toppingFlow_aabb = NULL;
    int toppingFlow_aabbIdx = 0;
    
    float _toppingFlow = 0;
    unsigned long _toppingFlowTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        TS_idx* T[0xFF] = {NULL,};
        int Tidx = 0;
        TS_idx* TBase[0xFF] = {NULL,};
        int TBaseidx = 0;
        
        if(_link) {
            for(int i = _link->toppingFlow->len - 1; i > -1 ; i--) {
                bool isHave = false;
                TS_idx* _t = (TS_idx*)_link->toppingFlow->data[i];
                for(int j = 0; j < Tidx; j++) {
                    if(T[j]->_t == _t->_t) {
                        isHave = true;
                        break;
                    }
                }
                if(!isHave) {
                    T[Tidx] = _t;
                    Tidx++;
                }
            }
        }
        
        if(_linkBase) {
            for(int i = _linkBase->toppingFlow->len - 1; i > -1 ; i--) {
                bool isHave = false;
                TS_idx* _t = (TS_idx*)_linkBase->toppingFlow->data[i];
                for(int j = 0; j < TBaseidx; j++) {
                    if(TBase[j]->_t == _t->_t) {
                        isHave = true;
                        break;
                    }
                }
                if(!isHave) {
                    TBase[TBaseidx] = _t;
                    TBaseidx++;
                }
            }
        }
        
        for(int i = 0; i < Tidx; i++)
            toppingFlow_aabb = VBAABBMemResizeAndSet(toppingFlow_aabb, VBAABBShift(T[i]->_aabb, _vec), toppingFlow_aabbIdx, ++toppingFlow_aabbIdx);
        for(int i = 0; i < TBaseidx; i++)
            toppingFlow_aabb = VBAABBMemResizeAndSet(toppingFlow_aabb, VBAABBShift(TBase[i]->_aabb, _vec), toppingFlow_aabbIdx, ++toppingFlow_aabbIdx);
        
        _toppingFlowTotal += MAX(Tidx, TBaseidx) * 2 * 3;
        for(int i = 0; i < Tidx; i++) {
            for(int j = 0; j < TBaseidx; j++) {
                if(T[i]->_t == TBase[j]->_t) {
                    if(i == j) {
                        _toppingFlow += 2 * (3 - abs(TBase[j]->_idx - T[i]->_idx));
                    } else {
                        _toppingFlow += 0.5 * (3 - abs(TBase[j]->_idx - T[i]->_idx));
                    }
                }
            }
        }
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float toppingFlow_amount = VBAABBGetAmountAtManyBox(toppingFlow_aabbIdx, toppingFlow_aabb);
    
    float _toppingFlowPer = (float)_toppingFlow / (float)_toppingFlowTotal;
    _toppingFlowPer = isnan(_toppingFlowPer) ? 0 : _toppingFlowPer;
    cout << "_toppingFlowPer:" << _toppingFlowPer << ", _toppingFlow:" << _toppingFlow << ", _toppingFlowTotal:" << _toppingFlowTotal << "\n";
    
    if(toppingFlow_aabb)
        free(toppingFlow_aabb);
    
    
    /*******************toppingCreamOrCherry***********************/
    cout << "\n";
    cout << "< GetClear toppingCreamOrCherry >\n";
    
    VBAABB* toppingCreamOrCherry_aabb = NULL;
    int toppingCreamOrCherry_aabbIdx = 0;
    
    unsigned long _toppingCreamOrCherry = 0;
    unsigned long _toppingCreamOrCherryTotal = 0;
    
    _link = this;
    _linkBase = baseIceCream;
    
    _vec = VBVector2DCreate(0, 0);
    
    while (_link || _linkBase) {
        int haveCream = 0;
        int haveCherry = 0;
        
        void* cream = NULL;
        void* cherry = NULL;
        void* creamBase = NULL;
        void* cherryBase = NULL;
        
        if(_link) {
            if(_link->toppingCherry) {
                haveCherry = 1;
                cherry = _link->toppingCherry;
                ToppingCherry* _t = (ToppingCherry*)cherry;
                toppingCreamOrCherry_aabb = VBAABBMemResizeAndSet(toppingCreamOrCherry_aabb, VBAABBShift(_t->aabbThumb[_link->toppingCream ? 1 : 0], _vec), toppingCreamOrCherry_aabbIdx, ++toppingCreamOrCherry_aabbIdx);
            }
            if(_link->toppingCream) {
                haveCream = 1;
                cream = _link->toppingCream;
                ToppingCream* _t = (ToppingCream*)cream;
                if(cherry == NULL)
                    toppingCreamOrCherry_aabb = VBAABBMemResizeAndSet(toppingCreamOrCherry_aabb, VBAABBShift(_t->aabbThumb, _vec), toppingCreamOrCherry_aabbIdx, ++toppingCreamOrCherry_aabbIdx);
            }
        }
        
        if(_linkBase) {
            if(_linkBase->toppingCherry) {
                haveCherry = 1;
                cherryBase = _linkBase->toppingCherry;
                ToppingCherry* _t = (ToppingCherry*)cherryBase;
                toppingCreamOrCherry_aabb = VBAABBMemResizeAndSet(toppingCreamOrCherry_aabb, VBAABBShift(_t->aabbThumb[_linkBase->toppingCream ? 1 : 0], _vec), toppingCreamOrCherry_aabbIdx, ++toppingCreamOrCherry_aabbIdx);
            }
            if(_linkBase->toppingCream) {
                haveCream = 1;
                creamBase = _linkBase->toppingCream;
                ToppingCream* _t = (ToppingCream*)creamBase;
                if(cherry == NULL)
                    toppingCreamOrCherry_aabb = VBAABBMemResizeAndSet(toppingCreamOrCherry_aabb, VBAABBShift(_t->aabbThumb, _vec), toppingCreamOrCherry_aabbIdx, ++toppingCreamOrCherry_aabbIdx);
            }
        }
        
        if(cream && creamBase)
            _toppingCreamOrCherry++;
        if(cherry && cherryBase)
            _toppingCreamOrCherry++;
        
        if(haveCream)
            _toppingCreamOrCherryTotal++;
        if(haveCherry)
            _toppingCreamOrCherryTotal++;
        
        _vec = VBVector2DSubtract(_vec, VBVector2DCreate(0, -NEXT_ICECREAM_Y));
        
        if(_link)
            _link = _link->next;
        if(_linkBase)
            _linkBase = _linkBase->next;
    }
    
    float toppingCreamOrCherry_amount = VBAABBGetAmountAtManyBox(toppingCreamOrCherry_aabbIdx, toppingCreamOrCherry_aabb);
    
    float _toppingCreamOrCherryPer = (float)_toppingCreamOrCherry / (float)_toppingCreamOrCherryTotal;
    _toppingCreamOrCherryPer = isnan(_toppingCreamOrCherryPer) ? 0 : _toppingCreamOrCherryPer;
    cout << "_toppingCreamOrCherryPer:" << _toppingCreamOrCherryPer << ", _toppingCreamOrCherry:" << _toppingCreamOrCherry << ", _toppingCreamOrCherryTotal:" << _toppingCreamOrCherryTotal << "\n";
    
    if(toppingCreamOrCherry_aabb)
        free(toppingCreamOrCherry_aabb);
    
    
    
    
    /*******************print***********************/
    cout << "\n";
    int sum = bg_amount + subToppingFlow_amount + subTopping_amount + mask_amount + toppingSpuit_amount + toppingCreamOrCherry_amount;
    cout << "bg_amount::" << bg_amount << ", subToppingFlow_amount:" << subToppingFlow_amount << ", subTopping_amount:" << subTopping_amount << ", mask_amount:" << mask_amount << ", toppingSpuit_amount:" << toppingSpuit_amount << ", toppingFlow_amount:" << toppingFlow_amount << ", toppingCreamOrCherry_amount:" << toppingCreamOrCherry_amount << "\n";
    
    cout << "아이스크림 기본 색상 칼라 일치율:" << _bgPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (bg_amount / sum)) << "%\n";
    cout << "여러개 쌓을수 있는 작은 아이스크림 일치율:" << _subToppingFlowPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (subToppingFlow_amount / sum)) << "%\n";
    cout << "한개만 쌓을수 있는 작은 쿠키 일치율:" << _subToppingPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (subTopping_amount / sum)) << "%\n";
    cout << "마스크 올라간 상태 일치율:" << _maskThumbPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (mask_amount / sum)) << "%\n";
    cout << "눈깔의 일치율:" << _toppingSpuitPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (toppingSpuit_amount / sum)) << "%\n";
    cout << "뿌리는 토핑가루의 일치율:" << _toppingFlowPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (toppingFlow_amount / sum)) << "%\n";
    cout << "크림과 체리의 일치율:" << _toppingCreamOrCherryPer * 100 << "%, 해답영역+현재아이스크림에서의 영역비율:" << (100 * (toppingCreamOrCherry_amount / sum)) << "%\n";
    
    cout << "\n";
    
    float totalPer = (_bgPer * (bg_amount / sum) + 
                      _subToppingFlowPer * (subToppingFlow_amount / sum) + 
                      _subToppingPer * (subTopping_amount / sum) + 
                      _maskThumbPer * (mask_amount / sum) + 
                      _toppingSpuitPer * (toppingSpuit_amount / sum) + 
                      _toppingFlowPer * (toppingFlow_amount / sum) + 
                      _toppingCreamOrCherryPer * (toppingCreamOrCherry_amount / sum)) * 100;
    cout << "전체 일치율 " << totalPer << "%\n";
    
    return totalPer;
}