#ifndef GENERATOR_H
#define GENERATOR_H
#include <math.h>

#include "config.h"
#include "signal/signal.h"

class Sound {
private:
  Signal signal;
  uint64_t time;

public:
  Sound& fromSaw(unsigned int frequency);
  Sound& fromSine(unsigned int frequency);
  Sound& fromSquare(unsigned int frequency);
  Sound& fromTriangle(unsigned int frequency);

  Sound& amplify(float value);

  void toFunction(void (*output)(sample data, void *param), void *param);
  void toFunction(void (*output)(sample *data, void *param), void *param);

private:
  int calculateSaw(unsigned int frequency);
};

#endif // GENERATOR_H