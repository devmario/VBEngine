#include "VBQuadtree.h"
#include "../IO/VBSystem.h"
#include "../VBEngine.h"

VBQuadtree* VBQuadtreeAlloc(void) {
    VBQuadtree* _quadtree = VBSystemCalloc(1, sizeof(VBQuadtree));
    return _quadtree;
}

VBQuadtree* VBQuadtreeInit(VBQuadtree* _quadtree, VBQuadtreeIsSlice _is_slice, VBQuadtreeIsApear _is_apear, void* _reference, VBFloat _max_size, VBFloat _min_size) {
    if(_quadtree->child) {
        VBQuadtreeFree(&_quadtree->child[0]);
        VBQuadtreeFree(&_quadtree->child[1]);
        VBQuadtreeFree(&_quadtree->child[2]);
        VBQuadtreeFree(&_quadtree->child[3]);
        VBSystemFree(_quadtree->child);
        _quadtree->child = VBNull;
    }
    
    _quadtree->has_child = VBFalse;
    _quadtree->x = 0.0f;
    _quadtree->y = 0.0f;
    
    _quadtree->reference = _reference;
    _quadtree->is_slice = _is_slice;
    _quadtree->is_apear = _is_apear;
    _quadtree->max_size = _max_size;
    _quadtree->size = _max_size;
    _quadtree->width = _quadtree->size;
    _quadtree->height = _quadtree->size;
    _quadtree->min_size = _min_size;
    
    return _quadtree;
}

void VBQuadtreeSlice(VBQuadtree* _quadtree) {
    if(_quadtree->size > _quadtree->min_size) {
        if(_quadtree->is_slice(_quadtree)) {
            _quadtree->has_child = VBTrue;
            
            _quadtree->child = VBSystemCalloc(4, sizeof(VBQuadtree*));
            
            VBFloat half_size = _quadtree->size * 0.5;
            VBFloat half_size_half = half_size * 0.5;
            VBFloat half_x_size = _quadtree->x + half_size;
            VBFloat half_y_size = _quadtree->y + half_size;
            
            _quadtree->child[0] = VBQuadtreeInit(VBQuadtreeAlloc(), _quadtree->is_slice, _quadtree->is_apear, _quadtree->reference, _quadtree->max_size, _quadtree->min_size);
            _quadtree->child[0]->size = half_size;
            _quadtree->child[0]->width = _quadtree->child[0]->height = _quadtree->child[0]->size;
            _quadtree->child[0]->x = _quadtree->x;
            _quadtree->child[0]->y = _quadtree->y;
            _quadtree->child[0]->center_x = _quadtree->child[0]->x + half_size_half;
            _quadtree->child[0]->center_y = _quadtree->child[0]->y + half_size_half;
            _quadtree->child[0]->is_apear(_quadtree->child[0], VBTrue);
            VBQuadtreeSlice(_quadtree->child[0]);
            
            _quadtree->child[1] = VBQuadtreeInit(VBQuadtreeAlloc(), _quadtree->is_slice, _quadtree->is_apear, _quadtree->reference, _quadtree->max_size, _quadtree->min_size);
            _quadtree->child[1]->size = half_size;
            _quadtree->child[1]->width = _quadtree->child[1]->height = _quadtree->child[1]->size;
            _quadtree->child[1]->x = half_x_size;
            _quadtree->child[1]->y = _quadtree->y;
            _quadtree->child[1]->center_x = _quadtree->child[1]->x + half_size_half;
            _quadtree->child[1]->center_y = _quadtree->child[1]->y + half_size_half;
            _quadtree->child[1]->is_apear(_quadtree->child[1], VBTrue);
            VBQuadtreeSlice(_quadtree->child[1]);
            
            _quadtree->child[2] = VBQuadtreeInit(VBQuadtreeAlloc(), _quadtree->is_slice, _quadtree->is_apear, _quadtree->reference, _quadtree->max_size, _quadtree->min_size);
            _quadtree->child[2]->size = half_size;
            _quadtree->child[2]->width = _quadtree->child[2]->height = _quadtree->child[2]->size;
            _quadtree->child[2]->x = _quadtree->x;
            _quadtree->child[2]->y = half_y_size;
            _quadtree->child[2]->center_x = _quadtree->child[2]->x + half_size_half;
            _quadtree->child[2]->center_y = _quadtree->child[2]->y + half_size_half;
            _quadtree->child[2]->is_apear(_quadtree->child[2], VBTrue);
            VBQuadtreeSlice(_quadtree->child[2]);
            
            _quadtree->child[3] = VBQuadtreeInit(VBQuadtreeAlloc(), _quadtree->is_slice, _quadtree->is_apear, _quadtree->reference, _quadtree->max_size, _quadtree->min_size);
            _quadtree->child[3]->size = half_size;
            _quadtree->child[3]->width = _quadtree->child[3]->height = _quadtree->child[3]->size;
            _quadtree->child[3]->x = half_x_size;
            _quadtree->child[3]->y = half_y_size;
            _quadtree->child[3]->center_x = _quadtree->child[3]->x + half_size_half;
            _quadtree->child[3]->center_y = _quadtree->child[3]->y + half_size_half;
            _quadtree->child[3]->is_apear(_quadtree->child[3], VBTrue);
            VBQuadtreeSlice(_quadtree->child[3]);
        }
    }
}

void VBQuadtreeFree(VBQuadtree** _quadtree) {
    (*_quadtree)->is_apear(*_quadtree, VBFalse);
    VBQuadtreeInit(*_quadtree, VBNull, VBNull, VBNull, 0.0f, 0.0f);
    VBSystemFree(*_quadtree);
    *_quadtree = VBNull;
}
