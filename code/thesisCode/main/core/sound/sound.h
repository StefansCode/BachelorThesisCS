#ifndef SOUND_H
#define SOUND_H
#include <math.h>

#include "config.h"
#include "signal/signal.h"

class Sound {
private:
  Signal<sample, SOUND_BUFFER_SIZE> signal;
  uint64_t time = 0;
  unsigned int sampleRate = STANDART_SAMPLE_RATE;

public:
  void setSampleRate(unsigned int sampleRate) {
    this->sampleRate = sampleRate;
  }

  Sound& fromSilence();
  Sound& fromSaw(unsigned int frequency);
  Sound& fromSine(unsigned int frequency);
  Sound& fromSquare(unsigned int frequency);
  Sound& fromTriangle(unsigned int frequency);

  Sound &applyFunction(sample (*func)(sample data, void *param), void *param);
  Sound &applyFunction(sample (*func)(sample *data, void *param), void *param);

  Sound& amplify(float value);
  Sound& add(Sound &other);
  Sound& add(sample value);

  sample returnValue();
  sample* returnBuffer();

private:
  int calculateSaw(unsigned int frequency);
};

#endif // SOUND_H

/**
 * Generate: 17 ms, Amplify: 3 ms, Amplify (Variable): 8 ms,Add(random): 246 ms, Add: 3 ms, Output: 2 ms
 */