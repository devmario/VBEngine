#include "VBModel.h"
#include "OverlapTester.h"

bool VBModel::IsHitByPoint(CCPoint pos, bool _recursion) {
    if(is_bitmap) {
        CCPoint _pos = pos;
        if(CCDirector::sharedDirector()->isRetinaDisplay()) {
            float scale = CCDirector::sharedDirector()->getDisplaySizeInPixels().height / 320;
            _pos.x *=  scale;
            _pos.y *=  scale;
        }
        CCAffineTransform wt = nodeToWorldTransform();
        CCPoint tl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y), wt);
        CCPoint tr = CCPointApplyAffineTransform(CCPointMake(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y), wt);
        CCPoint bl = CCPointApplyAffineTransform(CCPointMake(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y), wt);
        CCPoint br = CCPointApplyAffineTransform(CCPointMake(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y), wt);
        
        if(CheckTriangle(tl, tr, bl, _pos))
            return true;
        if(CheckTriangle(bl, tr, br, _pos))
            return true;
    }
    if(_recursion) {
        if(getChildren()) {
            for(int i = 0; i < getChildren()->count(); i++) {
                if(((VBModel*)getChildren()->objectAtIndex(i))->IsHitByPoint(pos, _recursion))
                    return true;
            }
        }
    }
    return false;
}

bool VBModel::IsHit(VBModel* _model_tester, bool _recursion) {
    int vertIdx = 0;
    int remain = -1;
    
    while(remain < 0) {
        CCPoint vert[4];
        double p[4][2];
        remain = GetVertex(vertIdx, vert, _recursion);
        vertIdx++;
        if(remain > -1)
            break;
        
        for(int i = 0; i < 4; i++) {
            p[i][0] = (double)vert[i].x;
            p[i][1] = (double)vert[i].y;
        }
        
        int vertIdx_model_tester = 0;
        int remain_model_tester = -1;
        
        while(remain_model_tester < 0) {
            CCPoint vert_model_tester[4];
            double p_model_tester[4][2];
            remain_model_tester = _model_tester->GetVertex(vertIdx_model_tester, vert_model_tester, _recursion);
            vertIdx_model_tester++;
            if(remain_model_tester > -1)
                break;
            
            for(int i = 0; i < 4; i++) {
                p_model_tester[i][0] = (double)vert_model_tester[i].x;
                p_model_tester[i][1] = (double)vert_model_tester[i].y;
            }
            
            if(tri_tri_overlap_test_2d(p[0], p[1], p[2], p_model_tester[0], p_model_tester[1], p_model_tester[2])) {
                return true;
            }
            if(tri_tri_overlap_test_2d(p[0], p[1], p[2], p_model_tester[2], p_model_tester[1], p_model_tester[3])) {
                return true;
            }
            if(tri_tri_overlap_test_2d(p[2], p[1], p[3], p_model_tester[0], p_model_tester[1], p_model_tester[2])) {
                return true;
            }
            if(tri_tri_overlap_test_2d(p[2], p[1], p[3], p_model_tester[2], p_model_tester[1], p_model_tester[3])) {
                return true;
            }
        }
    }
    return false;
}