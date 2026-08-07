#ifndef SIGNAL_H
#define SIGNAL_H
#include "config.h"

class Signal {
private:
  sample buffer[BUFFER_SIZE] = {0};
  unsigned int index = 0;
  unsigned int size = BUFFER_SIZE;

public:

  Signal& fromFunction(sample (*input)(void *param), void *param);
  Signal& fromValue(sample value);

  Signal& applyFunction(sample (*func)(sample data, void *param), void *param);

  Signal& add(Signal &other);
  Signal& add(sample value);

  Signal& multiply(Signal &other);
  Signal& multiply(sample value);
  Signal& multiply(float value);

  Signal& FourierTransform();

  void toFunction(void (*output)(sample data, void *param), void *param);
  void toFunction(void (*output)(sample *data, void *param), void *param);
};

#endif // SIGNAL_H