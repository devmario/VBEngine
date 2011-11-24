

src
	프로젝트에 추가되는 에니메이션 렌더링 엔진 소스코드
VBPhotoshopPlugIn
	포토샵 플러그 인
VBFlashPlugIn
	플래쉬 플러그인
VBPlugInScript
	포토샵과 플래쉬의 데이터 뽑는 스크립트
VBEngine+cocos2D
	cocos2d를 쓸경우 추가
	VBModel클래스를 사용(CCSprite상속)
cocos2d
	마지막으로 테스트한 cocos2d CPP버전


프로젝트셋팅에 추가
	코코스2D를 쓸경우
		HEADER_SEARCH_PATHS
			cocos2d/cocos2dx
			cocos2d/CocosDenshion/include
			$(SDKROOT)/usr/include/libxml2
	코코스2D를 쓰지 않을 경우
		IPHONE_OPTIMIZE_OPTIONS
			-skip-PNGs

