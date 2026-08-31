#ifndef SOUND_H
#define SOUND_H
#include <math.h>

#include "config.h"
#include "signal/signal.h"

#if STANDART_SAMPLE_RATE == 32768
  #if BITS_PER_SAMPLE_ == 16
    #include "sineTable32768.h"
  #elif BITS_PER_SAMPLE_ == 32
    #include "sineTable32768_32Bit.h"
  #endif
#elif STANDART_SAMPLE_RATE == 16384
  #if BITS_PER_SAMPLE_ == 16
    #include "sineTable16384.h"
  #elif BITS_PER_SAMPLE_ == 32
    #include "sineTable16384_32Bit.h"
  #endif
#elif STANDART_SAMPLE_RATE == 44100
  #include "sineTable44100.h"
#elif STANDART_SAMPLE_RATE == 22050
  #include "sineTable22050.h"
#elif STANDART_SAMPLE_RATE == 11025
  #include "sineTable11025.h"
#else
  #error "Unsupported STANDART_SAMPLE_RATE. Please use 44100, 22050, or 11025."
#endif
#include "noiseTable.h"

class Sound {
private:
  Signal<sample, SOUND_BUFFER_SIZE> signal;
  unsigned int time = 0;

public:
  Sound &fromSilence();
  Sound &fromSine(unsigned int frequency);
  Sound &fromTriangle(unsigned int frequency);
  Sound &fromSquare(unsigned int frequency);
  Sound &fromSaw(unsigned int frequency);
  Sound &fromNoise();

  Sound &applyFunction(sample (*func)(sample data, void *param), void *param);
  Sound &applyFunction(sample (*func)(sample *data, void *param), void *param);

  Sound &amplify(float value);
  Sound &add(Sound &other);
  Sound &add(sample value);

  sample returnValue();
  sample *returnBuffer();

private:
  sample calculateSaw(unsigned int frequency);
};

#endif // SOUND_H