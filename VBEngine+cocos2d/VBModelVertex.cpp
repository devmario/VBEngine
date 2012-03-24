#include "VBModel.h"

VBAABB VBModel::GetAABB(bool _recursion) {
    VBAABB _aabb = VBAABBLoadIndentity();
    if(is_bitmap) {
        CCAffineTransform wt;
        
        wt = nodeToWorldTransform();
        
        CCPoint tl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y), wt);
        CCPoint tr = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y), wt);
        CCPoint bl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y), wt);
        CCPoint br = CCPointApplyAffineTransform(CCPointMake(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y), wt);
        VBVector2D vtx[4] = {{tl.x,tl.y}, {tr.x,tr.y}, {bl.x,bl.y}, {br.x,br.y}};
        _aabb = VBAABBMerge(_aabb, VBAABBCreateWithVertex(vtx, 4));
    }
    if(_recursion) {
        if(getChildren()) {
            for(int i = 0; i < getChildren()->count(); i++) {
                _aabb = VBAABBMerge(_aabb, ((VBModel*)getChildren()->objectAtIndex(i))->GetAABB());
            }
        }
    }
    return _aabb;
}

int VBModel::GetVertex(int _idx, CCPoint* _vertex, bool _recursion) {
    if(is_bitmap) {
        if(_idx == 0) {
            CCAffineTransform wt = nodeToWorldTransform();
            CCPoint tl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y), wt);
            CCPoint tr = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y), wt);
            CCPoint bl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y), wt);
            CCPoint br = CCPointApplyAffineTransform(CCPointMake(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y), wt);
            _vertex[0] = tl;
            _vertex[1] = tr;
            _vertex[2] = bl;
            _vertex[3] = br;
            
            //성공시 -1 리턴
            return -1;
        }
        _idx--;
    }
    
    if(_recursion) {
        if(getChildren()) {
            for(int i = 0; i < getChildren()->count(); i++) {
                int _subIdx = ((VBModel*)getChildren()->objectAtIndex(i))->GetVertex(_idx, _vertex);
                if(_subIdx < 0)
                    return _subIdx;
                else
                    _idx -= (_idx - _subIdx);
            }
        }
    }
    
    //실패시 그냥 리턴
    return _idx;
}

float VBModel::GetWidth(bool _recursion) {
    return VBAABBGetWidth(GetAABB(_recursion));
}

float VBModel::GetHeight(bool _recursion) {
    return VBAABBGetHeight(GetAABB(_recursion));
}
