#ifndef __Equalizer_H__
#define __Equalizer_H__

#ifdef __cplusplus
extern "C" {
#endif
	
	typedef struct Equalizer Equalizer;
	
	struct Equalizer {
		unsigned long outputDataLength;
		float* outputData;
		
		void* userReference;
		void (*eventEqualizer)(void* userReference, unsigned long outputDataLength, float* outputData);
	};
	
	Equalizer* EqualizerInit(unsigned long outputDataLength,
							 void* userReference,
							 void (*eventEqualizer)(void* userReference, unsigned long outputDataLength, float* outputData));
	void EqualizerFree(Equalizer** eq);
	
	void EqualizerCompute(Equalizer* eq, unsigned long inputDataLength, signed long* inputData);
	
#ifdef __cplusplus
}
#endif

#endif