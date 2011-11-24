#include "AudioPlayer.h"
#include <stdlib.h>
#include <string.h>

#define AudioOutputBufferSize 3
typedef struct {
	AudioQueueLevelMeterState* meter;
	
	AudioQueueRef queue;
	AudioQueueBufferRef buffers[AudioOutputBufferSize];
	
	int bufSize;
} AudioOutputQueue;

void AudioOutputBufferHandler(void* inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer) {
	AudioPlayer* player = (AudioPlayer*)inUserData;
	AudioOutputQueue* outputQueue = player->ptr;
	
	inBuffer->mAudioDataByteSize = fread(inBuffer->mAudioData, 1, outputQueue->bufSize, player->file);
	
	if(inBuffer->mAudioDataByteSize < outputQueue->bufSize) {
		AudioPlayerStop(player);
	} else {
		UInt32 data_sz = sizeof(AudioQueueLevelMeterState) * player->channelNum;
		AudioQueueGetProperty(outputQueue->queue, kAudioQueueProperty_CurrentLevelMeterDB, outputQueue->meter, &data_sz);
		float* avrPower = calloc(player->channelNum, sizeof(float));
		float* peakPower = calloc(player->channelNum, sizeof(float));
		int i;
		for(i = 0; i < player->channelNum; i++) {
			avrPower[i] = outputQueue->meter[i].mAveragePower;
			peakPower[i] = outputQueue->meter[i].mPeakPower;
		}
		player->eventMeter(player->userReference, player->channelNum, avrPower, peakPower);
		free(avrPower);
		free(peakPower);
		
		player->eventOutput(player->userReference, (unsigned long)inBuffer->mAudioDataByteSize, (signed long*)inBuffer->mAudioData);
		
		AudioQueueEnqueueBuffer(inAQ, inBuffer, 0, NULL);
	}
}

int AudioOutputComputeRecordBufferSize(AudioPlayer* player, const AudioStreamBasicDescription *format, float seconds) {
	AudioOutputQueue* outputQueue = player->ptr;
	
	int packets, frames, bytes = 0;
	frames = (int)ceil(seconds * format->mSampleRate);
	
	if(format->mBytesPerFrame > 0) {
		bytes = frames * format->mBytesPerFrame;
	} else {
		UInt32 maxPacketSize;
		if(format->mBytesPerPacket > 0) {
			maxPacketSize = format->mBytesPerPacket;
		} else {
			UInt32 propertySize = sizeof(maxPacketSize);
			AudioQueueGetProperty(outputQueue->queue, kAudioQueueProperty_MaximumOutputPacketSize, &maxPacketSize, &propertySize);
		}
		if(format->mFramesPerPacket > 0) {
			packets = frames / format->mFramesPerPacket;
		} else {
			packets = frames;
		}
		if(packets == 0) {
			packets = 1;
		}
		bytes = packets * maxPacketSize;
	}
	return bytes;
}

AudioPlayer* AudioPlayerInit(const char* path, void* userReference, void (*eventEnded)(void* userReference),
							 void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower),
							 void (*eventOutput)(void* userReference, unsigned long inputDataLength, signed long* inputData)) {
	AudioPlayer* player = calloc(1, sizeof(AudioPlayer));
	player->path = calloc(strlen(path) + 1, sizeof(char));
	sprintf(player->path, "%s", path);
	player->userReference = userReference;
	player->eventEnded = eventEnded;
	player->eventMeter = eventMeter;
	player->eventOutput = eventOutput;
	
	return player;
}

void AudioPlayerFree(AudioPlayer** player) {
	AudioPlayerStop(*player);
	free((*player)->path);
	(*player)->path = NULL;
	
	free(*player);
	*player = NULL;
}

bool AudioPlayerStart(AudioPlayer* player, AudioStreamBasicDescription outputFormat, float queueRenderSecond) {
	if(!player->isPlaying) {
		player->isPlaying = true;
		
		player->file = fopen(player->path, "rb");
		
		player->ptr = calloc(1, sizeof(AudioOutputQueue));
		AudioOutputQueue* outputQueue = player->ptr;
		
		player->outputFormat = outputFormat;
		AudioQueueNewOutput(&player->outputFormat, AudioOutputBufferHandler, player, NULL, NULL, 0, &outputQueue->queue);
		
		//채널
		player->channelNum = player->outputFormat.mChannelsPerFrame;
		
		//미터(성량)
		outputQueue->meter = (AudioQueueLevelMeterState*)calloc(player->channelNum, sizeof(AudioQueueLevelMeterState));
		UInt32 val = 1;
		AudioQueueSetProperty(outputQueue->queue, kAudioQueueProperty_EnableLevelMetering, &val, sizeof(UInt32));
		
		//사이즈 계산해서 큐 메모리 잡기
		outputQueue->bufSize = AudioOutputComputeRecordBufferSize(player, &player->outputFormat, queueRenderSecond);
		for(int i = 0; i < AudioOutputBufferSize; ++i) {
			AudioQueueAllocateBuffer(outputQueue->queue, outputQueue->bufSize, &outputQueue->buffers[i]);
			AudioOutputBufferHandler(player, outputQueue->queue, outputQueue->buffers[i]);
		}
		AudioQueueSetParameter(outputQueue->queue, kAudioQueueParam_Volume, 1.0);
		
		//큐시작
		AudioQueueStart(outputQueue->queue, NULL);
				
		return true;
	} else {
		return false;
	}
}

void AudioPlayerSetIsAwake(AudioPlayer* player, bool isAwake) {
    AudioOutputQueue* outputQueue = player->ptr;
    if(isAwake) {
		AudioQueueStart(outputQueue->queue, NULL);
    } else {
        AudioQueuePause(outputQueue->queue);
    }
}

bool AudioPlayerStop(AudioPlayer* player) {
	if(player->isPlaying) {
		player->isPlaying = false;
		
		AudioOutputQueue* outputQueue = player->ptr;
		
		//큐중단
		AudioQueueStop(outputQueue->queue, true);
		
		//큐메모리 삭제
		for(int i = 0; i < AudioOutputBufferSize; ++i) {
			AudioQueueFreeBuffer(outputQueue->queue, outputQueue->buffers[i]);
		}
		
		//미터 삭제
		if(outputQueue->meter) {
			free(outputQueue->meter);
			outputQueue->meter = NULL;
		}
		
		//큐삭제
		AudioQueueDispose(outputQueue->queue, true);
		
		free(outputQueue);
		outputQueue = NULL;
		
		fclose(player->file);
		
		player->eventEnded(player->userReference);
		
		return true;
	} else {
		return false;
	}
}

#undef AudioOutputBufferSize