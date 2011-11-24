#include "AudioInput.h"

#define AudioInputBufferSize 3
typedef struct {
	AudioQueueLevelMeterState* meter;
	
	AudioQueueRef queue;
	AudioQueueBufferRef buffers[AudioInputBufferSize];
} AudioInputQueue;

//오디오 입력 중단 리스너
void AudioInputInterruptionListener(void* inClientData, UInt32 inInterruptionState) {
	AudioInput* input = (AudioInput*)inClientData;
	if(inInterruptionState == kAudioSessionBeginInterruption) {
		//종료콜백
		input->eventInterrupt(input->userReference);
	}
}

//오디오 입력 변경 리스너
void AudioInputPropertyListener(void* inClientData, AudioSessionPropertyID inID, UInt32 inDataSize, const void* inData) {
	AudioInput* input = (AudioInput*)inClientData;
	if(inID == kAudioSessionProperty_AudioRouteChange) {
		CFDictionaryRef routeDictionary = (CFDictionaryRef)inData;			
		CFShow(routeDictionary);
		CFNumberRef reason = (CFNumberRef)CFDictionaryGetValue(routeDictionary, CFSTR(kAudioSession_AudioRouteChangeKey_Reason));
		SInt32 reasonVal;
		CFNumberGetValue(reason, kCFNumberSInt32Type, &reasonVal);
		if(reasonVal != kAudioSessionRouteChangeReason_CategoryChange) {
			AudioInputRouteType old = AudioInputRouteType_NotFound;
			AudioInputRouteType new = AudioInputRouteType_NotFound;
			
			CFStringRef oldRoute = (CFStringRef)CFDictionaryGetValue(routeDictionary, CFSTR(kAudioSession_AudioRouteChangeKey_OldRoute));
			if(oldRoute) {
				if(strcmp("SpeakerAndMicrophone", CFStringGetCStringPtr(oldRoute, CFStringGetSystemEncoding())) == 0) {
					old = AudioInputRouteType_SpeakerAndMicrophone;
				} else if(strcmp("HeadphonesAndMicrophone", CFStringGetCStringPtr(oldRoute, CFStringGetSystemEncoding())) == 0) {
					old = AudioInputRouteType_HeadphonesAndMicrophone;
				} else if(strcmp("HeadsetInOut", CFStringGetCStringPtr(oldRoute, CFStringGetSystemEncoding())) == 0) {
					old = AudioInputRouteType_HeadsetInOut;
				}
			} else {
				//이전라우터 찾기 실패: 에러
			}
			
			CFStringRef newRoute;
			UInt32 size; size = sizeof(CFStringRef);
			OSStatus error = AudioSessionGetProperty(kAudioSessionProperty_AudioRoute, &size, &newRoute);
			if(error) {
				//새로운라우터 찾기 실패: 에러
			} else {
                if(strcmp("SpeakerAndMicrophone", CFStringGetCStringPtr(newRoute, CFStringGetSystemEncoding())) == 0) {
					new = AudioInputRouteType_SpeakerAndMicrophone;
				} else if(strcmp("HeadphonesAndMicrophone", CFStringGetCStringPtr(newRoute, CFStringGetSystemEncoding())) == 0) {
					new = AudioInputRouteType_HeadphonesAndMicrophone;
				} else if(strcmp("HeadsetInOut", CFStringGetCStringPtr(newRoute, CFStringGetSystemEncoding())) == 0) {
					new = AudioInputRouteType_HeadsetInOut;
				}
			}
			
			//라우터 변경
			input->eventRouteChange(input->userReference, old, new);
		}	
	} else if(inID == kAudioSessionProperty_AudioInputAvailable) {
		if (inDataSize == sizeof(UInt32)) {
			UInt32 isAvailable = *(UInt32*)inData;
			input->eventAvailable(input->userReference, (bool)isAvailable);
		}
	}
}

//오디오입력(성량->입력데이터) 핸들러
void AudioInputBufferHandler(void* inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer,
							 const AudioTimeStamp* inStartTime, UInt32 inNumberPacketDescriptions,
							 const AudioStreamPacketDescription* inPacketDescs) {
	AudioInput* input = (AudioInput*)inUserData;
	AudioInputQueue* inputQueue = input->privatePtr;
	
	UInt32 data_sz = sizeof(AudioQueueLevelMeterState) * input->channelNum;
	AudioQueueGetProperty(inputQueue->queue, kAudioQueueProperty_CurrentLevelMeterDB, inputQueue->meter, &data_sz);
	float* avrPower = calloc(input->channelNum, sizeof(float));
	float* peakPower = calloc(input->channelNum, sizeof(float));
	int i;
	for(i = 0; i < input->channelNum; i++) {
		avrPower[i] = inputQueue->meter[i].mAveragePower;
		peakPower[i] = inputQueue->meter[i].mPeakPower;
	}
	input->eventMeter(input->userReference, input->channelNum, avrPower, peakPower);
	free(avrPower);
	free(peakPower);
	
	unsigned long bufferSize = inBuffer->mAudioDataByteSize;
	signed long* buffer = inBuffer->mAudioData;
	input->eventInput(input->userReference, bufferSize, buffer);
	
	AudioQueueEnqueueBuffer(inAQ, inBuffer, 0, NULL);
}

//오디오 입력 버퍼사이즈 계산
int AudioInputComputeRecordBufferSize(AudioInput* input, const AudioStreamBasicDescription *format, float seconds) {
	AudioInputQueue* inputQueue = input->privatePtr;
	
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
			AudioQueueGetProperty(inputQueue->queue, kAudioQueueProperty_MaximumOutputPacketSize, &maxPacketSize, &propertySize);
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

//메모리및 초기화
AudioInput* AudioInputInit(void* userReference, 
						   void (*eventInput)(void* userReference, unsigned long inputDataLength, signed long* inputData),
						   void (*eventInterrupt)(void* userReference),
						   void (*eventRouteChange)(void* userReference, AudioInputRouteType oldRoute, AudioInputRouteType newRoute),
						   void (*eventAvailable)(void* userReference, bool isAvailable),
						   void (*eventMeter)(void* userReference, unsigned long channelNum, float* mAveragePower, float* mPeakPower)) {
	AudioInput* input = calloc(1, sizeof(AudioInput));
	
	input->isRecording = false;
	
	input->userReference = userReference;
	
	input->eventInput = eventInput;
	input->eventInterrupt = eventInterrupt;
	input->eventRouteChange = eventRouteChange;
	input->eventAvailable = eventAvailable;
	input->eventMeter = eventMeter;
	
	return input;
}

//삭제(입력정지->메모리해제)
void AudioInputFree(AudioInput** input) {
	AudioInputStop(*input);
	free(*input);
	*input = NULL;
}

//입력시작(오디오세션이 초기화 되어있지 않으면 설정)
bool AudioInputStart(AudioInput* input, float second) {
	if(input->isRecording) {
		return false;
	} else {
		input->privatePtr = calloc(1, sizeof(AudioInputQueue));
		AudioInputQueue* inputQueue = input->privatePtr;
		
		input->second = second;
		
		if(!input->initedAUsession) {
			//오디오 세션
			OSStatus error = AudioSessionInitialize(NULL, NULL, AudioInputInterruptionListener, input);
			if(error) {
				printf("오디오 세션 AudioSessionInitialize 실패 : AudioSessionInitialize\n");
				abort();
			} else {
				UInt32 category = kAudioSessionCategory_PlayAndRecord;	
                
                
				error = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(category), &category);
				if(error) {
					printf("오디오 세션 AudioSessionSetProperty 실패: kAudioSessionCategory_PlayAndRecord\n");
					abort();
				}
				
				CFStringRef route;
				UInt32 size = sizeof(CFStringRef);
				OSStatus error = AudioSessionGetProperty(kAudioSessionProperty_AudioRoute, &size, &route);
				if(error) {
					printf("오디오 세션 AudioSessionGetProperty 실패: kAudioSessionProperty_AudioRoute\n");
					abort();
				} else {
					input->eventRouteChange(input->userReference, 0, 0);
				}
				
				error = AudioSessionAddPropertyListener(kAudioSessionProperty_AudioRouteChange, AudioInputPropertyListener, input);
				if(error) {
					printf("오디오 세션 AudioSessionAddPropertyListener 실패: kAudioSessionProperty_AudioRouteChange\n");
					abort();
				}
				
				UInt32 inputAvailable = 0;
				size = sizeof(inputAvailable);
				error = AudioSessionGetProperty(kAudioSessionProperty_AudioInputAvailable, &size, &inputAvailable);
				if(error) {
					printf("오디오 세션 AudioSessionGetProperty 실패: kAudioSessionProperty_AudioInputAvailable\n");
					abort();
				} else {
					input->eventAvailable(input->userReference, (bool)inputAvailable);
				}
				
				error = AudioSessionAddPropertyListener(kAudioSessionProperty_AudioInputAvailable, AudioInputPropertyListener, input);
				if(error) {
					printf("오디오 세션 AudioSessionAddPropertyListener 실패: kAudioSessionProperty_AudioInputAvailable\n");
					abort();
				}
                
                
                /*삽입소스 마이크로 안나오고 드바이스에서 귀쪽으로 나오는 부분 해결*/
                UInt32 audioRouteOverride = kAudioSessionOverrideAudioRoute_Speaker;
                AudioSessionSetProperty ( 
                                         kAudioSessionProperty_OverrideAudioRoute,                         
                                         sizeof (audioRouteOverride),                                      
                                         &audioRouteOverride                                            
                                         );
                /*삽입소스*/
                
				
				error = AudioSessionSetActive(true); 
				if (error) {
					printf("오디오 세션 AudioSessionSetActive 실패\n");
					abort();
				}
			}
			input->initedAUsession = true;
		}
		
		memset(&input->recordFormat, 0, sizeof(input->recordFormat));
		
		//오디오세션(입력샘플레이트)
		UInt32 size = sizeof(input->recordFormat.mSampleRate);
		AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareSampleRate, &size, &input->recordFormat.mSampleRate);
		
		//오디오세션(입력채널)
		size = sizeof(input->recordFormat.mChannelsPerFrame);
		AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareInputNumberChannels, &size, &input->recordFormat.mChannelsPerFrame);
		
		//셋팅
		input->recordFormat.mFormatID = kAudioFormatLinearPCM;
		input->recordFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
		input->recordFormat.mBitsPerChannel = 16;
		input->recordFormat.mBytesPerPacket = input->recordFormat.mBytesPerFrame = (input->recordFormat.mBitsPerChannel / 8) * input->recordFormat.mChannelsPerFrame;
		input->recordFormat.mFramesPerPacket = 1;
		
		//오디오 큐 셋팅값으로 시작
		AudioQueueNewInput(&input->recordFormat, AudioInputBufferHandler, input, NULL, NULL, 0, &inputQueue->queue);
		
		//오디오 큐 셋팅후 값 가져오기
		size = sizeof(input->recordFormat);
		AudioQueueGetProperty(inputQueue->queue, kAudioQueueProperty_StreamDescription, &input->recordFormat, &size);
		
		//사이즈 계산해서 큐 메모리 잡기
		int bufferByteSize = AudioInputComputeRecordBufferSize(input, &input->recordFormat, second);
		for(int i = 0; i < AudioInputBufferSize; ++i) {
			AudioQueueAllocateBuffer(inputQueue->queue, bufferByteSize, &inputQueue->buffers[i]);
			AudioQueueEnqueueBuffer(inputQueue->queue, inputQueue->buffers[i], 0, NULL);
		}
		
		//채널
		input->channelNum = input->recordFormat.mChannelsPerFrame;
		
		//미터(성량)
		inputQueue->meter = (AudioQueueLevelMeterState*)calloc(input->channelNum, sizeof(AudioQueueLevelMeterState));
		UInt32 val = 1;
		AudioQueueSetProperty(inputQueue->queue, kAudioQueueProperty_EnableLevelMetering, &val, sizeof(UInt32));
		
		AudioQueueSetParameter(inputQueue->queue, kAudioQueueParam_Volume, 1.0);
		
		//큐시작
		AudioQueueStart(inputQueue->queue, NULL);
		
		input->isRecording = true;
		
		return true;
	}
}

void AudioInputSetIsAwake(AudioInput* input, bool isAwake) {
    AudioInputQueue* inputQueue = input->privatePtr;
    if(isAwake == false) {
        AudioQueuePause(inputQueue->queue);
    } else {
        AudioQueueStart(inputQueue->queue, NULL);
    }
}

//입력중지
bool AudioInputStop(AudioInput* input) {
	if(input->isRecording) {
		input->isRecording = false;
		AudioInputQueue* inputQueue = input->privatePtr;
        
		//큐중단
		AudioQueueStop(inputQueue->queue, true);
		
		//큐삭제
		AudioQueueDispose(inputQueue->queue, true);
		
		//큐메모리 삭제
		for(int i = 0; i < AudioInputBufferSize; ++i) {
			AudioQueueFreeBuffer(inputQueue->queue, inputQueue->buffers[i]);
		}
		
		//미터 삭제
		if(inputQueue->meter) {
			free(inputQueue->meter);
			inputQueue->meter = NULL;
		}
		
		free(inputQueue);
		inputQueue = NULL;
		return true;
	} else {
		return false;
	}
}

#undef AudioInputBufferSize
