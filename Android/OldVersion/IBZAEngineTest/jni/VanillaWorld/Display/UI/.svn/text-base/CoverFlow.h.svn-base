#ifndef __COVER_FLOW_H__
#define __COVER_FLOW_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
#include "../Object/Model.h"
	
	typedef struct CoverFlow CoverFlow;
	
	typedef struct CoverFlowEvent CoverFlowEvent;
	
	typedef struct {
		//데이터 관련
		short index;			//인덱스
		void* data;						//표시해줄 데이터
		bool selected;					//상태

		//개발자가 접근하여 사용하는 데이터
		void* userReference;			//동적으로 생성할 메모리 포인터
		
		//디스플레이 관련
		Model bundle;
		Model model;					//model
		Vector3D hitVertex[4];			//충돌
		
		//이벤트 관련
		void* touchID;					//터치 ID
		void* parentCoverFlow;			//coverFlow 타겟
		
		float x, z, angle;
	} Cover;
	
	struct CoverFlowEvent {
		void* userReference;
		void (*selectEvent)(Cover* cover, void* data);
		void (*addEvent)(Cover* cover, void* data);
		void (*removeEvent)(Cover* cover, void* data);
	};
	
	struct CoverFlow {
		Model model;
		Array* data;
		CoverFlowEvent event;
		
		unsigned short width;
		unsigned short height;
		
		unsigned char visibleCoverLength;
		Array visibleCovers;
		
		Vector3D coverFlowHitVertex[4];
		
		void* touchID;
		float force;
		float x;
		float preTouchX;
		float touchX;
		float stepTouchX;
		
		int selectedIndex;
	};
	
	CoverFlowEvent CoverFlowEventInit(void* userReference,
									  void (*selectEvent)(Cover* cover, void* data),
									  void (*addEvent)(Cover* cover, void* data),
									  void (*removeEvent)(Cover* cover, void* data));
	
	bool CoverFlowInit(CoverFlow* coverFlow, Array* data, CoverFlowEvent event,
					   unsigned short width, unsigned short height, unsigned char visibleCoverLength);
	bool CoverFlowFree(CoverFlow* coverFlow);
	void CoverFlowUpdate(CoverFlow* coverFlow);
	
#ifdef __cplusplus
}
#endif

#endif
