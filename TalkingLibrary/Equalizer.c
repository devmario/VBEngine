#include "Equalizer.h"
#include <stdlib.h>
#include "chuck_fft.h"
#include <limits.h>
#include <math.h>

Equalizer* EqualizerInit(unsigned long outputDataLength,
						 void* userReference,
						 void (*eventEqualizer)(void* userReference, unsigned long outputDataLength, float* outputData)) {
	Equalizer* eq = calloc(1, sizeof(Equalizer));
	
	eq->outputDataLength = outputDataLength;
	eq->outputData = calloc(eq->outputDataLength, sizeof(float));
	eq->userReference = userReference;
	eq->eventEqualizer = eventEqualizer;
	
	return eq;
}

void EqualizerFree(Equalizer** eq) {
	free((*eq)->outputData);
	(*eq)->outputData = NULL;
	free(*eq);
	*eq = NULL;
}

void EqualizerCompute(Equalizer* eq, unsigned long inputDataLength, signed long* inputData) {
	float buffer[inputDataLength];
	int i = 0;
	for(i = 0; i < inputDataLength; i++) {
		buffer[i] = (float)inputData[i] / INT_MAX;
	}
	
	rfft(buffer, eq->outputDataLength, FFT_FORWARD);
	
	complex* cbuf = (complex*)buffer;
	for(i = 0; i < eq->outputDataLength; i++) {
		eq->outputData[i] = cmp_abs(cbuf[i]);
	}
	
	eq->eventEqualizer(eq->userReference, eq->outputDataLength, eq->outputData);
}
