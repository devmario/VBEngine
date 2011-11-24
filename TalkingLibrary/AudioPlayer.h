#ifndef __AudioPlayer_H__
#define __AudioPlayer_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include <stdbool.h>
#include <AudioToolbox/AudioToolbox.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioUnit/AudioComponent.h>
#include <AudioToolbox/AudioQueue.h>
	
	typedef struct AudioPlayer AudioPlayer;
	
	struct AudioPlayer {
		char* path;
		FILE* file;
		
		void* userReference;
		void (*eventEnded)(void* userReference);
		void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower);
		void (*eventOutput)(void* userReference, unsigned long inputDataLength, signed long* inputData);
		
		void* ptr;
		
		bool isPlaying;
		
		//채널
		unsigned long channelNum;
		
		AudioStreamBasicDescription outputFormat;
	};
	
	AudioPlayer* AudioPlayerInit(const char* path, void* userReference, 
								 void (*eventEnded)(void* userReference),
								 void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower),
								 void (*eventOutput)(void* userReference, unsigned long inputDataLength, signed long* inputData));
	void AudioPlayerFree(AudioPlayer** player);
	
    void AudioPlayerSetIsAwake(AudioPlayer* player, bool isAwake);
	bool AudioPlayerStart(AudioPlayer* player, AudioStreamBasicDescription outputFormat, float queueRenderSecond);
	bool AudioPlayerStop(AudioPlayer* player);
	
#ifdef __cplusplus
}
#endif

#endif