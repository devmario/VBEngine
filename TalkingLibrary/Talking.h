#ifndef __Talking_H__
#define __Talking_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include <stdbool.h>
	
	enum {
		TalkingRouteType_NotFound					=	0x00,
		TalkingRouteType_HeadsetInOut				=	0x01,
		TalkingRouteType_SpeakerAndMicrophone		=	0x02,
		TalkingRouteType_HeadphonesAndMicrophone	=	0x03
	};
	typedef unsigned char TalkingRouteType;
	
	typedef struct TalkingEvent TalkingEvent;
	typedef struct Talking Talking;
	
	//이벤트
	struct TalkingEvent {
		//소스 사용자들을 위한 리퍼런스
		void* userReference;
		//미터데이터 콜백(녹음시)
		void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower);
		//이퀄라이저 데이터 콜백(플레이시 및 녹음시)
		void (*eventEqualizer)(void* userReference, unsigned long dataLength, float* data);
		//녹음 시작을 알리는 콜백
		void (*eventStartTalking)(void* userReference);
		//녹음 종료를 알리는 콜백
		void (*eventEndTalking)(void* userReference);
		//출력 데이터 변형을 위한 콜백(실시간 변형이기 때문에 속도는 느리지 않지만 전체적인 변형이 되지 않는다)
		void (*eventExtensionTalking)(void* userReference, unsigned long* inputDataLength, signed long** inputData);
		//플레이전에 녹음된 파일경로 리턴(녹음 데이터의 전체적인 변형을 위해:플레이 전에 하기때문에 약간 중간에 텀이 있을수 있음)
		void (*eventExtensionFilePathTalking)(void* userReference, char* recordFilePath);
		//녹음파일 플레이시 리턴
		void (*eventPlayTalking)(void* userReference);
		//녹음파일 플레이 종료시 리턴
		void (*eventPlayEndedTalking)(void* userReference);
		//어떤이유에서 입력이 중단되었을때
		void (*eventInputEventInterrupt)(void* userReference);
		//입력하는 방식이 바뀌었을때
		void (*eventInputEventRouteChange)(void* userReference, TalkingRouteType oldRoute, TalkingRouteType newRoute);
		//입력의 가능여부가 바뀔때
		void (*eventInputEventAvailable)(void* userReference, bool isAvailable);
	};
	
	//이벤트 생성
	TalkingEvent TalkingEventInit(void* userReference,
								  void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower),
								  void (*eventEqualizer)(void* userReference, unsigned long dataLength, float* data),
								  void (*eventStartTalking)(void* userReference),
								  void (*eventEndTalking)(void* userReference),
								  void (*eventExtensionTalking)(void* userReference, unsigned long* inputDataLength, signed long** inputData),
								  void (*eventExtensionFilePathTalking)(void* userReference, char* recordFilePath),
								  void (*eventPlayTalking)(void* userReference),
								  void (*eventPlayEndedTalking)(void* userReference),
								  void (*eventInputEventInterrupt)(void* userReference),
								  void (*eventInputEventRouteChange)(void* userReference, TalkingRouteType oldRoute, TalkingRouteType newRoute),
								  void (*eventInputEventAvailable)(void* userReference, bool isAvailable));
	
	//Talking의 상태
	enum {
		//녹음 대기 상태
		TalkingStatus_Record_Waiting	=	1,
		//녹음상태
		TalkingStatus_Recording			=	2,
		//플레이 준비상태
		TalkingStatus_Play_Ready		=	3,
		//플레이상태
		TalkingStatus_Play				=	4,
		//플레이 종료상태(초기상태)
		TalkingStatus_Play_Ended		=	0,
	};
	typedef unsigned char TalkingStatus;
	
	//Talking
	struct Talking {
		//상태
		TalkingStatus status;
		//녹음 파일 경로
		char* recordPath;
		//이퀄라이징 사이즈
		unsigned int equalizerSize;
		//녹음시작불륨 타입1:0.0이면 사용안함
		float recordStartVolumePower;
		//녹음시작불륨 타입2:0.0이면 사용안함
		float recordStartVolumeAverage;
		//녹음종료불륨 타입1:0.0이면 사용안함
		float recordEndVolumePower;
		//녹음종료불륨 타입2:0.0이면 사용안함
		float recordEndVolumeAverage;
		//최대 녹음시간(1.0 == 1second)
		float recordMaxTime;
		//오디오핏치(빠르기)
		float pitch;
		//이벤트
		TalkingEvent event;
		//private
		void* ptr;
	};
	
	//생성
	Talking* TalkingInit(const char* recordPath, TalkingEvent event, unsigned int equalizerSize,
						 float recordStartVolumePower, float recordEndVolumePower,
						 float recordStartVolumeAverage, float recordEndVolumeAverage,
						 float recordMaxTime, float pitch);
	//해제
	void TalkingFree(Talking** talking);
	
	//녹음 시작(리턴:play중이면 false리턴되고 녹음대기에 들어가지 않음)
	bool TalkingRecord(Talking* talking);
	//녹음된 파일 플레이(리턴:record 대기중이거나 record중이면 false리턴되고 플레이하지 않음)
	bool TalkingPlay(Talking* talking);
    
    void TalkingSetIsAwake(Talking* talking, bool isAwake);
	
#ifdef __cplusplus
}
#endif

#endif