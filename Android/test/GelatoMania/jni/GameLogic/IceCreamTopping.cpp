#include "IceCream.h"

void IceCream::AddToppingSpuit(ToppingSpuit* _ts) {
    if(next) {
        next->AddToppingSpuit(_ts);
    } else {
        int _l_count = 0;
        int _r_count = 0;
        for(int i = 0; i < toppingSpuitL->len; i++) {
            if(((TS_idx*)VBArrayVectorGetDataAt(toppingSpuitL, i))->_t == _ts) {
                _l_count++;
            }
        }
        for(int i = 0; i < toppingSpuitR->len; i++) {
            if(((TS_idx*)VBArrayVectorGetDataAt(toppingSpuitR, i))->_t == _ts) {
                _r_count++;
            }
        }
        int _idx = _l_count + _r_count;
        if(_idx < _ts->len) {
            VBAABB _aabb = _ts->aabbThumb[_idx];
            VBArrayVectorAddBack(thumbs, ThumbsInit(_ts->texThumb[_idx], _aabb, 0, _ts, false));
            TS_idx* _ti = (TS_idx*)malloc(sizeof(TS_idx));
            _ti->_t = _ts;
            _ti->_idx = _idx;
            _ti->_aabb = _aabb;
            if(_idx % 2) {
                VBArrayVectorAddBack(toppingSpuitR, _ti);
            } else {
                VBArrayVectorAddBack(toppingSpuitL, _ti);
            }
        }
    }
}

void IceCream::AddToppingFlow(ToppingFlow* _tf) {
    if(next) {
        next->AddToppingFlow(_tf);
    } else {
        int _rs_count = 0;
        for(int i = 0; i < toppingFlow->len; i++) {
            if(((TS_idx*)VBArrayVectorGetDataAt(toppingFlow, i))->_t == _tf) {
                _rs_count++;
            }
        }
        if(_rs_count < _tf->len) {
            VBArrayVectorAddBack(thumbs, ThumbsInit(_tf->texThumb[_rs_count], _tf->aabbThumb[_rs_count], 1, _tf, false));
            TS_idx* _ti = (TS_idx*)malloc(sizeof(TS_idx));
            _ti->_t = (void*)_tf;
            _ti->_idx = _rs_count;
            _ti->_aabb = _tf->aabbThumb[_rs_count];
            VBArrayVectorAddBack(toppingFlow, _ti);
        }
    }
}

void IceCream::AddToppingCream(ToppingCream* _tc) {
    if(next) {
        next->AddToppingCream(_tc);
    } else {
        int _rs_count = 0;
        int _t_count = 0;
        for(int i = 0; i < thumbs->len; i++) {
            Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
            if(_t->targ == _tc) {
                _rs_count++;
            }
            if(_t->isR == false && _t->type == 3) {
                _t_count++;
            }
        }
        if(_rs_count < 1 && _t_count == 0) {
            VBArrayVectorAddBack(thumbs, ThumbsInit(_tc->texThumb, _tc->aabbThumb, 2, _tc, false));
            toppingCream = _tc;
        }
    }
}

void IceCream::AddToppingCherry(ToppingCherry* _tc) {
    if(next) {
        AddToppingCherry(_tc);
    } else {
        int _rs_count = 0;
        int _t_count = 0;
        Thumbs* _tt = NULL;
        for(int i = 0; i < thumbs->len; i++) {
            Thumbs* _t = (Thumbs*)VBArrayVectorGetDataAt(thumbs, i);
            if(_t->targ == _tc) {
                _rs_count++;
            }
            if(_t->isR == false && _t->type == 2) {
                _tt = _t;
                _t_count++;
            }
        }
        if(_rs_count == 0) {
            if(_t_count > 0 && _tt) {
                if(getChildren()) {
                    if(getChildren()->indexOfObject(_tt->model) != UINT_MAX)
                        removeChild(_tt->model, false);
                }
                VBArrayVectorRemove(thumbs, _tt);
                ThumbsFree(&_tt);
            }
            VBArrayVectorAddBack(thumbs, ThumbsInit(_tc->texThumb[_t_count], _tc->aabbThumb[_t_count], 3, _tc, false));
            toppingCherry = _tc;
        }
    }
}

bool IceCream::AddTopping(int _topping) {
    if(next)
        return next->AddTopping(_topping);
    else {
        RT* _rtF = NULL;
        for(int i = 0; i < VBArrayVectorGetLength(tdVec); i++) {
            RT* _rt = (RT*)VBArrayVectorGetDataAt(tdVec, i);
            if(_rt->idx == _topping) {
                _rtF = _rt;
                break;
            }
        }
        
        if(_rtF) {
            switch(_rtF->type) {
                case 0:
                {
                    ToppingSpuit* _ts = (ToppingSpuit*)_rtF->data;
                    AddToppingSpuit(_ts);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 1: 
                {
                    ToppingFlow* _tf = (ToppingFlow*)_rtF->data;
                    AddToppingFlow(_tf);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 2: 
                {
                    ToppingCream* _tc = (ToppingCream*)_rtF->data;
                    AddToppingCream(_tc);
                    need_update_model = true;
                    Reshape();
                }
                    break;
                case 3: 
                {
                    ToppingCherry* _tch = (ToppingCherry*)_rtF->data;
                    AddToppingCherry(_tch);
                    need_update_model = true;
                    Reshape();
                }
                    break;
            }
        }
        return true;
    }
}

bool IceCream::IsPossibleTopping(int _topping) {
    if(next) {
        return next->IsPossibleTopping(_topping);
    } else {
        
        RT* _rtF = NULL;
        for(int i = 0; i < VBArrayVectorGetLength(tdVec); i++) {
            RT* _rt = (RT*)VBArrayVectorGetDataAt(tdVec, i);
            if(_rt->idx == _topping) {
                _rtF = _rt;
                break;
            }
        }
        
        if(_rtF) {
            switch(_rtF->type) {
                case 0:
                {
                }
                    break;
                case 1:
                {
                }
                    break;
                case 2:
                {
                }
                    break;
                case 3:
                {
                }
                    break;
            }
        }
        
        return true;
    }
}