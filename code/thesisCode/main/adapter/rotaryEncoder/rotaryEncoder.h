#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "../pinDefines.h"
#include "driver/pulse_cnt.h"

class RotaryEncoder {

public:
  RotaryEncoder();
  void init();
  int getvalue();
  void resetvalue();
};

extern RotaryEncoder encoder;

#endif // ROTARY_ENCODER_H