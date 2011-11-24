#include "AudioRecoder.h"
#include <stdlib.h>
#include <string.h>

AudioRecoder* AudioRecoderInit(const char* recordPath) {
	AudioRecoder* recorder = calloc(1, sizeof(AudioRecoder));
	recorder->path = calloc(strlen(recordPath) + 1, sizeof(char));
	sprintf(recorder->path, "%s", recordPath);
	return recorder;
}

void AudioRecoderFree(AudioRecoder** recorder) {
	AudioRecoderStop(*recorder);
	remove((*recorder)->path);
	
	free((*recorder)->path);
	(*recorder)->path = NULL;
	
	free(*recorder);
	*recorder = NULL;
}

bool AudioRecoderStart(AudioRecoder* recorder) {
	if(recorder->isRecoding) {
		return false;
	} else {
		recorder->isRecoding = true;
		recorder->file = fopen(recorder->path, "w");
		return true;
	}
}

bool AudioRecoderWrite(AudioRecoder* recorder, void* data, long dataLength, float factor) {
	if(recorder->isRecoding) {
		int size = (int)((float)dataLength / (float)sizeof(signed long) / factor);
		signed long tmp[size];
		signed long* tmpptr = tmp;
		signed long* dataptr = data;
		for(int i = 0; i < size; i++) {
			*tmpptr = dataptr[(int)(i * factor)];
			tmpptr++;
		}
		fwrite(tmp, sizeof(signed long), size, recorder->file);
		//fwrite(data, 1, dataLength, recorder->file);
		return true;
	} else {
		return false;
	}
}

bool AudioRecoderStop(AudioRecoder* recorder) {
	if(recorder->isRecoding) {
		fclose(recorder->file);
		recorder->file = NULL;
		recorder->isRecoding = false;
		return true;
	} else {
		return false;
	}
}

