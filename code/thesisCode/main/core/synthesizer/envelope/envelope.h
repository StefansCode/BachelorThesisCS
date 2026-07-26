#ifndef ENVELOPE_H
#define ENVELOPE_H
#include "stdint.h"
#include "adapter/timer/timer.h"

class Envelope {
private:

  Timer &timer;

  /** @brief time it takes to rise from 0 to 255 
   * MIN 0 : 0 seconds
   * MAX 255 : 16 seconds
   * STEP : 62 ms (1/16 second)
  */
  int attack = 0;
  /** @brief time it takes to fall from from 255 to sustain level 
   * MIN 0 : 0 seconds
   * MAX 255 : 16 seconds
   * STEP : 62 ms (1/16 second)
  */
  int decay = 0;
  /** @brief the level at which the output stays when holding.
  */
  int sustain = UINT8_MAX;
  /** @brief time it takes to fall from sustain level to 0 
   * MIN 0 : 0 seconds
   * MAX 255 : 16 seconds
   * STEP : 62 ms (1/16 second)
  */
  int release = 0;

  int returnValue;
  uint8_t returnValueAtrelease;
  uint64_t timeAtpress;
  uint64_t lastTimerValue;
  bool lastPressValue;
public:
  Envelope(Timer &timer);
  void set(uint8_t attack_, uint8_t decay_, uint8_t sustain_, uint8_t release_);
  void get(uint8_t *attack_, uint8_t *decay_, uint8_t *sustain_, uint8_t *release_);
  void calculateValue(bool pressed, uint64_t currentTime);
  uint8_t apply(bool pressedInput);
};

#endif // ENVELOPE_H