#ifndef __AudioRecoder_H__
#define __AudioRecoder_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include <stdbool.h>
	
	typedef struct AudioRecoder AudioRecoder;
	
	struct AudioRecoder {
		char* path;
		FILE* file;
		
		bool isRecoding;
	};
	
	AudioRecoder* AudioRecoderInit(const char* recordPath);
	void AudioRecoderFree(AudioRecoder** recorder);
	
	bool AudioRecoderStart(AudioRecoder* recorder);
	bool AudioRecoderWrite(AudioRecoder* recorder, void* data, long dataLength, float factor);
	bool AudioRecoderStop(AudioRecoder* recorder);
	
#ifdef __cplusplus
}
#endif

#endif