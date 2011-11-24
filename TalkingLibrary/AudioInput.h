#ifndef __AudioInput_H__
#define __AudioInput_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
#include <AudioToolbox/AudioToolbox.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioUnit/AudioComponent.h>
#include <AudioToolbox/AudioQueue.h>
	
	enum {
		AudioInputRouteType_NotFound				=	0x00,
		AudioInputRouteType_HeadsetInOut			=	0x01,
		AudioInputRouteType_SpeakerAndMicrophone	=	0x02,
		AudioInputRouteType_HeadphonesAndMicrophone	=	0x03
	};
	typedef unsigned char AudioInputRouteType;
	
	typedef struct AudioInput AudioInput;
	
	struct AudioInput {
        
		//오디오장치 감시자 초기화 여부
		bool initedAUsession;
		
		//레코드 중인가의 여부
		bool isRecording;
		//한번 업력큐 진행할때의 데이터 사이즈(초로 표현)
		float second;
		
		//콜백 유저 참조 포인터
		void* userReference;
		//입력 콜백
		void (*eventInput)(void* userReference, unsigned long inputDataLength, signed long* inputData);
		//입력이 어떤이유에서 종료되었을때 콜백
		void (*eventInterrupt)(void* userReference);
		//입력라우터가 변경시 콜백
		void (*eventRouteChange)(void* userReference, AudioInputRouteType oldRoute, AudioInputRouteType newRoute);
		//입력의 가능여부 변경시 콜백
		void (*eventAvailable)(void* userReference, bool isAvailable);
		//입력성량 콜백
		void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower);
		
		//채널
		unsigned long channelNum;
		
		AudioStreamBasicDescription recordFormat;
		
		//private
		void* privatePtr;
	};
	
	AudioInput* AudioInputInit(void* userReference, 
							   void (*eventInput)(void* userReference, unsigned long inputDataLength, signed long* inputData),
							   void (*eventInterrupt)(void* userReference),
							   void (*eventRouteChange)(void* userReference, AudioInputRouteType oldRoute, AudioInputRouteType newRoute),
							   void (*eventAvailable)(void* userReference, bool isAvailable),
							   void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower));
	void AudioInputFree(AudioInput** input);
    
    
    void AudioInputSetIsAwake(AudioInput* input, bool isAwake);
	
	bool AudioInputStart(AudioInput* input, float second);
	bool AudioInputStop(AudioInput* input);
	
#ifdef __cplusplus
}
#endif

#endif