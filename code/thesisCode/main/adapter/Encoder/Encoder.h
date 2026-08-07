#ifndef ENCODER_H
#define ENCODER_H

#include "../pinDefines.h"
#include "driver/pulse_cnt.h"
#include "adapter/threadSaveVariable/threadSaveVariable.h"

class Encoder {
public:
  Encoder();
  void init();
  int getvalue();
  int getLastValue();
  void resetvalue();
  void changeExternalValue(ThreadSaveInt &value, int min, int max, int step);

private:
  int lastEncoderValue = 0;
};

extern Encoder encoder;

#endif // ENCODER_H