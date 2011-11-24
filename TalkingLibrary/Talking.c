#include "Talking.h"
#include <stdlib.h>
#include "AudioInput.h"
#include "Equalizer.h"
#include "AudioRecoder.h"
#include "AudioPlayer.h"
#include <AudioToolbox/AudioToolbox.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioUnit/AudioComponent.h>
#include <AudioToolbox/AudioQueue.h>

typedef struct TalkingPrivate TalkingPrivate;

struct TalkingPrivate {
	AudioInput* input;
	Equalizer* eq;
	AudioRecoder* rec;
	AudioPlayer* player;
};

void AudioInputEventInput(void* userReference, unsigned long inputDataLength, signed long* inputData) {
	Talking* talking = userReference;
	TalkingPrivate* talkingPrivate = talking->ptr;
	AudioRecoder* recorder = talkingPrivate->rec;
	Equalizer* eq = talkingPrivate->eq;
	
	if(talking->status == TalkingStatus_Recording || talking->status == TalkingStatus_Record_Waiting) {
		EqualizerCompute(eq, inputDataLength, inputData);
	}
	
	if(talking->status == TalkingStatus_Recording) {
		if(talking->event.eventExtensionTalking) {
			inputDataLength /= sizeof(signed long);
			talking->event.eventExtensionTalking(talking->event.userReference, &inputDataLength, &inputData);
			inputDataLength *= sizeof(signed long);
		}
	}
	
	if(talking->status == TalkingStatus_Recording) {
		AudioRecoderWrite(recorder, inputData, inputDataLength, 1.0 / talking->pitch);
	}
}

void AudioOutputEventOutput(void* userReference, unsigned long inputDataLength, signed long* inputData) {
	Talking* talking = userReference;
	TalkingPrivate* talkingPrivate = talking->ptr;
	Equalizer* eq = talkingPrivate->eq;
	if(talking->status == TalkingStatus_Play) {
		EqualizerCompute(eq, inputDataLength, inputData);
	}
}

void AudioInputEventInterrupt(void* userReference) {
	Talking* talking = userReference;
	talking->event.eventInputEventInterrupt(talking->event.userReference);
}

void AudioInputEventRouteChange(void* userReference, AudioInputRouteType oldRoute, AudioInputRouteType newRoute) {
	Talking* talking = userReference;
	talking->event.eventInputEventRouteChange(talking->event.userReference, oldRoute, newRoute);
}

void AudioInputEventAvailable(void* userReference, bool isAvailable) {
	Talking* talking = userReference;
	talking->event.eventInputEventAvailable(talking->event.userReference, isAvailable);
}

void AudioInputEventMeter(void* userReference, unsigned long channelNum, float* averagePower, float* peakPower) {
	Talking* talking = userReference;
	TalkingPrivate* talkingPrivate = talking->ptr;
	AudioRecoder* recorder = talkingPrivate->rec;
	AudioInput* input = talkingPrivate->input;
	talking->event.eventMeter(talking->event.userReference, channelNum, averagePower, peakPower);
	if(talking->status == TalkingStatus_Record_Waiting) {
		if(talking->recordStartVolumePower != 0.0) {
			if((*peakPower + 50.0) / 50.0 > talking->recordStartVolumePower) {
				AudioRecoderStart(recorder);
				talking->status = TalkingStatus_Recording;
				talking->event.eventStartTalking(talking->event.userReference);
			}
		}
		if(talking->recordStartVolumeAverage != 0.0) {
			if((*averagePower + 50.0) / 50.0 > talking->recordStartVolumeAverage) {
				AudioRecoderStart(recorder);
				talking->status = TalkingStatus_Recording;
				talking->event.eventStartTalking(talking->event.userReference);
			}
		}
	} else if(talking->status == TalkingStatus_Recording) {
		if(talking->recordEndVolumePower != 0.0) {
			if((*peakPower + 50.0) / 50.0 < talking->recordEndVolumePower) {
				talking->status = TalkingStatus_Play_Ready;
				AudioRecoderStop(recorder);
				talking->event.eventExtensionFilePathTalking(talking->event.userReference, recorder->path);
				AudioInputStop(input);
				talking->event.eventEndTalking(talking->event.userReference);
			}
		}
		if(talking->recordEndVolumeAverage != 0.0) {
			if((*averagePower + 50.0) / 50.0 < talking->recordEndVolumeAverage) {
				talking->status = TalkingStatus_Play_Ready;
				AudioRecoderStop(recorder);
				talking->event.eventExtensionFilePathTalking(talking->event.userReference, recorder->path);
				AudioInputStop(input);
				talking->event.eventEndTalking(talking->event.userReference);
			}
		}
	}
}
void AudioOutputEventMeter(void* userReference, unsigned long channelNum, float* averagePower, float* peakPower) {
	Talking* talking = userReference;
	talking->event.eventMeter(talking->event.userReference, channelNum, averagePower, peakPower);
}

void EqualizerEvent(void *userReference, unsigned long outputDataLength, float *outputData) {
	Talking* talking = userReference;
	talking->event.eventEqualizer(talking->event.userReference, outputDataLength, outputData);
}

void AudioPlayerEventEnded(void* userReference) {
	Talking* talking = userReference;
	talking->status = TalkingStatus_Play_Ended;
	talking->event.eventPlayEndedTalking(talking->event.userReference);
}

TalkingPrivate* TalkingPrivateInit(const char* recordPath, Talking* talking) {
	TalkingPrivate* talkingPrivate = calloc(1, sizeof(TalkingPrivate));
	talkingPrivate->eq = EqualizerInit(talking->equalizerSize, talking, EqualizerEvent);
	talkingPrivate->player = AudioPlayerInit(recordPath, talking, AudioPlayerEventEnded,
											 AudioOutputEventMeter,
											 AudioOutputEventOutput);
	talkingPrivate->rec = AudioRecoderInit(recordPath);
	talkingPrivate->input = AudioInputInit(talking, 
										   AudioInputEventInput,
										   AudioInputEventInterrupt,
										   AudioInputEventRouteChange,
										   AudioInputEventAvailable,
										   AudioInputEventMeter);
	return talkingPrivate;
}

void TalkingPrivateFree(TalkingPrivate** talkingPrivate) {
	AudioPlayerFree(&(*talkingPrivate)->player);
	AudioRecoderFree(&(*talkingPrivate)->rec);
	AudioInputFree(&(*talkingPrivate)->input);
	EqualizerFree(&(*talkingPrivate)->eq);
	free(*talkingPrivate);
	*talkingPrivate = NULL;
}

TalkingEvent TalkingEventInit(void* userReference,
							  void (*eventMeter)(void* userReference, unsigned long channelNum, float* averagePower, float* peakPower),
							  void (*eventEqualizer)(void* userReference, unsigned long dataLength, float* data),
							  void (*eventStartTalking)(void* userReference),
							  void (*eventEndTalking)(void* userReference),
							  void (*eventExtensionTalking)(void* userReference, unsigned long* inputDataLength, signed long** inputData),
							  void (*eventExtensionFilePathTalking)(void* userReference, char* recordFilePath),
							  void (*eventPlayTalking)(void* userReference),
							  void (*eventPlayEndedTalking)(void* userReference),
							  void (*eventInputEventInterrupt)(void* userReference),
							  void (*eventInputEventRouteChange)(void* userReference, TalkingRouteType oldRoute, TalkingRouteType newRoute),
							  void (*eventInputEventAvailable)(void* userReference, bool isAvailable)) {
	TalkingEvent event;
	event.userReference = userReference;
	event.eventMeter = eventMeter;
	event.eventEqualizer = eventEqualizer;
	event.eventStartTalking = eventStartTalking;
	event.eventEndTalking = eventEndTalking;
	event.eventExtensionTalking = eventExtensionTalking;
	event.eventExtensionFilePathTalking = eventExtensionFilePathTalking;
	event.eventPlayTalking = eventPlayTalking;
	event.eventPlayEndedTalking = eventPlayEndedTalking;
	event.eventInputEventInterrupt = eventInputEventInterrupt;
	event.eventInputEventRouteChange = eventInputEventRouteChange;
	event.eventInputEventAvailable = eventInputEventAvailable;
	return event;
}

Talking* TalkingInit(const char* recordPath, TalkingEvent event, unsigned int equalizerSize,
					 float recordStartVolumePower, float recordEndVolumePower,
					 float recordStartVolumeAverage, float recordEndVolumeAverage,
					 float recordMaxTime, float pitch) {
	Talking* talking = calloc(1, sizeof(Talking));
	talking->event = event;
	talking->equalizerSize = equalizerSize;
	talking->recordStartVolumePower = recordStartVolumePower;
	talking->recordEndVolumePower = recordEndVolumePower;
	talking->recordStartVolumeAverage = recordStartVolumeAverage;
	talking->recordEndVolumeAverage = recordEndVolumeAverage;
	talking->recordMaxTime = recordMaxTime;
	talking->pitch = pitch;
    
	talking->ptr = TalkingPrivateInit(recordPath, talking);
	return talking;
}

void TalkingFree(Talking** talking) {
	TalkingPrivateFree((TalkingPrivate**)&(*talking)->ptr);
	free(*talking);
	*talking = NULL;
}

bool TalkingRecord(Talking* talking) {
	if(talking->status == TalkingStatus_Play_Ended) {
		TalkingPrivate* talkingPrivate = talking->ptr;
		AudioInputStart(talkingPrivate->input, 1.0 / 60.0);
		talking->status = TalkingStatus_Record_Waiting;
		return true;
	} else {
		return false;
	}
}

bool TalkingPlay(Talking* talking) {
	if(talking->status == TalkingStatus_Play_Ready) {
		TalkingPrivate* talkingPrivate = talking->ptr;
		AudioPlayerStart(talkingPrivate->player, talkingPrivate->input->recordFormat, 1.0 / 60.0);
		talking->status = TalkingStatus_Play;
		talking->event.eventPlayTalking(talking->event.userReference);
		return true;
	} else {
		return false;
	}
}

bool isTalkingAwake = true;

void TalkingSetIsAwake(Talking* talking, bool isAwake) {
    if(isTalkingAwake != isAwake) {
        isTalkingAwake = isAwake;
        if(talking->status == TalkingStatus_Record_Waiting || talking->status == TalkingStatus_Recording) {
            TalkingPrivate* talkingPrivate = talking->ptr;
            AudioInputSetIsAwake(talkingPrivate->input, isAwake);
        } else if(talking->status == TalkingStatus_Play) {
            TalkingPrivate* talkingPrivate = talking->ptr;
            AudioPlayerSetIsAwake(talkingPrivate->player, isAwake);
        }
    }
}